#include <stdio.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

/************************************************************/
/****FUNÇÃO MAIN****/

int main()
{
    int codigo[MAX_TITULOS] = {0};
    int estoque[MAX_TITULOS] = {0};

    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];

    int qtdTitulos = 0;
    int qtdExemplares = 0;

    // Cadastro dos livros

    while (qtdTitulos < MAX_TITULOS) {

        int temp = 0;
        int repetido = 0;

        printf("Digite o codigo do %d° livro: \n", qtdTitulos + 1);
        scanf("%d", &temp);

        for (int i = 0; i < qtdTitulos; i++) {
            if (temp == codigo[i]) {
                repetido = 1;
            }
        }

        while (temp < 0 || repetido == 1) {

            if (temp < 0) {
                printf("Valor invalido. Digite um codigo maior ou igual a zero: \n");
            } else {
                printf("Codigo ja cadastrado. Digite outro codigo: \n");
            }

            scanf("%d", &temp);

            repetido = 0;

            for (int i = 0; i < qtdTitulos; i++) {
                if (temp == codigo[i]) {
                    repetido = 1;
                }
            }
        }

        codigo[qtdTitulos] = temp;

        printf("Digite o estoque do livro: \n");
        scanf("%d", &estoque[qtdTitulos]);

        while (estoque[qtdTitulos] < 0) {
            printf("Valor invalido. Digite um estoque maior ou igual a zero: \n");
            scanf("%d", &estoque[qtdTitulos]);
        }

        getchar();

        printf("Digite a descricao do livro: \n");

        if (qtdTitulos == 0) {
            fgets(descricao1, TAM_TEXTO, stdin);
        } else if (qtdTitulos == 1) {
            fgets(descricao2, TAM_TEXTO, stdin);
        } else {
            fgets(descricao3, TAM_TEXTO, stdin);
        }

        qtdTitulos++;

        printf("\nLivro cadastrado com sucesso!\n\n");
    }

    printf("\n--- ACERVO DA BIBLIOTECA ---\n");

    for (int i = 0; i < qtdTitulos; i++) {

        printf("\nCodigo: %d\n", codigo[i]);
        printf("Estoque: %d\n", estoque[i]);

        if (i == 0) {
            printf("Descricao: %s", descricao1);
        } else if (i == 1) {
            printf("Descricao: %s", descricao2);
        } else {
            printf("Descricao: %s", descricao3);
        }

        qtdExemplares = qtdExemplares + estoque[i];
    }

    printf("\nTotal de exemplares: %d\n", qtdExemplares);

    int codigoBusca;
    int posBusca = -1;

    // Busca de um livro

    printf("\nDigite o codigo do livro que deseja buscar: \n");
    scanf("%d", &codigoBusca);

    for (int i = 0; i < qtdTitulos; i++) {
        if (codigo[i] == codigoBusca) {
            posBusca = i;
        }
    }

    if (posBusca == -1) {

        printf("Titulo nao encontrado no acervo.\n");

    } else {

        printf("\nTitulo encontrado!\n");
        printf("Codigo: %d\n", codigo[posBusca]);
        printf("Estoque: %d\n", estoque[posBusca]);

        if (posBusca == 0) {
            printf("Descricao: %s", descricao1);
        } else if (posBusca == 1) {
            printf("Descricao: %s", descricao2);
        } else {
            printf("Descricao: %s", descricao3);
        }

        if (estoque[posBusca] == 0) {
            printf("Titulo temporariamente indisponivel.\n");
        } else {
            printf("Titulo disponivel.\n");
            printf("Quantidade em estoque: %d\n", estoque[posBusca]);
        }
    }

    return 0;
}
