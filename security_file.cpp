#include <iostream>
#include <string.h>
#define legal_psw "my.good.password"

int password_system()
{
	char user_psw[777];
	
	std::cout<<"print password please: ";std::cin>>user_psw;
	
	if (strcmp(legal_psw,user_psw))
	{std::cout<<"Error password:@!~`^*%$$$$$$$(;;)][||??///><<>"<<std::endl;}
	else {std::cout<<"Password legal"<<std::endl;}
	
	return 0;
}

int main()
{
	password_system();
	return 0;
}
