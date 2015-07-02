- ***Universidade Estadual do Oeste do Paraná***
- ***Ciência da Computação - Sistemas Operacionais***
- ***Professor Shiro - 07/04/2005***

Kerberos
========

Autores
-------
- Andre da Silva Barbosa
- Eder Ruiz Maria
- Rodrigo Renie Braga

Justificativa
=============

Porque faz-se necessário segurança?
-----------------------------------

A segurança das informações faz-se nescessaria devido a varios fatos:

- O atual modelo de comunicação de dados prove um meio de dispersão onde,
analogamente a uma conversa, uma frase emitida é capitada por todos em um
mesmo ambiente e esta frase e passivel de compreenção por todos.

- Há a nescessidade de transmissão de dados que não sejam intendiveis a
todos, algo similar a um cochicho em uma conversa.

- Todas as informações que trafegam no meio estão sujeitas a
interceptação, modificação, interrupção e usurpação.

- Inicialmente com a existência de sistemas distribuidos que faziam uso de
mainframe não existia esse problema, pois a comunicação era diretamente
entre o terminal burro e o mainframe atravéz de porta serial.

- O protocolo de rede utilizado atualmente foi planejado de forma a garantir
a comunicação apenas, e não prove-la de modo seguro.

Segurança
=========

Autenticação
------------

Autenticação é uma verificação da identidade do usuário. Para ser
autenticado, o usuário deve fornecer informações que provem sua identidade.
Essas informações podem estar em uma ou mais dentre três categorias: senhas,
dispositivos físicos ou biometria.

A primeira categoria, senhas, é a mais usada nas autenticações atualmente,
sendo baseada em senhas para garantir o acesso ao sistema. Esta senha pode ser
escolhida pelo próprio usuário ou gerada automaticamente por algum processo
aleatório.

A segunda categoria, dispositivos físicos, é menos comum e mais segura. Como
exemplo desse tipo de autenticação tem-se o smart card, método análogo a
uma chave, de forma que somente quem possuir o cartão terá acesso.

A terceira categoria, biometria, refere-se as características biométricas do
usuário. Partindo-se do princípio que todos os seres humanos possuem
características distintas, podem ser aplicadas medidas biométricas como
requisitos para a autenticação de usuários.

Como exemplo cita-se: impressão digital, verificação da retina e
reconhecimento de voz.

Esses métodos são pouco utilizados, pois ainda não estão maduros o
suficiente para uso intensivo, em função dos altos custos e pela falta de
softwares que suportam os dispositivos necessários.

Autorização
-----------

É responsável pelo gerenciamento de acessos a um recurso que requer a
identição do usuário. Esse processo é executado após a autenticação. A
autorização é usualmente realizada por meio da associação da
identificação do usuário, aplicando-se uma access control list (ACL)
(listas de controle de acesso). Essas listas são compostas por informações
como grupos aos quais o usuário pertence, regras de utilização, e outras
informações que determinam o nivel de acesso que o usuário possui em um
computador ou recurso da rede.

Privacidade
-----------

A privacidade visa ocultar o conte´do de uma mensagem para evitar o acesso
não autorizado de um usuário. Por meio de algoritmos criptográficos, que
são funções matemáticas usadas para cifrar e decifrar dados, é possivel
tornar a informação incompreensivel para entidades não envolvidas na
comunição.
	
Integridade
-----------

Enquanto a criptografia proporciona a privacidade das informações, a
integridade assegura que as mesmas não foram modificadas durante a
transmissão. É comum referenciar os algoritmos que verificam a integridade
da mensagem de funçõees hashes.

O propósito das funções hash é produzir uma "impressão digital" de um
arquivo, mensagem, ou qualquer outro bloco de dados. Em um processo de
autenticação de mensagens.

Kerberos
========

- Cerberos - Guardião do portão do inferno
- Protocolo de Comunicação
- Criado no MIT na década de 80
- Atua como uma terceira parte

Conceitos
---------

### Criptografia Simétrica

O DES - Data Encryption Standard - é um algoritmo de bloco simétrico
desenvolvido pela IBM visando atender a uma solicitação do governo dos EUA e
em nov/76, foi adotado como padrão federal americano (FIPS46 - Federal
Information Processing Standard). Atualmente é o algoritmo mais divulgado e
utilizado em sistemas criptográficos no mercado mundial.

A chave criptográfica DES possui apenas 56 bits; assim sendo, a segurança do
DES é bastante questionada: o algoritmo pode ser quebrado por um ataque de
força bruta pois a chave secreta faz parte de um conjunto de 256 chaves (esse
procedimento levará 2000 anos de execu-ção para descobrir a chave secreta se
considerarmos que uma máquina realizasse uma cripto-grafia DES em 1
microsegundo). Podemos concluir que esse algoritmo poderá não ser apro-priado
para confidencialidade de informações de longa duração (por exemplo para
informações diplomáticas que devem ser mantidas sobre sigilo por mais de 40
anos) mas pode ser to-talmente adequado para proporcionar segurança para
informações confidenciais de curta dura-ção (por exemplo nos dados de uma
aplicação de transferência eletrônica de fundos).

Existe uma técnica de melhorar a segurança do algoritmo DES utilizando uma
criptografia tripla que é conhecida como DES triplo. Nesta técnica cada
mensagem passa por três proces-sos criptográficos que irão reduzir a
possibilidade da segurança ser quebrada através de ata-ques de força bruta.
Isto equivale a, no mínimo, dobrar o tamanho da chave DES para 112 bits.

### Criptografia Assimétrica

O RSA (Rivest, Shamir e Adleman algorithm) é o mais popular algoritmo de chave
pública bem como o mais fácil de compreender e de implementar. Este algoritmo
foi desenvolvido por um grupo de pesquisadores: Ronald Rivest do MIT, Adi
Shamir do Weizmann Institute de Israel e Leonard Adleman da University of
Southern California, sendo patenteado pelo MIT em 1978.

A segurança do RSA está baseada na dificuldade de fatorar grandes números:
as chaves são calculadas matematicamente combinando dois números primos de
grande tamanho. Mesmo se conhecendo o produto desses número primos (que faz
parte da chave pública divulgada), a segurança do algoritmo é garantida pela
complexidade de fatorar esse produto e se obter os valores secretos.

A grande desvantagem do RSA é portanto a lentidão do processo que envolve
exponencia-ção modular (é realizado uma série de multiplicações modulares).

### Ticket Granting Server
	
O TGS é logicamente distinto do AS, mas eles podem residir na mesma maquina. A
função do TGS é a seguinte: antes de acessar qualquer serviço, o usuário
requisita um ticket para contatar o TGS, como se ele fosse um serviço qualquer.
Este ticket é chamado de ticket granting ticket (TGT).

Depois de receber o TGT, a qualquer momento que o usuário desejar requisitar um
serviço, ele irá requerer um ticket não mais do AS, mais sim do TGS. Além disto,
a resposta não será criptografada com a chave secreta do usuário, mas sim com a
chave de sessão providenciada pelo AS para ser usada entre usuário e TGS. O
conteúdo desta resposta é uma chave de sessão que será usada com o serviço
regular.

Funcionamento
-------------

Usuários e serviços que utilizem o Kerberos possuem chaves armazenadas no AS.
As chaves dos usuários são derivadas de senhas escolhidas por estes, e as
chaves dos serviços são geradas aleatoriamente.

Para esta explicação, imaginemos que as mensagens são escritas em papel, e são
criptografadas colocando-as em uma caixa-forte, associada a uma chave.

1. Primeiro o usuário envia uma mensagem ao AS: "Eu, J. Random User, gostaria
de falar com o servidor Foo".

2. Quando o AS recebe a mensagem, ele faz duas cópias de uma nova chave
registrada. Estas chaves são chamadas de chaves de sessão. Elas serão usadas
nas trocas diretas entre serviço e usuário.

3. Ele coloca uma das chaves de sessão na Caixa 1, junto com um pedaço de
papel com o nome "Servidor Foo" escrito. A caixa é trancada com a chave do
usuário (o AS conhece todas as chaves de usuário e todas as chaves de
serviço).

4. Por que este papel aqui? Devemos nos lembra que a caixa é na realidade
apenas uma mensagem criptografada, e que a chave de sessão é uma seqüência
randômica de bytes. Se a Caixa 1 somente contivesse a chave de sessão, o
usuário não teria como reconhecer se a resposta veio do AS, ou não saberia
se a decriptação teve sucesso. Pela adição da mensagem "Servidor Foo", o
usuário (mais precisamente a aplicação do usuário) poderia saber se a caixa
veio do AS, e se a decriptação obteve sucesso.

5. Ele coloca a outra chave de sessão em uma Caixa 2, junto com um pedaço de
papel com o nome "J. Random User". Esta caixa é fechada com a chave do
serviço.

6. Ele envia ambas as caixas ao usuário.

7. Na versão 4 do Kerberos, a Caixa 2 era colocada (sem necessidade) dentro da
caixa 1, mas na versão 5 isto foi corrigido.

8. O usuário destranca a Caixa 1 com sua chave, extraindo assim a chave de
sessão e o papel com o nome "Servidor Foo" escrito nele.

9. O usuário não consegue abrir a Caixa 2 (ela foi trancada com a chave do
serviço, que só o AS e o serviço conhecem). Então ele coloca um pedaço de
papel com a hora corrente numa Caixa 3, e tranca esta com chave de sessão, e
envia ambas ao serviço.

10. O serviço abre a Caixa 2 com sua própria chave, extraindo a chave de
sessão e o papel com "J. Random User" escrito nele. Ele abre a Caixa 3 com a
chave de sessão para extrair o pedaço de papel com a hora corrente nele.
Estes itens demonstram a identidade do usuário. O timestamp é colocado na
Caixa 3 para prevenir que alguém faça uma cópia da Caixa 2 (devemos nos
lembrar que as caixas são na verdade mensagens eletrônicas) e a utilize para
se passar pelo usuário mais tarde. Como os relógios da rede nunca são
perfeitamente sincronizados, uma pequena margem (em geral 5 minutos) é
permitida entre o timestamp e a hora atual. Além disto, o serviço mantém um
lista das autenticações recebidas recentemente para garantir que elas não
foram reenviadas.

A chave de serviço é gerada aleatoriamente e armazenada em um arquivo
especial chamado de SECRETE KEY FILE. O Kerberos assume que este é seguro,
que ninguém pode copiá-lo e se passar pelo serviço.

Considerações
=============

O Kerberos garante
------------------

- Segurança na rede
- Autenticação Mutua
- Centralização de Serviços
- Administração Simples

Problemas do Kerberos
---------------------

- Base de dados das chaves
- Senhas Fracas (amor, sexo, deus)
- Sincronização do Relógio (timestamp)

Bibliografia
============

- TUNG, B. The Moron's Guide to Kerberos. [S.l.], 2005. Disponível em:
<http://gost.isi.edu/brian/security/kerberos.html>. Acesso em: 22 novembro
2005.

- MERLOTTO, W. F. AUTENTICAÇÃO ÚNICA E SEGURA UTILIZANDO KERBEROS E LDAP.
Projeto de Conclusão de Curso (Ciência da Computação) - Universiade Estadual
do Oeste do Paraná, Foz do Iguaçu 2005.
