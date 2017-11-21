//Runge-Kutta de 4ªordem

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10
#define L 2
#define M 2
#define n 4

FILE *op;

typedef double (*sistfunc)();

double f(double y[M])
{
	return y[1];
}
double g(double y[0], double y[m], double t)
{
	return (3.*y[1]) - (2.*y[0]) + 6.*exp(-t);
}

double grunge(sistfunc func[], double y[M], double t,double h)
{

	double k1[n], k2[n], k3[n], k4[n], yrk[n], tn, t1, l1[n], l2[n], l3[n], l4[n], zn;
	int i;
		
	for(i=0; i<n;i++)	k1[i] = f(y[1]);
	for(i=0; i<n;i++)	l1[i] = g(k1[i],y[i],tn);
		
	for(i=0; i<n;i++)	k2[i] = y[1] + y[i] + (h/2.)*k1[i];
	for(i=0; i<n;i++)	l2[i] = g(k2[i],y[i],tn);
		
	for(i=0; i<n;i++)	k3[i] = y[1] + y[i] + (h/2)*k2[i];
	for(i=0; i<n;i++)	l3[i] = g(k3[i],y[i],tn);
		
	for(i=0; i<n;i++)	k4[i] = y[0] + y[i] + (h*k3[i]);
	for(i=0; i<n;i++)	l4[i] = g(k4[i],y[i],tn);

	for(i=0; i<n;i++)	yrk[i] = y[i] + (h/6.)*(l1[i] + (2.*l2[i]) + (2.*l3[i]) + l4[i]);

}

main(int argc, char **argv)
{
	double t0=0., y0=2., z0=2., h1=(1. - 0.)/N;
	
	op=fopen(argv[1], "w");
	
	while(tn<=1.){
	
		sistfunc equacoes[n]={f,g};
		grunge(sistfunc func[],y[M],t0,h1);
	}
	
	fclose(op);
}
