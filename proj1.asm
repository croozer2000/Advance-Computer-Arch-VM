LDB R3 nC //Displaying Name
TRP 3
LDB R3 nh
TRP 3
LDB R3 nr
TRP 3
LDB R3 ni
TRP 3
LDB R3 ns
TRP 3
LDB R3 nt
TRP 3
LDB R3 ni
TRP 3
LDB R3 na
TRP 3
LDB R3 nn
TRP 3
LDB R3 com
TRP 3
LDB R3 spc
TRP 3
LDB R3 nG
TRP 3
LDB R3 na
TRP 3
LDB R3 nr
TRP 3
LDB R3 nr
TRP 3
LDB R3 ne
TRP 3
LDB R3 nt
TRP 3
LDB R3 nt
TRP 3
LDB R3 ent
TRP 3
TRP 3
LDR R0 B1 //Adding list B
LDR R1 B2
ADD R0 R1
MOV R3 R0
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R1 B3
ADD R0 R1
MOV R3 R0
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R1 B4
ADD R0 R1
MOV R3 R0
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R1 B5
ADD R0 R1
MOV R3 R0
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R1 B6
ADD R0 R1
MOV R3 R0
TRP 1
LDB R3 ent //Adding a enter
TRP 3
TRP 3
LDR R1 A1 //MUL list A
LDR R2 A2
MUL R1 R2
MOV R3 R1
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R2 A3
MUL R1 R2
MOV R3 R1
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R2 A4
MUL R1 R2
MOV R3 R1
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R2 A5
MUL R1 R2
MOV R3 R1
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
LDR R2 A6
MUL R1 R2
MOV R3 R1
TRP 1
LDB R3 ent //Adding a enter
TRP 3
TRP 3
MOV R3 R0 //Part 7
LDR R2 B1
DIV R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R0
LDR R2 B2
DIV R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R0
LDR R2 B3
DIV R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R0
LDR R2 B4
DIV R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R0
LDR R2 B5
DIV R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R0
LDR R2 B6
DIV R3 R2
TRP 1
LDB R3 ent //Adding a enter
TRP 3
TRP 3
MOV R3 R1 //part 9
LDR R2 C1
SUB R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R1
LDR R2 C2
SUB R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R1
LDR R2 C3
SUB R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
MOV R3 R1
LDR R2 C4
SUB R3 R2
TRP 1
LDB R3 spc //Adding a space
TRP 3
TRP 3
TRP 0
nC .BYT 'C'
nh .BYT 'h'
nr .BYT 'r'
ni .BYT 'i'
ns .BYT 's'
nt .BYT 't'
na .BYT 'a'
nn .BYT 'n'
nG .BYT 'G'
ne .BYT 'e'
com .BYT 44
spc .BYT 32
ent .BYT 10
A1 .INT 1
A2 .INT 2
A3 .INT 3
A4 .INT 4
A5 .INT 5
A6 .INT 6
B1 .INT 300
B2 .INT 150
B3 .INT 50
B4 .INT 20
B5 .INT 10
B6 .INT 5
C1 .INT 500
C2 .INT 2
C3 .INT 5
C4 .INT 10