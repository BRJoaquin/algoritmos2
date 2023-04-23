#ifndef HASH_TABLE_SEPARATE_CHAINING_IMP
#define HASH_TABLE_SEPARATE_CHAINING_IMP

#include "./HashTable.h"
#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"

/**
 * @brief A hash table implementation using separate chaining.
 *
 * @tparam K The key type.
 * @tparam V The value type.
 *
 * @see https://www.geeksforgeeks.org/hashing-set-2-separate-chaining/
 */
template <class K, class V>
class HashTableSeparateChaining : public HashTable<K, V>
{
private:
    /* It's a class that represents a node in a linked list */
    class Node
    {
    public:
        K key;
        V value;
        Node *next;
        Node(K key, V value, Node *next) : key(key), value(value), next(next) {}
    };

    // The array of linked lists
    Node **table;

    // Saves the count of the elements
    int elementCount;

    // Saves the size of the hash table (the size of the array)
    int buckets;

    // The hash function used to hash the keys
    int (*hashFunction)(K);

    // The compare function used to compare the keys and determinate if they are equal
    bool (*compareFunction)(K, K);

    /**
     * Private function that handles the insertion of a new element in the hash table (recursive).
     *
     * @param key The key of the element to insert.
     * @param value The value of the element to insert.
     * @param node The pointer to the node that will be the head of the linked list.
     */
    void insertRecursive(K key, V value, Node *&node)
    {
        if (node == NULL)
        {
            node = new Node(key, value, NULL);
            elementCount++;
        }
        else
        {
            // if the key already exists, update the value
            if (this->compareFunction(node->key, key))
            {
                node->value = value;
            }
            else
            {
                insertRecursive(key, value, node->next);
            }
        }
    }

    /**
     * Private function that handles the deletion of an element in the hash table (recursive).
     *
     * @param key The key of the element to delete.
     * @param node The pointer to the node that will be the head of the linked list.
     */
    void removeRecursive(K key, Node *&node)
    {
        if (node == NULL)
        {
            throw "Key not found";
        }
        else
        {
            if (this->compareFunction(node->key, key))
            {
                Node *toDelete = node;
                node = node->next;
                delete toDelete;
                elementCount--;
            }
            else
            {
                removeRecursive(key, node->next);
            }
        }
    }

public:
    /**
     * It creates a hash table with a given capacity and hash function.
     *
     * @param capacity The initial number of buckets in the hash table.
     * @param hashFunction This is a pointer to a function that takes in a key and returns an integer.
     * This function is used to hash the key and find the bucket where the key-value pair should be
     * stored.
     * @param compareFunction This is a function pointer that takes two keys as parameters and returns
     * a boolean value. This function is used to compare two keys.
     */
    HashTableSeparateChaining(int capacity, int (*hashFunction)(K), bool (*compareFunction)(K, K)) : buckets(capacity), hashFunction(hashFunction), compareFunction(compareFunction)
    {
        table = new Node *[buckets]();
        for (int i = 0; i < buckets; i++)
        {
            table[i] = NULL;
        }
    }

    /**
     * Inserts the given key and value in the hash table.
     * If the key already exists, the value is updated.
     *
     * @param key The key to be inserted.
     * @param value The value to be inserted into the hash table.
     */
    void insert(K key, V value)
    {
        int index = abs(hashFunction(key)) % buckets;
        this->insertRecursive(key, value, table[index]);
    }

    /**
     * Search and return the value of the given key.
     *
     * @param key The key of the element to be retrieved.
     *
     * @return The value associated with the key.
     *
     * @pre The key must exist in the hash table.
     */
    V get(K key)
    {
        assert(this->exists(key));
        int index = abs(hashFunction(key)) % buckets;
        Node *node = table[index];
        while (node != NULL)
        {
            if (this->compareFunction(node->key, key))
            {
                return node->value;
            }
            node = node->next;
        }
        throw "Key not found";
    }

    /**
     * If the key exists in the hash table, return true. Otherwise, return false
     *
     * @param key The key to search for.
     */
    bool exists(K key)
    {
        int index = abs(hashFunction(key)) % buckets;
        Node *node = table[index];
        while (node != NULL)
        {
            if (this->compareFunction(node->key, key))
            {
                return true;
            }
            node = node->next;
        }
        return false;
    }

    /**
     * If the key exists, then remove it.
     *
     * @param key The key of the element to be removed.
     */
    void remove(K key)
    {
        assert(this->exists(key));
        int index = abs(hashFunction(key)) % buckets;
        this->removeRecursive(key, table[index]);
    }

    /**
     * Returns the load factor of the hash table.
     */
    float getLoadFactor()
    {
        return (float)elementCount / buckets;
    }

    /**
     * Returns the number of elements in the hash table.
     */
    int getSize()
    {
        return elementCount;
    }

    /**
     * @brief Get the Iterator object
     */
    Iterator<Tuple<K, V>> *getIterator()
    {
        List<Tuple<K, V>> *list = new ListImp<Tuple<K, V>>();
        for (int i = 0; i < buckets; i++)
        {
            Node *aux = table[i];
            while (aux != NULL)
            {
                list->insert(Tuple<K, V>(aux->key, aux->value));
                aux = aux->next;
            }
        }
        return list->getIterator();
    }
};
#endif