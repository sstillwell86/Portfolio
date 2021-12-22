// Steven Stillwell
// CIS 2207 N02
// Assignment 10 

#include "DirectedGraph.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

Graph::Graph()
{
	size = 0;
	maxSize = 3;
	isDirected = false;

	graph = new int *[maxSize];

	for (int index = 0; index < maxSize; index++)
	{
		graph[index] = new int[maxSize];

		for (int jndex = 0; jndex < maxSize; jndex++)
			graph[index][jndex] = 0;
	}
}


Graph::~Graph()
{
	for (int index = 0; index < maxSize; index++)
		delete[] graph[index];

	delete[] graph;
}

void Graph::print()
{
	int width = 0;

	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			if (log10(graph[index][jndex]) > width)
				width = log10(graph[index][jndex]);

	width++;

	std::cout << "Size: " << size << std::endl;
	std::cout << "Edges: " << edges << std::endl;
	//	std::cout << "Width: " << width << std::endl;
	if (isDirected)
		std::cout << "Directed: true" << std::endl;
	else
		std::cout << "Directed: false" << std::endl;


	std::cout << std::setw(log10(size) + 1) << " " << "  ";
	for (int jndex = 0; jndex < size; jndex++)
		std::cout << std::setw(width + 1) << jndex << "  ";
	std::cout << std::endl;

	for (int index = 0; index < size; index++)
	{
		std::cout << std::setw(log10(size) + 1) << index << " | ";

		for (int jndex = 0; jndex < size; jndex++)
			std::cout << std::setw(width) << graph[index][jndex] << " | ";

		std::cout << std::endl;
	}

}

void Graph::newMaxSize(int newMaxSize)
{
	if (maxSize >= newMaxSize)
	{
		std::cerr << "Already large enough..." << std::endl;
		return;
	}

	int **newMatrix = new int *[newMaxSize];

	for (int index = 0; index < newMaxSize; index++)
	{
		newMatrix[index] = new int[newMaxSize];

		for (int jndex = 0; jndex < newMaxSize; jndex++)
			newMatrix[index][jndex] = 0;
	}

	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			newMatrix[index][jndex] = graph[index][jndex];

	for (int index = 0; index < size; index++)
		delete[] graph[index];

	delete[] graph;

	graph = newMatrix;

	maxSize = newMaxSize;
}

bool Graph::addVertex()
{
	// Is there room?
	if (size == maxSize)
	{
		newMaxSize(size * 2);
	}

	// add vertex to end of vertices
	size++;

	return true;
}

bool Graph::addEdge(int vertex1, int vertex2, int weight)
{
	if (vertex1 == vertex2)
	{
		std::cerr << "Can not have Vertex1 = Vertex2" << std::endl;
		return false;
	}

	if (vertex1 < 0 || vertex1 >= size)
	{
		std::cerr << "Vertex 1 is out of bounds" << std::endl;
		return false;
	}

	if (vertex2 < 0 || vertex2 >= size)
	{
		std::cerr << "Vertex 2 is out of bounds" << std::endl;
		return false;
	}

	if (weight <= 0)
	{
		std::cerr << "Edge Weight is out of bounds" << std::endl;
		return false;
	}

	if (isDirected)
	{
		graph[vertex1][vertex2] = weight;
	}
	else
	{
		graph[vertex1][vertex2] = weight;
		graph[vertex2][vertex1] = weight;
	}

	return true;
}


bool Graph::removeEdge(int vertex1, int vertex2)
{
	if (graph[vertex1][vertex2] == 0)
	{
		std::cerr << "Not needed, already empty" << std::endl;
		return false;
	}

	if (isDirected)
	{
		graph[vertex1][vertex2] = 0;
	}
	else
	{
		graph[vertex1][vertex2] = 0;
		graph[vertex2][vertex1] = 0;
	}

	return true;
}

// Removes the last vertex
bool Graph::removeVertex()
{
	if (size == 0)
	{
		std::cerr << "You have an empty graph alread" << std::endl;
		return false;
	}

	// find any graph edge who has a vertex >= size and remove it.
	for (int index = 0; index < size; index++)
		if (graph[size - 1][index] > 0 || graph[index][size - 1] > 0)
		{
			// We have a choice, either remove it or throw an error
			// Remove it
			removeEdge(index, size - 1);
		}

	size--;

	return true;
}

// Removes the nth vertex
bool Graph::removeVertex(int vertex)
{
	if (size == 0)
	{
		std::cerr << "You have an empty graph alread" << std::endl;
		return false;
	}
	if (vertex < 0 || vertex >= size)
	{
		std::cerr << "Vertex is out of bounds" << std::endl;
		return false;
	}

	if (vertex == size - 1)
		return removeVertex();

	for (int index = vertex; index < size - 1; index++)
		for (int jndex = 0; jndex < size; jndex++)
		{
			if (index != jndex)
			{
				//				std::cout << index << "," << jndex << " << " << index +1 << "," << jndex << std::endl;
				graph[index][jndex] = graph[index + 1][jndex];
				graph[jndex][index] = graph[jndex][index + 1];
			}
		}

	//	print();

	return removeVertex();
	//	return true;
}

void Graph::clear()
{
	for (int index = 0; index < size; index++)
		for (int jndex = 0; jndex < size; jndex++)
			graph[index][jndex] = 0;

	size = 0;
	edges = 0;
}

void Graph::printWeight(int *weight)
{
	for (int index = 0; index < size; index++)
		std::cout << weight[index] << " ";
	std::cout << std::endl;
}

void Graph::shortestPath(int vertex1, int index, bool *visited, int *weight)
{
	for (int jndex = 0; jndex < size; jndex++)
	{
		if (!visited[jndex] && graph[index][jndex] != 0)
		{
			visited[jndex] = true;
			weight[jndex] = graph[index][jndex];
		}
	}

	printWeight(weight);
}

void Graph::shortestPath(int vertex1, int vertex2)
{
	int *newWeight = new int[size];
	bool *visited = new bool[size];


	for (int index = 0; index < size; index++)
	{
		if (index == vertex1)
			newWeight[index] = 0;
		else
			newWeight[index] = 1000000;

		visited[index] = false;
	}

	for (int index = 0; index < size; index++)
	{
		if (!visited[index] && graph[vertex1][index] != 0)
			shortestPath(vertex1, index, visited, newWeight);
	}

	printWeight(newWeight);

	std::cout << "Found weight of " << newWeight[vertex1] << std::endl;

}

bool Graph::read(std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);
	if (inFile.is_open()) {
		if (!inFile.eof()) {
			std::string fileLine;
			getline(inFile, fileLine);
			if (isdigit(fileLine[0])) {							//Adds vertices
				for (int i = atoi(fileLine.c_str()); i > 0; i--) {
					addVertex();
				}
			}
			else {
				std::cout << "Error reading file." << std::endl;
				return false;
			}

			getline(inFile, fileLine);
			if (fileLine != "D" && fileLine != "U") {			//Sets directed or undirected
				std::cout << "Error reading file." << std::endl;
				return false;
			}
			else if (fileLine == "D") {
				if (!isDirected) {
					flip();
				}
			}

			for (int i = size-1; i > 0; i--) {					//Adds the edges to the graph (- '0' to convert from ASCII)
				if (!getline(inFile, fileLine)) {
					std::cout << "Error reading file." << std::endl;
					for (int i = 0; i < fileLine.length(); i++) {
						std::cout << fileLine[i];
					}
					return false;
				}
				else {
					addEdge(fileLine[0]-'0', fileLine[2]-'0', fileLine[4]-'0');
				}
			}
		}
	}
	else {
		std::cout << "Error reading file." << std::endl;
		return false;
	}

	return true;
}

bool Graph::write(std::string filename)
{
	std::ofstream outFile;
	outFile.open(filename);
	if (outFile.is_open()) {
		outFile << size << std::endl;
		if (isDirected) {
			outFile << "D" << std::endl;
		}
		else {
			outFile << "U" << std::endl;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (graph[i][j] != 0) {
					if (i <= j) {
						outFile << i << ' ' << j << ' ' << graph[i][j] << std::endl;
					}	
				}
			}
		}
	}
	else {
		return false;
	}
	return true;
}