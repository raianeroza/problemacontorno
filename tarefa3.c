#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10
#define n 2

FILE *op;

typedef double (*sistfunc)();

double f(double y[], double t)
{
	return y[1];
}
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
	double t0=0., y1[n]={-0.3,0.}, y2[n]={0.,1.},  h=((M_PI/2.) - 0.)/N, tn, yt1[N+1], yt2[N+1], yn[N+1];
	int i=0;
	
	sistfunc equacoes[n]={f,f1}, equacoes2[n]={f,f2};
	
	
	op=fopen(argv[1], "w");
	
	tn=t0;
	yt1[0]=y1[0];
	yt2[0]=y2[0];
	
	i=1;
	while(tn<(M_PI/2)){
		
		yt1[i] = grunge(equacoes,y1,tn,h);
		yt2[i] = grunge(equacoes2,y2,tn,h);
		//printf("%lf\t%lf\t%lf\n", tn, yt1[i], yt2[i]);
		
		tn+=h;	
		i++;

	}
	
	tn=t0;
	
	for(i=0; i<N; i++)
	{
		yn[i] = yt1[i] + ( (-0.1-yt1[N]) / yt2[N] )*yt2[i];
		fprintf(op,"%lf\t%lf\t%lf\t%lf\n", tn, yt1[i], yt2[i], yn[i]);
		
		tn+=h;
		
	}
	fclose(op);
}
