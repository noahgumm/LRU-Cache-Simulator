/*
    Noah Gumm
    02/07/2025
    This class simulates a cache that utilizes the LRU policy
*/

#include "Cache.h"
#include "CacheStatistics.h"
#include "math.h"
#include "iostream"

namespace CacheSimulator {
    //Constructor that takes values to initilize the cache
    Cache::Cache(
        const std::string& name,
		unsigned num_sets,
		unsigned num_ways,
		unsigned block_size
    ) :
        name(name),
        num_sets(num_sets),
        num_ways(num_ways),
        block_size(block_size)
    {
        //Find the total number of blocks
        num_blocks = num_sets * num_ways;

        log_block_size = log2(block_size);
        block_mask = block_size - 1;

        sets = std::make_unique<Set[]>(num_sets);  // Allocate array

        for (unsigned set_id = 0; set_id < num_sets; set_id++) {
            sets[set_id].lru_list.clear(); // ✅ Ensure empty before adding
        
            for (unsigned way_id = 0; way_id < num_ways; way_id++) {
                sets[set_id].lru_list.emplace_back();  // ✅ Create default Block
                sets[set_id].lru_list.back().way_id = way_id;
                sets[set_id].lru_list.back().state = BlockInvalid;
            }
        }
    }

    //Decode an address into its set_id, tag, and address
    void Cache::DecodeAddress(unsigned long address, unsigned &set_id, unsigned &tag, unsigned &block_offset) const {   
        // Get block offset by getting remainder of address % block_size
        block_offset = address % block_size;  
        address /= block_size;                // Remove block offset bits

        set_id = address % num_sets;          // Set_id is the remainder when dividing by num_sets
        tag = address / num_sets;  
    }

    //Find a cache block, return true fi found and false otherwise
    bool Cache::FindBlock(unsigned& set_id, unsigned& tag, unsigned& way_id) const {
        //Store the block_list for the set being searched
        auto& block_list = sets[set_id].lru_list;

        // For every block check to see if the tag matches
        for (auto i = block_list.begin(); i != block_list.end(); ++i) {
            if (i->getTag() == tag) {
                way_id = i->getWayId();
                
                // Move block to front if matchinig tag is found
                block_list.splice(block_list.begin(), block_list, i);
                return true;
            }
        }
        return false;
    }

    //Set the tag and state of the block
    void Cache::setBlock(unsigned set_id, unsigned way_id, unsigned tag, BlockState state){

        //Get the block list for the referenced set
        auto &block_list = sets[set_id].lru_list;

        //Create a new block, move it to the front of the block_list, and give it the appropriate state and tag
        Block &new_block = block_list.front();
        new_block.setStateTag(state, tag);
        new_block.way_id = way_id;

        // Move to MRU position only if list has elements
        if (block_list.size() > 1) {
            block_list.splice(block_list.begin(), block_list, std::prev(block_list.end()));
        }
    }


    //Handles any access to cache when given an address and access type
    void Cache::Access(unsigned address, int access_type){

        //Decode the address and store the set_id, tag, and block_offset
        unsigned set_id, tag, block_offset;
        DecodeAddress(address, set_id, tag, block_offset);
    
        //Attempt to find the block in the cache
        unsigned way_id;
        bool hit = FindBlock(set_id, tag, way_id);
    
        //Boolean for tracking statistics on evictions
        bool eviction = false;

        //If there is no hit
        if (!hit) {
            //Get the way_id of the block the replace
            unsigned replace_way = ReplaceBlock(set_id);
        
            //If the list is full then we need to record an eviction in our statistics
            if (sets[set_id].lru_list.size() == num_ways) {
                eviction = true;
            }
            setBlock(set_id, replace_way, tag, (access_type == 1) ? BlockModified : BlockInvalid);
        }
        
        //Update stats after every access
        cache_stats.RecordAccess(hit, block_size, eviction);
    }


    //Replace a block and return the way_id of the LRU block
    unsigned Cache::ReplaceBlock(unsigned set_id){

        //Get blocks for referenced set
        auto& blocks = sets[set_id].lru_list;

        //If there blocks aren't empty
        if (!blocks.empty()) {
            //Get the block at the back of the list and remove it
            unsigned lru_way_id = blocks.back().getWayId();
            blocks.pop_back();

            // Create an empty block in place of the LRU block removed
            //The block is populated with data within the Access function
            //This is merely a form of error control 
            Block block;
            blocks.emplace_back(block);
            blocks.back().setStateTag(BlockInvalid, lru_way_id);
            return lru_way_id;
        }

        //Return a failure
        return static_cast<unsigned>(-1);
    }

    //Wrapper function for printing statistics
    void Cache::PrintStatistics() {
        cache_stats.PrintStatistics();
    }
}