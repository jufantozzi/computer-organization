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
#define IF_DEBUG if(DEBUG)

#define boolean char
#define TRUE  1
#define FALSE 0

/*******************************************************/

// +---------+
// |  CLOCK  |
// +---------+
boolean clock = FALSE;

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
typedef char word[32];
word MEMORY[MAX_SIZE];

int dynamic_mem_pointer;
int memory_pointer;

/*******************************************************/

// +----+
// | IR |
// +----+
char op_code[6];
char function[6];
char rs[5];
char rt[5];
char rd[5];
char immediate[16];
char jump_addr[26];

// +------------------------+
// | BANCO DE REGISTRADORES |
// +------------------------+
typedef char reg[32];
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

reg A;      // read data 1
reg B;      // read data 2

reg ALUOut; // saída da ULA

reg MAR;    // memory address register
reg IR;     // instruction register
reg MBR;    // memory buffer register

int PC;     // program counter

/*******************************************************/

// +--------------------+
// | SINAIS DE CONTROLE |
// +--------------------+
char RegDst0;       // 00
char RegDst1;       // 01
char RegWrite;      // 02
char ALUSrcA;       // 03
char ALUSrcB0;      // 04
char ALUSrcB1;      // 05
char ALUOp0;        // 06
char ALUOp1;        // 07
char PCSource0;     // 08
char PCSource1;     // 09
char PCWriteCond;   // 10
char PCWrite;       // 11
char IorD;          // 12
char MemRead;       // 13
char MemWrite;      // 14
char BNE;           // 15
char IRWrite;       // 16
char MemtoReg0;     // 17
char MemtoReg1;     // 18

// +--------------------+
// | SINAIS DE ESTADO   |
// +--------------------+
char state[4];

/*******************************************************/

// +---------------------+
// | UNIDADES FUNCIONAIS |
// +---------------------+
/**
* funcao()
* SINAL DE CONTROLE: IORD
* 0 - PEGA O VALOR DE PC
* 1 - PEGA O VALOR DE ALUOUT
* SAIDA: PARA ADDRESS EM MEMORY
*/
void MUX_MEMORY() {
    switch (IorD) {
            MAR = PC;
            break;
        case 1:
            MAR = ALUout;
            break;
    }
}

/**
 * funcao()
 * Descricao
 */
void MEMORY_BANK() {
    if (MemRead) {
        MBR = MEMORY[MAR];
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
void MUX_WRITE_REG() {
    /* code */
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
    /* code */
}


/**
 * funcao()
 * SINAL DE CONTROLE: ALUSRCA
 * 0 - PEGA O VALOR DE PC
 * 1 - PEGA O VALOR DE A (READ DATA 1 - REGISTERS)
 * SAIDA: ENTRADA 1 DA ALU
 */
void MUX_ALU_1() {
    /* code */
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
    /* code */
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
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void MUX_BNE() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void IR_SET() {
    int i;

    // IR = MBR
    if (IRWrite) {
        for (i = 0; i < 6; i++) {
            op_code[i] = MBR[31-i];
            function[i] = MBR[5-i];
        }

        for (i = 0; i < 5; i++) {
            rs[i] = MBR[25-i];
            rt[i] = MBR[20-i];
            rd[i] = MBR[15-i];
        }

        for (i = 0; i < 16; i++) {
            immediate[i] = MBR[15-i];
        }

        for (i = 0; i < 26; i++) {
            jump_addr[i] = MBR[25-i];
        }

    }
}

/**
 * funcao()
 * Descricao
 */
void MEM_DATA_REGISTER() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void REGISTER_BANK() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void SIGNAL_EXTEND_16_TO_32() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void SHIFT_LEFT_2_PC() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void SHIFT_LEFT_2_MUX_ALU_2() {
    /* code */
}


/**
 * funcao()
 * Descricao
 */
void ALU_CONTROL() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void ALU() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void CONTROL(char* op) {

}

/*******************************************************/

// +----------------------------------+
// | FUNÇÕES - BANCO DE REGISTRADORES |
// +----------------------------------+

/**
 * funcao()
 * Descricao
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


/**
 * funcao()
 * Descricao
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

void initialize() {
    int i, j;
    reg* current_reg = NULL;

    // inicializar memória
    memory_pointer = 0;
    dynamic_mem_pointer = 0;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < 32; j++) {
            MEMORY[i][j] = 0;
        }
    }

    // inicializar banco de registradores
    for (i = 0; i < 32; i++) {
        current_reg = get_register(i);
        for (j = 0; j < 32; j++) {
            (*current_reg)[j] = 0;
        }
    }

    // inicializar PC p/ primeira posição válida
    PC = 0;

}

/**
 * ESTADO 0
 * start()
 * Inicializa todos os sinais de controle,
 * memória e registradores
 */
void start() {
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
}

/**
 * funcao()
 * Descricao
 */
void finalize() {
    int i, j;
    char* regid = NULL; // identificador do registrador (nome)
    reg* current_reg = NULL; // ponteiro para registrador

    // imprimir todos os registradores temporários
    printf("\nREGISTRADORES:\n");
    for (i = 0; i < 32; i++) {
        // imprimir nome do registrador
        current_reg = get_register(i);
        regid = register_name(i);
        printf("%s:\t", regid);
        // imprimir conteúdo do registrador
        for (j = 0; j < 32; j++) {
            printf("%d", (*current_reg)[j]);
        }
        printf("\n");
    }

    printf("\nMEMÓRIA:\n");
    // imprimir as 32 primeiras posições de memória
    dynamic_mem_pointer = 0;
    for (i = dynamic_mem_pointer; i < dynamic_mem_pointer + 32; i++) {
        printf("MEMORIA[%d] = \t", i - dynamic_mem_pointer);
        for (j = 0; j < 32; j++) {
            printf("%d", MEMORY[i][j]);
        }
        printf("\n");
    }
}

/**
 * funcao()
 * Descricao
 */
int bin2dec(int n) {
    int decimal = 0;
    int i = 0;
    int remainder;

    while (n != 0) {
        remainder = n % 10;
        n /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }
    return decimal;
}

/*******************************************************/

// +-----------+
// | SIMULAÇÃO |
// +-----------+
int main(int argc, char const *argv[]) {

    int i;
    char instruction[32];
    const char* source = NULL;

    // verificar se código fonte foi passado como argumento
    if (argc < 2) {
        printf("ERRO: Código fonte não foi passado como argumento.\n");
        exit(1);
    }

    // abrir código fonte
    source = argv[1];
    FILE* bin = NULL;
    bin = fopen(source, "r");

    // inicializar memória e registradores
    initialize();

    // checar integridade do código fonte
    if (bin == NULL) {
        printf("ERRO: Código fonte não carregado.\n");
        exit(0);
    }

    // ler instruções do có{digo fonte
    while (fscanf(bin, "%s ", &instruction) != EOF) {
        // armazenar instruções na memória
        for (i = 0; i < 32; i++) {
            MEMORY[memory_pointer][i] = instruction[i];
        }
        // alinhamento por palavra
        memory_pointer += 1;
    }
    // memória dinâmica começa depois da memória de instruções
    dynamic_mem_pointer = memory_pointer;

    // fechar código fonte
    fclose(bin);
    bin = NULL;

    IF_DEBUG printf("dynamic_mem_pointer = %d\n", dynamic_mem_pointer);

    /* CICLOS */
    // primeiro ciclo: inicializar sinais de controle
    start();

    // executar instruções
    while (PC < dynamic_mem_pointer) {
        clock = TRUE;
        // carrega endereço de PC ou ALUout em MAR
        MUX_MEMORY();
        // carrega dado/instrução da memória em MBR
        MEMORY_BANK();
        // carregar valores de IR
        IR_SET();
        //


    }

    // finalizar a execução
    // exibir os registradores e memória
    finalize();

    return 0;
}
