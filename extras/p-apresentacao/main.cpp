/*g++ -I/caminho/lib2Okean.hpp arquivo.cpp*/
#include <lib2Okean.hpp>

int main(){
    Graphs<int> topology(11, true);
    
    topology.addDirecEdge(10, 1, 10);
    topology.addDirecEdge(1, 2, 8);
    topology.addDirecEdge(2, 3, 4);
    topology.addDirecEdge(3, 2, 4);
    topology.addDirecEdge(3, 6, 6);
    topology.addDirecEdge(2, 5, 6);
    topology.addDirecEdge(5, 6, 2);
    topology.addDirecEdge(6, 5, 2);
    topology.addDirecEdge(5, 8, 10);

    cout << "Matriz:"<< endl;
    topology.printAdjacencyMatrix();


    return 0;
}
