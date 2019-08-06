#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int getDistance(int axCoord, int ayCoord, int bxCoord, int byCoord);

void printPath(int path[], int i);

int printSolution(int* distance, int numNodes, int* path, int start, int dest);

void dijkstra(int** matrix, int source, int dest, int numNodes);

void adjacent(FILE* fp, FILE* query);

#endif
