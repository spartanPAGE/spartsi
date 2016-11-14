#include "unparse.h"
#include "catch.hpp"

TEST_CASE("unparse_attribute_value", "[spartsi::unparse*]") {
    SECTION("empty value") {
        auto result = spartsi::unparse_attribute_value("");
        REQUIRE(result.size() == 1);
        REQUIRE(result.at(0) == "\"\"");
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
            INFO(i);
            REQUIRE(lines.size() == 0);
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

TEST_CASE("unparse(attribute)", "[spartsi::unparse*]") {
    SECTION("empty attribute") {
        spartsi::attribute attr {};
        auto result = spartsi::unparse("sample attr name", attr);
        spartsi::lines desired_result = {
            "attr sample attr name \"\""
        };
        REQUIRE(result == desired_result);
    }

    SECTION("attribute with singleline comment and singleline value") {
        spartsi::attribute attr = {
            "sample value", "sample comment"
        };
        auto result = spartsi::unparse("sample", attr);
        spartsi::lines desired_result = {
            ":: sample comment",
            "attr sample \"sample value\""
        };
        REQUIRE(result == desired_result);
    }

    SECTION("attribute with multiline comment and singleline value") {
        spartsi::attribute attr = {
            "sample value", "1st line\n2nd line"
        };
        auto result = spartsi::unparse("sample", attr);
        spartsi::lines desired_result = {
            ":: 1st line",
            ":: 2nd line",
            "attr sample \"sample value\""
        };
        REQUIRE(result == desired_result);
    }

    SECTION("attribute with singleline comment and multiline value") {
        spartsi::attribute attr = {
            "val line no. 1\nval line no. 2", "sample comment"
        };
        auto result = spartsi::unparse("sample", attr);
        spartsi::lines desired_result = {
            ":: sample comment",
            "attr sample \"val line no. 1\"",
            "            \"val line no. 2\""
        };
        REQUIRE(result == desired_result);
    }

    SECTION("attribute with multiline comment and multiline value") {
        spartsi::attribute attr = {
            "val line no. 1\nval line no. 2", "comment line no. 1\ncomment line no. 2"
        };
        auto result = spartsi::unparse("sample", attr);
        spartsi::lines desired_result = {
            ":: comment line no. 1",
            ":: comment line no. 2",
            "attr sample \"val line no. 1\"",
            "            \"val line no. 2\""
        };
        REQUIRE(result == desired_result);
    }
}