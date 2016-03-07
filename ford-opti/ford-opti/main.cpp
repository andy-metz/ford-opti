#include <iostream>
#include "ford-opti.h"
#include <map>
#include <string>

using namespace std;
int main()
{

	Graph *g = new Graph();


	// negative cycle
	/*
	g->add_edge("A", "B", 1.0);
	g->add_edge("B", "A", -2.0);
	*/

	// negative cycle
	/*
	g->add_edge("A", "B", 1.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "B", -1.0);
	g->add_edge("C", "E", 1.0);
	g->add_edge("D", "B", -1.0);
	g->add_edge("B", "E", -1.0);
	g->add_edge("D", "F", 4.0);
	g->add_edge("E", "D", 1.0);
	g->add_edge("E", "F", 2.0);
	*/

	
	g->add_edge("A", "B", 1.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "B", -2.0);
	g->add_edge("C", "E", 1.0);
	g->add_edge("B", "D", 5.0);
	g->add_edge("B", "E", -1.0);
	g->add_edge("D", "F", 4.0);
	g->add_edge("E", "D", 1.0);
	g->add_edge("E", "F", 2.0);
	


	cout << "Nombre sommets:" << g->getNumberOfVertex() << endl;


	g->setStartVertex("A");
	if (g->shortest_path())
		g->getShortestPathTo("B");




	cout << endl << "Fin" << endl;
	system("pause");

}
