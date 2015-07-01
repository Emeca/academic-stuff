#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PCB 69
#define LST 93
#define BOX 32
#define SCD 27

#define TERMINOU 80
#define IO 81

struct pcb
{
	char nome;
	int chegada;
	int cpu_tempo;
	int es_intervalo;
	int es_tempo;
	int cont;
};

struct pcb_box
{
	struct pcb_box *ant;		// nao utilizado
	struct pcb *proc;			// processo
	struct pcb_box *prox;		// proximo elemento da lista
};

struct lst
{
	int n;						// numero de elementos na lista
	struct pcb_box *head;		// ponteiro p/ inicio da lista
	struct pcb_box *fim;		// ponteiro p/ o ultimo elemento da lista
};

struct scd
{
	struct lst *processos;
	struct lst *pronto;
	struct lst *io;
	struct lst *finalizados;
	struct pcb *exec;
	struct pcb *io_exec;
	FILE *output;
};

// aloca uma struct conforma a constante passada
void *
make(int tipo)
{
	struct pcb_box *pbox = NULL;
	struct pcb *proc = NULL;
	struct lst *lista = NULL;
	struct scd *sched = NULL;

	switch (tipo) {
	case (LST):
		lista = (struct lst *)malloc(sizeof(struct lst));
		lista->head = NULL;
		lista->fim = NULL;
		lista->n = 0;
		return (void *)lista;
	case (PCB):
		proc = (struct pcb *)malloc(sizeof(struct pcb));
		proc->nome = 'a';
		//proc->nome = NULL;
		proc->chegada = 0;
		proc->cpu_tempo = 0;
		proc->es_intervalo = 0;
		proc->es_tempo = 0;
		proc->cont = 0;
		return (void *)proc;
	case (BOX):
		pbox = (struct pcb_box *)malloc(sizeof(struct pcb_box));
		pbox->ant = NULL;
		pbox->prox = NULL;
		pbox->proc = NULL;
		return (void *)pbox;
	case (SCD):
		sched = (struct scd *)malloc(sizeof(struct scd));
		sched->pronto = NULL;
		sched->io = NULL;
		sched->processos = NULL;
		sched->finalizados = NULL;
		sched->exec = NULL;
		sched->io_exec = NULL;
		sched->output = stdout;
		return (void *)sched;
	}
	return NULL;
}

// imprime as informacoes de um processo
void
processo_imprime(struct pcb *processo)
{
	if (processo) {
		printf("%c ", processo->nome);
		printf("%d ", processo->chegada);
		printf("%d ", processo->cpu_tempo);
		printf("%d ", processo->es_intervalo);
		printf("%d\n", processo->es_tempo);
	} else {
		printf("%s\n", "processo_imprime: processa nao alocado");
		exit(0);
	}
}

// carrega um processo do arquivo pro pcb
struct pcb *
processo_load(FILE * arquivo)
{
	struct pcb *processo = (struct pcb *)make(PCB);
	if (arquivo) {
		if (processo) {
			if (!feof(arquivo)) {
				fscanf(arquivo, "%c", &processo->nome);
				fscanf(arquivo, "%i", &processo->chegada);
				fscanf(arquivo, "%i", &processo->cpu_tempo);
				fscanf(arquivo, "%i", &processo->es_intervalo);
				fscanf(arquivo, "%i\n", &processo->es_tempo);

				// fscanf(arquivo,"%i",&processo->es_tempo);
				// fgetc(arquivo);
			}
		} else {
			printf("%s\n", "oops: falha ao alocar pcb");
			exit(0);
		}
	} else {
		printf("%s\n", "falha ao acessar o FILE*");
		exit(0);
	}
	return processo;
}

// adiciona um processo a uma lista de processos
void
lista_add_fim(struct lst *lista, struct pcb *proc)
{
	struct pcb_box *pbox = (struct pcb_box *)make(BOX);
	pbox->proc = proc;

	// lista vazia
	if (!lista->head) {
		lista->head = pbox;
		lista->fim = pbox;
	} else {
		lista->fim->prox = pbox;
		lista->fim = pbox;
	}
	lista->n++;
}

// carrega um arquivo de processos para uma lista de processo
struct lst *
lista_load(char *nome_do_arquivo)
{
	FILE *arquivo = fopen(nome_do_arquivo, "r");
	struct lst *lista = (struct lst *)make(LST);
	struct pcb *proc_aux = NULL;

	if (arquivo) {
		if (lista) {
			while (!feof(arquivo)) {
				proc_aux = processo_load(arquivo);
				lista_add_fim(lista, proc_aux);
				lista->n++;
			}
		} else {
			printf("%s\n", "oops: falha ao alocar lista");
			exit(0);
		}
	} else {
		printf("%s%s\n", "falha ao abrir o arquivo: ", nome_do_arquivo);
		exit(0);
	}
	fclose(arquivo);
	return lista;
}

void
lista_print(struct lst *lista)
{
	struct pcb_box *pbox;
	if (lista) {
		pbox = lista->head;
		while (pbox) {
			processo_imprime(pbox->proc);
			pbox = pbox->prox;
		}
	}
}

void
lista_free(struct lst *lista)
{
	if (lista) {
		while (lista->head) {
			lista->fim = lista->head;
			lista->head = lista->fim->prox;
			free(lista->fim);
		}
		lista->head = NULL;
		lista->fim = NULL;
		lista->n = 0;
	}
}

struct pcb_box *
copy_pbox(struct pcb_box *original)
{
	struct pcb_box *destino = (struct pcb_box *)make(BOX);
	struct pcb *proc = (struct pcb *)make(PCB);

	proc->nome = original->proc->nome;
	proc->chegada = original->proc->chegada;
	proc->cpu_tempo = original->proc->cpu_tempo;
	proc->es_tempo = original->proc->es_tempo;
	proc->es_intervalo = original->proc->es_intervalo;
	proc->cont = original->proc->cont;
	destino->ant = original->ant;
	destino->prox = original->prox;
	destino->proc = proc;
	return destino;
}

struct pcb *
copy_pcb(struct pcb *original)
{
	struct pcb *destino = (struct pcb *)make(PCB);

	destino->nome = original->nome;
	destino->chegada = original->chegada;
	destino->cpu_tempo = original->cpu_tempo;
	destino->es_tempo = original->es_tempo;
	destino->es_intervalo = original->es_intervalo;
	destino->cont = original->cont;
	return destino;
}

void
processos_que_chegam(struct lst *pronto, struct lst *proc, int instante)
{
	struct pcb_box *pbox = proc->head;

	while (pbox) {
		if (instante == pbox->proc->chegada) {
			pbox->proc->chegada = 0;
			lista_add_fim(pronto, copy_pcb(pbox->proc));
		}
		pbox = pbox->prox;
	}
}

void
proc_print(struct pcb *proc, FILE * output)
{
	if (proc) {
		fprintf(output, "%c[%i;%i]", proc->nome, proc->cpu_tempo, proc->cont);
	} else {
		fprintf(output, "%s", "[null]");
	}
}

void
tela_print_lista(struct pcb_box *pbox, FILE * output)
{
	int i;
	struct pcb *proc = NULL;
	if (pbox) {
		for (i = 0; i < 4; i++) {
			proc = pbox->proc;
			proc_print(proc, output);
			fprintf(output, "-");
			pbox = pbox->prox;
			if (!pbox)
				break;
		}
	} else
		fprintf(output, "%s", "===========[null]===========");
}

void
sched_print(struct scd *sched, int instante)
{
	fprintf(sched->output, "[%i]\r\t", instante);
	tela_print_lista(sched->pronto->head, sched->output);
	fprintf(sched->output, "\r\t\t\t\t\t");
	proc_print(sched->exec, sched->output);
	fprintf(sched->output, "\r\t\t\t\t\t\t");
	tela_print_lista(sched->io->head, sched->output);
	fprintf(sched->output, "\r\t\t\t\t\t\t\t\t\t\t");
	proc_print(sched->io_exec, sched->output);
	fprintf(sched->output, "\r\t\t\t\t\t\t\t\t\t\t\t");
	tela_print_lista(sched->finalizados->head, sched->output);
	fprintf(sched->output, "\n");

//  usleep(3000000);
}

struct pcb *
lista_getfirst(struct lst *lista)
{
	struct pcb_box *pbox = lista->head;
	struct pcb *proc = NULL;;

	if (pbox) {
		proc = pbox->proc;
		lista->head = pbox->prox;
		if (!lista->head)
			lista->fim = NULL;
		proc = copy_pcb(pbox->proc);
		free(pbox);
		lista->n--;
		return proc;
	}
	return NULL;
}

void
gerencia_io(struct scd *sched)
{
	if (sched->io_exec) {
		sched->io_exec->cont--;
		if (sched->io_exec->cont == 0) {
			sched->io_exec->chegada = 0;
			if (sched->exec) {
				lista_add_fim(sched->pronto, sched->io_exec);
			} else {
				sched->exec = sched->io_exec;
			}
			sched->io_exec = NULL;
			if (sched->io->n != 0) {
				sched->io_exec = lista_getfirst(sched->io);
				if (sched->io_exec->cont == 0)
					sched->io_exec->cont = sched->io_exec->es_tempo;
			}
		}
	} else {
		if (sched->io->n != 0) {
			sched->io_exec = lista_getfirst(sched->io);
			if (sched->io_exec->cont == 0)
				sched->io_exec->cont = sched->io_exec->es_tempo;
		}
	}
}

void
espera_io(struct scd *sched, int *instante)
{
	if (sched->io) {
		while (!sched->exec) {
			sched_print(sched, (*instante)++);
			gerencia_io(sched);

			// if (!sched->exec) sched->exec = lista_getfirst(sched->pronto);
			// se nao tiver nada em io tenta pega na fila de pronto
			// if (sched->exec) break;
		}
	} else
		fprintf(sched->output, "\noops: kernel panic\n");
}

void
escalonador(struct scd *sched)
{
	int instante = 0;
	int i;
	int flag = 0;				//acende se ocorrer i/o

	// ligando o escalonador, estado 0   
	processos_que_chegam(sched->pronto, sched->processos, instante);
	sched_print(sched, instante++);

	// enquanto nao for executados todos os processos
	while (sched->finalizados->n < sched->processos->n) {

		// carregando primeiro processo da fila de pronto
		sched->exec = lista_getfirst(sched->pronto);
		if (!sched->exec)
			espera_io(sched, &instante);	//cpu ociosa aguardando i/o

		// dando timeslice de 3ms para o processo
		i = 0;
		flag = 0;
		while ((i < 3) && (flag == 0)) {
			sched_print(sched, instante++);
			sched->exec->chegada++;
			sched->exec->cpu_tempo--;
			if (sched->exec->cpu_tempo == 0)
				flag = TERMINOU;
			else				// processo termina e preempta
			if ((sched->exec->es_intervalo != 0)
					&& (sched->exec->es_intervalo == sched->exec->chegada))
				flag = IO;		// IO

			// tratando tb io
			gerencia_io(sched);
			i++;
		}

		switch (flag) {			// ocorreu interrupcao
		case (TERMINOU):
			lista_add_fim(sched->finalizados, sched->exec);
			sched->finalizados->n++;
			sched->exec = NULL;
			break;
		case (IO):
			if (sched->io_exec) {
				lista_add_fim(sched->io, sched->exec);
			} else {
				sched->io_exec = sched->exec;
				if (sched->io_exec->cont == 0)
					sched->io_exec->cont = sched->io_exec->es_tempo;
			}
			sched->exec = NULL;
			break;
		}
		if (i == 3) {
			if (flag == 0)
				lista_add_fim(sched->pronto, sched->exec);
			sched->exec = NULL;
		}
	}
	sched_print(sched, instante++);
	printf("%s\n", "todos os processos foram escalonados");
}

int
main(void)
{
	struct scd *sched;
	sched = (struct scd *)make(SCD);
	sched->finalizados = (struct lst *)make(LST);
	sched->pronto = (struct lst *)make(LST);
	sched->io = (struct lst *)make(LST);

	sched->processos = lista_load("in.txt");

	// sched->processos = lista_load("dados.txt");
	// sched->output = fopen("c:\\merc\\output.txt","w");
	// sched->output = fopen("output.txt","w");
	escalonador(sched);

	// fprintf(sched->output,"%s\n","maravilha alberto");
	lista_print(sched->processos);
	fclose(sched->output);
	lista_free(sched->processos);
	lista_free(sched->finalizados);
	lista_free(sched->pronto);
	lista_free(sched->io);
	free(sched->exec);
	free(sched->io_exec);
	free(sched);
	return 0;
}
