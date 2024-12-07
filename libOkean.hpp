/*Copyright (C) @JrOkean #Joana dos Santos Raposo
    e-mail contato: amarelaxx@gmail.com 
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std; 

//Classe para lidar com inputs em files e em "linha" de comando.
class Read_input{
    private: 
        int number_lines_input;
        vector<string> dados;
        ifstream myfile;

    public:
        void _get_Input() {
            cin >> number_lines_input;
            cin.ignore(); // limpa o buffer após ler o número inteiro

            for (int i = 0; i < number_lines_input; i++) {
                string line;
                getline(cin, line);
                dados.push_back(line); // adiciona cada linha ao vetor
            };
        };

        void _get_Finput(string file_name) {
            myfile.open(file_name);
            if (!myfile.is_open()) {
                cerr << "Erro ao abrir o arquivo: " << file_name << endl;
                return;
            }
    
            string line;
            while (getline(myfile, line)) {
                cout << line << endl;
                dados.push_back(line); 
            }
            myfile.close();
        }

        // Forma de acessar os private dados
        vector<string> getDados() const {
            return dados;
        }
};

class period_problem{
    private: 
        ifstream myfile;
        vector<string> lines;

    public:
    string T;
 
    //verificar se o começo da line é uma dot
    bool if_dot(char any){
        if (any == '.'){
            return true;
        };
        return false;
    };

    int count_dots(string whole, int size){
        int count = 0;
        for (size_t i = 0; i < size; i++){
            if(whole[i] == '.'){
                count += 1;
            }
        }
        return count;
    };
    

    void _get_FinputwStopDot(string file_name) {
        myfile.open(file_name);
            if (!myfile.is_open()) {
                cerr << "Erro ao abrir o arquivo: " << file_name << endl;
                return;
            }
    
            string line;
            while(true){
                //grab the line
                getline(myfile, line);
                //look if start with a dot, if not, is not of my business 
                bool temp_response = if_dot(line[0]);
                lines.push_back(line); //add in the vector for later cocatanete
                //look after the amount of dots
                if(temp_response == true){
                    int number = count_dots(line, line.size());
                    if(number == 7){
                        break;
                    }
                } else{
                    continue;
                }
            }
            myfile.close();
    }

    void _sum_Strings(vector<string> finish_line){
        string long_string;
        for (size_t i = 0; i < finish_line.size(); i++){
            long_string += finish_line[i] + " ";
        }
        if (!long_string.empty()) {
            long_string.pop_back(); // Remove o último espaço
        }
        cout << "PLIM:: " << long_string << endl; 
    }

    vector<string> getDados() const {
            return lines;
        }
};

