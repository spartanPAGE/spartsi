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