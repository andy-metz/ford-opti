// opti
#include <string>
#include <iostream>

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
class 
// 




// Graph Class
class Graph{

private:
	Edge * Start_edge;
	Vertices_list *vertices_list = NULL;
	Edges_list *edges_list = NULL;

public:
	Graph(){
		Start_edge = NULL;
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

	Vertices_list * getVertices_list(){
		return(vertices_list);
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


	// algo Ford-Bellman optimisé
	void shortest_path(){
		// initialisation




	}
};