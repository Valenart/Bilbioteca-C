#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 120

/************************************************************/
/**********************| STRUCTS |***************************/
/************************************************************/

/****LIVRO****/

typedef struct {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

/****USUÁRIO****/
                       
typedef struct {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
} Usuario;




/************************************************************/
/*********************** FUNÇÕES ****************************/
/************************************************************/

/****CADASTRAR UM LIVRO****/

int cadastrarLivro(Livro livros[], int qtdLivros)
{
    int temp;
    int Codrepetido;

    printf("\nDigite o codigo do %d livro: \n", qtdLivros + 1);
    scanf("%d", &temp);

    Codrepetido = 0;

    for (int i = 0; i < qtdLivros; i++) {
        if (temp == livros[i].codigo) {
            Codrepetido = 1;
        }
    }

    while (temp < 0 || Codrepetido == 1) {

        if (temp < 0) {
            printf("Codigo invalido. Digite um codigo maior ou igual a zero: \n");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: \n");
        }

        scanf("%d", &temp);

        Codrepetido = 0;

        for (int i = 0; i < qtdLivros; i++) {
            if (temp == livros[i].codigo) {
                Codrepetido = 1;
            }
        }
    }

    livros[qtdLivros].codigo = temp;


    printf("Digite o estoque do livro: \n");
    scanf("%d", &livros[qtdLivros].estoque);

    while (livros[qtdLivros].estoque < 0) {
        printf("Estoque invalido. Digite um valor maior ou igual a zero: \n");
        scanf("%d", &livros[qtdLivros].estoque);
    }

    getchar();

    printf("Digite a descricao do livro: \n");
    fgets(livros[qtdLivros].descricao,
          TAM_TEXTO,
          stdin);

    qtdLivros++;

    return qtdLivros;
}

/************************************************************/
/****LISTAR LIVROS****/

void listarLivros(Livro livros[], int qtdLivros)
{
    printf("\n--- ACERVO DA BIBLIOTECA ---\n");

    for (int i = 0; i < qtdLivros; i++) {
        printf("\nCodigo: %d\n", livros[i].codigo);
        printf("Descricao: %s", livros[i].descricao);
        printf("Estoque: %d\n", livros[i].estoque);
    }
}

/************************************************************/
/****BUSCAR LIVRO PELO CÓDIGO****/

int buscarLivro(Livro livros[], int qtdLivros, int codigoBuscado)
{
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].codigo == codigoBuscado) {
            return i;
        }
    }

    return -1;
}

/************************************************************/
/****CALCULAR QUANTIDADE DE EXEMPLARES****/

int calcularQtdExemplares(Livro livros[], int qtdLivros)
{
    int qtdExemplares = 0;

    for (int i = 0; i < qtdLivros; i++) {
        qtdExemplares = qtdExemplares + livros[i].estoque;
    }

    return qtdExemplares;
}



/************************************************************/
            /**DISPONIBILIDADE DO LIVRO**/

int disponibilidadeLivro(int qtdEstoque)
{
    if (qtdEstoque > 0) {
        return 1;
    } else {
        return 0;
    }
}



/************************************************************/
            /**FUNÇÃO PARA CADASTRAR USUÁRIO**/

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios)
{
    int temp;
    int repetido;

    printf("\nDigite o codigo do %d usuario: \n", qtdUsuarios + 1);
    scanf("%d", &temp);

    repetido = 0;

    for (int i = 0; i < qtdUsuarios; i++) {
        if (temp == usuarios[i].codigo) {
            repetido = 1;
        }
    }

    while (temp < 0 || repetido == 1) {

        if (temp < 0) {
            printf("Codigo invalido. Digite um codigo maior ou igual a zero: \n");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: \n");
        }

        scanf("%d", &temp);

        repetido = 0;

        for (int i = 0; i < qtdUsuarios; i++) {
            if (temp == usuarios[i].codigo) {
                repetido = 1;
            }
        }
    }

    usuarios[qtdUsuarios].codigo = temp;

    getchar();

    printf("Digite os dados do usuario: \n");
    fgets(usuarios[qtdUsuarios].dados,
          TAM_TEXTO,
          stdin);

    usuarios[qtdUsuarios].codigoLivroEmprestado = -1;

    qtdUsuarios++;

    return qtdUsuarios;
}




/************************************************************/
            /**FUNÇÃO LISTAR USUÁRIOS**/

void listarUsuarios(Usuario usuarios[], int qtdUsuarios)
{
    printf("\n--- USUARIOS CADASTRADOS ---\n");

    for (int i = 0; i < qtdUsuarios; i++) {
        printf("\nCodigo: %d\n", usuarios[i].codigo);
        printf("Dados: %s", usuarios[i].dados);
        printf("Codigo do livro emprestado: %d\n",
               usuarios[i].codigoLivroEmprestado);
    }
}





/************************************************************/
/**********************FUNÇÃO MAIN***************************/
/************************************************************/

int main()
{
    Livro livros[MAX_LIVROS]; // Struct Livros
    Usuario usuarios[MAX_USUARIOS]; // Struct Usuários

    int qtdLivros = 0;
    int qtdUsuarios = 0;
    int qtdExemplares = 0;

    int codigoBusca;
    int posBusca;
    int disponivel;


    // Cadastro dos livros

    while (qtdLivros < MAX_LIVROS) {
        qtdLivros = cadastrarLivro(livros, qtdLivros);
    }


    // Listagem dos livros

    listarLivros(livros, qtdLivros);


    // Calculo do estoque total

    qtdExemplares = calcularQtdExemplares(livros, qtdLivros);

    printf("\nTotal de exemplares: %d\n", qtdExemplares);


    // Busca de um livro

    printf("\nDigite o codigo do livro que deseja buscar: \n");
    scanf("%d", &codigoBusca);

    posBusca = buscarLivro(livros, qtdLivros, codigoBusca);


    if (posBusca == -1) {

        printf("Livro nao encontrado.\n");

    } else {

        printf("\nLivro encontrado!\n");
        printf("Codigo: %d\n", livros[posBusca].codigo);
        printf("Descricao: %s", livros[posBusca].descricao);
        printf("Estoque: %d\n", livros[posBusca].estoque);

        disponivel = disponibilidadeLivro(
            livros[posBusca].estoque
        );

        if (disponivel == 1) {
            printf("Livro disponivel.\n");
            printf("Quantidade em estoque: %d\n",
                   livros[posBusca].estoque);
        } else {
            printf("Livro temporariamente indisponivel.\n");
        }
    }


    // Cadastro dos usuarios

    while (qtdUsuarios < MAX_USUARIOS) {
        qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);
    }


    // Listagem dos usuarios

    listarUsuarios(usuarios, qtdUsuarios);


    return 0;
}
