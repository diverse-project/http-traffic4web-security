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



#define d 256
 
void search(string pat, string txt, int q)
{
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
                cout<<"Pattern found at index "<< i<<endl;
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
		if(search("GET", req, 101)){
			cout << "you can find it in this req" << endl;
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