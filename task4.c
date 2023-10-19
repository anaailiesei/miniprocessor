#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#define dim_int 8*sizeof(int)
#define dim_sh 16
#define dim_N_bits 3
#define dim_op_bits 2
#define dim_Dim_bits 4
#define byte 8

unsigned int get_N(unsigned int inst) {
    unsigned int N = 0;
    unsigned int x = 0;
    unsigned int mask = (unsigned int) pow(2, (dim_int - 1));
    for (int i = 0; i < dim_N_bits - 1; i++) {
        x = (int) inst / mask;
        N = 2 * (N + (x % 2));
        mask = mask / 2;
    }
    x = inst / mask;
    N = N + (x % 2);
    return N + 1;
}

char get_Nth_op(unsigned int inst, unsigned int N) {
    unsigned int x = 0, op = 0;
    unsigned int rang_mask = 1 + dim_N_bits + 2 * (N - 1);
    unsigned int mask = (unsigned int) pow(2, (int) (dim_int - rang_mask));
    x = inst / mask;
    op = 2 * (op + (x % 2));
    mask = mask / 2;

    x = inst / mask;
    op = op + (x % 2);
    if (op == 0) {
        return '+';
    } else if (op == 1) {
        return '-';
    } else if (op == 2) {
        return '*';
    } else {
        return '/';
    }
}

unsigned int get_dim(unsigned int inst, unsigned int N) {
    unsigned int dim = 0;
    unsigned int x = 0;
    unsigned int rang_mask = 1 + dim_N_bits + N * dim_op_bits;
    unsigned int mask = (unsigned int) pow(2, (int) (dim_int - rang_mask));
    for (int i = 0; i < dim_Dim_bits - 1; i++) {
        x = inst / mask;
        dim = 2 * (dim + (x % 2));
        mask = mask / 2;
    }
    x = inst / mask;
    dim = dim + (x % 2);
    return dim + 1;
}

__uint16_t *get_operanzi(unsigned int N, unsigned int Dim, char *operatii) {
    __uint16_t *operanzi = calloc(N+1, sizeof(__uint16_t));
    unsigned int nr_citiri = 0;
    nr_citiri = ((N + 1) * Dim) / dim_sh;
    if (((N + 1)*Dim) % dim_sh != 0) {
        nr_citiri++;
    }
    int contor = 0;
    unsigned int rezultat = 0;
    __int16_t instruct = 0;
    int cont_dim = 0;
    unsigned int operand = 0;
    unsigned int index = Dim;
    for (int i = 0; i < nr_citiri; i++) {
        scanf("%hu", &instruct);
        while (contor <= N) {
            unsigned int x = 0, rang = 0;
            if (index >= Dim) {
                rang = 1 + index - Dim;
            } else {
                rang = 1;
            }
            unsigned int mask = (unsigned int) pow(2, (int) (dim_sh - rang));
            while ((cont_dim < (Dim-1)) && (cont_dim + rang <= dim_sh)) {
                x = instruct / mask;
                operand = 2 * (operand + (x % 2));
                mask = mask / 2;
                cont_dim++;
            }
            if (cont_dim + rang > dim_sh) {
                break;
            }
            if (cont_dim == (Dim-1)) {
            x = instruct / mask;
            operand = operand + (x % 2);
            cont_dim = 0;
            }
            if ((contor == 0) || (cont_dim == 0)) {
                operanzi[contor] = operand;
                operand = 0;
            }
            index += Dim;
            if (cont_dim == 0) {
                contor++;
            }
        }
        index = index % dim_sh;
    }
    return operanzi;
}

__uint16_t calcul(__uint16_t a, __uint16_t b, char op) {
    __uint16_t rezultat = 0;
    if (op == '*') {
        rezultat = a * b;
    } else if (op == '/') {
        rezultat = a / b;
    } else if (op == '+') {
        rezultat = a + b;
    } else if (op == '-') {
        rezultat = a - b;
    }
    return rezultat;
}
int *prioritate_operatie(unsigned int N, char *operatii) {
    int *prioritate_op = calloc(N, sizeof(int));
    for (int index = 0; index < N; index++) {
        if (operatii[index] == '+' || operatii[index] == '-') {
            prioritate_op[index] = 0;
        } else if (operatii[index] == '*' || operatii[index] == '/') {
            prioritate_op[index] = 1;
        }
    }
    return prioritate_op;
}


int calculator(unsigned int N, __uint16_t *operanzi,
char *operatii, int *prioritate_op) {
    int rezultat = operanzi[0], rez_int = 0;
    int contor = 0, ok = 1;
    // se parcurg toti operanzii, incepand de la al doilea (index 1)
    for (int index = 1 ; index < N + 1 ; index++) {
        ok = 1;
        contor = index;
        if (prioritate_op[index - 1] == 1) {
            // cazul 1: prima operatie din sir este de prioritate 1
            while (prioritate_op[contor - 1] == 1 && contor < N) {
                if (operatii[contor - 1] == '*') {
                    rezultat = calcul(rezultat, operanzi[contor], '*');
                } else if (operatii[contor - 1] == '/') {
                    rezultat = calcul(rezultat, operanzi[contor], '/');
                }
                contor++;
            }
            if (contor == (N + 1)) return rezultat;
            index = contor - 1;
        } else if (prioritate_op[index] == 1) {
            // cazul 2: operatia de dinaintea operandului este de prioritate 0,
            // dar  operatia de dupa operand este de prioritate 1
            // se efectueaza mai intai toate op de prioritate 1 care urmeaza
            ok = 0;
            rez_int = operanzi[contor];
            while (prioritate_op[contor] == 1 && contor < N) {
                if (operatii[contor] == '*') {
                    rez_int = calcul(rez_int, operanzi[contor+1], '*');
                } else if (operatii[contor] == '/') {
                    rez_int = calcul(rez_int, operanzi[contor+1], '/');
                }
                contor++;
            }
        }
        if (prioritate_op[index-1] == 0 && ok == 1) {
            // cazul 3: op de dinainte si de dupa operand sunt de prioritate 0
            if (operatii[index-1] == '+') {
                rezultat = calcul(rezultat, operanzi[index], '+');
            } else if (operatii[index-1] == '-') {
            rezultat = calcul(rezultat, operanzi[index], '-');
            }
        } else if (prioritate_op[index-1] == 0 && ok == 0) {
            // cazul 2 se efectueaza si operatia de dinaintea operandului actual
            if (operatii[index-1] == '+') {
                rezultat = calcul(rezultat, rez_int, '+');
            } else if (operatii[index-1] == '-') {
            rezultat = calcul(rezultat, rez_int, '-');
            }
            index = contor;
        }
    }
    return rezultat;
}


int main() {
    unsigned int inst = 0;
    int i = 0;
    scanf("%u", &inst);

    unsigned int N = get_N(inst);
    unsigned int Dim = get_dim(inst, N);

    char *operatii = calloc(N, sizeof(char));
    for (i = 0; i < N; i++) {
        operatii[i] = get_Nth_op(inst, i+1);
    }
    int *prioritate_op = prioritate_operatie(N, operatii);

    __uint16_t *operanzi = get_operanzi(N, Dim, operatii);

    int rezultat = calculator(N, operanzi, operatii, prioritate_op);
    printf("%d\n", rezultat);
    free(operatii);
    free(operanzi);
    free(prioritate_op);
    return 0;
}
