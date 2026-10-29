#include <stdio.h>
#include <stdlib.h>
#include "hanoi.h"

/* Complete somente as funcoes abaixo. Nao use vetor para representar as torres. */

int push(No **topo, int disco)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        return 0;
    }
    novo->disco = disco;
    novo->proximo = *topo;
    *topo = novo;
    return 1;
}
int pop(No **topo)
{
    /* TODO 2: remover do inicio, usar free(), retornar disco ou -1. */
    if (topo == NULL || *topo == NULL)
    {
        return -1;
    }

    No *aux = *topo;
    int disco = aux->disco;
    *topo = aux->proximo;
    free(aux);
    return disco;
}
int peek(No *topo)
{
    /* TODO 3: consultar topo sem remover. */
    if (topo == NULL)
    {
        return -1;
    }
    return topo->disco;
}
int torreVazia(No *topo)
{
    /* TODO 4 */
    return (topo == NULL) ? 1 : 0;
}

int registrarMovimento(Movimento **historico, char origem, char destino, int disco)
{
    /* TODO 5: historico em lista encadeada, mantendo ordem cronologica. */
    Movimento *novo = (Movimento *)malloc(sizeof(Movimento));
    if (novo == NULL)
    {
        return 0;
    }

    novo->origem = origem;
    novo->destino = destino;
    novo->disco = disco;
    novo->proximo = NULL;

    if (*historico == NULL)
    {
        *historico = novo;
    }
    else
    {
        Movimento *atual = *historico;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    return 1;
}
int contarMovimentos(Movimento *historico)
{
    /* TODO 6 */
    int contador = 0;
    Movimento *atual = historico;
    while (atual != NULL)
    {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}
int moverDisco(Torre *origem, Torre *destino, Movimento **historico)
{
    /* TODO 7:
       - origem nao vazia;
       - maior nunca sobre menor;
       - invalido nao altera estrutura;
       - valido usa pop + push e registra historico;
       retorno: 1 sucesso, 0 invalido, -1 erro memoria.
    */
    if (origem == NULL || destino == NULL || torreVazia(origem->topo))
    {
        return 0;
    }

    int discoOrigem = peek(origem->topo);
    int discoDestino = peek(destino->topo);

    if (discoDestino != -1 && discoOrigem > discoDestino)
    {
        return 0;
    }

    int discoRemovido = pop(&(origem->topo));
    if (!push(&(destino->topo), discoRemovido))
    {
        /* Se falhar o push por falta de memória, desfaz o pop para não quebrar a estrutura */
        push(&(origem->topo), discoRemovido);
        return -1;
    }

    if (!registrarMovimento(historico, origem->nome, destino->nome, discoRemovido))
    {
        return -1;
    }
}
int verificarVitoria(Torre *destino, int quantidadeDiscos)
{
    /* TODO 8 */
    if (destino == NULL)
        return 0;

    int contador = 0;
    No *atual = destino->topo;

    while (atual != NULL)
    {
        contador++;
        atual = atual->proximo;
    }

    return (contador == quantidadeDiscos) ? 1 : 0;
}

void liberarTorre(No **topo)
{
    /* TODO 9 */
    if (topo == NULL)
        return;
    No *atual = *topo;
    while (atual != NULL)
    {
        No *aux = atual->proximo;
        free(atual);
        atual = aux;
    }
    *topo = NULL;
}
void liberarHistorico(Movimento **historico)
{
    /* TODO 10 */
    if (historico == NULL)
        return;
    Movimento *atual = *historico;
    while (atual != NULL)
    {
        Movimento *aux = atual->proximo;
        free(atual);
        atual = aux;
    }
    *historico = NULL;
}

int inicializarJogo(Torre *a, Torre *b, Torre *c, int quantidadeDiscos)
{
    /* TODO 11: 3 a 8 discos; A com 1 no topo; B/C vazias. */
    if (quantidadeDiscos < 3 || quantidadeDiscos > 8)
    {
        return 0;
    }

    a->topo = NULL;
    b->topo = NULL;
    c->topo = NULL;

    a->nome = 'A';
    b->nome = 'B';
    c->nome = 'C';

    for (int i = quantidadeDiscos; i >= 1; i--)
    {
        if (!push(&(a->topo), i))
        {
            liberarTorre(&(a->topo));
            return 0;
        }
    }

    return 1;
}
void reiniciarJogo(Torre *a, Torre *b, Torre *c, Movimento **historico, int quantidadeDiscos)
{
    /* TODO 12 */
    liberarTorre(&(a->topo));
    liberarTorre(&(b->topo));
    liberarTorre(&(c->topo));
    liberarHistorico(historico);
    inicializarJogo(a, b, c, quantidadeDiscos);
}
