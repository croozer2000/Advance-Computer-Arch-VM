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
#define MEM_SIZE 250
string REGISTER_LIST[] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8"};
#define NUM_OF_REG 9
#define NUM_OPPS 21
bool debug_on = true;

class assembler_mem {
    public:
    bool    byte_transfer = true;
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
    char    op1_type[NUM_OPPS];
    char    op2_type[NUM_OPPS];
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

// Assembler items
assembler_mem current_assebler_memory[MEM_SIZE];
oppcode_dictionary OPPS_DICTIONARY;

class my_assembly_VM {
    public:
    // VM Items
    int     VM_REGISTERS[9];
    int     VM_MEMORY[MEM_SIZE];

    
    void initialize(){
        for(int i = 0; i < NUM_OF_REG; i++){
            VM_REGISTERS[i] = 0;
        }
        for(int i = 0; i < MEM_SIZE; i++){
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

    void run(){
        bool run = true;
        unsigned char current_operation[4]; //NOTE USING UNSIGNED BYTES
        while (run){

            *(int*)current_operation = VM_MEMORY[(VM_REGISTERS[8])];
            VM_REGISTERS[8]++;
            switch (current_operation[0]){
                case 1: { //JMP
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 2: { //JMR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 3: { //BNZ
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 4: { //BGT
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 5: { //BLT
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 6: { //BRZ
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 7: { //MOV
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_operation[1]] = VM_REGISTERS[current_operation[2]];
                }
                break;
                case 8: { //LDA
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 9: { //STR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 10: { //LDR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_operation[1]] = VM_MEMORY[current_operation[2]];
                }
                break;
                case 11: { //STB
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 12: { //LDB
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    *(char*)(VM_REGISTERS+current_operation[1]) = *(char*)(VM_MEMORY+current_operation[2]);
                }
                break;
                case 13: { //ADD
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    // if(debug_on) cout << "regD: " << VM_REGISTERS[current_operation[1]] << "regS: " << VM_REGISTERS[current_operation[2]] << endl;
                    int temp_int = VM_REGISTERS[current_operation[1]] + VM_REGISTERS[current_operation[2]];
                    VM_REGISTERS[current_operation[1]] = temp_int;
                }
                break;
                case 14: { //ADI
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 15: { //SUB
                    int temp_int = VM_REGISTERS[current_operation[1]] - VM_REGISTERS[current_operation[2]];
                    VM_REGISTERS[current_operation[1]] = temp_int;
                }
                break;
                case 16: { //MUL
                    int temp_int = VM_REGISTERS[current_operation[1]] * VM_REGISTERS[current_operation[2]];
                    VM_REGISTERS[current_operation[1]] = temp_int;
                }
                break;
                case 17: { //DIV
                    int temp_int = VM_REGISTERS[current_operation[1]] / VM_REGISTERS[current_operation[2]];
                    VM_REGISTERS[current_operation[1]] = temp_int;
                }
                break;
                case 18: { //AND
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 19: { //OR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 20: { //CMP
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                }
                break;
                case 21: { //TRP
                    switch (current_operation[2]) {
                        case 0: run = false;
                        break;
                        case 1: {
                            cout << VM_REGISTERS[3];
                        }
                        break;
                        case 2: run = false;
                        break;
                        case 3: {
                            // int* temp_int;
                            // *temp_int = VM_REGISTERS[3];
                            // VM_REGISTERS[3] = 'a';
                            char temp_char = *(char*)(VM_REGISTERS+3);
                            cout << temp_char;
                        }
                        break;
                        case 4: run = false;
                        break;
                        default: run = false;
                        break;
                    }
                    
                }
                break;
                default: {
                    cout << "ERROR not an oppcode at memory location: (" << VM_REGISTERS[8]-1 << ") OPP Code dump: " << + current_operation[0] <<endl;
                }
                break;
            }
        }
    }
};




void initialize(){
    // initalize opps
    OPPS_DICTIONARY.add("JMP",1,'L',' ');
    OPPS_DICTIONARY.add("JMR",2,'S',' ');
    OPPS_DICTIONARY.add("BNZ",3,'S','L');
    OPPS_DICTIONARY.add("BGT",4,'S','L');
    OPPS_DICTIONARY.add("BLT",5,'S','L');
    OPPS_DICTIONARY.add("BRZ",6,'S','L');
    OPPS_DICTIONARY.add("MOV",7,'D','S');
    OPPS_DICTIONARY.add("LDA",8,'D','L');
    OPPS_DICTIONARY.add("STR",9,'S','L');
    OPPS_DICTIONARY.add("LDR",10,'D','L');
    OPPS_DICTIONARY.add("STB",11,'S','L');
    OPPS_DICTIONARY.add("LDB",12,'D','L');
    OPPS_DICTIONARY.add("ADD",13,'D','S');
    OPPS_DICTIONARY.add("ADI",14,'D','I');
    OPPS_DICTIONARY.add("SUB",15,'D','S');
    OPPS_DICTIONARY.add("MUL",16,'D','S');
    OPPS_DICTIONARY.add("DIV",17,'D','S');
    OPPS_DICTIONARY.add("AND",18,'D','S');
    OPPS_DICTIONARY.add("OR",19,'D','S');
    OPPS_DICTIONARY.add("CMP",20,'D','S');
    OPPS_DICTIONARY.add("TRP",21,'I',' ');
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
    if(isdigit(key_in[0])){
        is_label = false;
        location_return = stoi(key_in);
    }
    for (int i = 0; i < 9; i++) // Check if item is a register
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
// void convert_to_instant(int &OPP_IN) {
//     //function converts a direct addressing to an indirect addressing
//     //This runs if the given label is acctually a label
// }
void my_assembler(string instruction_in, int location){
    smatch m;
    regex gen_opp_serach ("(\\w+)*? ?([A-Z]{2,3}) (R[0-8])? *(R[0-8]|\\w+)");   // matches words beginning by "sub"
    regex label_search ("(\\w+)? *.(INT|BYT) *[']?(\\w+)[']?");

    if(std::regex_search(instruction_in,m,label_search)){
        // for (auto x:m) std::cout << x << endl;
        if (m[0] != ""){
            if(debug_on) cout << "Found MATCH: (";
            if(debug_on) cout << m[0] << ")"; //full matched string
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],location);
        }
        if (m[2] != ""){
            if(debug_on) cout << " Label Identifier: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            if (m[3] != ""){
                if(debug_on) cout << " data: (";
                if(debug_on) cout << m[3] << ")";   //register
                if(m[2] == "INT"){
                    current_assebler_memory[location].opp_code = stoi(m[3]);
                    current_assebler_memory[location].byte_transfer = false;
                }
                else if(m[2] == "BYT"){
                    current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[3]);
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
                }
                
            }
        }
        
        if(debug_on) cout << endl;
    }
    // General instruction Regex search
    else if(std::regex_search(instruction_in,m,gen_opp_serach)){
        // for (auto x:m) std::cout << x << endl;
        if (m[0] != ""){
            if(debug_on) cout << "MATCH (";
            if(debug_on) cout << m[0] << ")"; //full matched string
        }
        if (m[1] != ""){
            if(debug_on) cout << " label: (";
            if(debug_on) cout << m[1] << ")"; //label
            add_label(m[1],location);
        }
        if (m[2] != ""){
            if(debug_on) cout << " OP CODE: (";
            if(debug_on) cout << m[2] << ")";   //oppcode
            current_assebler_memory[location].opp_code = OPPS_DICTIONARY.get_code(m[2]);
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
                // convert_to_instant(current_assebler_memory[location].opp_code) //USE IN PROJECT 2
            }
            if(debug_on) cout << m[4] << ")";   //register/label
        }
        if(debug_on) cout << endl;
        // std::cout << std::endl;
        // s = m.suffix().str();
    }
}
void my_assembler_transfer_to_mem(my_assembly_VM &VM_IN){
    for(int i = 0; i < MEM_SIZE; i++){
        if(current_assebler_memory[i].byte_transfer){
            *((char*)(VM_IN.VM_MEMORY+i)+0) = current_assebler_memory[i].opp_code;
            *((char*)(VM_IN.VM_MEMORY+i)+1) = current_assebler_memory[i].arg1;
            *((char*)(VM_IN.VM_MEMORY+i)+2) = current_assebler_memory[i].arg2;
            if(debug_on) cout << current_assebler_memory[i].opp_code << " | " << current_assebler_memory[i].arg1 << " | " << current_assebler_memory[i].arg2 << endl;
            //NOTE DEBUG USING UNSIGNED BYTES
            if(debug_on) cout << +*((unsigned char*)(VM_IN.VM_MEMORY+i)+0) << " | " << +*((unsigned char*)(VM_IN.VM_MEMORY+i)+1) << " | " << +*((unsigned char*)(VM_IN.VM_MEMORY+i)+2) << " | " << +*((char*)(VM_IN.VM_MEMORY+i)+3) << " | int (" << VM_IN.VM_MEMORY[i] << ")" << endl << endl;
        }
        else {
            VM_IN.VM_MEMORY[i] = current_assebler_memory[i].opp_code;
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
        while (getline(my_file_in,temp_string)){ //grab line
            stringstream temp_stream(temp_string);
            string token;
            vector<string> vec_tokens; //temp vector to hold tokens
            if(debug_on) cout << "This is the count:     ----" << count << "----------------" << endl;
            if(count > MEM_SIZE) cout << "DEBUG: OUT OF MEMORY. ASM file larger than VM memory." << endl;
            my_assembler(temp_string,count); //assembler pass one
            count++;
        }
        my_assembler_label_replace(); //replace all labels with addresses
        my_assembler_transfer_to_mem(VM1); //transfer assembly to VM memory
        VM1.run();
    }
    else{
        if(debug_on) cout << "No Text file avalible!\n";
    }

    my_file_in.close();
    
    return 0;
}