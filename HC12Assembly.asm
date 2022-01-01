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
            XDEF SCI_init, readValue, readN, char2Str, addValue
            
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
String      ds.b 5
Sum         ds.b 1

; code section
MyCode:     SECTION
main:
_Startup:
Entry:
SCI_init:   LDAA  #$4c
            STAA  SCICR1
            LDAA  #$0c
            STAA  SCICR2
            LDAA  #52
            STAA  SCIBDL
            RTS 
                        
readN:      BRCLR SCISR1, #$20, readN
            TFR D,X
            LDAB  SCIDRL
            SUBB Zero                     
            STAB 0,X                     
            RTS
             
readValue:  TFR D,X
            LDD #0
            LDAB 4,SP
            TFR D,Y                      ;puts N into Y            
anotherOne: LDAB #0
nextChar:   BRCLR SCISR1, #$20, nextChar  ;keeps scanning data port until there is a value entered.    
            CMPB #0                       ;if B is zero this is the first value so load into A and read next digit, otherwise 
            BNE next                      ;multiply A by 10 (makes it tens place or hundreds) then add value in data port.
            LDAB SCIDRL
            SUBB Zero                     ;turns char into decimal
            BRA nextChar
next:       LDAA SCIDRL                   ;load data port into A to compare with Enter (if it's enter all digits have been entered, subroutine ends)
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
return:     STAB 0,X                ;stores the final value in X which is address of Array
            INX                     ;next address
            DEY                     ;N-1
            CPY #0                  ;if N=0 no more values to enter so RTS                   
            BEQ endValues                      
            BRA anotherOne
endValues:  RTS
                           
addValue:   TFR D,X                ;puts address of array into X
            LDD #0
            LDAB 4,SP              ;puts N into B                 
add:        ADDA 0,X               ;add first value in array to A
            INX                    ;address of array +1 (next value)
            DECB                   ;N-1
            CMPB #0                ;if N=0 done adding, store sum and RTS
            BEQ done
            BRA add
done:       STAA 15,SP
            RTS
            
char2Str:   TFR D,Y                ;Puts address of string into Y
            LDAB 15,SP             ;Puts sum into B           
            LDAA #0
            CMPB #100
            BGE threeDigits
            CMPB #10
            BGE twoDigits
            BRA oneDigit
threeDigits:LDX #100
            IDIV
            PSHD
            TFR X,D
            ADDD #$30
            STAB 0,Y
            PULD
            LDX #10
            IDIV
            PSHD
            TFR X,D
            ADDD #$30
            STAB 1,Y
            PULD
            ADDD #$30
            STAB 2,Y
            LDAB #$0a
            STAB 3,Y
            BRA writeStr
twoDigits:  LDX #10
            IDIV
            PSHD
            TFR X,D           
            ADDD #$30
            STAB 0,Y
            PULD
            ADDD #$30
            STAB 1,Y
            LDAB #$0a
            STAB 2,Y
            BRA writeStr
oneDigit    ADDD #$30
            STAB 0,Y
            LDAB #$0a
            STAB 1,Y
writeStr:   LDAB  0,Y
            CMPB  #$0
            BEQ   complete
loop3:      BRCLR SCISR1, #$80, loop3        
            STAB  SCIDRL
            INY  
            BRA   writeStr
complete:   RTS
