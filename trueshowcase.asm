# showcase.asm
# Calculate and store squares of 0..200 using only add, sub, addi, lw, sw, beq, j, nop

    addi $t0, $zero, 0     # i = 0
    addi $t1, $zero, 0     # square = 0
    addi $t2, $zero, 0     # addr = 0 (byte offset into data memory)
    addi $t4, $zero, 200  # limit = 200

Loop:
    sw   $t1, 0($t2)       # Mem[addr] = square
    beq  $t0, $t4, End     # if i == 200, done

    # compute next square: square += 2*i + 1
    add  $t3, $t0, $t0     # t3 = 2 * i
    addi $t3, $t3, 1       # t3 = 2*i + 1
    add  $t1, $t1, $t3     # square = square + (2*i + 1)

    addi $t0, $t0, 1       # i++
    addi $t2, $t2, 4       # addr += 4 bytes
    j    Loop

End:
    nop                    # finished storing squares
    
