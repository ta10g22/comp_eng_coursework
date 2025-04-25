# Long MIPS Assembly Test Program

# Initialize some values in registers
addi $t0, $zero, 5      # $t0 = 5
addi $t1, $zero, 10     # $t1 = 10
addi $t2, $zero, 15     # $t2 = 15
addi $t3, $zero, 20     # $t3 = 20
addi $t4, $zero, 25     # $t4 = 25
addi $t5, $zero, 30     # $t5 = 30

# Add and subtract operations
add  $t6, $t0, $t1       # $t6 = 5 + 10 = 15
sub  $t7, $t3, $t2       # $t7 = 20 - 15 = 5
add  $s0, $t4, $t5       # $s0 = 25 + 30 = 55
sub  $s1, $t5, $t0       # $s1 = 30 - 5 = 25

# Store and load from memory (mem[0] = 15)
sw   $t6, 0($zero)       # Mem[0] = 15
lw   $s2, 0($zero)       # $s2 = Mem[0]

# Store more values in memory
sw   $t1, 4($zero)       # Mem[4] = 10
sw   $t2, 8($zero)       # Mem[8] = 15
sw   $t3, 12($zero)      # Mem[12] = 20
sw   $t4, 16($zero)      # Mem[16] = 25

# Load them back
lw   $s3, 4($zero)       # $s3 = 10
lw   $s4, 8($zero)       # $s4 = 15
lw   $s5, 12($zero)      # $s5 = 20
lw   $s6, 16($zero)      # $s6 = 25

# Loop using beq and jump
addi $t7, $zero, 3       # $t7 = 3
Loop:
    sub $t7, $t7, $t0    # $t7 -= $t0
    beq  $t7, $zero, done   # if $t7 == 0, jump to Done
    j Loop

# Some extra unused instructions to simulate pipeline flush
add  $a0, $t0, $t1       # fake
add  $a1, $t1, $t2       # fake
add  $a2, $t2, $t3       # fake   //mistake cause to jump to beginning of loop

done:
    nop
    nop
    nop
    nop
    nop

# Extra workload (many instructions for pipeline testing)
addi $s7, $zero, 100
add  $t0, $s7, $t1
sub  $t1, $t0, $s7
add  $t2, $t0, $t1
sub  $t3, $t2, $t1
add  $t4, $t3, $t2
sub  $t5, $t4, $t3
add  $t6, $t5, $t4
sub  $t7, $t6, $t5
add  $s0, $t7, $t6
sub  $s1, $s0, $t7
add  $s2, $s1, $s0
sub  $s3, $s2, $s1
add  $s4, $s3, $s2
sub  $s5, $s4, $s3
add  $s6, $s5, $s4
sub  $s7, $s6, $s5
