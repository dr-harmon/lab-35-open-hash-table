# Lab 35: Open Hash Table

In this lab, you are to implement an "open" hash table. It should handle collisions by chaining to a singly-linked list. It should provide the following map ADT methods:

* `exists(k)`: Returns true if a value exists for the given key, false otherwise.
* `find(k)`: Returns the value for the given key, or throws an exception if there is no mapping for the key.
* `put(k,v)`: Adds a mapping of the given key to the given value, or replaces the current mapping with the given value if one already exists.
* `erase(k)`: Removes the mapping for the given key, or throws an exception if no such mapping exists.
* `getSize()`: Returns the current number of mappings in the hashtable.

You can assume that all keys are unique.

When you have implemented all of these methods, run the unit tests and make sure they all pass.

## Requirements

When implementing the hash table, you must:

* Fill in the methods of the provided `OpenHashMap` class.
* Define each bucket as a [`std::forward_list`](https://en.cppreference.com/w/cpp/container/forward_list), a singly-linked list implementation in the STL.
* Define each element in this list as a `std::pair`, where the first element in the pair is a key, and the second is its corresponding value.

## Hints

* Use the provided `HashtableEntry` type as an alias for elements in the hash table.
* Watch out for copy assignment! For example, `auto list = hashtable[index]` creates a copy of the list in the hashtable. Any modifications then apply to the _copy_ of the list, not the one in the hashtable. Instead, try `auto& list = hashtable[index]`.
* To convert a key to an integer, create a [`std::hash`](https://en.cppreference.com/w/cpp/utility/hash) and invoke its function object. For example: `std::hash<K>()(key)`.
* One way to erase elements in a `forward_list` is by keeping track of the previous element, then calling `erase_after` on that element. For example:

        auto prev = list.before_begin();
        for (auto i = list.begin(); i != list.end(); i++) {
            if (*i == ...) {
                list.erase_after(prev);
                break;
            }
            prev = i;
        }
