#include <stdio.h>
#include <math.h>
#define dim_int 8*sizeof(int)
#define dim_N_bits 3
#define dim_op_bits 2
#define dim_Dim_bits 4

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
    printf("%d ", N);
    for (i = 1; i <= N; i++) {
        printf("%c ", get_Nth_op(inst, i));
    }
    printf("%d\n", get_dim(inst, N));

    return 0;
}
