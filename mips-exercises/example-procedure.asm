.data
    message: .asciiz "Hello, World"

.text
    main:

        jal display # pula para display e linka main em $ra
        # (return address)

    # Encerrar execução
    li $v0, 10
    syscall

    display:
        li $v0, 4
        la $a0, message
        syscall

        jr $ra # retorna para a procedure que chamou essa
        # (acredito que na linha da chamada)

# Para usar parâmetros: registros $a (arguments)
# Para retorno: registros $v (value?)
