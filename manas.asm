addi  $s0, $zero, 0      # i = 0
addi  $s1, $zero, 0      # sq = 0
addi  $s2, $zero, 100    # base address of array
addi  $t1, $zero, 200    # loop until i == 201

loop:   
sw   $s1, 0($s2)        # store sq (i^2)
addi  $s2, $s2, 4        # advance memory address
add   $t0, $s0, $s0      # 2*i
addi  $t0, $t0, 1        # +1 → 2*i + 1
add   $s1, $s1, $t0      # sq = sq + (2*i + 1)
addi  $s0, $s0, 1        # i++
beq  $s0, $t1, done     # exit if i == 201
j     loop
done:
nop