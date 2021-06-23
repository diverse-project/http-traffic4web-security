//#include <bits/stdc++.h>
//#include <tins/tins.h>
#include "json.hpp"

using namespace Tins;
using namespace std;
using json = nlohmann::json;


// compile using : c++ model.cpp -ltins

json model;
string method, path, code, req, resp;
set<string> tags;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;
 
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
 
    return result;
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
		method = req.substr(0, req.find(' '));
		std::transform(method.begin(), method.end(), method.begin(),
    [](unsigned char c){ return std::tolower(c); });

		vector<string> r = split(req, ' ');
		string str = r[1];
		vector<string> v = split (str, '/');
		path = "/" + v[2]; 
		tags.insert(v[2]);
		cout << req << endl;

	}else if(tcp.sport() == 8080){

		resp = "";

  		for(const auto &query : payload){
			resp += query;
		} 

		if(resp[0] != '0'){
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