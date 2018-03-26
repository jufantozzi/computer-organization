#	SSC-0112 - Organização de Computadores Digitais
#
#	Implementação de uma Bitwise Trie em Assembly MIPS
#
#	Alunos:
#		Felipe Scrochio Custódio - 9442688
#		Gabriel Henrique Scalici - 9292970
#		Juliano Fantozzi - 9791218
#		André Luis Storino Junior - 9293668
#
# Montado e executado utilizando MARS
#
# USO DE REGISTRADORES
# ╔═════════════╦══════════════════════════╗
# ║ Registrador ║        Usado para        ║
# ╠═════════════╬══════════════════════════╣
# ║ $s0-$s4     ║ Opções do Menu           ║
# ║ $t0         ║ Input do Menu            ║
# ║ $s5         ║ Endereço inicial da Trie ║
# ║ $s6         ║ Contador (Trie)          ║
# ║ $s7         ║ Contador (Pilha)         ║
# ╚═════════════╩══════════════════════════╝
#
# ESTRUTURA DE DADOS
# ╔══════════════════════╦══════════════╦═════════╗
# ║       Atributo       ║ Tipo de Dado ║ Tamanho ║
# ╠══════════════════════╬══════════════╬═════════╣
# ║ Conteúdo             ║ Inteiro      ║ 4 bytes ║
# ║ Endereço nó esquerda ║ Ponteiro     ║ 4 bytes ║
# ║ Endereço nó direita  ║ Ponteiro     ║ 4 bytes ║
# ╚══════════════════════╩══════════════╩═════════╝

.data

	# Strings de menu
	str_menu: .asciiz "\n\nBITWISE TRIE\n\n    1. Inserção\n    2. Remoção\n    3. Busca\n    4. Visualização\n    5. Sair\n    Escolha uma opção (1 a 5): "

	# Strings das opções do menu
	str_insert: .asciiz "Digite o binário para inserção: "
	str_remove: .asciiz "Digite o binário para remoção: "
	str_search: .asciiz "Digite o binário para busca: "

	str_duplicated: .asciiz "Chave repetida. Inserção não permitida.\n"
	str_invalid: .asciiz "Chave inválida. Insira somente números binários (ou -1 retorna ao menu)\n"
	str_return: .asciiz "Retornando ao menu.\n"

	# Strings da visualização
	str_vis_n: .asciiz "N"
	str_vis_p1: .asciiz "("
	str_vis_p2: .asciiz ")"
	srt_vis_info_t: .asciiz "T"
	str_vis_info_nt: .asciiz "NT"
	str_vis_null: .asciiz "null"

	# Input
	chave:
	.space 64 # 16 dígitos = 64 bytes

.text

	main:

		# Opções do Menu ficam armazenadas
		# nos registradores $sX
		li $s0, 1 # 1 - Inserção
		li $s1, 2 # 2 - Remoção
		li $s2, 3 # 3 - Busca
		li $s3, 4 # 4 - Visualizar
		li $s4, 5 # 5 - Sair

		# Alocar vetor que representa a Trie
		li $v0, 9 # alocar memória
		la $a0, 12 # 1 nó = 12 bytes
		syscall

		# Armazenar endereço inicial da Trie
		move $s5, $v0

	# Funcionalidade do Menu
	menu:

		li $v0, 4 # imprimir string
		la $a0, str_menu
		syscall

		li $v0, 5 # ler inteiro
		syscall
		move $t0, $v0 # guardar input em $t0

		beq $t0, $s0, insert_node # 1
		beq $t0, $s1, delete_node # 2
		beq $t0, $s2, search_node # 3
		beq $t0, $s3, print_trie # 4
		beq $t0, $s4, exit # 5
		j menu # loop

	# Funcionalidades da Trie
	insert_node:
		li $v0, 4 # imprimir string
		la $a0, str_insert

		li $v0, 8 # ler string
		la $a0, chave # armazenar 'chave'
		li $a1, 64 # preparar para ler 64 bytes
		syscall

		jal check_input

		j menu

	delete_node:
		li $v0, 4 # imprimir string
		la $a0, str_remove

		li $v0, 8 # ler string
		la $a0, chave
		li $a1, 64
		syscall

		jal check_input

		j menu

	search_node:
		li $v0, 4 # imprimir string
		la $a0, str_search
		syscall

		li $v0, 8 # ler string
		la $a0, chave
		li $a1, 64
		syscall

		jal check_input


		j menu

	print_trie:
		li $v0, 4 # imprimir string
		la $a0, str_vis
		syscall

		j menu

	# Funções auxiliares
	check_input:

	# Percorrer string de entrada ($a0 = chave)
	check_input_loop:

		# Verificar se bit atual é 0, 1 ou -1

		# Imprimir mensagem de erro caso não seja

		# Voltar para menu caso seja -1

		# beq "source", -1, menu

	check_input_error:
		li $v0, -1

	check_input_pass:
		jr $ra # retornar

	exit:
		li $v0, 4 # imprimir string
		la $a0, str_exit
		syscall

		li $v0, 10 # finalizar execução
		syscall

# FIM DO PROGRAMA
