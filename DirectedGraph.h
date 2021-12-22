// Steven Stillwell
// CIS 2207 N02
// Assignment 10 

#pragma once

#include <string>

class Graph
{
private:
	int maxSize;		//Maximum Size
	int size;			// Current size
	int edges;			// number of edges
	int **graph;		// Adjacency Matrix
	bool isDirected;	// Is this a directed or undirected graph

	void printWeight(int *);

	void newMaxSize(int);
	void shortestPath(int, int, bool *, int *);

public:
	Graph();
	~Graph();

	void print();
	bool addVertex();
	bool addEdge(int, int, int);
	bool removeVertex();
	bool removeVertex(int);
	bool removeEdge(int, int);
	void flip() { isDirected = !isDirected; }

	void clear();
	void shortestPath(int vertex1, int vertex2);

	// Homework:
	bool read(std::string);
	bool write(std::string);

};

#pragma once
