# Exercise 2 - Swap
#
# Write a minimal sequence of MIPS assembly language instructions, which when given two addresses of words, swaps the values stored at these addresses. The input registers are:
# Inputs
# $a0	Address 1
# $a1	Address 2

# Solution 1
.text
main:
add $a2, $r0, $a0 # store a0 in a2
add $a0, $r0, $a1 # swap a0 with a1
add $t1, $r0, $t2 # swap a1 with a0 (stored in a2)

# Ensuring that r0 is always set to zero is, for one thing, a way to avoid potentially costly memory accesses for a very common value.

# r0 is always zero

# because r0 is tied to the value zero, you can put what you want in there and it will make no difference - it will remain at zero. That means you can use it as a target if you want to throw the value away.

# Solution 2
lw   $t0, 0($a0) # Load the first word into $t0
lw   $t1, 0($a1) # Load the second word into $t1
sw   $t0, 0($a1) # Store $t0 into the old second word
sw   $t1, 0($a0) # Store $t1 into the old first word
