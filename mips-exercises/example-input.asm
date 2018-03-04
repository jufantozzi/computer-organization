.data
    # RAM
    message: .asciiz "Hello, "
    userInput: .space 20

.text

    # Registradores a = Argumentos
    # Registradores v = Sistema

    main:
        # Get user input as text
        li $v0, 8 # Read string
        la $a0, userInput # Load address of variable
        li $a1, 20 # Tell the system the max length of variable
        syscall # Execute

        # Displays message
        li $v0, 4 # Output string
        la $a0, message
        syscall

        # Displays name
        li $v0, 4
        la $a0, userInput
        syscall

    # End program
    li $v0, 10
    syscall
