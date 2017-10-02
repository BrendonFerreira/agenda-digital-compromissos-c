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

// Definição da Estrutura Lista Linear Simplemente Encadeada
typedef struct Bloco {  
    Compromisso compromisso;
    struct Bloco *prox;
} Nodo;

//Inicializa a Lista Linear Simplesmente Encadeada
void inicializa_lista(Nodo **N) {
    *N = NULL;
}

Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));
    if(!p) {
        printf("Problema de alocação");
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
    printf("digite a descricao do compromisso:\n");
    fgets(compromisso.descricao, sizeof( compromisso.descricao ), stdin );
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
void insere_inicio_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo;
    novo = Cria_Nodo();
    novo->compromisso = compromisso;
    novo->prox = *N;
    *N = novo;
}
void insere_ordenado_lista(Nodo **N, Compromisso compromisso){
    Nodo *novo, *aux1, *aux2;
    novo = Cria_Nodo();
    novo->compromisso = compromisso;
    if(*N == NULL) {
        novo->prox = NULL;
        *N=novo;
    }
    else {
        if( compara_datas( compromisso.data_compromisso, ( *N )->compromisso.data_compromisso ) < 0 )
            insere_inicio_lista(N, compromisso);
        else {
            for(aux1=*N; aux1->prox != NULL; aux1 = aux1->prox) {
                aux2 = aux1->prox;
                if( dado_esta_entre_os_nos( compromisso, aux1, aux2 ) ) {
                    aux1->prox = novo;
                    novo->prox = aux2;
                    break;
                }
            }
            if(aux1->prox == NULL)
                insere_fim_lista(N, compromisso);
        }
    }
}

int remove_inicio_lista(Nodo **N, char *dado [80]) {
    Nodo *aux;
    if(*N == NULL)
        return 0;
    else {
        *dado = (*N)->compromisso.descricao;
        aux = (*N)->prox;
        free(*N);
        *N = aux;
    }
    return 1;
}

int remove_final_lista(Nodo **N, char *dado[80]) {
    Nodo *aux, *anterior;
    if(*N == NULL)
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

void imprime_lista_ecandeada(Nodo *N) {
    Nodo *aux;
    if(N == NULL)
        printf("\n A lista esta vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox) { 
            printa_compromisso( aux->compromisso );
        }
    }
} 

void salva_compromissos(Nodo **N){
	Nodo *aux;
	FILE *fp;	
	fp = fopen("agenda.dat", "w");
	if(fp == NULL){
		printf("ERRO: arquivo 'agenda.dat' nao existe");
	}
	aux = *N;
	while(aux != NULL) {
		fwrite(&(aux->compromisso), sizeof(Compromisso), 1, fp);
        aux = aux->prox;
    }
	fclose(fp);
}

void le_agenda(Nodo **N){
    int loaded = 0;
	Compromisso compromisso;
	FILE *fp;
	fp = fopen("agenda.dat", "r");
	if(fp == NULL){
		printf("ERRO: arquivo 'agenda.dat' nao existe\n");
	}
	// printf("comecando a ler\n");
	while(fread(&compromisso, sizeof(Compromisso), 1, fp)){
		insere_ordenado_lista(N, compromisso);
        // printf("inserindo\n");
        loaded++;
    };
    printf("Carregando %d compromissos.\n", loaded);
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
    char * found;
    int found_counter = 0;

    if(N == NULL)
        printf("\n A lista estÃ¡ vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox) { 
            found = strstr( aux->compromisso.descricao, pesquisa ); /* should return 0x18 */
            int index = found - aux->compromisso.descricao;          /* index is 8 */
            printf( "\n -----> %d\n", index );
            if( index > -1 ) {
                
                printa_compromisso( aux->compromisso );
                found_counter++;
            }
        }
    }

    if( found_counter == 0 ){
        printf("\nNenhum compromisso encontrado.\n");
    }
}

void cancelar_compromisso( Nodo ** N, char pesquisa [80]  ) {
    
    Nodo *aux;
    char * found;
    int found_counter = 0;

    if(N == NULL)
        printf("\n A lista estÃ¡ vazia!!");
    else {
        for(aux = *N; aux != NULL; aux = aux->prox) { 
            found = strstr( aux->compromisso.descricao, pesquisa ); /* should return 0x18 */
            int index = found - aux->compromisso.descricao;          /* index is 8 */
            printf( "\n -----> %d\n", index );
            if( index > -1 ) {
                strcpy( aux->compromisso.descricao, "Compromisso cancelado" );
                found_counter++;
            }
        }
    }

    if( found_counter == 0 ){
        printf("\nNenhum compromisso encontrado.\n");
    }

    else {
        printf("\n%d Compromissos cancelados\n", found_counter);
    }
}


int main(){
    Nodo *MyList = NULL;
    Compromisso novo_compromisso;
    char pesquisa[80];
    int menu, valor;
    int choice;
    FILE *fp;
    inicializa_lista(&MyList);
    le_agenda(&MyList);

    do {
        printf("\n1. Novo compromisso");
        printf("\n2. Cancelar compromisso");
        printf("\n3. Listar compromissos");
        printf("\n4. Salva na agenda.dat");
        // printf("\n5. Le a agenda.dat");
        printf("\n6. Pesquisar por compromisso");
        printf("\n5. sair\n");
        scanf("%d%*c", &menu);
        switch(menu) {
            case 1:
                novo_compromisso = le_dados();
                insere_ordenado_lista( &MyList, novo_compromisso );
                break;
            case 2:
                // Fazer funcao para cancelar compromisso

                printf("Pesquise o compromisso:");
                scanf ("%[^\n]%*c", pesquisa);
                cancelar_compromisso( &MyList, pesquisa );
                break;
            case 3:
                imprime_lista_ecandeada(MyList);
				break;
			case 4:
				salva_compromissos(&MyList);
				break;
			// case 5:
			// 	le_agenda(&MyList);
			// 	break;
            case 5:
                printf("\n\n\nSaindo do programa!");
                break;
            case 6: 
                printf("Pesquise o compromisso:");
                scanf ("%[^\n]%*c", pesquisa);
                buscar_compromisso( MyList, pesquisa );
                break;
            default:
                printf("\nOpcao Invalida!!!");
        }
    } while(menu != 5);
    return 0;
}
