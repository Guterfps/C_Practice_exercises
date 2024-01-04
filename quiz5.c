#include<stdio.h>

int Bursa(int prices[], int len, int *buy, int *sell);

int main()
{
	int prices[] = {4, 15, 3, 15, 1, 4, 9, 2};
	int buy_indx = 0;
	int sell_indx = 0;
	int len = sizeof(prices) / sizeof(*prices);
	
	printf("buy index = %d, sell index = %d, profit = %d \n", 
			buy_indx, sell_indx, Bursa(prices, len, &buy_indx, &sell_indx));
			
	return 0;
}


int Bursa(int prices[], int len, int *buy, int *sell)
{
	int current_min = *prices;
	int current_min_indx = 0;
	int profit = 0;
	int i = 0;
	
	for (i = 0; i < len; ++i)
	{
		if (prices[i] < current_min)
		{
			current_min = prices[i];
			current_min_indx = i;
		}
		
		if ((prices[i] - current_min) > profit)
		{
			profit = prices[i] - current_min;
			*buy = current_min_indx;
			*sell = i;
		}
	}
	
	return profit;
}
