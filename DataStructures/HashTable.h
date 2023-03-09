#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../Helpers/Iterator.h"
#include "../Helpers/Tuple.cpp"

/**
 * @class HashTable
 * @brief A hash table data structure.
 * @tparam K The key type.
 * @tparam V The value type.
 */
template <class K, class V>
class HashTable
{
public:

    /**
     * Inserts the given key and value in the hash table.
     * 
     * @param key The key to insert.
     * @param value The value to insert.
     */
    virtual void insert(K key, V value) = 0;

    /**
     * Returns the value associated with the given key.
     * 
     * @param key The key to search.
     * 
     * @return The value associated with the given key.
     * 
     * @pre The key must be in the hash table.
     */
    virtual V get(K key) = 0;

    /**
     * Returns if the key is in the table.
     * 
     * @param key The key to search.
     * 
     * @return If the key is in the table.
     */
    virtual bool exists(K key) = 0;
    
    /**
     * Removes the key and value from the table.
     * 
     * @param key The key to remove.
     * 
     * @pre The key must be in the table.
     */
    virtual void remove(K key) = 0;

    
    /**
     * Returns the load factor of the table. λ=n/b (siendo n la cantidad de elementos y b la cantidad de buckets).
     * 
     * @return The load factor of the table.
     */
    virtual float getLoadFactor() = 0;

    /**
     * Returns the number of elements in the table.
     */
    virtual int getSize() = 0;
    
    /**
     * Returns an iterator to iterate over the elements of the table.
     */
    virtual Iterator<Tuple<K, V>> *getIterator() = 0;
};

#endif // HASH_TABLE_H