Hospital Originale de La Assuncion (HOLA)
=========================================

Requisitos
----------

- Linux
- Terminal com 48 linhas e 128 colunas
	
Funcionamento
-------------

Este programa simula o funcionamente dos elevadores (3) de um hospital com
andares (5), embora a representação seja espancivel.

A quantidade de ciclos de tempo que durará a simulação pode ser passado
como parametro pela linha de comando, o default é 10 ciclos.

O atendimento aos pacientes pelos elevadores é feito conforme uma prioridade,
onde o elevador E1 atende o paciente que esta a mais tempo na fila, o E2 o que
segundo esta a mais tempo na fila, assim como o EM atende o que esta em
terceiro lugar nessa classificação.

A cada ciclo os elevadores retiram no maximo 4 pessoas de cada andar, também
chegam de 0 a 3 pessoas nos andares, nos andares 0 e 4 chegam também
emergencias.

Ao final dos ciclos é exibido um relatório com estatisticas do uso dos
elevadores.

Autores
-------

- Eder Ruiz Maria
- Wilson Yudi
