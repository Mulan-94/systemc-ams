/*
 * tb2.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: lexy
 */

#include "sin_source_with_noise.h"
#include "prefilter.h"
#include "adc_sd.h"

#include <cstdlib> // for std::rand
#include <cmath>   // for M_PI, std::sin, std::sqrt, and std::log

void adc_sd::processing()
{
	double feedback;
	bool output;

		if (integ2>=0.0)
			output=true;
		if (integ2<0.0)
			output=false;

	if (integ2>=0.0)
		feedback=1.0;
	if (integ2<0.0)
		feedback=-1.0;

	adc_out.write(output);

	double a=0.5;
	double b=0.5;
	double c=1.0;

	double s1 = adc_in.read() - feedback;

	double k1 = a * s1;
	  double s2 = k1 + integ1;

	  double k3 = c * feedback;
	  double s3 = integ1 - k3;

	  double k2 = b * s3;

	  double s4 = k2 + integ2;

	  integ2 = s2;
	  integ1 = s4;

}

void adc_sd::ac_processing()
{
	sca_ac(adc_out) = 0.25 / (sca_ac_z(2) - 1.5 * sca_ac_z() + 0.75) * sca_ac(adc_in);
}

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
void prefilter::initialize()
{
	num(0)=1.0;
	den(0)=1.0;
	den(1)=1.0/(2.0 * M_PI * fc);
}

void prefilter::processing()
{
	out_1=ltf1(num, den, in_1);
}

void prefilter::ac_processing()
{
	sca_ac(out_1)= sca_ac_ltf_nd(num, den, sca_ac(in_1));
}

int sc_main(int argn,char* argc[])
{
  sca_tdf::sca_signal<double> sig_1, sig_2;
  sca_tdf::sca_signal<bool> sig_3;

  sin_source_with_noise sin1("sin1");
  sin1.out(sig_1);

  prefilter prefi1("lp1");
  prefi1.in_1(sig_1);
  prefi1.out_1(sig_2);

  adc_sd adc1("adc1");
  adc1.adc_in(sig_2);
  adc1.adc_out(sig_3);

  sca_trace_file* tfp =
    sca_create_tabular_trace_file("tb_lab2c.dat");

  sca_trace(tfp, sig_1, "sig_1");
  sca_trace(tfp, sig_2, "sig_2");
  sca_trace(tfp, sig_3, "sig_3");

  sc_start(5.0, SC_MS);

  tfp->reopen("tb_ac_lab2c.dat");
  tfp->set_mode(sca_ac_format(sca_util::SCA_AC_DB_DEG));

  sca_ac_start(1.0, 1e6, 1000, SCA_LOG);

  return 0;
}


