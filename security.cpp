#include "json.hpp"

#define d 256

using namespace std;
using json = nlohmann::json;

json model;

int main(){
	freopen ("mfile.txt","r",stdin);
	cin >> model; 
	
	for(auto x : model["paths"]){
		//cout << "x.key() is " << x.key() << endl; // path
		for(auto y : x){
			cout << "y is this : " << y << endl;
			for(auto z : y.items()){
				cout << "whearas z is : " << z << endl;
				cout << "whearas z's key is : " << z.key() << endl;
				cout << "whearas z's value is : " << z.value() << endl;
				json object = z.value();
				cout << "object is : " << object << endl; 
				for(auto code : object.items()){
					if (code.key() == "200"){
						cout << "works";
					}
					cout << "code is : " << code << endl;
					cout << "code.key() is : " << code.key() << endl;
				}
				if(z.key() == "responses"){
					/*for(auto code : z.items()){
						cout << "code is : " << code << endl;
						cout << "code.key() is : " << code.key() << endl;
					}*/
				}
			}
		}
	}

	return 0;
}