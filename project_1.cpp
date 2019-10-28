#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <bits/stdc++.h> //
#include <vector> 
#include <regex>
#include <map> //map table
#include <cctype> //testing characters

#include "assembler/assembler.h" //may want to use structure file

// Static items
using namespace std;
#define MEM_SIZE 250
string REGISTER_LIST[] = {"R0","R1","R2","R3","R4","R5","R6","R7","R8"};
#define NUM_OF_REG 9
#define NUM_OPPS 21
bool debug_on = true;



// Assembler items
assembler_mem current_assebler_memory[MEM_SIZE];
oppcode_dictionary OPPS_DICTIONARY;
bool found_first_opp = false;
int first_opp_location;

class my_assembly_VM {
    public:
    // VM Items
    int     VM_REGISTERS[9];
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

    void run(int program_start_location){
        bool run = true;
        int current_operation;
        int current_arg1;
        int current_arg2;
        VM_REGISTERS[8] = program_start_location;
        while (run){

            current_operation = *(int*)(VM_MEMORY+(VM_REGISTERS[8]));
            current_arg1 = *(int*)(VM_MEMORY+(VM_REGISTERS[8]+4));
            current_arg2 = *(int*)(VM_MEMORY+(VM_REGISTERS[8]+8));
            
            VM_REGISTERS[8]+=12;
            switch (current_operation){
                case 1: { //JMP
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 2: { //JMR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 3: { //BNZ
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 4: { //BGT
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 5: { //BLT
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 6: { //BRZ
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 7: { //MOV
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = VM_REGISTERS[current_arg2];
                }
                break;
                case 8: { //LDA
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 9: { //STR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 10: { //LDR
                    // cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation[0]) << endl;
                    VM_REGISTERS[current_arg1] = *(int*)(VM_MEMORY+current_arg2);
                }
                break;
                case 11: { //STB
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
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
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
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
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 19: { //OR
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
                }
                break;
                case 20: { //CMP
                    cout << "Function has not been programmed for: " << OPPS_DICTIONARY.get_opp_name(current_operation) << endl;
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
                    cout << "ERROR not an oppcode at memory location: (" << VM_REGISTERS[8]-12 << ") OPP Code dump: " << + current_operation <<endl;
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
void my_assembler(string instruction_in, int &location,int &count){
    smatch m;
    regex gen_opp_serach ("(\\w+)*? ?([A-Z]{2,3}) (R[0-8])? *(R[0-8]|\\w+)");   // matches words beginning by "sub"
    regex label_search ("(\\w+)? *.(INT|BYT) *[']?(\\w+)[']?");

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
    // General instruction Regex search
    else if(std::regex_search(instruction_in,m,gen_opp_serach)){
        // for (auto x:m) std::cout << x << endl;
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
            }
            if(debug_on) cout << m[4] << ")";   //register/label
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
                if(debug_on) cout << "(" << offset_temp << ") " << current_assebler_memory[i].opp_code << " | " << current_assebler_memory[i].arg1 << " | " << current_assebler_memory[i].arg2 << endl;
                if(debug_on) cout << "(" << offset_temp << ") " << *((int*)(VM_IN.VM_MEMORY+offset_temp)+0) << " | " << *((int*)(VM_IN.VM_MEMORY+offset_temp)+4) << " | " << *((int*)(VM_IN.VM_MEMORY+offset_temp)+8)  << endl << endl;
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
        my_assembler_label_replace(); //replace all labels with addresses
        my_assembler_transfer_to_mem(VM1); //transfer assembly to VM memory
        VM1.run(first_opp_location);
    }
    else{
        if(debug_on) cout << "No Text file avalible!\n";
    }

    my_file_in.close();
    
    return 0;
}