addi $t0,$zero,10
addi $t1,$zero,10
beq  $t0,$t1,then
addi $t2,$zero,0
then:
addi $t2,$zero,1
addi $t3,$zero,5
addi $t4,$zero,6
beq  $t3,$t4,end
addi $t5,$zero,1
j    done
end:
addi $t5,$zero,0
done:
nop