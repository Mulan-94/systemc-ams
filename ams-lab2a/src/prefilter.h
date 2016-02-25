/*
 * prefilter.h
 *
 *  Created on: Feb 11, 2016
 *      Author: lexy
 */

#ifndef PREFILTER_H_
#define PREFILTER_H_

#include <systemc-ams.h>
#include "sin_source_with_noise.h"

SCA_TDF_MODULE(prefilter)
{
	sca_tdf::sca_in<double> in_1;
	sca_tdf::sca_out<double> out_1;

	void initialize();

	//void set_attributes();

	void processing ();

	void ac_processing();

SCA_CTOR(prefilter)
	:in_1("in_1"),out_1("out_1"), fc(1e3){}

private:
	double fc;
 sca_vector<double> num, den;
 sca_tdf::sca_ltf_nd ltf1;


};


#endif /* PREFILTER_H_ */
