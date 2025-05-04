#include <anixart/Api.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <functional>
#include <codecvt>

#include <io.h>
#include <fcntl.h>

#include <conio.h>

using namespace anixart;

static void press_any_key() {
	std::cout << "Press any key to end... ";
	(void)_getch();
}

static std::string ask_for_input(std::string_view message) {
	std::wstring wout;
	std::string out;
	std::cout << message;
	std::getline(std::wcin, wout, L'\n');
	out.resize(wout.length());
	WideCharToMultiByte(CP_UTF8, 0, wout.data(), wout.length(), out.data(), out.size(), 0, 0);
	return out;
}

template<typename T>
	requires requires { typename T::value_type; }
int64_t ask_for_index(const T& arr, const std::function<void(const typename T::value_type&)>& print_func) {
	for (const auto& item : arr) {
		static int i = 0;
		std::cout << i++ << ": ";
		print_func(item);
	}
	size_t index;
	std::cout << "Index: ";
	std::wcin >> index;
	if (index >= arr.size()) {
		std::cout << "Index out of bounds" << std::endl;
		return -1;
	}
	return index;
}

int main() {
	std::atexit(press_any_key);
	_setmode(_fileno(stdin), _O_WTEXT);
	SetConsoleOutputCP(CP_UTF8);

	try {
		Api api("ru_RU", "release_info_tool", "1.0-1");
		api.set_verbose(false, false);
		requests::SearchRequest search_req;
		search_req.query = ask_for_input("Query: ");

		std::vector<Release::Ptr> search_resp = api.search().release_search(search_req, 0)->get();
		std::cout << "RELEASES" << std::endl;
		size_t release_index = ask_for_index(search_resp, [](const Release::Ptr& release) {
			std::cout << "[" << aux::to_string(release->id) << "] " << release->title_ru << std::endl;
			});
		if (release_index == -1) return -1;
		std::cout << std::endl;

		std::vector<EpisodeType::Ptr> types_resp = api.episodes().get_release_types(search_resp[release_index]->id);
		if (types_resp.size() == 0) {
			std::cout << "Failed to get release types. Use VPN" << std::endl;
			return -1;
		}
		std::cout << "TYPES" << std::endl;
		size_t type_index = ask_for_index(types_resp, [](const EpisodeType::Ptr& type) {
			std::cout << "[" << aux::to_string(type->id) << "] " << type->name << " (" << type->episodes_count << ")" << std::endl;
			});
		if (type_index == -1) return -1;
		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "UNKNOWN ERROR" << std::endl;
	}
}