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
		//cout << "x is : " << x<<  endl;
		for(auto y : x){
			for(auto z : y.items()){
				json object = z.value();
				for(auto code : object.items()){
					if (code.key() == "429"){
						flag = 1;
					}
					
				}
				if(!flag){
					//cout << RED << "/!\\ Response code 429 not defined " << RESET <<  endl;
				}
			}
		}
	}

	for (json::iterator it = model.begin(); it != model.end(); ++it) {
        cout << it.key() << endl;
        if(it.key() == "paths"){
        	cout << it.value() << endl;

        }
	}

	return 0;
}