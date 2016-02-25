/*
 * sin_source_with_noise.h
 *
 *  Created on: Feb 11, 2016
 *      Author: lexy
 */

#ifndef SIN_SOURCE_WITH_NOISE_H_
#define SIN_SOURCE_WITH_NOISE_H_

#include <systemc-ams.h>                   // SystemC AMS header

SCA_TDF_MODULE(sin_source_with_noise)      // Declare a TDF module
{
  sca_tdf::sca_out<double> out;            // TDF output port

  // Parameters
  double ampl;                             //   amplitude
  double freq;                             //   frequency
  double variance;                         //   variance for noise

  void set_attributes();                   // Set TDF attributes

  void processing();                       // Describe time-domain behaviour

  //void ac_processing();                    // Describe freq-domain behaviour

  SCA_CTOR(sin_source_with_noise)          // Constructor of the TDF module
  : out("out"),                            // Name the port(s)
   ampl(1.0), freq(1e6),variance(0.1){};  // Initial values for ampl and freq

};

#endif /* SIN_SOURCE_WITH_NOISE_H_ */
