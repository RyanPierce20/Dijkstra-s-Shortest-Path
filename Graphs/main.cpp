/*************************************************************
*
* Lab/Assignment: Lab 5 – SHortest path program
*
* Overview:
*	This program will find the shortest path for all the cities given in the graph
*
* Input:
*	The input will consist of the cities and roads to certain places
*
* Output:
*	The output of this program will display the path and distance to each vertex
*
************************************************************/

#include <iostream>
using std::endl;
using std::cout;
using std::cin;
#include "Graph.h"
#include "Dijk.h"
#include <string>
using std::string;
#define _CRTDBG_MAP_ALLOC
template <typename V>
void Visit(V data)
{
	cout << data << endl;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	string starting;
	string end;
	cout << "Welcome, Please Enter the Starting Point of where you start travelling:" << endl;
	std::getline(cin, starting);
	cout << "Now Enter the end point or Destination:" << endl;
	std::getline(cin, end);
	Dijk<string, string> b;
	b.Input();
	b.Read(starting, end);

	return 0;
}