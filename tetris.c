//DESAFIO TETRIS NIVEL NOVATO



#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct
{
    char nome;
    int id;
} Peca;

#define MAX 5

typedef struct
{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f)
{
    f->fim = 0;
    f->inicio = 0;
    f->total = 0;
}

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void inserir(Fila *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("Nao eh possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Peca *p)
{
    if (filaVazia(f))
    {
        printf("Nao eh possivel remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f)
{
    printf("Fila de pecas: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%c, %d]", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

Peca gerarPeca() {
    static int proximoId = 0;

    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

int main()
{
    
    Fila f;
    inicializarFila(&f);
    
    srand(time(NULL));

    for (int i = 0; i < MAX; i++){
        inserir(&f, gerarPeca());
    }

    int op;

    do
    {
        Peca removida;
        mostrarFila(&f);
        printf("1. Inserir Peca.\n");
        printf("2. Jogar Peca.\n");
        printf("0. Sair.\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            inserir(&f,gerarPeca());
            break;
        case 2:
            remover(&f, &removida);
            printf("Peca jogada: [%c, %d]\n", removida.nome, removida.id);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            break;
        }
    } while (op != 0);
}