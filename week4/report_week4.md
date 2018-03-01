# Report week4
### Assignment 1 : 
*Create a new project to implement the Home Assigment 1. Compile and upload to simulator. Initialize two operands (register $s1 and $s2), run this program step by step, observe memory and registers value*

**Resolve**
```
.text
li $s1,0x7fffffff #set s1 = greatest positive number 
li $s2,0x6fffffff #set s2 = positive number => result will be overflow
start:
li $t0,0 #No Overflow is default status
addu $s3,$s1,$s2 # s3 = s1 + s2
xor $t1,$s1,$s2 #Test if $s1 and $s2 have the same sign
bltz $t1,EXIT #If not, exit
slt $t2,$s3,$s1
bltz $s1,NEGATIVE #Test if $s1 and $s2 is negative?
beq $t2,$zero,EXIT #s1 and $s2 are positive
# if $s3 > $s1 then the result is not overflow
j OVERFLOW
NEGATIVE:
bne $t2,$zero,EXIT #s1 and $s2 are negative
# if $s3 < $s1 then the result is not overflow
OVERFLOW:
li $t0,1 #the result is overflow
EXIT:
```

### Assignment 2
*Write a program to do the following tasks:*

* Extract MSB of $s0 
* Clear LSB of $s0
* Set LSB of $s0 (bits 7 to 0 are set to 1)
* Clear $s0 (s0=0, must use logical instructions)
* MSB: Most Significant Byte 
* LSB: Least Significant Byte 

> s0 = 0x 1 2 3 4 5 6 7 8

**Resolve**
```
.text

#Extract MSB of $s0
li $s0,0x55555555
andi  $t0,$s0,0xff000000

#Clear LSB of $s0
li $s0,0x55555555
andi  $t0,$s0,0xffffff00

#set LSB to 1
li $s0,0x55555555
ori  $t0,$s0,0x000000ff

#sclear $s0
li $s0,0x55555555
andi  $t0,$s0,0
```

### Assignment 3
*Pseudo instructions in MIPS are not-directly- run-on- MIPS-
processor instructions which need to be converted to real-instructions of MIPS. Re-write the following pseudo instructions using real-instructions understood by MIPS processors:*


**Resolve**
```
#Abs
li $s1,0xfffffffe
bgtz $t0,POSITIVE
nop
xori $t1,$s1,0xffffffff
addi $s0,$t1,1
j END
#POSITIVE:
add $s0,$zero,$s1 
END:
#resutl is $s0

#Move
li $s1,1
add $s0,$zero,$s1

#Not
li $s1,1
nor $s0,$zero,$s1

#Ble
li $s1,3
li $s2,2
sgt $t0,$s1,$s2
beq $t0,$zero,L
nop
li $s3,3
#L:

```

### Assignment 4
*To dectect overflow in additional operation, we also use other rule than the one in Assignment 1. This rule is: when add two operands that have the same sign, overflow will occur if the sum doesn’t have the same sign with either operands. You need to use this rule to write another overflow detection program*

**Resolve**

```
.text
li $s1,0x7fffffff #set s1 = greatest positive number 
li $s2,0x6fffffff #set s2 = positive number => result will be overflow
start:
li $t0,0 #No Overflow is default status
addu $s3,$s1,$s2 # s3 = s1 + s2
xor $t1,$s1,$s2 #Test if $s1 and $s2 have the same sign
bltz $t1,EXIT #If not, exit
xor $t2,$s3,$s1 #if $s3 and $s1 have the same sign
bgtz $t2,EXIT #if not, over flow
li $t0,1 #the result is overflow
EXIT:
```

### Assignment 5
*Write a program that implement multiply by a small power of 2. (2, 4, 8, 16, etc for example).*

**Conclusions**
*Before you pass the laboratory exercise, think about the questions below:*

* What is the difference between SLLV and SLL instructions?
* What is the difference between SRLV and SRL instructions?

```
li $s0,4
sll $t0,$s0,1
```
*SLLV -- Shift left logical variable*
> * Description: Shifts a register value left by the value in a second register and places the result in
*a third register. Zeroes are shifted in.*
> * Operation: $d = $t << $s; advance_pc (4);
Syntax: sllv $d, $t, $s

*SLL -- Shift left logical*
> * Description: Shifts a register value left by the shift amount listed in the instruction and places
the result in a third register. Zeroes are shifted in.
> * Operation: $d = $t << h; advance_pc (4);
Syntax: sll $d, $t, h


# End

