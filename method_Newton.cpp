#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
int systema ()
{
	double a = 3.37;
	double b = 10.001;
	const int N = 100;
	double E = 1e-6;
	double y,k;
	double f;
	double Vi;
	double x;y = 0;
	
	
	f = (2.0/3.0)*pow(b,3) + (1.0/2.0)*pow(b,2) + 8*b - (2.0/3.0)*pow(a,3) + (1.0/2.0)*pow(a,2) + 8*a;  
	k = 1.0/f;
	
	for (int i = 0; i < N; ++i){
		srand(i);
		Vi = rand()%99;
		Vi /= 100;
		cout<<"Random value: "<<Vi<<endl;
		
		x = (a+b)/2.0;
		bool flag = false;
		while(flag == false)
		{
			y = x - ((k*(((2.0/3.0)*pow(x,3)) + ((1.0/2.0)*pow(x,2)) + 8*x) - (k*(((2.0/3.0)*pow(a,3)) + ((1.0/2.0)*pow(a,2)) + 8*a))-Vi)/(2*pow(x,2)+x+8));
			if (fabs(k*(((2.0/3.0)*pow(x,3)) + ((1.0/2.0)*pow(x,2)) + 8*x) - (k*(((2.0/3.0)*pow(a,3)) + ((1.0/2.0)*pow(a,2)) + 8*a))-Vi) < E)
			{
				flag = true;
				cout<<"Value Y : "<<y<<endl;
			}
			else {x = y;}	
		}
	}
	
	return 0;
}

int main()
{
	systema();//method Newtowna
	return 0;
}
