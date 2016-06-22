#include "cache_multilevel.hh"

MultilevelCache::MultilevelCache(int block_size, int L1_size, int L2_size){
	this->cpu_iteartor = 0;
	this->address = 0;
	this->block_size = block_size;
	this->L1_size = L1_size;
	this->L2_size = L2_size;
	this->L1_CPU0 = new Cache(L1_size, block_size);
	this->L1_CPU1 = new Cache(L1_size, block_size);
	this->L2 = new Cache(L2_size, block_size);
}
MultilevelCache::~MultilevelCache(void){
	delete this->L1_CPU0;
	delete this->L1_CPU1; 
	delete this->L2;
}
void MultilevelCache::Processing(unsigned int addr, string oprt){
	this->address = addr;
	if(cpu_iteartor == 0){//CPU0 processing
		cout<<"CPU0 processing a ";
		actual = L1_CPU0;
		other = L1_CPU1;
		cpu_iteartor++;
	}else{////CPU1 processing
		cout<<"CPU1 processing a ";
		actual = L1_CPU1;
		other = L1_CPU0;
		cpu_iteartor = 0;
	}
	if(oprt == "L"){//Load (read) operation
		cout<<"read"<<endl;
		//If the block is in the actual L1 cache
		if(actual->dataReq(address)){
			//If the block has been invalidated by other cahce
			if(actual->blockState() == INVALID){
				actual->changeState(SHARED);
				other->changeState(SHARED);
			}
		//If the block resides at other L1 cache	
		} else {	
			// If the other L1 cache has a copy of the same block
			if(other->dataReq(address)){
				//If the copy at other cache is in EXCLUSIVE or MODIFIED state
				if(other->blockState() == EXCLUSIVE || other->blockState() == MODIFIED){
					actual->bringsBlock(address);// then bring the block from the other L1 to the actual L1 cache
					actual->changeState(SHARED);
					other->changeState(SHARED);
				}
			// Then, searchs at L2 Cache
			} else {
				// If a block resides at L2 cache
				if(L2->dataReq(address)){
					actual->bringsBlock(address);//brings it from L2 cache;
					actual->changeState(EXCLUSIVE);
					
				// If only main memory has a valid block
				}else{
					L2->bringsBlock(address);//brings the block to L2 cache from main memory
					actual->bringsBlock(address);//then, brings it to L1 cache
					actual->changeState(EXCLUSIVE);
				}
			}
		}
	}else if(oprt == "S"){//Store (write) operation
		cout<<"write"<<endl;
		//If the block is in the actual L1 cache
		if(actual->dataReq(address)) {
			//If the state of the block is EXCLUSIVE
			if(actual->blockState() == EXCLUSIVE){
				actual->changeState(MODIFIED);
			//If the state of the block is SHARED
			}else if(actual->blockState() == SHARED){
				actual->changeState(MODIFIED);
				other->changeState(INVALID);
			}
		}else{
			if(L2->dataReq(address)) {
			//this is a hit at L2 cache, then bring the block to L1 from L2 cache
				actual->bringsBlock(address);
			} else {
			//This is a miss, we need to bring the block to both L1 and L2 caches
				actual->bringsBlock(address);
				L2->bringsBlock(address);
			}	
		}
	}
}
void MultilevelCache::hits(void){
	int L1_hits = L1_CPU0->getHitCount() + L1_CPU1->getHitCount();
	int L2_hits = L2->getHitCount();
	int misses = L2->getMissCount();
	cout<<"L1 cache hits: "<<L1_hits<<" L2 cache hits: "<<L2_hits<<" Total of misses: "<<misses<<endl;
}