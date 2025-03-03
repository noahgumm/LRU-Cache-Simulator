/*
    Noah Gumm 
    02/09/2025
    This main file runs a cache simulation that implements LRU policy
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include "../headers/Cache.h"

// Cache parameters
int main() {
    //Store the number of sets, ways, and block size for cache initilization
    //If memory accesses are of different size than those in the original trace.txt file then these values must be re-computed
    const unsigned NUM_SETS = 1024;
    const unsigned NUM_WAYS = 4;
    const unsigned BLOCK_SIZE = 64;

    //The trace file to read memory accesses from
    std::string trace_file = std::filesystem::absolute("../data/trace.txt").string();

    // Create cache object with fixed parameters
    CacheSimulator::Cache cache("Cache", NUM_SETS, NUM_WAYS, BLOCK_SIZE);

    //Open the trace file
    std::ifstream file(trace_file);

    //Read each line in the file
    //Address must be in format W:345435324533 or R:3454235324543253 in order to parse correctly
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; //Ignore possible empty lines
        
        //Check line to see if it meets criteria for a memory access
        if (line.size() < 3 || (line[0] != 'W' && line[0] != 'R') || line[1] != ':') {
            continue; // Skip invalid lines
        }    

        size_t colon_pos = line.find(':');  // Find the position of :
    
        char access_type = line[0];  // First character
        std::string address_str = line.substr(colon_pos + 1); // Extract address **after** ':'

        unsigned long address = std::stoul(address_str); // Parse as decimal
        int type = (access_type == 'W') ? 1 : 0; //Is it a read or write?
        cache.Access(address, type); //Access the cache with the address and the access type
    }

    file.close();

    // Print final cache statistics
    cache.PrintStatistics();

    return 0;
}