# testing string with newline
.data
    string: .asciiz "Hello\nWorld!\n!"

.text
    main:
        li $v0, 4       # $system call code for print_str
        la $a0, string     # $address of string to print
        syscall

        li $v0, 10
        syscall
