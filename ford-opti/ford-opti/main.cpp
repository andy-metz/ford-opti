#include <iostream>
#include "ford-opti.h"

using namespace std;
int main()
{

	Graph *g = new Graph();




	g->add_edge("A", "B", 10.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "E", 5.0);
	g->add_edge("B", "E", 7.0);


	cout << g->getVertices_list()->getVertexList();

	cout << "Fin" << endl;
	system("pause");

}