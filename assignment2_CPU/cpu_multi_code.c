/* SSC-0112 - Organizacao de Computadores Digitais */
/* Turma A - 2018/01                               */
/* Prof. Paulo Sergio Lopes de Souza               */
/*                                                 */
/* Trabalho 2                                      */
/* CPU MIPS Multiciclo de 32 bits                  */
/*                                                 */
/* Aluno                          NUSP             */
/* Felipe Scrochio Custodio       9442688          */
/* Gabriel Henrique Scalici       9292970          */
/* Juliano Fantozzi               9791218          */
/* Andre Luis Storino Junior      9293668          */

#include <stdlib.h>
#include <pthread.h>

/* MEMÓRIA */
#define MAX_SIZE 100
char MEMORY[MAX_SIZE];

/* SINAIS DE CONTROLE */
// .......................................
// : Sinais de Controle : Função         :
// :....................:................:
// : RegDst0            :           00   :
// : RegDst1            :           01   :
// : EscReg             :           02   :
// : UALFonteA          :           03   :
// : UALFonteB0         :           04   :
// : UALFonteB1         :           05   :
// : UALOp0             :           06   :
// : UALOp1             :           07   :
// : FontePC0           :           08   :
// : FontePC1           :           09   :
// : PCEscCond          :           10   :
// : PCEsc              : Escrever no PC :
// : IouD               :           12   :
// : LerMem             :           13   :
// : EscMem             :           14   :
// : BNE                :           15   :
// : IREsc              :           16   :
// : MemParaReg0        :           17   :
// : MemParaReg1        :           18   :
// :....................:................:

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


void PC() {
    /* code */
}


int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
