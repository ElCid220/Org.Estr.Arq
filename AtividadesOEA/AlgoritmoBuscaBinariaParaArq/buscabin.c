#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

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

int main(int argc, char **argv)
{

	FILE *f;

	Endereco e;
	int qt;

	f = fopen("cep_ordenado.dat", "rb");

	fseek(f, 0, SEEK_END);
	long tb = ftell(f);
	long tr = tb / sizeof(Endereco);

	long inicio = 0, fim = tr - 1;
	int cont = 0;


	while (inicio <= fim)
	{
		int meio = (inicio + fim) / 2;

		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		fread(&e, sizeof(Endereco), 1, f);

		int cmp = strncmp(argv[1], e.cep, 8);
		
		if (cmp == 0)
		{
			printf("Achamos. Quantidade: %d\n",cont);
			break;
		}

		if(cmp < 0)
		{
			printf("vou procurar na primeira metade entre %ld e %d\n", inicio, meio-1);
			fim = meio-1;
		}
		else{
			printf("vou buscar entre %d e %ld\n", meio+1, fim);
			inicio = meio +1;
		}
		cont++;
	}

fclose(f);
}