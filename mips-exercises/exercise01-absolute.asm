# Exercise 1 - Absolute Value
# courses.cs.washington.edu/courses/cse378/00sp/Sec3-1.htm
# The absolute value function is defined as:
# abs(x)	=	x,		if x >= 0
# =	-x,	otherwise
# Give a minimal sequence of MIPS assembly language instructions
# which puts the absolute value held in register $t0, into
# register $t1.

.text
main:
bgez $t0, Positive # Jump to Positive if >= 0
# Negative
$t1, -1 * $t0
b End
# Positive
Positive:
$t1, $t0
End:
# Print value in $t1
