/* SSC-0112 - Organizacao de Computadores Digitais */
/* Turma A - 2018/01                               */
/* Prof. Paulo Sergio Lopes de Souza               */
/*                                                 */
/* Trabalho 2                                      */
/* Simulação de uma CPU MIPS Multiciclo de 32 bits */
/*                                                 */
/* Aluno                          NUSP             */
/* Felipe Scrochio Custodio       9442688          */
/* Gabriel Henrique Scalici       9292970          */
/* Juliano Fantozzi               9791218          */
/* Andre Luis Storino Junior      9293668          */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 1
#define IF_DEBUG if (DEBUG)

#define GETBIT(x,p) (((x)>>(p))&1)

#define TRUE  1
#define FALSE 0

typedef char boolean;
typedef char byte;
typedef char bit;
typedef int word;

/*******************************************************/

// +---------+
// |  CLOCK  |
// +---------+
boolean clock = FALSE;

// +----------------------+
// |  FUNÇÕES AUXILIARES  |
// +----------------------+

/*
 * bin2dec
 * ----------------------------
 *   Retorna valor decimal convertido de um binário
 *
 *   bit* binary: string que representa o binário
 *   int size: tamanho desse binário
 *
 */
 int bin2dec(bit* binary, int size) {
	int i;
	int sum = 0;
	for (i = 0; i < size; i++) {
		if ((int)(binary[i])) {
			sum += pow(2, i);
		}
	}
	return sum;
 }

/*******************************************************/

// Decisões de projeto
// MUX possui como identificador a unidade funcional que ele dá a resposta
// MUX_IDENTIFICADOR

// - ANDI usa código de operação 11 do ALUOp

/*******************************************************/

// +---------+
// | MEMÓRIA |
// +---------+
#define MAX_SIZE 128
byte MEMORY[MAX_SIZE];
byte* memory_pointer;

/*******************************************************/

// +----+
// | IR |
// +----+
bit op_code[6];
bit function[6];
bit rs[5];
bit rt[5];
bit rd[5];
bit immediate[16];
//jump_addr começará com 26 bits quando sair do IR
bit jump_addr[32];

// +------------------------+
// | BANCO DE REGISTRADORES |
// +------------------------+
typedef unsigned int reg;
reg zero;   // 0
reg at;     // 1
reg v0;     // 2
reg v1;     // 3
reg a0;     // 4
reg a1;     // 5
reg a2;     // 6
reg a3;     // 7
reg t0;     // 8
reg t1;     // 9
reg t2;     // 10
reg t3;     // 11
reg t4;     // 12
reg t5;     // 13
reg t6;     // 14
reg t7;     // 15
reg s0;     // 16
reg s1;     // 17
reg s2;     // 18
reg s3;     // 19
reg s4;     // 20
reg s5;     // 21
reg s6;     // 22
reg s7;     // 23
reg t8;     // 24
reg t9;     // 25
reg k0;     // 26
reg k1;     // 27
reg gp;     // 28
reg sp;     // 29
reg fp;     // 30
reg ra;     // 31

bit write_register[5];

reg MAR;    // memory address register
reg IR;     // instruction register
reg MDR;    // memory buffer register

word reg_write_data;
reg* write_reg; // ponteiro para o registrador que receberá write data

reg PC;     // program counter
word pc_write_data; // saida do mux_pc

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
reg* get_register(int id) {
	switch (id) {
		case 0:
			return &zero;
			break;
		case 1:
			return &at;
			break;
		case 2:
			return &v0;
			break;
		case 3:
			return &v1;
			break;
		case 4:
			return &a0;
			break;
		case 5:
			return &a1;
			break;
		case 6:
			return &a2;
			break;
		case 7:
			return &a3;
			break;
		case 8:
			return &t0;
			break;
		case 9:
			return &t1;
			break;
		case 10:
			return &t2;
			break;
		case 11:
			return &t3;
			break;
		case 12:
			return &t4;
			break;
		case 13:
			return &t5;
			break;
		case 14:
			return &t6;
			break;
		case 15:
			return &t7;
			break;
		case 16:
			return &s0;
			break;
		case 17:
			return &s1;
			break;
		case 18:
			return &s2;
			break;
		case 19:
			return &s3;
			break;
		case 20:
			return &s4;
			break;
		case 21:
			return &s5;
			break;
		case 22:
			return &s6;
			break;
		case 23:
			return &s7;
			break;
		case 24:
			return &t8;
			break;
		case 25:
			return &t9;
			break;
		case 26:
			return &k0;
			break;
		case 27:
			return &k1;
			break;
		case 28:
			return &gp;
			break;
		case 29:
			return &sp;
			break;
		case 30:
			return &fp;
			break;
		case 31:
			return &ra;
			break;
	}
	printf("ERRO: Registrador de número %d não encontrado.\n", id);
	exit(0);
}

/*******************************************************/

// +--------------------+
// |        ULA         |
// +--------------------+
reg A; // read data 1
reg B; // read data 2
bit ALUInput[3]; // bits que definem quais operações a ULA deverá executar
word ALUResult; // saída da ULA
reg ALUOut; // registrador que armazena a saída da ULA
word immediate_extended; // saída do sign extend
word operator_1; // primeiro operando
word operator_2; // segundo operando
bit ALU_zero; // bit que indica se resultado é 0 ou não

/*******************************************************/

// +--------------------+
// | SINAIS DE CONTROLE |
// +--------------------+
bit RegDst0;       // 00
bit RegDst1;       // 01
bit RegWrite;      // 02
bit ALUSrcA;       // 03
bit ALUSrcB0;      // 04
bit ALUSrcB1;      // 05
bit ALUOp0;        // 06
bit ALUOp1;        // 07
bit PCSource0;     // 08
bit PCSource1;     // 09
bit PCWriteCond;   // 10
bit PCWrite;       // 11
bit IorD;          // 12
bit MemRead;       // 13
bit MemWrite;      // 14
bit BNE;           // 15
bit IRWrite;       // 16
bit MemtoReg0;     // 17
bit MemtoReg1;     // 18

// auxiliar para BNE:
// sinal de controle que chega ao PC
bit PCControl;

// +--------------------+
// | SINAIS DE ESTADO   |
// +--------------------+
bit state[5];
bit next_state[5];

/*******************************************************/

// +---------------------+
// | UNIDADES FUNCIONAIS |
// +---------------------+

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void MUX_MEMORY() {
	switch (IorD) {
			MAR = PC;
			break;
		case 1:
			MAR = ALUOut;
			break;
	}
}

/**
* funcao()
* SINAL DE CONTROLE: IORD
* 0 - PEGA O VALOR DE PC
* 1 - PEGA O VALOR DE ALUOUT
* SAIDA: PARA ADDRESS EM MEMORY
*/
void PROGRAM_COUNTER() {
	if (PCControl) {
		PC = pc_write_data;
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void MEMORY_BANK() {
	if (MemRead) {
		MDR = MEMORY[MAR];
		IR = MEMORY[MAR];
	}

	if (MemWrite) {
		// B = registrador read data 2
		MEMORY[MAR] = B;
	}
}

/**
 * funcao()
 * SINAL DE CONTROLE: REGDEST0 E REGDEST1
 * 0 - PEGA O VALOR DE INSTRUCTION[20 .. 16]
 * 1 - PEGA O VALOR DE INSTRUCTION[15 .. 11]
 * 2 - PEGA O VALOR 31 (NUMÉRICO)
 * 3 - NÃO EXISTE
 * SAIDA: PARA WRITE REGISTER (REGISTERS)
 */

// write_reg = get_register(bin2dec(write_register, 5));

void MUX_WRITE_REG() {
	int i;

  switch (RegDst1) {
	  case 0:
			switch (RegDst0) {
				case 0:
					// escrever no registrador apontado por rt
					write_reg = get_register(bin2dec(rt, 5));
					break;
				case 1:
					// escrever no registrador apontado por rd
					write_reg = get_register(bin2dec(rd, 5));
					break;
			}
		  break;
	  case 1:
		  // registrador 31 = 11111 = $ra
		  write_reg = get_register(31);
		  break;
  }
}


/**
 * funcao()
 * SINAL DE CONTROLE: MEMTOREG0 E MEMTOREG1
 * 0 - PEGA O VALOR DE ALUOUT
 * 1 - PEGA O VALOR DE MEM_DATA_REGISTER
 * 2 - PEGA O VALOR DE PC
 * 3 - NÃO EXISTE
 * SAIDA: PARA WRITE DATA (REGISTERS)
 */
void MUX_WRITE_DATA() {
  int i;
  switch (MemtoReg1) {
	  case 0:
			switch (MemtoReg0) {
				case 0:
					// escreve de ALUOut em Banco de Registradores
					reg_write_data = ALUOut;
					break;
				case 1:
					// escreve de MDR em banco de registradores[write_register]
					reg_write_data = MDR;
					break;
			}
		  break;
	  case 1:
		  // escreve de PC em banco de registradores[write_register]
		  reg_write_data = PC;
		  break;
  }
}


/**
 * funcao()
 * SINAL DE CONTROLE: ALUSRCA
 * 0 - PEGA O VALOR DE PC
 * 1 - PEGA O VALOR DE A (READ DATA 1 - REGISTERS)
 * SAIDA: ENTRADA 1 DA ALU
 */
void MUX_ALU_1() {
	switch (ALUSrcA) {
		case 0:
			// PRIMEIRO OPERANDO DA ULA RECEBE PC
			operator_1 = PC;
			break;
		case 1:
			//PRIMEIRO OPERANDO DA ULA RECEBE A
			operator_1 = A;
		  	break;
	}
}


/**
 * funcao()
 * SINAL DE CONTROLE: ALUSRCB0 E ALUSRCB1
 * 0 - PEGA O VALOR DE B (READ DATA 2 - REGISTERS)
 * 1 - PEGA O VALOR 4 (NÚMERO)
 * 2 - PEGA O VALOR DE INSTRUCTION[15 .. 0] (DEPOIS DE SIGNAL_EXTEND_16_TO_32)
 * 3 - PEGA O VALOR DE INSTRUCTION[15 .. 0] (DEPOIS DE SIGNAL_EXTEND_16_TO_32 E SHIFT_LEFT_2_MUX_ALU_2)
 * SAIDA: ENTRADA 2 DA ALU
 */
void MUX_ALU_2() {
  switch (ALUSrcB1) {
	  case 0:
			switch (ALUSrcB0) {
				case 0:
					//SEGUNDO OPERANDO DA ULA RECEBE B
					operator_2 = B;
					break;
				case 1:
					//SEGUNDO OPERANDO DA ULA RECEBE 4
					operator_2 = 4;
					break;
			}
			break;
	  case 1:
			switch (ALUSrcB0) {
				case 0:
					//SEGUNDO OPERANDO DA ULA RECEBE IMEDIATO EXTENDIDO
					operator_2 = immediate_extended;
					break;
				case 1:
					//SEGUNDO OPERANDO DA ULA RECEBE IMEDIATO EXTENDIDO << 2
					operator_2 = immediate_extended << 2;
					break;
			}
		  break;
    }
}

/**
 * funcao()
 * SINAL DE CONTROLE: PCSORCE0 E PCSOURCE1
 * 0 - PEGA O VALOR DE RESULTADO DA ULA
 * 1 - PEGA O VALOR DE ALUOUT
 * 2 - PEGA O VALOR DE PC SHIFT 2 LEFT
 * 3 - PEGA O VALOR DE A (REGISTRADORES)
 * SAIDA: PARA PC
 */
void MUX_PC() {
	int i;
	switch (PCSource1) {
		case 0:
			switch (PCSource0) {
				case 0:
					// PC RECEBE ALU RESULT (SAIDA DA ULA)
					pc_write_data = ALUResult;
					break;
				case 1:
					// PC RECEBE ALUOUT
					pc_write_data = ALUOut;
					break;
			}
			break;
		case 1:
			switch (PCSource0) {
				case 0:
					// PC RECEBE PC[31..28] + (jump_addr[26..0] << 2)
					pc_write_data = 0;
					for(i = 0; i < 4; i++)
						pc_write_data += GETBIT(PC, 31-i) * ((unsigned int)pow(2, 31-i));
					pc_write_data += (bin2dec(jump_addr, 26) << 2);
					break;
				case 1:
					// PC RECEBE A
					pc_write_data = A;
					break;
			}
			break;
	  }
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void MUX_BNE() {
	switch (BNE) {
	  case 0:
			PCControl = ((ALU_zero & PCWriteCond) | PCWrite);
			break;
		case 1:
			PCControl = (((!ALU_zero) & PCWriteCond) | PCWrite);
			break;
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void IR_SET() {
	int i;

	// IR = MDR
	if (IRWrite) {
		for (i = 0; i < 6; i++) {
			op_code[i] = GETBIT(IR, 26+i);
			function[i] = GETBIT(IR, i);
		}

		for (i = 0; i < 5; i++) {
			rs[i] = GETBIT(IR, 21+i);
			rt[i] = GETBIT(IR, 16+i);
			rd[i] = GETBIT(IR, 11+i);
		}

		for (i = 0; i < 16; i++) {
			immediate[i] = GETBIT(IR, i);
		}

		for (i = 0; i < 26; i++) {
			jump_addr[i] = GETBIT(IR, i);
		}
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void REGISTER_BANK() {
	if (RegWrite) {
		(*write_reg) = reg_write_data;
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void SIGNAL_EXTEND_16_TO_32() {
	immediate_extended = bin2dec(immediate, 16);
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void ALU_CONTROL() {
	switch(ALUOp1) {
		// não precisa checar o campo de função (instruções LW, SW, Branch)
		case 0:
			switch(ALUOp0) {
				case 0:	// add
					ALUInput[2] = 0;
					ALUInput[1] = 1;
					ALUInput[0] = 0;
					break;
				case 1:	// subtract
					ALUInput[2] = 1;
					ALUInput[1] = 1;
					ALUInput[0] = 0;
					break;
			}
			break;
		// precisa checar o campo de função e ALUOp0 sempre será 0
		case 1:
			// (ALUOp = 10 e Function = 100000) operação = add
			if ((function[5] == 1) && ((function[4] == 0) && ((function[3] == 0) && ((function[2] == 0) && ((function[1] == 0) && ((function[0] == 0))))))) {
				ALUInput[2] = 0;
				ALUInput[1] = 1;
				ALUInput[0] = 0;
			}
			// (ALUOp = 10 e Function = 100010) operação = subtract
			else if ((function[5] == 1) && ((function[4] == 0) && ((function[3] == 0) && ((function[2] == 0) && ((function[1] == 1) && ((function[0] == 0))))))) {
				ALUInput[2] = 1;
				ALUInput[1] = 1;
				ALUInput[0] = 0;
			}
			// (ALUOp = 10 e Function = 100100) operação = and
			else if ((function[5] == 1) && ((function[4] == 0) && ((function[3] == 0) && ((function[2] == 1) && ((function[1] == 0) && ((function[0] == 0))))))) {
				ALUInput[2] = 0;
				ALUInput[1] = 0;
				ALUInput[0] = 0;
			}
			// (ALUOp = 10 e Function = 100101) operação = or
			else if ((function[5] == 1) && ((function[4] == 0) && ((function[3] == 0) && ((function[2] == 1) && ((function[1] == 0) && ((function[0] == 1))))))) {
				ALUInput[2] = 0;
				ALUInput[1] = 0;
				ALUInput[0] = 1;
			}
			// (ALUOp = 10 e Function = 101010) operação = set on less than
			else if ((function[5] == 1) && ((function[4] == 0) && ((function[3] == 1) && ((function[2] == 0) && ((function[1] == 1) && ((function[0] == 0))))))) {
				ALUInput[2] = 1;
				ALUInput[1] = 1;
				ALUInput[0] = 1;
			}
			break;
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void ALU() {
	// (ALUInput = 010) operação = add
	if ((ALUInput[2] == 0) && (ALUInput[1] == 1) && (ALUInput[0] == 0)) {
		ALUResult = operator_1 + operator_2;
	}
	// (ALUInput = 110) operação = subtract
	else if ((ALUInput[2] == 1) && (ALUInput[1] == 1) && (ALUInput[0] == 0)) {
		ALUResult = operator_1 - operator_2;
	}
	// (ALUInput = 000) operação = and
	else if ((ALUInput[2] == 0) && (ALUInput[1] == 0) && (ALUInput[0] == 0)) {
		ALUResult = operator_1 & operator_2;
	}
	// (ALUInput = 001) operação = or
	else if ((ALUInput[2] == 0) && (ALUInput[1] == 1) && (ALUInput[0] == 1)) {
		ALUResult = operator_1 | operator_2;
	}
	// (ALUInput = 111) operação = set on less than
	else if ((ALUInput[2] == 1) && (ALUInput[1] == 1) && (ALUInput[0] == 1)) {
		(operator_1 < operator_2) ? (ALUResult = 1) : (ALUResult = 0);
	}
}


/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void ALU_OUT() {
	ALUOut = ALUResult;
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
 void CONTROL(char* op) {

	 //Setando os sinais
	 RegDst0 = (state[0] & state[1] & state[2] & !state[3] & !state[4]);

	 RegDst1 = (state[0] & state[1] & !state[2] & state[3] & !state[4]) | (state[0] & !state[1] & !state[2] & !state[3] & state[4]);

	 RegWrite = (!state[0] & !state[1] & state[2] & !state[3] & !state[4]) | (state[0] & state[1] & state[2] & !state[3] & !state[4]) |
					 (state[0] & state[1] & !state[2] & state[3] & !state[4]) | (state[0] & !state[1] & state[2] & state[3] & !state[4]) |
						 (!state[0] & !state[1] & !state[2] & !state[3] & state[4]) | (state[0] & !state[1] & !state[2] & !state[3] & state[4]); //conferido até aqui

	 ALUSrcA = (!state[0] & state[1] & !state[2] & !state[3] & !state[4]) | (!state[0] & state[1] & state[2] & !state[3] & !state[4]) |
					 (!state[0] & !state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & !state[1] & state[2] & state[3] & !state[4]) |
						 (!state[0] & state[1] & state[2] & state[3] & !state[4]) | (state[0] & state[1] & state[2] & state[3] & !state[4]);

	 ALUSrcB0 = (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]) | (state[0] & !state[1] & !state[2] & !state[3] & !state[4]);

	 ALUSrcB1 = (state[0] & !state[1] & !state[2] & !state[3] & !state[4]) | (!state[0] & state[1] & !state[2] & !state[3] & !state[4]) |
					 (!state[0] & !state[1] & state[2] & state[3] & !state[4]) | (state[0] & state[1] & state[2] & state[3] & !state[4]);

	 ALUOp0 = (!state[0] & !state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & state[1] & state[2] & state[3] & !state[4]);

	 ALUOp1 = (!state[0] & state[1] & state[2] & !state[3] & !state[4]) | (state[0] & state[1] & state[2] & state[3] & !state[4]);

	 PCSource0 = (!state[0] & !state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & state[1] & !state[2] & state[3] & !state[4]) |
					 (state[0] & state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & state[1] & state[2] & state[3] & !state[4]);

	 PCSource1 = (state[0] & !state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & state[1] & !state[2] & state[3] & !state[4]) |
					 (state[0] & state[1] & !state[2] & state[3] & !state[4]) | (state[0] & !state[1] & !state[2] & !state[3] & state[4]);

	 PCWriteCond = (!state[0] & !state[1] & !state[2] & state[3] & !state[4]) | (!state[0] & state[1] & state[2] & state[3] & !state[4]);

	 PCWrite = (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]) | (state[0] & !state[1] & !state[2] & state[3] & !state[4]) |
					 (!state[0] & state[1] & !state[2] & state[3] & !state[4]) | (state[0] & state[1] & !state[2] & state[3] & !state[4]) |
						 (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]);

	 IorD = (state[0] & state[1] & !state[2] & !state[3] & !state[4]) | (state[0] & !state[1] & state[2] & !state[3] & !state[4]);

	 MemRead = (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]) | (state[0] & state[1] & !state[2] & !state[3] & !state[4]);

	 MemWrite = (state[0] & !state[1] & state[2] & !state[3] & !state[4]);

	 BNE = (!state[0] & state[1] & state[2] & state[3] & !state[4]);

	 IRWrite = (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]);

	 MemtoReg0 = (!state[0] & !state[1] & state[2] & !state[3] & !state[4]);

	 MemtoReg1 = (state[0] & state[1] & !state[2] & state[3] & !state[4]) | (state[0] & !state[1] & state[2] & !state[3] & state[4]);

	 //Setando next state
	 next_state[0] = (!state[0] & !state[1] & !state[2] & !state[3] & !state[4]) | (!state[0] & state[1] & !state[2] & !state[3] & !state[4]) |
					 (!state[0] & state[1] & state[2] & !state[3] & !state[4]) |
						 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
						 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & op_code[4] & !op_code[5]) |
						 (state[0] & !state[1] & state[2] & state[3] & !state[4]) |
						 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]);

	 next_state[1] = (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & op_code[1] & !op_code[2] & !op_code[4] & op_code[5]) |
					 (!state[0] & state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (!state[0] & state[1] & state[2] & !state[3] & !state[4]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & op_code[3] & !op_code[4] & !op_code[5]);

	 next_state[2] = (state[0] & state[1] & !state[2] & !state[3] & !state[4]) |
					 (!state[0] & state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & op_code[1] & !op_code[2] & op_code[3] & !op_code[4] & op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (!state[0] & state[1] & state[2] & !state[3] & !state[4]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & !op_code[2] & op_code[3] & !op_code[4] & !op_code[5]) |
					 (!state[0] & !state[1] & state[2] & state[3] & !state[4]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & op_code[3] & !op_code[4] & !op_code[5]);

	 next_state[3] = (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (!state[0] & !state[1] & state[2] & state[3] & !state[4]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & !op_code[1] & op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & !op_code[0] & !op_code[1] & op_code[2] & op_code[3] & !op_code[4] & !op_code[5]);

	 next_state[4] = (state[0] & !state[1] & !state[2] & !state[3] & !state[4] & op_code[0] & op_code[1] & !op_code[2] & !op_code[3] & !op_code[4] & !op_code[5]) |
					 (state[0] & state[1] & state[2] & state[3] & !state[4]);

 }

/*******************************************************/

// +----------------------------------+
// | FUNÇÕES - BANCO DE REGISTRADORES |
// +----------------------------------+

/*
 * register_name
 * ----------------------------
 *   Retorna o nome (string) do registrador
 *   com base em seu número
 *
 *   int id: valor identificador do registrador
 *
 */
char* register_name(int id) {
	switch (id) {
		case 0:
			return "$zero";
			break;
		case 1:
			return "$at";
			break;
		case 2:
			return "$v0";
			break;
		case 3:
			return "$v1";
			break;
		case 4:
			return "$a0";
			break;
		case 5:
			return "$a1";
			break;
		case 6:
			return "$a2";
			break;
		case 7:
			return "$a3";
			break;
		case 8:
			return "$t0";
			break;
		case 9:
			return "$t1";
			break;
		case 10:
			return "$t2";
			break;
		case 11:
			return "$t3";
			break;
		case 12:
			return "$t4";
			break;
		case 13:
			return "$t5";
			break;
		case 14:
			return "$t6";
			break;
		case 15:
			return "$t7";
			break;
		case 16:
			return "$s0";
			break;
		case 17:
			return "$s1";
			break;
		case 18:
			return "$s2";
			break;
		case 19:
			return "$s3";
			break;
		case 20:
			return "$s4";
			break;
		case 21:
			return "$s5";
			break;
		case 22:
			return "$s6";
			break;
		case 23:
			return "$s7";
			break;
		case 24:
			return "$t8";
			break;
		case 25:
			return "$t9";
			break;
		case 26:
			return "$k0";
			break;
		case 27:
			return "$k1";
			break;
		case 28:
			return "$gp";
			break;
		case 29:
			return "$sp";
			break;
		case 30:
			return "$fp";
			break;
		case 31:
			return "$ra";
			break;
	}
	printf("ERRO: Registrador de número %d não encontrado.\n", id);
	exit(0);
}




/*******************************************************/


/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void initialize(const char* source) {
	int i;
	// instrução a ser lida do arquivo
    int instruction;
    long int big_instruction;
    char* bytes = NULL;
	// conta quantas instruções foram lidas para indexar memória
	int instr_counter;
	reg* current_reg = NULL;

	// abrir arquivo do código fonte
	FILE* bin = NULL;
	bin = fopen(source, "r");

	// checar integridade do código fonte
	if (bin == NULL) {
		printf("ERRO: Código fonte não carregado.\n");
		exit(0);
	}

	// inicializar memória
	for (i = 0; i < MAX_SIZE; i++) {
		MEMORY[i] = 0;
	}

	// ler instruções do código fonte
    memory_pointer = &(MEMORY);
    instr_counter = 0;
	while (fscanf(bin, "%d ", &instruction) != EOF) {
        // verificar se instrução é maior que palavra
        if (instruction <= 0) {
            // overflow, precisamos cortar em duas palavras
            // volta para ler instrução maior
            printf("OVERFLOW\n");
            fseek(bin, -8, SEEK_CUR);
            fscanf(bin, "%ld ", &big_instruction);

            // armazenar na posição atual da memória
            memcpy(memory_pointer, &big_instruction, 4);
            memory_pointer += 4;

            // armazenar bytes remanescentes na próxima palavra
            memcpy(memory_pointer, ((&big_instruction) + 4), 4);
            memory_pointer += 4;

        } else {
            // armazenar instruções na memória
            memcpy(memory_pointer, &instruction, 4);
            memory_pointer += 4;
        }
	}

	// fechar arquivo do código fonte
	fclose(bin);
	bin = NULL;

	// inicializar banco de registradores
	for (i = 0; i < 32; i++) {
		current_reg = get_register(i);
		(*current_reg) = 0;
	}

	// inicializando o destino de escrita no banco de registradores
	for(i = 0; i < 5; i++) {
		write_register[i] = 0;
	}

	// inicializar PC p/ primeira posição válida
	PC = 0;

}

 /*
  * start
  * ----------------------------
  * Inicializa todos os sinais de controle,
  * memória e registradores
  * Estado 0
  *
  */
void start() {
	int i;
	// inicializar sinais de controle
	// inicializa para o ciclo de busca
	RegDst0     = 0;
	RegDst1     = 0;
	RegWrite    = 0;
	ALUSrcA     = 0;
	// ALUSrcB = 01
	ALUSrcB0    = 1;
	ALUSrcB1    = 0;
	ALUOp0      = 0;
	ALUOp1      = 0;
	PCSource0   = 0;
	PCSource1   = 0;
	PCWriteCond = 0;
	PCWrite     = 0;
	IorD        = 0;
	MemRead     = 1;
	MemWrite    = 0;
	BNE         = 0;
	IRWrite     = 0;
	MemtoReg0   = 0;
	MemtoReg1   = 0;

	// inicializa o vetor de estado
	for(i = 0; i < 5; i++) {
		state[i] = 0;
	}
}

/*
 * funcao
 * ----------------------------
 *   O que ela faz:
 *          * X recebe Y
 *
 *   argumento1:
 *   argumento2:
 *
 */
void finalize() {
	int i, j;
	char* regid = NULL; // identificador do registrador (nome)
	reg* current_reg = NULL; // ponteiro para registrador

	printf("PC = %d\t", PC);
	printf("IR = %d\t", IR);
	printf("MDR = %d\t", MDR);
	printf("\n");
	printf("A = %d\t", A);
	printf("B = %d\t", B);
	printf("AluOut = %d\n", ALUOut);
	printf("Controle = []\n");
	printf("\n");

	// imprimir todos os registradores temporários
	printf("Banco de Registradores\n");
	for (i = 0; i < 8; i++) {
		for (j = i; j < (i + (8 * 4)); j+=8) {
			regid = register_name(j);
			current_reg = get_register(j);
			printf("R%02d (%s) = %d\t", j, regid, (*current_reg));
		}
		printf("\n");
	}
	printf("\n");

	printf("Memória (endereços a byte)\n");
	// imprimir as 32 primeiras posições de memória
	memory_pointer = &(MEMORY);
	for (i = 0; i < 28; i += 4) {
		for (j = i; j < (i + (32 * 4)); j += 32) {
            printf("[%02d] = %d\t", j, memory_pointer[j]);
		}
		printf("\n");
	}
}


/*******************************************************/

// +-----------+
// | SIMULAÇÃO |
// +-----------+
int main(int argc, char const *argv[]) {

	int i;
	const char* source = NULL;

	// verificar se código fonte foi passado como argumento
	if (argc < 2) {
		printf("ERRO: Código fonte não foi passado como argumento.\n");
		exit(1);
	}

	// abrir código fonte
	source = argv[1];

	// inicializar memória e registradores
	initialize(source);

	// inicializar sinais de controle
	start();

	finalize();

	// ciclos
	// executar instruções
	// while (TRUE) {
		// ciclo
	// }

	return 0;
}
