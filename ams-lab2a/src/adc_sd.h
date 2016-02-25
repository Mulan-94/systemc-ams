/*
 * adc_sd.h
 *
 *  Created on: Feb 12, 2016
 *      Author: lexy
 */

#ifndef ADC_SD_H_
#define ADC_SD_H_

#include <systemc-ams>

SCA_TDF_MODULE (adc_sd){

	sca_tdf::sca_in<double>adc_in;
	sca_tdf::sca_out<bool> adc_out;


	void processing ();

	void ac_processing();

	SCA_CTOR(adc_sd):integ1(0.0), integ2(0.0)
	{}

private:
	double integ1,integ2;


};



#endif /* ADC_SD_H_ */
