#pragma once

#include <forward_list>
#include <functional>
#include <memory>
#include <utility>

template <typename K, typename V>
class OpenHashMap {
private:

    typedef std::forward_list<std::pair<K,V>> HashtableEntry;

    int size;
    int tableSize;

    std::unique_ptr<HashtableEntry[]> hashtable;

    int computeHash(K key) const {
        std::hash<K> keyHash;
        return keyHash(key) % tableSize;
    }

public:

    class KeyNotFoundException {};

    OpenHashMap(int tableSize) {
        this->size = 0;
        this->tableSize = tableSize;
        hashtable = std::make_unique<HashtableEntry[]>(tableSize);
    }

    bool exists(K key) const {
        int hash = computeHash(key);
        const auto& chain = hashtable[hash];
        for (const auto& pair : chain) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    const V& find(K key) const {
        const auto& chain = hashtable[computeHash(key)];
        for (const auto& pair : chain) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        throw KeyNotFoundException();
    }

    void put(K key, V value) {
        int hash = computeHash(key);
        auto& chain = hashtable[hash];
        for (auto& pair : chain) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        chain.emplace_front(key, value);
        size++;
    }

    void erase(K key) {
        if (!exists(key)) {
            throw KeyNotFoundException();
        }

        auto& chain = hashtable[computeHash(key)];
        auto prev = chain.before_begin();
        for (auto i = chain.begin(); i != chain.end(); i++) {
            if (i->first == key) {
                chain.erase_after(prev);
                size--;
                break;
            }

            prev = i;
        }
    }

    int getSize() const {
        return size;
    }
};
