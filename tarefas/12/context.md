**Indexador de documentos**
Suponha um sistema de indexação e controle de documentos para uma órgão do governo, que tem como objetivo registrar metadados de documentos à medida que chegam e realizar consultas a respeito dos documentos.

Suponha que os documentos são grandes e que o sistema vai manter em RAM apenas um índice, que armazena o identificador do documento, a visibilidade do documento e o estado do documento. O documento em si fica em um arquivo em disco, com nome igual ao identificador do documento.

Implemente o índice em C usando uma árvore AVL. Cada nó da árvore armazenará as seguintes informações:

Identificador: um número natural.
Visibilidade: uma string indicando se o documento é restrito, interno, publico ou bloqueado.
Estado: uma string indicando qual a situação do documento, dentre atualizado, desatualizado ou obsoleto.
O sistema não necessita da operação de remoção, apenas de inserção, atualização e consultas.

**Entrada**
A entrada é composta por uma sequência de comandos, um por linha. Cada linha na entrada é da forma:
i x nivel estado
O programa deve inserir um novo documento com identificador x (long), visibilidade nivel e estado estado no índice. Se o identificador x já estiver no índice então a operação deve ser ignorada.

a x nivel estado
O programa deve atualizar o documento com identificador x, modificando sua visibilidade e nível. Se o identificador x não estiver no índice então a operação deve ser ignorada.

b x
O programa deve buscar o documento com identificador x no índice. Se for encontrado, ele deve imprimir uma linha no formato ilustrado abaixo. Caso contrário, deve imprimir x nao existe em uma linha.

l
O progaram debe imprimir os identificadores dos documentos da árvore em ordem crescente em uma única linha separados por espaço. Se o índice estiver vazio, o programa deve imprimir Indice vazio.

t
O programa deve imprimir o número de documentos no índice categorizando por estado, como exemplificado abaixo.

f:
O programa deve terminar.

**Saída**
A saída é composta pela saída das linhas b, p e t.

**Exemplo**
Entrada:
l
i 20 interno obsoleto
i 10 publico atualizado
i 30 restrito desatualizado
l
b 40
b 10
a 30 restrito atualizado
t
f
Saida:
indice vazio
documentos: 10 20 30
40 nao existe
10, publico, atualizado
atualizado: 2, desatualizado: 0, obsoleto: 1
