
#include <stdio.h>

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main(void)
{
	towerOfHanoi(3, 'A', 'C', 'B');
	
	return 0;
}

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	if (0 < n)
	{
		towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
		printf("Disk: %d moved from %c to %c \n", n, from_rod, to_rod);
		towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
	}
}
