/*
 * lpf.h
 *
 *  Created on: Feb 18, 2016
 *      Author: lexy
 */

#ifndef LPF_H_
#define LPF_H_

#include <systemc-ams>
SC_MODULE(rc_eln)
{
	sca_eln::sca_r* r1;
	sca_eln::sca_c* c1;

	sca_eln::sca_terminal in;
	sca_eln::sca_terminal out;

	sca_eln::sca_node_ref gnd;

	void set_attributes(){};
	void intialize(){};
	void processing(){};

	SC_CTOR(rc_eln)
	{
		r1= new sca_eln::sca_r ("r1", 1.0e+3);
		r1->p(in);
		r1->n(out);

		c1= new sca_eln::sca_c("c1", 1.0e-6);
		c1->p(out);
		c1->n(gnd);
	}

};


#endif /* LPF_H_ */
