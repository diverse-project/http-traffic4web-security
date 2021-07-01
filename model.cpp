//#include <bits/stdc++.h>
//#include <tins/tins.h>
#include "json.hpp"

#define d 256

using namespace Tins;
using namespace std;
using json = nlohmann::json;


// compile using : c++ model.cpp -ltins

json model;
string method, path, code, req, resp;
set<string> tags;
vector<string> methods{"GET", "POST", "PUT", "DELETE"}; 
//vector<string> methods{"GET", "POST", "PUT", "DELETE", "HEAD", "CONNECT", "OPTIONS", "TRACE", "PATCH"}; 

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
 
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
 
    return result;
}

 
bool search(string pat, string txt, int q){
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;
 
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++){
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
 
    for (i = 0; i <= N - M; i++){
        if ( p == t ){
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M){
                //cout<<"Pattern found at index "<< i<<endl;
                return true; 
            }
            
        }

        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
            if (t < 0)
            t = (t + q);
        }
    }
    return false;
}


bool handler(const PDU& pkt) {
	const TCP &tcp = pkt.rfind_pdu<TCP>();
	const RawPDU& raw = tcp.rfind_pdu<RawPDU>();
	const RawPDU::payload_type& payload = raw.payload(); 

	if(tcp.dport() == 8080){
		req = "";
		for(const auto &query : payload){
			req += query;
		} 
		for(auto x : methods){
			if(search(x, req, 101)){
				method = req.substr(0, req.find(' '));
				//std::transform(method.begin(), method.end(), method.begin(),[](unsigned char c){ return std::tolower(c); });
				vector<string> r = split(req, ' ');
				string str = r[1];
				vector<string> v = split (str, '/');
				path = "/" + v[2]; 
				tags.insert(v[2]);
				if(x != method){
					cout << "******* smthing is wrong *******" << endl;
					cout << x << " does not equal " << method << endl;
				}
			}
		}
		
		cout << req << endl;

	}else if(tcp.sport() == 8080){

		resp = "";

  		for(const auto &query : payload){
			resp += query;
		} 

		if(resp[0] != '0' && search("{", resp, 101)){
			//cout << resp; 
			string body = resp.substr(resp.find('{'), resp.length());
    		//json j = json::parse(body);
    		//cout << j.dump(4) << endl;
    		//cout << body << endl;	
    		code = resp.substr(resp.find(' ')+1, 3);
    		cout << code << endl;
    		model["paths"][path][method]["responses"][code]["description"] = "example of a description";  
		}
  		
	}
	model["tags"] = tags;
	//for(auto x : tags){
		
		//model["tags"][["description"]] = "insert description here";	
	//}
	cout << model.dump(4) << endl;
    cout << "###########################" << endl;
    return true;
}



int main() {
	model["openapi"] = "3.0.0"; 	
	model["externalDocs"]["description"] = "Find out more about OpenAPI generator";
	model["externalDocs"]["url"] = "https://openapi-generator.tech";
	cout << model.dump(4) << endl;
	Sniffer("docker0").sniff_loop(handler);
	
}