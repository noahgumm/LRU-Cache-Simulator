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
    std::string trace_file = std::filesystem::absolute("data/trace.txt").string();

    // Create cache object with fixed parameters
    CacheSimulator::Cache cache("Cache", NUM_SETS, NUM_WAYS, BLOCK_SIZE);

    std::ifstream file(trace_file);
    if (!file) {
        std::cerr << "[ERROR] Failed to open trace file: " << trace_file << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.size() < 3 || (line[0] != 'W' && line[0] != 'R') || line[1] != ':') {
            std::cerr << "[WARNING] Skipping invalid line: " << line << std::endl;
            continue;
        }

        char access_type = line[0];
        std::string address_str = line.substr(2);
        
        try {
            unsigned long address = std::stoul(address_str, nullptr, 16);  // Convert from hex
            std::cout << "[DEBUG] Read address: " << std::hex << address << std::endl;
            int type = (access_type == 'W') ? 1 : 0;
            cache.Access(address, type);
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Failed to parse address: " << address_str << " (" << e.what() << ")" << std::endl;
        }
    }

    file.close();

    // Print final cache statistics
    cache.PrintStatistics();

    return 0;
}