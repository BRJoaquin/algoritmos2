#include <string>
#include <iostream>
#include <limits>
#include <cassert>
using namespace std;

template <class K, class V>
class Node
{
public:
    K key;
    V value;
    Node *next;
    Node(K _key, V _value) : key(_key), value(_value), next(NULL){};
    Node(K _key, V _value, Node *_next) : key(_key), value(_value), next(_next){};
};

template <class K, class V>
class HashTable
{
private:
    Node<K, V> **table; // la tabla en si
    int N;              // la cant de elementos acutal
    int B;              // la cant de buckets/celdas
    int (*hash)(K);

    void addNode(Node<K, V> *&_ptrNode, K _key, V _value)
    {
        if (_ptrNode == NULL)
        {
            _ptrNode = new Node<K, V>(_key, _value);
            this->N++;
        }
        else
        {
            if (_ptrNode->key == _key)
            {
                _ptrNode->value = _value;
            }
            else
            {
                addNode(_ptrNode->next, _key, _value);
            }
        }
    }

    bool searchNode(Node<K, V> *_ptrNode, K _key)
    {
        if (_ptrNode == NULL)
        {
            return false;
        }
        else
        {
            if (_ptrNode->key == _key)
            {
                return true;
            }
            else
            {
                return searchNode(_ptrNode->next, _key);
            }
        }
    }

    V getValue(Node<K, V> *_ptrNode, K _key) {
        if (_ptrNode->key == _key)
        {
            return _ptrNode->value;
        }
        else
        {
            return getValue(_ptrNode->next, _key);
        }
    }

public:
    HashTable(int _B, int (*_hash)(K))
    {
        this->N = 0;
        this->B = _B;
        table = new Node<K, V> *[_B]();
        hash = _hash;
        for (int i = 0; i < B; i++)
        {
            table[i] = NULL;
        }
    }

    void add(K _key, V _value)
    {
        int bucket = this->hash(_key) % this->B;
        cout << bucket << endl;
        this->addNode(this->table[bucket], _key, _value);
    }

    bool exist(K _key) {
        int bucket = this->hash(_key) % this->B;
        return this->searchNode(this->table[bucket], _key);
    }

    // pre: la clave debe existir
    V get(K _key)
    {
        assert(this->exist(_key));
        int bucket = this->hash(_key) % this->B;
        return this->getValue(this->table[bucket], _key);
    }

    int getEmptyBucket() {
        int ret = 0;
        for (int i = 0; i < this->B; i++)
        {
            if(this->table[i] == NULL) {
                ret++;
            }
        }
        return ret;
    }

    void rehash(int _newB) {
        // creo la nueva tabla
        Node<K, V> ** newTable = new Node<K, V> *[_newB]();
        for (int i = 0; i < _newB; i++)
        {
            newTable[i] = NULL;
        }

        // recorrer todos los elmentos de la antigua tabla
        for (int oldBucket = 0; oldBucket < B; oldBucket++)
        {
            Node<K,V> * aux = this->table[oldBucket];
            while(aux != NULL) { // recorremos la lista
                // obtenemos la clave y valor de cada nodo
                K key = aux->key;
                V value = aux->value;
                // calculamos la nueva posicion 
                int newBucket = this->hash(key) % _newB;
                this->addNode(newTable[newBucket], key, value);
                // seguimos al siguiente nodo
                aux = aux->next;
            }
        }

        // delete old table
        // ...

        // reasignar los nuevos valores
        this->B = _newB;
        this->table = newTable;
    }
};

int hashASCII(string clave)
{
    int ret = 0;
    for (int i = 0; i < clave.size(); i++)
    {
        ret += clave[i];
    }
    return ret;
}

int hashASCIIv2(string clave)
{
    int ret = 0;
    for (int i = 0; i < clave.size(); i++)
    {
        ret += clave[i] * (i+1);
    }
    return ret;
}

int superFuncionDeHashQueSeLaReBanca(string clave)
{
    int h = 0;
    for (int i = 0; i < clave.size(); i++){
        h = 31 * h + int(clave[i]);
    }
    return abs(h);
}

std::string generateRandomName(int minLength = 3, int maxLength = 20) {
    // Characters to use in the names
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsLen = chars.length();
    
    // Generate random length within specified range
    int nameLength = minLength + std::rand() % (maxLength - minLength + 1);

    std::string name;
    for(int i = 0; i < nameLength; ++i) {
        name += chars[std::rand() % charsLen];
    }

    return name;
}

int main()
{
    int B = 20;
    HashTable<string, int> * miPrimeraAgenda = new HashTable<string, int>(B, superFuncionDeHashQueSeLaReBanca);
    miPrimeraAgenda->add("Joaco", 123);
    miPrimeraAgenda->rehash(40);
    if(miPrimeraAgenda->exist("Joaco")) {
        cout << "existe!" << endl;
    }else{
        cout << "no existe" << endl;
    }
}