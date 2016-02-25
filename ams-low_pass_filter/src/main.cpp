/*
 * main.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: lexy
 */
#include<systemc.h>
#include <systemc-ams>
#include"lpf.h"

int sc_main(int argc, char* argv[])
{
	sca_eln::sca_node node_in;
	sca_eln::sca_node node_out;
	sca_eln::sca_node_ref gnd;

	sc_signal<double> sig;

	sca_eln::sca_de_vsource src("src", 1.0); //discrete event voltage source with an initial value of 1
	src.set_timestep(0.5, sc_core::SC_US);  //time-step for voltage source

	src.inp(sig);
	src.p(node_in);
	src.n(gnd);

	rc_eln dut("dut");  //rc object
	dut.in(node_in);
	dut.out(node_out);

	sca_util::sca_trace_file *tfp = sca_util::sca_create_vcd_trace_file("rc_filter.vcd");
	sca_trace(tfp,node_in,"node_in");
	sca_trace(tfp, node_out,"node_out");
	sca_trace(tfp, sig,"sig");

	sig.write(0.0);

	sc_core::sc_start(10, sc_core::SC_MS);

	sig.write(1.0);

	sc_core::sc_start(10, SC_MS);

	sig.write(0.0);

	sc_core::sc_start(10, sc_core::SC_MS);

	sig.write(1.0);

	sc_core::sc_start(10, SC_MS);

	sca_util::sca_close_vcd_trace_file(tfp);


	return 0;

}


