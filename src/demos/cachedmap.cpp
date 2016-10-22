/*
 * cachedmap.cpp
 *
 *  Created on: 21/10/2016
 *      Author: Miguel
 */
#include "cpualg.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdint.h>

#define MEM_DEPTH         8192 // How many locations exist in memory
#define TAG_WIDTH         20   // Unique tag identifier
#define INDEX_WIDTH       10   // How wide do we want to index into the Cache byte offset
#define CACHE_BLOCK_COUNT 4096 // How many entries exist on the Cache
#define CACHE_BLOCK_SIZE  1    // How many blocks fit in each Cache entry

typedef struct cacheaddr {
	uint32_t index:INDEX_WIDTH;
	uint32_t tag  :TAG_WIDTH;
} cacheaddr_t;

typedef struct dmcache_ent {
	uint8_t  valid:1;
	cacheaddr_t addr;
	uint32_t data;
} dmcache_ent_t;

typedef struct dmcache {
	dmcache_ent_t * entries;
} dmcache_t;

uint8_t   * memory;
dmcache_t * cache;

class CacheDirectMapped : public CPUDemo {
public:
	uint64_t access_ctr, hit_ctr, miss_ctr;

	CacheDirectMapped() : createDemo("cachedmap", "Cache - Direct Mapped") {
		cache          = new dmcache_t;
		cache->entries = new dmcache_ent_t[CACHE_BLOCK_COUNT];
		for(unsigned int i = 0; i < CACHE_BLOCK_COUNT; i++)
			cache->entries[i].valid = 0;

		memory = new uint8_t[MEM_DEPTH];
		for(unsigned int i = 0; i < MEM_DEPTH; i++)
			memory[i] = i + 1;

		access_ctr = hit_ctr = miss_ctr = 0;
	}

	~CacheDirectMapped() {
		delete[] memory;
		delete[] cache->entries;
		delete cache;
	}

	void populate_cache(uint32_t address) {
		dmcache_ent_t * ent = &cache->entries[((cacheaddr_t*)&address)->index];
		ent->data  = memory[address];
		ent->addr = *((cacheaddr_t*)&address);
		ent->valid = 1;
	}

	uint8_t fetch(uint32_t address, uint32_t & ret_data) {
		if(address >= MEM_DEPTH) {
			ret_data = (uint32_t)-1;
			return 0;
		}

		access_ctr++;

		// Search on the cache using the received address:
		dmcache_ent_t * ent = &cache->entries[((cacheaddr_t*)&address)->index];
		if(!ent->valid) {
			// This block is invalid, fill up the cache, but don't return the value:
			miss_ctr++;
			populate_cache(address);
			ret_data = (uint32_t)-1;
			return 0;
		} else {
			// This block is valid, but is the tag the same?
			if(ent->addr.tag == ((cacheaddr_t*)&address)->tag) {
				// It's a hit!
				hit_ctr++;
				ret_data = ent->data;
				return 1;
			} else {
				// It's a miss...
				miss_ctr++;
				populate_cache(address);
				ret_data = (uint32_t)-1;
				return 0;
			}
		}

		// The returned value should be ignored if there's a miss
		ret_data = (uint32_t)-1;

		// It's a miss...
		miss_ctr++;
		return 0;
	}

	std::string itosb(uint32_t val) {
		if(!val) return "0b0";
		std::string ret = "";
		while (val) {
			ret = (val & 1 ? "1" : "0") + ret;
		    val >>= 1;
		}
		return "0b" + ret;
	}

	void run() {
		uint32_t access_repeat = CACHE_BLOCK_COUNT;
		uint32_t access_repeat_burst = 100;
		uint32_t access_spread = 2025;
		uint32_t access_offset = 1;

		srand(time(NULL));

		uint32_t ret_data;
		for(uint32_t j = 0; j < access_repeat; j++) {
			for(uint32_t i = 0; i < access_repeat_burst; i++) {
				uint32_t fetch_addr = rand() % access_spread + access_offset;
				uint8_t hit = fetch(fetch_addr, ret_data);
				printf("- Fetch @0x%x (%s): %s", fetch_addr, itosb(fetch_addr).c_str(), (hit ? "Hit!" : "Miss..."));
				if(hit) printf(" Data: %d\n", ret_data);
				else printf("\n");
			}
		}

		std::cout << "\n** Results **\n- Accesses: " << access_ctr
				  << "\n- Hit count: "  << hit_ctr
				  << "\n- Miss count: " << miss_ctr
				  << "\n- Hit ratio: "  << ((float)hit_ctr / access_ctr) * 100 << "%"
				     "\n- Miss ratio: " << ((float)miss_ctr / access_ctr) * 100 << "%";
	}
};

MAKE_DEMO(CacheDirectMapped);
