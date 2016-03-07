#include <iostream>
#include "ford-opti.h"
#include <map>
#include <string>

using namespace std;
int main()
{

	Graph *g = new Graph();




	g->add_edge("A", "B", 4.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "D", 2.0);
	g->add_edge("B", "D", 1.0);

	/*
	cout << g->getVertices_list()->getVertexList();

	map<string, Vertex *> dict;
	dict["A"] = g->getVertex("A");


	cout << "Test hash:" << endl;
	Vertex * v = dict["D"];

	if (v)
		cout << v->getName() << endl;
	//cout << v.getName()) << "\n";
	*/

	cout << "Nombre sommets:" << g->getNumberOfVertex() << endl;
	//std::map<string, Vertex> x = { { "A", g->getVertex("A") }, { "B", g->getVertex("B") }, { "C", g->getVertex("C") } };
	//map<string, Vertex> x = { { "A", g->getVertex("A") }, { "B", g->getVertex("B") }, { "C", g->getVertex("C") } };

	g->setStartVertex("A");

	g->shortest_path();


	cout <<  "predecessor:" << g->getPredecessor("D");
	cout << endl << "Fin" << endl;
	system("pause");

}