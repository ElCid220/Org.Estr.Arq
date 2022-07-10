No código ordena1.c, lemos uma lista de endereços, salvamo-os em um buffer e ordenamos esse buffer. Após ordenação em ordem crscente, um novo arquivo é aberto para a ordenação ser escrita nele.
&nbsp;
No código ordena2.c, vamos dividir a lista de endereços em duas metades. Depois, vamos ordenar a 1° metade, usando a comparação entre cep, em seguida escreveremos a ordenação em um arquivo. Agora ordenamos segunda metade usando a comparação por meio de cep, e concluímos escrevendo a ordenação em outro arquivo. 
&nbsp;

Observação: usamos a função qsort() para efetuar a ordenação.