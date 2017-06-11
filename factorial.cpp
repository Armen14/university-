#include <iostream>
using namespace std;
//factorial
int f = 0;

int factorial (int n)
{
	if ( n <= 1) f = 1;
	else {factorial(n-1); f *= n;}
	return 0;
}
int main()
{
	int input;
	cout<<"Input value: ";cin>>input;
	factorial(input);
	cout<<"factorial: "<<f<<endl;
	return 0;
}
