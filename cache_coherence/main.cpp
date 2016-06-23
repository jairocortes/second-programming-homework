#include "cache_multilevel.hh"

int main(){
	float access_counter = 0; //variable was used to estimate the miss-rate
	srand (time(NULL));
	string instruction; //it will contain the address string
	string address;
	string operation;
	unsigned int addr_hex; //it will contain the address in hexadecimal format
	MultilevelCache * mycache = new MultilevelCache(16,8,64);
	//This "While" will be to scroll through the instructions list
	while(getline(cin,instruction)){
		access_counter++;
		istringstream iss(instruction);
		vector<string> tokens;
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
		address = tokens.at(0);
		operation = tokens.at(1);
		stringstream ss;
		ss<<hex<<address;
		ss>>addr_hex; //now, "addr" contain the address in hexadecimal format
		//cout<<"Reading line  ----   address: "<<addr_hex<<" Operation: "<<operation<<endl;
		mycache->Processing(addr_hex, operation);
		}
	mycache->hits();
	mycache->printStates();
	delete mycache;
	return 0;

}