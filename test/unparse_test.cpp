#include "unparse.h"
#include "catch.hpp"

TEST_CASE("unparse_attribute_value", "[spartsi::unparse*]") {
    SECTION("empty value") {
        REQUIRE(spartsi::unparse_attribute_value("").at(0) == "\"\"");
    }

    SECTION("singleline value") {
        REQUIRE(spartsi::unparse_attribute_value("sample value").at(0) == "\"sample value\"");
    }

    SECTION("multiline value") {
        auto input = "some\nmultiline\nvalues";
        spartsi::lines desired_result = {
            "\"some\"", "\"multiline\"", "\"values\""
        };
        REQUIRE(spartsi::unparse_attribute_value(input) == desired_result);
    }
}

TEST_CASE("unparse_comment", "[spartsi::unparse*") {
    SECTION("empty comment") {
        for(auto i = 0; i < 10; ++i) {
            auto lines = spartsi::unparse_comment(std::string(i, ' '));
            REQUIRE(lines.size() == 1);
            INFO(i);
            REQUIRE(lines.at(0) == "::");
        }
    }

    SECTION("singleline comment") {
        auto lines = spartsi::unparse_comment("sample comment");
        REQUIRE(lines.size() == 1);
        REQUIRE(lines.at(0) == ":: sample comment");
    }

    SECTION("multiline comment") {
        auto input = "    some\n    multiline \n  comment ";
        spartsi::lines desired_result = {
            ":: some", ":: multiline", ":: comment"
        };
        REQUIRE(spartsi::unparse_comment(input) == desired_result);
    }
}