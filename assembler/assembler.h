#include <iostream>
#include <string>
#include <map>

#define NUM_OPPS1 21

using namespace std;
int test();

class assembler_mem {
    public:
    int     location = -1;
    bool    byte_transfer = false;
    bool    is_instruction = false;
    int     opp_code;
    int     arg1;
    string  arg1_string;
    bool    arg1_is_label;
    int     arg2;
    string  arg2_string;
    bool    arg2_is_label;
};

class oppcode_dictionary {
    public:
    map<string, int> opp_name;
    string  opp_name_string[NUM_OPPS1];
    char    op1_type[NUM_OPPS1];
    char    op2_type[NUM_OPPS1];
    void add(string name_in, int code_num, char op1_type_in,char op2_type_in){
        opp_name[name_in] = code_num;
        opp_name_string[code_num - 1] = name_in;
        op1_type[code_num - 1] = op1_type_in;
        op2_type[code_num - 1] = op2_type_in;
    }
    int get_code(string opp_name_in){
        return opp_name[opp_name_in];
    }
    string get_opp_name(int code_num){
        if(code_num > 0 & code_num < 22) {
            return opp_name_string[code_num - 1];
        }
        else {
            return "Not valid OPP Code.";
            
        }
    }
};