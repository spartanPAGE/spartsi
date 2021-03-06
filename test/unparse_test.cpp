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

TEST_CASE("unparse(ref_attribute)", "[spartsi::unparse*]") {
    SECTION("empty attribute") {
        spartsi::ref_attribute attr = {};
        auto result = spartsi::unparse("ref", attr);
        spartsi::lines desired_declaration = {
            "ref attr ref"
        };
        spartsi::lines desired_definition = {
            "ref attr ref \"\""
        };

        REQUIRE(result.first == desired_declaration);
        REQUIRE(result.second == desired_definition);
    }

    SECTION("full-blown attribute") {
        spartsi::ref_attribute attr = {
            "v1\nv2\nv3", "declc1\ndeclc2\ndeclc3", "defc1\ndefc2\ndefc3"
        };
        auto result = spartsi::unparse("ref", attr);
        spartsi::lines desired_declaration = {
            ":: declc1",
            ":: declc2",
            ":: declc3",
            "ref attr ref"
        };
        spartsi::lines desired_definition = {
            ":: defc1",
            ":: defc2",
            ":: defc3",
            "ref attr ref \"v1\"",
            "             \"v2\"",
            "             \"v3\""
        };

        REQUIRE(result.first == desired_declaration);
        REQUIRE(result.second == desired_definition);
    }
}

TEST_CASE("unparse(attributes_map)", "[spartsi::unparse*]") {
    SECTION("full-blown attributes_map") {
        spartsi::attributes_map attrs = {
            { "1st attr", spartsi::attribute { "val", "comment" } },
            { "1st ref attr", spartsi::ref_attribute { "val", "comment", "ref comment" } },
            { "2nd ref attr", spartsi::ref_attribute { "val1\nval2", "comment", "ref comment" } },
            { "2nd attr", spartsi::attribute { "val1\nval2", "comment" } }
        };

        spartsi::lines desired_declaration = {
            ":: comment",
            "attr 1st attr \"val\"",
            ":: comment",
            "ref attr 1st ref attr",
            ":: comment",
            "ref attr 2nd ref attr",
            ":: comment",
            "attr 2nd attr \"val1\"",
            "              \"val2\""
        };

        spartsi::lines desired_definition = {
            ":: ref comment",
            "ref attr 1st ref attr \"val\"",
            ":: ref comment",
            "ref attr 2nd ref attr \"val1\"",
            "                      \"val2\""
        };
        auto result = spartsi::unparse(attrs);

        REQUIRE(result.first == desired_declaration);
        REQUIRE(result.second == desired_definition);
    }
}