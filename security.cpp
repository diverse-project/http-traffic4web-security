#include "json.hpp"

#define d 256

using namespace std;
using json = nlohmann::json;

json model;
bool isNumber(const std::string &str) {    
  return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}
int main(){
	freopen ("mfile.txt","r",stdin);
	cin >> model; 
	for (json::iterator it = model.begin(); it != model.end(); ++it) {
        if(it.key() == "paths"){
        	json m1 = it.value();
        	for (json::iterator it1 = m1.begin(); it1 != m1.end(); ++it1) {
			        string path = it1.key();
			        json m2 = it1.value();
			        for (json::iterator it2 = m2.begin(); it2 != m2.end(); ++it2) {
					        string method = it2.key();
					        std::transform(method.begin(), method.end(), method.begin(),[](unsigned char c){ return std::toupper(c); });
					        json m3 = it2.value();
					        for (json::iterator it3 = m3.begin(); it3 != m3.end(); ++it3) {
					        	int flag = 0;
					        	if(it3.key() == "responses"){
					        		json m4 = it3.value();
					        		for (json::iterator it4 = m4.begin(); it4 != m4.end(); ++it4) {
					        			if (it4.key() == "429"){
											flag = 1;
										}
					        		}
					        		if(!flag){
										cout << RED << "[!] Response code 429 not defined in \"" << path << "\" for " << method << " request" << RESET <<  endl;
									}
					        	}
					        }
					        
					}

					
			}

        }

	}

	set<string> pathsset;
	for (json::iterator it = model.begin(); it != model.end(); ++it) {
	    if(it.key() == "paths"){
	        json model1 = it.value();
	        for (json::iterator it1 = model1.begin(); it1 != model1.end(); ++it1) {
	                pathsset.insert(it1.key());
	        }
	    }
	}
	map<string,vector<string>> index;
	for(auto xx: pathsset){
		auto rr = xx.end();
		while(--rr != xx.begin()){
			if(*rr == '/'){
				string left = string(xx.begin(),rr);
				string right = string(rr+1,xx.end());
				if(isNumber(right))	index[left].push_back(right);

			} 
		}
	}
	for(auto path : index){
		cout << YELLOW << "[!] WARNING Possibility of ID enumeration on \"" << path.first << "\"" << RESET << endl;
	}



	/*
	vector<vector<int>> foldertree;
	int id = 0;
	map<string,int> roots;
	map<int,map<string,int>> index;
	map<int,string> foldername;
	for(string path : pathsset){
	    auto folderarray = split(path,"/");
	    assert(folderarray.size()>0);
	    int &rootid = roots[folderarray[0]];
	    if(rootid == 0) { // if new root take new id; roots are multiples of 1e7
	        id = 10000000 + id - id%10000000;
	        rootid = id;
	        foldername[rootid] = folderarray[0];
	    }
	    int parid = rootid;
	    for(int i = 1; i < foldersarray.size();i++){
	        int &nodeid = index[parid][foldersarray[i]];
	        if(nodeid !=0 ){
	            parid = nodeid;
	            continue;
	        }
	        if(nodeid == 0) nodeid = ++id;
	        foldertree[parid].push_back(nodeid);
	        foldername[nodeid] = folderarray[i];
	        parid = nodeid;
		    }
		}*/



	return 0;
}