#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int captureThieves(vector<char>& arr, int k) {
    int n = arr.size();
    vector<int> thieves;
    vector<int> police;

    // Recolectar posiciones de policías y ladrones
    for (int i = 0; i < n; i++) {
        if (arr[i] == 'P') {
            police.push_back(i);
        } else if (arr[i] == 'T') {
            thieves.push_back(i);
        }
    }

    int captured = 0;
    int i = 0, j = 0;

    // Usar dos punteros para capturar ladrones de manera óptima
    while (i < police.size() && j < thieves.size()) {
        if (abs(police[i] - thieves[j]) <= k) {
            captured++;
            i++;
            j++;
        } else if (police[i] < thieves[j]) {
            i++;
        } else {
            j++;
        }
    }

    return captured;
}

int captureThievesV2(vector<char>& arr, int k) {
    int n = arr.size();
    vector<bool> captured(n, false);
    int capturedCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 'P') {
            for (int j = max(0, i - k); j <= min(n - 1, i + k); j++) {
                if (arr[j] == 'T' && !captured[j]) {
                    captured[j] = true;
                    capturedCount++;
                    break;
                }
            }
        }
    }

    return capturedCount;
}


// Función para generar casos de prueba
vector<char> generateTestCase(int n) {
    vector<char> arr(n, ' ');
    
    for(int i = 0; i < n; i++) {
        int random = rand() % 2;
        arr[i] = (random == 0) ? 'P' : 'T';
    }

    return arr;
}


int main() {
    for (int i = 0; i < 1000000; i++) {
        int n = rand() % 100 + 1;
        vector<char> arr = generateTestCase(n);
        int k = (rand() % 10) + 1;
        int res1 = captureThieves(arr, k);
        int res2 = captureThievesV2(arr, k);

        if (res1 != res2) {
            cout << "Test case failed" << endl;
            cout << "Input: " << endl;
            for (int i = 0; i < n; i++) {
                cout << arr[i];
            }
            break;
        }
    }
    return 0;
}
