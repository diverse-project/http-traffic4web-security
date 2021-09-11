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
			cout << "y's key is this : " << y.key() << endl;
			for(auto z : y){
				if(z.key()){
					cout << "whearas z is : " << z << endl;
				}
			}
		}
	}

	return 0;
}