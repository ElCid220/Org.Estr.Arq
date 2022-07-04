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
	char lixo[2]; // Ao EspaÃ§o no final da linha + quebra de linha
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char **argv)
{
	FILE *a, *b, *saida1, *saida2, *saida3, *saida4, *fim;
	Endereco ea, eb, ec, ed;
	int proxnome = 4, proxint = 0;
	long tam, qtd, qtdmemb, q0, q1, qq, q2, q3;
	char nomearq[10], nomearq2[10], proxNome[10];

	a = fopen("cep-AC.dat", "rb");
    fseek(a, 0, SEEK_END);
	tam = ftell(a);
	qtd = tam/4;
	qtdmemb = qtd / sizeof(Endereco) ;
	q0 = qtd;
	q1 = (tam / 2) - q0 ;
	qq = tam - (tam /2);
	q2 = qq /2 ;
	q3 = qq - q2 ;

    rewind(a);

	fread(&ea, sizeof(Endereco), q0, a);
	qsort(&ea, q0, sizeof(Endereco), compara);
    saida1 = fopen("arq0.dat", "wb");
	fwrite(&ea ,sizeof(Endereco), q0, saida1);
     
	fread(&eb, sizeof(Endereco), q1, a);
	qsort(&eb, q1, sizeof(Endereco), compara);
    saida2 = fopen("arq1.dat", "wb");
	fwrite(&eb ,sizeof(Endereco), q1, saida2);

    fread(&ec, sizeof(Endereco), q2, a); 
	qsort(&ec, q2, sizeof(Endereco), compara);
    saida3 = fopen("arq2.dat", "wb");
	fwrite(&ec ,sizeof(Endereco), q2, saida3);
    
	fread(&ed, sizeof(Endereco), q3, a);
	qsort(&ed, q3, sizeof(Endereco), compara);
    saida4 = fopen("arq3.dat", "wb");
	fwrite(&ed ,sizeof(Endereco), q3, saida4);

	fclose(a);

	//sprintf('nomearq', 'arq%d.dat', i);
	
	while (proxnome - proxint > 1)
	{   
		sprintf('nomearq', 'arq%d.dat', proxint);
		sprintf('nomearq2', 'arq%d.dat', (proxint+1));
		sprintf('proxNome', 'arq%d.dat', proxnome);
        a = fopen("nomearq", "rb");
        b = fopen("nomearq2", "rb"); 
		fim = fopen("proxNome", "wb");
        
		while (!feof(a) && !feof(fim))
		{
			if (compara(&ea, &eb) < 0)
			{
				fwrite(&ea, sizeof(Endereco), 1, fim);
				fread(&ea, sizeof(Endereco), 1, a);
			}
			else
			{
				fwrite(&eb, sizeof(Endereco), 1, fim);
				fread(&eb, sizeof(Endereco), 1, b);
			}
		}

		while (!feof(a))
		{
			fwrite(&ea, sizeof(Endereco), 1, fim);
			fread(&ea, sizeof(Endereco), 1, a);
		}
		while (!feof(fim))
		{
			fwrite(&eb, sizeof(Endereco), 1, fim);
			fread(&eb, sizeof(Endereco), 1, b);
		}
		remove(a);
		remove(b);

		proxint+=2;
		proxnome++;
	}

	fclose(fim);
}
