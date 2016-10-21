/*
 * cpualg.h
 *
 *  Created on: 21/10/2016
 *      Author: Miguel
 */

#include <vector>
#include <string>
#include <cstdio>

#ifndef CPUALG_H_
#define CPUALG_H_

#define createDemo(shortname, fullname) CPUDemo(shortname, fullname)
#define MAKE_DEMO(Classname) static Classname Classname ## _obj

class CPUDemo {
public:
	static std::vector<CPUDemo*> cpu_demo_list;
	static void run_demo(std::string demo_shortname);
	static void run_demo(unsigned int demo_idx);
	std::string shortname;
	std::string fullname;

	CPUDemo(std::string shortname, std::string fullname);
	virtual ~CPUDemo() = 0;
	virtual void run() = 0;
};

#endif /* CPUALG_H_ */
