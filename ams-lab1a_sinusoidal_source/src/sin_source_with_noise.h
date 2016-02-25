/*
 * sin_source_with_noise.h
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#ifndef SIN_SOURCE_WITH_NOISE_H_
#define SIN_SOURCE_WITH_NOISE_H_


#include <systemc-ams.h>                   // SystemC AMS header

SCA_TDF_MODULE(sin_source_with_noise)      // Declare a TDF module
{
  sca_tdf::sca_out<double> out;            // TDF output port

  //parameter
  double ampl;                             //   amplitude
  double freq;                             //   frequency
  double variance;                         //   variance for noise

  void set_attributes();                   // Set TDF attributes

  void processing();                       // Describe time-domain behaviour

  SCA_CTOR(sin_source_with_noise)          // Constructor of the TDF module
  : out("out"),                            // Name the port(s)
    ampl(1.0), freq(1e3),variance(0.1) {}  // Initial values for ampl and freq
};




#endif /* SIN_SOURCE_WITH_NOISE_H_ */
