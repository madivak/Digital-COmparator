#include "systemc.h"

SC_MODULE (sc_comparatorm)
 {
  sc_in<bool> a, b;
  sc_out<bool> C_out, D_out, E_out;
 
  void do_comparator()
  {
//for the equality output pin
	bool x;
	bool y;
	bool z;
	x = !a.read() & b.read();	
	y = a.read() & !b.read();
	z = x + y;	

      D_out.write(!z);

//for the less-than output pin
      if(a < b)
	{ C_out=true; }
      else
	{ C_out=false;}
//for the greater-than output pin
      if(a > b)
	{ E_out=true; }
      else
	{ E_out=false;}
	
  }
 
  SC_CTOR (sc_comparatorm) 
  {
    SC_METHOD(do_comparator);
      sensitive << a << b;
  }
};

int sc_main(int argc, char* argv[])
{	  
  sc_set_time_resolution(1, SC_PS);
  sc_time             t1(1, SC_PS);
  sc_comparatorm sc_comparator1("comparatorm1");
 
  sc_signal<bool> a, b, C_out, D_out, E_out;
 
  sc_comparator1.a(a);
  sc_comparator1.b(b);
  sc_comparator1.C_out(C_out);
  sc_comparator1.D_out(D_out);
  sc_comparator1.E_out(E_out);
 
  sc_trace_file *wf = sc_create_vcd_trace_file("comparatorm");
  sc_trace(wf, sc_comparator1.a, "a");
  sc_trace(wf, sc_comparator1.b, "b");
  sc_trace(wf, sc_comparator1.C_out, "C_out");
  sc_trace(wf, sc_comparator1.D_out, "D_out");
  sc_trace(wf, sc_comparator1.E_out, "E_out");
 
  a.write(0);
  b.write(0);
 
  sc_start(t1);
  a.write(0);
  b.write(1);
 
  sc_start(t1);
  a.write(1);
  b.write(0);
 
  sc_start(t1);
  a.write(1);
  b.write(1);
 
  sc_start(t1);
  a.write(0);
  b.write(0);
 
  sc_start(t1);
  sc_stop();
 
  sc_close_vcd_trace_file(wf);
  return(0);
}
