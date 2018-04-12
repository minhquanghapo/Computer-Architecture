Báo cáo thực hành tuần 3


# Laboratory Exercise 3, Home Assignment 1
#### Asignment 1: Create a new project to implement the code in Home Assignment 1Home Assignment . Initialize for i and j variable. Compile and upload to the simulator. Run this program step by step, observe the changing of memory and the content of registers at each step. 

```
start:
slt 	$t0,$s2,$s1 		# j<i
bne	 $t0,$zero,else 		# branch to else if j<i
addi	 $t1,$t1,1 		# then part: x=x+1
addi 	$t3,$zero,1 		# z=1 
j 	endif 			# skip “else” part
else:
 addi 	$t2,$t2,-1 		# begin else part: y=y-1
add $t3,$t3,$t3 			# z=2*z 
endif:
```

Trường hợp 1: i < j
	li $s1, 1
	li $s2, 2
Khởi tạo i = 1, j = 2
Sau lệnh slt $t0,$s2,$s1 thì $t0 = 0 do i < j
Sau lệnh bne $t0,$zero,else thì nhảy xuống lệnh addi $t1,$t1,1
Sau lệnh addi $t1,$t1,1 thì $t1 = 1
Sau lệnh addi $t3,$zero,1 thì $t3 = 1
Trường hợp 2: i > j
li $s1, 2
	li $s2, 1
Khởi tạo i = 2, j = 1
Sau lệnh slt $t0,$s2,$s1 thì $t0 = 1 do i < j
Sau lệnh bne $t0,$zero,else thì nhảy xuống lệnh addi $t2,$t2,-1
Sau lệnh addi $t2,$t2,-1 thì $t2 = -1
Sau lệnh add $t3,$t3,$t3 thì $t3 = 0

#### Assignment 2: Create a new project implementing the code in Home Assignment 2. Initialize for i, n, step, sum variables and array A. Compile and upload to the simulator. Run this program step by step, observe the changing of memory and the content of registers by each step. Try to test with some more cases (change the value of variables).
```
#Laboratory 3, Home Assigment 2 
.text 
loop: 
add 	$s1,$s1,$s4 		#i=i+step 
add	$t1,$s1,$s1 		#t1=2*s1 
add 	$t1,$t1,$t1 		#t1=4*s1 
add 	$t1,$t1,$s2 		#t1 store the address of A[i]
lw 	$t0,0($t1) 		#load value of A[i] in $t0 
add 	$s5,$s5,$t0		#sum=sum+A[i] 
bne 	$s1,$s3,loop 		#if i != n, goto loop
```
Sau các khởi tạo thì $s1 = -1, $s4 = 1, $s3 = 5, $s2 = 268500992, $s5 = 0
Sau lệnh add $s1,$s1,$s4 thì $s1 = 0
Sau lệnh add $t1,$s1,$s1 thì $t1 = 0
Sau lệnh add $t1,$t1,$t1 thì $t1 = 0
Sau lệnh add $t1,$t1,$s2 thì $t1 = 268500992
Sau lệnh lw $t0,0($t1) thì $t0 = 1 là phần tử đầu tiên của mảng A
Sau lệnh add $s5,$s5,$t0 thì $s5 = 1
Sau lệnh bne $s1,$s3,loop thì lại trở lại vòng lặp do $s1 != $s3 (0 != 5)
Vòng lặp sẽ chạy 6 lần kết quả cuối là $s5 = 21 (sum = 21)

#### Assignment 3: Create a new project implementing the code in
##### Home Assignment 3Home Assignment . Compile and upload to the simulator. Run this program step by step; observe the changing of memory and the content of registers by each step. Change the value of test variable and run this program some times to check all cases.

```
#Laboratory Exercise 3, Home Assignment 3 
.data 
test: .word 1 
.text 
la 	$s0,test 		#load the address of test variable 
lw 	$s1,0($s0) 		#load the value of test to register $t1 
li 	$t0,0 			#load value for test case 
li 	$t1,1 li $t2,2 
beq	$s1,$t0,case_0 
beq 	$s1,$t1,case_1 
beq 	$s1,$t2,case_2 
b 	default 
case_0: 
addi 	$s2,$s2,1 		#a=a+1 
b 	continue 
case_1:
 	sub 	$s2,$s2,$t1 		#a=a-1 
b 	continue 
case_2: 
	add 	$s3,$s3,$s3 		#b=2*b 
	b 	continue 
default: continue:
```
Giải thích câu lệnh:
beq nhảy đến nhánh nếu 2 đầu vào bằng nhau.
Sự thay đổi bộ nhớ:
Do $s1 = 1 = $t1 nên chương trình nhảy vào nhánh case_1.
case_1 thực hiện a=a-1, $s2 bị giảm đi 1 đơn vị.


#### Assignment 4: Modify the Assignment 1, so that the condition tested is
a. i <j
![](/assign-image/1.png)

b. i >= j
![](/assign-image/2.png)

c. i+j <= 0

![](/assign-image/3.png)
d. i+j > m+n
![](/assign-image/4.png)

#### Assignment 5

Modify the Assignment 2, so that the condition tested at the end of the loop is
a. i < n

![](/assign-image/5.png)
b. i <= n
![](/assign-image/6.png)
c. sum >= 0
![](/assign-image/7.png)
d. A[i] == 0
![](/assign-image/8.png)

#### Assignment 6: Using all of above instructions and statements, create a new project to implement
this function: find the element with the largest absolute value in a list of integers.
Assuming that this list is store in an integer array and we know the number of elements in it.

![](/assign-image/9.png)
