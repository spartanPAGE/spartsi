#include "elementary_types.h"
#include "catch.hpp"

TEST_CASE("everything compiles well", "[spartsi::elementary_types*") {
    spartsi::tree subject {
        "example tree",
        "with some example data",
        spartsi::nodes_map {
            { "node", spartsi::ref_node {
                "comment", "ref comment"
            }}
        },
        spartsi::attributes_map {
            { "attr", spartsi::attribute {
                "value", "comment"
            }},

            { "attr 2", spartsi::ref_attribute {
                "value 2", "comment 2", "ref comment"
            }}
        }
    };

    SECTION("validate root data") {
        REQUIRE(subject.name == "example tree");
        REQUIRE(subject.comment == "with some example data");
        REQUIRE(subject.children.count("node"));
        REQUIRE(subject.attributes.count("attr"));
        REQUIRE(subject.attributes.count("attr 2"));
    }

    SECTION("validate node") {
        auto &node = boost::get<spartsi::ref_node>(subject.children.at("node"));
        REQUIRE(node.comment == "comment");
        REQUIRE(node.ref_comment == "ref comment");
    }

    SECTION("validate attr") {
        auto &attr = boost::get<spartsi::attribute>(subject.attributes.at("attr"));
        REQUIRE(attr.value == "value");
        REQUIRE(attr.comment == "comment");
    }

    SECTION("validate attr2") {
        auto &attr2 = boost::get<spartsi::ref_attribute>(subject.attributes.at("attr 2"));
        REQUIRE(attr2.value == "value 2");
        REQUIRE(attr2.comment == "comment 2");
        REQUIRE(attr2.ref_comment == "ref comment");
    }
}