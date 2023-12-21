#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main()
{
	if (malloc(3741893049816238746) == NULL)
		printf("2\n");
	printf("1\n");
}