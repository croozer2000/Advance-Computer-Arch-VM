cSize .INT 7
cCnt .INT 4
cData .BYT 48
.BYT 49
.BYT 50
.BYT 10
.BYT 0
.BYT 0
.BYT 0
ent .BYT 10 //return character
atSign .BYT 64
tolargeflag .BYT 0
notNumflag .BYT 0
lowerNum .BYT 47
upperNum .BYT 58
stringNotNum .BYT 32 //a space
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 'n'
.BYT 'o'
.BYT 't'
.BYT 32
.BYT 'n'
.BYT 'u'
.BYT 'm'
.BYT 'b'
.BYT 'e'
.BYT 'r'
.BYT 10
tooBig .BYT 'N'
.BYT 'u'
.BYT 'm'
.BYT 'b'
.BYT 'e'
.BYT 'r'
.BYT 32
.BYT 't'
.BYT 'o'
.BYT 'o'
.BYT 32
.BYT 'B'
.BYT 'i'
.BYT 'g'
.BYT 10
numberString .BYT 'O'
.BYT 'p'
.BYT 'e'
.BYT 'r'
.BYT 'a'
.BYT 'n'
.BYT 'd'
.BYT 32
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 10

start ADD R1 R2
ADI R7 1
ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP whatPrint     //function call code end - 
JMP start

whatPrint SUB R0 R0        //print line function -- clear Reg0
BNZ R7 printTooBig
BNZ R6 printNotNum

LDA R2 numberString
ADI R10 -4      //function call code start printlns- move stack pointer size of int
MOV R3 R11     
MOV R11 R10     
ADI R10 -4      
STR R3 R10      
MOV R1 R8       
ADI R1 36       
STR R1 R11
JMP println2     //function call code end printlns- 

LDA R2 cData
ADI R10 -4      //function call code start printlns- move stack pointer size of int
MOV R3 R11     
MOV R11 R10     
ADI R10 -4      
STR R3 R10      
MOV R1 R8       
ADI R1 36       
STR R1 R11
JMP printlns     //function call code end printlns- 
JMP Return

printNotNum LDB R3 notNumflag
TRP 3           //print not number string
LDA R2 stringNotNum
JMP startprint

printTooBig LDA R2 tooBig
startprint ADI R10 -4      //function call code start printlns- move stack pointer size of int
MOV R3 R11     
MOV R11 R10     
ADI R10 -4      
STR R3 R10      
MOV R1 R8       
ADI R1 36       
STR R1 R11
JMP printlns     //function call code end printlns- 

Return LDR R5 R11    //Return code start - grab the return address
MOV R3 R11      //copy the frame pointer over
ADI R3 -4       //increment copy of frame pointer to point to previous FP location
LDR R11 R3      //place previous frame pointer back
ADI R10 8      //Decrement stack pointer
JMR R5         //Return code end

printlns LDB R1 ent     //print function
LDB R3 R2
ADI R2 1
TRP 3
CMP R1 R3
BNZ R1 printlns     //if char is not enter then loop
JMP Return

println2 LDB R1 ent     //print function that does not print return chars
LDB R3 R2
ADI R2 1
CMP R1 R3
BRZ R1 Return     //if char is not enter then loop
TRP 3
JMP println2
done TRP 0