#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

const char POLICE = 'P';

template <class T>
void print(vector<T>& v){
	cout << "Vector start: \n";
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "Vector end \n";
}

void solve(vector<int>& policemen, vector<int>& thieves, int maxDistance) {
	if(maxDistance > policemen.size() + thieves.size()){
	    cout << 0 << "\n";
	    return;
	}

    int thievesCatched = 0;
	int police = 0;
	int thief = 0;

	while(thief < thieves.size() && police < policemen.size()){
		int currentDistance = abs(thieves[thief] - policemen[police]);

		if(currentDistance <= maxDistance){
			thievesCatched++;
			police++;
			thief++;
		}else if(thieves[thief] < policemen[police]){
			thief++;
		}else{
			police++;
		}
	}

	cout << thievesCatched << " \n";
}

void processCase() {
	int k;
	cin >> k;
	int caseSize;
	cin >> caseSize;

	int index = 0; 
	vector<int> policemen;
	vector<int> thieves;

	while(caseSize > 0){
		char person;
		cin >> person;

		if(person == POLICE){
			policemen.push_back(index);
		}else{
			thieves.push_back(index);
		}

		index++;
		caseSize--;
	}

	//print(policemen);
	//print(thieves);

	solve(policemen, thieves, k);
}

int main() {
	int cases;
	cin >> cases;

	while(cases > 0){
		processCase();

		cases--;
	}

	return 0;
}
