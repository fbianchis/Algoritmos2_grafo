#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdlib.h>
///funções de fila
typedef struct tg
{
    int num;
    int peso;
    char text[30];
    struct tg* next;
}no;
typedef struct
{
    int n_elem;
    no* first;
    no* last;
}FILA;
///função para definir e zerar a fila, recebendo a fila;
void define_queue (FILA* Q)
{
    Q->first = NULL;
    Q->last = NULL;
    Q->n_elem = 0;
}
///função para inserir na fila, sempre no ultimo elemnto, recebendo a fila e o novo nó;
int enqueue (FILA* Q, no* novo)
{
    if(Q->first == NULL)
    {
        novo->next = Q->first;
        Q->first = novo;
        Q->last = novo;
    }
    else
    {
        novo->next = Q->last->next;
        Q->last->next = novo;
        Q->last = novo;
    }
    Q->n_elem++;
}
///função para remover um elemento da fila, sempre o primeiro, recebendo a fila e retornando um ponteiro para o primeiro nó;
no* de_queue(FILA* Q)
{
    no* aux = NULL;
    if(Q->first == NULL)
    {
        printf("Lista Vazia!");

        return (aux);
    }
    else if (Q->first == Q->last)
    {
        aux=Q->first;
        Q->n_elem--;
        define_queue(Q);
        return(aux);
    }
    else
    {
        aux=Q->first;
        Q->first = aux->next;
        Q->n_elem--;
        return(aux);
    }

}
///função que recebe uma fila e a imprime;
int printqueue (FILA* Q)
{
    no* aux;
    if(Q->n_elem == 0)
    {
        printf("Lista vazia!");
        return(-1);
    }
    else
    {
        aux = Q->first;
        printf("\nA lista eh:");
        while(aux != NULL)
        {
            printf("->%d",aux->num);
            aux=aux->next;
        }
    }
}
///estrutura usada para execultar as buscas em largura e buscas em profundidade;
typedef struct
{
    int idvertice;
    int distancia;
    int pai;
    int tempo_descoberta;
    int tempo_finalizacao;
    char cor;
}victor;
///estrutura criada para demonstrar a quais arestas os vertices estão ligados;
typedef struct semtag
{
    int idaresta;
    int peso;
    struct semtag* prox;
}aresta;
///estrutura criada para ligar os vertices
typedef struct semnome
{
    int idvertice;
    aresta* are;
    int qtdeare;
    struct semnome* down;

}vertice;
///estrutura criada para indicar a cabeça do grafo
typedef struct
{
    vertice* head;
    int qntd_vertices;
}grafo;
///funçao que recebe um grafo e o define, inicializado
void definegrafo (grafo* a)
{
    a->head=NULL;
    a->qntd_vertices=0;
}
///função que recebe um grafo e percorre até o final dele retornando o ponteiro pro ultimo elemento;
vertice* percorrer_final (grafo* a)
{
    vertice* aux;
    aux = a->head;
    while(aux->down != NULL)
    {
        aux=aux->down;
    }
    return(aux);
}
///função que recebe um grado e um id e verifica se o mesmo já fora inserido no grafo
int verificar_vertice (grafo* a, int id)
{
    vertice* aux;
    aux = a->head;
    while(aux != NULL)
    {
        if (aux->idvertice == id)
        {
            return(1);
        }
        aux=aux->down;
    }
    return(0);
}
///função que recebe um grafo e o id de um vertice e faz a busca dentro do mesmo e retorna um ponteiro para o vertice desejado
vertice* busca_vetice (grafo* a, int id)
{
    vertice* aux;
    aux = a->head;
    while(aux != NULL)
    {
        if(aux->idvertice == id)
        {
            return(aux);
        }
        aux=aux->down;
    }
    return(aux);
}
///função que recebe uma grafo e dois identificadores, e verifica se já foi criado esse vertice e retorna que já existe (1) e não existe (0)
int verificar_aresta_existencia (grafo* a,int id1,int id2)
{
    int resp1 = verificar_vertice(a, id1);
    int resp2 = verificar_vertice(a, id2);
    int aux,aux2;
    if(resp1 == 1 && resp2 == 1)
    {

        vertice* v1;
        v1 = busca_vetice(a,id1);
        vertice* v2;
        v2 = busca_vetice(a,id2);
        aresta* a1;
        aresta* a2;
        a1 = v1->are;
        a2 = v2->are;
        if(a1 == NULL && a2 == NULL)
        {
            return(0);
        }
        else
        {
            while (a1 != NULL)
            {
                if(a1->idaresta == id2)
                {
                    aux = 1;
                }
                a1=a1->prox;
            }
            while (a2 != NULL)
            {
                if(a2->idaresta == id1)
                {
                    aux2 = 1;
                }
                a2=a2->prox;
            }
            if(aux + aux2 == 2)
            {
                return(1);
            }
            return(0);
        }
    }
    else
    {
        return(0);
    }
}
///função que recebe um grafo e dois identificadores de arestas e remove-os;
int remove_aresta(grafo* a, int id1, int id2)
{
    int resp1 = verificar_aresta_existencia(a,id1,id2);
    if(resp1 == 1)
    {
        vertice* v1;
        v1 = busca_vetice(a, id1);
        aresta* a1;
        aresta* aux;
        aresta* aux2;
        a1 = v1->are;
        if(v1->qtdeare == 1)
        {
            while(a1->idaresta != id2)
            {
                a1 = a1->prox;
            }
            v1->are = NULL;
            free(a1);
            v1->qtdeare = v1->qtdeare - 1;
        }
        else
        {
            while(a1->idaresta != id2)
            {
                a1 = a1->prox;
            }
            aux2 = v1->are;
            if(a1 == aux2)
            {
                aux = a1->prox;
                v1->are = aux;
                free(a1);
                v1->qtdeare = v1->qtdeare - 1;
            }
            else
            {
                while(aux2->prox != a1)
                {
                    aux2= aux2->prox;
                }
                aux = a1->prox;
                aux2->prox = aux;
                free(a1);
                v1->qtdeare = v1->qtdeare - 1;
            }

        }

        vertice* v2;
        v2 = busca_vetice(a, id2);
        aresta* a2;
        a2 = v2->are;
        if(v2->qtdeare == 1)
        {
            while(a2->idaresta != id1)
            {
                a2 = a2->prox;
            }
            v2->are = NULL;
            free(a2);
            v2->qtdeare = v2->qtdeare - 1;
        }
        else
        {
            while(a2->idaresta != id1)
            {
                a2 = a2->prox;
            }
            aux2 = v2->are;
            if(a2 == aux2)
            {
                aux = a2->prox;
                v2->are = aux;
                free(a2);
                v2->qtdeare = v2->qtdeare - 1;
            }
            else
            {
                while(aux2->prox != a2)
                {
                    aux2= aux2->prox;
                }
                aux = a2->prox;
                aux2->prox = aux;
                v2->qtdeare = v2->qtdeare - 1;
                free(a2);
            }

        }

    }
    else
    {
        printf("A aresta %d->%d não existe",id1,id2);
        return(0);
    }

}
///função que recebe um grafo e um id do vertice desejado, e o remove do grafo;
int remove_vertice (grafo* a, int id)
{
    if(a->qntd_vertices == 0)
    {
        printf("Grafo vazio, não há vertices para serem exclucidos\n");
        return(0);
    }
    int resp = verificar_vertice(a,id);
    if(resp == 1)
    {
        vertice* v1;
        v1 = busca_vetice(a,id);
        int analizando;
        while(v1->qtdeare != 0)
        {
            analizando = v1->are->idaresta;
            remove_aresta(a,id,analizando);
        }
        if(a->qntd_vertices == 1)
        {
            free(v1);
            definegrafo(a);
        }
        else
        {
            if(a->head == v1)
            {
                a->head = v1->down;
                free(v1);
                a->qntd_vertices = a->qntd_vertices - 1;
            }
            else
            {
                vertice* aux;
                aux = a->head;
                while(aux->down != v1)
                {
                    aux = aux->down;
                }
                aux->down = v1->down;
                a->qntd_vertices = a->qntd_vertices - 1;
                free(v1);
            }
        }
        return(1);
    }
    else
    {
        printf("\nO vertice %d não existe\n",id);
        return(0);
    }
}
///função que recebe uma grafo e dois identificadores, e verifica se já foi criado esse vertice e aresta ou se há possibilidade de criar
int verificar_arestas (grafo* a,int id1,int id2)
{
    int resp1 = verificar_vertice(a, id1);
    int resp2 = verificar_vertice(a, id2);
    if(resp1 == 1 && resp2 == 1)
    {

        vertice* v1;
        v1 = busca_vetice(a,id1);
        vertice* v2;
        v2 = busca_vetice(a,id2);
        aresta* a1;
        aresta* a2;
        a1 = v1->are;
        a2 = v2->are;
        if(a1 == NULL && a2 == NULL)
        {
            return(1);
        }
        else
        {
            while (a1 != NULL)
            {
                if(a1->idaresta == id2)
                {
                    printf("Aresta já criada\n");
                    return(0);
                }
                a1=a1->prox;
            }
            while (a2 != NULL)
            {
                if(a2->idaresta == id1)
                {
                    printf("Aresta já criada");
                    return(0);
                }
                a2=a2->prox;
            }
            return(1);
        }
    }
    else
    {
        if(resp1 == 1 && resp2 == 0)
        {
            printf("O vertice %d não existe\n",id2);
        }
        else if(resp1 == 0 && resp2 == 1)
        {
            printf("O vertice %d não existe\n",id1);
        }
        else if(resp1 == 0 && resp2 == 0)
        {
            printf("Os vertices %d e %d não existem\n",id1,id2);
        }
        return(0);
    }
}
///função que recebe um grafo e dois valores de vertices para realizar a ligação entre eles e então liga-los por uma aresta
int new_aresta (grafo* a, int id1, int id2, int peso)
{
    if(id1 == id2)
    {
        printf("Não é possivel criar laços\n");
        return(0);
    }
    int resp = verificar_arestas(a,id1,id2);
    if(resp == 1)
    {
        vertice* v1;
        v1 = busca_vetice(a,id1);
        vertice* v2;
        v2 = busca_vetice(a,id2);
        aresta* a1;
        aresta* a2;
        aresta* aux;
        a1 = malloc(sizeof(aresta));
        a1->idaresta = id1;
        a1->peso = peso;
        a2 = malloc(sizeof(aresta));
        a2->idaresta = id2;
        a2->peso = peso;
        aux = v2->are;
        v2->are = a1;
        a1->prox = aux;
        aux = v1->are;
        v1->are = a2;
        a2->prox = aux;
        v1->qtdeare = v1->qtdeare + 1;
        v2->qtdeare = v2->qtdeare + 1;
    }
    else if (resp == 0)
    {
        return(-1);
    }
}
///função que recebe um grafo e um id e o insere um novo vertice
int new_vertice (grafo* a,int id)
{
    int resp=0;
    if(a->qntd_vertices != 0)
    {
        resp = verificar_vertice(a,id);
        if (resp == 1)
        {
            printf("Vertice já criado\n");
            return(-1);
        }
        else if (resp == 0)
        {
            vertice* v;
            v = percorrer_final(a);
            vertice* v2;
            v2 = malloc(sizeof(vertice));
            v2->are =NULL;
            v2->down = NULL;
            v2->idvertice = id;
            v2->qtdeare = 0;
            v->down = v2;
            a->qntd_vertices++;
        }
    }
    else
    {
        vertice* v2;
        v2 = malloc(sizeof(vertice));
        v2->are =NULL;
        v2->down = NULL;
        v2->idvertice = id;
        v2->qtdeare = 0;
        a->head = v2;
        a->qntd_vertices++;
    }

}
/// função que recebe um grafo e o imprime
void print_grafo (grafo* a)
{
    if(a->qntd_vertices != 0)
    {
        vertice* aux;
        aresta* aux2;
        aux = a->head;
        while(aux != NULL)
        {
            printf("V%d->",aux->idvertice);
            aux2 = aux->are;
            while(aux2 != NULL)
            {
                printf("A%d(%d)->",aux2->idaresta,aux2->peso);
                aux2=aux2->prox;
            }
            printf("[%d]\n",aux->qtdeare);
            aux = aux->down;
        }
    }
    else
    {
        printf("Grafo vazio!\n");
    }
}
///função que recebe um grafo e o vertice desejado e retorna o grau do vertice em forma de inteiro
int grau_vertice (grafo* a,int id)
{
    int resp = verificar_vertice(a,id);
    if(resp == 1)
    {
        vertice* aux;
        aux = busca_vetice(a,id);
        return(aux->qtdeare);
    }
    else
    {
        return(0);
    }

}
///função que recebe um grafo e o imprime em uma matriz de adjacencias, com 1 a existencia da aresta, 0 com a inexistencia e -1 a impossibilidade
void matriz_adj (grafo* a)
{
    //linhas = i
    //colunas = j
    int i,j,linhas,colunas;
    int resp;
    linhas = a->qntd_vertices + 1;
    colunas = linhas;
    int matriz[linhas][colunas];
    vertice* aux;
    aux = a->head;
    i=1;
    for(i=0;i<linhas;i++)
    {
        for(j=0;j<colunas;j++)
        {
            matriz[i][j]=0;
        }

    }
    matriz[1][1]=-1;
    i=1;
    while(aux != NULL)
    {
        matriz[i][0]=aux->idvertice;
        matriz[0][i]=aux->idvertice;
        matriz[i+1][i+1] = -1;
        aux=aux->down;
        i++;
    }
    for(i=0;i<linhas;i++)
    {
        for(j=0;j<colunas;j++)
        {
            resp = verificar_aresta_existencia(a,i,j);
            if(resp == 1)
            {
                matriz[i][j]=1;

            }
            printf("%d\t",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
///função que recebe um grafo e execulta a busca em largura nele, e imprime um vetor contendo o id do vertice, o pai, a distancia da origem e a cor dele.
int busca_largura (grafo* a,int id_origem, int imprimir)
{
    int vertices = a->qntd_vertices;
    victor vetor[vertices];
    int i=0;
    vertice* aux = a->head;
    FILA Q;
    define_queue(&Q);
    no* elemento;
    no* elemento2;
    while(aux != NULL)
    {
        if(aux->idvertice == id_origem)
        {
            elemento = malloc(sizeof(no));
            elemento->num = id_origem;
            vetor[i].idvertice=aux->idvertice;
            vetor[i].distancia=0;
            vetor[i].pai = -1;
            vetor[i].cor = 'c';
        }
        else
        {
            vetor[i].idvertice=aux->idvertice;
            vetor[i].distancia=9999;
            vetor[i].pai = -1;
            vetor[i].cor = 'b';
        }
        aux=aux->down;
        i++;
    }
    enqueue(&Q, elemento);
    while(Q.n_elem != 0)
    {
        aux = busca_vetice(a,Q.first->num);
        elemento2 = de_queue(&Q);
        free(elemento2);
        aresta* auxare = aux->are;
        int j=0;
        while(vetor[j].idvertice != aux->idvertice)
        {
                j++;
        }
        while(auxare != NULL)
        {
            i=0;

            while(vetor[i].idvertice != auxare->idaresta)
            {
                i++;
            }
            if(vetor[i].cor == 'b')
            {
                vetor[i].cor = 'c';
                vetor[i].distancia = vetor[j].distancia + 1;
                vetor[i].pai = vetor[j].idvertice;
                //printf("\n%d é pai de %d\n",vetor[i].pai,vetor[i].idvertice);
                elemento2 = malloc(sizeof(no));
                elemento2->num = auxare->idaresta;
                enqueue(&Q,elemento2);
            }
            auxare = auxare->prox;
        }
        vetor[j].cor = 'p';
        //printqueue(&Q);
    }
    int contadorpai = 0;
    if(imprimir == 1)
    {
        printf("\n");
        for(i=0;i<vertices;i++)
        {
            if(vetor[i].pai == -1)
            {
                contadorpai++;
            }
            printf("ID:%d DISTANCIA:%d PAI:%d COR:%c\n",vetor[i].idvertice,vetor[i].distancia,vetor[i].pai,vetor[i].cor);
        }
    }
    else
    {
        for(i=0;i<vertices;i++)
        {
            if(vetor[i].pai == -1)
            {
                contadorpai++;
            }
        }
    }
    if(contadorpai == 1)
    {
        return(1);
    }
    else
    {
        return(0);
    }

}
///função que recebe um grafo, o vetor que irá ser modificado, qtde de vertices, o indice atual, e o tempo e faz a visita em cada item da lista de adjacencia
int dfs_visit(grafo* a,victor vetor[],int vertices,int u,int* tempo)
{
    //printf("ATUAL U: %d COR:%c\n\n",vetor[u].idvertice,vetor[u].cor);
    vetor[u].cor = 'c';
    *tempo = *tempo + 1;
    vetor[u].tempo_descoberta = *tempo;
    aresta* auxare;
    vertice* auxver;
    auxver = busca_vetice(a,vetor[u].idvertice);
    auxare = auxver->are;
    int v=0;
    int i;
    //printf("\n\n\n");
    while(auxare != NULL)
    {
        v=0;
        while(vetor[v].idvertice != auxare->idaresta)
        {
            v++;
        }
        //printf("%d",auxver->qtdeare);
        //printf("ATUAL ADJACENCIA: %d COR:%c\n\n",vetor[v].idvertice,vetor[v].cor);
        if(vetor[v].cor == 'b')
        {
            //printf("****ENTROU\n");
            vetor[v].pai = vetor[u].idvertice;
            dfs_visit(a,vetor,vertices,v,tempo);
        }
        auxare = auxare->prox;
    }
    vetor[u].cor = 'p';
    *tempo = *tempo + 1;
    vetor[u].tempo_finalizacao = *tempo;

}
///função que recebe um grafo e executa a busca em profundidade e retorna 1 para i grafo conexo e 0 para não conexo
int dfs(grafo* a,int imprimir)
{
    int vertices = a->qntd_vertices;
    victor vetor[vertices];
    int i=0,tempo = 0;
    vertice* aux = a->head;
    while(aux != NULL)
    {
        vetor[i].idvertice = aux->idvertice;
        vetor[i].cor ='b';
        vetor[i].pai = -1;
        vetor[i].tempo_descoberta = -1;
        vetor[i].tempo_finalizacao = -1;
        aux = aux->down;
        i++;
    }
    for(i=0;i<vertices;i++)
    {
        //printf("ATUAL EXECUÇÃO: %d\n",i);
        if(vetor[i].cor == 'b')
        {
            dfs_visit(a,vetor,vertices,i,&tempo);
        }
        //printf("\n______________________________________________________\n\n");
    }
    //printf("\n\n\n");
    int contadorpai = 0;
    if(imprimir == 1)
    {
        for(i=0;i<vertices;i++)
        {
            if(vetor[i].pai == -1)
            {
                contadorpai++;
            }
            printf("ID:%d PAI:%d TEMPOD:%d TEMPOF:%d COR:%c\n",vetor[i].idvertice,vetor[i].pai,vetor[i].tempo_descoberta,vetor[i].tempo_finalizacao,vetor[i].cor);
        }
    }
    else
    {
        for(i=0;i<vertices;i++)
        {
            if(vetor[i].pai == -1)
            {
                contadorpai++;
            }
        }
        if(contadorpai == 1)
        {
            return(1);
        }
        else
        {
            return(0);
        }
    }


}
///função que recebe um grafo e dois vertice e retorna o peso desta aresta
int peso (grafo* a,int id1, int id2)
{
    int resp = verificar_aresta_existencia (a,id1,id2);
    if(resp == 1)
    {
        vertice* aux_vertice;
        aresta* aux_aresta;
        aux_vertice = busca_vetice(a,id1);
        aux_aresta = aux_vertice->are;
        while(aux_aresta->idaresta != id2)
        {
            aux_aresta = aux_aresta->prox;
        }
        return(aux_aresta->peso);
    }
    else
    {
        return(0);
    }
}
///função para verificar se um determinado numero esta na fila, retorna 0 para falso e 1 para verdadeiro
int existe_fila (int id, FILA* Q)
{
    no* aux;
    aux = Q->first;
    while(aux != NULL)
    {
        if(aux->num == id)
        {
            return(1);
        }
        aux = aux->next;
    }
    return(0);
}
///função que recebe um grafo, o vetor e o indice dos vertices u e v e retorna alteraçoes na distancia e no pai do vertice u
void relax(grafo* a,victor vetor[],int u, int v)
{
    int peso_aresta = peso(a,vetor[u].idvertice,vetor[v].idvertice);
    //printf("ANALIZANDO U>%d  V>%d\n",vetor[u].idvertice,vetor[v].idvertice);
    //printf("RESULTADO PESO %d\n",peso_aresta);
    //printf("PESO %d e %d\n\n\n",vetor[v].distancia,vetor[u].distancia + peso_aresta);
    if(vetor[v].distancia >(vetor[u].distancia + peso_aresta))
    {
        //printf("ENTROU =D\n\n\n");
        vetor[v].distancia = vetor[u].distancia + peso_aresta;
        vetor[v].pai = vetor[u].idvertice;
    }
}
///função que recebe uma fila e retira o menor valor dela;
no* de_queue_minimo (victor vetor[], FILA* Q,int vertices)
{
    no* minimo;
    no* aux = Q->first;
    int i=0;
    int minimo_valor;
    int j=0;
    for(i=0;i<vertices;i++)
    {
        if(vetor[i].cor == 'b')
        {
            if(minimo_valor > vetor[i].distancia )
            {
                minimo_valor = vetor[i].distancia;
                j=i;
            }
        }
    }
    vetor[j].cor = 'p';
    while(aux->num != vetor[j].idvertice)
    {
        aux = aux->next;
    }
    minimo = aux;
    if(minimo == Q->first)
    {
        Q->first = minimo->next;
        Q->n_elem--;
        return minimo;
    }
    else if (minimo == Q->last)
    {
        aux = Q->first;
        while (aux->next != minimo)
        {
            aux = aux->next;
        }
        aux->next = Q->last->next;
        Q->last = aux;
        Q->n_elem--;
        return(minimo);
    }
    else
    {
        aux = Q->first;
        while (aux->next != minimo)
        {
            aux = aux->next;
        }
        aux->next =  minimo->next;
        Q->n_elem--;
        return(minimo);
    }
}
///função que recebe um grafo, o vertice origem e retorna a arvore geradora minima
void alg_prim (grafo* a,int id_origem)
{
    int resp = dfs(a,0);
    if(resp == 1)
    {
        int vertices = a->qntd_vertices;
        victor vetor[vertices];
        int i=0;
        int v;
        vertice* aux = a->head;
        FILA Q;
        define_queue(&Q);
        no* elemento;
        no* elemento2;
        while(aux != NULL)
        {
            if(aux->idvertice == id_origem)
            {
                elemento = malloc(sizeof(no));
                elemento->num = id_origem;
                elemento->peso = 0;
                vetor[i].idvertice=aux->idvertice;
                vetor[i].distancia=0;
                vetor[i].pai = -1;
            }
            else
            {
                elemento = malloc(sizeof(no));
                elemento->num = aux->idvertice;
                elemento->peso = 9999;
                vetor[i].idvertice=aux->idvertice;
                vetor[i].distancia=9999;
                vetor[i].pai = -1;
            }
            vetor[i].cor = 'b';
            enqueue(&Q,elemento);
            aux=aux->down;
            i++;
        }
        printf("\n");
        while(Q.n_elem != 0)
        {
            elemento2 = de_queue_minimo(vetor,&Q,vertices);
            aux = busca_vetice(a,elemento2->num);
            aresta* auxare = aux->are;
            int u=0;
            while(vetor[u].idvertice != aux->idvertice)
            {
                u++;
            }
            while(auxare != NULL)
            {
                v=0;
                while(vetor[v].idvertice != auxare->idaresta)
                {
                    v++;
                }
                resp = existe_fila(vetor[v].idvertice,&Q);
                int respp = peso(a,vetor[u].idvertice,vetor[v].idvertice);
                if((resp == 1) && (respp < vetor[v].distancia))
                {
                    vetor[v].pai = vetor[u].idvertice;
                    vetor[v].distancia = respp;
                }
            auxare = auxare->prox;
            }
        }
        for(i=0;i<vertices;i++)
        {
            printf("ID:%d DISTANCIA:%d PAI:%d\n",vetor[i].idvertice,vetor[i].distancia,vetor[i].pai);
        }
    }
    else
    {
        printf("Grafo não conexo, logo não pode ser executado");
    }
}
///função que recebe um grafo, o vertice origem e retorna o caminho minimo do grafo
void dijkstra (grafo* a,int id_origem)
{
    int resp = dfs(a,0);
    if(resp == 1)
    {
        int vertices = a->qntd_vertices;
        victor vetor[vertices];
        int i=0;
        int v;
        int u=0;
        vertice* aux = a->head;
        FILA Q;
        define_queue(&Q);
        no* elemento;
        no* elemento2;
        while(aux != NULL)
        {
            if(aux->idvertice == id_origem)
            {
                elemento = malloc(sizeof(no));
                elemento->num = id_origem;
                elemento->peso = 0;
                vetor[i].idvertice=aux->idvertice;
                vetor[i].distancia=0;
                vetor[i].pai = -1;
            }
            else
            {
                elemento = malloc(sizeof(no));
                elemento->num = aux->idvertice;
                elemento->peso = 9999;
                vetor[i].idvertice=aux->idvertice;
                vetor[i].distancia=9999;
                vetor[i].pai = -1;
            }
            vetor[i].cor = 'b';
            enqueue(&Q,elemento);
            aux=aux->down;
            i++;
        }
        while(Q.n_elem != 0)
        {
            elemento2 = de_queue_minimo(vetor, &Q, vertices);
            aux = busca_vetice(a, elemento2->num);
            free(elemento2);
            aresta* auxare = aux->are;
            u=0;
            while(vetor[u].idvertice != aux->idvertice)
            {
                u++;
            }
            while(auxare != NULL)
            {
                v=0;
                while(vetor[v].idvertice != auxare->idaresta)
                {
                    v++;
                }
                relax(a,vetor,u,v);
                auxare = auxare->prox;
            }
        }
        printf("\n");
        for(i=0;i<vertices;i++)
        {
            printf("ID:%d DISTANCIA:%d PAI:%d\n",vetor[i].idvertice,vetor[i].distancia,vetor[i].pai);
        }
    }
    else
    {
        printf("Grafo não conexo, logo não pode ser executado");
    }
}
///função que inicializa o grafo apresentado nos finais de cada aula
void grafo_teste (grafo* a)
{
    definegrafo(a);
    new_vertice(a,1);
    new_vertice(a,2);
    new_vertice(a,3);
    new_vertice(a,4);
    new_vertice(a,5);
    new_vertice(a,6);
    new_vertice(a,7);
    new_vertice(a,8);
    new_vertice(a,9);
    new_vertice(a,10);
    new_aresta(a,1,2,7);
    new_aresta(a,1,4,9);
    new_aresta(a,1,5,10);
    new_aresta(a,1,6,8);
    new_aresta(a,1,8,9);
    new_aresta(a,1,10,8);
    new_aresta(a,2,3,4);
    new_aresta(a,2,4,5);
    new_aresta(a,2,9,9);
    new_aresta(a,2,10,9);
    new_aresta(a,3,4,1);
    new_aresta(a,3,5,4);
    new_aresta(a,4,5,3);
    new_aresta(a,5,6,18);
    new_aresta(a,6,7,9);
    new_aresta(a,6,8,9);
    new_aresta(a,7,8,3);
    new_aresta(a,7,9,6);
    new_aresta(a,8,9,4);
    new_aresta(a,8,10,2);
    new_aresta(a,9,10,2);
}
///função que inicializa o grafo apresentado em aula de busca em largura
void grafo_largura (grafo* a)
{
    definegrafo(a);
    new_vertice(a,1);
    new_vertice(a,2);
    new_vertice(a,3);
    new_vertice(a,4);
    new_vertice(a,5);
    new_vertice(a,6);
    new_vertice(a,7);
    new_vertice(a,8);
    new_aresta(a,1,2,1);
    new_aresta(a,1,5,1);
    new_aresta(a,2,6,1);
    new_aresta(a,3,7,1);
    new_aresta(a,3,6,1);
    new_aresta(a,3,4,1);
    new_aresta(a,4,7,1);
    new_aresta(a,4,8,1);
    new_aresta(a,6,7,1);
    new_aresta(a,7,8,1);
    print_grafo(a);
}
///função que inicializa o grafo apresentado em aula de arvore geradora mínima
void grafo_arvore_minima (grafo* a)
{
    definegrafo(a);
    new_vertice(a,1);
    new_vertice(a,2);
    new_vertice(a,3);
    new_vertice(a,4);
    new_vertice(a,5);
    new_vertice(a,6);
    new_vertice(a,7);
    new_vertice(a,8);
    new_vertice(a,9);
    new_aresta(a,1,2,4);
    new_aresta(a,1,8,8);
    new_aresta(a,2,3,8);
    new_aresta(a,2,8,11);
    new_aresta(a,3,4,7);
    new_aresta(a,3,6,4);
    new_aresta(a,3,9,2);
    new_aresta(a,4,5,9);
    new_aresta(a,4,6,14);
    new_aresta(a,5,6,10);
    new_aresta(a,6,7,2);
    new_aresta(a,7,8,1);
    new_aresta(a,7,9,6);
    new_aresta(a,8,9,7);

}
int main (void)
{
    setlocale(LC_ALL,"Portuguese");
    grafo a;
    definegrafo(&a);
    int resp=0;
    int id1;
    int id2;
    int aux;
    int i,j,aresta_peso;
    char limpar;
    char sequencia;
    printf("Welcome!\n");
    while(resp < 13)
    {
        printf("0.  Inserir grafo já implementado.\n1.  Inserir Vértices.\n2.  Inserir Arestas.\n3.  Visualizar Grafo.\n4.  Remover Vértices.\n5.  Remover Arestas.\n6.  Grau do vertice.\n");
        printf("7.  Verificar se o grafo é conexo.\n8.  Matriz de Adjacência.\n9.  Busca em largura.\n10. Busca em profundidade.\n11. Caminho Mínimo.\n12. Árvore Geradora Mínima.\n13. Sair.\nEscolha uma opção: ");
        scanf("%d",&resp);
        fflush(stdin);
        if(resp == 0)
        {
            do
            {
                printf("\n\n1.Grafo do final de cada transparencia\n2.Grafo apresentado na aula de busca em largura\n3.Grafo apresentado na aula de busca em largura\n");
                scanf("%d",&resp);
                fflush(stdin);
                if(resp == 1)
                {
                    grafo_teste(&a);
                }
                else if(resp == 2)
                {
                    grafo_largura(&a);
                }
                else if (resp == 3)
                {
                    grafo_arvore_minima(&a);
                }
            }while(resp<=0 || resp>=4);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 1)
        {
            printf("Deseja inserir em sequência?(s para sim): ");
            scanf("%c",&sequencia);
            fflush(stdin);
            if(sequencia == 's')
            {
                printf("Quantos vertices deseja inserir?: ");
                scanf("%d",&j);
                fflush(stdin);
                for(i=1;i<=j;i++)
                {
                    new_vertice(&a,i);
                }
            }
            else
            {
                do
                {
                    printf("Digite o vertice a ser criado: ");
                    scanf("%d",&id1);
                }while(id1<=0);
                fflush(stdin);
                new_vertice(&a,id1);
            }
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 2)
        {
            printf("Digite o primeiro vertice: ");
            scanf("%d",&id1);
            fflush(stdin);
            printf("Digite o segundo vertice: ");
            scanf("%d",&id2);
            printf("Digite o peso desta aresta: ");
            scanf("%d",&aresta_peso);
            fflush(stdin);
            new_aresta(&a,id1,id2,aresta_peso);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 3)
        {
            printf("\nO grafo está da seguinte forma até o momento:\n\n");
            print_grafo(&a);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 4)
        {
            printf("Digite o vertice a ser removido: ");
            scanf("%d",&id1);
            fflush(stdin);
            remove_vertice(&a,id1);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 5)
        {
            printf("Digite o primeiro vertice: ");
            scanf("%d",&id1);
            printf("Digite o segundo vertice: ");
            scanf("%d",&id2);
            fflush(stdin);
            remove_aresta(&a,id1,id2);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 6)
        {
            printf("\nDigite o vertice: ");
            scanf("%d",&id1);
            fflush(stdin);
            aux = grau_vertice(&a,id1);
            printf("\nO grau do vertice %d é %d",id1,aux);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 7)
        {
            resp = dfs(&a,0);
            if(resp == 1)
            {
                printf("\nO grafo é conexo");
            }
            else
            {
                printf("\nO grafo não é conexo");
            }
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 8)
        {
            fflush(stdin);
            printf("\n");
            matriz_adj(&a);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 9)
        {
            printf("Informe um vertice para ser o primeiro analizado: ");
            scanf("%d",&id1);
            fflush(stdin);
            busca_largura(&a,id1,1);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 10)
        {
            dfs(&a,1);
            fflush(stdin);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 11)
        {
            printf("Informe um vertice para ser o primeiro analizado: ");
            scanf("%d",&id1);
            fflush(stdin);
            dijkstra(&a,id1);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
        else if(resp == 12)
        {
            printf("Informe um vertice para ser o primeiro analizado: ");
            scanf("%d",&id1);
            fflush(stdin);
            alg_prim(&a,id1);
            printf("\nDeseja limpar a tela?(s para sim, qualquer outro caractere para não)\n");
            scanf("%c",&limpar);
            if(limpar == 's')
            {
                system("cls");
            }
            else
            {
                printf("\n\n\n");
            }
        }
    }
    printf("Até mais");
}
