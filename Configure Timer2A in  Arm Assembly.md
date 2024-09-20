![][image1]  
**EGCP 280- Microcontrollers** 

**LAB \#8 Report** 

**Name: Alexander Martinez** 

**1\. Write a code to configure the Timer 2A timer to operate in the interrupt mode, set  at the maximum possible interval. At the end of each interval, the ISR for timer 2A changes the LED to the next LED color in the table below. Start with LEDs all off.**  

 .thumb 

 .data 

TimerCount .word 0 

 .text ; Puts code in ROM 

SYSCTL\_RCGTIMER\_R .word 0X400FE604; Clock Registers 

;Time Registers 

TIMER2\_CTL\_R .word 0X4003200C 

TIMER2\_CFG\_R .word 0X40032000 

TIMER2\_TAMR\_R .word 0X40032004  
TIMER2\_TAILR\_R .word 0X40032028 TIMER2\_TAPR\_R .word 0X40032038 TIMER2\_ICR\_R .word 0X40032024 TIMER2\_IMR\_R .word 0X40032018 TIMER2\_RIS\_R .word 0X40032 

;Constants 

MASK .word 0X00FFFFFF PRI4 .word 0X80000000 ENABLE .word 0X00800000 

Period .word 80000 

;NVIC Registers 

NVIC\_PRI5\_R .word 0XE000E414 NVIC\_EN0\_R .word 0XE000E100 

;Pointers 

TimerCountPtr .word TimerCount 

;PortF 

SYSCTL\_RCGC2\_R .word 0x400FE108 ; clock registers GPIO\_PORTF\_LOCK\_R .word 0x40025520 GPIO\_PORTF\_CR\_R .word 0x40025524 GPIO\_PORTF\_AMSEL\_R .word 0x40025528 GPIO\_PORTF\_PCTL\_R .word 0x4002552C GPIO\_PORTF\_DIR\_R .word 0x40025400 GPIO\_PORTF\_AFSEL\_R .word 0x40025420 GPIO\_PORTF\_PUR\_R .word 0x40025510 GPIO\_PORTF\_DEN\_R .word 0x4002551C GPIO\_PORTF\_DATA\_R .word 0x400253FC 

GPIO\_UL .word 0x4C4F434B CNT .word 0x000FFFFF 

 .global asm\_main 

 .thumbfunc asm\_main 

 .global Timer2A\_ISR 

 .thumbfunc Timer2A\_ISR 

 .global asm\_logic 

 .thumbfunc asm\_logic  
asm\_main: .asmfunc ; main 

 LDR R2, SYSCTL\_RCGC2\_R  LDR R1, \[R2\] 

 ORR R1, \#0x28 

 STR R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_LOCK\_R  LDRB R1, \[R2\] 

 LDR R1, GPIO\_UL 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_CR\_R  LDRB R1, \[R2\] 

 ORR R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_AMSEL\_R  LDRB R1, \[R2\] 

 BIC R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_PCTL\_R  LDRB R1, \[R2\] 

 BIC R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_DIR\_R  LDRB R1, \[R2\] 

 ORR R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_AFSEL\_R  LDRB R1, \[R2\] 

 BIC R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_PUR\_R  LDRB R1, \[R2\] 

 BIC R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 LDR R2, GPIO\_PORTF\_DEN\_R  LDRB R1, \[R2\] 

 ORR R1, \#0X0E ; 1110 

 STRB R1, \[R2\]  
 LDR R2, GPIO\_PORTF\_DATA\_R 

 LDRB R1, \[R2\] 

 BIC R1, \#0X0E ; 1110 

 STRB R1, \[R2\] 

 ; Finishes Initiliazation fo port F 

 ;Timer Initiliazation 

 CPSID i 

 LDR R0, SYSCTL\_RCGTIMER\_R; Activate Clock for Timer2  LDR R1, \[R0\] 

 ORR R1, \#0X04 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_CTL\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0x00 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_CFG\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X00 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_TAMR\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X02 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_TAILR\_R 

 LDR R1, \[R0\] 

 mov R1, \#0XFF 

 LSL R1, \#8 

 ORR R1, \#0XFF 

 LSL R1, \#8 

 ORR R1, \#0XFF 

 STR R1, \[R0\] 

;F42400 

 LDR R0, TIMER2\_TAPR\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X00 

 STR R1, \[R0\]  
 LDR R0, TIMER2\_ICR\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X01 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_IMR\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X01 

 STR R1, \[R0\] 

; NVIC REGISTERS 

 LDR R0, NVIC\_PRI5\_R 

 LDR R1, \[R0\] 

 LDR R2, MASK 

 AND R1, R2 

 LDR R2, PRI4 

 ORR R1, R2 

 STR R1, \[R0\] 

 LDR R0, NVIC\_EN0\_R 

 LDR R1, \[R0\] 

 LDR R2, ENABLE 

 MOV R1, R2 

 STR R1, \[R0\] 

 LDR R0, TIMER2\_CTL\_R 

 LDR R1, \[R0\] 

 MOV R1, \#0X01 

 STR R1, \[R0\] 

 CPSIE I 

 bx lr ; return to C program  .endasmfunc 

asm\_logic: .asmfunc 

 LDR R3, Period 

 BL asm\_main 

 bx lr ; return to C program  
 .endasmfunc 

Timer2A\_ISR: .asmfunc 

 LDR R0, TIMER2\_ICR\_R  LDR R1, \[R0\] 

 MOV R1, \#0X01 

 STR R1, \[R0\] 

 ;LDR R0, TimerCountPtr  ;LDR R1, \[R0\] 

 ;ADD R1, \#0X01 

 ;STR R1, \[R0\] 

 LDR R0, GPIO\_PORTF\_DATA\_R;  LDRB R1, \[R0\] 

 ADD R1, R1, \#0X02 

 BIC R1, \#0X10 

 strb r1, \[r0\] 

 bx lr 

 .endasmfunc 

 .end 




main.c

\#include \<stdint.h\> 

\#include "tm4c123gh6pm.h" 

extern void asm\_main(); 

extern void Timer2A\_ISR(); 

extern void asm\_logic(); 

/\* 

\* Main Function 

\* Start of program 

\*/ 

void Timer2A\_Handler() { Timer2A\_ISR(); } 

void main() { 

asm\_main(); // Call Assembly Main  
while (1) { asm\_logic(); } 

}   
