#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 10
#define n 3

FILE *op;

typedef double (*sistfunc)();

double f(double y[], double t)
{
	return y[1];
}
double f1(double y[], double t)
{
	return y[2];
}
double f2(double y[], double t)
{
	return (2.*y[2]) - y[1] - exp(t);
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
	double t0=0., y1[n]={1., 2., 0.}, h=(3. - 0.)/N, tn, yt[N], y2;
	int i;
	
	sistfunc equacoes1[n]={f,f1,f2};
	
	//op=fopen(argv[1], "w");
	
	tn=t0;
	yt[0]=y1[0];

	i=1;
	while(tn<3.){
		
		yt[i] = grunge(equacoes1,y1,tn,h);
		printf("%lf\t%lf\n", tn, yt[i]);
		
		tn+=h;	
		i++;
	}
	
	//fclose(op);
}
