#include <iostream>
#include <string.h>
#include <vector>

typedef char trans;
using namespace std;

class TRANSFER{
	public:
		int sp;	//start point
		int ep;	//end point
		char sign;
	TRANSFER(int a, int b, char c) {
		sp = a;
		ep = b;
		sign = c;
	}

	int getSP() {
		return sp;
	}
	
	void setSP(int spp) {
		spp = sp;
	}

	int getEP() {
		return ep;
	}

	void setEP(int epp) {
		epp = ep;
	}

	char getSIGN() {
		return sign;
	}
	
	void setSIGN(char zz) {
		zz = sign;
	}

};
class RECHNER{
	public:
		int state;
		vector<trans> transfers;
		vector<int> endpoints;

	RECHNER(int s) {
		s = 0;
		state = s;
	}
	void INIT() {
		TRANSFER* TRANS = new TRANSFER(1, 2, 3);
	}
	void addTransfers(trans tr) {
		transfers.push_back(tr);
	}
	
	void addEndpoints(int eps) {
		endpoints.push_back(eps);
	}

	void input (char c) {
		for(const auto& trans: transfers) {
			if(state == TRANS.getSP() && c == TRANS.getSIGN()) {
				state = TRANS.getEP();
				break;
			}
		}
	bool test(String s) {
		vector<char> chars;

		for(const char& c : s) {
			chars.push_back(c);
			input(c);
		}

		if(find(endpoints.begin(), endpoints.end(), state) != endpoints.end()) {return true;} else {return false;}			
	}
	
	void testErgebnis(String s) {
		if(test(s) == true) {
			cout << "String accepted!" << endl;
		} else {
			cout << "String not accepted!" << endl;
		}
	}
    }
};
