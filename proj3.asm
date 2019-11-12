cSize .INT 5
cCnt .INT 0
cData .BYT 0
.BYT 0
.BYT 0
.BYT 0
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
ADI R10 -4      //move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP getChar


ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP isNumber     //function call code end - 

ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP whatPrint     //function call code end - 

SUB R0 R0       //Reset Flags
STB R0 cCnt
STB R0 notNumflag
STB R0 tolargeflag
JMP start

getChar LDR R1 cCnt
MOV R2 R1   //create copy of count
TRP 4
LDB R5 ent
CMP R5 R3 // compare to a return char to break from loop
BRZ R5 getCharReturn // if char is a return char branch to function return
LDB R5 atSign
CMP R5 R3 // compare to a @ char to break from loop
MUL R5 R5
ADD R5 R1
BRZ R5 done // if char is a @ char branch to function return
LDR R0 cSize //getChar function - check if we are under array size
CMP R1 R0 // break loop if char array too big
BNZ R1 getCharCont
SUB R7 R7
ADI R7 1
STB R7 tolargeflag    //set the larger than array flag
JMP getChar

getCharReturn LDA R1 cData 
LDR R2 cCnt
ADD R1 R2
LDB R2 ent
STB R2 R1 
JMP Return

getCharCont LDA R0 cData    //grab location of cData
ADD R0 R2       //Increment cCount pointer
STB R3 R0       //Store the char to the array
ADI R2 1    //add 1 to the cCnt
STR R2 cCnt
JMP getChar

isNumber LDR R0 cCnt        //grab cCnt
isNumberloop LDA R1 cData                //grab location of cData
SUB R3 R3                   //clear register 2
SUB R6 R6                   //clear register 6
ADI R0 -1
BLT R0 Return       //if cCnt is less than zero then end function
MOV R2 R1                   //copy the cData pointer
ADD R2 R0                   //base and offset
LDB R3 R2                   //load the character
MOV R4 R3
LDB R5 lowerNum             //Find if char is number
CMP R3 R5
LDB R5 upperNum
CMP R4 R5
ADD R4 R3                   //if reg3 has zero than we have a number
LDB R3 R2   //grab the char
LDB R5 ent
CMP R5 R3
BRZ R5 isNumberloop         //continue through branches if - not number
BRZ R4 isNumberloop         //                              - or not return symbol
ADI R6 1                    //Set the not number flag
STB R3 notNumflag

Return LDR R5 R11    //grab the return address
MOV R3 R11      //copy the frame pointer over
ADI R3 -4       //increment copy of frame pointer to point to previous FP location
LDR R11 R3      //place previous frame pointer back
ADI R10 8      //Decrement stack pointer
JMR R5

done TRP 0

whatPrint SUB R0 R0        //print line function -- clear Reg0
LDB R7 tolargeflag
LDB R6 notNumflag
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

LDR R0 cCnt     //check if any items were passed
BNZ R0 haveItem
SUB R3 R3
ADI R3 48
TRP 3
haveItem LDA R2 cData
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
JMP Return

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