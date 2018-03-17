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

###### TODO ######
# Coloquem dúvidas e coisas a fazer aqui
# [] Usar .align
# [] Alinhar e identar textos

#.data

    ### data structures ###
    # node:
    # trie:

    # Exemplo array:
    # list: .word 3, 0, 1, 2, 6, -2, 4, 7, 3, 7

    #### strings ####
    # Visualizing the trie
    # * Node
    # +----+
    # | %d |
    # +----+
    # %d = node's value
    node_box_top:    .asciiz    "+----+\n| "
    node_box_bottom: .asciiz    "  |\n+----+\n"

    str_newline:     .asciiz     "\n"

    # Menu
    str_menu:       .asciiz     "\n\nBITWISE TRIE\n\n    1. Insert node\n    2. Search node\n    3. Delete node\n    4. Visualize trie\n    5. Exit\n\nSelect your option: \n"

    str_op:         .asciiz     "Select option: "
    str_insert:     .asciiz     "Value to insert: "
    str_remove:     .asciiz     "Value to remove: "
    str_search:     .asciiz     "Value to search: "
    str_vis: .asciiz "Visualizing trie\n"
    str_exit: .asciiz "Exiting...\n"

.text

    # MAIN
    main:

        # load menu options
        li $s0, 1 # 1 - Insert
        li $s1, 2 # 2 - Search
        li $s2, 3 # 3 - Remove
        li $s3, 4 # 4 - Visualize
        li $s4, 5 # 5 - Exit

        menu:
            li $v0, 4 # print string
            la $a0, str_menu #  menu
            syscall

            li $v0, 5 # read int
            syscall
            move $t0, $v0 # store user input

            # check user choice
            # TODO:
            # Mudar p/ labels de menu_1, menu_2...
            # Usar JAL em vez de BEQ?
            # Funções da trie viram procedures
            # com retorno $ra
            beq $t0, $s0, insert_node
            beq $t0, $s1, search_node
            beq $t0, $s2, delete_node
            beq $t0, $s3, print_trie
            beq $t0, $s4, exit
            j menu

    ### TRIE FUNCTIONS ###
    insert_node:
        li $v0, 4 # print string
        la $a0, str_insert

        li $v0, 5 # read int
        syscall
        move $t0, $v0 # store user input

        syscall
        j menu

    delete_node:
        li $v0, 4 # print string
        la $a0, str_remove

        li $v0, 5 # read int
        syscall
        move $t0, $v0 # store user input

        syscall
        j menu

    search_node:
        li $v0, 4 # print string
        la $a0, str_search
        syscall

        li $v0, 5 # read int
        syscall
        move $t0, $v0 # store user input

        j menu

    print_trie:
        li $v0, 4 # print string
        la $a0, str_vis
        syscall
        j menu

    exit:
        li $v0, 4 # print string
        la $a0, str_exit
        syscall

        li $v0, 10
        syscall
