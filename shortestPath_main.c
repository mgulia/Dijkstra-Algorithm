#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[])
{
	
	if(argc!=3)
	{
		printf("Error\n");
	}
	
	FILE *fp = fopen(argv[1], "r");
	FILE *query = fopen(argv[2], "r");

	adjacent(fp, query);

	fclose(fp);
	fclose(query);

	return 1;
}
