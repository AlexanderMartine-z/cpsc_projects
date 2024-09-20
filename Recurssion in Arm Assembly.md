

**EGCP 280- Microcontrollers** 



**Name: Alexander Martinez**

**Write a code that computes the factorial of a number (stored in R0) recursively, and  stores the final result in R1. You must use the stack to hold all intermediate values of  each recursive function call.** 

**Insert a copy of the assembly code below** 

.thumb 

**.data** 

**.text** ; Puts code in ROM 

**.global** asm\_main 

.thumbfunc asm\_main 

**asm\_main:** .asmfunc ; main 

**MOV** R0, \#6; COUNTER 

**MOV** R1, \#1 

**LOOP:** 

**CMP** R0, \#1 

BEQ MOVE 

**push** {r0} 

**sub** R0, R0, \#1  
**B** LOOP 

**MOVE:** 

**CMP** r0, \#6 

**ADD** r0, R0, \#1 

BEQ EXIT 

**POP** {R5} 

MUL R1, R1, R5 

**B** MOVE 

**EXIT:**

