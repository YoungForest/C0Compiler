# generate time: Mon Dec 05 02:32:16 2016
.data
array: .space 400
i: .word 0
j: .word 0
k: .word 0
ch: .word 0
set: .space 104
h: .word 0
yangsen_string0: .asciiz "The number of 'f*10' is:"
yangsen_string1: .asciiz "The first number you input is "
yangsen_string2: .asciiz "Its fibonacci is "
.text
move $fp, $sp
j end
func_2_number:   
sw $ra 0($sp) 
sw $fp -4($sp) 
move $fp $sp 
sw $v1 -8($sp) 
sw $a0 -12($sp) 
sw $a1 -16($sp) 
sw $a2 -20($sp) 
sw $a3 -24($sp) 
sw $t0 -28($sp) 
sw $t1 -32($sp) 
sw $t2 -36($sp) 
sw $t3 -40($sp) 
sw $t4 -44($sp) 
sw $t5 -48($sp) 
sw $t6 -52($sp) 
sw $t7 -56($sp) 
sw $s0 -60($sp) 
sw $s1 -64($sp) 
sw $s2 -68($sp) 
sw $s3 -72($sp) 
sw $s4 -76($sp) 
sw $s5 -80($sp) 
sw $s6 -84($sp) 
sw $s7 -88($sp) 
sw $t8 -92($sp) 
sw $t9 -96($sp) 
sw $k0 -100($sp) 
sw $k1 -104($sp) 
subi $sp $sp 108
subi $sp $sp 1000
li $t0 48 
sw $t0 -116($fp) 
lw $t1 -108($fp) 
mul $t0 $t1 10
sw $t0 -124($fp) 
lw $t1 -124($fp) 
lw $t2 -112($fp) 
add $t0 $t1 $t2
sw $t0 -128($fp) 
lw $t0 -128($fp) 
sw $t0 -120($fp) 
lw $v0 -120($fp) 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
putchar:   
sw $ra 0($sp) 
sw $fp -4($sp) 
move $fp $sp 
sw $v1 -8($sp) 
sw $a0 -12($sp) 
sw $a1 -16($sp) 
sw $a2 -20($sp) 
sw $a3 -24($sp) 
sw $t0 -28($sp) 
sw $t1 -32($sp) 
sw $t2 -36($sp) 
sw $t3 -40($sp) 
sw $t4 -44($sp) 
sw $t5 -48($sp) 
sw $t6 -52($sp) 
sw $t7 -56($sp) 
sw $s0 -60($sp) 
sw $s1 -64($sp) 
sw $s2 -68($sp) 
sw $s3 -72($sp) 
sw $s4 -76($sp) 
sw $s5 -80($sp) 
sw $s6 -84($sp) 
sw $s7 -88($sp) 
sw $t8 -92($sp) 
sw $t9 -96($sp) 
sw $k0 -100($sp) 
sw $k1 -104($sp) 
subi $sp $sp 108
subi $sp $sp 1000
lw $a0 -108($fp) 
li $v0 11 
syscall   
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
fibonacci:   
sw $ra 0($sp) 
sw $fp -4($sp) 
move $fp $sp 
sw $v1 -8($sp) 
sw $a0 -12($sp) 
sw $a1 -16($sp) 
sw $a2 -20($sp) 
sw $a3 -24($sp) 
sw $t0 -28($sp) 
sw $t1 -32($sp) 
sw $t2 -36($sp) 
sw $t3 -40($sp) 
sw $t4 -44($sp) 
sw $t5 -48($sp) 
sw $t6 -52($sp) 
sw $t7 -56($sp) 
sw $s0 -60($sp) 
sw $s1 -64($sp) 
sw $s2 -68($sp) 
sw $s3 -72($sp) 
sw $s4 -76($sp) 
sw $s5 -80($sp) 
sw $s6 -84($sp) 
sw $s7 -88($sp) 
sw $t8 -92($sp) 
sw $t9 -96($sp) 
sw $k0 -100($sp) 
sw $k1 -104($sp) 
subi $sp $sp 108
subi $sp $sp 1000
lw $t1 -108($fp) 
blt $t1 0 elsebegin0
lw $t1 -108($fp) 
bgt $t1 1 elsebegin1
li $v0 1 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
j ifend1  
elsebegin1:   
lw $t1 -108($fp) 
sub $t0 $t1 1
sw $t0 -112($fp) 
lw $t0 -112($fp) 
sw $t0 -108($sp) 
jal fibonacci  
sw $v0 -116($fp) 
lw $t1 -108($fp) 
sub $t0 $t1 2
sw $t0 -120($fp) 
lw $t0 -120($fp) 
sw $t0 -108($sp) 
jal fibonacci  
sw $v0 -124($fp) 
lw $t1 -116($fp) 
lw $t2 -124($fp) 
add $t0 $t1 $t2
sw $t0 -128($fp) 
lw $v0 -128($fp) 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
ifend1:   
j ifend0  
elsebegin0:   
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
ifend0:   
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
func:   
sw $ra 0($sp) 
sw $fp -4($sp) 
move $fp $sp 
sw $v1 -8($sp) 
sw $a0 -12($sp) 
sw $a1 -16($sp) 
sw $a2 -20($sp) 
sw $a3 -24($sp) 
sw $t0 -28($sp) 
sw $t1 -32($sp) 
sw $t2 -36($sp) 
sw $t3 -40($sp) 
sw $t4 -44($sp) 
sw $t5 -48($sp) 
sw $t6 -52($sp) 
sw $t7 -56($sp) 
sw $s0 -60($sp) 
sw $s1 -64($sp) 
sw $s2 -68($sp) 
sw $s3 -72($sp) 
sw $s4 -76($sp) 
sw $s5 -80($sp) 
sw $s6 -84($sp) 
sw $s7 -88($sp) 
sw $t8 -92($sp) 
sw $t9 -96($sp) 
sw $k0 -100($sp) 
sw $k1 -104($sp) 
subi $sp $sp 108
subi $sp $sp 1000
li $t0 100 
sw $t0 -120($fp) 
li $t0 40 
sw $t0 -112($fp) 
li $t0 20 
sw $t0 -116($fp) 
lw $t0 -112($fp) 
sw $t0 -108($sp) 
li $t0 20 
sw $t0 -112($sp) 
jal func_2_number  
sw $v0 -124($fp) 
lw $t1 -124($fp) 
neg $t0 $t1 
sw $t0 -128($fp) 
lw $t1 -128($fp) 
lw $t2 -116($fp) 
add $t0 $t1 $t2
sw $t0 -132($fp) 
lw $t1 -120($fp) 
lw $t2 -132($fp) 
mul $t0 $t1 $t2
sw $t0 -136($fp) 
lw $t1 -112($fp) 
lw $t2 -116($fp) 
div $t0 $t1 $t2
sw $t0 -140($fp) 
lw $t1 -136($fp) 
lw $t2 -140($fp) 
mul $t0 $t1 $t2
sw $t0 -144($fp) 
lw $a0 -144($fp) 
li $v0 1 
syscall   
li $t0 95 
sw $t0 -108($sp) 
jal putchar  
li $t0 47 
sw $t0 -108($fp) 
lw $t1 -108($fp) 
add $t0 $t1 10
sw $t0 -148($fp) 
lw $t1 -148($fp) 
bge $t1 126 elsebegin2
lw $t1 -108($fp) 
add $t0 $t1 10
sw $t0 -152($fp) 
lw $t1 -152($fp) 
beq $t1 32 elsebegin3
lw $t1 -108($fp) 
sub $t0 $t1 5
sw $t0 -156($fp) 
lw $t1 -156($fp) 
ble $t1 32 elsebegin4
lw $t1 -108($fp) 
sub $t0 $t1 4
sw $t0 -160($fp) 
lw $t1 -160($fp) 
blt $t1 32 elsebegin5
lw $t1 -108($fp) 
add $t0 $t1 15
sw $t0 -164($fp) 
lw $t1 -164($fp) 
bgt $t1 126 elsebegin6
lw $t1 -108($fp) 
add $t0 $t1 10
sw $t0 -168($fp) 
lw $t1 -168($fp) 
beq $t1 34 elsebegin7
lw $t0 -108($fp) 
beqz $t0 elsebegin8 
lw $t1 -108($fp) 
bne $t1 47 elsebegin9
lw $t1 -108($fp) 
bne $t1 47 elsebegin10
lw $t1 -108($fp) 
sub $t0 $t1 10
sw $t0 -172($fp) 
lw $a0 -172($fp) 
li $v0 1 
syscall   
j ifend10  
elsebegin10:   
ifend10:   
j ifend9  
elsebegin9:   
ifend9:   
j ifend8  
elsebegin8:   
ifend8:   
j ifend7  
elsebegin7:   
ifend7:   
j ifend6  
elsebegin6:   
ifend6:   
j ifend5  
elsebegin5:   
ifend5:   
j ifend4  
elsebegin4:   
ifend4:   
j ifend3  
elsebegin3:   
ifend3:   
j ifend2  
elsebegin2:   
ifend2:   
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
main:   
sw $ra 0($sp) 
sw $fp -4($sp) 
move $fp $sp 
sw $v1 -8($sp) 
sw $a0 -12($sp) 
sw $a1 -16($sp) 
sw $a2 -20($sp) 
sw $a3 -24($sp) 
sw $t0 -28($sp) 
sw $t1 -32($sp) 
sw $t2 -36($sp) 
sw $t3 -40($sp) 
sw $t4 -44($sp) 
sw $t5 -48($sp) 
sw $t6 -52($sp) 
sw $t7 -56($sp) 
sw $s0 -60($sp) 
sw $s1 -64($sp) 
sw $s2 -68($sp) 
sw $s3 -72($sp) 
sw $s4 -76($sp) 
sw $s5 -80($sp) 
sw $s6 -84($sp) 
sw $s7 -88($sp) 
sw $t8 -92($sp) 
sw $t9 -96($sp) 
sw $k0 -100($sp) 
sw $k1 -104($sp) 
subi $sp $sp 108
subi $sp $sp 1000
li $t0 0 
sw $t0 i 
j forcmp0  
forbegin0:   
lw $t2 i 
add $t0 $t2 65
sw $t0 -256($fp) 
lw $t0 -256($fp) 
lw $t1 i 
mul $t1 $t1 4
sub $t1 $fp $t1
sw $t0 -112($t1) 
lw $t1 i 
mul $t1 $t1 4
sub $t1 $fp $t1
lw $t0 -112($t1) 
sw $t0 -260($fp) 
lw $t0 -260($fp) 
sw $t0 -108($sp) 
jal putchar  
lw $a0 i 
li $v0 1 
syscall   
lw $t1 i 
add $t0 $t1 1
sw $t0 i 
forcmp0:   
lw $t1 i 
blt $t1 26 forbegin0
li $t0 95 
sw $t0 -108($sp) 
jal putchar  
li $t0 66 
sw $t0 -116($fp) 
li $t0 67 
sw $t0 -120($fp) 
li $t0 68 
sw $t0 -124($fp) 
li $t0 69 
sw $t0 -128($fp) 
li $t0 70 
sw $t0 -132($fp) 
li $t0 71 
sw $t0 -136($fp) 
li $t0 72 
sw $t0 -140($fp) 
li $t0 73 
sw $t0 -144($fp) 
li $t0 74 
sw $t0 -148($fp) 
li $t0 75 
sw $t0 -152($fp) 
li $t0 76 
sw $t0 -156($fp) 
li $t0 77 
sw $t0 -160($fp) 
li $t0 78 
sw $t0 -164($fp) 
li $t0 79 
sw $t0 -168($fp) 
li $t0 80 
sw $t0 -172($fp) 
li $t0 81 
sw $t0 -176($fp) 
li $t0 82 
sw $t0 -180($fp) 
li $t0 83 
sw $t0 -184($fp) 
li $t0 84 
sw $t0 -188($fp) 
li $t0 85 
sw $t0 -192($fp) 
li $t0 86 
sw $t0 -196($fp) 
li $t0 87 
sw $t0 -200($fp) 
li $t0 76 
sw $t0 -204($fp) 
li $t0 89 
sw $t0 -208($fp) 
li $t0 90 
sw $t0 -212($fp) 
li $t0 48 
sw $t0 -216($fp) 
li $t0 49 
sw $t0 -220($fp) 
li $t0 50 
sw $t0 -224($fp) 
li $t0 51 
sw $t0 -228($fp) 
li $t0 52 
sw $t0 -232($fp) 
li $t0 53 
sw $t0 -236($fp) 
li $t0 54 
sw $t0 -240($fp) 
li $t0 55 
sw $t0 -244($fp) 
li $t0 56 
sw $t0 -248($fp) 
li $t0 57 
sw $t0 -252($fp) 
li $t0 26 
sw $t0 i 
j forcmp1  
forbegin1:   
lw $t1 i 
mul $t1 $t1 4
sub $t1 $fp $t1
lw $t0 -112($t1) 
sw $t0 -264($fp) 
lw $t0 -264($fp) 
sw $t0 -108($sp) 
jal putchar  
lw $a0 i 
li $v0 1 
syscall   
lw $t1 i 
add $t0 $t1 1
sw $t0 i 
forcmp1:   
lw $t1 i 
ble $t1 35 forbegin1
li $t0 0 
sw $t0 -108($fp) 
dobegin0:   
lw $t1 -108($fp) 
add $t0 $t1 5
sw $t0 -268($fp) 
lw $t0 -268($fp) 
sw $t0 -108($fp) 
li $v0 4 
la $a0 yangsen_string0 
syscall   
lw $t1 -108($fp) 
mul $t0 $t1 10
sw $t0 -272($fp) 
lw $a0 -272($fp) 
li $v0 1 
syscall   
li $t0 95 
sw $t0 -108($sp) 
jal putchar  
lw $t1 -108($fp) 
blt $t1 12 dobegin0
li $v0 5 
syscall   
sw $v0 i 
li $v0 5 
syscall   
sw $v0 j 
li $v0 5 
syscall   
sw $v0 k 
li $v0 12 
syscall   
sw $v0 ch 
li $v0 4 
la $a0 yangsen_string1 
syscall   
lw $a0 i 
li $v0 1 
syscall   
lw $t0 i 
beqz $t0 elsebegin11 
li $v0 4 
la $a0 yangsen_string2 
syscall   
lw $t0 i 
sw $t0 -108($sp) 
jal fibonacci  
sw $v0 -276($fp) 
lw $a0 -276($fp) 
li $v0 1 
syscall   
li $t0 95 
sw $t0 -108($sp) 
jal putchar  
j ifend11  
elsebegin11:   
ifend11:   
jal func  
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
li $v0 0 
lw $v1 -8($fp) 
lw $a0 -12($fp) 
lw $a1 -16($fp) 
lw $a2 -20($fp) 
lw $a3 -24($fp) 
lw $t0 -28($fp) 
lw $t1 -32($fp) 
lw $t2 -36($fp) 
lw $t3 -40($fp) 
lw $t4 -44($fp) 
lw $t5 -48($fp) 
lw $t6 -52($fp) 
lw $t7 -56($fp) 
lw $s0 -60($fp) 
lw $s1 -64($fp) 
lw $s2 -68($fp) 
lw $s3 -72($fp) 
lw $s4 -76($fp) 
lw $s5 -80($fp) 
lw $s6 -84($fp) 
lw $s7 -88($fp) 
lw $t8 -92($fp) 
lw $t9 -96($fp) 
lw $k0 -100($fp) 
lw $k1 -104($fp) 
lw $ra 0($fp) 
move $sp $fp 
lw $fp -4($fp) 
jr $ra  
end:
jal main
