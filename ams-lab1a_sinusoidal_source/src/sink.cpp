/*
 * sink.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#include <systemc-ams.h>
#include "sink.h"
#include <iostream>

void sink::processing()
	{
		std::cout<<this->name()
				<<"at"<<this->get_time()
				<<"is"
				<<in.read()
				<<std::endl;
	}

/*int sc_main (int argc, char* argv[])
{
	sink myObject1;
	myObject1.processing();

	return 0;
}*/
