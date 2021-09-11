#include "json.hpp"

#define d 256

using namespace std;
using json = nlohmann::json;

json model;

int main(){
	freopen ("mfile.txt","r",stdin);
	cin >> model; 
	
	for(auto x : model["paths"].items()){
		//cout << x.key() << endl; // path
		for(auto y : x.items()){
			for(auto z : y.items()){
				cout << z.key() << endl;
			}
		}
	}

	return 0;
}