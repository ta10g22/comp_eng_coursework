# Test MIPS jump instruction — ends cleanly
# Exercises both forward and backward jumps without using only the `j` instruction

    addi $t0, $zero, 0     # i = 0
    addi $t1, $zero, 0     # square = 0
    addi $t2, $zero, 0     # addr = 0 (byte offset into data memory)
    addi $t4, $zero, 200  # limit = 200

    # Forward jump: skip over the next two instructions
    j  Forward
    nop
    addi $t0, $zero, 1   # skipped
    addi $t1, $zero, 2   # skipped

Forward:
    addi $t2, $zero, 3   # executed after forward jump

    # Backward jump: jump back to 'backward' label
    j  backward
    nop

    # These instructions are skipped by the backward jump
    addi $t3, $zero, 4
    addi $t4, $zero, 5

backward:
    addi $t5, $zero, 6   # executed after backward jump

    # Jump to exit
    j  Exit
    nop
Exit:
