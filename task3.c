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
    unsigned int nr_citiri = 0;
    nr_citiri = ((N + 1) * Dim) / dim_sh;
    if (((N + 1)*Dim) % dim_sh != 0) {
        nr_citiri++;
    }
    int contor = 0;
    unsigned int rezultat = 0;
    __uint16_t instruct = 0;
    int cont_dim = 0;
    __uint16_t operand = 0;
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
            if (contor == 0) {
                rezultat = operand;
                operand = 0;
            } else {
                if (cont_dim == 0) {
                    if (operatii[contor-1] == '+') {
                        rezultat += operand;
                    } else if (operatii[contor-1] == '-') {
                        rezultat -= operand;
                    } else if (operatii[contor-1] == '*') {
                        rezultat *= operand;
                    } else {
                        rezultat /= operand;
                    }
                    operand = 0;
                }
            }

            index += Dim;
            if (cont_dim == 0) {
                contor++;
            }
        }
        index = index % dim_sh;
    }
    printf("%d\n", rezultat);
    free(operatii);
    return 0;
}
