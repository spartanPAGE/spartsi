#pragma once
#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <cassert>

namespace spartsi {
    // TreeStructInfo spec implies that insertion order matters;
    // and becouse we want O(1) access (instead of O(n)), there shall be implemented container
    // with O(1) access and insertion history keeping
    // (the class shown below)
    template<typename Key, typename T>
    class history_keeping_map {
    public:
        using key_type = Key;
        using mapped_type = T;
        using data_type = std::unordered_map<key_type, mapped_type>;
        using value_type = typename data_type::value_type;
        using history_type = std::vector<key_type>;

        using iterator = typename data_type::iterator;
        using const_iterator = typename data_type::const_iterator;

        template<typename InputIterator>
        history_keeping_map(InputIterator first, InputIterator last):
            data(first, last)
        {
            set_keys_history(first, last);
        }

        history_keeping_map() {}

        history_keeping_map(std::initializer_list<value_type> il) {
            for(auto const &pair: il) {
                data.insert(pair);
                keys_history.push_back(pair.first);
            }
        }

        std::size_t erase(key_type const &k) {
            if(data.count(k)) {
                keys_history.erase(
                    std::remove(
                        std::begin(keys_history),
                        std::end(keys_history),
                        k
                    ),
                    std::end(keys_history)
                );
            }
            return data.erase(k);
        }


        mapped_type &operator[](key_type const &k) {
            if(!data.count(k)) {
                keys_history.push_back(k);
            }
            return data[k];
        }

        mapped_type &operator[](key_type &&k) {
            if(!data.count(k)) {
                keys_history.push_back(k);
            }
            return data[k];
        }

        mapped_type &at(const key_type &k) {
            return data.at(k);
        }

        mapped_type const &at(key_type &k) const {
            return data.at(k);
        }

        void insert(value_type const &val) {
            data.insert(val);
            keys_history.push_back(val.first);
        }

        std::size_t count(key_type const &k) const {
            return data.count(k);
        }

        std::size_t size() const noexcept {
            return data.size();
        }

        history_type const &history() const noexcept {
            return keys_history;
        }
    private:
        template<typename InputIterator>
        void set_keys_history(InputIterator first, InputIterator last) {
            keys_history = history_type(std::distance(first, last));
            std::transform(first, last, std::begin(keys_history), [](auto &&pair) {
                return pair.first;
            });
        }

        data_type data;
        history_type keys_history;
    };
}