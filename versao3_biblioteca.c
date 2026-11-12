#include <stdio.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);


/************************************************************/
/****FUNÇÃO MAIN****/

int main()
{
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};

    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];

    int qtdTitulos = 0;
    int qtdExemplares = 0;

    int codigoBusca;
    int posBusca;
    int disponivel;


    // Cadastro dos livros

    while (qtdTitulos < MAX_TITULOS) {

        qtdTitulos = cadastrarTitulo(
            codigos,
            estoques,
            descricao1,
            descricao2,
            descricao3,
            qtdTitulos
        );
    }


    // Listagem dos livros

    listarTitulos(
        codigos,
        estoques,
        descricao1,
        descricao2,
        descricao3,
        qtdTitulos
    );


    qtdExemplares = calcularQtdExemplares(
        estoques,
        qtdTitulos
    );

    printf("\nTotal de exemplares: %d\n", qtdExemplares);


    // Busca de um livro

    printf("\nDigite o codigo do livro que deseja buscar: \n");
    scanf("%d", &codigoBusca);

    posBusca = buscarTitulo(
        codigos,
        qtdTitulos,
        codigoBusca
    );


    if (posBusca == -1) {

        printf("Titulo nao encontrado.\n");

    } else {

        printf("\nTitulo encontrado!\n");
        printf("Codigo: %d\n", codigos[posBusca]);
        printf("Estoque: %d\n", estoques[posBusca]);

        if (posBusca == 0) {
            printf("Descricao: %s", descricao1);
        } else if (posBusca == 1) {
            printf("Descricao: %s", descricao2);
        } else {
            printf("Descricao: %s", descricao3);
        }

        disponivel = disponibilidadeTitulo(
            estoques[posBusca]
        );

        if (disponivel == 1) {
            printf("Titulo disponivel.\n");
            printf("Quantidade em estoque: %d\n", estoques[posBusca]);
        } else {
            printf("Titulo temporariamente indisponivel.\n");
        }
    }


    return 0;
}


/************************************************************/
/****CADASTRAR UM LIVRO****/

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
)
{
    int temp = 0;
    int repetido = 0;

    printf("Digite o codigo do %d° livro: \n", qtdTitulos + 1);
    scanf("%d", &temp);


    for (int i = 0; i < qtdTitulos; i++) {

        if (temp == codigos[i]) {
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

            if (temp == codigos[i]) {
                repetido = 1;
            }
        }
    }


    codigos[qtdTitulos] = temp;


    printf("Digite o estoque do livro: \n");
    scanf("%d", &estoques[qtdTitulos]);


    while (estoques[qtdTitulos] < 0) {

        printf("Valor invalido. Digite um estoque maior ou igual a zero: \n");
        scanf("%d", &estoques[qtdTitulos]);
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

    return qtdTitulos;
}


/************************************************************/
/****LISTAR LIVROS****/

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
)
{
    printf("\n--- ACERVO DA BIBLIOTECA ---\n");


    for (int i = 0; i < qtdTitulos; i++) {

        printf("\nCodigo: %d\n", codigos[i]);
        printf("Estoque: %d\n", estoques[i]);

        if (i == 0) {

            printf("Descricao: %s", descricao1);

        } else if (i == 1) {

            printf("Descricao: %s", descricao2);

        } else {

            printf("Descricao: %s", descricao3);
        }
    }
}


/************************************************************/
/****BUSCAR LIVRO PELO CÓDIGO****/

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
)
{
    int posBusca = -1;


    for (int i = 0; i < qtdTitulos; i++) {

        if (codigos[i] == codigoBuscado) {

            posBusca = i;
        }
    }


    return posBusca;
}


/************************************************************/
/****CALCULAR QUANTIDADE DE EXEMPLARES****/

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
)
{
    int qtdExemplares = 0;


    for (int i = 0; i < qtdTitulos; i++) {

        qtdExemplares = qtdExemplares + estoques[i];
    }


    return qtdExemplares;
}


/************************************************************/
/****DISPONIBILIDADE DO LIVRO****/

int disponibilidadeTitulo(
    int qtdEstoque
)
{
    if (qtdEstoque > 0) {

        return 1;

    } else {

        return 0;
    }
}
