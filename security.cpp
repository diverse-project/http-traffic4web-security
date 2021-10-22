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
        if(it.key() == "paths"){
        	json m1 = it.value();
        	for (json::iterator it1 = m1.begin(); it1 != m1.end(); ++it1) {
			        string path = it1.key();
			        json m2 = it1.value();
			        for (json::iterator it2 = m2.begin(); it2 != m2.end(); ++it2) {
					        string method = it2.key();
					        json m3 = it2.value();
					        for (json::iterator it3 = m3.begin(); it3 != m3.end(); ++it3) {
					        	if(it3.key() == "responses"){
					        		m4 = it3.value();
					        		for (json::iterator it4 = m4.begin(); it4 != m4.end(); ++it4) {
					        			if (it4.key() == "429"){
											flag = 1;
										}
					        		}
					        		if(!flag){
										cout << RED << "/!\\ Response code 429 not defined in " << path << " for " << method << " method" << RESET <<  endl;
									}
					        	}
					        }
					        
					}

					
			}

        }

	}

	cout << "#############################" << endl;

	for (json::iterator it = model.begin(); it != model.end(); ++it) {
        if(it.key() == "paths"){
        	json model1 = it.value();
        	for (json::iterator it1 = model1.begin(); it1 != model1.end(); ++it1) {
			        cout << it1.key() << endl;
			        string path = it1.key();
			        vector<string> cpaths = split (path, '/');

			}

        }
	}

	return 0;
}