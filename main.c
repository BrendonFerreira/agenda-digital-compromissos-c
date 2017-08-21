#include<stdio.h>
#include<stdlib.h>

#define MAX_VETOR 5

typedef struct Vetor
{
 int dados[MAX_VETOR];
 int inicio, fim;
} Tipo_Lista;

Tipo_Lista lista;

void insertStart(Tipo_Lista *v, int dado){
	if(v -> fim < MAX_VETOR){
  		v -> dados[v -> inicio] = dado;
  		(v -> inicio)++;
  		return 1;
	}
}

void insertEnd(Tipo_Lista *v, int dado){
	if(v -> fim < MAX_VETOR){
  		v -> dados[v -> fim] = dado;
  		(v -> fim)++;
  		return 1;
	}
return 0;
}

void insertOrdered(){
		
}

int excludeStart( Tipo_Lista * v ){
	if(v -> fim < MAX_VETOR){
  		v -> dados[v -> inicio] = 'NULL';
  		(v -> inicio)++;
  		return 1;
    }
    return 0;
}

int excludeEnd(  Tipo_Lista * v  ){
	if(v -> fim < MAX_VETOR){
  		v -> dados[v -> fim] = 'NULL';
  		(v -> fim)++;
  		return 1;
    }
    return 0;
}



void excludeSpecific(Tipo_Lista * v, int indice){
  int i, dado;
  if (v -> fim != 0) //verifica se a lista está vazia
  {
    if ((indice >= 0) && (indice < v -> fim)) //verifica se o indice está correto
    {
      if (indice == 0) //verifica se exclui o primeiro elemento
      {
        if (excludeStart(&v) == 1)
          printf("\nO elemento excluido da posicao %d foi: %d", indice, dado);
        return 1;
      } else {
        if (indice == v -> fim - 1) //verifica se exclui o ultimo elemento
        {
          if (excludeEnd(&v) == 1)
            printf("\nO elemento excluido da posicao %d foi: %d", indice, dado);
          return 1;
        } else {
          dado = v -> dados[indice];
          for (i = indice; i < v -> fim; i++)
            v -> dados[i] = v -> dados[i + 1];
          (v -> fim) --;
          printf("\nO elemento excluido da posicao %d foi: %d", indice, dado);
          return 1;
        }
      }
    }
    return -1;
  }
  return 0;
}

void search(Tipo_Lista v, int dado, int * indice){
  	int i, achou = 0;
  	for (i = 0; i < v.fim - 1; i++) {
    	if (v.dados[i] == dado) { 
			* indice = i;
      		achou = 1;
      		break;
    	}
	}
  	if (achou){
    	return 1;
	}
  	return 0;
}

void print(Tipo_Lista V){
	int i;
	printf("\n\n\n");
	if (V.fim != 0) {
	  for (i = 0; i < V.fim; i++)
	    printf("\n%d", V.dados[i]);
		return 1;
	  }
	  return 0;
}

int main(){
	int option;
	printf("Escolha que operação deseja realizar:\n1.Inserir no inicio\n2.Inserir no fim\n3.Inserir ordenado (no meio)\n4.Remover do inicio\n5.Remover do fim\n6.Remover especifico\n7.Buscar\n8.Imprimir lista\n0.Sair");
	scanf("%d", &option);
	switch(option){
		case(1):
			//insertStart(  );
		break;
		case(2):
			//insertEnd();
		break;
		case(3):
			//insertOrdered();
		break;
		case(4):
			excludeStart( &lista );
		break;
		case(5):
			excludeEnd( &lista );
		break;
		case(6):
			//removeSpecific();
		break;
		case(7):
			//search( lista );
		break;
		case(8):
			lista.inicio = 0;
			lista.fim = 0;
			print(lista);
		break;
		default:
			printf("goin' now");
		break;	
	}
	return 0;
}