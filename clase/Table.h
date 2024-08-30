#ifndef TABLE_H
#define TABLE_H

template <class K, class V>
class Table
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
};

#endif // TABLE_H