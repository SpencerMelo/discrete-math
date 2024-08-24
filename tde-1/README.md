# TDE-1

## Description
Solution for set problems written in C, I did choose to not implement a hashtable to solve, it's not part of the C class. <br />
My solution is an implementation of singly linked list for elements of the set, with this I don't need to limit the amount <br />
of elements accepted per each set using an array with size defined at compile time. <br />

The solution avoids duplication on each set while reading the file, for both sets, for example, '1,2,1,3' will result in {1,2,3}. <br />
I did choose to read each character alone, so I don't need to set buffersize, I though the 'fgets' would perform many syscalls  <br />
which could result in performance problems, but it's not true, fgets already works on top of a buffer. <br />

## Problem statement:
> O programa que você desenvolverá irá receber como entrada um arquivo de texto (.txt)
contendo vários conjuntos de dados e várias operações. Estas operações e dados estarão representadas
em um arquivo de textos contendo apenas os dados referentes as operações que devem ser realizadas
segundo a seguinte regra fixa: a primeira linha do arquivo de texto de entrada conterá o número de
operações que estão descritas no arquivo, este número de operações será um inteiro; as linhas
seguintes seguirão sempre o mesmo padrão de três linhas: a primeira linha apresenta o código da
operação (U para união, I para interseção, D para diferença e C produto cartesiano), a segunda e
terceira linhas conterão os elementos dos conjuntos separados por virgulas.

## Constraints:
- Each element length cannot be more than 64 char long (will cause a crash), I choosed this limit.
- There is NO constraint on the amount of elements for each line.
- There is NO limit on the amount of operations per file (U, I, D, C)
- The solution does NOT preserve order.
- The solution does NOT allow repeated elements on the same set.
- The solution does NOT allow repeated elements on resolutions.

## How to run:
- You must have a '.txt' file in the same directory with the executable (or you must provide a full file path)
- All your test cases must be on the '.txt' file
- The file must have the pattern mentioned on the 'valid example' section
- You should provide the file name when running, see command bellow.
- There are 3 test case files, you can select each one to run by the name.

```sh
gcc -o runnable solution.c && ./runnable "test-cases-1.txt"
```

## Valid example:
```
2
U
1,2,3,A,CD,Computer Science
3,4,5,B,Computer Science
I
A,B,C
a,b,C
```

## Invalid example:
```
1
C
0000000000000000000000000000001,0000000000000000000000000000002
0000000000000000000000000000002,0000000000000000000000000000003
```
