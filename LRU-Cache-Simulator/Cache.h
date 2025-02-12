/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MEMORY_CACHE_H
#define MEMORY_CACHE_H

#include <memory>
#include <list>
#include <string> // Include for std::string
#include "CacheStatistics.h"

namespace CacheSimulator {
	class Cache
	{
		public:
			/// Possible values for a cache block state
			enum BlockState
			{
				BlockInvalid,
				BlockModified
			};

			/// Cache block class
			class Block
			{
				// Only Cache needs to initialize fields
				friend class Cache;

				// Block tag
				unsigned tag = 0;

				// Way identifier
				unsigned way_id = 0;

				// Block state
				BlockState state = BlockInvalid;

				public:
					/// Constructor
					Block() {}

					/// Get the block tag
					unsigned getTag() const { return tag; }

					/// Get the way index of this block
					unsigned getWayId() const { return way_id; }

					/// Get the block state
					BlockState getState() const { return state; }

					/// Set new state and tag
					void setStateTag(BlockState state, unsigned tag)
					{
						this->state = state;
						this->tag = tag;
					}
			};

		private:
			// Name of the cache, used for debugging purposes
			std::string name;
			CacheStatistics cache_stats;

			// Cache geometry
			unsigned num_sets;
			unsigned num_ways;
			unsigned num_blocks;
			unsigned block_size;
			
			// Mask used to get the block address
			unsigned block_mask;

			// Log base 2 of the block size
			int log_block_size;

			// Cache set
			class Set
			{
				// Only Cache needs to initialize fields
				friend class Cache;

				// List of blocks in LRU order
				// Replace 'List<Block>' with 'std::list<Block>' if appropriate
				std::list<Block> lru_list;
			};

			// Array of sets
			std::unique_ptr<Set[]> sets;

		public:
			/// Constructor
			Cache(const std::string& name,
				unsigned num_sets,
				unsigned num_ways,
				unsigned block_size);

			/// Decode a physical address
			void DecodeAddress(unsigned long address, unsigned &set_id, unsigned &tag, unsigned &block_offset) const;

			/// Check whether an address is present in the cache
			/// Mark a block as last accessed as per the LRU policy if it is presented in the cache
			bool FindBlock(unsigned& set_id, unsigned& tag, unsigned& way_id) const;

			/// Set a new tag and state for a cache block
			void setBlock(unsigned set_id, unsigned way_id, unsigned tag, BlockState state);

			/// access to the cache memory
			void Access(unsigned address, int access_type);

			/// Return the way index of the block to be replaced
			unsigned ReplaceBlock(unsigned set_id);
			
			void PrintStatistics();

			template<typename T> 
			std::unique_ptr<T[]>new_unique_array(int size)
			{
				return std::unique_ptr<T[]>(new T[size]());
			}
	};
}
#endif // MEMORY_CACHE_H
