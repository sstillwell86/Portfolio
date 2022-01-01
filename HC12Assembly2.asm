;**************************************************************
;* This stationery serves as the framework for a              *
;* user application. For a more comprehensive program that    *
;* demonstrates the more advanced functionality of this       *
;* processor, please see the demonstration applications       *
;* located in the examples subdirectory of the                *
;* Freescale CodeWarrior for the HC12 Program directory       *
;**************************************************************
; Include derivative-specific definitions
            INCLUDE 'derivative.inc'

; export symbols
            XDEF Entry, _Startup, main
            ; we use export 'Entry' as symbol. This allows us to
            ; reference 'Entry' either in the linker .prm file
            ; or from C/C++ later on

            XREF __SEG_END_SSTACK      ; symbol defined by the linker for the end of the stack
; Constant Data Section
DATA: SECTION
Enter       dc.b $0d
Zero        dc.b $30


; variable/data section
MY_EXTENDED_RAM: SECTION
; Insert here your data definition.
N           ds.b 1
Array       ds.b 5
Sum         ds.b 1

; code section
MyCode:     SECTION
main:
_Startup:
Entry:
            LDS  #__SEG_END_SSTACK
            JSR SCI_init
            LDX #N
            PSHX
            JSR readN
            LEAS 2, SP
            LDAB N
            LDY #0
            ABY
            LDX #Array
            PSHX                          ;puts X (Address of Array) onto stack
            JSR readValue                 ;first call
            LEAS 2, SP
            DEY
moreValues: INX
            PSHX                          ;passes Array+1 to subroutine (which now stores next value at Array+1)
            JSR readValue                 ;2nd call
            LEAS 2, SP
            DEY
            CPY #0                       ;if N is zero now, we're done
            BEQ addValues
            BRA moreValues                ;else inc X for next Array address and call subroutine again
addValues:  LDAB N
            PSHB
            LDX #Array
            PSHX
            LEAS -1, SP
            JSR addValue
            LDAB 0,SP
            LEAS 4,SP
endLoop:    BRA endLoop                          
readN:      BRCLR SCISR1, #$20, readN
            LDAB  SCIDRL
            SUBB Zero
            LDX 2,SP                     
            STAB 0,X                     
            RTS 
readValue:  LDAB #0
nextChar:   BRCLR SCISR1, #$20, nextChar  ;keeps scanning data port until there is a value entered.    
            CMPB #0                       ;if A is zero this is the first value so load into A and read next digit, otherwise 
            BNE next                      ;multiply A by 10 (makes it tens place or hundreds) then add value in data port.
            LDAB SCIDRL
            SUBB Zero                     ;turns char into decimal
            BRA nextChar
next:       LDAA SCIDRL                   ;load data port into B to compare with Enter (if it's enter all digits have been entered, subroutine ends)
            CMPA Enter
            BEQ return
            LDAA #10                      ;can only MUL A x B and store in B so load 10 into B and multiply then add data port value
            MUL
            LDAA  SCIDRL
            SUBA Zero
            ABA                           ;adds B and A and stores in A (if entered digits were 13 then 1*10+3=13
            LDAB #1                       ;moves A into B by loading 1 into B and using MUL which stores result in B
            MUL                           
            BRA nextChar                          
return:     LDX 2,SP                      ;ERROR more than 2 digits it stores $0D every time
            STAB 0,X                      ;stores the final value in X which is address of Array
            RTS               
SCI_init:   LDAA  #$4c
            STAA  SCICR1
            LDAA  #$0c
            STAA  SCICR2
            LDAA  #52
            STAA  SCIBDL
            RTS
addValue:   LDD #0
            LDAB 5,SP                     
            LDX 3,SP           
add:        ADDA 0,X
            INX
            DECB            
            CMPB #0
            BEQ done
            BRA add
done:       STAA 2,SP
            RTS     
            
                                