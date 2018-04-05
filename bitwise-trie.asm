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
# ║ $s0-$s4     ║ Opções do Menu (1-5)     ║
# ║ $t0         ║ Input do Menu            ║
# ║ $s5         ║ Endereço inicial da Trie ║
# ║ $s6         ║ Contador (Trie)          ║
# ║ $s7         ║ Contador (Pilha)         ║
# ║ $a1         ║ Endereço de 'Chave'      ║
# ╚═════════════╩══════════════════════════╝
#
# ESTRUTURA DE DADOS
# ╔══════════════════════╦══════════════╦═════════╗
# ║       Atributo       ║ Tipo de Dado ║ Tamanho ║
# ╠══════════════════════╬══════════════╬═════════╣
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

	str_exit: .asciiz "Saindo...\n"

	# Strings da visualização
	str_vis_root: .asciiz "raiz"
	str_vis_n: .asciiz "N"
	str_vis_p1: .asciiz "("
	str_vis_p2: .asciiz ")\n"
	srt_vis_info_t: .asciiz "T"
	str_vis_info_nt: .asciiz "NT"
	str_vis_null: .asciiz "null"

	# String de input
	chave: .space 64 # 16 dígitos = 64 bytes

	# Nó da Trie
	root: .space 8 # Cada nó possui dois ponteiros de 4 bytes (esq, dir)

.text

	main:

		# Opções do Menu ficam armazenadas
		# nos registradores $sX
		li $s0, 1 # 1 - Inserção
		li $s1, 2 # 2 - Remoção
		li $s2, 3 # 3 - Busca
		li $s3, 4 # 4 - Visualizar
		li $s4, 5 # 5 - Sair

		# Alocar nó raiz
		li $v0, 9 # alocar memória
		la $a0, 8 # 1 nó = 8 bytes (2 endereços/ponteiros)
		syscall
		# (TODO) apontar para null no inicio, logo que eh criado a raiz

		# Armazenar endereço inicial da Trie
		# (TODO) Armazenar endereço que está em $v0 em root (store word)
		move $s5, $v0



	# Funcionalidade do Menu
	menu:

		li $v0, 4 # imprimir string
		la $a0, str_menu
		syscall

		li $v0, 5 # ler inteiro
		syscall
		move $t0, $v0 # guardar input em $t0

		# ir para opção escolhida
		beq $t0, $s0, insert_node # 1
		beq $t0, $s1, remove_node # 2
		beq $t0, $s2, search_node # 3
		beq $t0, $s3, print_trie # 4
		beq $t0, $s4, exit # 5
		j menu # loop (opção inválida)

	# Funcionalidades da Trie
	insert_node:
		li $v0, 4 # imprimir string
		la $a0, str_insert
		syscall

		li $v0, 8 # ler string
		la $a0, chave # armazenar input do usuário em 'chave'
		li $a1, 16 # preparar para ler 16 bytes
		syscall

		jal check_input # verificar se input é válido (volta ao menu se -1)
		bne $v0, 1, insert_node # pede nova chave caso seja inválida

		# (TODO)verificar se chave já existe -> Colocar a busca
		# jal search_node
		# bne $v0, 1, insert_node # pede nova chave caso seja repetida

		# acessar 'chave' do usuário
		# $a1 é nosso ponteiro para iterar sobre a chave
		la $a1, chave

		# acessar nó raiz
		# $t1 = nó atual
		la $t1, root

		insert_node_loop:
			# percorrer chave do usuário
			# $t0 = caractere atual da chave
			# $a1 = endereço do caractere atual da chave
			lb $t0, 0($a1) # $a1 sempre estará atualizado
			beq $t0, $zero, insert_node_left # 0 = inserir à esquerda
			beq $t0, $s0, insert_node_right # 1 = inserir à direita
			j insert_node # chegou ao fim da string, pede nova

		insert_node_left:
			# verificar se já existe (TODO)
			# se não for null, continuar descendo
			addi $a1, $a1, 1 # ir para próximo caractere na chave
			j insert_node_loop

			# se for null, criar novo nó
			# vamos alocar e inserir
			li $v0, 9 # alocar memória
			li $a0, 8 # 1 nó = 8 bytes (2 endereços/ponteiros)
			syscall # $v0 contém endereço inicial do novo nó
			# (TODO) coloca o valor null nos dois endereços alocados
			# 0($v0) = null  4($v0) = null

			# (TODO) move -> store word
			move 0($t1), $v0 # novo nó é armazenado como filho esquerdo do nó atual
			addi $a1, $a1, 1 # ir para próximo caractere na chave
			# (TODO) move -> store word ou load
			move $t1, 0($t1) # acessar novo nó esquerdo

			j insert_node_loop # retorna ao loop de inserção

		insert_node_right:
			# verificar se já existe (TODO)
			# se não for null, continuar descendo
			addi $a1, $a1, 1 # ir para próximo caractere na chave
			j insert_node_loop

			# se for null, criar novo nó
			# vamos alocar e inserir
			li $v0, 9 # alocar memória
			li $a0, 8 # 1 nó = 8 bytes (2 endereços/ponteiros)
			syscall # $v0 contém endereço inicial do novo nó
			# (TODO) coloca o valor null nos dois endereços alocados
			# 0($v0) = null  4($v0) = null

			# (TODO) move -> store word
			move 4($t1), $v0 # novo nó é armazenado como filho direito do nó atual
			addi $a1, $a1, 1 # ir para próximo caractere na chave
			# (TODO) move -> store word ou load
			move $t1, 4($t1) # acessar novo nó direito
			j insert_node_loop # retorna ao loop de inserção

	remove_node:
		li $v0, 4 # imprimir string
		la $a0, str_remove
		syscall

		li $v0, 8 # ler string
		la $a0, chave # armazenar input do usuário em 'chave'
		li $a1, 64 # preparar para ler 64 bytes (16 dígitos)
		syscall

		jal check_input # verificar que input é válido (volta ao menu se -1)

		j menu

	search_node:
		li $v0, 4 # imprimir string
		la $a0, str_search
		syscall

		li $v0, 8 # ler string
		la $a0, chave # armazenar input do usuário em 'chave'
		li $a1, 64 # preparar para ler 64 bytes (16 dígitos)
		syscall

		jal check_input # verificar que input é válido (volta ao menu se -1)

		j menu

		search_node_left:
			# armazenar nó atual na pilha (caminho)
			# verificar próximo caractere da string
			addi $a0, $a0, 4 # ir p/ endereço do próximo caractere
			lb $t0, 0($a0)

		search_node_right:
			# armazenar nó atual na pilha (caminho)

			# ok, esse nó existe?
			# estamos em 0($a0), certo? logo, byte em 8($a0) nos dará sua existencia

			# verificar próximo caractere da string
			addi $a0, $a0, 4 # ir p/ endereço do próximo caractere
			lb $t0, 0($a0)



	# +--------------+
	# | VISUALIZAÇÃO |
	# +--------------+
	print_trie:
		# li $v0, 4 # imprimir string
		# la $a0, str_vis
		# syscall

		j menu

	# +--------------+
	# | CHECAR INPUT |
	# +--------------+
	check_input:
		# Percorrer string de entrada
		li $t1, 48 # 0 em ASCII
		li $t2, 49 # 1 em ASCII
		li $t3, 45 # - em ASCII
		li $t4, 10 # \n em ASCII
		la $a1, chave # carregar endereço de chave em $a1

		check_input_loop:
			# Carregar valor do endereço em $t0
			lb $t0, 0($a1)
			# Verificar se bit atual é 0, 1
			beq $t0, $t1, check_input_continue # checa se é 0
			beq $t0, $t2, check_input_continue # checa se é 1
			beq $t0, $t3, check_input_return # checa se é -
			beq $t0, $t4, check_input_pass # verifica se é '\n', se chegou no fim
			# não é 0, 1 ou -1
			j check_input_error

		# é 0 ou 1, continua
		check_input_continue:
			# Ver se está na posição final da entrada
			lb $t0, 0($a1) # carrega byte sem sinal
			beq $t0, $zero, check_input_pass # verifica se é '\0', se chegou no final, sucesso

			addi $a1, $a1, 1 # Andar para o próximo char checando novamente se é válido
			j check_input_loop

		# voltar ao menu (-1)
		check_input_return:
			addi $a1, $a1, 1 # Andar para o próximo byte
			lb $t0, 0($a1) # Carregar byte
			# bne $t0, $t2, check_input_error # Checa se é 1
			# Exibir string de retorno
			li $v0, 4 # Imprimir string
			la $a0, str_return
			syscall
			# voltar ao menu
			j menu

		check_input_error:
			# exibir string de chave inválida
			li $v0, 4 # imprimir string
			la $a0, str_invalid
			syscall

			li $v0, -1 # -1 no retorno = erro
			jr $ra # retornar

		check_input_pass:
			li $v0, 1 # 1 no retorno = sucesso
			jr $ra # retornar

	exit:
		li $v0, 4 # imprimir string
		la $a0, str_exit
		syscall

		li $v0, 10 # finalizar execução
		syscall

# FIM DO PROGRAMA
