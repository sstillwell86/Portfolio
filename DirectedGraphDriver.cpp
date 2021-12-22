// Steven Stillwell
// CIS 2207 N02
// Assignment 10 


#include "DirectedGraph.h"

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>


// prototyes
void menu();

// main()
int main()
{
	menu();

	return 0;
}


char getChoice()
{

	std::cout << "Choice: " << std::endl;
	std::cout << "\tQ -- Quit" << std::endl;
	std::cout << "\tP -- Print" << std::endl;
	std::cout << "\tN -- New Vertex" << std::endl;
	std::cout << "\tA -- New Edge" << std::endl;
	std::cout << "\tR -- Remove Edge" << std::endl;
	std::cout << "\tD -- Remove Vertex" << std::endl;
	std::cout << "\tL -- Load (Read) Graph" << std::endl;
	std::cout << "\tW -- Write Graph" << std::endl;
	std::cout << "\tS -- ShortestPath Test" << std::endl;
	std::cout << "\tF -- Flip Undirecte / Directed Graph" << std::endl;

	std::cout << std::endl;
	std::cout << "Enter Choice: ";

	char c = _getch();

	while (!(
		c == 'P' || c == 'p' ||
		c == 'N' || c == 'n' ||
		c == 'A' || c == 'a' ||
		c == 'R' || c == 'r' ||
		c == 'D' || c == 'd' ||
		c == 'L' || c == 'l' ||
		c == 'W' || c == 'w' ||
		c == 'S' || c == 's' ||
		c == 'F' || c == 'f' ||
		c == 'Q' || c == 'q'
		))
	{
		std::cout << "Error, you entered a '" << c << "'" << std::endl;
		std::cout << "Enter Choice: ";
		c = _getch();
	}

	c = _toupper(c);

	std::cin.clear();
	return c;
}

void menu()
{
	Graph graph;
	char choice = getChoice();


	while (choice != 'Q')
	{
		int newValue;
		std::string newString;
		std::string filename;
		bool returnCode;
		int vertex1, vertex2, weight;

		std::cout << std::endl;

		switch (choice)
		{
		case 'P':
			graph.print();
			break;
		case 'N':
			returnCode = graph.addVertex();

			if (returnCode == true)
				std::cout << "Vertex Added" << std::endl;
			else
				std::cout << "Vertex Not Added" << std::endl;

			break;
		case 'A':
			std::cout << "Enter Vertex 1: ";
			std::cin >> vertex1;

			std::cout << "Enter Vertex 2: ";
			std::cin >> vertex2;

			std::cout << "Enter Weight: ";
			std::cin >> weight;

			returnCode = graph.addEdge(vertex1, vertex2, weight);

			if (returnCode)
				std::cout << "Edge Added" << std::endl;
			else
				std::cout << "Edge NOT Added" << std::endl;
			break;
		case 'R':
			std::cout << "Enter Vertex 1: ";
			std::cin >> vertex1;
			std::cout << "Enter Vertex 2: ";
			std::cin >> vertex2;

			returnCode = graph.removeEdge(vertex1, vertex2);

			if (returnCode)
				std::cout << "Edge Removed" << std::endl;
			else
				std::cout << "Edge NOT Removed" << std::endl;

			break;
		case 'D':
			std::cout << "Enter a Vertex to remove: ";
			std::cin >> vertex1;

			returnCode = graph.removeVertex(vertex1);

			if (returnCode)
				std::cout << "Vertex Removed" << std::endl;
			else
				std::cout << "Vertex NOT Removed" << std::endl;

			break;
		case 'L':
			std::cout << "Enter a filename to load from: ";
			std::cin >> filename;
			graph.read(filename);
			break;
		case 'W':
			std::cout << "Enter a filename to save to: ";
			std::cin >> filename;

			graph.write(filename);
			break;
		case 'S':
			std::cout << "Enter a start vertex: ";
			std::cin >> vertex1;
			std::cout << "enter an end vertex: ";
			std::cin >> vertex2;

			graph.shortestPath(vertex1, vertex2);
			break;
		case 'F':
			graph.flip();
			break;
		}


		choice = getChoice();
	}
}


