
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(void) {
    float notas[10];
    float soma = 0, media;
    float maior, menor, temp;
    float valor;
    int quantidade;
    int acima = 0, abaixo = 0, iguais = 0;
    int i, j, troca;
    int posicao, digito, temDigito, temPonto;
    int linhaValida;
    long numero;
    char texto[100];

    // Ler a quantidade de notas
    while (1) { // significa repetir para sempre, até que alguma instrução interrompa o laço.
        printf("Quantas notas deseja informar (1 a 10)? ");

        if (fgets(texto, sizeof(texto), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            return 0;
        }

        // Verificar se a linha cabe no vetor de caracteres
        linhaValida = 0;

        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == '\n') {
                linhaValida = 1;
            }
        }

        if (!linhaValida && !feof(stdin)) {
            while (getchar() != '\n') {}
            printf("Entrada muito longa. Tente novamente.\n");
            continue;
        }

        // Ignorar espacos no inicio
        posicao = 0;
        while (isspace((unsigned char)texto[posicao])) {
            posicao++;
        }

        // Verificar se a entrada contem apenas digitos
        numero = 0;
        temDigito = 0;
        linhaValida = 1;

        while (texto[posicao] != '\0' &&
               texto[posicao] != '\n' &&
               !isspace((unsigned char)texto[posicao])) {

            if (texto[posicao] < '0' || texto[posicao] > '9') {
                linhaValida = 0;
                break;
            }

            digito = texto[posicao] - '0';
            numero = numero * 10 + digito;
            temDigito = 1;
            posicao++;
        }

        // Verificar se ha algo invalido depois do numero
        while (isspace((unsigned char)texto[posicao])) {
            posicao++;
        }

        if (texto[posicao] != '\0' &&
            texto[posicao] != '\n') {
            linhaValida = 0;
        }

        if (!linhaValida || !temDigito) {
            printf("Entrada invalida! Digite um numero inteiro.\n");
            continue;
        }

        if (numero < 1 || numero > 10) {
            printf("Digite uma quantidade entre 1 e 10.\n");
            continue;
        }

        quantidade = (int)numero;
        break;
    }

    // Ler e validar as notas
    for (i = 0; i < quantidade; i++) {
        while (1) {
            printf("Digite a nota %d (0 a 10): ", i + 1);

            if (fgets(texto, sizeof(texto), stdin) == NULL) {
                printf("\nEntrada encerrada.\n");
                return 0;
            }

            linhaValida = 0;

            for (j = 0; texto[j] != '\0'; j++) {
                if (texto[j] == '\n') {
                    linhaValida = 1;
                }
            }

            if (!linhaValida && !feof(stdin)) {
                while (getchar() != '\n') {}
                printf("Entrada muito longa. Tente novamente.\n");
                continue;
            }

            // Ignorar espacos no inicio
            posicao = 0;
            while (isspace((unsigned char)texto[posicao])) {
                posicao++;
            }

            // Verificar o formato numerico da nota
            temDigito = 0;
            temPonto = 0;
            linhaValida = 1;

            if (texto[posicao] == '+' || texto[posicao] == '-') {
                posicao++;
            }

            while (texto[posicao] != '\0' &&
                   texto[posicao] != '\n' &&
                   !isspace((unsigned char)texto[posicao])) {

                if (texto[posicao] >= '0' &&
                    texto[posicao] <= '9') {
                    temDigito = 1;
                } else if (texto[posicao] == '.' && !temPonto) {
                    temPonto = 1;
                } else {
                    linhaValida = 0;
                    break;
                }

                posicao++;
            }

            while (isspace((unsigned char)texto[posicao])) {
                posicao++;
            }

            if (texto[posicao] != '\0' &&
                texto[posicao] != '\n') {
                linhaValida = 0;
            }

            if (!linhaValida || !temDigito) {
                printf("Entrada invalida! Digite uma nota numerica.\n");
                continue;
            }

            valor = (float)atof(texto);

            if (!isfinite(valor)) {
                printf("Nota invalida! Digite um valor finito.\n");
                continue;
            }

            if (valor < 0 || valor > 10) {
                printf("Nota invalida! Digite uma nota entre 0 e 10.\n");
                continue;
            }

            notas[i] = valor;
            break;
        }
    }

    // Calcular a media
    for (i = 0; i < quantidade; i++) {
        soma = soma + notas[i];
    }

    media = soma / quantidade;

    // Encontrar a maior e a menor nota
    maior = notas[0];
    menor = notas[0];

    for (i = 1; i < quantidade; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
        }

        if (notas[i] < menor) {
            menor = notas[i];
        }
    }

    // Contar notas acima, abaixo e iguais a media
    for (i = 0; i < quantidade; i++) {
        if (notas[i] > media) {
            acima++;
        } else if (notas[i] < media) {
            abaixo++;
        } else {
            iguais++;
        }
    }

    // Ordenar as notas usando Bubble Sort - verifica os vizinhos
    for (i = 0; i < quantidade - 1; i++) {
        troca = 0;

        for (j = 0; j < quantidade - 1 - i; j++) {
            if (notas[j] > notas[j + 1]) {
                temp = notas[j];
                notas[j] = notas[j + 1];
                notas[j + 1] = temp;

                troca = 1;
            }
        }

        if (troca == 0) {
            break;
        }
    }

    // Exibir os resultados
    printf("\n--- RESULTADOS ---\n");
    printf("Media: %.2f\n", media);

    if (media >= 7.0) {
        printf("Aluno aprovado!\n");
    } else {
        printf("Aluno reprovado!\n");
    }

    printf("Notas acima da media: %d\n", acima);
    printf("Notas abaixo da media: %d\n", abaixo);
    printf("Notas iguais a media: %d\n", iguais);
    printf("Maior nota: %.2f\n", maior);
    printf("Menor nota: %.2f\n", menor);

    printf("Notas em ordem crescente: ");

    for (i = 0; i < quantidade; i++) {
        printf("%.2f ", notas[i]);
    }

    printf("\n");

    return 0;
}

