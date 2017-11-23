#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10
#define n 2

FILE *op;

typedef double (*sistfunc)();

double f2(double y[], double t)
{
	return y[1] + 2*y[0];
}
double f1(double y[], double t)
{
	return f2(y,t) + cos(t);
}

double grunge(sistfunc func[], double y[], double t, double h)
{

	double k1[n], k2[n], k3[n], k4[n], tn, yt[n];
	int i;
		
	for(i=0; i<n;i++)	k1[i] = func[i](y, t);
	
	for(i=0; i<n;i++)	yt[i] = y[i] + (h/2.)*k1[i];
		
	for(i=0; i<n;i++)	k2[i] = func[i](yt, t + (h/2.)) ;
	
	for(i=0; i<n;i++)	yt[i] = y[i] + (h/2.)*k2[i];
		
	for(i=0; i<n;i++)	k3[i] = func[i](yt, t + (h/2.));
	
	for(i=0; i<n;i++)	yt[i] = y[i] + h*k3[i];
		
	for(i=0; i<n;i++)	k4[i] = func[i](yt, t+h);
	

	for(i=0; i<n;i++)	y[i] = y[i] + (h/6.)*(k1[i] + (2.*k2[i]) + (2.*k3[i]) + k4[i]);
	
	return y[0];
}

main(int argc, char **argv)
{
	double t0=0., y0=0.3, y1=0,  h=((M_PI/2.) - 0.)/N, tn, yt[n], y;
	
	sistfunc equacoes[n]={f2,f1};
	op=fopen(argv[1], "w");
	
	tn=t0;
	yt[0]=y0;
	yt[1]=y1;
	
	y=y0;
	
	while(tn<(M_PI/2)){
		
		fprintf(op,"%.2lf\t%.2lf\n", tn, y);
		
		y = grunge(equacoes,yt,tn,h);
		
		tn=tn+h;	
	}
	
	fclose(op);
}
