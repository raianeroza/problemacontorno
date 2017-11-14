//Runge-Kutta de 4ªordem

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10

FILE *op;

double f(double t, double y)
{
	return 1. + pow((t-y),2.);
}
double frunge(double ti, double yi, double h)
{
	double yn, k1=0., k2=0., k3=0., k4=0., yrk, tn, t1;
	
	yn=yi;
	tn=ti;
	
	while(tn<=3.){
		
		fprintf(op,"%.2lf\t%.2lf\n", tn, yn);
		
		k1 = f(tn,yn);
		k2 = f(tn+h/2., yn + h/2.*k1);
		k3 = f(tn+h/2., yn + h/2.*k2);
		k4 = f(tn+h, yn + h*k3);
	
		yrk = yn + (h/6.)*(k1 + (2.*k2) + (2.*k3) + k4);
		
		t1=tn+h;
		
		tn=t1;
		yn=yrk;
		
	}
}
//função z
double g(double z, double y, double t)
{
	return (3.*z) - (2.*y) + 6.*exp(-t);
}

double grunge(double ti, double yi, double h, double zi)
{

	double yn, k1=0., k2=0., k3=0., k4=0., yrk, tn, t1, l1=0., l2=0., l3=0., l4=0., zn;
	
	yn=yi;
	tn=ti;
	zn=zi;
	
	while(tn<=1.){
		
		fprintf(op,"%.2lf\t%.2lf\n", tn, yn);
		
		k1 = zn;
		l1 = g(k1,yn,tn);
		
		k2 = zn + (h/2.)*k1;
		l2 = g(k2,yn,tn);
		
		k3 = zn + (h/2)*k2;
		l3 = g(k3,yn,tn);
		
		k4 = yn + (h*k3);
		l4 = g(k4,yn,tn);
	
		yrk = yn + (h/6.)*(l1 + (2.*l2) + (2.*l3) + l4);
		
		t1=tn+h;
		
		tn=t1;
		yn=yrk;
		
	}
}

main(int argc, char **argv)
{
	double t0=0., y0=2., z0=2., h1;
	
	
	h1 =(1. - 0.)/N;
	
	op=fopen(argv[1], "w");
	
	//frunge(t0,y0,h);
	grunge(t0,y0,h1,z0);
	
	fclose(op);
}
