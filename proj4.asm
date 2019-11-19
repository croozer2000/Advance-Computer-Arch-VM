label .BYT 13

ADI R0 1
main ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP fibonacci     //function call code end - 
print MOV R3 R0
TRP 1
LDB R3 ent
TRP 3
TRP 0

fibonacci SUB R1 R1
ADI R1 1
CMP R1 R0       //if number is 1 or less return
BLT R1 fibCall
Return LDR R5 R11    //grab the return address
MOV R3 R11      //copy the frame pointer over
ADI R3 -4       //increment copy of frame pointer to point to previous FP location
LDR R11 R3      //place previous frame pointer back
ADI R10 8      //Decrement stack pointer
JMR R5

fibCall ADI R10 -4      //move stack pointer up int
STR R0 R10              //save the n variable
ADI R0 -1
ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP fibonacci     //function call code end - 

MOV R1 R0       //copy the return item to another register
LDR R0 R10      //reload from stack the number
ADI R0 -2
STR R1 R10      //save previous return value to stack

ADI R10 -4      //second fib call - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP fibonacci     //function call code end - 

LDR R1 R10      //grab last return value back off stack
ADD R0 R1       //add new return with old return
ADI R10 4       //return stack count to normal
JMP Return