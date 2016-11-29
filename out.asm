.data
array: .space 
i: .word 0
j: .word 0
k: .word 0
ch: .word 0
set: .space 
h: .word 0
yangsen_string0: .asciiz "The number of 'f*10' is:"
yangsen_string1: .asciiz "The first number you input is "
yangsen_string2: .asciiz "Its fibonacci is"
.text
move $fp, $sp
j main
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
li $t0 w 
sw $t0 w($fp) 
lw $t1 ($fp) 
mul $t0 $t1 
sw $t0 ($fp) 
lw $t1 ($fp) 
lw $t2 ($fp) 
add $t0 $t1 $t2
sw $t0 ($fp) 
lw $t0 ($fp) 
sw $t0 ($fp) 
lw $v0 ($fp) 
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
lw $a0 w($fp) 
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
lw $t1 ($fp) 
blt $t1  elsebegin
lw $t1 ($fp) 
bgt $t1  elsebegin
li $v0  
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
j ifend  
elsebegin:   
lw $t1 ($fp) 
sub $t0 $t1 
sw $t0 ($fp) 
lw $t0 ($fp) 
sw $t0 ($sp) 
jal fibonacci  
sw $v0 ($fp) 
lw $t1 ($fp) 
sub $t0 $t1 
sw $t0 ($fp) 
lw $t0 ($fp) 
sw $t0 ($sp) 
jal fibonacci  
sw $v0 ($fp) 
lw $t1 ($fp) 
lw $t2 ($fp) 
add $t0 $t1 $t2
sw $t0 ($fp) 
lw $v0 ($fp) 
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
ifend:   
j ifend  
elsebegin:   
li $v0  
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
ifend:   
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
subi $sp $sp 1000
li $t0  
sw $t0 i 
j forcmp  
forbegin:   
lw $t2 i 
add $t0 $t2 
sw $t0 ($fp) 
lw $t0 ($fp) 
lw $t1 i 
mul $t1 $t1 4
sub $t1 $fp $t1
sw $t0 ($t1) 
lw $t1 i 
mul $t1 $t1 4
sub $t1 $fp $t1
lw $t0 ($t1) 
sw $t0 ($fp) 
lw $t0 ($fp) 
sw $t0 ($sp) 
jal putchar  
lw $a0 i 
li $v0 1 
syscall   
lw $t1 i 
add $t0 $t1 
sw $t0 i 
forcmp:   
lw $t1 i 
blt $t1 v forbegin
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 ($fp) 
li $t0  
sw $t0 k 
dobegin:   
lw $t1 ($fp) 
add $t0 $t1 
sw $t0 ($fp) 
lw $t0 ($fp) 
sw $t0 ($fp) 
li $v0 4 
la $a0 yangsen_string 
syscall   
lw $t1 ($fp) 
mul $t0 $t1 
sw $t0 ($fp) 
lw $a0 ($fp) 
li $v0 1 
syscall   
lw $t1 v($fp) 
blt $t1 v dobegin
li $v0 4 
la $a0 yangsen_string 
syscall   
lw $a0 i 
li $v0 1 
syscall   
lw $t0 i 
beqz $t0 elsebegin 
li $v0 4 
la $a0 yangsen_string 
syscall   
lw $t0 i 
sw $t0 ($sp) 
jal fibonacci  
sw $v0 ($fp) 
lw $a0 ($fp) 
li $v0 1 
syscall   
j ifend  
elsebegin:   
ifend:   
lw $t0 j 
sw $t0 ($sp) 
li $t0  
sw $t0 ($sp) 
jal func_2_number  
sw $v0 ($fp) 
lw $t1 ($fp) 
neg $t0 $t1 
sw $t0 ($fp) 
lw $t1 ($fp) 
lw $t2 k 
add $t0 $t1 $t2
sw $t0 ($fp) 
lw $t1 i 
lw $t2 ($fp) 
mul $t0 $t1 $t2
sw $t0 ($fp) 
lw $t1 j 
lw $t2 k 
div $t0 $t1 $t2
sw $t0 ($fp) 
lw $t1 ($fp) 
lw $t2 ($fp) 
mul $t0 $t1 $t2
sw $t0 ($fp) 
lw $a0 ($fp) 
li $v0 1 
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
