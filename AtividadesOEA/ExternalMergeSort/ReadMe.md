O external merge sort serve para fazermos ordenação externa em uma hipótese de que um arquivo não cabe todo em memória. Então resolvemos essa falta de memória quebrando o arquivo em n partes, ordenando cada uma delas e, por fim utilizamos o código intercala para ordernarmos cada uma das partes, de duas em duas partes, até q reste apenas um arquivo, que é o arquivo inicial, mas ordenado. Neste exemplo eu quebro o arquivo cep-AC.dat, que veio do arquivo cep.dat, em 4 partes, ordeno-as utilizando o a função qsort() e, termino intercalando todas as partes, duas a duas, até que seja gerado um arquivo final, o arquivo cep-AC.dat, porém ordenado.  

Comandos, no terminal, para execução:   

gcc -o extMerS extMerS.c    

./extMerS

Obs: quem usar SO Windows deverá instalar o Cygwin64, MSYS2 ou MinGW-w64 para dar os comandos.
