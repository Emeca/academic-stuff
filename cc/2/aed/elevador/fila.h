/* vim: set ts=4 sw=4: */

#ifndef _FILA_H
#define _FILA_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define ANDARES 5
#define N_ELEVADORES 3
#define CHEGAM 3

#define SUBIR 1
#define DESCER 0

#define TRUE 1
#define FALSE 0


typedef struct paciente
{
	unsigned char estado;
	unsigned int tempo_espera;

} paciente;

typedef struct box
{
	struct box *ant;
	paciente p;
	struct box *prox;

} box;

typedef struct fila
{
	box *ini;
	box *efim;
	box *nfim;
	int tam;
	int obito;
	int max;
	int e;
	int e_cont;

} fila;

typedef struct andar
{
	fila F;
	int usuarios;
	int espera_total;

} andar;

typedef struct elevador
{
	int bloqueado;
	int andar;

} elevador;

typedef struct prioridade
{
	int andar;
	int tempo_espera;

} prioridade;

typedef struct hospital
{
	andar A[ANDARES];
	elevador E[N_ELEVADORES];
	prioridade P[N_ELEVADORES];

} hospital;

/* retorna um novo paciente em um determinado estado */
box *novo_paciente(char estado);

/* insere na fila um paciente */
int chega_paciente(fila *F, char c);

/* insere uma box na fila apartir de nfim */
void insere_nfim(fila *F, char c);

/* insere uma box na fila apartir de efim */
void insere_efim(fila *F, char c);

/* imprime na tela a fila */
void print_fila(fila *F);

/* imprime na tela a fila de traz pra frente */
void print_fila_contrario(fila *F);

/* imprime na tela a fila (prioridade) */
void print_fila_prioridade(fila *F);

/* inicializa a fila com os devidos valores */
void inicia_fila(fila *F);

/*
 * insere novas pessoas na fila randomicamente de 0..CHEGAM,
 * retorna a quantia de pessoas que chegaram
 */
int atualiza_fila(fila *F);

/*
 * diminui a fila em n elementos e atuliza dados estatisticos (usuarios e
 * espera_total)
 */
void diminui_fila(hospital * H, int andar, int n);

/* retorna o tamanho da fila de um determinado andar  */
int fila_tam(hospital * H, int andar);

/* incrementa tempo_espera de todos os nos da fila */
void incrementa_tempo_de_espera(fila *F);

/* retorna true se pode ser uma emergencia, false se naum poder */
int eh_emergencia(fila *F);

/* retorna treu se o andar pode sobrer emergencias (andar 0 ou 4) */
int andar_emergencial(fila *F);

#endif
