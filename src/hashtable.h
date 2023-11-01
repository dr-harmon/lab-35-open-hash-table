#pragma once

#include <forward_list>
#include <functional>
#include <utility>

template <typename K, typename V>
class OpenHashMap {
private:

    typedef std::forward_list<std::pair<K,V>> HashtableEntry;

    int size;
    int tableSize;

public:

    OpenHashMap(int tableSize) {
        this->size = 0;
        this->tableSize = tableSize;
    }

    bool exists(K key) const {
        // TODO
    }

    const V& find(K key) const {
        // TODO
    }

    void put(K key, V value) {
        // TODO
    }

    void erase(K key) {
        // TODO
    }

    int getSize() const {
        return size;
    }
};
