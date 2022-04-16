/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>

#define NTHREADS  2 //total de threads a serem criadas

typedef struct {
   int indexComeco;
   int* vetor;
} t_Args;

//--funcao executada pelas threads
void *elevarAoQuadrado (void *arg) {

  t_Args* argumento = (t_Args *) arg;
  for(int i = argumento->indexComeco; i < 1000; i += 3){
    argumento->vetor[i] = pow(argumento->vetor[i], 2);
  }
  free(arg); //aqui pode liberar a alocacao feita na main
  pthread_exit(NULL);
}

//--funcao principal do programa
int main(void) {
  pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
  int thread; //variavel auxiliar
  int vetor[1000];
  t_Args* argumento;
  for(int i = 0; i < 1000; i++){ //apenas para que tenhamos uma forma fácil de analisar
    vetor[i] = i; 
  }
  for(thread=0; thread<NTHREADS; thread++) {
    argumento = malloc(sizeof(t_Args));
    argumento->vetor = vetor;
    argumento->indexComeco = thread + 1;
    if (pthread_create(&tid_sistema[thread], NULL, elevarAoQuadrado, (void *)argumento)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  for(int i = 0; i < 1000; i += 3){
    argumento->vetor[i] = pow(argumento->vetor[i], 2);;
  }
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }
  for(int i = 0; i < 1000; i++){ 
    printf("%d\n", vetor[i]); 
  }
  printf("--Thread principal terminou\n");

  pthread_exit(NULL);
}
