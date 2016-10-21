//============================================================================
// Name        : CPUAlgorithms.cpp
// Author      : Miguel Santos
// Version     :
// Copyright   : Miguel
//============================================================================

#include <cpualg.h>

int main(int argc, char ** argv) {
	if(argc > 1) {
		printf(">> Executing program '%s'...\n", argv[1]);
		CPUDemo::run_demo(argv[1]);
	} else {
		printf("-- CPUAlgorithms --\n> Pick the program below:");
		for(unsigned int i = 0;i < CPUDemo::cpu_demo_list.size(); i++) {
			CPUDemo * demo = CPUDemo::cpu_demo_list[i];
			printf("\n   %d- %s: %s", i+1, demo->shortname.c_str(), demo->fullname.c_str());
		}
		printf("\n\n> Choice: ");
		fflush(stdout);
		unsigned int demo_idx;
		scanf("%d", &demo_idx);
		CPUDemo::run_demo(demo_idx);
	}
	return 0;
}
