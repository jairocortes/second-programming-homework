#include "cache.hh"

Cache::Cache(int cache_size, int block_size){
	this->tag = this->index = 0;
	this->hit_count = this->miss_count = 0;
	this->block_size = block_size;
	this->cache_size = cache_size;
	this->offset_bits = log2 (block_size);
	//the count of "sets" will depend of the associativity and the count of "blocks"
	this->blocks_num = ((cache_size*1024)/block_size);
	//here we are calculating how many "bits" that we'll need use to select the "blocks"
	this->blocks_bits = log2 (this->blocks_num);
	//We will need to know the size of the "set" in bits
	iterator = new Block[(this->blocks_num)];//pointer to scroll through the "blocks"
	//cout<<"cache size: "<<cache_size<<" kB -- block size: "<<block_size<<" bytes"<<endl;
	//cout<<"Directed Mapped cache   --   offset bits = "<<offset_bits<<"   --  index bits = "<<blocks_bits<<endl;

	}
Cache::~Cache(void){
	delete [] iterator;
	}
bool Cache::dataReq(unsigned int addr){
     //Calculating block index
	index = (addr/block_size) % blocks_num;
	//Shift register to obtain only the "tag"
	tag = addr >> (offset_bits + blocks_bits);
	//cout<<"direct mapped cache";
	if((iterator[index].isValid()) && (iterator[index].cmpTag(tag))){
    //if valid bit is 1 and the "tag" matches, we have a hit
	hit_count++;
	return true;
	//cout<<" -- hit"<<endl;
	} else{
    //if don't, count 1 miss and brings the "block"
		miss_count++;
		return false;
		//cout<<" -- miss"<<endl;
	}
}
void Cache::bringsBlock(unsigned int addr){
	iterator[index].setAsValid();
	iterator[index].setTag(tag);
}
void Cache::writeBack(unsigned int addr){
	iterator[index].invalidate();
}
int Cache::blockState(void){
	return iterator[index].getFlag();
}
void Cache::changeState(int state){
	iterator[index].setFlag(state);
}