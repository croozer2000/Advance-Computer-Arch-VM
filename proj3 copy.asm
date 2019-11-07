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
start ADD R1 R2
ADI R10 -4      //function call code start - move stack pointer size of int
MOV R3 R11      //save fame pointer for later
MOV R11 R10     //frame pointer pointing at bottom of activation record (stack pointer)
ADI R10 -4      //move stack pointer size of int
STR R3 R10      //place previous frame pointer on the stack
MOV R1 R8       //save the PC to a temp location
ADI R1 36       //caluclate return address
STR R1 R11      //store the return address
JMP isNumber     //function call code end - 
JMP start
isNumber LDR R0 cCnt        //grab cCnt
isNumberloop LDA R1 cData                //grab location of cData
SUB R3 R3                   //clear register 2
SUB R6 R6                   //clear register 6
ADI R0 -1
BLT R0 isNumberReturn       //if cCnt is less than zero then end function
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
STR R6 notNumflag
isNumberReturn LDR R5 R11    //Return code start - grab the return address
MOV R3 R11      //copy the frame pointer over
ADI R3 -4       //increment copy of frame pointer to point to previous FP location
LDR R11 R3      //place previous frame pointer back
ADI R10 8      //Decrement stack pointer
JMR R5         //Return code end
done TRP 0