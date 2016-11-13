#include "utensils/history_keeping_map.h"
#include "catch.hpp"

using hkmap = spartsi::history_keeping_map<int, int>;
using history = typename hkmap::history_type;

TEST_CASE("map can be created", "[spartsi::history_keeping_map]") {
    SECTION("without args") {
        auto subject = hkmap {};
        REQUIRE(subject.size() == 0);
    }

    SECTION("with initializer list") {
        auto subject = hkmap {
            {0, 1},
            {1, 2},
            {2, 3}
        };

        history desired_result = {0, 1, 2};
        REQUIRE(subject.history() == desired_result);
    }

    SECTION("with input iterators") {
        std::pair<int, int> data[] = {
            {0, 1}, {1, 2}, {2, 3}
        };

        auto subject = hkmap(std::begin(data), std::end(data));
        history desired_result = {0, 1, 2};
        REQUIRE(subject.history() == desired_result);
    }
}

TEST_CASE("history is being properly remembered", "[spartsi::history_keeping_map]") {
    auto subject = hkmap {
        {0, 1},
        {1, 2},
        {2, 3}
    };
    history desired_result = {0, 1, 2, 3};

    SECTION("with insertion") {
        subject.insert({3, 4});
        REQUIRE(subject.history() == desired_result);
    }

    SECTION("with [] accessor and new key") {
        subject[3] = 4;
        REQUIRE(subject.history() == desired_result);
    }

    SECTION("with [] accessor and key that`s already present in the container") {
        subject[0] = 2;
        history desired_result = {0, 1, 2};
        REQUIRE(subject.history() == desired_result);
    }

    SECTION("when data is being erased") {
        subject.erase(1);
        subject[1] = 2;
        desired_result = {0, 2, 1};
        REQUIRE(subject.history() == desired_result);
    }
}