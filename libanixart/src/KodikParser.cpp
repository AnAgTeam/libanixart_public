#include <anixart/KodikParser.hpp>
#include <ext/base64.hpp>
#include <boost/regex.hpp>

// if set this to positive value, then KodikParser doesn't try to get it
constexpr int32_t UNIVERSAL_CAESAR_OFFSET = -1;
static_assert(UNIVERSAL_CAESAR_OFFSET < 0 || (0 <= UNIVERSAL_CAESAR_OFFSET && UNIVERSAL_CAESAR_OFFSET <= 26));

static constexpr size_t cstrlen(const char* const str) {
	return std::char_traits<char>::length(str);
}

static void extend_url_protocol(std::string& url) {
	if (!url.starts_with("http")) {
		url.insert(0, "https:");
	}
}

namespace anixart::parsers {
	constexpr std::string_view LINKS_URL_S = "https://kodik.biz/api/video-links?p=56a768d08f43091901c44b54fe970049&link=";
	constexpr std::string_view KODIK_INFO_HOST = "https://kodik.info";

	KodikParser::KodikParser() : _caesar_offset(UNIVERSAL_CAESAR_OFFSET) {
		_session.set_default_headers(get_default_headers());
	}

	bool KodikParser::valid_host(const std::string& host) const {
		if (host == "kodik.cc") {
			return true;
		}
		else if (host == "kodik.info") {
			return true;
		}
		else if (host == "aniqit.com") {
			return true;
		}
		return false;
	}

	std::string_view KodikParser::get_name() const {
		return "KodikParser";
	}

	std::unordered_map<std::string, std::string> KodikParser::extract_info_fallback(const std::string& url, const std::vector<ParserParameter>& params) {
		static const boost::regex ID_HASH_RE(R"(videoInfo.hash ?= ?(?:"|')(\w+)(?:"|'))");
		static const boost::regex URL_TYPE_ID_RE(R"(/(seria|video)/(\d+))");
		boost::smatch hash_match, type_id_match;
		if (!boost::regex_search(url, type_id_match, URL_TYPE_ID_RE)) {
			// cannot find serial id in url
			return {};
		}
		std::string serial_url = url.substr(0, url.find('?')); // no url parameters
		std::string serial_resp = _session.get_request(serial_url);
		if (!boost::regex_search(serial_resp, hash_match, ID_HASH_RE)) {
			// cannot find hash. error
			return {};
		}
		std::string serial_pdata;
		serial_pdata.reserve(cstrlen("type=&hash=&id=") + type_id_match[1].length() + hash_match[1].length() + type_id_match[2].length() + 1);
		serial_pdata.append("type=");
		serial_pdata.append(type_id_match[1]);
		serial_pdata.append("&hash=");
		serial_pdata.append(hash_match[1]);
		serial_pdata.append("&id=");
		serial_pdata.append(type_id_match[2]);

		network::JsonObject links_json = network::parse_json(_session.post_request("https://kodik.info/ftor", serial_pdata, "application/x-www-form-urlencoded"));
		if (!links_json.contains("links")) {
			// no links. :C
			return {};
		}
		if (_caesar_offset < 0) {
			// offset not initialized. Initialize it
			// TODO: maybe invalidate it after some time
			_caesar_offset = get_caesar_offset(serial_resp);
			if (_caesar_offset < 0) {
				// failed to initialize caesar offset. error
				return {};
			}
		}

		std::unordered_map<std::string, std::string> out;
		network::JsonObject& links = links_json["links"].as_object();
		for (auto& [res, enc_url_arr] : links) {
			network::JsonObject& enc_url_obj = enc_url_arr.as_array()[0].as_object();
			std::string url = boost::json::value_to<std::string>(enc_url_obj["src"]);
			if (!url.ends_with("manifest.m3u8")) {
				// base64 encoded url
				url = decode_url(url);
			}
			out[res] = url;
			extend_url_protocol(out[res]);
		}
		return out;
	}

	std::unordered_map<std::string, std::string> KodikParser::extract_info(const std::string& url, const std::vector<ParserParameter>& params) {
		process_params(params);

		size_t param_i = url.find('?'), pend_i = url.find(':');
		if (param_i == std::string::npos || pend_i == std::string::npos) {
			// error
			return {};
		}
		std::string url_link = url.substr(pend_i + 1, param_i - (pend_i + 1));
		std::string url_params = url.substr(param_i + 1);

		std::string links_url;
		links_url.reserve(LINKS_URL_S.length() + url_link.length() + 1 + url_params.length());
		links_url.append(LINKS_URL_S);
		links_url.append(url_link);
		links_url.append("&");
		links_url.append(url_params);

		std::unordered_map<std::string, std::string> out;
		network::JsonObject links_json = network::parse_json(_session.get_request(links_url));
		if (!links_json.contains("links")) {
			// Invalid sign. Idk the reason, but this problem from anixart. Try universal variant
			dbg_log("KodikParser: fallback...");
			return extract_info_fallback(url, params);
		}
		network::JsonObject& links = links_json["links"].as_object();
		for (auto& [k, v] : links) {
			out[k] = boost::json::value_to<std::string>(v.as_object()["Src"]);
			extend_url_protocol(out[k]);
		}

		return out;
	}
	int32_t KodikParser::get_caesar_offset(const std::string& serial_response) const {
		static const boost::regex SEASON_SCRIPT_RE(R"(/assets/js/app\.(?:season|player_single)\.[a-zA-Z0-9]+\.js)");
		static const boost::regex CAESAR_OFFSET_RE(R"(String\.fromCharCode\(\(e<="Z"\?90:122\)>=\(e=e\.charCodeAt\(0\)\+(\d+)\)\?e:e-\d+\))");
		boost::smatch season_script_match, caesar_offset_match;
		if (!boost::regex_search(serial_response, season_script_match, SEASON_SCRIPT_RE)) {
			return -1;
		}
		std::string app_season_resp = _session.get_request(std::string(KODIK_INFO_HOST) + season_script_match[0]);
		if (!boost::regex_search(app_season_resp, caesar_offset_match, CAESAR_OFFSET_RE)) {
			return -1;
		}
		return std::stol(caesar_offset_match[1]);
	}
	std::string KodikParser::decode_url(std::string_view encoded_url) const {
		std::string url_b64;
		const int src_endc = encoded_url.length() % 4;
		const size_t pad = src_endc == 0 ? 0ULL : (4ULL - src_endc);
		url_b64.reserve(encoded_url.length() + pad);
		for (const char& c : encoded_url) {
			if (std::isdigit(c)) {
				url_b64.push_back(c);
				continue;
			}
			url_b64.push_back(std::tolower(c) <= ('z' - _caesar_offset) ? c + _caesar_offset : c - (26 - _caesar_offset));
		}
		// add padding
		for (int i = 0; i < pad; ++i) {
			url_b64.push_back('=');
		}
		return base64::from_base64(url_b64);
	}
};
