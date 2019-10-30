//Prova Estrutura de dados 1
//Keven Lucas Paiva de Paula

#include "stdlib.h"
#include "stdio.h"
#include "windows.h"
#include "locale.h"

void definirIdioma(){
 // Definir o idioma usado pelo programa
 setlocale(LC_ALL, "Portuguese");
}

//Definindo a estrutura: Dado, apontador
typedef struct elemento{
	int dado;
	struct elemento *prox;
} TElemento;

//criando a estrutura da lista de elementos contendo o apontador inicio e final
typedef struct lista{
  int nroElementos;
  TElemento *inicio;
  TElemento *final;
} TLista;

//criando a lista
TLista *criarLista(){
  TLista *lista = malloc(sizeof(TLista));
  lista->nroElementos = 0;
  lista->inicio=NULL;
  lista->final = NULL;
  return lista;
}

//procedimento limpar tela
void cls(){
	system("cls");	
}

void imprimirLista(TLista *lista){
  int contador=0;

	if(lista->inicio == NULL){
		printf("\n\tLista Vazia!\n");
	} else {
		TElemento *caminhador = lista->inicio;
		printf("\n");
		while(caminhador != NULL){
			printf("\t[%d] - %d\n",contador, caminhador->dado);
      contador++;
			caminhador = caminhador->prox;
		}
	}

}

//verificar se o elemento existe na lista, retorna 1(sim) ou 0 (não)
int verificaExistente(TLista *lista, int elemento){
  TElemento *caminhador = lista->inicio;
  while(caminhador != NULL){
    if(caminhador->dado == elemento){
      return 1;
    }
    caminhador = caminhador->prox;
  }
  return 0;
}

//insere elemento no inicio da lista
void inserirInicio(TLista *lst, TElemento *e_novo){
  // lista vazia
  if (lst->inicio == NULL){
    lst->inicio = e_novo;
    lst->final = e_novo;
    e_novo->prox = NULL;
    lst->nroElementos = 1;
  }else{
    // trocar o inicio da Lista pelo  novo elemento, e faz esse novo elemento apontar para o antigo inicio da lista
    e_novo->prox = lst->inicio; //importante fazer essa relacao primeiro para nao perder o endereco do inicio da lista que vai ser atualizado
    lst->inicio = e_novo;
    lst->nroElementos++;
  }
}

// inserir no final
void inserirFinal(TLista *lst, TElemento *e_novo){
  // se lista vazia, inicio e final da lista apontam para esse novo elemento que vai ser inserido, que aponta para nulo
  if (lst->inicio == NULL){
    lst->inicio = e_novo;
    lst->final = e_novo;
    e_novo->prox = NULL;
    lst->nroElementos = 1;
  }else{ //se lista nao está vazia, inserir no final é simples,
    lst->final->prox=e_novo;
    lst->final = e_novo;
    e_novo->prox = NULL;
    lst->nroElementos++;
  }
}

//Função Incluir recebe como parametros uma lista e o novo elemento.
void incluir(TLista *lista, TElemento *novo_elem){
	TElemento *atual, *anterior;
	anterior = NULL;
	atual = lista->inicio;

      //verificar se a lista esta vazia
      if(lista->inicio == NULL){
        inserirInicio(lista, novo_elem);
      }
      //insere no inicio: se o valor do elemento atual for menor que o elemento do inicio da lista
      else if(novo_elem->dado < lista->inicio->dado){
        novo_elem->prox = lista->inicio; //insere o valor antes do valor que ja existia
        lista->inicio = novo_elem; //o inicio da lista passa a ser o valor inserido
        lista->nroElementos++;
      }

      //inserir no final: se o valor do elemento atual for maior que o ultimo elemento da lista
      else if (novo_elem->dado > lista->final->dado) {
        inserirFinal(lista,novo_elem); //adiciona o elemento no final da lista
      }

      //inserir no meio: se o valor for maior que o inicio da lista, e menor que o final
      else if ((novo_elem->dado > lista->inicio->dado) && (novo_elem->dado < lista->final->dado)) {

          //enquanto o atual for diferente de Nulo e o dado do elemento atual for menor que o dado do novo elemento
          while ((atual!=NULL) && (atual->dado < novo_elem->dado)){
          anterior = atual;
          atual = atual->prox;
        }

      //novo elemento aponta para o caminhador atual
      novo_elem->prox = atual;
      //caminhador anterior aponta para o novo elemento
      anterior->prox = novo_elem;
      //atualiza o numero de elementos da lista
      lista->nroElementos++;
	  }
}

void pesquisa(TLista *lista, int elemento){
  int resp;
  resp = verificaExistente(lista, elemento);
  if (resp)
    printf("\n\tElemento existe na lista!");
  else
    printf("\n\telemento nao existe na lista!");
}

//apagar toda lista
void removerInicio(TLista *lst) {
  if(lst->inicio != NULL) {
    TElemento *prim = lst->inicio;
    TElemento *novoInicio = prim->prox;
    free(prim);
    lst->inicio = novoInicio;
    lst->nroElementos--;
    if(lst->inicio == NULL) lst->final = NULL;
  }
}

void removerFinal(TLista *lst){
  TElemento *caminhador = lst->inicio;
  //int achou = 0;
  if (lst->inicio == NULL){
    printf("\n\tLista Vazia\n");
  }else if (lst->inicio == lst->final){
      free(lst->inicio);
      lst->inicio = NULL;
      lst->final = NULL;
  }else{
    while (caminhador->prox != lst->final){
      caminhador = caminhador->prox;
    }
    caminhador->prox=NULL;
    free(lst->final);
    lst->final = caminhador;
    }
}

void removerElemento(TLista *lista, int valor){
  TElemento *anterior= lista->inicio;
  TElemento *atual = lista->inicio;
  TElemento *final = lista->final;
  
  if(atual->dado == valor){
  	removerInicio(lista);
  }else if(final->dado == valor){
  	removerFinal(lista);
  }else{
	  while(atual->dado!=valor){
	    anterior=atual;
	    atual=atual->prox;
	  }
	  anterior->prox = atual->prox;
	  free(atual);
	}	
}



//alterar elemento
int alterar(TLista *lista, int elemento, int novo_valor){
	TElemento *novoElemento = malloc(sizeof(TElemento));
 	novoElemento->dado = novo_valor;
	int flag=verificaExistente(lista,elemento);
	
	if (flag){
		removerElemento(lista, elemento);
		incluir(lista, novoElemento);
		}
	else
		printf("\n\tEste valor não está presente na lista! ");
		
	return flag;
}


//Função apagarLista interpreta a lista como uma fila, e vai removendo o inicio da lista até o inicio apontar para nulo.
void apagarLista(TLista *lista){
	TElemento *inicio = lista->inicio;
	
	if (lista->inicio==NULL)
		printf("\n\tLista inexistente\n");
	else{
		while(inicio!=NULL){
    		removerInicio(lista);
    		inicio = inicio->prox;
    }
	printf("\n\tLista apagada\n");
  }
}

void leitura(TLista *lista){
	
	TElemento *entrada = malloc(sizeof(TElemento));
  	int valor, flag,inseriu=0;
	
	while (inseriu!=1){
		scanf("%d",&(entrada->dado));
  		valor = entrada->dado;

		flag = verificaExistente(lista, valor);
	
    	if(!flag){
   		 	incluir(lista,entrada); //insere ordenado na lista
   		 	cls();
    		printf("\n\tElemento incluído a lista.\n\n\tAperte Enter para continuar...");
			inseriu=1;
    	}else{
    		cls();
    		printf("\n\tElemento já existe na lista!\n\tInsira outro: ");
		}
}
	getch();
	}

//mostrar monitor principal
void monitorPrincipal(){
	printf("\t---------------------MENU---------------------\n\n");
	printf("\t	[1] incluir item na lista\n");
	printf("\t	[2] mostrar lista\n");
	printf("\t	[3] alterar item da lista\n");
	printf("\t	[4] remover item da lista\n");
	printf("\t	[5] pesquisa item na lista\n");
	printf("\t	[6] apagar lista\n");
	printf("\t	[7] apagar lista e sair\n\n");
	printf("\t----------------------------------------------\n");
}


int main(){
	//cria a lista inicialmente vazia
	TLista *lista = criarLista(); 
	//definindo o idioma
	definirIdioma();
	
	//variavel de controle de opções
    int continuar=1;
    //flag verifiadora para leitura
    int flag=0;
    int procura, anterior, valor, lixo, verificacao, numExistente, verificarLixo;

    do{
    	cls();
        monitorPrincipal();
        printf("\n\tEscolha uma opção: ");
        scanf("%d", &continuar);
        cls();

        switch(continuar)
        {
            case 1:
            	//insere um item na lista
                printf("\n\tDigite um número para inserir a lista: ");
                leitura(lista);
                
                break;

            case 2:
            	
            	//imprime a lista
                imprimirLista(lista);
                
				printf("\n\tDigite qualquer tecla para continuar... ");
				getch();
                
				break;

            case 3:
            	
            	//verifica se a lista está vazia
            	if (lista->inicio==NULL){
            		printf("\n\tA Lista está vazia!");
					printf("\n\n\tAperte qualquer tecla para continuar...");
                	getch();
					break;
				}
            	
            	//imprimindo a lista pra localizar a posição a ser alterada          	
                imprimirLista(lista);
                
                
                // lendo a posição que será alterada e escolhendo o novo valor a ser inserido na lista
                printf("\n\t insira o valor a ser alterado: ");
                scanf("%d", &anterior);
                printf("\n\t Digite o novo valor: ");
                scanf("%d", &valor);
                
                //numExistente: verificar se o elemento existe na lista atual
                numExistente=verificaExistente(lista,valor);
                
                if (numExistente){
                	cls();
                	printf("\n\tElemento já existe na lista! ");
                	printf("\n\n\tAperte qualquer tecla para continuar...");
                	getch();
					break;
				}
                
                //mostrando lista atual
                cls();
                imprimirLista(lista);
                
                //verificacao: verifica se o valor foi ou não alterado
                verificacao=alterar(lista, anterior, valor);
				
				//se a verificacao retornar 1 significa que o valor foi alterado entao deve mostrar a lista atual
                if (verificacao){
				printf("\n\tPosição alterada\n");
				imprimirLista(lista);
				}
				
				printf("\n\tAperte qualquer tecla para continuar...");
                getch();
				break;
				
			case 4:
				
				//verifica se a lista está vazia
				if (lista->inicio==NULL){
            		printf("\n\tA Lista está vazia!");
					printf("\n\n\tAperte qualquer tecla para continuar...");
                	getch();
					break;
				}
				
				//imprime a lista e recebe a varivel para ser removida
				imprimirLista(lista);
				printf("\n\tDigite o valor a ser removido: ");
				scanf("%d", &lixo);
				
				//verifica se o elemento a ser removido existe ou não na lista
				verificarLixo=verificaExistente(lista, lixo);
				
				if (!verificarLixo){
					printf("\n\tElemento não existe na lista! ");
					printf("\n\tAperte qualquer tecla para continuar...");
                	getch();
					break;
				}
				
				//remove o elemento
				removerElemento(lista, lixo);
				printf("\n\tElemento removido com sucesso!\n");
				
				//mostra a lista atual
				imprimirLista(lista);
				printf("\n\tAperte qualquer tecla para continuar...");
                getch();				
				break;
				
			case 5: 
				//verifica se a lista está vazia
				if (lista->inicio==NULL){
            		printf("\n\tA Lista está vazia!");
					printf("\n\n\tAperte qualquer tecla para continuar...");
                	getch();
					break;
				}
				
				//pesquisa se o elemento existe ou não na lista
				printf("\n\tDigite um valor para pesquisar: ");
				scanf("%d", &procura);
				pesquisa(lista,procura);
				
				printf("\n\n\tAperte qualquer tecla para continuar...");
                getch();
				break;
				
            case 6:
            	//apaga a lista e volta ao menu principal
                apagarLista(lista);
                
                printf("\n\tAperte qualquer tecla para continuar...");
                getch();
                break;
            
            case 7:
            	//apagar a lista e finaliza o programa
            	apagarLista(lista);
            	return 0;

            default:
            	//mensagem de erro e volta ao menu principal
                printf("\n\tDigite uma opcao valida\n");
                printf("\n\tAperte qualquer tecla para continuar...");
                getch();
        }
    } while(continuar);
}
