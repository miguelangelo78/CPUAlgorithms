/*
 * cpualg.cpp
 *
 *  Created on: 21/10/2016
 *      Author: Miguel
 */

#include "cpualg.h"

std::vector<CPUDemo*> CPUDemo::cpu_demo_list;

CPUDemo::CPUDemo(std::string shortname, std::string fullname) {
	this->shortname = shortname;
	this->fullname  = fullname;
	CPUDemo::cpu_demo_list.push_back(this);
}

void CPUDemo::run_demo(std::string demo_shortname) {
	for(unsigned int i = 0; i < CPUDemo::cpu_demo_list.size(); i++) {
		CPUDemo * demo = CPUDemo::cpu_demo_list[i];
		if(demo_shortname == demo->shortname) {
			demo->run();
			printf("\n\n>> Demo '%s' has finished <<", demo->shortname.c_str());
			return;
		}
	}
	printf("\n>> ERROR: The demo '%s' does not exist <<", demo_shortname.c_str());
}

void CPUDemo::run_demo(unsigned int demo_idx) {
	if(demo_idx > CPUDemo::cpu_demo_list.size() || demo_idx == 0) {
		printf("\n>> ERROR: The demo no. %d does not exist <<", demo_idx);
		return;
	}
	CPUDemo * demo = CPUDemo::cpu_demo_list[demo_idx - 1];
	demo->run();
	printf("\n\n>> Demo '%s' has finished <<", demo->shortname.c_str());
}

CPUDemo::~CPUDemo() { }
