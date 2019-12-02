#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <bits/stdc++.h> //
#include <vector> 
#include <regex>
#include <map> //map table
#include <cctype> //testing characters

// #include "assembler/assembler.h" //may want to use structure file

// Static items
using namespace std;
#define MEM_SIZE 400
string REGISTER_LIST[] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12"};
#define NUM_OF_REG 13
#define NUM_OPPS 30
bool debug_on = true;

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
    string  opp_name_string[NUM_OPPS];
    string  dual_opp_name_string[NUM_OPPS];
    char    op1_type[NUM_OPPS];
    char    op2_type[NUM_OPPS];
    bool    dual_opp[NUM_OPPS];
    int     dual_opp_int[NUM_OPPS];
    bool    register_convert[NUM_OPPS];
    void add(string name_in, int code_num, char op1_type_in,char op2_type_in,bool dual_opp_in){
        opp_name[name_in] = code_num;
        opp_name_string[code_num - 1] = name_in;
        op1_type[code_num - 1] = op1_type_in;
        op2_type[code_num - 1] = op2_type_in;
        dual_opp[code_num - 1] = dual_opp_in;
    }

    int get_code(string opp_name_in){
        return opp_name[opp_name_in];
    }
    string get_opp_name(int code_num){
        if(code_num > 0 & code_num < 22) {
            return opp_name_string[code_num - 1];
        }
        else if(code_num >= 22 & code_num < 25){
            return dual_opp_name_string[code_num - 1];
        }
        else {
            return "Not valid OPP Code.";
            
        }
    }
    void add_dual_opp(int code_num_in, int convert_code, bool convert_on_registers, string opp_name_string){
        dual_opp_int[code_num_in - 1] = convert_code;
        register_convert[code_num_in - 1] = convert_on_registers;
        dual_opp_name_string[convert_code - 1] = opp_name_string;
    }
    bool is_dual_opp(int code_num){
        return dual_opp[code_num - 1];
    }
    void convert_dual_opp(int &code_num_in, bool convert_on_registers){
        if (register_convert[code_num_in - 1] == convert_on_registers){
            if(debug_on) cout << "I converted " << code_num_in << " " << dual_opp_int[code_num_in - 1] << endl; //debug
            code_num_in = dual_opp_int[code_num_in - 1];
        }
    }
};

// Assembler items
assembler_mem current_assebler_memory[MEM_SIZE];
oppcode_dictionary OPPS_DICTIONARY;
bool found_first_opp = false;
int first_opp_location = 0;
int last_opp_location;

class my_assembly_VM {
    public:
    // VM Items
    int     VM_REGISTERS[NUM_OF_REG];
    char     VM_MEMORY[MEM_SIZE*12];

    
    void initialize(){
        for(int i = 0; i < NUM_OF_REG; i++){
            VM_REGISTERS[i] = 0;
        }
        for(int i = 0; i < MEM_SIZE*12; i++){
            VM_MEMORY[i] = 0;
        }
    }
    my_assembly_VM(){ //constructor
        initialize();
    }
    // int grab_memory(int offset, int location){
    //     char temp_char = *((char*)(VM_MEMORY+offset)+location);
    //     int temp_int = temp_char;
    //     return temp_int;
    // }

    void run(int program_start_location, int program_end_location){
        bool run = true;
        int current_operation;
        int current_arg1;
        int current_arg2;
        VM_REGISTERS[8] = program_start_location;
        VM_REGISTERS[9] = program_end_location;
        VM_REGISTERS[10] = ((MEM_SIZE)*12)-1;
        VM_REGISTERS[12] = ((MEM_SIZE)*12)-1;
        // R8 is the PC
        // R9 is the SL (stack Limit)
        // R10 is the SP (stack Pointer)
        // R11 is the FP (frame Pointer) 
        // R12 is the SB (Stack Base)
        
        while (run){
            //stack overflow test
            if (VM_REGISTERS[10] <= VM_REGISTERS[9]+32) cout << "STACK OVERFLOW";
            if (VM_REGISTERS[10] > VM_REGISTERS[12]) cout << "STACK UNDERFLOW";
            current_operation = *(int*)(VM_MEMORY+(VM_REGISTERS[8]));
            current_arg1 = *(int*)(VM_MEMORY+(VM_REGISTERS[8]+4));
            current_arg2 = *(int*)(VM_MEMORY+(VM_REGISTERS[8]+8));
            if(debug_on) cout << OPPS_DICTIONARY.get_opp_name(current_operation) << " ARG 1: (" << current_arg1 << ") ARG 2: (" << current_arg2 << ")" << endl;

            VM_REGISTERS[8]+=12;
            switch (current_operation){
                case 1: { //JMP
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    VM_REGISTERS[8] = current_arg2; //base memory address and offset (label)
                }
                break;
                case 2: { //JMR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    VM_REGISTERS[8] = VM_REGISTERS[current_arg2];
                }
                break;
                case 3: { //BNZ
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    if (VM_REGISTERS[current_arg1] != 0){
                        VM_REGISTERS[8] = current_arg2;
                    }
                }
                break;
                case 4: { //BGT
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    if (VM_REGISTERS[current_arg1] > 0){
                        VM_REGISTERS[8] = current_arg2;
                    }
                }
                break;
                case 5: { //BLT
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    if (VM_REGISTERS[current_arg1] < 0){
                        VM_REGISTERS[8] = current_arg2;
                    }
                }
                break;
                case 6: { //BRZ
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    if (VM_REGISTERS[current_arg1] == 0){
                        VM_REGISTERS[8] = current_arg2;
                    }
                }
                break;
                case 7: { //MOV
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = VM_REGISTERS[current_arg2];
                }
                break;
                case 8: { //LDA
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    VM_REGISTERS[current_arg1] = current_arg2;
                }
                break;
                case 9: { //STR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    *(int*)(VM_MEMORY+current_arg2) = VM_REGISTERS[current_arg1];
                }
                break;
                case 10: { //LDR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = *(int*)(VM_MEMORY+current_arg2);
                }
                break;
                case 11: { //STB
                    //cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    (VM_MEMORY[current_arg2]) = 0;
                    (VM_MEMORY[current_arg2]) = *(char*)(VM_REGISTERS+current_arg1);
                }
                break;
                case 12: { //LDB
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = 0;
                    *(char*)(VM_REGISTERS+current_arg1) = (VM_MEMORY[current_arg2]);
                }
                break;
                case 13: { //ADD
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    // if(debug_on) cout << "regD: " << VM_REGISTERS[current_operation[1]] << "regS: " << VM_REGISTERS[current_operation[2]] << endl;
                    int temp_int = VM_REGISTERS[current_arg1] + VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 14: { //ADI
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    VM_REGISTERS[current_arg1] += current_arg2;
                }
                break;
                case 15: { //SUB
                    int temp_int = VM_REGISTERS[current_arg1] - VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 16: { //MUL
                    int temp_int = VM_REGISTERS[current_arg1] * VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 17: { //DIV
                    int temp_int = VM_REGISTERS[current_arg1] / VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 18: { //AND
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    int temp_int = VM_REGISTERS[current_arg1] && VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 19: { //OR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    int temp_int = VM_REGISTERS[current_arg1] || VM_REGISTERS[current_arg2];
                    VM_REGISTERS[current_arg1] = temp_int;
                }
                break;
                case 20: { //CMP
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    if(VM_REGISTERS[current_arg1] == VM_REGISTERS[current_arg2]){
                        VM_REGISTERS[current_arg1] = 0;
                    }
                    else if(VM_REGISTERS[current_arg1] > VM_REGISTERS[current_arg2]){
                        VM_REGISTERS[current_arg1] = 1;
                    }
                    else {
                        VM_REGISTERS[current_arg1] = -1;
                    }
                }
                break;
                case 21: { //TRP
                    switch (current_arg2) {
                        case 0: run = false;
                        break;
                        case 1: {
                            cout << VM_REGISTERS[3];
                        }
                        break;
                        case 2:  {
                            int temp_int;
                            cin >> temp_int;
                            if(debug_on) cout << "I recieved: " << temp_int << endl;
                            VM_REGISTERS[3] = temp_int;
                        }
                        break;
                        case 3: {
                            // int* temp_int;
                            // *temp_int = VM_REGISTERS[3];
                            // VM_REGISTERS[3] = 'a';
                            char temp_char = *(char*)(VM_REGISTERS+3);
                            cout << temp_char;
                        }
                        break;
                        case 4: {
                            char temp_char = getchar();
                            if(debug_on) cout << "I recieved: " << temp_char << endl;
                            *(char*)(VM_REGISTERS+3) = temp_char;
                        }
                        break;
                        case 99: {
                            cout << " " << endl;
                            if(debug_on) cout << "Break" << endl;
                        }
                        break;
                        default: 
                        if(debug_on) cout << "Debud: I ran" << endl;
                        else run = false;
                        break;
                    }
                    
                }
                break;
                case 22: { //STR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    *(int*)(VM_MEMORY+(VM_REGISTERS[current_arg2])) = VM_REGISTERS[current_arg1];
                }
                break;
                case 23: { //LDR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = *(int*)(VM_MEMORY+(VM_REGISTERS[current_arg2]));
                }
                break;
                case 24: { //STB
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                    VM_MEMORY[VM_REGISTERS[current_arg2]] = *(char*)(VM_REGISTERS+current_arg1);
                }
                break;
                case 25: { //LDB
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = 0;
                    *(char*)(VM_REGISTERS+current_arg1) = VM_MEMORY[VM_REGISTERS[current_arg2]];
                }
                break;
                case 26: { //RUN
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 27: { //END
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 28: { //BLK
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 29: { //LCK
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 30: { //ULK
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                default: {
                    cout << "ERROR not an oppcode at memory location: (" << VM_REGISTERS[8]-12 << ") OPP Code dump: " << + current_operation <<endl;
                }
                break;
            }
        }
    }
};




void initialize(){
    // initalize opps
    OPPS_DICTIONARY.add("JMP",1,'L',' ',false);
    OPPS_DICTIONARY.add("JMR",2,'S',' ',false);
    OPPS_DICTIONARY.add("BNZ",3,'S','L',false);
    OPPS_DICTIONARY.add("BGT",4,'S','L',false);
    OPPS_DICTIONARY.add("BLT",5,'S','L',false);
    OPPS_DICTIONARY.add("BRZ",6,'S','L',false);
    OPPS_DICTIONARY.add("MOV",7,'D','S',false);
    OPPS_DICTIONARY.add("LDA",8,'D','L',false);
    OPPS_DICTIONARY.add("STR",9,'S','L',true);
    OPPS_DICTIONARY.add("LDR",10,'D','L',true);
    OPPS_DICTIONARY.add("STB",11,'S','L',true);
    OPPS_DICTIONARY.add("LDB",12,'D','L',true);
    OPPS_DICTIONARY.add("ADD",13,'D','S',false);
    OPPS_DICTIONARY.add("ADI",14,'D','I',false);
    OPPS_DICTIONARY.add("SUB",15,'D','S',false);
    OPPS_DICTIONARY.add("MUL",16,'D','S',false);
    OPPS_DICTIONARY.add("DIV",17,'D','S',false);
    OPPS_DICTIONARY.add("AND",18,'D','S',false);
    OPPS_DICTIONARY.add("OR",19,'D','S',false);
    OPPS_DICTIONARY.add("CMP",20,'D','S',false);
    OPPS_DICTIONARY.add("TRP",21,'I',' ',false);
    OPPS_DICTIONARY.add("RUN",26,'D','L',false);
    OPPS_DICTIONARY.add("END",27,' ',' ',false);
    OPPS_DICTIONARY.add("BLK",28,' ',' ',false);
    OPPS_DICTIONARY.add("LCK",29,'L',' ',false);
    OPPS_DICTIONARY.add("ULK",30,'L',' ',false);
    // list dual defined opp codes
    OPPS_DICTIONARY.add_dual_opp(9,22,true, "STR(INDIRECT)"); // STR
    OPPS_DICTIONARY.add_dual_opp(10,23,true, "LDR(INDIRECT)"); // LDR
    OPPS_DICTIONARY.add_dual_opp(11,24,true, "STB(INDIRECT)"); // STB
    OPPS_DICTIONARY.add_dual_opp(12,25,true, "LDB(INDIRECT)"); // LDB
}

// Label map object
map<string, int> labels;
int replace_label(string label_in) { 
    if (labels.find(label_in) == labels.end()){
        if(debug_on) cout << "DEBUG: No Label found for: " << label_in << endl;
        return -1;
    }
    else {
        return labels[label_in];
    }
}

void my_assembler_label_replace(){
    for (int i = 0; i < MEM_SIZE; i++) {
        if (current_assebler_memory[i].arg1_is_label){
            current_assebler_memory[i].arg1 = replace_label(current_assebler_memory[i].arg1_string);
        }
        if (current_assebler_memory[i].arg2_is_label){
            current_assebler_memory[i].arg2 = replace_label(current_assebler_memory[i].arg2_string);
        }
    }
}
void add_label(string key_in, int location){
    if (labels.find(key_in) != labels.end()){
        if(debug_on) cout << "DEBUG: Duplicate label found" << endl;
    }
    else {
        labels[key_in] = location;
    }
    // cout << endl << key_in << " has item " << labels[key_in] << endl; //DEBUG
}
int is_label(string key_in, int location){
    bool is_label = true;
    int location_return = 0;
    if(isdigit(key_in[0]) | key_in[0] == '-' | key_in[0] == '+'){
        is_label = false;
        location_return = stoi(key_in);
    }
    for (int i = 0; i < NUM_OF_REG; i++) // Check if item is a register
    {
        if(REGISTER_LIST[i] == key_in){ 
            if(debug_on) cout << "reg: ";
            location_return = stoi(key_in.substr(1,key_in.length()-1));
            if(debug_on) cout << " : " << location_return << " ";
            is_label = false;
        }
    }
    if (is_label){
        if(debug_on) cout << "label: ";
        location_return = -2; // code for label
    }
    return location_return;
}
void my_assembler(string instruction_in, int &location,int &count){
    smatch m;
    regex gen_opp_serach ("(\\w+)*? ?([A-Z]{2,3}) (R[0-9][0-9]?)? *(R[0-9][0-9]?|[-]?\\w+)");   // matches words beginning by "sub"
    regex label_search ("(\\w+)? *.(INT|BYT) *[']?([-]?\\w+)[']?");
    regex mutext_search ("(\\w+)*? *(LCK|ULK) *(\\w*)");
    regex end_blk_search ("(\\w+)*? *(END|BLK)");


    if(std::regex_search(instruction_in,m,label_search)){
        // for (auto x:m) std::cout << x << endl;
        if (m[0] != ""){
            if(debug_on) cout << "Found MATCH: (";
            if(debug_on) cout << m[0] << ")"; //full matched string
            current_assebler_memory[location].location = count;
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],count);
        }
        if (m[2] != ""){
            if(debug_on) cout << " Label Identifier: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            if (m[3] != ""){
                if(debug_on) cout << " data: (";
                if(debug_on) cout << m[3] << ")";   //register
                if(m[2] == "INT"){
                    current_assebler_memory[location].opp_code = stoi(m[3]);
                    count+=4;
                }
                else if(m[2] == "BYT"){
                    current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[3]);
                    current_assebler_memory[location].byte_transfer = true;
                    string temp_string = m[3];
                    if(isdigit(temp_string[0])){
                        int temp_int = stoi(temp_string);
                        char temp_char = (char)temp_int;
                        current_assebler_memory[location].opp_code = temp_char;
                    }
                    else {
                        char temp_char = temp_string[0];
                        current_assebler_memory[location].opp_code = temp_char;
                    }
                    count++;
                }
                
            }
        }
        
        if(debug_on) cout << endl;
    }
    // search for LCK and ULK
    else if(std::regex_search(instruction_in,m,mutext_search)){
        if (m[0] != ""){
            if(debug_on) cout << "Found MATCH: (";
            if(debug_on) cout << m[0] << ")"; //full matched string
            current_assebler_memory[location].location = count;
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],count);
        }
        if (m[2] != ""){
            if(debug_on) cout << " OP CODE: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[2]); //convert the string to opp code
        }
        if (m[3] != ""){
            if(debug_on) cout << " Register/Label: (";
            if(is_label(m[3],location) == -2){
                current_assebler_memory[location].arg2_string = m[3];
                current_assebler_memory[location].arg2_is_label = true;
            }
            else {
                current_assebler_memory[location].arg2 = is_label(m[3],location);
            }
            if(debug_on) cout << m[4] << ")";   //register/label
        }
        count+=12;
    }
    // Search for BLK and END
    else if(std::regex_search(instruction_in,m,end_blk_search)){
        if (m[0] != ""){
            if(debug_on) cout << "Found MATCH: (";
            if(debug_on) cout << m[0] << ")"; //full matched string
            current_assebler_memory[location].location = count;
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],count);
        }
        if (m[2] != ""){
            if(debug_on) cout << " OP CODE: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[2]); //convert the string to opp code
        }
        count+=12;
    }
    // General instruction Regex search
    else if(std::regex_search(instruction_in,m,gen_opp_serach)){
        // for (auto x:m) std::cout << x << endl;
        bool dual_opp_code = false; // variable to hold if the opp code is a dual defined opp code
        if (m[0] != ""){
            if(debug_on) cout << "MATCH (";
            if(debug_on) cout << m[0] << ")"; //full matched string
            current_assebler_memory[location].location = count;
            if(!found_first_opp) {
                first_opp_location = count;
                found_first_opp = true;
            }
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],count);
        }
        if (m[2] != ""){
            if(debug_on) cout << " OP CODE: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[2]); //convert the string to opp code
            dual_opp_code = OPPS_DICTIONARY.is_dual_opp(current_assebler_memory[location].opp_code); // sets flag for dual code
            // cout << m[2] << " " << OPPS_DICTIONARY.is_dual_opp(current_assebler_memory[location].opp_code) << endl; // Debug the dual opp code function
        }
        if (m[3] != ""){
            if(debug_on) cout << " Register: (";
            if(debug_on) cout << m[3] << ")";   //register
            current_assebler_memory[location].arg1 = is_label(m[3],location);
        }
        if (m[4] != ""){
            if(debug_on) cout << " Register/Label: (";
            if(is_label(m[4],location) == -2){
                current_assebler_memory[location].arg2_string = m[4];
                current_assebler_memory[location].arg2_is_label = true;
            }
            else {
                current_assebler_memory[location].arg2 = is_label(m[4],location);
            }
            if(debug_on) cout << m[4] << ")";   //register/label
        }
        if (dual_opp_code) { // Convert opp-code if the label is a register
            OPPS_DICTIONARY.convert_dual_opp(current_assebler_memory[location].opp_code, !current_assebler_memory[location].arg2_is_label);
        }
        if(debug_on) cout << endl;
        count+=12;
        // std::cout << std::endl;
        // s = m.suffix().str();
    }
}
void my_assembler_transfer_to_mem(my_assembly_VM &VM_IN){
    int offset_temp;
    for(int i = 0; i < MEM_SIZE; i++){
        offset_temp = current_assebler_memory[i].location;
        if(offset_temp != -1){
            if(!current_assebler_memory[i].is_instruction){
                *(int*)(VM_IN.VM_MEMORY+offset_temp+0) = current_assebler_memory[i].opp_code;
                *(int*)(VM_IN.VM_MEMORY+offset_temp+4) = current_assebler_memory[i].arg1;
                *(int*)(VM_IN.VM_MEMORY+offset_temp+8) = current_assebler_memory[i].arg2;
                if(debug_on) cout << "ASSEMBLER(" << offset_temp << ") " << current_assebler_memory[i].opp_code << " | " << current_assebler_memory[i].arg1 << " | " << current_assebler_memory[i].arg2 << endl;
                if(debug_on) cout << "MEMORY   (" << offset_temp << ") " << *(int*)(VM_IN.VM_MEMORY+offset_temp+0) << " | " << *(int*)(VM_IN.VM_MEMORY+offset_temp+4) << " | " << *(int*)(VM_IN.VM_MEMORY+offset_temp+8)  << endl << endl;
            }
            else {
                if(current_assebler_memory[i].byte_transfer){
                    VM_IN.VM_MEMORY[offset_temp] = current_assebler_memory[i].opp_code;
                    if(debug_on) cout << VM_IN.VM_MEMORY[offset_temp] << endl;
                }
                else{
                    *((int*)(VM_IN.VM_MEMORY+offset_temp)+0) = current_assebler_memory[i].opp_code;
                    if(debug_on) cout << *((int*)(VM_IN.VM_MEMORY+offset_temp)+0) << endl;
                }
                
            }
        }
    }
}

int main(int argc, char** argv)
{
    initialize();
    debug_on = false; //debug output enabled or disabled

    my_assembly_VM VM1;

    // grab the arguments passed in from the program run
    if(argc < 1){
        if(debug_on) cout << "A file argument was not passed\n";
        return 0;
    }
    if(argc >= 3){
        if (argv[2][1] == 'd'){
            debug_on = true;
        }
    }
    ifstream my_file_in(argv[1]);
    if(!my_file_in.is_open()){ //check if we could open the file
        if(debug_on) cout << "Could not open file: " << argv[1] << " \n";
        return 0;
    }
    // DEBUG print out all arguments
    for (int i = 0; i < argc; ++i) 
        if(debug_on) cout << argv[i] << "\n"; 

    // Initialize Memory
    char mem[MEM_SIZE];

    char temp_char[50];

    // Using string to read from file
    string temp_string;
    if(my_file_in.is_open()){
        int location_counter = 0;
        if(debug_on) cout << "printing with strings\n"; //debug line
        int count = 0;
        int location = 0;
        while (getline(my_file_in,temp_string)){ //grab line
            stringstream temp_stream(temp_string);
            string token;
            vector<string> vec_tokens; //temp vector to hold tokens
            if(debug_on) cout << "This is the count:     ----" << count << "----------------" << endl;
            if(location > MEM_SIZE) cout << "DEBUG: OUT OF MEMORY. ASM file larger than VM memory." << endl;
            my_assembler(temp_string, location, count); //assembler pass one
            location++;
        }
        last_opp_location = count; //find the last place of the code
        my_assembler_label_replace(); //replace all labels with addresses
        my_assembler_transfer_to_mem(VM1); //transfer assembly to VM memory
        VM1.run(first_opp_location, last_opp_location);
    }
    else{
        if(debug_on) cout << "No Text file avalible!\n";
    }

    my_file_in.close();
    
    return 0;
}