#include <iostream>
#include "ford-opti.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void split(const string& s, char c,
	vector<string>& v) {
	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}


int main()
{

	Graph *g = new Graph();


	// negative cycle
	/*
	g->add_edge("A", "B", 1.0);
	g->add_edge("B", "A", -2.0);
	if (g->shortest_path("A"))
		g->getShortestPathTo("B");
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
	if (g->shortest_path("A"))
		g->getShortestPathTo("F");
	*/



	/* No negative cycle
	g->add_edge("A", "B", 1.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "B", -2.0);
	g->add_edge("C", "E", 1.0);
	g->add_edge("B", "D", 5.0);
	g->add_edge("B", "E", -1.0);
	g->add_edge("D", "F", 4.0);
	g->add_edge("E", "D", 1.0);
	g->add_edge("E", "F", 2.0);
	if (g->shortest_path("A"))
		g->getShortestPathTo("F");
	*/

	/*
	g->add_edge("A", "B", 1.0);
	g->add_edge("A", "C", 2.0);
	g->add_edge("C", "B", -2.0);
	g->add_edge("C", "E", 1.0);
	g->add_edge("B", "D", 5.0);
	g->add_edge("B", "E", -1.0);
	g->add_edge("D", "F", 4.0);
	g->add_edge("E", "D", 1.0);
	g->add_edge("E", "F", 2.0);
	g->add_vertex("X");
	if (g->shortest_path("A"))
		g->getShortestPathTo("X");
	*/



	// TD 4 Exo 4
	/*
	g->add_edge("1", "2", 3.0);
	g->add_edge("1", "3", 2.0);
	g->add_edge("2", "4", -2.0);
	g->add_edge("2", "5", 2.0);
	g->add_edge("3", "2", -1.0);
	g->add_edge("3", "4", 4.0);
	g->add_edge("4", "5", 4.0);
	g->add_edge("4", "6", 2.0);
	g->add_edge("5", "2", 7.0);
	g->add_edge("5", "8", 8.0);
	if (g->shortest_path("1"))
		g->getShortestPathTo("6");
	*/


	// TD 4 Exo 1
	
	g->add_edge("1", "2", 7.0);
	g->add_edge("1", "3", 1.0);
	g->add_edge("2", "4", 4.0);
	g->add_edge("2", "6", 1.0);
	g->add_edge("3", "2", 5.0);
	g->add_edge("3", "5", 2.0);
	g->add_edge("3", "6", 7.0);
	g->add_edge("4", "7", 2.0);
	g->add_edge("5", "2", 2.0);
	g->add_edge("5", "7", 10.0);
	g->add_edge("6", "4", 5.0);
	g->add_edge("6", "5", 3.0);
	g->add_edge("6", "7", 8.0);
	if (g->shortest_path("1"))
		g->getShortestPathTo("7");
	
	


	//TEST FICHIER
	/*
	ifstream fichier("g1.grp", ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a réussi
	{

		string s, d;
		double w;

		if (fichier)
		{
			string ligne;
			while (getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
			{
				vector<string> v;
				split(ligne, ':', v);
				s = v[0];
				d = v[1];
				w = stod(v[2]);

				g->add_edge(s, d, w);
				
			}
		}

		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	if (g->shortest_path("i1"))
		g->getShortestPathTo("i112");
	*/
	// FIN TEST FICHIER



	cout << endl << "End" << endl;
	system("pause");

}
