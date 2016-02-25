/*
 * sin_source.h
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#ifndef SIN_SOURCE_H_
#define SIN_SOURCE_H_

#include <systemc-ams.h>

SCA_TDF_MODULE(sin_source)
{
	sca_tdf::sca_out<double> out;

	double ampl;
	double freq;

	void set_attributes()
	{
		out.set_timestep(5, SC_US);
	}

	void processing ()
	{
		double t=out.get_time().to_seconds();
		double x = ampl * std::sin(2.0 * M_PI * freq * t);
		out.write(x);
	}

	SCA_CTOR(sin_source):
		out("out"), ampl(1.0), freq(1e3){}
};



#endif /* SIN_SOURCE_H_ */
