#   SSC-0112 - Organização de Computadores Digitais
#
#   Implementação de uma Bitwise Trie em Assembly MIPS
#
#   Alunos:
#       Felipe Scrochio Custódio - 9442688
#       Gabriel Henrique Scalici - 9292970
#       Juliano Fantozzi - ...
#
#   Recursos Utilizados:
#   MIPS Green Sheet
#   http://students.cs.tamu.edu/tanzir/csce350/reference/syscalls.html
#   https://en.m.wikipedia.org/wiki/Trie

.data

    # Strings de menu
    str_menu: .asciiz "\n\nBITWISE TRIE\n\n    1. Inserção\n    2. Remoção\n    3. Busca\n    4. Visualização\n    5. Sair\n    Escolha uma opção (1 a 5): "

    # Strings das opções do menu
    str_insert:     .asciiz     "Digite o binário para inserção: "
    str_remove:     .asciiz     "Digite o binário para remoção: "
    str_search:     .asciiz     "Digite o binário parra busca: "

    # Strings da visualização
    str_vis_n: .asciiz "N"
    str_vis_p1: .asciiz "("
    str_vis_p2: .asciiz ")"
    srt_vis_info_t: .asciiz "T"
    str_vis_info_nt: .asciiz "NT"
    str_vis_null: .asciiz "null"

.text

    main:

        # Opções do Menu ficam armazenadas nos registradores $sX
        li $s0, 1 # 1 - Inserção
        li $s1, 2 # 2 - Remoção
        li $s2, 3 # 3 - Busca
        li $s3, 4 # 4 - Visualizar
        li $s4, 5 # 5 - Sair

        # Funcionalidade de Menu
        menu:

            li $v0, 4 # imprimir string
            la $a0, str_menu
            syscall

            li $v0, 5 # ler inteiro
            syscall
            move $t0, $v0 # guardar input em $t0

            beq $t0, $s0, insert_node
            beq $t0, $s1, delete_node
            beq $t0, $s2, search_node
            beq $t0, $s3, print_trie
            beq $t0, $s4, exit
            j menu

    # Funcionalidades da Trie
    insert_node:
        li $v0, 4 # imprimir string
        la $a0, str_insert

        li $v0, 5 # ler inteiro
        syscall
        move $t0, $v0 # guardar input em $t0

        j menu

    delete_node:
        li $v0, 4 # imprimir string
        la $a0, str_remove

        li $v0, 5 # ler inteiro
        syscall
        move $t0, $v0 # guardar input em $t0

        j menu

    search_node:
        li $v0, 4 # imprimir string
        la $a0, str_search
        syscall

        li $v0, 5 # ler inteiro
        syscall
        move $t0, $v0 # guardar input em $t0

        j menu

    print_trie:
        li $v0, 4 # imprimir string
        la $a0, str_vis
        syscall

        j menu

    exit:
        li $v0, 4 # imprimir string
        la $a0, str_exit
        syscall

        li $v0, 10 # finalizar execução
        syscall
