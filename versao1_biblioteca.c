#include <stdio.h>
#define MAX_TITULOS 3

/************************************************************/
/****FUNÇÃO MAIN****/

int main()
{
    int codigo[MAX_TITULOS] = {0};
    int estoque[MAX_TITULOS] = {0};

    int qtdTitulos = 0;
    int qtdExemplares = 0;

    // Cadastro dos livros

    while (qtdTitulos < MAX_TITULOS) {
        int temp = 0;
        int repetido = 0;

        printf("Digite o codigo do %d° livro: \n", qtdTitulos + 1);
        scanf("%d", &temp);

        // Verifica se o codigo ja foi cadastrado
        for (int i = 0; i < qtdTitulos; i++) {
            if (temp == codigo[i]) {
                repetido = 1;
            }
        }

   
        while (temp < 0 || repetido == 1) {

            if (temp < 0) {
                printf("Codigo invalido! Digite um valor maior ou igual a zero: \n");
            } else {
                printf("Codigo ja cadastrado! Digite outro codigo: \n");
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
            printf("Estoque invalido! Digite um valor maior ou igual a zero: \n");
            scanf("%d", &estoque[qtdTitulos]);
        }

        printf("Livro cadastrado com sucesso!\n\n");

        qtdTitulos++;
    }

    printf("\n------- LIVROS E ESTOQUE -------\n");

    for (int i = 0; i < qtdTitulos; i++) {
        printf("O codigo do %d° livro e %d e o seu estoque e %d\n",
               i + 1, codigo[i], estoque[i]);

        qtdExemplares = qtdExemplares + estoque[i];
    }

    printf("\n");
    printf("O valor total dos estoques de livros e: %d\n", qtdExemplares);

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

    // Verifica se encontrou o livro
    if (posBusca == -1) {
        printf("\n Livro nao encontrado no acervo.\n");
    } else {
        printf("Livro encontrado!\n");

        if (estoque[posBusca] == 0) {
            printf("O livro esta temporariamente indisponivel.\n");
        } else {
            printf("O livro esta disponivel.\n");
            printf("Quantidade em estoque: %d\n", estoque[posBusca]);
        }
    
        printf("Fim.");
    }

    return 0;
}
