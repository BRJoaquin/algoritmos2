#ifndef HASH_ABIERTO
#define HASH_ABIERTO

#include "./Table.h"

template <class K, class V>
class HashAbierto : public Table<K, V>
{
private:
    struct NodoLista
    {
        K key;
        V value;
        NodoLista *sig;
        NodoLista(K unKey, V unValue) : key(unKey), value(unValue), sig(NULL) {}
    };

    NodoLista **arr;

    int (*hash)(K);

    int buckets;

    int getBucket(K key)
    {
        int n = this->hash(key);
        return abs(n % this->buckets);
    }

    void insertRec(NodoLista *&nodoPtr, K key, V value)
    {
        if (nodoPtr == NULL)
        {
            nodoPtr = new NodoLista(key, value);
        }
        else
        {
            if (nodoPtr->key == key)
            {
                nodoPtr->value = value;
            }
            else
            {
                insertRec(nodoPtr->sig, key, value);
            }
        }
    }

    V getRec(NodoLista *nodoPtr, K key)
    {
        if (nodoPtr->key == key)
        {
            return nodoPtr->value;
        }
        else
        {
            return getRec(nodoPtr->sig, key);
        }
    }

    bool existsRec(NodoLista *&nodoPtr, K key)
    {
        if (nodoPtr == NULL)
        {
            return false;
        }
        if (nodoPtr->key == key)
        {
            return true;
        }
        else
        {
            return existsRec(nodoPtr->sig, key);
        }
    }

    void removeRec(NodoLista *&nodoPtr, K key)
    {
        if (nodoPtr->key == key)
        {
            NodoLista *toDelete = nodoPtr;
            nodoPtr = nodoPtr->sig;
            // delete toDelete;
        }
        else
        {
            removeRec(nodoPtr->sig, key);
        }
    }

public:
    HashAbierto(int capInicial, int (*_hash)(K))
    {
        arr = new NodoLista *[capInicial]();
        hash = _hash;
        for (int i = 0; i < capInicial; i++)
        {
            arr[i] = NULL;
        }
        buckets = capInicial;
    }

    void insert(K key, V value)
    {
        int bucket = this->getBucket(key);
        this->insertRec(arr[bucket], key, value);
    }

    V get(K key)
    {
        assert(this->exists(key));
        int bucket = this->getBucket(key);
        return this->getRec(arr[bucket], key);
    }

    bool exists(K key)
    {
        int bucket = this->getBucket(key);
        return this->existsRec(arr[bucket], key);
    }

    void remove(K key)
    {
        assert(this->exists(key));
        int bucket = this->getBucket(key);
        this->removeRec(arr[bucket], key);
    }
};
#endif