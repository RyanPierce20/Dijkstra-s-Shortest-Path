/*************************************************************
* Author:		Ryan Pierce
* Filename:		Lab5.cpp
* Date Created:	3/1/15
* Modifications:	3/3/15
**************************************************************/
/************************************************************************
* Class: Dijk
*
* Purpose: This class inputs all the data into the list and does all the calculations for the paths and arrays
*
* Manager functions:
* 		void Input();
void Read(V s, V end);
int Smallest();
void Linked(int tiniest);
void ShortestPath(V num);

*
* Methods:
*	Graph<string, string> a;
vector<double> Distance;
vector<int> Predeccesor;
vector<bool> Processed;
vector<Vertex<V, E>> l;
bool finished;
*		...
*************************************************************************/

#ifndef Dijk_H
#define Dijk_H

#include <string>
using std::string;
#include <iostream>
#include "Graph.h"
using std::cin;
template <typename V, typename E>
class Dijk
{
public:
	void Input();
	void Read(V s, V end);
	int Smallest();
	void Linked(int tiniest);
	void ShortestPath(V num);
private:
	Graph<string, string> a;
	vector<double> Distance;
	vector<int> Predeccesor;
	vector<bool> Processed;
	vector<Vertex<V, E>> l;
	bool finished;
	int pos;
	int start;
};
/**********************************************************************
* Purpose: This function will ask the user for the source and destination
*
* Precondition:
*     the strings are passed in
*
* Postcondition:
*      determines the shortest path and everything else
*
************************************************************************/
template <typename V, typename E>
void Dijk<V, E>::Read(V starting, V end)
{
	bool first = false;
	finished = false;
	start = 0;
	int position = 0;
	for (Vertex<V, E> vertex : a.GetList())
	{
		l.push_back(vertex);
		Distance.assign(l.size(), -1);
		Predeccesor.assign(l.size(), -1);
		Processed.assign(l.size(), false);
	}
	for (start = 0; start < l.size(); start++)
	{
		if (l[start].GetData() == starting)
		{
			first = true;
			position = start;
		}
	}
	if (first == false)
	{
		cout << "Not A Starting Point" << endl;
		return;
	}
	Distance[position] = 0;
	Processed[position] = true;
	pos = position;
	double miles = 0;
	int current = 0;
	for (Arc<V, E> edge : l[position].GetEdges())
	{
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].GetData() == edge.GetDestination().GetData())
			{
				current = i;
			}
		}
		if (Processed[current] == false)
		{
			int n = 0;
			for (int j = 0; j < l.size(); j++)
			{
				if (l[j].GetData() == edge.GetDestination().GetData())
				{
					n = j;
				}
			}
			int length = edge.GetWeight();
			if (Distance[position] > 0)
			{
				length += Distance[position];
			}
			if (length < Distance[n] || Distance[n] < 0)
			{
				Distance[n] = length;
				Predeccesor[n] = position;
			}
		}
	}
	Processed[position] = true;
	int count = 0;
	while (count != 35)
	{
		count = 0;
		int num = 0;
		for (int m = 0; m < l.size(); m++)
		{
			if (Processed[m] != false)
				count++;
		}
		int tiniest = Smallest();
		Linked(tiniest);
	}
	ShortestPath(end);



	cout << endl;

}
/**********************************************************************
* Purpose: This function will get the edges of the smallest edges and set the values
*
* Precondition:
*     smallest edge is passed in
*
* Postcondition:
*      sets the data in the arrays
*
************************************************************************/
template <typename V, typename E>
void Dijk<V, E>::Linked(int tiniest)
{
	int current = 0;

	for (Arc<V, E> edge : l[tiniest].GetEdges())
	{
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].GetData() == edge.GetDestination().GetData())
			{
				current = i;
			}
		}
		if (Processed[current] == false)
		{
			int n = 0;
			for (int j = 0; j < l.size(); j++)
			{
				if (l[j].GetData() == edge.GetDestination().GetData())
				{
					n = j;
				}
			}
			int length = edge.GetWeight();
			if (Distance[tiniest] > 0)
			{
				length += Distance[tiniest];
			}
			if (length < Distance[n] || Distance[n] < 0)
			{
				Distance[n] = length;
				Predeccesor[n] = tiniest;
			}
		}
	}
	Processed[tiniest] = true;
}
/**********************************************************************
* Purpose: This function finds the smallest edge value
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the smallest vertex
*
************************************************************************/
template <typename V, typename E>
int Dijk<V, E>::Smallest()
{
	unsigned int smallest = -1;
	int index = 0;
	for (int i = 0; i < Distance.size(); i++)
	{
		if (Distance[i] > 0 && Processed[i] != true && Distance[i] < smallest)
		{
			index = i;
			smallest = Distance[i];
		}
	}
	return index;
}
/**********************************************************************
* Purpose: This function calculates the shortest distance between the two vertex's
*	and will display all the paths it took to get to each city
* Precondition:
*     the string passed in its looking for
*
* Postcondition:
*     displays the paths
*
************************************************************************/
template <typename V, typename E>
void Dijk<V, E>::ShortestPath(V num)
{
	int index = -1;
	for (int i = 0; i < l.size(); i++)
	{
		if (l[i].GetData() == num)
		{
			index = i;
		}
	}
	if (index >= 0)
	{
		bool end = false;
		list<Vertex<V, E>> stack;
		stack.push_back(l[index]);
		while (index != start && end != true)
		{
			index = Predeccesor[index];
			if (index != -1)
				stack.push_back(l[index]);
			else
				end = true;
		}
		while (stack.back().GetData() != num)
		{
			Vertex<V, E> current = stack.back();
			list<Arc<V, E>>::iterator stack2;
			stack.pop_back();

			int distance = 0;
			for (int p = 0; p < l.size(); p++)
			{
				if (l[p].GetData() == stack.back().GetData())
				{
					distance = p;
				}
			}
			distance = Distance[distance];
			double time = distance / 55.00;
			stack2 = current.GetEdges().begin();
			while (stack2->GetDestination().GetData() != stack.back().GetData())
			{
				stack2++;
			}
			if (stack2->GetData() == "I - 5")
				time = distance / 65.00;
			time = time * 60;

			cout << "From " << current.GetData() << " to " << stack.back().GetData() << " will take: " << distance << " miles" << " with a time of " << time << " minutes" << endl;

		}
	}
	else
		cout << "Not an End Point." << endl;
}
/**********************************************************************
* Purpose: This function reads in all of the vertex's and edges
*
* Precondition:
*     nothing
*
* Postcondition:
*      reads all of the new data
*
************************************************************************/
template <typename V, typename E>
void Dijk<V, E>::Input()
{
	a.InsertVertex("Klamath Falls");
	a.InsertVertex("Keno");
	a.InsertVertex("Hwy 140 and Dead Indian Memorial Road Junction");
	a.InsertVertex("Clover Creek and Dead Indian Memorial Road Junction");
	a.InsertVertex("Ashland");
	a.InsertVertex("Hwy 97 and Hwy 62 Junction");
	a.InsertVertex("Hwy 62 and Hwy 230 Junction");
	a.InsertVertex("Hwy 97 and Hwy 138 Junction");
	a.InsertVertex("Chemult");
	a.InsertVertex("Hwy 97 and Hwy 58 Junction");
	a.InsertVertex("Bend");
	a.InsertVertex("Sisters");
	a.InsertVertex("Hwy 242 and Hwy 126 Junction");
	a.InsertVertex("Oakridge");
	a.InsertVertex("Hwy 138 and Hwy 230 Junction");
	a.InsertVertex("Glide");
	a.InsertVertex("Medford");
	a.InsertVertex("Grants Pass");
	a.InsertVertex("Crescent City");
	a.InsertVertex("Winston");
	a.InsertVertex("Coquille");
	a.InsertVertex("Brookings");
	a.InsertVertex("Gold Beach");
	a.InsertVertex("Port Orford");
	a.InsertVertex("Bandon");
	a.InsertVertex("Hwy 101 and Hwy 42 Junction");
	a.InsertVertex("Coos Bay");
	a.InsertVertex("Lakeside");
	a.InsertVertex("Roseburg");
	a.InsertVertex("Sutherlin");
	a.InsertVertex("Drain");
	a.InsertVertex("Elkton");
	a.InsertVertex("Hwy 58 and I - 5 Junction");
	a.InsertVertex("Reedsport");
	a.InsertVertex("Eugene");

	a.InsertArc("Klamath Falls", "Hwy 140 and Dead Indian Memorial Road Junction", "Hwy 140", 31);
	a.InsertArc("Klamath Falls", "Keno", "Hwy 66", 9);
	a.InsertArc("Klamath Falls", "Hwy 97 and Hwy 62 Junction", "Hwy 97", 23);
	a.InsertArc("Keno", "Clover Creek and Dead Indian Memorial Road Junction", "Clover Creek", 20);
	a.InsertArc("Keno", "Ashland", "Hwy 66", 48);
	a.InsertArc("Hwy 140 and Dead Indian Memorial Road Junction", "Clover Creek and Dead Indian Memorial Road Junction", "Dead Indian Memorial Road", 7);
	a.InsertArc("Clover Creek and Dead Indian Memorial Road Junction", "Ashland", "Dead Indian Memorial Road", 43);
	a.InsertArc("Ashland", "Medford", "I - 5", 12);
	a.InsertArc("Hwy 140 and Dead Indian Memorial Road Junction", "Medford", "Hwy 140", 36);
	a.InsertArc("Hwy 97 and Hwy 62 Junction", "Hwy 62 and Hwy 230 Junction", "Hwy 62", 49);
	a.InsertArc("Hwy 62 and Hwy 230 Junction", "Medford", "Hwy 62", 56);
	a.InsertArc("Hwy 97 and Hwy 62 Junction", "Hwy 97 and Hwy 138 Junction", "Hwy 97", 40);
	a.InsertArc("Hwy 97 and Hwy 138 Junction", "Chemult", "Hwy 97", 9);
	a.InsertArc("Chemult", "Hwy 97 and Hwy 58 Junction", "Hwy 97", 8);
	a.InsertArc("Hwy 97 and Hwy 58 Junction", "Bend", "Hwy 97", 57);
	a.InsertArc("Bend", "Sisters", "Hwy 20", 21);
	a.InsertArc("Sisters", "Hwy 242 and Hwy 126 Junction", "Hwy 242", 39);
	a.InsertArc("Hwy 242 and Hwy 126 Junction", "Eugene", "Hwy 126", 53);
	a.InsertArc("Hwy 97 and Hwy 58 Junction", "Oakridge", "Hwy 58", 51);
	a.InsertArc("Oakridge", "Hwy 58 and I - 5 Junction", "Hwy 58", 36);
	a.InsertArc("Hwy 97 and Hwy 138 Junction", "Hwy 138 and Hwy 230 Junction", "Hwy 138", 19);
	a.InsertArc("Hwy 138 and Hwy 230 Junction", "Hwy 62 and Hwy 230 Junction", "Hwy 230", 24);
	a.InsertArc("Hwy 138 and Hwy 230 Junction", "Glide", "Hwy 138", 61);
	a.InsertArc("Glide", "Roseburg", "Hwy 138", 18);
	a.InsertArc("Medford", "Grants Pass", "I - 5", 29);
	a.InsertArc("Grants Pass", "Crescent City", "Hwy 199", 82);
	a.InsertArc("Crescent City", "Brookings", "Hwy 101", 19);
	a.InsertArc("Grants Pass", "Winston", "I - 5", 58);
	a.InsertArc("Winston", "Roseburg", "I - 5", 10);
	a.InsertArc("Winston", "Coquille", "Hwy 42", 64);
	a.InsertArc("Coquille", "Hwy 101 and Hwy 42 Junction", "Hwy 42", 11);
	a.InsertArc("Brookings", "Gold Beach", "Hwy 101", 31);
	a.InsertArc("Gold Beach", "Port Orford", "Hwy 101", 28);
	a.InsertArc("Port Orford", "Bandon", "Hwy 101", 30);
	a.InsertArc("Bandon", "Hwy 101 and Hwy 42 Junction", "Hwy 101", 18);
	a.InsertArc("Hwy 101 and Hwy 42 Junction", "Coos Bay", "Hwy 101", 6);
	a.InsertArc("Coos Bay", "Lakeside", "Hwy 101", 16);
	a.InsertArc("Lakeside", "Reedsport", "Hwy 101", 11);
	a.InsertArc("Roseburg", "Sutherlin", "I - 5", 11);
	a.InsertArc("Sutherlin", "Elkton", "Hwy 138", 27);
	a.InsertArc("Sutherlin", "Drain", "I - 5", 27);
	a.InsertArc("Drain", "Elkton", "Hwy 38", 20);
	a.InsertArc("Elkton", "Reedsport", "Hwy 38", 37);
	a.InsertArc("Drain", "Hwy 58 and I - 5 Junction", "I - 5", 27);
	a.InsertArc("Hwy 58 and I - 5 Junction", "Eugene", "I - 5", 3);
	a.InsertArc("Reedsport", "Florence", "Hwy 101", 21);
	a.InsertArc("Eugene", "Florence", "Hwy 126", 61);
	//Read();
}
#endif