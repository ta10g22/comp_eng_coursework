# Initialize registers and perform basic arithmetic
add $t0, $zero, $zero    # $t0 = 0
add $t1, $zero, $zero    # $t1 = 0
add $t2, $zero, $zero    # $t2 = 0

# Load a value from memory into $t1
lw $t1, 0($a0)           # Assume $a0 contains the address of data[0], $t1 = data[0]

# Add a constant (manually, since no addi)
add $t3, $t1, $t1        # $t3 = $t1 + $t1 (double the value)

# Store result in memory
sw $t3, 4($a0)           # Store $t3 at data[1]

# Subtract test
sub $t4, $t3, $t1        # $t4 = $t3 - $t1 → should be equal to $t1

# Branch test: branch if $t4 == $t1 (should be true)
beq $t4, $t1, label1     # Jump to label1 if equal

# This should be skipped if beq is successful
add $t5, $zero, $zero    # $t5 = 0 (skip this if branch taken)

label1:
# More math just to continue execution
add $t6, $t1, $t3        # $t6 = $t1 + $t3
sub $t7, $t6, $t4        # $t7 = $t6 - $t4

# Optional: jump (if you implement it later)
# j end

# Label to mark end
# end: