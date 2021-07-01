//#include <bits/stdc++.h>
//#include <tins/tins.h>
#include "json.hpp"

using namespace Tins;
using namespace std;
using json = nlohmann::json;


// compile using : c++ traffic.cpp -ltins

json model;
string method, path, code, req, resp;
set<string> tags;


bool handler(const PDU& pkt) {
	const TCP &tcp = pkt.rfind_pdu<TCP>();
	const RawPDU& raw = tcp.rfind_pdu<RawPDU>();
	const RawPDU::payload_type& payload = raw.payload(); 

	if(tcp.dport() == 8080){
		req = "";
		for(const auto &query : payload){
			req += query;
		} 
		cout << req << endl;

	}else if(tcp.sport() == 8080){

		resp = "";

  		for(const auto &query : payload){
			resp += query;
		} 

		if(resp[0] != '0'){
			cout << resp << endl; 
		}
  		
	}
	
    cout << "###########################" << endl;
    return true;
}



int main() {
	
	Sniffer("docker0").sniff_loop(handler);
	
}