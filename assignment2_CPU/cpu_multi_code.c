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

#include <stdlib.h>
#include <pthread.h>

/*******************************************************/

// +---------+
// | MEMÓRIA |
// +---------+
#define MAX_SIZE 100
char MEMORY[MAX_SIZE];

/*******************************************************/

// +------------------------+
// | BANCO DE REGISTRADORES |
// +------------------------+
typedef char register[32];
register zero;  // 0
register at;    // 1
register v0;    // 2
register v1;    // 3
register a0;    // 4
register a1;    // 5
register a2;    // 6
register a3;    // 7
register t0;    // 8
register t1;    // 9
register t2;    // 10
register t3;    // 11
register t4;    // 12
register t5;    // 13
register t6;    // 14
register t7;    // 15
register s0;    // 16
register s1;    // 17
register s2;    // 18
register s3;    // 19
register s4;    // 20
register s5;    // 21
register s6;    // 22
register s7;    // 23
register t8;    // 24
register t9;    // 25
register k0;    // 26
register k1;    // 27
register gp;    // 28
register sp;    // 29
register fp;    // 30
register ra;    // 31

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

// +--------------------+
// | FUNÇÕES AUXILIARES |
// +--------------------+

/**
 * bin2dec(int binary)
 * Converte 'binary', número em binário,
 * para decimal e retorna.
 */
void bin2dec(int binary) {
    int dec;
    while (binary > 0) {
        rem = binary % 10;
        dec = dec + rem * base;
        binary = binary / 10 ;
        base = base * 2;
    }
    return dec;
}

/**
 * initialize()
 * Inicializa todos os sinais de controle,
 * memória e registradores
 */
void initialize() {
    int i;

    // inicializar sinais de controle
    RegDst0 = 0
    RegDst1 = 0
    EscReg = 0
    UALFonteA = 0
    UALFonteB0 = 0
    UALFonteB1 = 0
    UALOp0 = 0
    UALOp1 = 0
    FontePC0 = 0
    FontePC1 = 0
    PCEscCond = 0
    PCEsc = 0
    IouD = 0
    LerMem = 0
    EscMem = 0
    BNE = 0
    IREsc = 0
    MemParaReg0 = 0
    MemParaReg1 = 0

    // inicializar memória
    for (i = 0; i < MAX_SIZE; i++) {
        MEMORY[i] = 0;
    }

    // inicializar banco de registradores
    for (i = 0; i < 32; i++) {
        zero[i] = 0
        at[i] = 0
        v0[i] = 0
        v1[i] = 0
        a0[i] = 0
        a1[i] = 0
        a2[i] = 0
        a3[i] = 0
        t0[i] = 0
        t1[i] = 0
        t2[i] = 0
        t3[i] = 0
        t4[i] = 0
        t5[i] = 0
        t6[i] = 0
        t7[i] = 0
        s0[i] = 0
        s1[i] = 0
        s2[i] = 0
        s3[i] = 0
        s4[i] = 0
        s5[i] = 0
        s6[i] = 0
        s7[i] = 0
        t8[i] = 0
        t9[i] = 0
        k0[i] = 0
        k1[i] = 0
        gp[i] = 0
        sp[i] = 0
        fp[i] = 0
        ra[i] = 0
    }
}

/**
 * decode()
 * Processo de decodificação de uma instrução
 */
void decode() {

}

/*******************************************************/

// +---------------------+
// | UNIDADES FUNCIONAIS |
// +---------------------+
void PC() {
    /* code */
}

/*******************************************************/


// +----------------------------------+
// | FUNÇÕES - BANCO DE REGISTRADORES |
// +----------------------------------+
void select_reg(int id) {
    switch (id) {
        case 0:
            // reg
            break;
        case 1:
            // reg
            break;
        case 2:
            // reg'
            break;
        case 3:
            // reg'
            break;
        case 4:
            // reg'
            break;
        case 5:
            // reg'
            break;
        case 6:
            // reg'
            break;
        case 7:
            // reg'
            break;
        case 8:
            // reg'
            break;
        case 9:
            // reg'
            break;
        case 10:
            // reg'
            break;
        case 11:
            // reg'
            break;
        case 12:
            // reg'
            break;
        case 13:
            // reg'
            break;
        case 14:
            // reg'
            break;
        case 15:
            // reg'
            break;
        case 16:
            // reg'
            break;
        case 17:
            // reg'
            break;
        case 18:
            // reg'
            break;
        case 19:
            // reg'
            break;
        case 20:
            // reg'
            break;
        case 21:
            // reg'
            break;
        case 22:
            // reg'
            break;
        case 23:
            // reg'
            break;
        case 24:
            // reg'
            break;
        case 25:
            // reg'
            break;
        case 26:
            // reg'
            break;
        case 27:
            // reg'
            break;
        case 28:
            // reg'
            break;
        case 29:
            // reg'
            break;
        case 30:
            // reg'
            break;
        case 31:
            // reg'
            break;
    }
}


void write_reg() {

}

void read_reg() {

}

/*******************************************************/

// +-------------------+
// | FUNÇÕES - MEMÓRIA |
// +-------------------+
void write_mem() {

}

void read_mem() {

}

/*******************************************************/

// +-----------+
// | SIMULAÇÃO |
// +-----------+
int main(int argc, char const *argv[]) {

    char instruction[32];

    // inicializar sinais
    initialize();

    // ler código fonte
    FILE *bin = NULL;
    bin = fopen(argv[1], "r");

    // ler instrução por instrução

    // – Enviar o PC para a memória e buscar a instrução.
    // – Ler um ou dois registradores (usando o campo da instrução para selecionar os registradores a serem lidos)

    fclose(bin);
    bin = NULL;

    return 0;
}
