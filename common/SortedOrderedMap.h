#pragma once
#include <vector>
#include <algorithm>
#include <utility>

namespace sgc {

template<typename Key, typename Value>
class SortedOrderedMap {
public:
    void insert(const Key& key, const Value& value) {
        // Check if key already exists using linear search before sorting
        const auto existing = std::find_if(_data.begin(), _data.end(),
            [&key](const KeyValuePair& pair) {
                return pair.first == key;
            });
        
        if (existing != _data.end()) {
            // Key exists, update value
            existing->second = value;
        } else {
            // Key doesn't exist, add new pair
            _data.emplace_back(key, value);
        }
        
        // Sort the entire vector after insertion/update
        std::sort(_data.begin(), _data.end(), 
            [](const KeyValuePair& a, const KeyValuePair& b) {
                return a.first < b.first;
        });
    }
    
    // Find iterator by key using binary search
    auto find(const Key& key) const {
        const auto it = std::lower_bound(_data.begin(), _data.end(), 
            KeyValuePair{key, Value{}}, 
            [](const KeyValuePair& a, const KeyValuePair& b) {
                return a.first < b.first;
            });
        
        if (it != _data.end() && it->first == key) {
            return it;
        }
        
        return _data.end();
    }
    
    // Non-const version of find
    auto find(const Key& key) {
        const auto it = std::lower_bound(_data.begin(), _data.end(), 
            KeyValuePair{key, Value{}}, 
            [](const KeyValuePair& a, const KeyValuePair& b) {
                return a.first < b.first;
            });
        
        if (it != _data.end() && it->first == key) {
            return it;
        }
        
        return _data.end();
    }
    
    // Check if key exists
    bool contains(const Key& key) const {
        auto it = std::lower_bound(_data.begin(), _data.end(), 
            KeyValuePair{key, Value{}}, 
            [](const KeyValuePair& a, const KeyValuePair& b) {
                return a.first < b.first;
        });
        
        return it != _data.end() && it->first == key;
    }
    
    size_t size() const {
        return _data.size();
    }
    
    bool empty() const {
        return _data.empty();
    }
    
    void clear() {
        _data.clear();
    }

    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }
    auto begin() { return _data.begin(); }
    auto end() { return _data.end(); }

private:
    using KeyValuePair = std::pair<Key, Value>;
    std::vector<KeyValuePair> _data;
};

}