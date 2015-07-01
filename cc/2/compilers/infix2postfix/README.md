Trabalho de compiladores - 17/10/2005


Alunos:
	Rodrigo Renie
	Eder Ruiz Maria


Para compilar, apenas digite "make". Você deve ter o flex, bison e gcc instalados
no computador para compilar corretamente.

Para executar o programa, crie um arquivo de entrada (ou use o input.txt existente)
e execute:

	./calc < input.txt

O arquivo de entrada deve estar contendo expressões matemáticas no formato infix, e o 
programa irá gerar o equivalente no formato posfix (da calculadora polonesa reversa).

Se deseja que a saída seja colocado em um arquivo, faça:

	./calc < input.txt > output.txt

O resultado será armazenado em output.txt.
