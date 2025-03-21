// @JrOkean - Joana dos Santos Raposo || 2025
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;
//typedef tuple<
/*Seção 1.4*/
class InputType{
    public:
    //Casos na primeira linha::
    void read_first_line(){
        int TC; cin >> TC; //ou cin >> 
        while(TC--){
            int a, b; cin >> a >> b;
            cout << a+b;
            //faça uma ação continua
        }
    }
    //Quando a condição de parada é 0
    void read_until_zero(){
        int a, b;
        while(cin >> a >> b, (a != 0 || b != 0)){ cout << a+b;}
    }
    //Quando termina por EOF
    void read_until_EOF(){
        int a, b;
        while (cin >> a >> b){cout << a+b;}
    }
    //OR
    void read_until_EOF2(){
        int a, b;
        while (scanf("%d %d", &a, &b) != EOF){printf("%d\n", a+b);}
        
    }
    //Output com blank line
    void read_and_output_n(){
        int a, b, c = 0;
        while(scanf("%d %d", &a, &b) != EOF) printf("CASO %d: %d\n\n", c++, a+b);
    }
    //Output blank apenas entre
    void read_and_output_n2(){
        int a, b, c = 0;
        while(scanf("%d %d", &a, &b) != EOF){
            if( c > 0) printf("\n"); 
            printf("CASO %d: %d\n", c++, a+b);};
    }
    //Input em sequência até EOF + soma dos números
    void read_grown_eof(){
        int k;
        while (scanf("%d, &k") != EOF){
            int ans = 0, v;
            while (k--){scanf("%d", &v); ans+= v; printf("%d\n", ans);}
        }   
    }
    void read_grown_eof2(){
        while(1){
            int ans = 0, v;
            char dummy;
            while (scanf("%d%c", &v, &dummy) != EOF){
                ans += v;
                if(dummy == '\n') break; //test EOLN
            }
            if (feof(stdin)) break;
            printf("%d\n", ans);}
    }
};

class LinearSort{
    //O(n)
    public:
    //faixa limitada, algoritmo estável
    void counting_sort(const vector<int>& A, vector<int>& B, int k) {
        vector<int> C(k + 1, 0); 
        // Passo 1: Contar a ocorrência de cada elemento em A
        for (size_t j = 0; j < A.size(); j++) {
            int indice = A[j];
            C[indice]++;
        }
        // Passo 2: Atualizar o vetor C para armazenar as posições corretas
        for (size_t i = 1; i <= k; i++) {
            C[i] += C[i - 1];
        }
        // Passo 3: Construir o vetor B ordenado
        for (int j = A.size() - 1; j >= 0; j--) {
            int indice = A[j];
            B[C[indice] - 1] = A[j];
            C[indice]--; 
        }
    }
    //input distribuído uniformimente
    //BUCKET SORT
    template <typename T>
    int calcularIndiceDoBalde(T elemento, T min, T max, int numBaldes) {
        return static_cast<int>((elemento - min) * numBaldes / (max - min + 1));
    }
    template <typename T>
    void bucketSort(vector<T>& array, int numBaldes) {
        if (array.empty()) return;
        // Passo 1: Encontrar o valor mínimo e máximo no array
        T min = *min_element(array.begin(), array.end());
        T max = *max_element(array.begin(), array.end());
        // Passo 2: Criar baldes
        vector<vector<T>> baldes(numBaldes);
        // Passo 3: Distribuir os elementos nos baldes
        for (T elemento : array) {
            int indice = calcularIndiceDoBalde(elemento, min, max, numBaldes);
            baldes[indice].push_back(elemento);
        }
        // Passo 4: Ordenar cada balde
        for (auto& balde : baldes) {
            sort(balde.begin(), balde.end());
        }
        // Passo 5: Concatenar os baldes ordenados
        int index = 0;
        for (auto& balde : baldes) {
            for (T elemento : balde) {
                array[index++] = elemento;
            }
        }
    }
    //não-comparativo, int ou strings; é estável
    //RADIX_SORT
    // Função para encontrar o valor máximo no array
    int encontrarMaximo(vector<int>& array) {
        return *max_element(array.begin(), array.end());
    }
    // Função para ordenar os elementos com base no dígito atual
    void countingSort(vector<int>& array, int exp) {
        int n = array.size();
        vector<int> output(n); // Array de saída
        vector<int> count(10, 0); // Contador para cada dígito (0 a 9)
        // Contar a ocorrência de cada dígito
        for (int i = 0; i < n; i++) {
            int indice = (array[i] / exp) % 10;
            count[indice]++;
        }
        // Atualizar o contador para armazenar a posição correta de cada dígito
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        // Construir o array de saída
        for (int i = n - 1; i >= 0; i--) {
            int indice = (array[i] / exp) % 10;
            output[count[indice] - 1] = array[i];
            count[indice]--;
        }
        // Copiar o array de saída de volta para o array original
        for (int i = 0; i < n; i++) {
            array[i] = output[i];
        }
    }
    // Função Radix Sort
    void radix_sort(vector<int>& array) {
        int max = *max_element(array.begin(), array.end());
        vector<int> B(array.size());
        // Processar cada dígito (unidades, dezenas, centenas, etc.)
        for (int exp = 1; max / exp > 0; exp *= 10) {
            counting_sort(array, B, 9); // Usando Counting Sort para cada dígito
            array = B; // Atualiza o array original
        }
    }
};

class DivedAconquer{
    public:
    //p. calcular exponenciação de um número
    long long binary_exponentiation(long long a, long long n) {
        if (n == 0) {
            return 1; // Qualquer número elevado a 0 é 1
        }
        // Chamada recursiva para calcular a^(n/2)
        long long result = binary_exponentiation(a, n / 2);
        // Se n for par, retorna (a^(n/2))^2
        if (n % 2 == 0) {
            return result * result;
        }
        // Se n for ímpar, retorna a * (a^(n/2))^2
        else {
            return a * result * result;
        }
    }
    //mergesort, ordenação por divisão em arrays menores
    void merge(vector<int>& array, int left, int mid, int right) {
        // Tamanho das duas metades
        int n1 = mid - left + 1; // Tamanho da metade esquerda
        int n2 = right - mid;    // Tamanho da metade direita
        vector<int> L(n1), R(n2);
        // Copia os dados para os vetores temporários L e R
        for (int i = 0; i < n1; i++) {
            L[i] = array[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = array[mid + 1 + j];
        }
        // Combina as duas metades ordenadas
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
            }
            k++;
        }
        // Copia os elementos restantes de L (se houver)
        while (i < n1) {
            array[k] = L[i];
            i++;
            k++;
        }
        // Copia os elementos restantes de R (se houver)
        while (j < n2) {
            array[k] = R[j];
            j++;
            k++;
        }
    }
    // Função principal do Merge Sort
    void merge_sort(vector<int>& array, int left, int right) {
        if (left < right) {
            // Encontra o ponto médio para dividir o array
            int mid = left + (right - left) / 2;
            // Ordena a primeira metade
            merge_sort(array, left, mid);
            // Ordena a segunda metade
            merge_sort(array, mid + 1, right);
            // Combina as duas metades ordenadas
            merge(array, left, mid, right);
        }
    }
    // Função merge_wInversion: combina as metades e conta as inversões
    long long merge_wInversion(vector<int>& array, int left, int mid, int right) {
        int n1 = mid - left + 1; // Tamanho da metade esquerda
        int n2 = right - mid;    // Tamanho da metade direita
        vector<int> L(n1), R(n2);
        // Copia os dados para os vetores temporários L e R
        for (int i = 0; i < n1; i++) {
            L[i] = array[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = array[mid + 1 + j];
        }
        // Combina as duas metades ordenadas e conta as inversões
        int i = 0, j = 0, k = left;
        long long inversions = 0; // Contador de inversões
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
                inversions += (n1 - i); // Conta as inversões cruzadas
            }
            k++;
        }
        // Copia os elementos restantes de L (se houver)
        while (i < n1) {
            array[k] = L[i];
            i++;
            k++;
        }
        // Copia os elementos restantes de R (se houver)
        while (j < n2) {
            array[k] = R[j];
            j++;
            k++;
        }
        return inversions; // Retorna o número de inversões contadas
    }
    // Função principal do Merge Sort com contagem de inversões
    long long merge_sort_wInversion(vector<int>& array, int left, int right) {
        long long inversions = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            // Conta as inversões na metade esquerda
            inversions += merge_sort_wInversion(array, left, mid);
            // Conta as inversões na metade direita
            inversions += merge_sort_wInversion(array, mid + 1, right);
            // Combina as duas metades e conta as inversões cruzadas
            inversions += merge_wInversion(array, left, mid, right);
        }
        return inversions; }
    // Função inversion_index
    void inversion_index(vector<int>& array) {
        long long inversions = merge_sort_wInversion(array, 0, array.size() - 1);
    }
    // LCP
    string longest_common_prefix(vector<string>& strs) {
        if (strs.empty()) return ""; // Se não houver strings, retorna vazio
        // O prefixo comum não pode ser maior que a menor string
        int min_length = strs[0].length();
        for (const string& s : strs) {
            if (s.length() < min_length) {
                min_length = s.length();
            }
        }
        string prefix = ""; // Inicializa o prefixo comum
        for (int i = 0; i < min_length; i++) {
            char current_char = strs[0][i]; // Pega o caractere atual da primeira string
            // Verifica se o caractere atual é o mesmo em todas as strings
            for (const string& s : strs) {
                if (s[i] != current_char) {
                    return prefix; // Se não for, retorna o prefixo atual
                }
            }
            prefix += current_char; // Adiciona o caractere ao prefixo comum
        }
        return prefix; // Retorna o prefixo comum mais longo
    }
};

template <typename T>
class GreedyAlg{
    private:
    //Mochila Fracionário
    struct item{
        T value;
        T weight;
        T ratio;
        item(T v, T w) : value(v), weight(w), ratio(v/w) {}
    }
    public:
    //Mochila Fracionárria
    bool compareItems(const Item &a, const Item &b){
        return a.ratio > b.ration;
    }
    double fracKnapsack(vector<Item> &items, double capacity){
        sort(items.begin(), items.end(), compareItems);
        double totalValue = 0.0;
        for (const auto &item : item){
            if(capacity == 0){
                break;
            } 
        }
        if(item.weight <= capacity){
            totalValue += item.value;
            capacity - = item.weight;
        } else{
            double fraction = capacity /item.weight;
            totalValue += item.value * fraction;
            capacity = 0;
        }
        return totalValue;
    }
    //Problema do troco
    vector<int> change_problem(int change, vector<int> coins) {
        vector<int> result;
        sort(coins.begin(), coins.end(), greater<int>());
        for (int coin : coins) {
            while (change >= coin) {
                result.push_back(coin);
                change -= coin;
            }
        }
        if (change != 0) {
            cout << "infinity" << endl;
        }
        return result;
    }
    //Escalonamento de tarefas
    int activitySelection(vector<int> &start, vector<int> &end){
        int ans = 0;
        priority_queue<pair<int, int>>, vector<pair<int, int>>, greater<pair<int, int>> >> p;
        for (size_t i = 0; i < start.size(); i++){
            p.push(make_pair(end[i], start[i]))
        }
        int finish = -1
        while (!p.empty()){
            pair<int, int> activity = p.top();
            p.pop();
            if (activity.second > finish){
                finish = activity.first;
                ans++;
            }
        }
    }
    return ans;
};

template <typename T>
class GeometricAlg{
    public:
    struct point{
       struct Point {
        T x, y;
        T z = 0; 
        Point(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    };
    double distanceBetweenTwo(const Point &p1, const Point &p2) {
        T dx = p1.x - p2.x;
        T dy = p1.y - p2.y;
        T dz = p1.z - p2.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    double slopeBetweenTwo(const Point &p1, const Point &p2) {
        if (p1.x == p2.x) {
            throw invalid_argument("infinity");
        }
        return static_cast<double>(p1.y - p2.y) / (p1.x - p2.x);
    }
    double distanceToLine(const Point &p, double a, double b, double c) {
        if (a == 0 && b == 0) {
            throw invalid_argument("error");
        }
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
};

};

template <typename T> 
class GraphMatrix{
    private:
    struct graph{
        
    }

};

template <typename T> 
class GraphList{
    
};

template <typename T>
class Graphs{
    private:
    struct graph{
        int numVertex;
        vector<vector<T>> adjMatrix;
        vector<vector<T>> adjList;
        vector<vector<T>> residual;
        bool useMatrix;
        bool useList;
        //Construtor de inicialização
        graph(int n, bool useMatrix = false, bool useList = false) :
        numVertex(n), useMatrix(useMatrix), useList(useList){
            if(useMatrix){
                adjMatrix = vector<vector<T>>(n, vector<T>(n, T())); 
                residual= vector<vector<T>>(n, vector<T>(n, T()));
            } 
            if (useList){
                adjList= vector<vector<T>>(n);
            }   
        }
    };
    graph graph;
    //declaração para uso dos membros privados
    void DFS_ListRecursive(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << "Visitando: " << u << endl;
        for (int v : graph.adjList[u]) {
            if (!visited[v]) {
                DFS_ListRecursive(v, visited);
            }
        }
    }
    void DFS_MatrixRecursive(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << "Visitando: " << u << endl;
        for (int v = 0; v < graph.numVertex; v++) {
            if (graph.adjMatrix[u][v] && !visited[v]) {
                DFS_MatrixRecursive(v, visited);
            }
        }
    }
    public: 
    Graphs(int n, bool useMatrix = false, bool useList = false) :
    graph(n, useMatrix, useList){}
    void addUndirectEdge(int v1, int v2, T weight = T(1)){
        if(graph.useMatrix){
            graph.adjMatrix[v1][v2] = weight;
            graph.adjMatrix[v2][v1] = weight;
        }
        if(graph.useList){
            graph.adjList[v1].push_back(v2);
            graph.adjList[v2].push_back(v1);           
        } 
    }
    void addDirecEdge(int v1, int v2, T weight = T(1)){
        if(graph.useMatrix){
            graph.adjMatrix[v1][v2] = weight;
        }
        if(graph.useList){
            graph.adjList[v1].push_back(v2);            
        } 
    }
    bool hasEdgeList(int v1, int v2) const {
        if (graph.useList && v1 >= 0 && v1 < graph.numVertex && v2 >= 0 && v2 < graph.numVertex) {
            for (T neighbor : graph.adjList[v1]) {
                if (neighbor == v2) {
                    return true;
                }
            }
            return false;
        }
        return false;
    }
    void printAdjacencyMatrix() const {
        if (graph.useMatrix) {
            for (int i = 0; i < graph.numVertex; i++) {
                for (int j = 0; j < graph.numVertex; j++) {
                    cout << graph.adjMatrix[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            cerr << "Erro: Matriz de adjacência não inicializada!" << endl;
        }
    }
    void printAdjacencyList() const {
        if (graph.useList) {
            for (int i = 0; i < graph.numVertex; i++) {
                cout << "Vértice " << i << ": ";
                for (T neighbor : graph.adjList[i]) {
                    cout << neighbor << " ";
                }
                cout << endl;
            }
        } else {
            cerr << "Erro: Lista de adjacência não inicializada!" << endl;
        }
    }
    //BFS : caminho mais curto, conexidade, componetes conexos, caminho mínimo ou área de influência
    //quando o grafo for esparso
    void BFS_list(int start){
        int n = graph.numVertex;
        vector<bool> visited(n, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            cout << "Visitando: " << u << endl;
            for (int v : graph.adjList[u]){
                if (!visited[v]){
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    //quando o grafo for denso
    void BFS_matrix(int start){
        int n = graph.numVertex;
        vector<bool> visited(n, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            cout << "Visitando: " << u << endl;
            for (int v = 0; v < n; v++){
                if (graph.adjMatrix[u][v] && !visited[v]){
                    visited[v] = true;
                    q.push(v);
                }
            }        
        }
    }
    // DFS : conexidade, componentes conexos, ciclos, labirintos ou árvores
    void DFS_list(int start){
        vector<bool> visited(graph.numVertex, false);
        DFS_ListRecursive(start, visited);
    } 
    void DFS_Matrix(int start){
        vector<bool> visited(graph.numVertex, false);
        DFS_MatrixRecursive(start, visited);
    } 
    
/* ################# Parte da Segunda Entrega ################# */

//Ford-Fulkerson-fluxo máximo
    bool findAugmentingPathDFS(int s, int t, vector<int>& parent, vector<vector<T>>& residualGraph) {
        int n = graph.numVertex;
        vector<bool> visited(n, false);
        stack<int> stack;
        stack.push(s);
        visited[s] = true;
        parent[s] = -1;
        while (!stack.empty()) {
            int u = stack.top();
            stack.pop();
            for (int v = 0; v < n; v++) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    stack.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == t) {
                        return true; // Caminho aumentante encontrado
                    }
                }
            }
        }
        return false; // Não há caminho aumentante
    }
    // Método Ford-Fulkerson
    T EdmondsKarp(int s, int t) {
        if (!graph.useMatrix) {
            cerr << "Erro: O método requer a matriz de adjacência!" << endl;
            return T();
        }
        int n = graph.numVertex;
        graph.residualMatrix = graph.adjMatrix; // Usa o membro residualMatrix
        vector<int> parent(n);
        T maxFlow = 0;
        while (findAugmentingPath(s, t, parent, graph.residualMatrix)) {
            T pathFlow = numeric_limits<T>::max();
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, graph.residualMatrix[u][v]);
            }
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                graph.residualMatrix[u][v] -= pathFlow;
                graph.residualMatrix[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
    // Método Edmonds-Karp (Ford-Fulkerson com BFS)
    bool findAugmentingPathBFS(int s, int t, vector<int>& parent, vector<vector<T>>& residualGraph) {
        int n = graph.numVertex;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == t) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    T EdmondsKarp(int s, int t) {
        if (!graph.useMatrix) {
            cerr << "Erro: O método requer a matriz de adjacência!" << endl;
            return T();
        }

        int n = graph.numVertex;
        vector<vector<T>> residualGraph = graph.adjMatrix;
        vector<int> parent(n);
        T maxFlow = 0;
        while (findAugmentingPath(s, t, parent, residualGraph)) {
            T pathFlow = numeric_limits<T>::max();
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, residualGraph[u][v]);
            }
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
};

class combinatorics{

};

class numeric_theory{

};