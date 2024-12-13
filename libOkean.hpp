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

class substrings_finding{
    public:

    bool _is_match(string subgroup, string goal){
        int magic = subgroup.compare(goal);
        if(magic == 0){
            return true;
        };
        return false;
    };

    vector<int> search_subtring(string whole, string find_it){
        int t_whole, t_find_t;
        t_whole = whole.size(); t_find_t = find_it.size();
        vector<int> v_indices;
        //cout << "HEY YEH::" << t_find_t << ", " << t_whole << endl;

        int indice_s = 0;
        string sub;

        for (int i = 0; i < t_whole; i++){
            sub = whole.substr(i, t_find_t);
            //cout << "entrou:: " << sub << endl;

            if(_is_match(sub, find_it)){
                //cout << "indice:: " << endl;
                v_indices.push_back(i);
            }
        }

        if(v_indices.empty()){
            return {-1};
        } else{
            return v_indices;
        }
    };

    void _response_print(vector<int> results){
        cout << "{";

        for (size_t i = 0; i < results.size(); ++i) {
            cout << results[i];
            if (i < results.size() - 1) {
            cout << ", "; // Adiciona uma vírgula entre os elementos
            }
        }
        cout << "}" << endl;    
    }
};    

class string_analysis{
    public:
    vector<int> anylizeStrings(string T){   
        int digit_count = 0;
        int vowel_count = 0;
        int consonant_count = 0;

        for(char ch : T){
            // Verifica se é um dígito
            if (isdigit(ch)) {
                digit_count++;
            }
            // Verifica se é uma vogal
            else if (isalpha(ch)) { // Verifica se é uma letra
                ch = tolower(ch); // Converte para minúscula para facilitar a comparação
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                    vowel_count++;
                } else {
                    consonant_count++; // Se não for vogal, é consoante
                }
            }
        }
        return {digit_count, vowel_count, consonant_count};
    }

    void _print_results(vector<int> results){
        cout << "Digitos: " << results[0] << endl;
        cout << "Vogais: " << results[1] << endl;
        cout << "Consoantes: " << results[2] << endl;
    }
};

class to_tokens {
    private:
        vector<string> tokens;
        char delim[2] = {' ', ','};
        int delim_count = 2;
        vector<string> sorted_tokens;
        //string str = "I love,and,donuts bullshit";

    public:
        vector<string> _get_tokens(string whole) {

            int start = 0;  
            for (int idx = 0; idx < whole.length(); idx++) {
                char curr = whole[idx];

                for (int j = 0; j < delim_count; j += 1) {
                    if (curr == delim[j]) {
                        string local  = string(whole.data() + start, idx - start);
                        tokens.push_back(local);
                        start = idx + 1;
                        break;
                    }
                }
        }
        
            string local  = string(whole.data() + start, whole.length() - start);
            tokens.push_back(local);
                
            return tokens;
        };

        void _sort_tokens(){

        };

        void _print_results() {
            for (const auto& token : tokens) {
                cout << token << "\n";
            }
        };
};