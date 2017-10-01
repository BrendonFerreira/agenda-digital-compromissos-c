#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>


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

// DefiniÃ§Ã£o da Estrutura Lista Linear Simplemente Encadeada
typedef struct Bloco {  
    Compromisso compromisso;
    struct Bloco *prox;
} Nodo;
//funÃ§Ãµes auxiliares
//Inicializa a Lista Linear Simplesmente Encadeada
void inicializa_lista(Nodo **N) {
    *N = NULL;
}
//Aloca memÃ³ria par'MyLista um nodo da lista Linear Simplesmente Encadeada
Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));
    if(!p) {
        printf("Problema de alocaÃ§Ã£o");
        exit(0);
    }
    return p;
}

Note_Date le_data(){
    Note_Date data_compromisso;
    printf("digite a data do compromisso: dd/mm/yyyy hh:mm\n");
    scanf("%d/%d/%d %d:%d", &data_compromisso.dia, &data_compromisso.mes, &data_compromisso.ano, &data_compromisso.hora, &data_compromisso.minuto);
    return(data_compromisso);
}

Compromisso le_compromisso(){
    Compromisso compromisso;
    printf("digite a descriÃ§Ã£o do compromisso:\n");
    fgets(compromisso.descricao, sizeof( compromisso.descricao ), stdin );
    // fgets(compromisso.descricao, sizeof( compromisso.descricao ), stdin );
    return(compromisso);
}

Compromisso le_dados(){
    Compromisso compromisso;
    compromisso = le_compromisso();
    compromisso.data_compromisso = le_data();
    return compromisso;
}

void printa_datas(Note_Date data_compromisso){
    printf("%d/%d/%d %d:%d - ", data_compromisso.dia, data_compromisso.mes, data_compromisso.ano, data_compromisso.hora, data_compromisso.minuto);
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

//OperaÃ§Ãµes que incidem sobre a estrutura
//OperaÃ§Ã£o de InserÃ§Ã£o no Final da Lista
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
//OperaÃ§Ã£o de InserÃ§Ã£o no InÃ­cio da Lista
void insere_inicio_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo;
    novo = Cria_Nodo();
    novo->compromisso = compromisso;
    novo->prox = *N;
    *N = novo;
}
//OperaÃ§Ã£o de InserÃ§Ã£o ordenada
void insere_ordenado_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo, *aux1, *aux2;
    novo = Cria_Nodo();
    novo->compromisso = compromisso;
    if(*N == NULL) {//lista estÃ¡ vazia
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

//OperaÃ§Ã£o de RemoÃ§Ã£o do InÃ­cio da Lista Linear Simplesmente Encadeada
int remove_inicio_lista(Nodo **N, char *dado [80]) {
    Nodo *aux;
    if(*N == NULL) //verifica se a lista estÃ¡ vazia
        return 0;
    else {
        *dado = (*N)->compromisso.descricao;
        aux = (*N)->prox;
        free(*N);
        *N = aux;
    }
    return 1;
}

//OperaÃ§Ã£o de RemoÃ§Ã£o do InÃ­cio da Lista Linear Simplesmente Encadeada
int remove_final_lista(Nodo **N, char *dado[80]) {
    Nodo *aux, *anterior;
    if(*N == NULL) //verifica se a lista estÃ¡ vazia
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

//OperaÃ§Ã£o de ImpressÃ£o dos Elementos da Lista Linear Simplesmente Encadeada
void imprime_lista_ecandeada(Nodo *N) {
    Nodo *aux;
    if(N == NULL)
        printf("\n A lista estÃ¡ vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox) { 
            printa_compromisso( aux->compromisso );
            printf("\n");
        }
    }
} 

void salva_compromisso(Compromisso compromisso){
	FILE *fp;
	fp = fopen("agenda.dat", "w+");
	if(fp == NULL){
		printf("ERRO: arquivo 'agenda.dat' nao existe");
	}
	fwrite(&compromisso, sizeof(Compromisso), 1, fp);
	fclose(fp);
}

void imprime_agenda(Compromisso compromisso){
	FILE *fp;
	fp = fopen("agenda.dat", "w+");
	if(fp == NULL){
		printf("ERRO: arquivo 'agenda.dat' nao existe");
	}
	fread(&compromisso, sizeof(Compromisso), 1, fp);
	printa_compromisso(compromisso);
	fclose(fp);             
}

int strcicmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

void buscar_compromisso( Nodo * N, char pesquisa [80]  ) {

    Nodo *aux;
    if(N == NULL)
        printf("\n A lista estÃ¡ vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox) { 
            printf( "%d", strcicmp( pesquisa, aux->compromisso.descricao ) );
            printf("\n");
        }
    }
}


//FunÃ§Ã£o main
int main(){
    Nodo *MyList;
    Compromisso novo_compromisso;
    char pesquisa[80];
    int menu, valor;
    int choice;
    FILE *fp;
    inicializa_lista(&MyList);
    do {
        printf("\n1. Novo compromisso");
        printf("\n2. Cancelar compromisso");
        printf("\n3. Listar compromissos");
        printf("\n4. Listar compromissos da agenda.dat");
        printf("\n5. sair\n");
        scanf("%d%*c", &menu);
        switch(menu) {
            case 1:
                novo_compromisso = le_dados();
                insere_ordenado_lista( &MyList, novo_compromisso );
				printf("Deseja salvar compromisso em um arquivo? 1-sim/2-nao\n");
				scanf("%d", &choice);
				switch(choice){
					case 1:
						salva_compromisso(novo_compromisso);
						break;
					case 2:
						imprime_agenda(novo_compromisso);
						break;
					default:
						printf("\nOpcao Invalida!!!");
				}
                break;
            case 2:
                break;
            case 3:
                imprime_lista_ecandeada(MyList);
				break;
			case 4:
				imprime_agenda(novo_compromisso);	
				break;
            case 5:
                printf("\n\n\nSaindo do programa!");
                break;
            case 6: 
                // fflush( stdin );
                fgets( pesquisa, 80, stdin );
                buscar_compromisso( MyList, pesquisa );
                break;
            default:
                printf("\nOpcao Invalida!!!");
        }
    } while(menu != 5);
    return 0;
}
