/* Compile with -I(name path for `libOkean.hpp`) for work
*/
#include <libOkean.hpp>

class Substrings_finding{
    public:
    void something(){
        return;
    }
};

int main() {
    //Para lidar com os inputs
    Read_input dados_input;
    vector<string> lines;
    period_problem p;

    //Testando se o código está rodando
    cout << "### Hello, you new here?" <<endl;
   
    //##periods problem resolution #1
    /*dados_input._get_Finput("files/periods.txt");
    lines = dados_input.getDados();
    int size_Ls = lines.size();

    int number = 0;
    for (size_t line = 0; line < size_Ls; line++){
        int size_l = lines[line].size();
        string temp = lines[line];
        cout << "BUSTED::" << lines[line] << endl;
        for (size_t c = 0; c < size_l; c++){
            char some = temp[c];
            cout << "TRUTRUE::" << some << endl;
            bool temp_response = p.if_dot(some);
            if(temp_response == true){
                number = p.count_dots(temp, size_l);
            } else {
                break;
            }          
        }        
    }*/

    //##periods problem resolution || FINAL
    p._get_FinputwStopDot("files/periods.txt");
    vector<string> data_period_problem = p.getDados();
    /* TESTEfor (size_t i = 0; i < data_period_problem.size(); i++){
        cout << "TACA A MÃE:: " << data_period_problem[i] <<endl;
    }*/
    

    p._sum_Strings(data_period_problem);

    //cout << number << endl;
    cout << "FINISHED ###" << endl;
}