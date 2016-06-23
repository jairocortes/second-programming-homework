#include "cache_multilevel.hh"

MultilevelCache::MultilevelCache(int block_size, int L1_size, int L2_size){
	for(int i=0; i<20; i++){
		this->last_states.push_back(0);
	}
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
		//cout<<"CPU0 processing a ";
		actual = L1_CPU0;
		other = L1_CPU1;
		cpu_iteartor++;
	}else{////CPU1 processing
		//cout<<"CPU1 processing a ";
		actual = L1_CPU1;
		other = L1_CPU0;
		cpu_iteartor = 0;
	}
	if(oprt == "L"){//Load (read) operation
		//cout<<"read"<<endl;
		//If the block is in the actual L1 cache
		if(actual->dataReq(address)){
			//If the block has been invalidated by other cahce
			if(actual->blockState() == INVALID){
				actual->changeState(SHARED);
				other->changeState(SHARED);
				last_states.push_back(actual->blockState());
    			last_states.pop_front();
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
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				}
			// Then, searchs at L2 Cache
			} else {
				// If a block resides at L2 cache
				if(L2->dataReq(address)){
					actual->bringsBlock(address);//brings it from L2 cache;
					actual->changeState(EXCLUSIVE);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
					
				// If only main memory has a valid block
				}else{
					L2->bringsBlock(address);//brings the block to L2 cache from main memory
					actual->bringsBlock(address);//then, brings it to L1 cache
					actual->changeState(EXCLUSIVE);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				}
			}
		}
	}else if(oprt == "S"){//Store (write) operation
		//cout<<"write"<<endl;
		//If the block is in the actual L1 cache
		if(actual->dataReq(address)) {
			//If the state of the block is EXCLUSIVE
			if(actual->blockState() == EXCLUSIVE){
				actual->changeState(MODIFIED);
				last_states.push_back(actual->blockState());
    			last_states.pop_front();
			//If the state of the block is SHARED
			}else if(actual->blockState() == SHARED){
				actual->changeState(MODIFIED);
				other->changeState(INVALID);
				last_states.push_back(actual->blockState());
    			last_states.pop_front();
			}
		//If the block isn´t in the actua L1 cache
		}else{
			// If the other L1 cache has a copy of the same block
			if(other->dataReq(address)){
				//If the copy at other cache is in MODIFIED state
				if(other->blockState() == MODIFIED){
					actual->changeState(MODIFIED);
					other->changeState(INVALID);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				//If the copy at other cache is in EXCLUSIVE or SHARED state
				}else if(other->blockState() == EXCLUSIVE || other->blockState() == SHARED){
					actual->changeState(MODIFIED);
					other->changeState(INVALID);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				}
			// So, searchs at L2 Cache
			}else{
				// If a block resides at L2 cache
				if(L2->dataReq(address)){
					actual->bringsBlock(address);//brings it from L2 cache;
					actual->changeState(MODIFIED);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				// If only main memory has a valid block
				}else{
					L2->bringsBlock(address);//brings the block to L2 cache from main memory
					actual->bringsBlock(address);//then, brings it to L1 cache
					actual->changeState(MODIFIED);
					last_states.push_back(actual->blockState());
    				last_states.pop_front();
				}
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
void MultilevelCache::printStates(void){
	cout<<"The last ten states of each L1 cache (interleaved)"<<endl;
	for(int i=0; i < (int)last_states.size(); i++){
		cout << last_states[i] << "\n";
	}
}