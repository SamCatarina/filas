/**** INÍCIO do Código ****/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Operações de Pilha **/
#define STACK_MAX_SIZE 100   // tamanho máximo da pilha

typedef struct stack Stack;  // tipo abstrato Pilha
typedef char elm_t;           // tipo de elemento da pilha

struct stack {
  int top;
  elm_t data[STACK_MAX_SIZE];
};

Stack *stk_alloc();                  // aloca, inicializa e retorna um ponteiro para um novo objeto Pilha
void stk_free(Stack *stk);           // desaloca o objeto Pilha stk alocado com stk_alloc
bool stk_isempty(Stack *stk);        // retorna true se a pilha stk estiver vazia, e false caso contrário
bool stk_isfull(Stack *stk);         // retorna false se a pilha stk estiver cheia, e false caso contrário
void stk_push(Stack *stk, elm_t i);  // empilha o elemento i na pilha stk
elm_t stk_pop(Stack *stk);           // remove e retorna o elemento do topo da pilha stk
elm_t stk_top(Stack *stk);           // retorna o elemento do topo da pilha stk, sem removê-lo
void imprimir(Stack *stk);



// Questão 1
// implemente AQUI a solução da questão 1
// comente a sua implementação!

bool exp_formatada(char exp[]){

	Stack *p = stk_alloc(); //cria a pilha 
	int cont = 0;
	bool inverter = true;

	if(exp[0] == '\0'){
		return false; //se a pilha estiver vazia, retorna false
	}

	while (exp[cont] != '\0'){ //percorre ate o ultimo elemento da expressão
		
		if (exp[cont] == 'c'){ //se encontrar um 'c', o inverter fica falso
			inverter = false;
			cont++; //para pular o caracter 'c'
		}
		
		if(inverter){
			stk_push(p, exp[cont]); //se o caracter não for 'c', ele adiciona na pilha.
		}else{
			if (exp[cont] == stk_top(p) && (exp[cont] == 'a' || exp[cont] == 'b')){
				stk_pop(p); //verifica se o caracter é igual ao que está no topo da pilha e se ele é 'a' ou 'b'
			}else{
				return false;
			}
		}
		cont++;
	}
	
	
	return stk_isempty(p); //se a pilha estiver vazia nesse momento do código, então a expressão está correta
	
	
}



// Questão 2
// implemente AQUI a solução da questão 2
// comente a sua implementação!

bool varias_exp_formatada(char exp[]){

	int cont = 0; //contador para a exp recebida
	int cont2 = 0; //cont para a expressao auxiliar
	char exp_part[100] = ""; //exp auxiliar

	while (exp[cont] != '\0'){ //percorre a exp recebida
		if (exp[cont] == 'd'){ //se encontrar um caracter 'd', a função da primeira questão é chamada com a exp auxiliar como parametro
			bool resul_parcial = exp_formatada(exp_part);
			if (resul_parcial == false){
				return false; 
			}
			cont2 = 0; //cont da exp auxiliar volta a ser zero
			for(int i = 0; exp_part[i] != '\0'; i++){
				exp_part[i] = '\0'; //"apago" todos os elementos da exp auxiliar
			}
			
		}else{
			exp_part[cont2] = exp[cont]; //se não encontrar um 'd', ele adc na exp auxiliar 
			cont2++;
		}	
		cont++;
	}
	bool resul_parcial = exp_formatada(exp_part); //a função da primeira questão é chamada pela ultima vez para a ultima expressao apos o último 'd'
			if (resul_parcial == false){
				return false; 
			}
	return true;

	
}

/** Operações de Fila Versão 1 **/
#define QUEUE_MAX_SIZE 100     // tamanho máximo da fila
typedef struct queueV1 QueueV1; // tipo abstrato Fila
typedef int elm_tp;              // tipo de elemento da fila

struct queueV1{
	int rear;
	elm_tp data[QUEUE_MAX_SIZE];
};


QueueV1 *queuev1_alloc();                       // aloca, inicializa e retorna um ponteiro para um novo objeto Fila
void queuev1_free( QueueV1 *queue  );            // desaloca o objeto Fila queue alocado com queue_alloc
bool queuev1_isempty( QueueV1 *queue  );         // retorna true se a fila queue estiver vazia, e false caso contrário
bool queuev1_isfull( QueueV1 *queue  );          // retorna false se a fila queue estiver cheia, e false caso contrário
void queuev1_insert( QueueV1 *queue  , elm_tp i); // insere o elemento i no final da fila queue
elm_tp queuev1_remove(QueueV1 *queue);           // remove e retorna o elemento do início da fila queue

// Questão 3
// implemente AQUI as operações da questão 3
// comente a sua implementação!

QueueV1 *queuev1_alloc(){

	QueueV1 *fi;
	fi = (QueueV1 *) malloc(sizeof(struct queueV1)); 
	fi->rear = -1;

	return fi;
	
};

void queuev1_free( QueueV1 *queue  ){
	free(queue);
};

bool queuev1_isempty( QueueV1 *queue  ){
	if(queue->rear == -1){
		return true;
	}
	return false;
};


bool queuev1_isfull( QueueV1 *queue  ){
	if(queue->rear == QUEUE_MAX_SIZE -1){
		return true;
	}
	return false;
};


void queuev1_insert( QueueV1 *queue, elm_tp i){
	if(!queuev1_isfull(queue)){
		queue->rear++;
		queue->data[queue->rear] = i;
	}
	
	
};

elm_tp queuev1_remove(QueueV1 *queue){
	if (!queuev1_isempty(queue)){ //antes de remover, verifica se a fila está vazia
		elm_tp aux = queue->data[0];
		for(int i = 0; i<queue->rear; i++){ //todos os elementos descem um index na fila sempre que um elemento é removido
			queue->data[i] = queue->data[i+1];
		}
		queue->rear--;
		return aux; //retorna o valor removido
		
	}
	return NULL;
	
};

void queuev1_imprimir(QueueV1 *q){
	for(int i = 0; i<=q->rear; i++){
		printf(" %d ", q->data[i]);
	}
}



/** Operações de Fila Versão 2 **/
typedef struct queueV2 QueueV2; // tipo abstrato Fila
typedef int elm_tp2;              // tipo de elemento da fila

struct queueV2{
	int front;
	int rear;
	elm_tp2 data[QUEUE_MAX_SIZE];
};

QueueV2 *queuev2_alloc();                       // aloca, inicializa e retorna um ponteiro para um novo objeto Fila
void queuev2_free( QueueV2 *queue  );            // desaloca o objeto Fila queue alocado com queue_alloc
bool queuev2_isempty( QueueV2 *queue  );         // retorna true se a fila queue estiver vazia, e false caso contrário
bool queuev2_isfull( QueueV2 *queue  );          // retorna false se a fila queue estiver cheia, e false caso contrário
void queuev2_insert( QueueV2 *queue  , elm_tp2 i); // insere o elemento i no final da fila queue
elm_tp2 queuev2_remove(QueueV2 *queue);           // remove e retorna o elemento do início da fila queue
void queuev2_imprimir(QueueV2 *q);


// Questão 4
// implemente AQUI as operações da questão 3
// comente a sua implementação!

QueueV2 *queuev2_alloc(){

	QueueV2 *fi;
	fi = (QueueV2 *) malloc(sizeof(struct queueV2)); 
	fi->rear = -1;
	fi->front = -1;

	return fi;
	
};

void queuev2_free( QueueV2 *queue  ){
	free(queue);
};

bool queuev2_isempty( QueueV2 *queue  ){
	return queue->rear<0;
};

bool queuev2_isfull( QueueV2 *queue  ){
	if(queue->rear == QUEUE_MAX_SIZE -1 && (queue->rear - queue->front == 0)){ //a fila só estará vazia se o rear estiver no máximo e a diferença entre o rear e o front seja igual a zero, ou seja, não há mais espaço disponivel antes do front.
		return true;
	}
	return false;
};

void queuev2_insert( QueueV2 *queue  , elm_tp2 i){
	if(queuev2_isfull(queue)){ //se a fila estiver no maximo (rear no maximo), os elementos descem os index e o front fica 0.
		for(int c = 0; c<=(queue->rear - queue->front); c++){
			queue->data[c] = queue->data[queue->front + c];
		}
		queue->front = 0;
	}
	queue->rear++;
	queue->data[queue->rear] = i;
	
};

elm_tp2 queuev2_remove(QueueV2 *queue){

	queue->front++;
	elm_tp2 aux = queue->data[queue->front -1];
	return aux;
	
};

void queuev2_imprimir(QueueV2 *q){

	for(int i = q->front+1; i<=q->rear; i++){
		printf(" %d ", q->data[i]);
	}
	
};





/** Programa Principal **/
int main(int argc, char *argv[])
{

	
	
	

  // Teste da Questão 1
  // imprima a pilha de testes antes e depois da execução da operação
  // comente o seu teste! Teste os casos excepcionais!
	printf("\n\n\t\tQUESTÃO 1");
	char algo[] = "abcba";
	
	if(exp_formatada(algo)){
		printf("\n\nA expressão [ %s ] é do tipo x'c'y.", algo);
	}else{
		printf("\n\nA expressão [ %s ] não é do tipo x'c'y.", algo);
	}
	

	

  // Teste da Questão 2
  // imprima a pilha de testes antes e depois da execução da operação
  // comente o seu teste! Teste os casos excepcionais!
	printf("\n\n\t\tQUESTÃO 2");
	

	char expp[] = "abcbadabcbadabcba";

	if(varias_exp_formatada(expp)){
		printf("\n\nA expressão [ %s ] é do tipo x'd'y.", expp);
	}else{
		printf("\n\nA expressão [ %s ] não é do tipo x'd'y.", expp);
	}


  
  // Teste da Questão 3
  // imprima a fila de testes antes e depois da execução das operações
  // comente o seu teste! Teste os casos excepcionais!
	printf("\n\n\t\tQUESTÃO 3");
	

	QueueV1 *q = queuev1_alloc();

	queuev1_insert(q, 1);
	queuev1_insert(q, 2);
	queuev1_insert(q, 3);
	queuev1_insert(q, 4);
	printf("\n\nA fila original: [ ");
	queuev1_imprimir(q);
	printf(" ]");

	queuev1_remove(q);
	printf("\nPrimeiro elemento da fila removido: [ ");
	queuev1_imprimir(q);
	printf(" ]");
	
	
  
  // Teste da Questão 4
  // imprima a fila de testes antes e depois da execução das operações
  // comente o seu teste! Teste os casos excepcionais!
	printf("\n\n\t\tQUESTÃO 4");
	

	QueueV2 *q2 = queuev2_alloc();

	queuev2_insert(q2, 1);
	queuev2_insert(q2, 2);
	queuev2_insert(q2, 3);
	queuev2_insert(q2, 4);
	printf("\n\nA fila original: [ ");
	queuev2_imprimir(q2);
	printf(" ]");

	queuev2_remove(q2);
	printf("\nPrimeiro elemento da fila removido: [ ");
	queuev2_imprimir(q2);
	printf(" ]");

	
  
  return EXIT_SUCCESS;
}

/** Implementação das Operações de Pilha **/
// implemente AQUI as estruturas e operações de Pilha definidas acima.

Stack *stk_alloc() {
  Stack *stk = (Stack *)malloc(sizeof(
      struct stack)); // usa o malloc para fazer a alocação da pilha na memoria
                      // heap, com uma tamanho de um "struct stack"
  stk->top =
      -1; // inicializa o topo da pilha como "-1", para indicar pilha vazia

  return stk; // retorna a pilha
};

void stk_free(Stack *stk) {
  free(stk); // desaloca a pilha da memoria
};

bool stk_isempty(Stack *stk) {
  if (stk->top == -1) { // verifica se o topo da pilha é "-1", ou seja, se está
                        // vazia. Se sim, retorna true, se não, retorna false.
    return true;
  } else {
    return false;
  }
};

bool stk_isfull(Stack *stk) {
  if (stk->top == STACK_MAX_SIZE -
                      1) { // verifica se o topo da pilha, que guarda a
                           // quantidade de elementos, é igual ao tamanho
                           // máximo, se sim, retorna true, se não retorna false
    return true;
  } else {
    return false;
  }
};

void stk_push(Stack *stk, elm_t i) {
  stk->top++; // incrementa o valor do topo
  stk->data[stk->top] =
      i; // adiciona o elemento recebido no parametro no topo da pilha
};

elm_t stk_pop(Stack *stk) {
  // armazeno o valor removido
  elm_t pop = stk->data[stk->top];
  stk->top--; // decremento o valor do topo
  return pop;
}; // remove e retorna o elemento do topo da pilha stk

elm_t stk_top(Stack *stk) {
  // elm_t top = stk_pop(stk);
  // stk_push(stk, top);

  return stk->data[stk->top]; // retorna o elemento que está no topo
};

void imprimir(Stack *stk) { // imprime todos os elementos da pilha
  printf("[ ");
  for (int c = 0; c <= stk->top; c++) {
    printf("%c ", stk->data[c]);
  }
  printf("]\n");
}

