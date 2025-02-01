#include <iostream>
#include <vector>
using namespace std;
/*Seção 1.4*/
class inputType{
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
    void read_until_EOF(){
        int a, b;
        while (scanf("%d %d", &a, &b) != EOF){printf("%d\n", a+b);}
        
    }
    //Output com blank line
    void read_and_output_n(){
        int a, b, c = 0;
        while(scanf("%d %d", &a, &b) != EOF) printf("CASO %d: %d\n\n", c++, a+b);
    }
    //Output blank apenas entre
    void read_and_output_n(){
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

class linearSort{
        public:

        void couting_sort(){
            
        }

        void bucket_sort(){

        }

        void radix_sort(){

        }

};

class divedAconquer{
        public:

        void binary_exponantiation(){

        }

        void merge_sort(){

        }

        void inversion_index(){

        }

        void longest_commom_prefix(){

        }

};

class greedyAlg{
};

class geometricAlg{
};

    /** Exemplos clássicos de algoritmo Guloso: mochila fracionária, problema do troco, e escalonamento de tarefas
        * Fonte com estrutura de dados e funções geométricas tratadas no seminário:
    - Ponto, função da distância entre dois pontos, distância entre ponto e reta, área da seção transversal, etc.*/
