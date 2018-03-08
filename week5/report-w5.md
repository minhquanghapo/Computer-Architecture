WEEK 5
Assignment 1: Create a new project to implement the program in Home Assignment 1. Compile and upload to simulator. Run and observe the result. Go to data memory section, check how test string are stored and packed in memory. 
```
#Laboratory Exercise 5, Home Assignment 1 
#Laboratory Exercise 5, Home Assignment 1 
.data 
test: .asciiz "Hello World" 
.text    li  $v0, 4    
la  $a0, test    
syscall
```


Assignment 2: Create a new project to print the sum of two register $s0 and $s1 according to this format:  “The sum of (s0) and (s1) is (result)” 
```
.data
t1: .asciiz "\nThe sum of ("
t2: .asciiz ") and ("
t3: .asciiz ") is ("
t4: .asciiz ")\n"

.text 
    li $s0, 8000        # $s0 = 8000
    li $s1, 3       	# $s1 = 3
    add $s2, $s0, $s1   # $s2 = $s1 + $s0
    
    li $v0, 4
    la $a0, t1
    syscall
    
    li $v0, 1
    add $a0,$zero, $s0 
    syscall         	# print $s0
    
    li $v0, 4
    la $a0, t2
    syscall
    
    li $v0, 1
    add $a0,$zero, $s1
    syscall         	# print $s1
    
    li $v0, 4
    la $a0, t3
    syscall         
    
    li $v0, 1
    add $a0,$zero, $s2
    syscall         	# print $s2
    
    li $v0, 4
    la $a0, t4
    syscall

```
Assignment 3: Create a new project to implement the program in Home Assignment 2. Add more instructions to assign a test string for y variable, and implement strcpy function. Compile and upload to simulator. Run and observe the result. 
#Laboratory Exercise 5, Home Assignment 2 
```
.data 
y: .asciiz "Hello"                 # source string y 
x: .space 1000                     # destination string x, empty 
.text 

    la $a1, y
    la $a0, x

strcpy:  
    add $s0,$zero,$zero             #s0 = i=0 
L1:  
    add $t1,$s0,$a1             #t1 = s0 + a1 = i + y[0]                                     
                    #   = address of y[i]  
    lb $t2,0($t1)               #t2 = value at t1 = y[i]  
    add $t3,$s0,$a0                 #t3 = s0 + a0 = i + x[0]                                      
                    #   = address of x[i]  
    sb $t2,0($t3)               #x[i]= t2 = y[i]  
    beq $t2,$zero,end_of_strcpy     #if y[i]==0, exit  
    nop 

 
    addi $s0,$s0,1                  #s0=s0 + 1 <-> i=i+1  
    j L1                        #next character  
    nop 
end_of_strcpy:

```
Assignment 4: Accomplish the Home Assignment 3 with syscall function to get a string from dialog, and show the length to message dialog. 
#Laboratory Exercise 5, Home Assignment 3 
```
.data 
    string:     .space   50 
    Message1:       .asciiz "Nhap xau:" 
    Message2:   .asciiz "Do dai la " 
.text 
main: 
get_string:   
    la $a0, Message1
    la $a1, string
    la $a2, 49
    li $v0, 54
    syscall
            
get_length:   
    la   $a0, string        # a0 = Address(string[0])               
    xor  $v0, $zero, $zero  # v0 = length = 0               
    xor  $t0, $zero, $zero  # t0 = i = 0 
check_char:   
    add  $t1, $a0, $t0      # t1 = a0 + t0                                          
                #= Address(string[0]+i)                
    lb   $t2, 0($t1)        # t2 = string[i]               
    beq  $t2,$zero,end_of_str # Is null char?                      
    addi $v0, $v0, 1          # v0=v0+1->length=length+1               
    addi $t0, $t0, 1          # t0=t0+1->i = i + 1               
    j    check_char 
end_of_str:
    addi $v0, $v0, -1                              
end_of_get_length:
     

print_length: 
    la $a0, Message2
    add $a1, $zero, $v0
    li $v0, 56
    syscall
```
 

Assignment 5: Write a program that let user input a string. Input process will be terminated when user press Enter or then length of the string exceed 20 characters. Print the reverse string. 
```
.data
buffer: .space 50

.text
    li $s6, 20  # Max length
    li $s7, 10  # ASCII code of '\n'
    
    la $s0, buffer  # Load buffer
    li $s1, 0   # index = 0
    li $s3, 0   # i = 0
start_read_char:
    li $v0, 12
    syscall     # Read char
    
    add $s1, $s0, $s3   # Load buffer[i]
    addi $s3, $s3, 1    # i++
    beq $s3, $s6, end_read_char #   exit when max length
    beq $v0, $s7, end_read_char #   exit when enter
    sb $v0, 0($s1)
    j start_read_char
end_read_char:

Print_the_reverse_string:
    li $v0, 11
    lb $a0, 0($s1)
    syscall
    beq $s1, $s0, exit
    addi $s1, $s1, -1
    j Print_the_reverse_string
exit:
```
##Conclusions: Before you pass the laboratory exercise, think about the questions below: 

> What the difference between the string in C and Java?
String in C is Array terminated with a NUL (\0) character. But, in Java strings are instances (objects) of the java.lang.String class, you can not use them as array.
In C, with 8 bytes, how many characters that we can store? 
Chars in C are typically (not always) 8-bit
In Java, with 8 bytes, how many characters that we can store?
Java chars are 16-bits (always).
