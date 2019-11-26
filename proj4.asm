ent .BYT 10 //return character
fibString .BYT 'F'
.BYT 'i'
.BYT 'b'
.BYT 'o'
.BYT 'n'
.BYT 'a'
.BYT 'c'
.BYT 'c'
.BYT 'i'
.BYT 32
.BYT 10

stringIs .BYT 32
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 10

cnt .INT 0
arrayThirty .INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0
.INT 0

main TRP 2      //grab integer
MOV R0 R3
SUB R3 R3
CMP R3 R0
BRZ R3 done

ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP fibMain     //function call code end - 
JMP main

fibMain MOV R3 R0
ADI R10 -4      //Save the passed int to the stack
STR R3 R10
MOV R0 R7       //reg 7 will not be altered during the course of fibbinachi

LDA R2 fibString
ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP println2     //function call code end - 

LDR R3 R10      //pull from the stack the placed number
ADI R10 4
TRP 1

LDA R2 stringIs
ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save frame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP println2     //function call code end - 

ADI R10 -4      //function call code start - move stack pointer size of int
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
JMP Return        //when creating multi threading replace JMP with a end

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
SUB R4 R4
ADI R4 2
SUB R0 R4
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
JMP Return      //end of fibbinachi function

println2 LDB R1 ent     //print function that does not print return chars
LDB R3 R2
ADI R2 1
CMP R1 R3
BRZ R1 Return     //if char is not enter then loop
TRP 3
JMP println2

done TRP 0      //end statement