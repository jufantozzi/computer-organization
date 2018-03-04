# Exercise 3 - Linear Search
#
# Write an assembly language procedure to find a given 32-bit integer in an array of integers.
# Inputs
# $a0	Base address of the array
# $a1	Number of elements in the array
# $a2	Element to search for
# Outputs
# $v0	Flag (see below)
# Register $v0 will hold the value 1 if the element held in $a2 is in the array. Otherwise it will hold the value 0.
#
# Note that the array is not sorted, so we cannot perform a binary search. Your code should still work if the size of the array is 0.
# You may assume that the procedure is a leaf procedure.

# $t0 = index
# $t1 = value at index
# $t2 = counter

# By using a pointer into the array, you can avoid having to
# multiply the index by 4 and adding it to the base address of
# the array. This is to save instructions so that the code
# executes quicker.

.text
add $t2, $r0 # initialize counter to 0
lw $t0, $a0 # load base address to t0 (index)

search:
lw $t1, 0($t0) # load current value to t1
beq $t1, $a2, found # jump to found if value is found
addi  $t0, $t0, 4 # move index to next position
addi  $t2, $r0, 1 # add 1 to counter
bge $t2, $a1, not_found # jump to not_found
j search # loop

found:
addi $v0, $r0, 1
j exit

not_found:
add $v0, $r0, $r0

exit:

.data
