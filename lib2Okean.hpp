// @JrOkean - Joana dos Santos Raposo || 2025
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <limits>
#include <stdexcept>
using namespace std;
typedef long long ll;
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
//Combinatorial&Numerica
template <typename T>
class GeometricAlg{
    public:
    struct point{
       struct Point {
        T x, y,z;
        Point(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    };
    struct Segment {
        Point start;
        Point end;
        Segment(const Point& s, const Point& e) : start(s), end(e) {}
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
    bool isPointOnSegment(const Point& A, const Point& B, const Point& P) {
        // Verifica colinearidade (usando distância do ponto à reta)
        double distToLine = distanceToLine(P, a, b, c); // Supondo que a reta AB é ax + by + c = 0
        const double EPSILON = 1e-9;
        if (distToLine > EPSILON) return false;
        // Verifica se P está entre A e B (coordenadas paramétricas)
        T minX = min(A.x, B.x);
        T maxX = max(A.x, B.x);
        T minY = min(A.y, B.y);
        T maxY = max(A.y, B.y);
        return (P.x >= minX - EPSILON && P.x <= maxX + EPSILON) &&
            (P.y >= minY - EPSILON && P.y <= maxY + EPSILON);
    }
    bool areLinesIntersecting(double a1, double b1, double c1, double a2, double b2, double c2) const {
        const double EPSILON = 1e-9; 
        if ((abs(a1) < EPSILON && abs(b1) < EPSILON) || 
            (abs(a2) < EPSILON && abs(b2) < EPSILON)) {
            throw invalid_argument("Coeficientes 'a' e 'b' não podem ser ambos zero.");
        }
        double det = a1 * b2 - a2 * b1;
        if (abs(det) > EPSILON) {
            return true;
        }
        else {
            bool coincident = ((a1 * c2 - a2 * c1) < EPSILON) && 
                            ((b1 * c2 - b2 * c1) < EPSILON);
            return coincident;
        }
    }
    Point closestPointOnSegment(const Segment& seg, const Point& P) {
        Point A = seg.start;
        Point B = seg.end;
        // Vetor AB e AP
        Point AB = {B.x - A.x, B.y - A.y, B.z - A.z};
        Point AP = {P.x - A.x, P.y - A.y, P.z - A.z};
        // Projeção escalar de AP em AB
        double t = (AP.x * AB.x + AP.y * AB.y + AP.z * AB.z) / 
                (AB.x * AB.x + AB.y * AB.y + AB.z * AB.z);
        // Clamp t entre [0, 1]
        t = max(0.0, min(1.0, t));
        // Retorna o ponto projetado
        return {A.x + t * AB.x, A.y + t * AB.y, A.z + t * AB.z};
    }
    Point convexCombination(const vector<Point>& points, const vector<double>& weights) {
        if (points.size() != weights.size()) {
            throw invalid_argument("Número de pontos e pesos deve ser igual");
        }
        double sumWeights = 0.0;
        for (double w : weights) {
            sumWeights += w;
        }
        const double EPSILON = 1e-6;
        if (abs(sumWeights - 1.0) > EPSILON) {
            throw invalid_argument("Soma dos pesos deve ser 1");
        }
        T x = 0, y = 0, z = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            x += weights[i] * points[i].x;
            y += weights[i] * points[i].y;
            z += weights[i] * points[i].z;
        }
        return {x, y, z};
    }
    bool areSegmentsIntersecting(const Segment& seg1, const Segment& seg2) {
        // Coeficientes das retas suporte (ax + by + c = 0)
        double a1 = seg1.end.y - seg1.start.y;
        double b1 = seg1.start.x - seg1.end.x;
        double c1 = seg1.end.x * seg1.start.y - seg1.start.x * seg1.end.y;
        double a2 = seg2.end.y - seg2.start.y;
        double b2 = seg2.start.x - seg2.end.x;
        double c2 = seg2.end.x * seg2.start.y - seg2.start.x * seg2.end.y;
        // Verifica se as retas suporte se intersectam
        bool linesIntersect = areLinesIntersecting(a1, b1, c1, a2, b2, c2);
        if (!linesIntersect) {
            return false; // Linhas paralelas ou coincidentes sem sobreposição
        }
        // Calcula o ponto de interseção (se existir)
        double det = a1 * b2 - a2 * b1;
        if (abs(det) > 1e-9) {
            Point intersection;
            intersection.x = (b1 * c2 - b2 * c1) / det;
            intersection.y = (a2 * c1 - a1 * c2) / det;
            // Verifica se o ponto está dentro dos dois segmentos
            return isPointOnSegment(seg1.start, seg1.end, intersection) &&
                isPointOnSegment(seg2.start, seg2.end, intersection);
        } else {
            // Linhas coincidentes: verifica se os segmentos se sobrepõem
            return (isPointOnSegment(seg1.start, seg1.end, seg2.start) ||
                    isPointOnSegment(seg1.start, seg1.end, seg2.end) ||
                    isPointOnSegment(seg2.start, seg2.end, seg1.start) ||
                    isPointOnSegment(seg2.start, seg2.end, seg1.end));
        }
    }
    // Função auxiliar para cálculo da orientação (produto vetorial 2D)
    static T cross(const Point& O, const Point& A, const Point& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
    // Algoritmo de Andrew para envoltória convexa 2D (ignora z)
    vector<Point> convexHullAndrew(vector<Point>& points) {
        int n = points.size();
        if (n <= 1) return points;

        // Ordena pontos por x (e y em caso de empate)
        sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });
        vector<Point> hull;
        // Parte inferior da envoltória
        for (int i = 0; i < n; ++i) {
            while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        // Parte superior da envoltória
        int lower_hull_size = hull.size();
        for (int i = n-2; i >= 0; --i) {
            while (hull.size() > lower_hull_size && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        // Remove duplicatas (primeiro e último ponto são iguais)
        if (hull.size() > 1) hull.pop_back();
        return hull;
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
                cout << val << " ";
            }
            cout << "\n";
        }
    }
    // Outras funções úteis:
    int getNumVertices() const { return g.numVertices; }
    bool isDirected() const { return g.isDirected; }
    // BFS para matriz de adjacência
    vector<int> BFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices)
            throw out_of_range("Vértice inicial inválido");

        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(current);
            // Percorre todos os vértices para encontrar vizinhos
            for (int neighbor = 0; neighbor < g.numVertices; ++neighbor) {
                if (g.adjMatrix[current][neighbor] != T() && !visited[neighbor]) { // Se há aresta
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return traversalOrder;
    }
    // DFS Iterativo para matriz de adjacência
    vector<int> DFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices)
            throw out_of_range("Vértice inicial inválido");

        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        stack<int> s;

        s.push(startVertex);
        visited[startVertex] = true;

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            traversalOrder.push_back(current);
            // Empilha os vizinhos em ordem inversa para manter a ordem correta
            for (int neighbor = g.numVertices - 1; neighbor >= 0; --neighbor) {
                if (g.adjMatrix[current][neighbor] != T() && !visited[neighbor]) { // Se há aresta
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        return traversalOrder;
    }
    //#######################
    //####################### SEGUNDA ENTREGA GRAFOS::
    //#######################
    private:
    bool bfsEdmondsKarp(const vector<vector<T>>& residual, int source, int sink, vector<int>& parent) const {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(source);
        parent[source] = -2; 

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < g.numVertices; ++v) {
                if (residual[u][v] > 0 && parent[v] == -1) {
                    parent[v] = u;
                    if (v == sink) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    bool dfsFordFulkerson(const vector<vector<T>>& residual, int u, int sink, vector<int>& parent) const {
        if (u == sink) return true;
        for (int v = 0; v < g.numVertices; ++v) {
            if (residual[u][v] > 0 && parent[v] == -1) {
                parent[v] = u;
                if (dfsFordFulkerson(residual, v, sink, parent)) return true;
                parent[v] = -1; // Backtrack
            }
        }
        return false;
    }

    bool bfsLevelGraph(const vector<vector<T>>& residual, int source, int sink, vector<int>& level) const {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < g.numVertices; ++v) {
                if (residual[u][v] > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[sink] != -1;
    }

    T sendFlow(vector<vector<T>>& residual, int u, int sink, T flow, vector<int>& level) {
        if (u == sink) return flow;

        for (int v = 0; v < g.numVertices; ++v) {
            if (residual[u][v] > 0 && level[v] == level[u] + 1) {
                T currentFlow = min(flow, residual[u][v]);
                T tempFlow = sendFlow(residual, v, sink, currentFlow, level);

                if (tempFlow > 0) {
                    residual[u][v] -= tempFlow;
                    residual[v][u] += tempFlow;
                    return tempFlow;
                }
            }
        }
        return 0;
    }
    public: 
    // Algoritmo de Ford-Fulkerson (DFS)
    T fordFulkerson(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");
        vector<vector<T>> residual = g.adjMatrix;
        T maxFlow = 0;
        vector<int> parent(g.numVertices);

        while (true) {
            fill(parent.begin(), parent.end(), -1);
            parent[source] = -2;

            if (!dfsFordFulkerson(residual, source, sink, parent)) break;

            T pathFlow = numeric_limits<T>::max();
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, residual[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residual[u][v] -= pathFlow;
                residual[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }
        return maxFlow;
    }
    // Algoritmo de Edmonds-Karp (BFS)
    T edmondsKarp(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");

        vector<vector<T>> residual = g.adjMatrix;
        T maxFlow = 0;
        vector<int> parent(g.numVertices);

        while (bfsEdmondsKarp(residual, source, sink, parent)) {
            T pathFlow = numeric_limits<T>::max();
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, residual[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residual[u][v] -= pathFlow;
                residual[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }
        return maxFlow;
    }
    // Algoritmo de Dinic
    T dinic(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");

        vector<vector<T>> residual = g.adjMatrix;
        T maxFlow = 0;
        vector<int> level(g.numVertices);

        while (bfsLevelGraph(residual, source, sink, level)) {
            T flow;
            do {
                flow = sendFlow(residual, source, sink, numeric_limits<T>::max(), level);
                maxFlow += flow;
            } while (flow > 0);
        }
        return maxFlow;
    }
};

template <typename T>
class GraphList {
private:
    struct Graph {
        bool isDirected;
        int numVertices;
        vector<vector<pair<int, T>>> adjList;
    };
    Graph g;
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
            remove_if(neighborsU.begin(), neighborsU.end(),
                           [v](const pair<int, T>& edge) { return edge.first == v; }),
            neighborsU.end()
        );
        if (!g.isDirected) {
            auto& neighborsV = g.adjList[v];
            neighborsV.erase(
                remove_if(neighborsV.begin(), neighborsV.end(),
                               [u](const pair<int, T>& edge) { return edge.first == u; }),
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
    // BFS a partir de um vértice inicial
    vector<int> BFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices) {
            throw out_of_range("Vértice inicial inválido");
        }
        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(current);
            // Visita todos os vizinhos do vértice atual
            for (const auto& edge : g.adjList[current]) {
                int neighbor = edge.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return traversalOrder;
    }
    // DFS Iterativo a partir de um vértice inicial
    vector<int> DFS(int startVertex) const {
        if (startVertex < 0 || startVertex >= g.numVertices) {
            throw out_of_range("Vértice inicial inválido");
        }
        vector<bool> visited(g.numVertices, false);
        vector<int> traversalOrder;
        stack<int> s;
        s.push(startVertex);
        visited[startVertex] = true;
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            traversalOrder.push_back(current);
            // Empilha os vizinhos em ordem inversa para manter a ordem correta
            for (auto it = g.adjList[current].rbegin(); it != g.adjList[current].rend(); ++it) {
                int neighbor = it->first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        return traversalOrder;
    }
    //#######################
    //####################### SEGUNDA ENTREGA GRAFOS::
    //#######################
    private:
    struct ResidualEdge {
        int to;
        T capacity;
        int rev; // Índice da aresta reversa no vetor de adjacência do nó 'to'
        ResidualEdge(int to, T capacity, int rev) : to(to), capacity(capacity), rev(rev) {}
    };

    bool bfsEdmondsKarp(const vector<vector<ResidualEdge>>& residual, int source, int sink, vector<int>& parent) const {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(source);
        parent[source] = -2;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const ResidualEdge& e : residual[u]) {
                if (parent[e.to] == -1 && e.capacity > 0) {
                    parent[e.to] = u;
                    if (e.to == sink) return true;
                    q.push(e.to);
                }
            }
        }
        return false;
    }

    bool dfsFordFulkerson(vector<vector<ResidualEdge>>& residual, int u, int sink, vector<bool>& visited) {
        if (u == sink) return true;
        visited[u] = true;

        for (ResidualEdge& e : residual[u]) {
            if (!visited[e.to] && e.capacity > 0) {
                if (dfsFordFulkerson(residual, e.to, sink, visited)) {
                    e.capacity -= 1; 
                    residual[e.to][e.rev].capacity += 1;
                    return true;
                }
            }
        }
        return false;
    }

    bool bfsLevelGraph(const vector<vector<ResidualEdge>>& residual, int source, int sink, vector<int>& level) const {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const ResidualEdge& e : residual[u]) {
                if (level[e.to] == -1 && e.capacity > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    T sendFlow(vector<vector<ResidualEdge>>& residual, int u, int sink, T flow, vector<int>& level) {
        if (u == sink) return flow;

        for (ResidualEdge& e : residual[u]) {
            if (e.capacity > 0 && level[e.to] == level[u] + 1) {
                T currentFlow = min(flow, e.capacity);
                T tempFlow = sendFlow(residual, e.to, sink, currentFlow, level);

                if (tempFlow > 0) {
                    e.capacity -= tempFlow;
                    residual[e.to][e.rev].capacity += tempFlow;
                    return tempFlow;
                }
            }
        }
        return 0;
    }
    public:
    T fordFulkerson(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");

        // Inicializa o grafo residual
        vector<vector<ResidualEdge>> residual(g.numVertices);
        for (int u = 0; u < g.numVertices; ++u) {
            for (const auto& edge : g.adjList[u]) {
                int v = edge.first;
                T cap = edge.second;
                residual[u].emplace_back(v, cap, residual[v].size());
                residual[v].emplace_back(u, 0, residual[u].size() - 1);
            }
        }

        T maxFlow = 0;
        vector<bool> visited(g.numVertices);

        while (dfsFordFulkerson(residual, source, sink, visited)) {
            fill(visited.begin(), visited.end(), false);
            maxFlow += 1; // Ajuste para exemplo (fluxo unitário)
        }
        return maxFlow;
    }

    // Algoritmo de Edmonds-Karp (BFS)
    T edmondsKarp(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");

        vector<vector<ResidualEdge>> residual(g.numVertices);
        for (int u = 0; u < g.numVertices; ++u) {
            for (const auto& edge : g.adjList[u]) {
                int v = edge.first;
                T cap = edge.second;
                residual[u].emplace_back(v, cap, residual[v].size());
                residual[v].emplace_back(u, 0, residual[u].size() - 1);
            }
        }

        T maxFlow = 0;
        vector<int> parent(g.numVertices);

        while (bfsEdmondsKarp(residual, source, sink, parent)) {
            T pathFlow = numeric_limits<T>::max();
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (ResidualEdge& e : residual[u]) {
                    if (e.to == v) {
                        pathFlow = min(pathFlow, e.capacity);
                        break;
                    }
                }
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (ResidualEdge& e : residual[u]) {
                    if (e.to == v) {
                        e.capacity -= pathFlow;
                        residual[v][e.rev].capacity += pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }
        return maxFlow;
    }

    // Algoritmo de Dinic
    T dinic(int source, int sink) {
        if (source < 0 || source >= g.numVertices || sink < 0 || sink >= g.numVertices)
            throw out_of_range("Vértice inválido");

        vector<vector<ResidualEdge>> residual(g.numVertices);
        for (int u = 0; u < g.numVertices; ++u) {
            for (const auto& edge : g.adjList[u]) {
                int v = edge.first;
                T cap = edge.second;
                residual[u].emplace_back(v, cap, residual[v].size());
                residual[v].emplace_back(u, 0, residual[u].size() - 1);
            }
        }

        T maxFlow = 0;
        vector<int> level(g.numVertices);

        while (bfsLevelGraph(residual, source, sink, level)) {
            T flow;
            do {
                flow = sendFlow(residual, source, sink, numeric_limits<T>::max(), level);
                maxFlow += flow;
            } while (flow > 0);
        }
        return maxFlow;
    }
};

/* ################# Parte da Segunda Entrega ################# */
class Combinatorics {
    private:
    // Memoização: cache de resultados
    static vector<vector<ll>> memo;

    static ll binomialRecursiveMemo(int n, int k) {
        if (k == 0 || k == n) return 1;
        if (memo[n][k] != -1) return memo[n][k];

        memo[n][k] = binomialRecursiveMemo(n - 1, k - 1) + binomialRecursiveMemo(n - 1, k);
        return memo[n][k];
    }

public:
    static ll binomialCoefficientRecursive(int n, int k) {
        if (k < 0 || k > n) return 0;
        // Inicializa a tabela de memoização
        memo.resize(n + 1, vector<ll>(k + 1, -1));
        return binomialRecursiveMemo(n, k);
    }

    static ll binomialCoefficientAnalytic(int n, int k) {
        if (k < 0 || k > n) return 0; // Casos inválidos
        if (k == 0 || k == n) return 1; // Casos base
        // Usa a propriedade C(n, k) = C(n, n - k) para otimizar
        k = min(k, n - k);
        ll result = 1;
        for (int i = 1; i <= k; ++i) {
            result = result * (n - k + i) / i;
        }
        return result;
    }
};

template <typename T>
class NumberTheory {
    private:
    static T extendedEuclid(T a, T b, T& x, T& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        T gcd = extendedEuclid(b, a % b, x, y);
        T temp = x;
        x = y;
        y = temp - (a / b) * y;
        return gcd;
    }
    
    public:
    static bool isPrimeBruteForce(T n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;

        for (T i = 3; i < n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    static bool isPrimeOptimized(T n) {
        if (n <= 1) return false;
        if (n <= 3) return true; // 2 e 3 são primos
        if (n % 2 == 0 || n % 3 == 0) return false;

        // Verifica divisibilidade até sqrt(n), pulando múltiplos de 2 e 3
        for (T i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Inverso modular (retorna -1 se não existir)
    static T modularInverse(T a, T m) {
        if (m <= 0) throw std::invalid_argument("m deve ser positivo");

        T x, y;
        T gcd = extendedEuclid(a, m, x, y);

        if (gcd != 1) {
            throw std::invalid_argument("a e m não são coprimos");
        }

        // Ajusta x para o intervalo [0, m-1]
        x = (x % m + m) % m;
        return x;
    }
};