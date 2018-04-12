# Report Week 1
### I. Assignment 1
#### Chương trình
```
#Laboratory Exercise 2, Assignment 1
.text
addi $s0, $zero, 0x3007 # $s0 = 0 + 0x3007 = 0x3007 ;I-type
add $s0, $zero, $0
# $s0 = 0 + 0 = 0 ;R-type
```
#### Sự thay đổi của thanh ghi `$s0`
- Sau lệnh thứ nhất:
```
$s0 lưu giá trị 0x3307
```
- Sau lệnh thứ 2:
```
$s0 lưu giá trị 0x0000
```
#### Sự thay đổi của thanh ghi `$pc`
- Sau lệnh thứ nhất
```
$pc lưu giá trị 0x00400004
```
- Sau lệnh thứ 2
```
$pc lưu giá trị 0x00400008
```
#### Mã máy
- Lệnh thứ nhất `addi $s0, $zero, 0x3007 # $s0 = 0 + 0x3007 = 0x3007 ;I-type`
```
Mã máy: 0010 0000 0001 0000 0011 0000 0000 0111
```
- Khuôn dạng lệnh thứ nhất:
```
op: 0010 00
rs: 00 000
rt: 1 0000
operand/offset: 0011 0000 0000 0111 (0x3007)
=> Đúng khuôn dạng.
```
- Lệnh thứ 2: `add $s0, $zero, $0 #R type`
```
Mã máy: 0000 0000 0000 0000 1000 0000 0010 0000
```
- Khuôn dạng lệnh thứ 2
```
op: 0000 00
rs: 00 000
rt: 0 0000
rd: 1000 0
sh: 000 00
fn: 10 0000
=> Đúng khuôn dạng.
```

#### Thay đổi lệnh thành 
`addi $s0, $zero, 0x2110003d`
- Khi biên dịch tạo ra 3 lệnh mới:
```
lui $1, 0x00002110
ori $1, $1, 0x0000003d
add $16, $0, $1
```
- Giải thích
> Vì `addi` chỉ thực hiện cộng `16bit` nên khi ta tính toán số `32 bit` thì sẽ tách ra làm 3 lệnh. Thực hiện lệnh gán $1 với lệnh `lui` sau đó thực hiện với lệnh ori để thanh ghi `$1` lưu giá trị `0x2110003d`. Sau đó thực hiện lệnh add để lưu giá trị vào thanh ghi `$16` hay còn gọi là `$s0`

### II. Assignment 2: Lệnh gán số 32 bit
#### Chương trình:
```
#Laboratory Exercise 2, Assignment 2
.text
lui $s0,0x2110 #put upper half of pattern in $s0
ori $s0,0x003d #put lower half of pattern in $s0
```
#### Sự thay đổi trên thanh ghi `$s0`
- Sau lệnh `lui $s0,0x2110`
```
$s0 sẽ lưu giá trị 0x21100000
```
- Sau lệnh `ori $s0,0x003d`
```
$s0 sẽ lưu giá trị 0x2110003d
```
#### Sự thay đổi trên thanh ghi `$pc`
- Sau lệnh `lui $s0,0x2110`
```
$p0 lưu giá trị 0x00400004
```
- Sau lệnh `ori $s0,0x003d`
```
$p0 lưu giá trị 0x00400008
```
#### Vùng lệnh .text
- Ở `Data Segment` khi click vào hộp combo ta thấy 
```
0x00400000(.text)
```
=> Các byte đầu trùng với các byte đầu trên cột Address trên `Text Segment`

### III. Assignment 3: Lệnh gán(giả lệnh)

#### Chương trình: 
```
#Laboratory Exercise 2, Assignment 3
.text
li $s0,0x2110003d #pseudo instruction=2 basic instructions
li $s1,0x2 #but if the immediate value is small, one ins
```

#### Biên dịch
> Khi biên dịch lệnh đầu tiên `li $s0,0x2110003d` sẽ được biên dịch thành 2 lệnh `lui $1, 0x00002110` và `ori $16, $1, 0x0000003d`
> Lệnh thứ 2 `li $s1,0x2` được biên dịch thành `addiu $17, $0, 0x00000002`

#### Giải thích
> Vì lệnh `li` chỉ để gán gía trị `32bit` nên câu lệnh thứ nhất phải tách làm hai. Đầu tiên thực hiện dùng câu lệnh `lui` để gán tạm thời giá trị `0x00002110` vào thanh ghi `$1` sau đó dùng lệnh `ori` để gán giá trị  `0x2110003d` bằng cách thay `4byte` giá trị thấp của tham số trước vào `4byte` giá trị cao của tham số sau vào thanh ghi $16
> Lệnh thứ 2 `0x2` là `4bit` là lệnh gán có thể thực hiện `addiu $17, $0, 0x00000002` vì `li` là giả lệnh thực chất phép toán gán là phét toán cộng với tham số là $0

### IV. Tính biểu thức `2x + y = ? `
#### Chương trình
```
#Laboratory Exercise 2, Assignment 4
.text
# Assign X, Y
addi $t1, $zero, 5 # X = $t1 = ?
addi $t2, $zero, -1 # Y = $t2 = ?
# Expression Z = 2X + Y
add $s0, $t1, $t1 # $s0 = $t1 + $t1 = X + X = 2X
add $s0, $s0, $t2 # $s0 = $s0 + $t2 = 2X + Y
```
#### Quan sát sự thay đổi
- Lệnh `addi $t1, $zero, 5`: 
> Thanh ghi $t1 được gán giá trị là `0x00000005` các thanh ghi khác không thay đổi.
- Lệnh `addi $t2, $zero, -1`
> Thanh ghi $t2 được gán giá trị `0xffffffff` các thanh ghi khác không thay đổi.
- Lệnh `add $s0, $t1, $t1`
> Thanh ghi $s0 lưu giá trị `0x0000000a` các thanh ghi khác không thay đổi.
- Lệnh `add $s0, $s0, $t2`
> Thanh ghi $s0 lưu giá trị `0x00000009` các thanh ghi khác không thay đổi.

**=> Kết quả ra đúng so với yêu cầu. (2*5 - 1 = 9) **

#### Kiểm tra mã máy
- Lệnh `addi`: `addi $t1, $zero, 5` và `addi $t2, $zero`
> Vì 2 lệnh tương đương nên ta chỉ xét một lệnh: `addi $t1, $zero, 5` 
>> Mã máy: `0010 0000 0000 1001 0000 0000 0000 0101`
>> Khuôn dạng: 
>>> 
op: 0010 00
rs: 00 000
rt: 0 1001
operand/offset : 0000 0000 0000 0101 (=5)



**=> Kết quả đúng khuôn dạng.**

- Lệnh `add`: `add $s0, $t1, $t1` và `add $s0, $s0, $t2`
> Vì 2 lệnh tương đương nên ta chỉ xét một lệnh: `add $s0, $t1, $t1` 
>> Mã máy: `0000 0001 0010 1001 1000 0000 0010 0000`
>> Khuôn dạng: 
>>>
op: 0000 00
rs: 01 001
rt: 0 1001
rd: 1000 0
sh: 000 00
fn: 10 0000

**=> Kết quả đúng**

### V. Phép nhân.

#### Chương trình:
```
#Laboratory Exercise 2, Assignment 5
.text
# Assign X, Y
addi $t1, $zero, 4 # X = $t1 = ?
addi $t2, $zero, 5 # Y = $t2 = ?
# Expression Z = 3*XY
mul $s0, $t1, $t2
# HI-LO = $t1 * $t2 = X * Y
mul $s0, $s0, 3
# $s0 = $s0 * 3 = 3 * X * Y
# Z' = Z
mflo $s1
```
#### Điều bất thường: 
> - Câu lệnh `mul $s0, $s0, 3` trong source được chuyển thành 2 câu lệnh `addi $1, $0, 0x00000003` và `mul $16, 16, $s1`
> - Giải thích: 
>> Do lệnh `mul` basic yêu cầu toán hạng là 2 thanh ghi, không chạy với hằng số nên hằng số sẽ được lưu vào thanh ghi `$1` trước khi thực hiện nhân thanh ghi `$1` với `$s0`.


#### Sự thay đổi giá trị trong thanh ghi
> - Thanh ghi `hi` luôn bằng 0, thanh ghi lo thay đổi giá trị và luôn bằng `$s0` bằng kết quả phép nhân.
> - Kết quả chính xác, sau phép nhân `mul $s0, $t1, $t2`, giá trị `$s0 = 20` sau phép nhân `mul $s0, $s0, 3` giá trị `$s0 = 60`.

### VI. Tạo biến và truy cập biến

#### Chương trình
```
#Laboratory Exercise 2, Assignment 5 
.data                      
# DECLARE VARIABLES 
X :  .word    5       # Variable X, word type, init value =  5
Y :  .word   -1            # Variable Y, word type, init value =  -1
Z :  .word                 # Variable Z, word type, no init value 
 
.text                      
# DECLARE INSTRUCTIONS       
#  Load X, Y to registers      
la    $t8, X           # Get the address of X in Data Segment      
la    $t9, Y           # Get the address of Y in Data Segment      
lw    $t1, 0($t8)      # $t1 = X      
lw    $t2, 0($t9)      # $t2 = Y  
 
#  Calcuate the expression Z = 2X + Y with registers only      
add   $s0, $t1, $t1    # $s0 = $t1 + $t1 = X + X = 2X       
add   $s0, $s0, $t2    # $s0 = $s0 + $t2 = 2X + Y 
 
# Store result from register to variable Z      
la    $t7, Z           # Get the address of Z in Data Segment           
sw    $s0, 0($t7)      # Z = $s0 = 2X + Y

```
#### Biên dịch
> -  Lệnh `la `được biên dịch thành 2 lệnh `lui` và `ori`
> - Địa chỉ của mỗi biến được tách làm 2 phần `16 bit` cao và `16 bit` thấp mỗi phần tương ứng với hằng số truyền vào lệnh la sau biên dịch 16 bit cao cho lệnh `lui`, 16 bit thấp cho lệnh `ori`.
> - Giá trị khởi tạo `X = 5; Y = -1; Z = 0` **Đảm bảo đúng giá trị khởi tạo mong muốn.**

#### Sự thay đổi giá trị của các thanh ghi:
```
$at: 0 -> 0x10010000 -> 0x10010000 -> 0x10010000 -> 0x10010000
$t8: 0 -> 0x00000000 -> 0x10010000
$t9: 0 -> 0x00000000 -> 0x00000000 -> 0x00000000 -> 0x10010004
$t1: 0 -> 0 -> 0 -> 0 -> 0 -> 5
$t1: 0 -> 0 -> 0 -> 0 -> 0 -> 0 -> -1
$s0: 0 -> … -> 10 -> 9 
$t7: 0 -> .. -> 0x10010008

```
- Vai trò
>
 `lw`: load giá trị từ bộ nhớ chính vào thanh ghi
 `sw`: lưu giá trị từ thanh ghi sang bộ nhớ chính 
 
 
 End.
 
