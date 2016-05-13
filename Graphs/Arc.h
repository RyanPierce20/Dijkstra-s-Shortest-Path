/*************************************************************
* Author:		Ryan Pierce
* Filename:		Lab5.cpp
* Date Created:	3/1/15
* Modifications:	3/3/15
**************************************************************/
/************************************************************************
* Class: Arc
*
* Purpose: This class makes the arc's for the graph
*
* Manager functions:
* 		Arc();
	~Arc();
	Arc(const Arc & copy);
	Arc<V,E> &operator =(const Arc & rhs);
	bool operator ==(const Arc & rhs);
	void SetData(E data);
	void SetWeight(int weight);
	void SetDestination(Vertex<V, E> * dest);
	E GetData();
	int GetWeight();
	Vertex<V, E> * GetDestination();

*
* Methods:
*	Vertex<V,E> * _destination;
	int _weight;
	E _data;
*************************************************************************/
#ifndef Arc_H
#define Arc_H
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
class Graph;

template <typename V, typename E>
class Arc
{
	template <typename V, typename E>
	friend class Graph;
public:
	Arc();
	~Arc();
	Arc(const Arc & copy);
	Arc<V,E> &operator =(const Arc & rhs);
	bool operator ==(const Arc & rhs);
	void SetData(E data);
	void SetWeight(int weight);
	void SetDestination(Vertex<V, E> * dest);
	E GetData();
	int GetWeight();
	Vertex<V, E> & GetDestination();

private:
	Vertex<V,E> * _destination;
	int _weight;
	E _data;
};
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
Arc<V, E>::Arc()
{}
/**********************************************************************
* Purpose: This function is the d'tor
*
* Precondition:
*     nothing
*
* Postcondition:
*      data members set to default
*
************************************************************************/
template <typename V, typename E>
Arc<V, E>::~Arc()
{
	_weight = 0;
	_destination = nullptr;
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
Arc<V, E>::Arc(const Arc & copy) :_data(copy._data), _weight(copy._weight), _destination(copy._destination)
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
Arc<V,E> & Arc<V, E>::operator =(const Arc & rhs)
{
	if (this != &rhs)
	{
		_data = rhs._data;
		_weight = rhs._weight;
		_destination = rhs._destination;
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
bool Arc<V, E>::operator ==(const Arc & rhs)
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
void Arc<V, E>::SetData(E data)
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
void Arc<V, E>::SetWeight(int weight)
{
	_weight = weight;
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
void Arc<V, E>::SetDestination(Vertex<V, E> * dest)
{
	_destination = dest;
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
E Arc<V, E>::GetData()
{
	return _data;
}
/**********************************************************************
* Purpose: This function is getting the weight
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
int Arc<V, E>::GetWeight()
{
	return _weight;
}
/**********************************************************************
* Purpose: This function is getting the destionaton
*
* Precondition:
*     nothing
*
* Postcondition:
*      gets the data
*
************************************************************************/
template <typename V, typename E>
Vertex<V, E> & Arc<V, E>::GetDestination()
{
	return * _destination;
}
#endif