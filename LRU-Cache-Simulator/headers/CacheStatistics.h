/*
    Noah Gumm
    2/8/2025
    Class to hold statistics computed from cache simulation
*/
#ifndef CACHE_STATISTICS_H
#define CACHE_STATISTICS_H

namespace CacheSimulator {
    class CacheStatistics {
        public:
            //Empty Constructor
            CacheStatistics();

            //Statistics to track
            unsigned total_accesses = 0;
            unsigned hit_count = 0;
            unsigned miss_count = 0;
            unsigned eviction_count = 0;
            unsigned data_movement = 0;

            //Function to update values for when cache memory is accessed
            void RecordAccess(bool hit, unsigned block_size, bool eviction);

            //Function to display results obtained
            void PrintStatistics() const;
    };
}

#endif