//#include <bits/stdc++.h>
//#include <tins/tins.h>
#include "json.hpp"
#define d 256

using namespace Tins;
using namespace std;



// compile using : c++ headers.cpp -ltins

ofstream myfile;
vector<string> v{"Cache-Control: no-store", "Content-Security-Policy: frame-ancestors 'none'", "Content-Type", "Strict-Transport-Security", "X-Content-Type-Options: nosniff", "X-Frame-Options: DENY"};
int q = 101;



/**************************************
              LPS function
***************************************/          
void lps_func(string txt, vector<int>&Lps){
    Lps[0] = 0;                   
    int len = 0;
    int i=1;
    while (i<txt.length()){
        if(txt[i]==txt[len]){   
            len++;
            Lps[i] = len;
            i++;
            continue;
        }
        else{                   
            if(len==0){         
                Lps[i] = 0;
                i++;
                continue;
            }
            else{              
                len = Lps[len-1];
                continue;
            }
        }
    }
}
/**************************************
              KMP Function
***************************************/  
void KMP(string pattern,string text){
    int n = text.length();
    int m = pattern.length();
    vector<int>Lps(m);
    int flag = 0;
    
    lps_func(pattern,Lps); 
    
    int i=0,j=0;
    while(i<n){
        if(pattern[j]==text[i]){i++;j++;} 
        if (j == m) { 
            cout<<"\033[1;32m[+] Header "<< pattern <<" found at index "<<i - m <<"\033[0m"<<endl;    
            j = Lps[j - 1]; 
	    flag = 1;
        } 
        else if (i < n && pattern[j] != text[i]) {  
            if (j == 0)          
                i++;
            else
                j = Lps[j - 1];  
        }
    }
    if(!flag){
	cout <<"\033[1;33m[!] Header "<< pattern <<" is not found \033[0m"<< endl;	
    }
}



bool handler(const PDU& pkt) {
    	// Lookup the TCP PDU
	const TCP &tcp = pkt.rfind_pdu<TCP>();
    	// Extract the RawPDU object.
	//const RawPDU& raw = tcp.rfind_pdu<RawPDU>();
	// Finally, take the payload (this is a vector<uint8_t>)
	/*const RawPDU::payload_type& payload = raw.payload(); 
	for(const auto &query : payload){
		cout << query;
	}*/

	if(tcp.sport() == 8080){
		string resp = "";
		const RawPDU& raw = tcp.rfind_pdu<RawPDU>();
		const RawPDU::payload_type& payload = raw.payload();

  		for(const auto &query : payload){
			resp += query;
		}
		if(resp[0] != '0'){
			cout << "\n\033[1;37m****************************************************\033[0m"<< endl;
			cout << "\n\033[1;37m                    New Request                \033[0m"<< endl;
			cout << "\n\033[1;37m****************************************************\033[0m\n"<< endl;
			cout << "\n\033[1;35m- Security Headers :\033[0m\n" << endl;
			for(auto x : v){
				KMP(x, resp);
			}
			cout << "\n\033[1;35m- DoS Attacks :\033[0m\n" << endl;
			//system("python3 pyflooder.py localhost 80 4000");
		
		}
  		
	}


    // We need source/destination port to be 53
    /*if (udp.sport() == 53 || udp.dport() == 53) {
        // Interpret it as DNS. This might throw, but Sniffer catches it
        DNS dns = pkt.rfind_pdu<RawPDU>().to<DNS>();
        // Just print out each query's domain name
        for (const auto &query : dns.queries()) {
            std::cout << query.dname() << std::endl;
        }
    }*/
	
    	return true;
}



int main() {
	
	Sniffer("docker0").sniff_loop(handler);
	
}