#include "pch.h"
#include <netsess/StringTools.hpp>

#pragma execution_character_set("utf-8")

using namespace network;
using namespace anixart;

using namespace std::string_literals;

std::string_view operator""sv(const char* str, size_t len) {
	return std::string_view{ str, len };
}

TEST_CASE("StringTools::sformat") {
	REQUIRE(StringTools::sformat("sdfdsf%s 88888 %s llll %s", "fff"sv, "sdf"sv, "ggg"sv) == "sdfdsffff 88888 sdf llll ggg");
	REQUIRE(StringTools::sformat("%s%s", "hello, "s, "world"sv) == "hello, world");
}

TEST_CASE("StringTools::snformat") {
	REQUIRE(StringTools::snformat("content/%lld/page/%ld", 110033LL, 12323) == "content/110033/page/12323");
}