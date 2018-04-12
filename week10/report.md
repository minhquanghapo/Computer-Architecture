>>>>>>>> `Hoàng Minh Quang`

>>>>>>>> `MSSV` `20152945`
# Week 10
### Assignment 1: Create a new project, type in, and build the program of Home Assignment 1. Show different values on LED.

` Source `
```
.eqv SEVENSEG_LEFT 0xFFFF0010

.eqv SEVENSEG_RIGHT 0xFFFF0011

.text

main:
	li $a0, 0x86
	jal SHOW_7SEG_LEFT
	li $a0, 0x86
	jal SHOW_7SEG_RIGHT
exit:
	li $v0, 10
	syscall
endmain:

SHOW_7SEG_LEFT:
	li $t0, SEVENSEG_LEFT
	sb $a0, 0($t0)
	jr $ra

SHOW_7SEG_RIGHT:
	li $t0, SEVENSEG_RIGHT
	sb $a0, 0($t0)
	jr $ra
```

### Assignment 2 Create a new project, type in, and build the program of Home Assignment 2. Draw something.

` Source `
```asm
.eqv MONITOR_SCREEN 0x10010000
.eqv RED 0x00FF0000
.eqv GREEN 0x0000FF00
.eqv BLUE 0x000000FF
.eqv WHITE 0x00FFFFFF
.eqv YELLOW 0x00FFFF00

.text
	li $k0, MONITOR_SCREEN
	
	
	li $t0, GREEN
	sw $t0, 76($k0)
	
	li $t0, BLUE
	sw $t0, 108($k0)
	
	li $t0, WHITE
	sw $t0, 12($k0)

	li $t0, YELLOW
	sw $t0, 44($k0)
```

### Assignment 3 Create a new project, type in, and build the program of Home Assignment 3. Make the Bot run and draw a triangle by tracking.

`Source`

```asm
.eqv HEADING 0xffff8010 	# Integer: An angle between 0 and 359
				# 0 : North (up)
				# 90: East (right)
				# 180: South (down)
				# 270: West (left)

.eqv MOVING 0xffff8050 		# Boolean: whether or not to move
.eqv LEAVETRACK 0xffff8020 	# Boolean (0 or non-0):
				# whether or not to leave a track
.eqv WHEREX 0xffff8030 		# Integer: Current x-location of MarsBot
.eqv WHEREY 0xffff8040 # Integer: Current y-location of MarsBot
.text
main: 
	jal TRACK # draw track line
	addi $a0, $zero, 90 # Marsbot rotates 90* and start running
	jal ROTATE
	jal GO
sleep1: 
	addi $v0,$zero,32 # Keep running by sleeping in 1000 ms
	li $a0,2000
	syscall

	jal UNTRACK # keep old track
	jal TRACK # and draw new track line
goDOWN: 
	addi $a0, $zero, 180 # Marsbot rotates 180*
	jal ROTATE

sleep2: 
	addi $v0,$zero,32 # Keep running by sleeping in 2000 ms
	li $a0,2000
	syscall
	jal UNTRACK # keep old track
	jal TRACK # and draw new track line
goDOWNRIGHT: 
	addi $a0, $zero, 135 # Marsbot rotates 270*
	jal ROTATE

sleep3: 
	addi $v0,$zero,32 # Keep running by sleeping in 1000 ms
	li $a0,5000
	syscall
	jal UNTRACK # keep old track
	jal TRACK # and draw new track line

goUPRIGHT:
	addi $a0, $zero, 45 # Marsbot rotates 120*
	jal ROTATE

sleep4: 
	addi $v0,$zero,32 # Keep running by sleeping in 2000 ms
	li $a0,5000
	syscall

	jal UNTRACK # keep old track
	jal TRACK # and draw new track line
goLEFT:
	addi $a0, $zero, 270 # Marsbot rotates 120*
	jal ROTATE

sleep5: 
	addi $v0,$zero,32 # Keep running by sleeping in 2000 ms
	li $a0,5000
	syscall

	jal UNTRACK # keep old track
	jal TRACK # and draw new track line


end_main:

#-----------------------------------------------------------
# GO procedure, to start running
# param[in] none
#-----------------------------------------------------------
GO: 
	li $at, MOVING # change MOVING port
	addi $k0, $zero,1 # to logic 1,
	sb $k0, 0($at) # to start running
	jr $ra
#-----------------------------------------------------------
# STOP procedure, to stop running
# param[in] none
#-----------------------------------------------------------
STOP: 
	li $at, MOVING # change MOVING port to 0
	sb $zero, 0($at) # to stop
	jr $ra
#-----------------------------------------------------------
# TRACK procedure, to start drawing line
# param[in] none
#-----------------------------------------------------------
TRACK: 
	li $at, LEAVETRACK # change LEAVETRACK port
	addi $k0, $zero,1 # to logic 1,
	sb $k0, 0($at) # to start tracking
	jr $ra

#-----------------------------------------------------------
# UNTRACK procedure, to stop drawing line
# param[in] none
#-----------------------------------------------------------
UNTRACK:
	li $at, LEAVETRACK # change LEAVETRACK port to 0
	sb $zero, 0($at) # to stop drawing tail
	jr $ra
#-----------------------------------------------------------
# ROTATE procedure, to rotate the robot
# param[in] $a0, An angle between 0 and 359
# 0 : North (up)
# 90: East (right)
# 180: South (down)
# 270: West (left)
#-----------------------------------------------------------
ROTATE: 
	li $at, HEADING # change HEADING port
	sw $a0, 0($at) # to rotate robot
	jr $ra

```

### Assignment 4 Create a new project, type in, and build the program of Home Assignment 4. Read key char and terminate the application when receiving “exit” command.
`Source`
```asm
.eqv KEY_CODE 0xFFFF0004 	# ASCII code from keyboard, 1 byte
.eqv KEY_READY 0xFFFF0000 	# =1 if has a new keycode ?
 				# Auto clear after lw
.eqv DISPLAY_CODE 0xFFFF000C 	# ASCII code to show, 1 byte
.eqv DISPLAY_READY 0xFFFF0008 	# =1 if the display has already to do
 				# Auto clear after sw
.text
 li $k0, KEY_CODE
 li $k1, KEY_READY

 li $s0, DISPLAY_CODE
 li $s1, DISPLAY_READY
loop: nop

WaitForKey:
 lw $t1, 0($k1) 		# $t1 = [$k1] = KEY_READY
 beq $t1, $zero, WaitForKey 	# if $t1 == 0 then Polling

ReadKey: 
 lw $t0, 0($k0) 		# $t0 = [$k0] = KEY_CODE
WaitForDis: 
 lw $t2, 0($s1) 		# $t2 = [$s1] = DISPLAY_READY
 beq $t2, $zero, WaitForDis 	# if $t2 == 0 then Polling

ShowKey:
 sw $t0, 0($s0) 		# show key
 nop
 
CheckExit:
 beq $t0, 101, to_state_1
 beq $t0, 120, to_state_2
 beq $t0, 105, to_state_3
 beq $t0, 116, finish
to_state_0:			# state 0: wait e
 add $t3, $zero, $zero
 j continue
to_state_1:			# state 1: wait x
 bne $t3, 0, to_state_0		
 add $t3, $t3, 1
 j continue
to_state_2:			# state 2: wait i
 bne $t3, 1, to_state_0
 add $t3, $t3, 1
 j continue
to_state_3:			# state 0: wait t
 bne $t3, 2, to_state_0		
 add $t3, $t3, 1
 j continue
finish:
 bne $t3, 3, to_state_0	
 j exit
continue:
 j loop
 
exit:
 li $v0, 10
 syscall
```