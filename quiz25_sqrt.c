
#include <stdio.h>

double Sqrt(double number);

int main(void)
{
	
	printf("sqrt of 2 is: %.2f \n", Sqrt(2));
	printf("sqrt of 1 is: %.2f \n", Sqrt(1));
	printf("sqrt of 0 is: %.2f \n", Sqrt(0));
	printf("sqrt of 25 is: %.2f \n", Sqrt(25));
	printf("sqrt of 3.14 is: %.2f \n", Sqrt(3.14));
	printf("sqrt of 9.8 is: %.2f \n", Sqrt(9.8));
	printf("sqrt of 420.69 is: %.2f \n", Sqrt(420.69));
	
	return 0;
}

double Sqrt(double number)
{
	double result = 0;
	double temp = 0;
	
	if (0 > number)
	{
		return -1;
	}
	
	result = number / 2;
	
	while (result != temp)
	{
		temp = result;
		
		result = (number / temp + temp) / 2; 
	}
	
	return result;
}
