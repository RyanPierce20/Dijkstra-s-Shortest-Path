/*************************************************************
* Author:		Ryan Pierce
* Filename:		Lab5.cpp
* Date Created:	3/1/15
* Modifications:	3/3/15
**************************************************************/
/************************************************************************
* Class: Vertex
*
* Purpose: This class makes the vertex's in the graph
*
* Manager functions:
* 		Vertex(V data);
	Vertex();
	~Vertex();
	Vertex(const Vertex & copy);
	Vertex<V,E> & operator = (const Vertex & rhs);
	bool operator ==(const Vertex & rhs);
	void SetData(V data);
	void SetEdges(list<Arc<V,E>> edges);
	void SetProcessed(bool proc);
	void SetInDegree(int in);
	void SetOutDegree(int out);
	V GetData();
	list<Arc<V,E>> & GetEdges();
	bool GetProcessed();
	int GetInDegree();
	int GetOutDegree();

*
* Methods:
*	V _data;
	int _indegree;
	int _outdegree;
	bool _processed;
	list<Arc<V,E>> _edges;
*		...
*************************************************************************/
#ifndef Vertex_H
#define Vertex_H
#include <iostream>
#include <list>
#include <queue>
#include <stack>
using std::list;
using std::stack;
using std::queue;
using std::cout;
using std::endl;
template <typename V, typename E>
class Arc;

template <typename V, typename E>
class Vertex
{
	template <typename V, typename E>
	friend class Graph;
public:
	Vertex(V data);
	Vertex();
	~Vertex();
	Vertex(const Vertex & copy);
	Vertex<V,E> & operator = (const Vertex & rhs);
	bool operator ==(const Vertex & rhs);
	void SetData(V data);
	void SetEdges(list<Arc<V,E>> edges);
	void SetProcessed(bool proc);
	void SetInDegree(int in);
	void SetOutDegree(int out);
	V GetData();
	list<Arc<V,E>> & GetEdges();
	bool GetProcessed();
	int GetInDegree();
	int GetOutDegree();

private:
	V _data;
	int _indegree;
	int _outdegree;
	bool _processed;
	list<Arc<V,E>> _edges;
};
template <typename V, typename E>
Vertex<V, E>::Vertex(V data)
{
	_data = data;
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
template <typename V, typename E>
Vertex<V,E>::Vertex()
{}
/**********************************************************************
* Purpose: This function is the d'tor
*
* Precondition:
*     nothing
*
* Postcondition:
*      processed set false
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E>::~Vertex()
{
	_processed = false;
}
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
template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex & copy) :_data(copy._data), _indegree(copy._indegree), _outdegree(copy._outdegree), _processed(copy._processed), _edges(copy._edges)
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
template <typename V, typename E>
Vertex<V,E> & Vertex<V, E>::operator =(const Vertex & rhs)
{
	if (this != &rhs)
	{
		_data = rhs._data;
		_indegree = rhs._indegree;
		_outdegree = rhs._outdegree;
		_edges = rhs._edges;
		_processed = rhs._processed;
	}
	return *this;
}
/**********************************************************************
* Purpose: This function is the comparing equals
*
* Precondition:
*     everyhitng is passed in to copy
*
* Postcondition:
*      if the same then return true
*
************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::operator ==(const Vertex & rhs)
{
	bool equal = false;
	if (_data == rhs._data)
	{
		equal = true;
	}
	return equal;
}
/**********************************************************************
* Purpose: This function is setting data
*
* Precondition:
*     everyhitng is passed in to set
*
* Postcondition:
*      sets the data
*
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::SetData(V data)
{
	_data = data;
}
/**********************************************************************
* Purpose: This function is setting data
*
* Precondition:
*     everyhitng is passed in to set
*
* Postcondition:
*      sets the data
*
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::SetEdges(list<Arc<V,E>> edges)
{
	_edges = edges;
}
/**********************************************************************
* Purpose: This function is setting data
*
* Precondition:
*     everyhitng is passed in to set
*
* Postcondition:
*      sets the data
*
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::SetProcessed(bool proc)
{
	_processed = proc;
}
/**********************************************************************
* Purpose: This function is setting data
*
* Precondition:
*     everyhitng is passed in to set
*
* Postcondition:
*      sets the data
*
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::SetInDegree(int in)
{
	_indegree = in;
}
/**********************************************************************
* Purpose: This function is setting data
*
* Precondition:
*     everyhitng is passed in to set
*
* Postcondition:
*      sets the data
*
************************************************************************/
template <typename V, typename E>
void Vertex<V, E>::SetOutDegree(int out)
{
	_outdegree = out;
}
/**********************************************************************
* Purpose: This function is getting the data
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
V Vertex<V, E>::GetData()
{
	return _data;
}
/**********************************************************************
* Purpose: This function is getting the data
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
list<Arc<V,E>> & Vertex<V, E>::GetEdges()
{
	return _edges;
}
/**********************************************************************
* Purpose: This function is getting the data
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::GetProcessed()
{
	return _processed;
}
/**********************************************************************
* Purpose: This function is getting the data
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
int Vertex<V, E>::GetInDegree()
{
	return _indegree;
}
/**********************************************************************
* Purpose: This function is getting the data
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
int Vertex<V, E>::GetOutDegree()
{
	return _outdegree;
}
#endif