Conjuntos como listas encadeadas
Uma das maneiras possíveis de implementar um conjunto é como uma lista encadeada dos elementos dele. Há diversas outras formas, como vetores dos elementos, vetores de bits para marcação dos elementos, tabelas de hashing, etc. A escolha por uma implementação ou outra vai depender das operações que se pretende realizar e da freqüência delas. A escolha neste trabalho é puramente didática, não técnica.

Neste trabalho deverão ser implementados conjuntos de inteiros e algumas operações sobre eles. Seu programa deve ser capaz de operar até 128 conjuntos simultaneamente.

Entrada
Cada linha da entrada contém um comando como descrito a seguir.
c i
Criar o conjunto i vazio. Se o programa já estiver operando um conjuto de nome i então ele deve ser liberado da memória e um novo conjunto vazio deve ser criado.
i j t x1 ... xt
Inserir os elementos x1, ..., xt no conjunto j. Se algum elemento a inserir já estiver no conjunto j então ele deve ser ignorado.
r j t x1 ... xt
Remover os elementos x1, ..., xt do conjunto j. Se algum elemento a remover não estiver no conjunto j então ele deve ser ignorado.
u i j k
Atribuir ao conjunto i a união dos conjuntos j e k.
n i j k
Atribuir ao conjunto i a interseção dos conjuntos j e k.
m i j k
Atribuir ao conjunto i a diferença dos conjuntos j e k (i = j - k).
e i x
Imprimir "x esta em Ci" ou "x nao esta em Ci" em uma única linha, como ilustrado abaixo.
p i
Imprimir os elementos do conjuntoci em ordem crescente e em uma única linha, como ilustrado abaixo.
t
Terminar. Antes de terminar, o programa deve liberar a memória ocupada pelos conjuntos.
Antes de algum comando i, r, p ou e envolvendo o conjunto j sempre haverá algum comando c, u, n ou m que criou j. Os nomes de conjuntos sempre serão um inteiro entre 0 e 127.
Saída
A saída deve conter o resultado dos comandos para testar existência e para imprimir.

Exemplos
Entrada 1:
c 1
i 1 4 7 1 5 4  
c 2
i 2 4 8 2 5 4
n 4 1 2
p 4
u 4 1 2
p 4
m 4 1 2
p 4
m 4 2 1
p 4
r 1 4 2 1 7 5
e 2 1
p 1
c 4
p 4
t
Saida 1:
C4 = {4, 5}
C4 = {1, 2, 4, 5, 7, 8}
C4 = {1, 7}
C4 = {2, 8}
1 nao esta em C2
C1 = {4}
C4 = {}
Requisitos adicionais
Cada conjunto deve ser representado como uma lista encadeada.
Não pode haver qualquer variável global. Uma variável é global se estiver declarada fora de alguma função (variáveis declaradas dentro da main não são globais, são locais à função main).
