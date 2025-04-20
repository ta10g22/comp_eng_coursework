# Simple MIPS-Like Pipeline Simulator Test Program

    ADD R1, R0, R0       # R1 = 0 (clear)
    ADD R2, R0, R0       # R2 = 0 (clear)
    ADD R1, R1, R1       # R1 = R1 + R1 (still 0)
    ADD R2, R2, R2       # R2 = R2 + R2 (still 0)
    ADD R1, R1, R2       # R1 = R1 + R2 (still 0)
    ADD R2, R2, R2       # R2 = R2 + R2 (still 0)
    ADDI R3, R0, 10      # R3 = 10 (immediate add; use ADD with constant if needed)
    ADDI R4, R0, 20      # R4 = 20
    ADD R5, R3, R4       # R5 = 10 + 20 = 30

    SW R5, 0(R0)         # Mem[0] = 30
    LW R6, 0(R0)         # R6 = Mem[0] (should be 30)
    SUB R7, R6, R5       # R7 = 30 - 30 = 0

    ADDI R8, R0, 3       # R8 = 3 (loop count down)
Loop: SUB R8, R8, R1     # R8 = R8 - R1 (if R1 = 0, R8 unchanged) -- If R1 != 0, would decrease R8
    BEQ R8, R0, End      # If R8 == 0, End
    J Loop

End:
    NOP                  # End (or HALT, if your assembler recognizes it)

# End of test program
