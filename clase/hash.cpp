#include <iostream>
using namespace std;

template<class T>
class ClosedHash {
private:
    T** hashTable;
    bool *isDeleted;
    int length;
    int maxElements;
    int (*hashFunc)(T);

    bool isPrime(int num) {
        if(num <= 1) {
            return false;
        } else {
            for (int i = 2; i <= num/2; i++) {
                if(num % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    int nextPrime(int num) {
        while(!isPrime(++num));
        return num;
    }

public:
    ClosedHash(int maxElements, int (*hashFunc)(T)) {
        this->maxElements = nextPrime(maxElements);
        this->length = 0;
        this->hashTable = new T*[this->maxElements];
        this->isDeleted = new bool[this->maxElements]();
        for (int i = 0; i < this->maxElements; i++) {
            this->hashTable[i] = NULL;
        }
        this->hashFunc = hashFunc;
    }

    void add(T data) {
        // if this->length / this->maxElements > 0.5 then resize vec
        int position = this->hashFunc(data) % this->maxElements;
        while(this->hashTable[position]) {
            position = (position+1) % this->maxElements;
        }
        this->isDeleted[position] = false;
        this->hashTable[position] = new T(data);
    }

    bool exists(T data) {
        int position = this->hashFunc(data) % this->maxElements;
        int tries = 0;
        while (this->hashTable[position] != NULL || (this->isDeleted[position] && this->hashTable[position] == NULL )) {
            if (!this->isDeleted[position] && *this->hashTable[position] == data) {
                return true;
            }
            position = (position + 1) % this->maxElements; // Linear, DON'T USE THIS
            
            tries++;
            // If we've checked all positions and circled back, break to avoid infinite loop
            if(tries > this->maxElements) {
                break;
            }
        }
        return false;
    }

    void remove(T data) {
        int position = this->hashFunc(data) % this->maxElements;
        int tries = 0;
        while (this->hashTable[position] != NULL || (this->isDeleted[position] && this->hashTable[position] == NULL )) {
            if (!this->isDeleted[position] && *this->hashTable[position] == data) {
                delete this->hashTable[position];
                this->hashTable[position] = NULL;
                this->isDeleted[position] = true;
                break;
            }
            position = (position + 1) % this->maxElements; // Linear, DON'T USE THIS
            
            tries++;
            // If we've checked all positions and circled back, break to avoid infinite loop
            if(tries > this->maxElements) {
                break;
            }
        }
    }

    ~ClosedHash() {
        for (int i =0 ; i< this->maxElements ; i++){
            if(hashTable[i]){
                delete hashTable[i];
                hashTable[i] = NULL;
            }
        }
        delete[] hashTable;
        delete[] isDeleted;
    }
};

// DON'T USE THIS
int simpleHash(int data) {
    return data;
}

int main() {
    ClosedHash<int>* hash = new ClosedHash<int>(5, simpleHash);


    hash->add(1);
    hash->add(2);
    hash->add(5);
    hash->add(3);


    
    cout << "Does '3' exist? " << (hash->exists(3) ? "Yes" : "No") << endl;  // Expected: Yes

    hash->remove(3);

    cout << "Does '3' exist? " << (hash->exists(3) ? "Yes" : "No") << endl; // Expected: No

    cout << "Does '5' exist? " << (hash->exists(5) ? "Yes" : "No") << endl;  // Expected: Yes
    
    delete hash;
    return 0;
}