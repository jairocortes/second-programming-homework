#include "cache.hh"

using namespace std;

#ifndef MULTILEVELCACHECLASS
#define MULTILEVELCACHECLASS 

class MultilevelCache{
	private:
	unsigned int address;
	int cpu_iteartor, block_size, L1_size, L2_size;
	Cache *L1_CPU0, *L1_CPU1, *L2;
	Cache *actual, *other; //pointer to select the cache of the processor that is currently processing
	
	public:
	MultilevelCache(int, int, int);
	~MultilevelCache(void);
	void Processing(unsigned int, string);
	void hits(void);
};

#endif