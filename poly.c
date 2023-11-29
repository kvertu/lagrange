/*
    Uma descrição do que cada função faz está disponível em poly.h
*/
#include "poly.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

poly new_poly(int g, double def) {
    /*
        g é o grau do polinômio
        def é o valor padrão dos coeficientes do polinômio
    */
    poly p;

    if (g >= 0) {
        p.grau = g;

        // Alocação de memória
        // É alocado um vetor de g + 1, levando em consideração o termo independente
        p.data = malloc((g + 1) * sizeof(double));
        if (p.data != NULL) {
            // Inicialização das entradas com o valor padrão
            for (int i = 0; i < (g + 1); i++) {
                p.data[i] = def;
            }
        } else {
            // Deu ruim para alocar a memória
            printf("ERRO: Memória insuficiente para alocação.\n");
        }
    } else {
        // Retorna polinômio nulo
        p.grau = -1;
        p.data = NULL;
        printf("ERRO: Grau de polinômio inválido, retornando polinômio nulo.\n");
    }

    return p;
}

bool is_poly_null(poly p) {
    /*
        Verifica se o polinômio p é nulo
    */
    if (p.data == NULL || p.grau < 0) return true;
    return false;
}

void free_poly(poly * p) {
    /*
        Libera o espaço de memória do polinômio p
    */
    if (p->data != NULL) {
        free(p->data);
        p->data = NULL;
    }
}

void normalize_poly(poly * p) {
    /*
        Normaliza o polinômio
    */
    if (!is_poly_null((*p))) {
        // O polinômio só será normalizado quando o polinômio ter grau maior que 0 e o coeficiente do maior grau for 0
        // Esse procedimento vai se repetir até não houver nenhum coeficiente 0 no último grau do polinômio ou quando só sobrar o termo independente
        while (p->grau > 0 && p->data[p->grau] == 0) {
            // É criado um polinômio temporário com grau menor que o polinômio p
            poly temp = new_poly(p->grau - 1, 0);
            
            for (int i = 0; i <= temp.grau; i++) {
                // Os coeficientes de p são transferidos para temp (com exceção do ultimo coeficiente de p)
                temp.data[i] = p->data[i];
            }

            // A memória alocada para p é liberada e substituida pelos dados de temp
            free_poly(p);
            (*p) = temp;
        }
    } else {
        // Polinômio é nulo
        printf("ERRO: Não é possível normalizar um vetor nulo.\n");
    }
}

void read_poly(poly p) {
    /*
        Preenche o polinômio p com entradas do usuário no terminal
        Pre-condição: grau precisa ser definido antes.
    */
    if (!is_poly_null(p)) {
        for (int i = 0; i < (p.grau + 1); i++) {
            printf("Insira o coeficiente de x^%d: ", i);
            scanf(" %lf", &p.data[i]);
        }
    } else {
        printf("ERRO: Não é possível inserir valores em um polinomio nulo.\n");
    }

    normalize_poly(&p);
}

poly readfile_poly(char * filename) {
    /*
        Lê os coeficientes do polinômio p do arquivo filename
    */
    poly p;

    FILE * fpoly = fopen(filename, "r"); 
    if (fpoly == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo, retornando polinômio nulo.\n");
        p.grau = 0;
        p.data = NULL;
        return p;
    }
    
    // Faz uma passagem pelo arquivo para determinar o seu tamanho
    int tam = 0;
    double tmp;
    while (!feof(fpoly)) {
        // Ele precisa pular a linha de alguma forma para assim chegar no EOF
        fscanf(fpoly, "%lf", &tmp);
        tam++;
    }
    rewind(fpoly); // Função para voltar ao inicio do arquivo

    // O grau do polinomio é o tamanho do arquivo menos a linha do termo independente
    p = new_poly(tam - 1, 0);

    for (int i = 0; i <= p.grau; i++) {
        if (feof(fpoly)) {
            // Se o arquivo acabar prematuramente, então tem coeficiente faltando;
            printf("ERRO: Arquivo de entrada parece estar faltando dados, retornando polinômio nulo.\n");
            p.grau = -1;
            p.data = NULL;
            return p;
        }
        fscanf(fpoly, "%lf", &p.data[i]);
    }

    fclose(fpoly);

    normalize_poly(&p);

    return p;
}

void print_poly(poly p) {
    /*
        Imprime os coeficientes do polinômio p na tela
    */
    if (!is_poly_null(p)) {
        printf("Grau do polinômio: %d\n", p.grau);
        for (int i = p.grau; i >= 0; i--) {
            printf("x^%d: %lf\n", i, p.data[i]);
        }
        printf("\n");
    } else {
        printf("ERRO: Não é possível imprimir os valores de um polinomio nulo.\n");
    }
}

void printfile_poly(char * filename, poly p) {
    /*
        Imprime os coeficientes do polinômio p no arquivo filename
    */
    if (is_poly_null(p)) {
        printf("ERRO: Não é possível escrever um polinômio nulo no arquivo.\n");
        return;
    }

    FILE * fpoly = fopen(filename, "w");

    if (fpoly == NULL) {
        printf("ERRO: Não foi possível acessar o arquivo.\n");
        return;
    } else {
        for (int i = 0; i <= p.grau; i++) {
            fprintf(fpoly, "%lf\n", p.data[i]);
        }

        fclose(fpoly);
    }
}

double calc_poly(poly p, double x) {
    /*
        Calcula p(x)
    */
    double soma = 0;
    if (!is_poly_null(p)) {
        for (int i = 0; i < (p.grau + 1); i++) {
            soma += p.data[i] * pow(x, i);
        }
    } else {
        printf("AVISO: Polinomio é nulo, retornando 0.\n");
    }
    return soma;
}

poly add_poly(poly p, poly q) {
    /*
        Calcula a soma dos polinômios p e q
    */
    poly r;

    if (!is_poly_null(p) && !is_poly_null(q)) {
        if (p.grau > q.grau) {
            r = new_poly(p.grau, 0);
        
            for (int i = 0; i <= q.grau; i++) {
                r.data[i] = p.data[i] + q.data[i];
            }
            for (int j = q.grau + 1; j <= p.grau; j++) {
                r.data[j] = p.data[j];
            }
        } else {
            r = new_poly(q.grau, 0);

            for (int i = 0; i <= p.grau; i++) {
                r.data[i] = p.data[i] + q.data[i];
            }
            for (int j = p.grau + 1; j <= q.grau; j++) {
                r.data[j] = q.data[j];
            }
        }
    } else {
        printf("ERRO: Não é possível calcular a soma de polinômios nulos.\n");
        r.grau = -1;
        r.data = NULL;
    }

    normalize_poly(&r);

    return r;
}

poly subtr_poly(poly p, poly q) {
    /*
        Calcula a diferença dos polinômios p e q
    */
    poly r;

    if (!is_poly_null(p) && !is_poly_null(q)) {
        if (p.grau > q.grau) {
            r = new_poly(p.grau, 0);
        
            for (int i = 0; i <= q.grau; i++) {
                r.data[i] = p.data[i] - q.data[i];
            }
            for (int j = q.grau + 1; j <= p.grau; j++) {
                r.data[j] =  p.data[j];
            }
        } else {
            r = new_poly(q.grau, 0);

            for (int i = 0; i <= p.grau; i++) {
                r.data[i] = p.data[i] - q.data[i];
            }
            for (int j = p.grau + 1; j <= q.grau; j++) {
                r.data[j] = -q.data[j];
            }
        }
    } else {
        printf("ERRO: Não é possível calcular a subtração de polinômios nulos.\n");
        r.grau = -1;
        r.data = NULL;
    }

    normalize_poly(&r);

    return r;
}

poly prod_poly(poly p, poly q) {
    /*
        Calcula o produto dos polinômios p e q
    */
    poly r;

    if (!is_poly_null(p) && !is_poly_null(q)) {
        r = new_poly(p.grau + q.grau, 0);

        if (p.grau > q.grau) {
            for (int i = 0; i <= q.grau; i++) {
                for (int j = 0; j <= p.grau; j++) {
                    r.data[i + j] += q.data[i] * p.data[j]; 
                }
            }
        } else {
            for (int i = 0; i <= p.grau; i++) {
                for (int j = 0; j <= q.grau; j++) {
                    r.data[i + j] += p.data[i] * q.data[j]; 
                }
            }
        }
    } else {
        printf("AVISO: Não é possível calcular o produto de um polinômio nulo.\n");
        r.grau = -1;
        r.data = NULL;
    }

    return r;
}

poly esc_poly(poly p, double a) {
    /*
        Calcula o produto escalar de a * p(x)
    */
    poly r;

    if (!is_poly_null(p)) {
        r = new_poly(p.grau, 0);

        for (int i = 0; i <= p.grau; i++) {
            r.data[i] = p.data[i] * a;
        }
    } else {
        printf("AVISO: Não é possível calcular o produto escalar de um polinômio nulo.\n");
        r.grau = -1;
        r.data = NULL;
    }

    return r;
}

poly derivate_poly(poly p) {
    /*
        Calcula a derivada do polinômio p
    */
    poly q;

    if (!is_poly_null(p)) {
        q = new_poly(p.grau - 1, 0);

        for (int i = 1; i <= p.grau; i++) {
            q.data[i - 1] = p.data[i] * i;
        }
    } else {
        printf("ERRO: Não é possível derivar um polinômio nulo.\n");
        q.grau = -1;
        q.data = NULL;
    }
    
    return q;
}

poly integrate_poly_undef(poly p, double k) {
    /*
        Calcula a integral indefinida do polinômio p
        k é o termo independente de p
    */
    poly q;

    if (!is_poly_null(p)) {
        q = new_poly(p.grau + 1, 0);

        for (int i = 0; i <= p.grau; i++) {
            q.data[i + 1] = p.data[i] / (i + 1);
        }
        q.data[0] = k;
    } else {
        printf("ERRO: Não é possível integrar um polinômio nulo.\n");
        q.grau = -1;
        q.data = NULL;
    }

    return q;
}

double integrate_poly_def(poly p, double min, double max) {
    /*
        Calcula a integral definida de p
        min e max é o intervalo da integral definida
    */
    poly q;
    double res;

    if (!is_poly_null(p)) {
        q = integrate_poly_undef(p, 0);
        res = calc_poly(q, max) - calc_poly(q, min);
    } else {
        printf("ERRO: Não é possível calcular a integral definida de um polinômio nulo, retornando 0.\n");
        res = 0;
    }

    return res;
}

double newton_poly(poly p, double start, int tmax, double epsilon) {
    /*
        Calcula o método de Newton-Raphson no polinômio para achar uma raiz das raizes do polinômio
        Essa função não considera casos de polinômios sem raizes reais
    */
    double res = 0, aux, num, den;

    if (epsilon <= 0) {
        printf("ERRO: Não é possível aplicar o método Newton-Raphson com um valor negativo ou nulo para epsilon.\n");
        return 0;
    }

    if (is_poly_null(p)) {
        printf("ERRO: Não é possível aplicar o método Newton-Raphson com um polinômio nulo.\n");
        return 0;
    }

    poly q = derivate_poly(p);

    res = start;
    for (int i = 0; i < tmax; i++) {
        aux = res;

        num = calc_poly(p, aux);
        den = calc_poly(q, aux);

        if (den == 0) {
            printf("AVISO: Calculo do denominador em %lf retornou zero na iteração %d de %d, interrompendo função.\n", aux, i + 1, tmax);
            return res;
        }
        res = aux - (num / den);

        if (fabs(res - aux) < epsilon) {
            break;
        }
    }

    return res;
}