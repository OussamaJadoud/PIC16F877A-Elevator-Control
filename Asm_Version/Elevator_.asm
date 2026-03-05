LIST p=16F877A                
Include "p16F877A.inc" 

ORG 0x00
GOTO init

ORG 0x04
GOTO Urgence 

CBLOCK 0x20
    Temp:2
	Svar:1
ENDC


init 
banksel INTCON
MOVLW 0x90 
MOVWF INTCON
banksel OPTION_REG
BSF OPTION_REG , 6 
banksel PORTB
CLRF PORTB
banksel TRISC
clrf TRISC
MOVLW 0XFF
MOVWF TRISB

clrf TRISD
CLRF TRISA
CLRF TRISE
banksel PORTC
MOVLW 0x01
MOVWF PORTC
CLRF PORTD
banksel ADCON1 
MOVLW 0x06
MOVWF ADCON1
banksel PORTA 
MOVLW 0x01
MOVWF PORTA



main 
	MOVLW 0x01 
	SUBWF PORTC , W
	BTFSC STATUS , 0
	CALL FLOOR1
	
	MOVLW 0x02 
	SUBWF PORTC , W
	BTFSC STATUS , 0
	CALL FLOOR2

	MOVLW 0x03 
	SUBWF PORTC , W
	BTFSC STATUS , 0
	CALL FLOOR3
	
goto main

FLOOR1
	BTFSC PORTB ,1 
	Nop
	
	BTFSC PORTB ,2
	call Fup12

	BTFSC PORTB ,3
	call F2up
Return 



FLOOR2
	BTFSC PORTB ,1 
	Call Fdown21
	
	BTFSC PORTB ,2
	NOP 

	BTFSC PORTB ,3
	call Fup23

Return




FLOOR3
	BTFSC PORTB ,1 
	Call F2down
	
	BTFSC PORTB ,2
	Call Fdown32 

	BTFSC PORTB ,3
	Nop

Return
 
 

Fincr
banksel PORTC 
INCF PORTC,1
RETURN 

Fdecr
banksel PORTC 
DECF PORTC,1
RETURN

Fup12
Call delay
MOVLW 0x02
MOVWF PORTA
Call delay
Call Motorup12
Call delay
Call Fincr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 

Fup23
Call delay
MOVLW 0x02
MOVWF PORTA
Call delay
Call Motorup23
Call delay
Call Fincr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 


Fdown21
Call delay
MOVLW 0x02
MOVWF PORTA
Call Motordown21
Call delay
Call Fdecr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 

Fdown32
Call delay
MOVLW 0x02
MOVWF PORTA
Call Motordown32
Call delay
Call Fdecr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 


F2up
Call delay
MOVLW 0x02
MOVWF PORTA
Call Motorup12
Call delay
Call Fincr
Call delay
Call Motorup23
Call delay
Call Fincr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 


F2down
call Temporisation 
Call Temporisation
MOVLW 0x02
MOVWF PORTA
Call Motordown32
Call delay
Call Fdecr
Call delay
Call Motordown21
Call delay
Call Fdecr
Call delay
MOVLW 0x01
MOVWF PORTA
Call delay
Return 


Motorup12
banksel PORTD  
MOVLW 0x01
MOVWF PORTD 
P1
BTFSS PORTB,5
Goto P1
Return

Motorup23

banksel PORTD  
MOVLW 0x01
MOVWF PORTD 
T1
BTFSS PORTB,6
Goto T1
Return

Motordown32

banksel PORTD  
MOVLW 0x03
MOVWF PORTD 
R1
BTFSS PORTB,5
Goto R1

Return

Motordown21

banksel PORTD  
MOVLW 0x03
MOVWF PORTD 
S1
BTFSS PORTB,4
Goto S1

Return

Temporisation
banksel Temp 
B1
INCFSZ Temp ,1
goto B1  
INCFSZ Temp+1 , 1
goto B1 
RETURN 



delay
call Temporisation 
Call Temporisation
call Temporisation 
Call Temporisation
Return




Alert
banksel PORTE
BSF PORTE,0
Call delay
BCF PORTE,0
Call delay
Return



UrgLed
BANKSEL PORTA
MOVLW 0x04 
MOVWF PORTA
call delay 
CLRF PORTA
call delay
return


Urgence
A1
Call Alert
Call UrgLed
Banksel PORTB 
BTFSS PORTB , 4
goto A1
Banksel INTCON 
BCF INTCON , 1 
RETFIE 


SounDelay 
banksel Svar
Movlw D'255'
MOVWF Svar 
E1
DECFSZ Temp ,1
goto E1  
Return

END