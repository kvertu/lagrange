#include "poly.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} pt;


int main() {
    int n;
    printf("Quantidade de pontos: ");
    scanf(" %d", &n);
    pt tabela[n]; // Tabela de pontos

    printf("Insira os pontos da tabela (x y):\n");
    for (int i = 0; i < n; i++) {
        printf("x%d y%d: ", i, i);
        scanf(" %lf %lf", &tabela[i].x, &tabela[i].y);
    }

    poly l[n]; // l0, l1, ..., ln-1
    double a[n]; // a1, a2, ..., an-1
    // ai = yi / ((xi - x1) * (xi - x2) * ... * (xi - xi-1) * (xi - xi+1) * ... * (xi - xn-1))
    
    // Calculando l0, l1, l2, ..., ln-1
    for (int j = 0; j < n; j++) {
        double den = 1; // Denominador de l[j]
        l[j] = new_poly(0, 1); // l[j] é declarado como 1
        for (int i = 0; i < n; i++) {
            if (i != j) {
                double * lixo = l[j].data; // Já que o resultado vai ser armazenado em um novo polinomio, o ponteiro para os coeficientes antigos tem que ser armazenado para que seja liberado depois

                poly tmp = new_poly(1, 0);
                tmp.data[0] = -tabela[i].x;
                tmp.data[1] = 1;
                l[j] = prod_poly(l[j], tmp);
                free_poly(&tmp);
                den *= tabela[j].x - tabela[i].x;

                free(lixo); // Libera resquicio de memória do resultado anterior
            }
        }
        a[j] = tabela[j].y / den; // Dividir yi pelo denominador de l[j]
    }

    poly res = new_poly(n - 1, 0); // Resultado
    for (int i = 0; i < n; i++) {
        double * lixo = res.data; // Já que o resultado vai ser armazenado em um novo polinomio, o ponteiro para os coeficientes antigos tem que ser armazenado para que seja liberado depois

        res = add_poly(res, esc_poly(l[i], a[i]));
        
        free(lixo); // Libera resquicio de memória do resultado anterior
    }

    print_poly(res);

    free_poly(&res);
    for (int i = 0; i < n; i++) {
        free_poly(&l[i]); // Libera a memória dos polinômios usados no método de Lagrange
    }

    return 0;
}