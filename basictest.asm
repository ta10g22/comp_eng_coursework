# Simple MIPS-Like Pipeline Simulator Test Program (Standard MIPS Style)

    add $t0, $zero, $zero     # $t0 = 0 (clear)       -> R1
    add $t1, $zero, $zero     # $t1 = 0 (clear)       -> R2
    add $t0, $t0, $t0         # $t0 = $t0 + $t0       -> still 0
    add $t1, $t1, $t1         # $t1 = $t1 + $t1       -> still 0
    add $t0, $t0, $t1         # $t0 = $t0 + $t1       -> still 0
    add $t1, $t1, $t1         # $t1 = $t1 + $t1       -> still 0
    addi $t2, $zero, 10       # $t2 = 10              -> R3
    addi $t3, $zero, 20       # $t3 = 20              -> R4
    add  $t4, $t2, $t3        # $t4 = 10 + 20 = 30    -> R5

    sw   $t4, 0($zero)        # Mem[0] = 30
    lw   $t5, 0($zero)        # $t5 = Mem[0] (should be 30) -> R6
    sub  $t6, $t5, $t4        # $t6 = 30 - 30 = 0     -> R7

    addi $t7, $zero, 3        # $t7 = 3               -> R8
Loop:
    sub  $t7, $t7, $t0        # $t7 = $t7 - $t0       (if $t0 = 0, unchanged)
    beq  $t7, $zero, End      # If $t7 == 0, go to End
    j    Loop

End:
    nop                       # End of program