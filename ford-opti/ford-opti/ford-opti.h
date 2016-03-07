/*
* Ford-Bellman algorithm (optimized version)
*
* Authors: André ERBA - Olivier Mertz
*
*
*
*/
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <math.h>
#include <algorithm>


using namespace std;

/*
*  Vertex class
*/
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


/*
*  Edge class
*/
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


/*
*  Vertices list of the graph
*/
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


/*
*  Edges list of the graph
*/
class Edges_list{
public:
	Edge * edge;
	Edges_list * next;
	Edges_list(Edge *e) :edge(e){
	}
};




/*
*  List of successors of each vertex of the graph
*/
class Successors{
public:
	string value;
	double w;
	Successors *next;
};



/*
*  Graph class
* cotains shortest_path method to retrieve shortest path using Ford-Bellman optimized
*/
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

	// Add a vertex, if already exists return a poiter to it
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


	// Return predecessor
	string getPredecessor(string x){
		return predecessor[x];
	}


	// Set the starting vertex of the graph to execute shortest_path
	void setStartVertex(string s){
		start_vertex = add_vertex(s);
	}


	// return a pointer to the vertices_list
	Vertices_list * getVertices_list(){
		return(vertices_list);
	}

	// return the number of vertex
	int getNumberOfVertex(){
		int n = 0;
		// Vertex * v;

		Vertices_list *vl;
		vl = vertices_list;
		while (vl){
			n++;
			vl = vl->next;
		}
		return n;
	}


	// Add an edge and vertices if not already in, update vertices_list to
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


	// Return a pointer to an edge giving source edge and destination edge
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


	// Return a vertex from vertices_list
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

// Return weight of shortest path from any edge of the graph
void getShortestPathTo(string x){
	static string  first = ""; 

	if (lambda[x] == DBL_MAX){  // Test if a shortest path exists
		cout << "No shortest path for this vertex" << endl;
		return;
	}

	if (first == "")
		first = x;
	if (x == ""){
		cout << "Shortest path: ";
		return;
	}

	getShortestPathTo(predecessor[x]);

	if (first != x)
		cout << x << "->";
	else{
		cout << x << endl;
		cout << "Weight:" << lambda[x];
	}

	return;
}

/*
*
*  Ford-Bellman optimized method
*  return 0 if negative cycle detected
*         1 otherwise
*/
double shortest_path(string sv){
		Vertices_list * vl = vertices_list;
		Edges_list * el;
		Edge *e;
		Successors * s;
		map<string, Successors *>::iterator it;

		setStartVertex(sv); // Set start_vertex

		// successor_list populate
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

		while (vl){ // 
			lambda[vl->vertex->getName()] = DBL_MAX; // DBL_MAX affectation to all vertex 
			predecessor[vl->vertex->getName()] = "";
			vl = vl->next;
		}

		// Set start_edge to 0.0
		lambda[this->start_vertex->getName()] = 0;

		// init marked_vertex with start_vertex
		marked_vertex->insert(start_vertex->getName());


		//
		//  MAIN LOOP
		//
		while ((k < n) && !marked_vertex->empty()){
			k++;
			alternate_marked_vertex->clear();

			for (auto itr = marked_vertex->begin(); itr != marked_vertex->end(); ++itr){

				it = successors_list.find(*itr);
				if (it != successors_list.end()){
					Successors *next_successor;
					next_successor = it->second;
					while (next_successor){ 
						if (lambda[*itr] + next_successor->w <  lambda[next_successor->value]){ // Better path (relaxation)
							predecessor[next_successor->value] = *itr;
							lambda[next_successor->value] = lambda[*itr] + next_successor->w;
							alternate_marked_vertex->insert(next_successor->value);
						}
						next_successor = next_successor->next;
					}
				}
			}
		// Update marked_vertex with alternate_marked_vertex
		marked_vertex->clear();
		for (auto itr = alternate_marked_vertex->begin(); itr != alternate_marked_vertex->end(); ++itr)
		marked_vertex->insert(*itr);
		}  // END MAIN LOOP

		// Negative cycle test
		if (!marked_vertex->empty()){
			cout << "This graph contains a negative cycle!!!";
			return 0;
		}
		else
			return 1; 
	}
};

