#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdexcept>

template <typename T>
class GraphList {
private:
    struct Graph {
        bool isDirected;
        int numVertices;
        vector<vector<pair<int, T>>> adjList;
    };
    Graph g;

    void DFSUtil(int current, std::vector<bool>& visited, std::vector<int>& traversalOrder) const {
        visited[current] = true;
        traversalOrder.push_back(current);

        for (const auto& edge : g.adjList[current]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, traversalOrder);
            }
        }
    }

public:
    GraphList(int n, bool directed = false) {
        g.isDirected = directed;
        g.numVertices = n;
        g.adjList.resize(n);
    }
    void addEdge(int u, int v, T weight = T()) {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        g.adjList[u].emplace_back(v, weight);
        if (!g.isDirected) 
            g.adjList[v].emplace_back(u, weight);
    }
    void removeEdge(int u, int v) {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        auto& neighborsU = g.adjList[u];
        neighborsU.erase(
            std::remove_if(neighborsU.begin(), neighborsU.end(),
                           [v](const std::pair<int, T>& edge) { return edge.first == v; }),
            neighborsU.end()
        );
        if (!g.isDirected) {
            auto& neighborsV = g.adjList[v];
            neighborsV.erase(
                remove_if(neighborsV.begin(), neighborsV.end(),
                               [u](const std::pair<int, T>& edge) { return edge.first == u; }),
                neighborsV.end()
            );
        }
    }
    bool hasEdge(int u, int v) const {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        for (const auto& edge : g.adjList[u]) {
            if (edge.first == v)
                return true;
        }
        return false;
    }
    const vector<pair<int, T>>& getNeighbors(int u) const {
        if (u < 0 || u >= g.numVertices)
            throw out_of_range("Vértice inválido");
        return g.adjList[u];
    }
    void printList() const {
        for (int u = 0; u < g.numVertices; ++u) {
            cout << u << ": ";
            for (const auto& edge : g.adjList[u]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << "\n";
        }
    }
    // Outras funções úteis:
    int getNumVertices() const { return g.numVertices; }
    bool isDirected() const { return g.isDirected; }
    // DFS Recursivo a partir de um vértice inicial
    vector<int> DFSRecursive(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices) {
            throw out_of_range("Vértice inicial inválido");
        }

        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        DFSUtil(startVertex, visited, traversalOrder);
        return traversalOrder;
    }
};

template <typename T>
class GraphMatrix {
private:
    struct Graph {
        bool isDirected;
        int numVertices;
        vector<vector<T>> adjMatrix; 
    };
    Graph g;

    void DFSUtil(int current, vector<bool>& visited, vector<int>& traversalOrder) const {
        visited[current] = true;
        traversalOrder.push_back(current);
        // Visita todos os vizinhos
        for (int neighbor = 0; neighbor < g.numVertices; ++neighbor) {
            if (g.adjMatrix[current][neighbor] != T() && !visited[neighbor]) { // Se há aresta
                DFSUtil(neighbor, visited, traversalOrder);
            }
        }
    }

public:
    GraphMatrix(int n, bool directed = false) {
        g.isDirected = directed;
        g.numVertices = n;
        g.adjMatrix.resize(n, vector<T>(n, T()));
    }
    void addEdge(int u, int v, T weight = T()) {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        g.adjMatrix[u][v] = weight;
        if (!g.isDirected)
            g.adjMatrix[v][u] = weight;
    }
    void removeEdge(int u, int v) {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        g.adjMatrix[u][v] = T();
        if (!g.isDirected)
            g.adjMatrix[v][u] = T();
    }
    bool hasEdge(int u, int v) const {
        if (u < 0 || u >= g.numVertices || v < 0 || v >= g.numVertices)
            throw out_of_range("Vértice inválido");
        return g.adjMatrix[u][v] != T();
    }
    vector<int> getNeighbors(int u) const {
        if (u < 0 || u >= g.numVertices)
            throw out_of_range("Vértice inválido");
        vector<int> neighbors;
        for (int v = 0; v < g.numVertices; ++v) {
            if (g.adjMatrix[u][v] != T())
                neighbors.push_back(v);
        }
        return neighbors;
    }
    void printMatrix() const {
        for (const auto& row : g.adjMatrix) {
            for (const auto& val : row) {
                std::cout << val << " ";
            }
            cout << "\n";
        }
    }
    // Outras funções úteis:
    int getNumVertices() const { return g.numVertices; }
    bool isDirected() const { return g.isDirected; }

    vector<int> DFSRecursive(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices)
            throw out_of_range("Vértice inicial inválido");

        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        DFSUtil(startVertex, visited, traversalOrder);
        return traversalOrder;
    }
};