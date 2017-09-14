#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


typedef struct Date {
    int minuto;
    int hora;
    int dia;
    int mes;
    int ano;
} Note_Date;

typedef struct NOTE {
    char descricao[80];
    Note_Date data_compromisso;
} Compromisso;

// Definição da Estrutura Lista Linear Simplemente Encadeada
typedef struct Bloco {  
    Compromisso compromisso;
    struct Bloco *prox;
} Nodo;
//funções auxiliares
//Inicializa a Lista Linear Simplesmente Encadeada
void inicializa_lista(Nodo **N) {
    *N = NULL;
}
//Aloca memória par'MyLista um nodo da lista Linear Simplesmente Encadeada
Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));
    if(!p) {
        printf("Problema de alocação");
        exit(0);
    }
    return p;
}

void printa_datas(Note_Date data_compromisso){
    printf("%d/%d/%d %d:%d", data_compromisso.dia, data_compromisso.mes, data_compromisso.ano, data_compromisso.hora, data_compromisso.minuto);
}

void printa_compromisso(Compromisso comp){
    printa_datas(comp.data_compromisso);
    printf("%s", comp.descricao);
}

int compara_datas(Note_Date data1, Note_Date data2){
    if(data1.ano > data2.ano){
        return 1;
    }else if(data1.ano < data2.ano){
        return -1;
    }else{
        if(data1.mes > data2.mes){
            return 1;
        }else if(data1.mes < data2.mes){
            return -1;
        }else{
            if(data1.dia > data2.dia){
                return 1;
            }else if(data1.dia < data2.dia){
                return -1;
            }else{
                if(data1.hora > data2.hora){
                    return 1;
                }else if(data1.hora < data2.hora){
                    return -1;
                }else{
                    if(data1.minuto > data2.minuto){
                        return 1;
                    }else if(data1.minuto < data2.minuto){
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

bool dado_esta_entre_os_nos( Compromisso compromisso, Nodo*aux1, Nodo*aux2 ){
    return ( compara_datas( compromisso.data_compromisso, aux1->compromisso.data_compromisso ) >= 0 ) 
        && ( compara_datas( compromisso.data_compromisso, aux2->compromisso.data_compromisso ) <= 0 );
}


Nodo * pegar_o_ultimo_no( Nodo * aux ) {
    while(aux->prox != NULL)
        aux = aux->prox;
    return aux;
}

//Operações que incidem sobre a estrutura
//Operação de Inserção no Final da Lista
void insere_fim_lista(Nodo **N, Compromisso compromisso) {
    Nodo *novo, * aux;
    novo = Cria_Nodo( );
    novo->compromisso = compromisso;
    novo->prox = NULL;
    if(*N == NULL)
        *N = novo;
    else {
        aux = pegar_o_ultimo_no( *N );
        aux->prox = novo;
    }
}
//Operação de Inserção no Início da Lista
void insere_inicio_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo;
    novo = Cria_Nodo();
    novo->compromisso = compromisso;
    novo->prox = *N;
    *N = novo;
}
// //Operação de Inserção ordenada
void insere_ordenado_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo, *aux1, *aux2;
    novo = Cria_Nodo();



    novo->compromisso = compromisso;
    if(*N == NULL) {//lista está vazia
        novo->prox = NULL;
        *N=novo;
    }
    else {
        if( compara_datas( compromisso.data_compromisso, ( *N )->compromisso.data_compromisso ) < 0 ) // insere no incio da lista
            insere_inicio_lista(N, compromisso);
        else {
            for(aux1=*N; aux1->prox != NULL; aux1 = aux1->prox) {
                aux2 = aux1->prox;
                if( dado_esta_entre_os_nos( compromisso, aux1, aux2 ) ) { //insere no meio da lista
                    aux1->prox = novo;
                    novo->prox = aux2;
                    break;
                }
            }
            if(aux1->prox == NULL)//insere no final da lista
                insere_fim_lista(N, compromisso);
        }
    }
}
//Operação de Remoção do Início da Lista Linear Simplesmente Encadeada
int remove_inicio_lista(Nodo **N, char *dado [80]) {
    Nodo *aux;
    if(*N == NULL) //verifica se a lista está vazia
        return 0;
    else {
        *dado = (*N)->compromisso.descricao;
        aux = (*N)->prox;
        free(*N);
        *N = aux;
    }
    return 1;
}

//Operação de Remoção do Início da Lista Linear Simplesmente Encadeada
int remove_final_lista(Nodo **N, char *dado[80]) {
    Nodo *aux, *anterior;
    if(*N == NULL) //verifica se a lista está vazia
        return 0;
    else {

        aux = *N;
        while(aux->prox != NULL) {
            anterior = aux;
            aux = aux->prox;
        }

        *dado = aux->compromisso.descricao;
        free(aux);
        anterior->prox = NULL;

    }
    return 1;
}


//Operação de Impressão dos Elementos da Lista Linear Simplesmente Encadeada
void imprime_lista_ecandeada(Nodo *N) {
    Nodo *aux;
    if(N == NULL)
        printf("\n A lista está vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox)
            printf("\n%s", aux->compromisso.descricao);
    }
}
//Função main
int main() {
    Nodo *MyList;
    int menu, valor;
    inicializa_lista(&MyList);
    do {
        printf("\n1. Insere no fim da Lista");
        printf("\n2. Insere no inicio da Lista");
        printf("\n3. Exclui do inicio da Lista");
        printf("\n4. Exclui do final da Lista");
        printf("\n5. Imprime Lista");
        printf("\n6. Insere ordenado\n");
        printf("\n7. sair\n");
        scanf("%d", &menu);
        switch(menu) {
        case 1:
            printf("\nInforme o valor a ser inserido no final da lista:");
            scanf("%d", &valor);
            // insere_fim_lista(&MyList, valor);
            break;
        case 2:
            printf("\nInforme o valor a ser inserido no inicio da lista:");
            scanf("%d", &valor);
            // insere_inicio_lista(&MyList, valor);
            break;
        case 3:
            if(remove_inicio_lista(&MyList, &valor) == 0)
                printf("\nA lista está vazia!!");
            else
                printf("\nO valor excluido do inicio da lista foi: %d", valor);
            break;

        case 4:
            if(remove_final_lista(&MyList, &valor) == 0)
                printf("\nA lista está vazia!!");
            else
                printf("\nO valor excluido do inicio da lista foi: %d", valor);
            break;
        case 5:
            imprime_lista_ecandeada(MyList);
            break;
        case 6:
            printf("\nInforme o valor desejado a inserir na Lista\n");
            Compromisso compromissoTemp;

            char my_text [80] = "TENHO Q COPIAR ESSA MERDA"; 

            strcpy( compromissoTemp.descricao, my_text );
            compromissoTemp.data_compromisso.dia = 25;
            compromissoTemp.data_compromisso.mes = 4;
            compromissoTemp.data_compromisso.ano = 1998;
            compromissoTemp.data_compromisso.hora = 23;
            compromissoTemp.data_compromisso.hora = 59;
            
            
            insere_ordenado_lista(&MyList, compromissoTemp);
            break;
        case 7:
            printf("\n\n\nSaindo do programa!");
            break;
        default:
            printf("\nOpcao Invalida!!!");
        }
    } while(menu != 7);
    return 0;
}
