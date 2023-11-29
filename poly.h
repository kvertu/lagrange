#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int grau;
    double * data;
} poly;

// Funções básicas para manipulação do polinômio
poly new_poly(int g, double def); // Cria um polinômio
bool is_poly_null(poly p); // Verifica se o polinômio é nulo
void free_poly(poly * p); // Libera o espaço alocado para o polinômio

/*
    Existe a possibilidade do coeficiente do polinômio de maior grau ser 0 após uma operação de soma ou subtração
    Exemplo:
        P = x^2 + 2 * x + 1
        Q = x^2 + x + 2
        P - Q = 0 * x^2 + x - 1
    O problema é que o coeficiente de maior grau é nulo, ocupando memória sem necessidade. Além disso, se esse polinômio for utilizado em uma multiplicação, o problema pode-se agravar ainda mais
    
    Por isso, foi criado a função normalize_poly, que verifica e remove esses coeficientes desnecessários caso existam
*/
void normalize_poly(poly * p); // Normaliza o polinômio

// Leitura e escrita em polinômios
void read_poly(poly p); // Lê o polinômio a partir da entrada do usuário no terminal (Não é utilizado na main.c, criado apenas para teste)
poly readfile_poly(char * filename); // Lê o polinômio a partir de um arquivo
void print_poly(poly p); // Imprime o polinômio no terminal
void printfile_poly(char * filename, poly p); // Imprime o polinômio em um arquivo (Não é utilizado na main.c, criado apenas para deixar a biblioteca poly.h mais completa)
/*
    Estrutura do arquivo:
        1ª Linha: Coeficiente do termo independente
        2ª Linha: Coeficiente de x
        3ª Linha: Coeficiente de x^2
        4ª Linha: Coeficiente de x^3
        ...
        Última Linha: Coeficiente do termo de maior grau
*/

// Soma, subtração, produto e cálculo de polinômios
poly add_poly(poly p, poly q); // p + q
poly subtr_poly(poly p, poly q); // p - q
poly prod_poly(poly p, poly q); // p * q
poly esc_poly(poly p, double a); // a * p
double calc_poly(poly p, double x); // Calcula p(x)

// Derivação e Integração
poly derivate_poly(poly p); // Derivada
poly integrate_poly_undef(poly p, double k); // Integral indefinida
double integrate_poly_def(poly p, double min, double max); // Integral definida

double newton_poly(poly p, double start, int tmax, double epsilon); // Método de Newton-Raphson