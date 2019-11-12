size .INT 10
arr .INT 10
.INT 2
.INT 3
.INT 4
.INT 15
.INT -6
.INT 7
.INT 8
.INT 9
.INT 10
divisor .INT 2
even .BYT 32 //a space
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 'e'
.BYT 'v'
.BYT 'e'
.BYT 'n'
ent .BYT 10
odd .BYT 32 //a space
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 'o'
.BYT 'd'
.BYT 'd'
.BYT 10
sum .BYT 'S'
.BYT 'u'
.BYT 'm'
.BYT 32
.BYT 'i'
.BYT 's'
.BYT 32
.BYT 10
LDA R7 arr
loopstart ADI R4 1 //increment loop counter
LDR R2 R7 //load array item
ADI R7 4 // increment array location variable
ADD R0 R2   //add to sum
LDR R5 divisor //load 2 to R5
MOV R1 R2
DIV R1 R5
MUL R1 R5
SUB R1 R2 //reg1 holds the modulous
MOV R3 R2
TRP 1
LDA R2 even //grab start of char array
BRZ R1 jump
LDA R2 odd
jump JMP print
return LDR R2 size // grab loop size
CMP R2 R4 // compare loop counter to loop size
BRZ R2 end //branch if loop is done
JMP loopstart //branch to begining of loop
end LDA R2 sum
JMP print2
endreturn MOV R3 R0
TRP 1
LDB R3 ent
TRP 3
TRP 3
TRP 0
print LDB R3 R2 //load char
TRP 3
ADI R2 1 //increment array pointer
LDB R5 ent
CMP R5 R3 // find a return char to break from loop
BNZ R5 print
JMP return
print2 LDB R3 R2 //load char
LDB R5 ent
CMP R5 R3 // find a return char to break from loop
BRZ R5 endreturn
TRP 3
ADI R2 1 //increment array pointer
JMP print2