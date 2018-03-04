# Exercise 2 - Swap
#
# Write a minimal sequence of MIPS assembly language instructions, which when given two addresses of words, swaps the values stored at these addresses. The input registers are:
# Inputs
# $a0	Address 1
# $a1	Address 2

.text
main:
add $a2, $r0, $a0 # store a0 in a2
add $a0, $r0, $a1 # swap a0 with a1
add $t1, $r0, $t2 # swap a1 with a0 (stored in a2)
