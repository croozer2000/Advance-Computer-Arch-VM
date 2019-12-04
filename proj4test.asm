mutex_array .INT -1
mutex_cnt .INT -1
ADI R0 2
RUN R3 test
END
BLK
crap LCK test
ULK test
RUN R3 test
doit ADD R0 R0
JMP doit
test ADD R2 R3
TRP 1
JMP test