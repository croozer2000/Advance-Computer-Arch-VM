#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
// #include <vector>


using namespace std;
#define MEM_SIZE 100
int main(int argc, char** argv)
{
    // in file stream
    ifstream my_file_in("text_in.txt");
    

    int j, i, *ii;  //32 bits
    char c, *cc;    //8 bits
    char mem[MEM_SIZE];

    int in_int = 26;

    // cast mem to an int pointer then dereference it
    *(int*)mem = in_int; 
    *(char*)(mem + 4) = 'a';

    // apply the chars from mem location 4 to int pointer ii
    ii = (int*)(mem + 4); //base address + 10
    cc = mem+4;

    mem[0] = 'c';
    mem[1] = 'h';
    mem[2] = 'r';
    mem[3] = 'i';

    i = *(int*)mem;

    *(int*)(mem + 4) = i;
    *(int*)(mem + 8) = i;

    cout << mem << '\n';


    char temp_char[50];
    if(my_file_in.is_open()){
        while(!my_file_in.eof()){
            my_file_in >> temp_char;
            //cout << temp_char << "\n";

            
            char delim[] = ",";
            char *token = strtok(temp_char,delim);
            while(token){
                printf("%s\n",token);
                token = strtok(NULL,delim);
            }
        }
    }
    my_file_in.close();
    my_file_in.open("text_in.txt");

    // Using string to read from file
    string temp_string;
    if(my_file_in.is_open()){
        int location_counter = 0;
        cout << "printing with strings\n";
        while (getline(my_file_in,temp_string)){
            cout << temp_string << '\n';
            
            for(int i = 0; i < temp_string.length();i++){
                mem[location_counter] = temp_string[i];
                location_counter++;
            }
        }
    }
    else{
        cout << "No Text file avalible!\n";
    }

    my_file_in.close();
    // grab the arguments passed in from the program run
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << "\n"; 
    return 0;
}