#############################################
# Showcase program: squares 0 … 200 (inclusive)
# Uses only: add, sub, lw, sw, beq
# Registers
#   $t0  i           (0 … 201)
#   $t2  square      (running result)
#   $t3  diff        (2*i + 1  — increment between squares)
#   $t4  const1      (=1)
#   $t5  const2      (=2)
#   $t6  const4      (=4)  – byte stride between array elements
#   $t7  limit       (=201)
#############################################

        # ---- load small constants ----
        lw   $t4, 0($a1)      # const1 = 1
        lw   $t5, 4($a1)      # const2 = 2
        add  $t6, $t5, $t5    # const4 = 2 + 2 = 4  (word stride)
        lw   $t7, 8($a1)      # limit  = 201

        # ---- initialise state ----
        add  $t0, $zero, $zero   # i       = 0
        add  $t2, $zero, $zero   # square  = 0
        add  $t3, $t4,  $zero    # diff    = 1   (2*0 + 1)

loop:
        # Store square[i]  (array is word‑aligned, stride = 4)
        sw   $t2, 0($a0)

        # Advance output‑array pointer
        add  $a0, $a0,  $t6      # a0 += 4

        # i ← i + 1
        add  $t0, $t0,  $t4

        # Have we reached 201?  If so, exit
        beq  $t0, $t7, done

        # square  ← square + diff        (new square value)
        add  $t2, $t2,  $t3

        # diff    ← diff + 2             (next difference = 2*i + 1)
        add  $t3, $t3,  $t5

        # Unconditional branch back to loop
        beq  $zero, $zero, loop

done:
        # Simple infinite hold‑off (could be NOPs in real HW)
        beq  $zero, $zero, done
