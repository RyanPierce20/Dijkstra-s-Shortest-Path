/*************************************************************
* Author:		Ryan Pierce
* Filename:		Lab5.cpp
* Date Created:	3/1/15
* Modifications:	3/3/15
**************************************************************/
/************************************************************************
* Class: Graph
*
* Purpose: This class makes the graph from vertex's and arcs/edges
*
* Manager functions:
* 		Graph();
	~Graph();
	Graph(const Graph & copy);
	Graph & operator=(const Graph & rhs);

	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertArc(V from, V to, E edge, int weight);
	void DeleteArc(V from, V to, E edge);

	void DepthFirst(void(*visit) (V));
	void BreadthFirst(void(*visit) (V));
	bool isEmpty();

	list<Vertex<V, E>> & GetList();

*
* Methods:
*	list<Vertex<V,E>> _list;
	int _count;
*************************************************************************/
#ifndef Graph_H
#define Graph_H
#include "Vertex.h"
#include "Arc.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
using std::list;
using std::stack;
using std::queue;
using std::vector;
using std::cout;
using std::endl;
#include "Vertex.h"
template <typename V, typename E>
class Vertex;
template <typename V, typename E>
class Arc;
template <typename V, typename E>
class Graph 
{
public:
	Graph();
	~Graph();
	Graph(const Graph & copy);
	Graph & operator=(const Graph & rhs);

	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertArc(V from, V to, E edge, int weight);
	void DeleteArc(V from, V to, E edge);

	void DepthFirst(void(*visit) (V));
	void BreadthFirst(void(*visit) (V));
	bool isEmpty();

	list<Vertex<V, E>> & GetList();

private:
	list<Vertex<V,E>> _list;
	int _count;
};
template<typename V, typename E>
list<Vertex<V, E>> & Graph<V, E>::GetList()
{
	return _list;
}
/**********************************************************************
* Purpose: This function is the defualt c'tor
*
* Precondition:
*     nothing
*
* Postcondition:
*      nothing
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph()
{}
/**********************************************************************
* Purpose: This function is the d'tor
*
* Precondition:
*     nothing
*
* Postcondition:
*      nothing
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::~Graph()
{}
/**********************************************************************
* Purpose: This function is the copy c'tor
*
* Precondition:
*     everyhitng is passed in to copy
*
* Postcondition:
*      everything is copied
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(const Graph & copy) : m_vertex(copy.m_vertex)
{}
/**********************************************************************
* Purpose: This function is the op equals
*
* Precondition:
*     everyhitng is passed in to copy
*
* Postcondition:
*      everything is copied
*
************************************************************************/
template<typename V, typename E>
Graph<V, E> & Graph<V, E>::operator=(const Graph & rhs)
{
	if (this != &rhs)
	{
		_list = rhs._list;
	}
	return *this;
}
/**********************************************************************
* Purpose: This function inserts the vertex
*
* Precondition:
*     the vertex is passed in
*
* Postcondition:
*      creates a new vertex
*
************************************************************************/
template <typename V, typename E>
void Graph<V,E>::InsertVertex(V data)
{
	bool same = false;
	if (isEmpty() == true) //if empty then insert and return
	{
		Vertex<V, E> * vertex = new Vertex < V, E >;
		vertex->SetData(data);
		vertex->SetProcessed(false);
		_list.push_back(*vertex);
		delete vertex;
		return;
	}
	if (isEmpty() == false) //if not empty then traverse through list to see if it already exists
	{
		for (list<Vertex<V, E>>::iterator it = _list.begin(); it != _list.end(); ++it)
		{
			if (it->GetData() == data)
			{
				cout << "Can't Enter the same Vertex" << endl;
				same = true;
			}
		}
		if (same != true)//if not exists then insert it
		{
			Vertex<V, E> * vertex = new Vertex < V, E >;
			vertex->SetData(data);
			vertex->SetProcessed(false);
			_list.push_back(*vertex);
			delete vertex;
		}
	}
}
/**********************************************************************
* Purpose: This function deletes the vertex and its edge 
*
* Precondition:
*     the vertex to be deleted in passed
*
* Postcondition:
*     deletes the vertex and the edges it has
*
************************************************************************/
template <typename V, typename E>
void Graph<V,E>::DeleteVertex(V data)
{
	list<Vertex<V, E>>::iterator front = _list.begin();
	list<Vertex<V, E>>::iterator end = _list.end();
	bool del = false;
	if (isEmpty() == true)
	{
		cout << "Can't delete an Empty list" << endl;
		return;
	}
	while (del == false && front != end) //find vertex to delete
	{
		if (front->GetData() == data) //once found
		{
			Vertex<V, E> * VertexList = new Vertex < V, E > ;
			*VertexList = *front;
			if (VertexList->_edges.empty() == false) //if not empty
			{
				list<Arc<V, E>>::iterator delet = VertexList->_edges.begin(); //get iterator for the list
				for (int i = 0; i < VertexList->_edges.size(); i++) //for loop through entire edges of the vertex
				{
					DeleteArc(VertexList->GetData(), delet->GetDestination()->GetData(), delet->GetData());//for each edge in vertex, delete it
					++delet;
				}
				_list.erase(front); //fully delete the vertex
				del = true;
			}
			else
			{
				_list.erase(front);//if edges empty then delete the vertex
				break;
			}
			delete VertexList;
		}
		if(del ==false) //if not deleted then increment to next vertex
			front++;
	}

}
/**********************************************************************
* Purpose: This function inserts the edge 
*
* Precondition:
*     the vertex's to and from where the edge wants to be and the weight and actual edge
*
* Postcondition:
*      the edge is connected between the two vertex's
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertArc(V from, V to, E edge, int weight)
{
	bool current = false;
	list<Vertex<V, E>>::iterator it = _list.begin();
	list<Vertex<V, E>>::iterator end = _list.end();
	Vertex<V, E> list1;
	Vertex<V, E> list2;
	Arc<V, E> * edge1 = new Arc< V, E > ;

	edge1->SetData(edge);
	edge1->SetWeight(weight);

	while (it != end && current != true) //find the destination in the list
	{
		list1 = *it;
		if (it->GetData() == to) //if there the same
		{
			edge1->SetDestination(&*it); //set temp arc to destination
			current = true;
		}
		++it;
	}
	--it;//go back to the temp arc

	list<Vertex<V, E>>::iterator iter = _list.begin();
	Arc<V, E> * edge2 = new Arc < V, E > ;
	edge2->SetData(edge);
	edge2->SetWeight(weight); //same thing as the top

	while (iter != end && current == true) //go through until the from is found
	{
		list2 = *iter; //each time go to next list
		if (iter->GetData() == from) //if same
		{
			edge2->SetDestination(&*iter);//set destination to from
			list1._edges.push_back(*edge2);
			list2._edges.push_back(*edge1);//set all values to other arc for bi-direction
			*iter = list2;
			*it = list1;
			current = false; //make the current false so it exits loop
		}
		++iter; //goes until it matches end
	}
	delete edge1; //delete the temps
	delete edge2;

}
/**********************************************************************
* Purpose: This function deletes an edge
*
* Precondition:
*     the vertex's from and to and the actual edge
*
* Postcondition:
*      the edge is deleted from both vertexs
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DeleteArc(V from, V to, E edge)
{
	//this will only display the vertexs with arcs
	bool done = false;
	list<Vertex<V, E>>::iterator it = _list.begin();
	Vertex<V, E> vertex1;
	Arc<V, E> edge1;

	if (isEmpty() != true)
	{
		edge1.SetData(edge);

		while (it != _list.end())//iterate through list
		{
			vertex1 = *it;
			if (vertex1.GetData() == from)//if from then delete its edges also
			{
				vertex1._edges.remove(edge1);
				*it = vertex1;
			}
			if (vertex1.GetData() == to)//same thing but for to
			{
				vertex1._edges.remove(edge1);
				*it = vertex1;
			}
			++it;
		}
	}
	else
		cout << "Cant Delete an Arc that doesnt exist" << endl;
}
/**********************************************************************
* Purpose: This function is display the data depth first
*
* Precondition:
*     visit function pointer
*
* Postcondition:
*      displays all data in the list depth first
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit) (V ))
{
	//this will only display the vertexs with arcs
	if (isEmpty() == false)
	{
		stack<Vertex<V, E> *> stack;
		stack.push(&_list.front());
		_list.front().SetProcessed(true);

		while (!stack.empty())
		{
			Vertex<V, E> * vertexs = stack.top();//get top node
			stack.pop();//pop off
			visit(vertexs->GetData());//cout popped off

			for (list<Arc<V, E>>::iterator it = vertexs->_edges.begin(); it != vertexs->_edges.end(); it++)
			{
				if (it->GetDestination()->GetProcessed() == false)
				{
					it->GetDestination()->SetProcessed(true);
					stack.push(it->_destination);
				}
				
			}
		}
		for (list<Vertex<V, E>>::iterator it2 = _list.begin(); it2 != _list.end(); ++it2)
		{
			it2->SetProcessed(false);
		}
	}
}
/**********************************************************************
* Purpose: This function is display breadthfirst
*
* Precondition:
*     visit function pointer
*
* Postcondition:
*      displays all elements
*
************************************************************************/
template <typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit) (V ))
{
	if (isEmpty() == false)
	{
		queue<Vertex<V, E> *> q; //make a queue
		q.push(&_list.front()); //put list on front
		_list.front()._processed = true;//make it true so it doesnt repeat it

		while (!q.empty()) //while list isnt empty
		{
			Vertex<V, E> * vertexs = q.front();//get the front
			q.pop();//take off stack
			visit(vertexs->GetData());//display

			for (list<Arc<V, E>>::iterator it = vertexs->_edges.begin(); it != vertexs->_edges.end(); ++it)
			{
				if (it->GetDestination()->GetProcessed() == false)//if not diplsayed then display
				{
					it->GetDestination()->SetProcessed(true);//make processsed
					q.push(it->_destination);//get next
				}
			}
		}
		for (list<Vertex<V, E>>::iterator it2 = _list.begin(); it2 != _list.end(); ++it2)
		{
			it2->SetProcessed(false);//set everything back to not processed so it can display again
		}
	}
}
/**********************************************************************
* Purpose: This function is checking if the list is empty
*
* Precondition:
*     nothing
*
* Postcondition:
*      returns bool if empty or not
*
************************************************************************/
template <typename V, typename E>
bool Graph<V, E>::isEmpty()
{
	bool empty = false;
	if (_list.empty())
	{
		empty = true;
	}
	return empty;
}

#endif