#include <iostream>
#include <vector>
using namespace std;
/*Seção 1.4*/
class input{
    public:
    //Casos na primeira linha::
    void read_first_line(){
        int TC; scanf("%d", &TC); //ou cin >> 
        while(TC--){
            int a, b; scanf("%d %d", &a, &b);
            printf("%d\n", a+b);
            //faça uma ação continua
        }
    }
    //Quando a condição de parada é 0
    void read_until_zero(){
        int a, b;
        while(scanf("%d %d", &a, &b), (a || b)){ printf("%d\n", a+b);}
    }
    //Quando termina por EOF
    void read_until_EOF(){
        int a, b;
        while (scanf("%d %d", &a, &b) == 2){printf("%d\n", a+b);}
        
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
    //Output apenas entre
        void read_and_output_n(){
        int a, b, c = 0;
        while(scanf("%d %d", &a, &b) != EOF){
            if( c > 0) printf("\n"); 
            printf("CASO %d: %d\n", c++, a+b);};
    }

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

};