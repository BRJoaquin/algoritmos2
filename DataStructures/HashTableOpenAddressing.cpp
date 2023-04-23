#ifndef HASH_TABLE_OPENING_ADDRESSING
#define HASH_TABLE_OPENING_ADDRESSING

#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"
#include "../Helpers/Tuple.cpp"
#include "./HashTable.h"
#include <cmath>


/**
 * Defines the different open addressing types.
 * @see https://www.geeksforgeeks.org/hashing-set-3-open-addressing/
 */
enum OpenAddressingType
{
    // https://en.wikipedia.org/wiki/Linear_probing
    LINEAR_PROBING,
    // https://en.wikipedia.org/wiki/Quadratic_probing
    QUADRATIC_PROBING,
    // https://en.wikipedia.org/wiki/Double_hashing
    DOUBLE_HASHING
};

/**
 * Implements HashTable using open addressing.
 *
 * @tparam K The key type.
 * @tparam V The value type.
 *
 * @see [more information](https://www.geeksforgeeks.org/hashing-set-3-open-addressing/)
 */
template <class K, class V>
class HashTableOpenAddressing : public HashTable<K, V>
{
private:
    // The table itself
    Tuple<K, V> **table;

    // The type of the open addressing
    OpenAddressingType type;

    // This help us to know if the element at some position is deleted or not
    // information needed when inserting, deleting and serching elements.

    /**
     * This help us to know if the element at some position is deleted or not
     * information needed when inserting, deleting and serching elements.
     * 
     * @see https://en.wikipedia.org/wiki/Lazy_deletion
     * @see https://stackoverflow.com/questions/9127207/hash-table-why-deletion-is-difficult-in-open-addressing-scheme
     */
    bool *isDeleted;

    // Saves the count of the elements
    int elementCount;

    // Saves the size of the hash table (the size of the array)
    int buckets;

    // The hash function used to hash the keys
    int (*hashFunction)(K);

    // A second hash function used only on double hashing
    int (*hashFunction2)(K);

    // The compare function used to compare the keys and determinate if they are equal
    bool (*compareFunction)(K, K);

    /**
     * The function calculates the index of the key in the hash table
     *
     * @param key The key to be hashed
     * @param tryCount The number of times we've tried to insert/search the key.
     *
     * @return The index of the bucket where the key should be stored.
     */
    int calculateIndex(K key, unsigned int tryCount)
    {
        // https://en.wikipedia.org/wiki/Linear_probing
        if (type == LINEAR_PROBING)
        {
            return abs(hashFunction(key) + tryCount) % buckets;
        }
        // https://en.wikipedia.org/wiki/Quadratic_probing
        else if (type == QUADRATIC_PROBING)
        {
            return abs(hashFunction(key) + pow(tryCount, 2)) % buckets;
        }
        // https://en.wikipedia.org/wiki/Double_hashing
        else if (type == DOUBLE_HASHING)
        {
            return abs(hashFunction(key) + tryCount * hashFunction2(key)) % buckets;
        }
        throw "Invalid open addressing type";
    }

public:
    /**
     * The constructor for the HashTableOpenAddressing class
     *
     * @param type The type of open addressing to use.
     * @param buckets The number of buckets in the hash table.
     * @param hashFunction The hash function to be used.
     * @param hashFunction2 This is the second hash function used in double hashing.
     */
    HashTableOpenAddressing(OpenAddressingType type, int buckets, int (*hashFunction)(K), int (*hashFunction2)(K), bool (*compareFunction)(K, K)) : type(type), buckets(buckets), hashFunction(hashFunction), hashFunction2(hashFunction2), compareFunction(compareFunction)
    {
        table = new Tuple<K, V> *[buckets]();
        isDeleted = new bool[buckets]();
        for (int i = 0; i < buckets; i++)
        {
            table[i] = NULL;
            isDeleted[i] = false;
        }
        elementCount = 0;
    }

    /**
     * If the key is already in the table, update the value. Otherwise, insert the key-value pair
     *
     * @param key The key to insert
     * @param value The value to insert into the table.
     */
    void insert(K key, V value)
    {
        // prevent insert
        assert(elementCount < buckets);

        int index = calculateIndex(key, 0);
        bool inserted = false;
        int tryCount = 1;
        while (!inserted)
        {
            // if is deleted or empty then insert the element
            if (isDeleted[index] || table[index] == NULL)
            {
                table[index] = new Tuple<K, V>(key, value);
                isDeleted[index] = false;
                elementCount++;
                inserted = true;
            }
            else
            {
                // if the key is already in the table, update the value
                if (compareFunction(table[index]->getFirst(), key))
                {
                    table[index]->setSecond(value);
                    inserted = true;
                }
                // in other case try in the next position
                else
                {
                    index = calculateIndex(key, tryCount);
                    tryCount++;
                }
            }
        }
    }

    /**
     * The key exists, return the value associated with it
     *
     * @param key The key of the element you want to get.
     *
     * @return The value of the key.
     */
    V get(K key)
    {
        assert(this->exists(key));
        int index = calculateIndex(key, 0);
        int tryCount = 1;
        bool found = false;
        while (!found)
        {
            if (!isDeleted[index] && compareFunction(table[index]->getFirst(), key))
            {
                return table[index]->getSecond();
            }
            else
            {
                index = calculateIndex(key, tryCount);
                tryCount++;
            }
        }
    }

    /**
     * If the key is not found, return false. If the key is found, return true
     *
     * @param key The key of the element you want to check if it exists.
     */
    bool exists(K key)
    {
        int index = calculateIndex(key, 0);
        bool found = false;
        int tryCount;
        while (!found)
        {
            if (isDeleted[index])
            {
                index = calculateIndex(key, tryCount);
            }
            else
            {
                if (table[index] == NULL)
                {
                    return false;
                }
                else
                {
                    if (compareFunction(table[index]->getFirst(), key))
                    {
                        return true;
                    }
                    else
                    {
                        index = calculateIndex(key, tryCount);
                    }
                }
            }
            tryCount++;
        }
        return false;
    }

    /**
     * Removes the key-value pair from the table. If the key is not found, do nothing.
     *
     * @param key The key of the element to be removed.
     */
    void remove(K key)
    {
        assert(this->exists(key));
        int index = calculateIndex(key, 0);
        int tryCount = 1;
        bool found = false;
        while (!found)
        {
            if (!isDeleted[index] && compareFunction(table[index]->getFirst(), key))
            {
                isDeleted[index] = true;
                table[index] = NULL;
                found = true;
                elementCount--;
            }
            else
            {
                index = calculateIndex(key, tryCount);
                tryCount++;
            }
        }
    }

    /**
     * The load factor is the number of elements in the hash table divided by the number of buckets
     *
     * @return The load factor of the hash table.
     */
    float getLoadFactor()
    {
        return (float)elementCount / buckets;
    }

    /**
     * Returns the number of elements in the array.
     */
    int getSize() { return elementCount; }

    /**
     * It returns an iterator for the hash table.
     */
    Iterator<Tuple<K, V>> *getIterator()
    {
        List<Tuple<K, V>> *list = new ListImp<Tuple<K, V>>();
        for (int i = 0; i < buckets; i++)
        {
            if (!isDeleted[i] && table[i] != NULL)
            {
                list->insert(*table[i]);
            }
        }
        return list->getIterator();
    }
};
#endif