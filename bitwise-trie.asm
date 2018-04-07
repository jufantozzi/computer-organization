#	SSC-0112 - Organização de Computadores Digitais
#	Turma A - 2018/01
#	Prof Paulo Sérgio Lopes de Souza
#
#	Implementação de uma Bitwise Trie em Assembly MIPS
#
#	Alunos:
#		Felipe Scrochio Custódio - 9442688
#		Gabriel Henrique Scalici - 9292970
#		Juliano Fantozzi - 9791218
#		André Luis Storino Junior - 9293668
#
#	 Montado e executado utilizando MARS
#
# USO DE REGISTRADORES
# //==============[]==========================\\
# ||  Registrador ||        Usado para        ||
# |]==============[]==========================[|
# ||  $s0-$s4     || Opções do Menu           ||
# ||  $t0         || Input do Menu            ||
# ||  $s5         || Endereço inicial da Trie ||
# ||  $s6         || Contador (Trie)          ||
# ||  $s7         || Contador (Pilha)         ||
# ||  $a1         || Endereço de 'Chave'      ||
# \\==============[]==========================//
#
# ESTRUTURA DE DADOS
# //======================[]==============[]=========\\
# ||       Atributo       || Tipo de Dado || Tamanho ||
# |]======================[]==============[]=========[|
# || Endereço nó esquerda || Ponteiro     || 4 bytes ||
# || Endereço nó direita  || Ponteiro     || 4 bytes ||
# || Flag de nó terminal  || Char         || 1 byte  ||
# \\======================[]==============[]=========//

.data

	.align 2

	# Menu principal
	str_menu: .asciiz "\n\nBITWISE TRIE\n\n    1. Inserção\n    2. Remoção\n    3. Busca\n    4. Visualização\n    5. Sair\n    Escolha uma opção (1 a 5): "

	# Strings das opções do menu
	str_insert: .asciiz "Digite o binário para inserção: "
	str_remove: .asciiz "Digite o binário para remoção: "
	str_search: .asciiz "Digite o binário para busca: "

	str_repeat: .asciiz "Binario já existente na arvore."
	str_sucess: .asciiz "Sucesso!\n"

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

	# Input
	chave: .space 16 # 16 dígitos = 16 bytes

	# Raiz da Trie
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

		# Colocando o valor null nos ponteiros do primeiro noh
		# endereco a esquerda = null
		sw $zero, 0($v0)
		# endereco a direita = null
		sw $zero, 4($v0)

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

		# ir para opção escolhida
		beq $t0, $s0, insert_node # 1
		beq $t0, $s1, remove_node # 2
		beq $t0, $s2, search_node # 3
		beq $t0, $s3, print_trie # 4
		beq $t0, $s4, exit # 5
		j menu # loop (opção inválida)

	# Funcionalidades da Trie

	# +----------+
	# | INSERÇÃO |
	# +----------+
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

		# verificar se chave já existe
		jal search_node
		bne $v0, 1, insert_node # pede nova chave caso seja repetida

		# acessar 'chave' do usuário
		# $a1 é nosso ponteiro para iterar sobre a chave
		la $a1, chave

		# acessar nó raiz
		# $t1 = sempre nó atual
		la $t1, root

		insert_node_loop:
			# percorrer chave do usuário
			# $t0 = caractere atual da chave
			# $a1 = endereço do caractere atual da chave
			lb $t0, 0($a1) # $ a1 sempre estará atualizado
			beq $t0, $zero, insert_node_left # 0 = inserir à esquerda
			beq $t0, $s0, insert_node_right # 1 = inserir à direita

			# fim da string significa que nó atual é nó terminal de chave
			sw $s0, 8($v0) # marcar flag como '1'

			j insert_node # encerrou, pedir nova string ou retorno ao menu

		insert_node_right:
			# verificar se existe filho à direita
			# $t2 = ponteiro temporário para filhos
			lw $t2, 4($t1)
			bnez $t2, insert_descend_right

			# se &dir == null, criar e inserir novo nó
			insert_node_right_new:
				# vamos alocar e inserir
				li $v0, 9 # alocar memória
				li $a0, 8 # 1 nó = 8 bytes (2 endereços/ponteiros)
				syscall # $v0 contém endereço inicial do novo nó

				# coloca o valor null nos ponteiros do novo nó
				# endereco a esquerda = null
				sw $zero, 0($v0)
				# endereco a direita = null
				sw $zero, 4($v0)
				# flag indicando se eh noh terminal = false
				sw $zero, 8($v0)

				sw 4($t1), $v0 # novo nó é armazenado como filho direito do nó atual
				# descer para novo nó e continuar loop

			# se &dir != null, descer para ele e voltar ao loop
			insert_descend_right:
				# descendo na árvore, t1 = &dir do nó em que estávamos
				lw $t1, 4($t1)
				addi $a1, $a1, 1 # ir para próximo caractere na chave
				j insert_node_loop

		insert_node_left:
			# verificar se existe filho à esquerda
			# $t2 = ponteiro temporário para filhos
			lw $t2, 0($t1)
			bnez $t2, insert_descend_left

			# se &dir == null, criar e inserir novo nó
			insert_node_left_new:
				# vamos alocar e inserir
				li $v0, 9 # alocar memória
				li $a0, 8 # 1 nó = 8 bytes (2 endereços/ponteiros)
				syscall # $v0 contém endereço inicial do novo nó

				# coloca o valor null nos ponteiros do novo nó
				# endereco a esquerda = null
				sw $zero, 0($v0)
				# endereco a esquerda = null
				sw $zero, 4($v0)
				# flag indicando se eh noh terminal = false
				sw $zero, 8($v0)

				sw 0($t1), $v0 # novo nó é armazenado como filho direito do nó atual
				# descer para novo nó e continuar loop

			# se &dir != null, descer para ele e voltar ao loop
			insert_descend_left:
				# descendo na árvore, t1 = &dir do nó em que estávamos
				lw $t1, 0($t1)
				addi $a1, $a1, 1 # ir para próximo caractere na chave
				j insert_node_loop

	# +---------+
	# | REMOÇÃO |
	# +---------+

	# +-------+
	# | BUSCA |
	# +-------+

	# +--------------+
	# | VISUALIZAÇÃO |
	# +--------------+

	# +--------------+
	# | CHECAR INPUT |
	# +--------------+

	exit:
		li $v0, 4 # imprimir string
		la $a0, str_exit
		syscall

		li $v0, 10 # finalizar execução
		syscall
