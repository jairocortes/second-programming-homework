#include "cache_multilevel.hh"

int main(){
	cout<<"print states"<<endl;
	cout<<"MODIFIED "<<MODIFIED<<endl;
	cout<<"EXCLUSIVE "<<EXCLUSIVE<<endl;
	cout<<"SHARED "<<SHARED<<endl;
	cout<<"INVALID "<<INVALID<<endl;
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
		address = instruction.substr(0,8);
		operation = instruction.substr(12,13);
		stringstream ss;
		ss<<hex<<address;
		ss>>addr_hex; //now, "addr" contain the address in hexadecimal format
		mycache->Processing(addr_hex, operation);
		}
	mycache->hits();
	delete mycache;
	return 0;

}