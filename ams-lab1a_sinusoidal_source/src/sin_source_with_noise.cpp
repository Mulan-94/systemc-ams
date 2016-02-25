/*
 * sin_source_with_noise.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: lexy
 */

#include "sin_source_with_noise.h"

#include <cstdlib> // for std::rand
#include <cmath>   // for M_PI, std::sin, std::sqrt, and std::log

double gauss_rand(double variance)
{
  double rnd1, rnd2, Q, Q1, Q2;

  do
  {
    rnd1 = static_cast<double>(std::rand()) / RAND_MAX;
    rnd2 = static_cast<double>(std::rand()) / RAND_MAX;

    Q1 = 2.0 * rnd1 - 1.0;
    Q2 = 2.0 * rnd2 - 1.0;
    Q = Q1 * Q1 + Q2 * Q2;
  }
  while (Q > 1.0);

  return ( std::sqrt(variance) * ( std::sqrt( - 2.0 * std::log(Q) / Q) * Q1) );
}

void sin_source_with_noise::set_attributes()    // Set TDF attributes
{
  out.set_timestep(1.0, SC_US);                 // Set time step of output port
}

void sin_source_with_noise::processing()
{
  double t = out.get_time().to_seconds();       // Get current time of the sample
  double n = gauss_rand(variance);
  double x = ampl * sin(2.0 * M_PI * freq * t) + n; // Calculate sine wave
  out.write(x);                                     // Write sample to the output
}

int sc_main (int argc, char* argv[])
{
	sca_tdf::sca_signal <double> out1;

	sin_source_with_noise mySine2("sine2 with noise");

	mySine2.out(out1);

	sca_util::sca_trace_file *tf1= sca_create_vcd_trace_file("sine_wave_with_noise");
	sca_util::sca_trace(tf1,out1,"i'm_sine_with_noise");

	sc_core::sc_start(10, SC_MS);
	sca_util::sca_close_vcd_trace_file(tf1);

	return 0;

}


