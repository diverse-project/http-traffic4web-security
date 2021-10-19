#include "json.hpp"

#define d 256

using namespace std;
using json = nlohmann::json;

json model;

int main(){
	freopen ("mfile.txt","r",stdin);
	cin >> model; 
	int flag = 0;
	for(auto x : model["paths"]){
		for(auto y : x){
			for(auto z : y.items()){
				json object = z.value();
				for(auto code : object.items()){
					if (code.key() == "4000"){
						flag = 1;
					}
					
				}
				if(!flag){
					//cout << "status code 4000 not defined " <<  endl;
				}
			}
		}
	}

	for(json x : model["paths"]){
		cout << "x.key() is : " << x.key()<<  endl;
		for(json y : x){
			out << "y is : " << y <<  endl;
			out << "y.key() is : " << y.key()<<  endl;
		}
	}

	return 0;
}