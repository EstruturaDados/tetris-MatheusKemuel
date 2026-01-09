// DESAFIO TETRIS NIVEL MESTRE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char nome;
    int id;
} Peca;

#define MAX 5
#define MAX_PILHA 3

typedef struct
{
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct
{
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

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

Peca gerarPeca()
{
    static int proximoId = 0;

    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

/////////////////////////////////////////////////////////

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

void push(Pilha *p, Peca peca)
{
    if (pilhaCheia(p))
    {
        printf("Pilha de reserva cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

void pop(Pilha *p, Peca *peca)
{
    if (pilhaVazia(p))
    {
        printf("Pilha vazia!\n");
        return;
    }
    *peca = p->itens[p->topo];
    p->topo--;
}

void reservarPeca(Fila *f, Pilha *p)
{
    Peca reservada;

    if (filaVazia(f))
    {
        printf("Fila vazia, nao ha peca para reservar.\n");
        return;
    }

    if (pilhaCheia(p))
    {
        printf("Pilha de reserva cheia.\n");
        return;
    }

    // 1. Remove da fila
    remover(f, &reservada);

    // 2. Coloca na pilha
    push(p, reservada);

    // 3. Gera nova peça
    inserir(f, gerarPeca());

    printf("Peca [%c %d] reservada com sucesso.\n",
           reservada.nome, reservada.id);
}

void usarPecaReservada(Pilha *p)
{
    Peca usada;

    if (pilhaVazia(p))
    {
        printf("Nao ha pecas reservadas.\n");
        return;
    }

    pop(p, &usada);

    printf("Peca reservada usada: [%c %d]\n",
           usada.nome, usada.id);
}

void mostrarPilha(Pilha *p)
{
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p))
    {
        printf("vazia");
    }
    else
    {
        for (int i = p->topo; i >= 0; i--)
        {
            printf("[%c, %d]", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

void inserirNoInicio(Fila *f, Peca p)
{
    if (filaCheia(f))
    {
        printf("Fila cheia, nao eh possivel inserir no inicio.\n");
        return;
    }

    f->inicio = (f->inicio - 1 + MAX) % MAX;
    f->itens[f->inicio] = p;
    f->total++;
}


void trocarPecaAtual(Fila *f, Pilha *p)
{
    Peca daFila;
    Peca daPilha;

    if (filaVazia(f) || pilhaVazia(p))
    {
        printf("Nao eh possivel trocar.\n");
        return;
    }

    remover(f, &daFila);   // tira da frente da fila
    pop(p, &daPilha);      // tira do topo da pilha

    inserirNoInicio(f, daPilha); // topo da pilha vai pra FRENTE da fila
    push(p, daFila);             // frente da fila vai pro TOPO da pilha

    printf("Troca realizada com sucesso.\n");
}

void trocarTresPecas(Fila *f, Pilha *p)
{
    if (f->total < 3)
    {
        printf("Fila nao tem 3 pecas suficientes.\n");
        return;
    }

    if (p->topo < 2)
    {
        printf("Pilha nao tem 3 pecas suficientes.\n");
        return;
    }

    Peca filaTemp[3];
    Peca pilhaTemp[3];

    // Remove 3 da frente da fila
    for (int i = 0; i < 3; i++)
    {
        remover(f, &filaTemp[i]);
    }

    // Remove 3 do topo da pilha
    for (int i = 0; i < 3; i++)
    {
        pop(p, &pilhaTemp[i]);
    }

    // Insere as peças da pilha NO INÍCIO da fila
    // ordem invertida para manter sequência correta
    for (int i = 2; i >= 0; i--)
    {
        inserirNoInicio(f, pilhaTemp[i]);
    }

    // Empilha as peças da fila na pilha
    for (int i = 0; i < 3; i++)
    {
        push(p, filaTemp[i]);
    }

    printf("Troca tripla realizada com sucesso.\n");
}

//////////////////////////////////////////////////////////////////
int main()
{

    Fila f;
    Pilha p;
    inicializarFila(&f);
    inicializarPilha(&p);

    srand(time(NULL));

    for (int i = 0; i < MAX; i++)
    {
        inserir(&f, gerarPeca());
    }

    int op;

    do
    {
        Peca removida;

        printf("\n==========================================\n");
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("\n==========================================\n");

        printf("1. Jogar peca da frente da fila.\n");
        printf("2. Enviar peca  da fila pra reserva(pilha).\n");
        printf("3. Usar peca da reserva.\n");
        printf("4. Trocar peca da frente da fila com o topo da pilha.\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha.\n");
        printf("0. Sair.\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            remover(&f, &removida);
            inserir(&f, gerarPeca());
            break;
        case 2:
            reservarPeca(&f, &p);
            break;
        case 3:
            usarPecaReservada(&p);
            break;
        case 4:
            trocarPecaAtual(&f, &p);
            break;
        case 5:
            trocarTresPecas(&f, &p);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            break;
        }
    } while (op != 0);
}