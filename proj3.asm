cSize .INT 7
cCnt .INT 0
cData .BYT 0
.BYT 0
.BYT 0
.BYT 0
.BYT 0
.BYT 0
.BYT 0
ent .BYT 10 //return character
flag .INT 1
start ADD R1 R2
ADI R10 -4      //move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP getChar
JMP start
getChar LDR R1 cCnt
MOV R2 R1   //create copy of count
TRP 4
LDB R5 ent
CMP R5 R3 // compare to a return char to break from loop
BRZ R5 getCharReturn // if char is a return char branch to function return
LDR R0 cSize //getChar function - check if we are under array size
CMP R1 R0 // break loop if char array too big
BNZ R1 getCharCont
LDR R7 flag     //set the larger than array flag
JMP getChar
getCharCont LDA R0 cData    //grab location of cData
ADD R0 R2       //Increment cCount pointer
STB R3 R0       //Store the char to the array
ADI R2 1    //add 1 to the cCnt
STR R2 cCnt
JMP getChar
getCharReturn LDR R5 R11    //grab the return address
MOV R3 R11      //copy the frame pointer over
ADI R3 -4       //increment copy of frame pointer to point to previous FP location
LDR R11 R3      //place previous frame pointer back
ADI R10 8      //Decrement stack pointer
JMR R5
done TRP 0