#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <iomanip> // setw

using namespace std;
typedef unsigned int Vertex;

typedef unsigned int Weight;

class Edge {
public:
	Weight weight;
	Edge(): weight(0) {} 
	Edge(Weight _weight): weight(_weight) {} 
};


class DigraphAM {
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;
    public:
        DigraphAM(unsigned int);
        ~DigraphAM();
        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);
        unsigned int get_num_vertices() {return num_vertices;}
        unsigned int get_num_edges() {return num_edges;}
        list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex u, Vertex v){return adj[u][v].weight;}
};

DigraphAM::DigraphAM(unsigned int num_vertices): num_vertices(num_vertices), num_edges(0){
    const unsigned int LINES = num_vertices;
    const unsigned int COLUMNS = num_vertices;
    adj = new Edge*[LINES];
    for(unsigned int i = 0; i < LINES; i++){
        adj[i] = new Edge[COLUMNS];
    }
}

DigraphAM::~DigraphAM(){
    const unsigned int LINES = num_vertices;
    for(unsigned int i = 0; i < LINES; ++i){
        delete[] adj[i];
    }
    delete[] adj;
    cout << "\nBye Bye Graph\n";
}

void DigraphAM::add_edge(Vertex u, Vertex v){
    Edge edge{1};
    adj[u][v] = edge;
    num_edges++;
}

void DigraphAM::remove_edge(Vertex u, Vertex v){
    Edge edge{0};
    adj[u][v] = edge;
    num_edges--;
}

list<Vertex>DigraphAM::get_adj(Vertex u){
    list<Vertex> values;
    for(unsigned int v = 0; v < num_vertices; ++v){
        if(adj[u][v].weight != 0){
            values.push_back(v);
        }
    }
    return values;
}

void display_matadj_graph(DigraphAM &g){
    int k = 3; // numeric field width
    // build the horizontal header
    cout << "     ";
    for(unsigned int j = 0; j < g.get_num_vertices(); j++){
        cout << setw(k) << j;
    }
    cout << endl;
    for(unsigned int j = 0; j < g.get_num_vertices()*(unsigned int)k + 3; j++){
        cout << "-";
    }
    cout << endl;

    // build each line of the matrix
    for(unsigned int i = 0; i < g.get_num_vertices(); i++){
        // line header value
        cout << setw(1) << i;
        cout << " |";
        // Line values
        for(unsigned int j = 0; j < g.get_num_vertices(); j++){
            cout << setw(k) << g.get_weight_edge(i, j);
        }
        cout << endl;
    }
}

void input_graph(DigraphAM &g, unsigned int num_edges) {
    Vertex u = 0, v = 0;
    for(unsigned int i = 0; i < num_edges; i++){
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    cout << "num_vertices: " << endl;
    cout << "num_edges: " << endl;

    DigraphAM g{num_vertices};
    input_graph(g, num_edges);
    display_matadj_graph(g);

    // cout << "\nRemove edge: " << endl;
    // g.remove_edge(0, 1);
    // display_matadj_graph(g);
    return 0;
}

// 4 7 0 1 1 0 1 2 0 2 0 3 3 0 3 2