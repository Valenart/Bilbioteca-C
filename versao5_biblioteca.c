#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 120

/************************************************************/
/****STRUCTS****/

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
/****CADASTRAR UM LIVRO****/

int cadastrarLivro(Livro livros[], int qtdLivros)
{
    int codigo;
    int estoque;
    int repetido = 0;

    printf("\nDigite o codigo do %d livro: ", qtdLivros + 1);
    scanf("%d", &codigo);

    for (int i = 0; i < qtdLivros; i++) {
        if (codigo == livros[i].codigo) {
            repetido = 1;
        }
    }

    while (codigo <= 0 || repetido == 1) {
        if (codigo <= 0) {
            printf("Codigo invalido. Digite um codigo maior que zero: ");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: ");
        }
        scanf("%d", &codigo);
        repetido = 0;

        for (int i = 0; i < qtdLivros; i++) {
            if (codigo == livros[i].codigo) {
                repetido = 1;
            }
        }
    }

    printf("Digite o estoque do livro: ");
    scanf("%d", &estoque);

    while (estoque < 0) {
        printf("Estoque invalido. Digite um valor maior ou igual a zero: ");
        scanf("%d", &estoque);
    }

    getchar();
    printf("Digite a descricao do livro: ");
    fgets(livros[qtdLivros].descricao, TAM_TEXTO, stdin);

    livros[qtdLivros].codigo = codigo;
    livros[qtdLivros].estoque = estoque;
    printf("Livro cadastrado com sucesso.\n");

    return qtdLivros + 1;
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
    int total = 0;

    for (int i = 0; i < qtdLivros; i++) {
        total = total + livros[i].estoque;
    }
    return total;
}

/************************************************************/
/****DISPONIBILIDADE DO LIVRO****/

int disponibilidadeLivro(int estoque)
{
    if (estoque > 0) {
        return 1;
    }
    return 0;
}

/************************************************************/
/****FUNÇÃO PARA CADASTRAR USUÁRIO****/

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios)
{
    int codigo;
    int repetido = 0;

    printf("\nDigite o codigo do %d usuario: ", qtdUsuarios + 1);
    scanf("%d", &codigo);

    for (int i = 0; i < qtdUsuarios; i++) {
        if (codigo == usuarios[i].codigo) {
            repetido = 1;
        }
    }

    while (codigo <= 0 || repetido == 1) {
        if (codigo <= 0) {
            printf("Codigo invalido. Digite um codigo maior que zero: ");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: ");
        }
        scanf("%d", &codigo);
        repetido = 0;

        for (int i = 0; i < qtdUsuarios; i++) {
            if (codigo == usuarios[i].codigo) {
                repetido = 1;
            }
        }
    }

    getchar();
    printf("Digite os dados do usuario: ");
    fgets(usuarios[qtdUsuarios].dados, TAM_TEXTO, stdin);

    usuarios[qtdUsuarios].codigo = codigo;
    usuarios[qtdUsuarios].codigoLivroEmprestado = -1;
    printf("Usuario cadastrado com sucesso.\n");

    return qtdUsuarios + 1;
}

/************************************************************/
/****FUNÇÃO LISTAR USUÁRIOS****/

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
/****ALTERAR ESTOQUE****/

void alterarEstoque(Livro *livro, int valor)
{
    livro->estoque = valor;
}

/************************************************************/
/****REGISTRAR EMPRÉSTIMO****/

void registrarEmprestimo(Usuario *usuario, int codigoLivro)
{
    usuario->codigoLivroEmprestado = codigoLivro;
}

/************************************************************/
/****ENCERRAR EMPRÉSTIMO****/

void encerrarEmprestimo(Usuario *usuario)
{
    usuario->codigoLivroEmprestado = -1;
}

/************************************************************/
/****FUNÇÃO MAIN****/

int main()
{
    Livro livros[MAX_LIVROS]; // Struct Livros
    Usuario usuarios[MAX_USUARIOS]; // Struct Usuários
    int qtdLivros = 0;
    int qtdUsuarios = 0;
    int codigoBusca;
    int posBusca;
    int estoqueInicial;

    // Cadastro dos livros

    while (qtdLivros < MAX_LIVROS) {
        qtdLivros = cadastrarLivro(livros, qtdLivros);
    }

    // Listagem dos livros

    listarLivros(livros, qtdLivros);
    printf("\nTotal de exemplares: %d\n",
           calcularQtdExemplares(livros, qtdLivros));

    // Busca de um livro

    printf("\nDigite o codigo do livro que deseja buscar: ");
    scanf("%d", &codigoBusca);
    posBusca = buscarLivro(livros, qtdLivros, codigoBusca);

    if (posBusca == -1) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("Livro encontrado.\n");
        printf("Codigo: %d\n", livros[posBusca].codigo);
        printf("Descricao: %s", livros[posBusca].descricao);
        printf("Estoque: %d\n", livros[posBusca].estoque);

        if (disponibilidadeLivro(livros[posBusca].estoque) == 1) {
            printf("Livro disponivel.\n");
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

    // Teste das alteracoes feitas por endereco.
    printf("\n--- TESTE DE PONTEIROS ---\n");
    estoqueInicial = livros[0].estoque;
    printf("Estoque inicial do livro %d: %d\n",
           livros[0].codigo, livros[0].estoque);

    if (estoqueInicial > 0) {
        alterarEstoque(&livros[0], livros[0].estoque - 1);
        printf("Estoque depois da primeira alteracao: %d\n", livros[0].estoque);
    } else {
        printf("O livro esta sem estoque para diminuir.\n");
    }

    registrarEmprestimo(&usuarios[0], livros[0].codigo);
    printf("Livro registrado no usuario %d: %d\n",
           usuarios[0].codigo, usuarios[0].codigoLivroEmprestado);

    encerrarEmprestimo(&usuarios[0]);
    printf("Livro registrado apos devolucao: %d\n",
           usuarios[0].codigoLivroEmprestado);

    if (estoqueInicial > 0) {
        alterarEstoque(&livros[0], livros[0].estoque + 1);
        printf("Estoque depois da segunda alteracao: %d\n", livros[0].estoque);
    }

    return 0;
}
