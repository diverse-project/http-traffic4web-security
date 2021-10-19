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
					if (code.key() == "200"){
						flag = 1;
					}
					
				}
				if(!flag){
					cout << "status code 200 not defined in "<< x<<  endl;
				}
			}
		}
	}

	return 0;
}