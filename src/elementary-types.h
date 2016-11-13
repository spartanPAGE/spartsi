#pragma once
#include <map>
#include <string>
#include "utensils/history_keeping_map.h"
#include "boost/unordered_map.hpp"

namespace spartsi {
    using name = std::string;
    template<typename Key, typename Value>
    using map = history_keeping_map<boost::unordered_map<Key, Value>>;

    struct attribute {
        std::string value, comment, ref_comment;
    };
    using attributes_map = map<name, attribute>;

    struct node;
    using nodes_map = map<name, node>;

    struct node {
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