// opti
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <math.h>
#include <algorithm>

using namespace std;

class Vertex{

private:
	string name;
public:
	Vertex(string name) :name(name){
	}

	string getName(){
		return name;
	}
};

class Edge{
private:
	double weight;
	Vertex * source;
	Vertex * destination;

public:
	Edge(Vertex *s, Vertex *d, double w) : source(s), destination(d), weight(w){

	}
	Vertex * getVertexSource(){
		return source;
	}
	Vertex * getVertexDestination(){
		return destination;
	}

	void setWeight(double w){
		weight = w;
		}
	double getWeight(){
		return weight;
	}

};

class Vertices_list{
public:
	Vertex * vertex;
	Vertices_list * next;

	Vertices_list(Vertex  * v):vertex(v){
	}

	const Vertices_list & operator= (const Vertices_list & v){
		if (this != &v){
			vertex = v.vertex;
			next = v.next;
		}
	}

	string getVertexList(){
		Vertices_list * vl = this;
		string s;
		while (vl){
			s = s + vl->vertex->getName() + " ";
			vl = vl->next;
		}

		return s;
	}

	friend ostream & operator << (ostream & os, const Vertices_list & vl);
};

class Edges_list{
public:
	Edge * edge;
	Edges_list * next;
	Edges_list(Edge *e) :edge(e){
	}
};





// List of predecessors
class Pred{

};

// List of successors for each vertex of a graph
class Successors{
public:
	string value;
	double w;
	Successors *next;
};
// 
// 


//
// Graph Class
//
class Graph{

private:
	Vertex * start_vertex;
	Vertices_list *vertices_list = NULL;
	Edges_list *edges_list = NULL;
	// Concern Shortest path
	map<string, double> lambda;
	unordered_set<string> *marked_vertex;
	unordered_set<string> *alternate_marked_vertex;
	map<string, Successors *> successors_list;
	map<string, string> predecessor;



public:
	Graph(){
		start_vertex = NULL;
	}

	// Add a vertex
	Vertex *  add_vertex(string name){
		Vertex * v;
		Vertices_list *vl;
		vl = vertices_list;
		while (vl){
			v = vl->vertex;
			if (v->getName() == name)
				return v;
			vl = vl->next;
		}
		v = new Vertex(name);
		vl = new Vertices_list(v);
		vl->next = vertices_list;
		vertices_list = vl;
		return v;
	}

	string getPredecessor(string x){
		return predecessor[x];
	}

	void setStartVertex(string s){
		start_vertex = add_vertex(s);
	}

	Vertices_list * getVertices_list(){
		return(vertices_list);
	}


	int getNumberOfVertex(){
		int n = 0;
		Vertex * v;

		Vertices_list *vl;
		vl = vertices_list;
		while (vl){
			n++;
			vl = vl->next;
		}
		return n;
	}


	// Add an edge
	Edge * add_edge(string es, string ed, double w){
		Edges_list *el;
		Vertex *s, *d;
		Edge * e;

		s = getVertex(es);
		if (!s)
			s = add_vertex(es);
		d = getVertex(ed);
		if (!d)
			d = add_vertex(ed);
		// Test if edge already exists

		if (e = getEdge(es, ed))
			e->setWeight(w);
		else
			e = new Edge(s, d, w);


		el = new Edges_list(e);
		el->next = edges_list;
		edges_list = el;
		return e;
	}


	// Get an edge
	Edge * getEdge(string s, string d){
		Edges_list * el;

		el = edges_list;
		while (el){
			if ((el->edge->getVertexSource()->getName() == s) && (el->edge->getVertexDestination()->getName() == d))
				return el->edge;
			el = el->next;
		}
		return NULL;
	}


	// Get a vertex
	Vertex * getVertex(string n){
		Vertices_list *vl;
		vl = this->vertices_list;
		while (vl){
			if (vl->vertex->getName() == n)
				return vl->vertex;
			vl = vl->next;
			}
		return NULL;
	}


	// relax


	// algo Ford-Bellman optimized
	void shortest_path(){
		Vertices_list * vl = vertices_list;
		Edges_list * el;
		Edge *e;
		Successors * s;
		map<string, Successors *>::iterator it;
		// initialisation successor_list
		el = edges_list;
		while (edges_list){
			e = edges_list->edge;
			s = new Successors();
			// s->next = NULL;
			s->value = e->getVertexDestination()->getName();
			s->w = e->getWeight();
			it = successors_list.find(e->getVertexSource()->getName());
			if (it == successors_list.end()){  // doesn't exists
				s->next = NULL;


			}
			else{
				s->next = it->second;
			}
			successors_list[e->getVertexSource()->getName()] = s;

			edges_list = edges_list->next;
		}



		int k = 0;
		int n = this->getNumberOfVertex();

		marked_vertex = new unordered_set<string>;
		alternate_marked_vertex = new unordered_set<string>;

		while (vl)
		{
			lambda[vl->vertex->getName()] = DBL_MAX; // Double max afffectation to all vertex 
			predecessor[vl->vertex->getName()] = "";
			vl = vl->next;
		}

		//
		lambda[this->start_vertex->getName()] = 0;

		// init marked_vertex
		marked_vertex->insert(start_vertex->getName());


		while ((k < n) && !marked_vertex->empty()){
			k++;
			alternate_marked_vertex->clear();


			for (auto itr = marked_vertex->begin(); itr != marked_vertex->end(); ++itr){

				it = successors_list.find(*itr);
				if (it != successors_list.end()){
					Successors *next_successor;
					next_successor = it->second;
					while (next_successor)
					{

						if (lambda[*itr] + next_successor->w < lambda[next_successor->value]){ // Better path
							predecessor[next_successor->value] = *itr;
							lambda[next_successor->value] = lambda[*itr] + next_successor->w;
							alternate_marked_vertex->insert(next_successor->value);
						}
						cout << endl << next_successor->value;



						next_successor = next_successor->next;
					}
				}

				//set<string>::const_iterator mkit(marked_vertex.begin()), mkend(marked_vertex.end());
				//for (; mkit != mkend; ++mkit){
				/*
				for_each(marked_vertex->begin(), marked_vertex->end(), [](string v){

				it = successors_list.find(e->getVertexSource()->getName());
				if (it == successors_list.end()){  // doesn't exists
				s->next = NULL;
				cout << v;


				}

				);*/
			}

		// 
		marked_vertex->clear();
		for (auto itr = alternate_marked_vertex->begin(); itr != alternate_marked_vertex->end(); ++itr)
		marked_vertex->insert(*itr);
		}

	}
};