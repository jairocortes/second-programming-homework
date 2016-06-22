#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#ifndef BLOCKCLASS
#define BLOCKCLASS

enum{
	MODIFIED = 0,
	EXCLUSIVE,
	SHARED,
	INVALID
};

class Block{							
private:
	unsigned int tag, valid, dirty, flag;
public:
	Block(){tag =0; valid=0; dirty=0; flag=INVALID;}
	~Block(){};
	bool isValid() {return valid==1;}
	bool cmpTag(unsigned int dirTag) {return tag == dirTag;}
	void setAsValid() {this->valid=1;}
	void setTag(unsigned int dirTag){this->tag=dirTag;}
	void setFlag(int flag){this->flag = flag;}
	int getFlag(){return flag;}
	void invalidate(){this->flag = INVALID;}
	};
	
#endif

#ifndef CACHECLASS
#define CACHECLASS

class Cache{
private:
	unsigned int index, tag;
	unsigned int offset_bits, blocks_bits;
	int cache_size, block_size, blocks_num, hit_count, miss_count;
	Block * iterator;
public:
	Cache(int, int);
	~Cache(void);
	int getHitCount(void){return hit_count;}
	int getMissCount(void){return miss_count;}
	bool dataReq(unsigned int);
	void bringsBlock(unsigned int);
	void writeBack(unsigned int);
	int blockState(void);
	void changeState(int);
	};

#endif
