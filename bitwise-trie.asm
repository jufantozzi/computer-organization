 # ,---- [ SSC-0112 - Organização de Computadores Digitais ]
# |
# |  Implementação de uma Bitwise Trie em Assembly MIPS
# |  Alunos:
# |        Felipe Scrochio Custódio - 9442688
# |        Gabriel Henrique Scalici - 9292970
# |        (...)
# `----

# Recursos Utilizados:
# MIPS Green Sheet
# http://students.cs.tamu.edu/tanzir/csce350/reference/syscalls.html
# https://en.m.wikipedia.org/wiki/Trie

.data

    ### data structures ###
    # node:
    # tree:

    #### strings ####

    # Representação visual da árvore
    # * Nó
    # +----+
    # | %d |
    # +----+

    # Sendo %d seu valor
    node_box_top: .asciiz "+----+\n| "
    node_box_bottom: .asciiz "  |\n+----+\n"

    # Quebras de linha
    str_newline: .asciiz "\n"

    # Menu
    str_welcome: .asciiz "### BINARY TRIE ###\n"
    str_menu: .asciiz ""
    str_op: .asciiz "Select option: "
    str_insert: .asciiz "Value to insert: "
    str_remove: .asciiz "Value to remove: "
    str_search: .asciiz "Value to search: "

.text

    insert_node:
        #

    delete_node:
        #

    search_node:
        #

    print_tree:
        #

    # MAIN
    main:
		# operações
        li $v0, 4       # $system call code for print_str
        la $a0, node_box_top     # $address of string to print
        syscall

        li $v0, 1       # $system call code for print_int
        li $a0, 5       # $integer to print
        syscall         # print it

        li $v0, 4       # $system call code for print_str
        la $a0, node_box_bottom     # $address of string to print
        syscall

        # Encerrar execução do programa
        li $v0, 10
        syscall
