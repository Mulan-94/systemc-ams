/*
 * sin_source.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#include "sin_source.h"
#include <systemc-ams.h>
#include <cmath>

int sc_main (int argc, char* argv[])
{
	sca_tdf::sca_signal <double> out1;

	sin_source mySine("sine1");

	mySine.out(out1);

	sca_util::sca_trace_file *tf1= sca_create_vcd_trace_file("sine_wave");
	sca_util::sca_trace(tf1,out1,"i'm_sine_1");

	sc_core::sc_start(10, SC_MS);
	sca_util::sca_close_vcd_trace_file(tf1);

	return 0;

}

