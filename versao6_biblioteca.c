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
/****BUSCAR USUÁRIO PELO CÓDIGO****/

int buscarUsuario(Usuario usuarios[], int qtdUsuarios, int codigoBuscado)
{
    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

/************************************************************/
/****CADASTRAR UM LIVRO****/

int cadastrarLivro(Livro livros[], int qtdLivros)
{
    Livro novoLivro;

    if (qtdLivros >= MAX_LIVROS) {
        printf("Limite de tres livros atingido.\n");
        return qtdLivros;
    }

    printf("Codigo do livro: ");
    if (scanf("%d", &novoLivro.codigo) != 1) {
        printf("Codigo invalido.\n");
        return qtdLivros;
    }

    if (novoLivro.codigo <= 0) {
        printf("O codigo deve ser maior que zero.\n");
        return qtdLivros;
    }
    if (buscarLivro(livros, qtdLivros, novoLivro.codigo) != -1) {
        printf("Esse codigo de livro ja esta cadastrado.\n");
        return qtdLivros;
    }

    printf("Estoque do livro: ");
    if (scanf("%d", &novoLivro.estoque) != 1) {
        printf("Estoque invalido.\n");
        return qtdLivros;
    }
    if (novoLivro.estoque < 0) {
        printf("O estoque nao pode ser negativo.\n");
        return qtdLivros;
    }

    getchar();
    printf("Descricao do livro: ");
    if (fgets(novoLivro.descricao, TAM_TEXTO, stdin) == NULL) {
        printf("Nao foi possivel ler a descricao.\n");
        return qtdLivros;
    }

    livros[qtdLivros] = novoLivro;
    printf("Livro cadastrado com sucesso.\n");
    return qtdLivros + 1;
}

/************************************************************/
/****FUNÇÃO PARA CADASTRAR USUÁRIO****/

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios)
{
    Usuario novoUsuario;

    if (qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite de tres usuarios atingido.\n");
        return qtdUsuarios;
    }

    printf("Codigo do usuario: ");
    if (scanf("%d", &novoUsuario.codigo) != 1) {
        printf("Codigo invalido.\n");
        return qtdUsuarios;
    }

    if (novoUsuario.codigo <= 0) {
        printf("O codigo deve ser maior que zero.\n");
        return qtdUsuarios;
    }
    if (buscarUsuario(usuarios, qtdUsuarios, novoUsuario.codigo) != -1) {
        printf("Esse codigo de usuario ja esta cadastrado.\n");
        return qtdUsuarios;
    }

    getchar();
    printf("Dados do usuario: ");
    if (fgets(novoUsuario.dados, TAM_TEXTO, stdin) == NULL) {
        printf("Nao foi possivel ler os dados do usuario.\n");
        return qtdUsuarios;
    }

    novoUsuario.codigoLivroEmprestado = -1;
    usuarios[qtdUsuarios] = novoUsuario;
    printf("Usuario cadastrado com sucesso.\n");
    return qtdUsuarios + 1;
}

/************************************************************/
/****LISTAR LIVROS****/

void listarLivros(Livro livros[], int qtdLivros)
{
    if (qtdLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("\n--- LIVROS CADASTRADOS ---\n");
    for (int i = 0; i < qtdLivros; i++) {
        printf("\nCodigo: %d\n", livros[i].codigo);
        printf("Descricao: %s", livros[i].descricao);
        printf("Estoque: %d\n", livros[i].estoque);
    }
}

/************************************************************/
/****FUNÇÃO LISTAR USUÁRIOS****/

void listarUsuarios(Usuario usuarios[], int qtdUsuarios)
{
    if (qtdUsuarios == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    printf("\n--- USUARIOS CADASTRADOS ---\n");
    for (int i = 0; i < qtdUsuarios; i++) {
        printf("\nCodigo: %d\n", usuarios[i].codigo);
        printf("Dados: %s", usuarios[i].dados);
        printf("Codigo do livro emprestado: %d\n",
               usuarios[i].codigoLivroEmprestado);
    }
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
/****EMPRESTAR LIVRO****/

int emprestarLivro(Livro *livro, Usuario *usuario)
{
    if (disponibilidadeLivro(livro->estoque) == 0) {
        return 0;
    }
    if (usuario->codigoLivroEmprestado != -1) {
        return 0;
    }

    alterarEstoque(livro, livro->estoque - 1);
    registrarEmprestimo(usuario, livro->codigo);
    return 1;
}

/************************************************************/
/****DEVOLVER LIVRO****/

int devolverLivro(Livro *livro, Usuario *usuario)
{
    if (usuario->codigoLivroEmprestado == -1) {
        return 0;
    }
    if (usuario->codigoLivroEmprestado != livro->codigo) {
        return 0;
    }

    alterarEstoque(livro, livro->estoque + 1);
    encerrarEmprestimo(usuario);
    return 1;
}

/************************************************************/
/****FUNÇÃO MAIN****/

int main()
{
    Livro livros[MAX_LIVROS]; // Struct Livros
    Usuario usuarios[MAX_USUARIOS]; // Struct Usuários
    int qtdLivros = 0;
    int qtdUsuarios = 0;
    int opcao = -1;
    int codigoLivro;
    int codigoUsuario;
    int indiceLivro;
    int indiceUsuario;
    int novoEstoque;
    int caractere;

    while (opcao != 0) {
        printf("\n--- SISTEMA DA BIBLIOTECA ---\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Cadastrar usuario\n");
        printf("3 - Listar livros\n");
        printf("4 - Buscar livro\n");
        printf("5 - Emprestar livro\n");
        printf("6 - Devolver livro\n");
        printf("7 - Listar usuarios\n");
        printf("8 - Buscar usuario\n");
        printf("9 - Alterar estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
            }
            opcao = -1;
        }

        if (opcao == 1) {
            qtdLivros = cadastrarLivro(livros, qtdLivros);

        } else if (opcao == 2) {
            qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);

        } else if (opcao == 3) {
            listarLivros(livros, qtdLivros);
            printf("Total de exemplares disponiveis: %d\n",
                   calcularQtdExemplares(livros, qtdLivros));

        } else if (opcao == 4) {
            printf("Codigo do livro: ");
            if (scanf("%d", &codigoLivro) != 1) {
                printf("Codigo invalido.\n");
            } else {
                indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
                if (indiceLivro == -1) {
                    printf("Livro nao encontrado.\n");
                } else {
                    printf("Codigo: %d\n", livros[indiceLivro].codigo);
                    printf("Descricao: %s", livros[indiceLivro].descricao);
                    printf("Estoque: %d\n", livros[indiceLivro].estoque);
                }
            }

        } else if (opcao == 5) {
            printf("Codigo do livro: ");
            if (scanf("%d", &codigoLivro) != 1) {
                printf("Codigo invalido.\n");
            } else {
                printf("Codigo do usuario: ");
                if (scanf("%d", &codigoUsuario) != 1) {
                    printf("Codigo invalido.\n");
                } else {
                    indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
                    indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);

                    if (indiceLivro == -1 || indiceUsuario == -1) {
                        printf("Livro ou usuario nao encontrado.\n");
                    } else if (emprestarLivro(&livros[indiceLivro],
                                              &usuarios[indiceUsuario]) == 1) {
                        printf("Emprestimo realizado.\n");
                    } else {
                        printf("Nao foi possivel realizar o emprestimo.\n");
                    }
                }
            }

        } else if (opcao == 6) {
            printf("Codigo do livro: ");
            if (scanf("%d", &codigoLivro) != 1) {
                printf("Codigo invalido.\n");
            } else {
                printf("Codigo do usuario: ");
                if (scanf("%d", &codigoUsuario) != 1) {
                    printf("Codigo invalido.\n");
                } else {
                    indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
                    indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);

                    if (indiceLivro == -1 || indiceUsuario == -1) {
                        printf("Livro ou usuario nao encontrado.\n");
                    } else if (devolverLivro(&livros[indiceLivro],
                                             &usuarios[indiceUsuario]) == 1) {
                        printf("Devolucao realizada.\n");
                    } else {
                        printf("Nao foi possivel realizar a devolucao.\n");
                    }
                }
            }

        } else if (opcao == 7) {
            listarUsuarios(usuarios, qtdUsuarios);

        } else if (opcao == 8) {
            printf("Codigo do usuario: ");
            if (scanf("%d", &codigoUsuario) != 1) {
                printf("Codigo invalido.\n");
            } else {
                indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
                if (indiceUsuario == -1) {
                    printf("Usuario nao encontrado.\n");
                } else {
                    printf("Codigo: %d\n", usuarios[indiceUsuario].codigo);
                    printf("Dados: %s", usuarios[indiceUsuario].dados);
                    printf("Codigo do livro emprestado: %d\n",
                           usuarios[indiceUsuario].codigoLivroEmprestado);
                }
            }

        } else if (opcao == 9) {
            printf("Codigo do livro: ");
            if (scanf("%d", &codigoLivro) != 1) {
                printf("Codigo invalido.\n");
            } else {
                indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
                if (indiceLivro == -1) {
                    printf("Livro nao encontrado.\n");
                } else {
                    printf("Novo estoque: ");
                    if (scanf("%d", &novoEstoque) != 1 || novoEstoque < 0) {
                        printf("Estoque invalido.\n");
                    } else {
                        alterarEstoque(&livros[indiceLivro], novoEstoque);
                        printf("Estoque atualizado para %d.\n",
                               livros[indiceLivro].estoque);
                    }
                }
            }

        } else if (opcao == 0) {
            printf("Programa encerrado.\n");

        } else {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
