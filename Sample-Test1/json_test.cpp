#include "pch.h"
#include <netsess/StringTools.hpp>
#include <netsess/JsonTools.hpp>

#pragma execution_character_set("utf-8")

using namespace network::json;

TEST_CASE("InlineJson::escape_string") {
	REQUIRE(
		InlineJson::escape_string("https://www.boost.org/doc/\"libs\"/1_80_0\\/libs/json/\n\t\rdoc/html/json/ref/boost\\__json__error.html  ") ==
		"https://www.boost.org/doc/\\\"libs\\\"/1_80_0\\\\/libs/json/\\n\\t\\rdoc/html/json/ref/boost\\\\__json__error.html  ");
}

TEST_CASE("InlineJson array serialization") {
	std::vector<std::string> arr = { "123123", "4444", "222" };
	REQUIRE(InlineJson::serialize(arr) == R"(["123123","4444","222"])");
}

TEST_CASE("InlineJson object creation") {
	std::string json;
	std::optional<int> opt_int;
	std::optional<int> opt_int_fill = 14;
	std::vector<int> arr = { 1, 2, 3 };

	InlineJson::open_object(json);
	InlineJson::append(json, "123123", 123123);
	InlineJson::append(json, "nullol", opt_int);
	InlineJson::append(json, "str", "12312332");
	InlineJson::append(json, "float", 14.4);
	InlineJson::append(json, "nonnull", opt_int_fill);
	InlineJson::append(json, "arr", arr);
	InlineJson::append(json, "escaped", "\r\n\\f");
	InlineJson::close_object(json);

	REQUIRE(json == R"({"123123":123123,"nullol":null,"str":"12312332","float":14.400000,"nonnull":14,"arr":[1,2,3],"escaped":"\r\n\\f"})");
}