#include<stdio.h>
#include<string.h>

int main()
{
	char k1,k2,k3,k4,k5;
	for(k1='a';k1<='z';k1++)
	{
		k2=(k1+15);
		k3=(k1+22);
		k4=(k1+13);
		k5=(k1+17);
		printf("%c%c%c%c%c\n",k1,k2,k3,k4,k5); 
	} 
	
 } 
