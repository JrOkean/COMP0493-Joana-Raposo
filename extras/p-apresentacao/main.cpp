/*g++ -I/caminho/lib2Okean.hpp arquivo.cpp*/
#include <lib2Okean.hpp>

int main(){
    Graphs<int> topology(4, true);
    
    topology.addDirecEdge(0, 1, 10);
    topology.addDirecEdge(0, 2, 5);
    topology.addDirecEdge(1, 3, 5);
    topology.addDirecEdge(2, 3, 10);
    topology.addDirecEdge(1, 2, 3);

    cout << "Matriz:"<< endl;
    topology.printAdjacencyMatrix();

    int maxFlow = topology.FordFulkerson(0, 3);
    cout << "maxFlow com DFS: " << maxFlow << endl;

    int maxFlow2 = topology.EdmondsKarp(0, 3);
    cout << "maxFlow com BFS: " << maxFlow2 << endl;

    
    return 0;
}
