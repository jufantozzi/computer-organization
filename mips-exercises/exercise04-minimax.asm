# Exercise 4 - MiniMax
#
# miniMax: # A procedure to find the minimum and maximum elements of an integer
#          # array
#          # On entry:
#          # $a0 - base address of the array
#          # $a1 - number of elements in the array
#          # On exit:
#          # $v0 - the minimum element
#          # $v1 - the maximum element

.text

# initialize
lw $v0, 0($t0) # min = first element
lw $v1, 0($t0) # max = first element
lw $t0, $a0 # $t0 = memory location (index)
lw $t2, $r0 # initialize counter at 0

loop:
lw $t1, 0($t0) # load current value to $t1
bgt $t1, $v1, new_max # check if maximum
blt $t1, $v0, new_min # check if minimum
addi $t0, $t0, 4 # move index to next position
addi $t2, $t2, 1 # increase counter by 1
bge $t2, $a1, exit # exit if reached end of array
j loop # loop

new_min:
lw $v0, $t1
j loop

new_max:
lw $v1, $t1
j loop

exit:
lw $v0, $t0
lw $v1, $t1
