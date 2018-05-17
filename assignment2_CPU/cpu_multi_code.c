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

/*******************************************************/

// Decisões de projeto
// - MUX possui como identificador a unidade funcional que ele dá a resposta
// - MUX_IDENTIFICADOR

/*******************************************************/

// +---------+
// | MEMÓRIA |
// +---------+
#define MAX_SIZE 100
typedef char word[32];
word MEMORY[MAX_SIZE];

int dynamic_mem_pointer;
int memory_pointer;

/*******************************************************/

// +------------------------+
// | BANCO DE REGISTRADORES |
// +------------------------+
typedef char reg[32];
reg zero;  // 0
reg at;    // 1
reg v0;    // 2
reg v1;    // 3
reg a0;    // 4
reg a1;    // 5
reg a2;    // 6
reg a3;    // 7
reg t0;    // 8
reg t1;    // 9
reg t2;    // 10
reg t3;    // 11
reg t4;    // 12
reg t5;    // 13
reg t6;    // 14
reg t7;    // 15
reg s0;    // 16
reg s1;    // 17
reg s2;    // 18
reg s3;    // 19
reg s4;    // 20
reg s5;    // 21
reg s6;    // 22
reg s7;    // 23
reg t8;    // 24
reg t9;    // 25
reg k0;    // 26
reg k1;    // 27
reg gp;    // 28
reg sp;    // 29
reg fp;    // 30
reg ra;    // 31

/*******************************************************/

// +--------------------+
// | SINAIS DE CONTROLE |
// +--------------------+
char RegDst0;        // 00
char RegDst1;        // 01
char EscReg;         // 02
char UALFonteA;      // 03
char UALFonteB0;     // 04
char UALFonteB1;     // 05
char UALOp0;         // 06
char UALOp1;         // 07
char FontePC0;       // 08
char FontePC1;       // 09
char PCEscCond;      // 10
char PCEsc;          // 11
char IouD;           // 12
char LerMem;         // 13
char EscMem;         // 14
char BNE;            // 15
char IREsc;          // 16
char MemParaReg0;    // 17
char MemParaReg1;    // 18

/*******************************************************/

// +---------------------+
// | UNIDADES FUNCIONAIS |
// +---------------------+

/**
 * funcao()
 * Descricao
 */
void PC() {
    /* code */
}

/**
 * funcao()
 * Descricao
 */
void MUX_MEMORY() {
    /* code */
}


/**
 * funcao()
 * Descricao
 */
void MUX_WRITE_REG() {
    /* code */
}


/**
 * funcao()
 * Descricao
 */
void MUX_WRITE_DATA() {
    /* code */
}


/**
 * funcao()
 * Descricao
 */
void MUX_ALU_1() {
    /* code */
}


/**
 * funcao()
 * Descricao
 */
void MUX_ALU_2() {
    /* code */
}

/**
 * funcao()
 * Descricao
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


/*******************************************************/

// +----------------------------------+
// | FUNÇÕES - BANCO DE REGISTRADORES |
// +----------------------------------+

/**
 * funcao()
 * Descricao
 */
char* select_reg(int id) {
    char* name = NULL;
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
}

/**
 * funcao()
 * Descricao
 */
void write_reg() {

}

/**
 * funcao()
 * Descricao
 */
void read_reg(int id) {

}

/*******************************************************/

// +-------------------+
// | FUNÇÕES - MEMÓRIA |
// +-------------------+

/**
 * funcao()
 * Descricao
 */
void write_mem() {

}


/**
 * funcao()
 * Descricao
 */
void read_mem() {

}

/*******************************************************/

// +--------+
// | CICLOS |
// +--------+
// void decode() {
//
// }
//
// void search_cycle() {
//     PC();
//     MemInst();
//     BcoReg();
//     ....
// }
//
// void execution_cycle() {
//
// }

/*******************************************************/


// +--------------------+
// | FUNÇÕES AUXILIARES |
// +--------------------+

/**
 * initialize()
 * Inicializa todos os sinais de controle,
 * memória e registradores
 */
void initialize() {
    int i, j;

    // inicializar sinais de controle
    RegDst0 = 0;
    RegDst1 = 0;
    EscReg = 0;
    UALFonteA = 0;
    UALFonteB0 = 0;
    UALFonteB1 = 0;
    UALOp0 = 0;
    UALOp1 = 0;
    FontePC0 = 0;
    FontePC1 = 0;
    PCEscCond = 0;
    PCEsc = 0;
    IouD = 0;
    LerMem = 0;
    EscMem = 0;
    BNE = 0;
    IREsc = 0;
    MemParaReg0 = 0;
    MemParaReg1 = 0;

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
        zero[i] = 0;
        at[i] = 0;
        v0[i] = 0;
        v1[i] = 0;
        a0[i] = 0;
        a1[i] = 0;
        a2[i] = 0;
        a3[i] = 0;
        t0[i] = 0;
        t1[i] = 0;
        t2[i] = 0;
        t3[i] = 0;
        t4[i] = 0;
        t5[i] = 0;
        t6[i] = 0;
        t7[i] = 0;
        s0[i] = 0;
        s1[i] = 0;
        s2[i] = 0;
        s3[i] = 0;
        s4[i] = 0;
        s5[i] = 0;
        s6[i] = 0;
        s7[i] = 0;
        t8[i] = 0;
        t9[i] = 0;
        k0[i] = 0;
        k1[i] = 0;
        gp[i] = 0;
        sp[i] = 0;
        fp[i] = 0;
        ra[i] = 0;
    }
}


/**
 * funcao()
 * Descricao
 */
void finalize() {
    int i;
    char* regid = NULL; // identificador do registrador (nome)
    // imprimir todos os registradores temporários
    for (i = 0; i < 32; i++) {
        regid = select_reg(i);
        printf("%s:\t%d\n", regid, i);
    }

    // imprimir as 32 primeiras posições de memória
    for (int i = dynamic_mem_pointer; i < 32; i++) {
        // mudar para for char a char
        printf("MEMORIA[%d] = %s\n", i - dynamic_mem_pointer, MEMORY[i]);
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
        printf("Código fonte não foi passado como argumento!\n");
        exit(1);
    }

    // abrir código fonte
    source = argv[1];
    FILE* bin = NULL;
    bin = fopen(source, "r");

    // inicializar sinais
    initialize();

    // checar integridade do código fonte
    if (bin == NULL) {
        printf("Código fonte não carregado.");
        exit(0);
    }

    // ler instruções do código fonte
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

    /* CICLOS */



    // fechar código fonte
    fclose(bin);
    bin = NULL;

    // finalizar a execução
    // exibir os registradores e memória
    finalize();

    return 0;
}
