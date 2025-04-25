# beqtest.asm – exercises BEQ taken and not‐taken paths, then halts

main:
    addi $t0, $zero, 5     # $t0 = 5
    addi $t1, $zero, 5     # $t1 = 5
    beq  $t0, $t1, br1     # taken → jump to br1
    addi $t2, $zero, 0     # skipped when branch is taken
br1:
    addi $t2, $zero, 1     # $t2 = 1 if branch was taken

    addi $t3, $zero, 7     # $t3 = 7
    addi $t4, $zero, 8     # $t4 = 8
    beq  $t3, $t4, skip2   # not taken → fall through
    addi $t5, $zero, 1     # $t5 = 1 when branch is not taken
skip2:
    nop                    # natural fall-off, sim stops when PC > 9
