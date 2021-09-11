#include "json.hpp"

#define d 256

using namespace std;
using json = nlohmann::json;

json model;

int main(){
	freopen ("mfile.txt","r",stdin);
	cin >> model; 
	
	for(auto x : model["paths"]){
		//cout << x.key() << endl; // path
		for(auto y : x){
			for(auto z : y){
				if(y.key() == "responses"){
					cout << z << endl;
				}
			}
		}
	}

	return 0;
}