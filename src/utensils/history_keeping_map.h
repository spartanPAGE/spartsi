#pragma once
#include <unordered_map>
#include <vector>

namespace spartsi {
    // TreeStructInfo spec implies that insertion order matters;
    // and becouse we want O(1) access (instead of O(n)), there shall be implemented container
    // with O(1) access and insertion history keeping
    // (the class shown below)
    template<typename Key, typename Value>
    class history_keeping_map {
    public:
        using key_type = Key;
        using value_type = Value;
    private:
        std::vector<key_type> keys_history;
        std::unordered_map<key_type, value_type> data;
    };
}