/*
    Noah Gumm
    02/08/2025
    Class implementing statistics functionality for cache simulator
*/

#include <iostream>
#include "CacheStatistics.h"

namespace CacheSimulator{
    //Empty constructor
    CacheStatistics::CacheStatistics(){}

    //Update statistics when cache memory is accessed
    void CacheStatistics::RecordAccess(bool hit, unsigned block_size, bool eviction) {

        //Increase access count
        total_accesses++;

        //Increase hit count if the access is a hit
        if (hit) {
            hit_count++;
        } else {
            //Otherwise increase miss count
            miss_count++;

            //Increase total data movement based on size of the block
            data_movement += block_size;

            //If least recently used block is evicted we must track that as well
            if (eviction) {
                eviction_count++;
            }
        }
    }

    //Display statistics to the user
    void CacheStatistics::PrintStatistics() const {
        std::cout << "Cache Statistics:\n";
        std::cout << "Total Accesses: " << total_accesses << "\n";
        std::cout << "Hits: " << hit_count << "\n";
        std::cout << "Misses: " << miss_count << "\n";
        std::cout << "Evictions: " << eviction_count << "\n";
        std::cout << "Hit %: " << (total_accesses ? (double)hit_count / total_accesses * 100 : 0) << "%\n";
        std::cout << "Miss %: " << (total_accesses ? (double)miss_count / total_accesses * 100 : 0) << "%\n";
        std::cout << "Eviction %: " << (total_accesses ? (double)eviction_count / total_accesses * 100 : 0) << "%\n";
        std::cout << "Data Movement (bytes): " << data_movement << "\n";
    }
}