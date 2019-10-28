#include <iostream>
#include "assembler.h"

using namespace std;
int test(){
    cout << "this worked" << "\n";
    return 1;
}

    int oppcode_dictionary::get_code(string opp_name_in){
        return opp_name[opp_name_in];
    }
    string oppcode_dictionary::get_opp_name(int code_num){
        if(code_num > 0 & code_num < 22) {
            return opp_name_string[code_num - 1];
        }
        else {
            return "Not valid OPP Code.";
            
        }
    }