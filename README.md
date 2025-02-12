# LRU Cache Simulator
### By: Noah Gumm
### 02/10/2025

This cache simulator mimics the behavior of a cache utlilizing the LRU (Least Recently Used) policy. That means it replaces blocks that have least recently been used in order to make room for incoming data.

## Structure
<em><strong>Main.cpp</strong></em>: This class reads the input file and feeds the information to the Access method of the cache.

<em><strong>Cache.cpp</strong></em>: Contains the core functionality for the cache simulator. Whenever access is called with an address and access type it then decodes the memory access by finding the set id, tag, and block offset. An attempt is made to find the block. If it is not found then it's a miss and then data is theoretically loaded from main memory into the block. If there is no free block then the least recently used block is replaced.

<em><strong>CacheStatistics.cpp</strong></em>: Cache statistics has a Record Statistics method that records various stats such as hits, misses, evictions, and data movement within the cache when it is accessed.


## How it works?

This program reads the memory access trace file that is included (trace.txt). The program interprets the lines as read or write and takes the appropriate action.

<em>!!! Note: This program currently uses a cache size of 1024 sets, 4 ways, and a 64 byte block size. These constants must be changed in <strong>main.cpp</strong> to account for different cache sizes. !!!</em>

<em>!!! Note: The program only works when reading trace files of the format 'W' or 'R' followed by ':' which is then followed by the memory access in decimal. If you wish to change the trace file being read then you can change it in <strong>main.cpp</strong>. !!!</em>

## How to run

A makefile is included to make running the program simple. Follow these steps to run the program. Make can be installed with <em><strong>sudo apt install make</strong></em>.

1. Navigate to the directory containing the source code and the make file.
2. Run the <em><strong>make</strong></em> command in your terminal. This compiles the source code.
3. In the terminal run <em><strong>./cache_simulator</strong></em> to execute the program.
4. To remove the program and the compiled source files you can run <em><strong>make clean</strong></em>