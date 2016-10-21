/*
 * cachedmap.cpp
 *
 *  Created on: 21/10/2016
 *      Author: Miguel
 */
#include "cpualg.h"

class CacheDirectMapped : public CPUDemo {
public:
	CacheDirectMapped() : createDemo("cachedmap", "Cache - Direct Mapped") {

	}

	void run() {
		printf("Test");
	}
};

MAKE_DEMO(CacheDirectMapped);
