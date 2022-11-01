#include <stdio.h>
#include <stdlib.h>

struct arvore
{
    int info;
    struct arvore* esq;
    struct arvore* dir;
};

typedef struct arvore Arvore;

// Cria uma Árvore vazia
Arvore* criaArvore()
{
    return NULL;
}

// Verifica se uma Árvore está vazia
int arvoreVazia(Arvore* arv)
{
    if(arv == NULL)
    {
        return 1;
    }

    return 0;
}

Arvore* liberaArvore(Arvore* arv)
{
    if(arvoreVazia(arv) != 0)
    {
        liberaArvore(arv->esq);
        liberaArvore(arv->dir);
        free(arv);
    }
    
    return NULL;
}

Arvore* inserirElemento(Arvore* arv, int v)
{
    if(arv == NULL)
    {
        arv = (Arvore*) malloc(sizeof(Arvore));
        arv->info = v;
        arv->esq = NULL;
        arv->dir = NULL;
    }
    else
    {
        if(v < arv->info)
        {
            arv->esq = inserirElemento(arv->esq, v);
        }
        else
        {
            arv->dir = inserirElemento(arv->dir, v);
        }
    }

    return arv;
}

void imprimeArvore(Arvore* arv)
{
    if(arv != NULL)
    {
        printf("%d\n", arv->info);
        imprimeArvore(arv->esq);
        imprimeArvore(arv->dir);
    }
}

// Remove um elemento da Árvore
Arvore* retiraArvore(Arvore* arv, int v)
{
    if(arv == NULL)
    {
        return NULL;
    }

    if(arv->info > v)
    {
        arv->esq = retiraArvore(arv->esq, v);
    }
    else
    {
        if(arv->info < v)
        {
            arv->dir = retiraArvore(arv->dir, v);
        }
        else // Aqui o elemento foi encontrado
        {
            // O elemento não possui filhos
            if(arv->esq == NULL && arv->dir == NULL)
            {
                free(arv);
                arv = NULL;
            }
            else
            {
                // O elemento só tem filho à direita
                if(arv->esq == NULL)
                {
                    Arvore* temp = arv; // Árvore temporária que aponta para o elemento atual
                    arv = arv->dir;
                    free(temp);
                }
                else
                {
                    // O elemento só tem filho à esquerda
                    if(arv->dir == NULL)
                    {
                        Arvore* temp = arv; // Árvore temporária que aponta para o elemento atual
                        arv = arv->esq;
                        free(temp);
                    }
                    else // O elemento tem os dois filhos
                    {
                        /*
                            Neste caso seguimos a seguinte estratégia:
                            - Primeiro encontramos o elemento que o tem o valor
                            imediatamente inferior ao elemento raiz (valor buscado)
                            - Depois trocamos os valores da raiz com o elemento encontrado
                            - Por último chamamos a função recursivamente para retirar
                            o nó que agora estará mais à direita na subárvore à esquerda.
                            Com isso ele será uma folha ou terá apenas um filho.
                        */
                        Arvore* sae = arv->esq;
                        while (sae->dir != NULL)
                        {
                            sae = sae->dir;
                        }
                        arv->info = sae->info;
                        sae->info = v;
                        arv->esq = retiraArvore(arv->esq, v);
                    }
                }
            }
        }
    }
    return arv;
}

Arvore* buscaArvore(Arvore* arv, int v)
{
    if(arv == NULL)
    {
        return NULL; // O elemento não está na Árvore
    }

    if(arv->info > v)
    {
        return buscaArvore(arv->esq, v);
    }

    if(arv->info < v)
    {
        return buscaArvore(arv->dir, v);
    }

    return arv;
}

// Menu para testar as funções
void menu()
{
    Arvore* arv;
    int opcao;
    int numero;

    arv = criaArvore();

    printf("Uma arvore vazia foi criada...\n\n");

    do
    {
        printf("Digite o numero da opcao desejada\n");
        printf("1- Inserir elemento na Arvore\n");
        printf("2- Imprimir Arvore\n");
        printf("3- Remover elemento da Arvore.\n");
        printf("4- Buscar um elemento na Arvore.\n");
        printf("5- Sair\n");
        
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite um numero inteiro: ");
            scanf("%d", &numero);
            arv = inserirElemento(arv, numero);
            break;
        case 2:
            printf("\n");
            imprimeArvore(arv);
            printf("\n");
            break;
        case 3:
            printf("Digite um numero inteiro: ");
            scanf("%d", &numero);
            arv = retiraArvore(arv, numero);
            printf("\nElemento removido com sucesso!\n\n");
            break;
        case 4:
            printf("Digite um numero inteiro: ");
            scanf("%d", &numero);
            if(buscaArvore(arv, numero) != NULL)
            {
                printf("O numero %d esta na Arvore.\n");
            }
            else
            {
                printf("O numero %d nao esta na Arvore.\n");
            }
            break;
        case 5:
            printf("Programa encerrado.\n");
            break;
        default:
            printf("Opcao invalida. Digite outro numero.\n\n");
            break;
        }
    } while (opcao != 5);
    
}

int main()
{
    menu();
    return 0;
}