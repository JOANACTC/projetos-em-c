#include <stdio.h>

#define TAXA_EURO_DOLAR 1.10
#define TAXA_DOLAR_EURO 0.91

int main() {
    double valor, resultado;
    int escolha;

    printf("Conversor de Moedas\n");
    printf("1. Euro para Dólar\n");
    printf("2. Dólar para Euro\n");
    printf("Escolha a conversão: ");
    scanf("%d", &escolha);

    printf("Digite o valor: ");
    scanf("%lf", &valor);

    switch (escolha) {
        case 1:
            resultado = valor * TAXA_EURO_DOLAR;
            printf("%.2lf Euros = %.2lf Dólares\n", valor, resultado);
            break;
        case 2:
            resultado = valor * TAXA_DOLAR_EURO;
            printf("%.2lf Dólares = %.2lf Euros\n", valor, resultado);
            break;
        default:
            printf("Opção inválida!\n");
    }

    return 0;
}

