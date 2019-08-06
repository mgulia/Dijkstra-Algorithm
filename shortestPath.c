#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int getDistance (int axCoord, int ayCoord, int bxCoord, int byCoord)
{
	double part1;
	double part2;
	double sum;
	int distance;

	part1 = pow((bxCoord - axCoord), 2);
	part2 = pow((byCoord - ayCoord), 2);
	sum = part1 + part2;

	distance = sqrt(sum);
	
	return distance;
}

int minDistance(int * distance, bool* set, int numNodes)
{
	int minimum = INT_MAX, minIndex;

	int i;
	for(i = 0; i<numNodes; i++)
	{
		if(set[i] == false && distance[i] <= minimum)
		{
			minimum = distance[i], minIndex = i;
		}
	}

	return minIndex;
}


void printPath(int path[], int i)
{
	if (path[i] == -1)
	{
		return;
	}

	printPath(path, path[i]);

	printf(" %d ", i);
}

int printSolution(int* distance, int numNodes, int* path, int start, int dest)
{
	int src = start;
	int i;

	if(distance[dest] != 0 && dest<numNodes && start<numNodes)
	{
		printf("%d\n", distance[dest]);
		printf("%d ", src);
		printPath(path, dest);
		printf("\n");
	}

	else
	{
		printf("INF\n");
		printf("%d %d\n", start, dest);
	}
	
}


void dijkstra(int** matrix, int source, int dest, int numNodes)
{
	int distance[numNodes];
	
	int path[numNodes];
	
	bool set[numNodes];
	int i;

	for(i = 0; i<numNodes; i++)
	{
		distance[i] = INT_MAX, set[i] = false;
		path[source] = -1;
	}
	
	
	distance[source] = 0;
	int count;
	int x;
	int y;

	for(count = 0; count<numNodes-1; count++)
	{
		x = minDistance(distance, set, numNodes);
		set[x] = true;
		
		for(y = 0; y<numNodes; y++)
		{
			if(!set[y] && matrix[x][y] && distance[x]!=INT_MAX && distance[x]+matrix[x][y] < distance[y])
			{
				distance[y] = distance[x] + matrix[x][y];
				path[y] = x;
			}
		}	
	}

	printSolution(distance, numNodes, path, source, dest);	
}

void adjacent(FILE * fp, FILE * query)
{
	
	int nodes = 0;
	int newNode = 0;
	int newEdges = 0;
	int edges = 0;
	if(fp == NULL)
	{
		return;
	}

	fscanf(fp, "%d %d\n", &nodes, &edges);

	newNode = nodes;
	newEdges = edges;


	//Dynamically creates matrix
	int **matrix = (int **)calloc(nodes, sizeof(int*));

	int x;
	for(x = 0; x < nodes; x++)
	{
		matrix[x] = calloc(nodes, sizeof(int));
	}



	int nodeA = 0;
	int nodeB = 0;
	
	int countCoords = 0;
	int placeHolder = 0;
	int xCoord = 0;
	int yCoord = 0 ;

	int xArr[nodes];
	int yArr[nodes];


	while(countCoords < nodes)
	{
		fscanf(fp, "%d %d %d\n", &placeHolder, &xCoord, &yCoord);

		xArr[countCoords] = xCoord;
		yArr[countCoords] = yCoord;

		countCoords++;
	}
	
	int var = 0;
	int axCoord = 0;
	int ayCoord = 0;
	int bxCoord = 0;
	int byCoord = 0;
	int distance = 0;

	
	while(var < newEdges)
	{
		fscanf(fp, "%d %d\n", &nodeA, &nodeB);
			
		axCoord = xArr[nodeA];
		ayCoord = yArr[nodeA];
		bxCoord = xArr[nodeB];
		byCoord = yArr[nodeB];	

		distance = getDistance(axCoord, ayCoord, bxCoord, byCoord);

		matrix[nodeA][nodeB] = distance;
		matrix[nodeB][nodeA] = distance;

		var++;
	}

	
	int i = 0;
	int j = 0;
	
	int numInputs = 0;
	int z = 0;
	int source = 0;
	int dest = 0;

	fscanf(query, "%d", &numInputs);

	for(z = 0; z<numInputs; z++)
	{
		fscanf(query, "%d %d\n", &source, &dest);
		
		dijkstra(matrix, source, dest, newNode);
	}

	int k;
	for (k = 0; k < nodes; k++)
	{
		free(matrix[k]);
	}

	free(matrix);	
}

