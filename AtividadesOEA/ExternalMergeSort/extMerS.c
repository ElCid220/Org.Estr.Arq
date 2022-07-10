#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv)
{   
	printf("abelha rainha");
    FILE *a = NULL, *b, *saida1 = NULL, *saida2, *saida3, *saida4, *fim;
	Endereco e0, e1, e2, e3, e4, e5;
	int proxnome = 4, proxint = 0;
	long posicao, metade, qtd, metade1, metade2, metade3, metade4;
	char nomearq[10], nomearq2[10], proxNome[10], entrada[10] = "cep-AC.dat";
	

	a = fopen(entrada, "rb");
	
	fseek(a, 0, SEEK_END);
	posicao = ftell(a);
	qtd = posicao / sizeof(Endereco); // qtd de enderecos
	metade = qtd/2;
	metade1 = metade/2; //1° quarto
    metade2 = metade - metade1; //2° quarto
	metade3 = (qtd - metade)/2; //3° quarto
	metade4 = qtd - metade3; //4° quarto

    rewind(a);
     
	fread(&e0, sizeof(Endereco), metade1, a); 
	qsort(&e0, metade1, sizeof(Endereco), compara); 
    saida1 = fopen("arq0.dat", "wb");
	fwrite(&e0 , sizeof(Endereco), metade1, saida1);
	rewind(saida1);
	fclose(saida1);
	   
	fread(&e1, sizeof(Endereco), metade2, a);
	qsort(&e1, metade2, sizeof(Endereco), compara);
    saida2 = fopen("arq1.dat", "wb");
	fwrite(&e1 ,sizeof(Endereco), metade2, saida2);
	rewind(saida2);
	fclose(saida2);
    
    fread(&e2, sizeof(Endereco), metade3, a); 
	qsort(&e2, metade3, sizeof(Endereco), compara);
    saida3 = fopen("arq2.dat", "wb");
	fwrite(&e2 ,sizeof(Endereco), metade3, saida3);
	rewind(saida3);
	fclose(saida3);
    
	fread(&e3, sizeof(Endereco), metade4, a);
	qsort(&e3, metade4, sizeof(Endereco), compara);
    saida4 = fopen("arq3.dat", "wb");
	fwrite(&e3 ,sizeof(Endereco), metade4, saida4);
	rewind(saida4);
	fclose(saida4);
    
	remove(entrada);
	fclose(a); 
	
     while (proxnome - proxint > 1)
	{   
		sprintf(nomearq, "arq%d.dat", proxint);
		sprintf(nomearq2, "arq%d.dat", (proxint++));
		sprintf(proxNome, "arq%d.dat", proxnome);
        
		a = fopen(nomearq, "rb");
        b = fopen(nomearq2, "rb"); 
		fim = fopen(proxNome, "wb");

		fread(&e4, sizeof(Endereco), 1, a);
		fread(&e5, sizeof(Endereco), 1, b);
        
		while (!feof(a) && !feof(b))
		{
			if (compara(&e4, &e5) < 0)
			{
				fwrite(&e4, sizeof(Endereco), 1, fim);
				fread(&e5, sizeof(Endereco), 1, a);
			}
			else
			{
				fwrite(&e5, sizeof(Endereco), 1, fim);
				fread(&e5, sizeof(Endereco), 1, b);
			}
		}

		while (!feof(a))
		{
			fwrite(&e4, sizeof(Endereco), 1, fim);
			fread(&e4, sizeof(Endereco), 1, a);
		}
		while (!feof(b))
		{
			fwrite(&e5, sizeof(Endereco), 1, fim);
			fread(&e5, sizeof(Endereco), 1, b);
		}
		
		remove(nomearq);
		remove(nomearq2);
		rewind(fim);

		fclose(a);
		fclose(b);
		fclose(fim);

		proxint+=2;
		proxnome++;
	}

	fclose(fim); 
}
