#pragma once
#include <map>
#include <string>
#include "utensils/history_keeping_map.h"
#include "boost/unordered_map.hpp"
#include "boost/variant.hpp"

namespace spartsi {
    using name = std::string;
    template<typename Key, typename Value>
    using map = history_keeping_map<boost::unordered_map<Key, Value>>;

    struct attribute {
        std::string value, comment;
    };
    struct ref_attribute {
        std::string value, comment, ref_comment;
    };
    using attribute_variant = boost::variant<attribute, ref_attribute>;
    using attributes_map = map<name, attribute_variant>;

    struct node;
    struct ref_node;
    using nodes_variant = boost::variant<node, ref_node>;
    using nodes_map = map<name, nodes_variant>;

    struct node {
        std::string comment;
        nodes_map children;
        attributes_map attributes;
    };

    struct ref_node {
        std::string comment, ref_comment;
        nodes_map children;
        attributes_map attributes;
    };

    struct tree {
        spartsi::name name;
        std::string comment;
        nodes_map children;
        attributes_map attributes;
    };
}