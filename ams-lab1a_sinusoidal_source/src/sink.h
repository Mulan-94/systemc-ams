/*
 * sink.h
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#ifndef SINK_H_
#define SINK_H_

#include <systemc-ams.h>


SCA_TDF_MODULE (sink)
{
	sca_tdf::sca_in<double>in;

	SCA_CTOR(sink):
		in("in"){}

	void processing ();

};



#endif /* SINK_H_ */
