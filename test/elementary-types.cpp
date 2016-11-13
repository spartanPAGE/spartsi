#include "elementary-types.h"
#include "catch.hpp"

TEST_CASE("everything compiles well", "[spartsi::elementary_types*") {
    spartsi::tree subject {
        "example tree",
        "with some example data",
        spartsi::nodes_map {
            { "node", spartsi::node {
                "comment", "ref comment"
            }}
        },
        spartsi::attributes_map {
            { "attr", spartsi::attribute {
                "value", "comment", "ref comment"
            }},

            { "attr 2", spartsi::attribute {
                "value 2", "comment 2", "ref comment 2"
            }}
        }
    };

    REQUIRE(subject.name == "example tree");
    REQUIRE(subject.comment == "with some example data");
    REQUIRE(subject.children.count("node"));
    REQUIRE(subject.children.at("node").comment == "comment");
    REQUIRE(subject.children.at("node").ref_comment == "ref comment");
    REQUIRE(subject.attributes.count("attr"));
    REQUIRE(subject.attributes.at("attr").value == "value");
    REQUIRE(subject.attributes.at("attr").comment == "comment");
    REQUIRE(subject.attributes.at("attr").ref_comment == "ref comment");
    REQUIRE(subject.attributes.count("attr 2"));
    REQUIRE(subject.attributes.at("attr 2").value == "value 2");
    REQUIRE(subject.attributes.at("attr 2").comment == "comment 2");
    REQUIRE(subject.attributes.at("attr 2").ref_comment == "ref comment 2");
}