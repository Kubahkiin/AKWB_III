#include "instance.hpp"
#include "Graph.h"

int main()
{
    vector < vector < char > > nucl;
    vector < vector < int > > qual;
    vector < vector < string > > oligos;
    int word_size;
    load_vector(nucl);
    load_vector(qual);

    purge_when_quality_lower(nucl, qual, 10);
    cout << "\nPodaj wielkosc oligonukleotydu (4 - 9)\n";
    cin >> word_size;



    Graph* G = new Graph(nucl, word_size);
    G->display_nodes();
    cout << "\nLaczenie wierzcholkow:\n";
    G->connectNodes(10*word_size);
    G->findMotive();

    delete G;

    return 0;
}
