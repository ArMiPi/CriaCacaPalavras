/*
	Nome: Arthur Miasato Pimont
	Data: 04/11/2020
	Descrição: Criar um Caça Palavras 30x40
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<string.h>

const int Linhas = 30;
const int Colunas = 41;
const char* path = "CacaPalavras.txt";

int aleatorio(int n);
char **alocaMatriz(int l, int c);
void preencheRespostas(char **m, int l);
void criaArquivo(char **m);
void inicializaMatriz(char **m);
void preencheCacaPalavras(char **m);
void posicionaRespostas(char **m, char *r);
void posiciona(char **m, char *r, int li, int ci, int mov);
void imprimeMatriz(char **m, int l);
char **liberaMatriz(char **m, int l);

int main()
{
	int n;
	char **R, **CP;
	
	printf("Digite a quantidade de palavras que estarao presentes no caca-palavras: ");
	scanf("%d", &n);
	fflush(stdin);
	
	//Matriz com as palavras que tem que estar no caça-palavras
	R = alocaMatriz(n, 26);
	preencheRespostas(R, n);
	
	//Criação do caça-palavras
	CP = alocaMatriz(Linhas, Colunas);
	srand(time(NULL));
	//Inicializa a Matriz com o caracter 0
	inicializaMatriz(CP);
	
	for(int i = 0; i < n; i++)
		posicionaRespostas(CP, R[i]); //Posiciona as respostas no caça-palavras
	preencheCacaPalavras(CP); //Preenche o restante do caça-palavras com caractres aleatórios
	//imprimeMatriz(CP, Linhas);
	criaArquivo(CP); //Cria um .txt com o caça-palavras
	
	//Liberar as duas matrizes utilizadas
	CP = liberaMatriz(CP, Linhas);
	liberaMatriz(R, n);
}

int aleatorio(int n)
{
	switch(n)
	{
		case 0:
			return 65 + (rand() % 26);
			break;
		case 1:
			return rand() % 30;
			break;
		case 2:
			return rand() % 40;
		case 3:
			return rand() % 8;
	}
}

char **alocaMatriz(int l, int c)
{
	char **m;
	
	m = (char**) malloc(l * sizeof(char *));
	for(int i = 0; i < l; i++)
		m[i] = (char *) malloc(c * sizeof(char));
	
	return m;
}

void preencheRespostas(char **m, int l)
{
	printf("\nEntre com as palavras:\n\n");
	for(int i = 0; i < l; i++)
	{
		printf("#%d: ", i+1);
		fgets(m[i], 25, stdin);
	}
	
	for(int i = 0; i < l; i++)
	{
		for(int j = 0; m[i][j] != '\0'; j++)
			m[i][j] = toupper(m[i][j]);
	}
}

void criaArquivo(char **m)
{
	FILE *ptr = fopen(path, "w");
		for(int i = 0; i < Linhas; i++)
		{
			for(int j = 0; j < Colunas; j++)
			{
				fprintf(ptr, "%c ", m[i][j]);	
			}
			fprintf(ptr, "\n");
		}
	fclose(ptr);
}

void inicializaMatriz(char **m)
{
	for(int i = 0; i < Linhas; i++)
	{
		for(int j = 0; j < Colunas; j++)
		{
			if(j == Colunas - 1)
				m[i][j] = '\0';
			else
				m[i][j] = '0';
		}
	}
}

void preencheCacaPalavras(char **m)
{
	for(int i = 0; i < Linhas; i++)
	{
		for(int j = 0; j < Colunas; j++)
		{
			if(m[i][j] == '0')
				m[i][j] = aleatorio(0);
		}
	}
}

void posicionaRespostas(char **m, char *r)
{
	int l, c, mov, aux = 0, temp, tam;
	
	while(aux == 0)
	{
		l = aleatorio(1);
		c = aleatorio(2);
		
		if(m[l][c] == '0' || m[l][c] == r[0])
			aux++;
	}
	
	aux = 0;
	tam = strlen(r) - 1;
	
	while(aux == 0)
	{
		mov = aleatorio(3);
		temp = 0;
		
		switch(mov)
		{
			case 0: //NO
				if(l - tam >= -1 && c - tam >= -1)
				{
					for(int i = l, j = c, k = 0; k < tam; i--, j--, k++)
					{
						if(m[i][j] !='0' && m[i][j] != r[k])
						{
							temp++;
							break;
						}
					}
					if(temp == 0)
					{
						posiciona(m, r, l, c, mov);
						aux++;
					}
				}
				break;
			case 1: //N
				if(l - tam >= -1)
				{
					for(int i = l, k = 0; k < tam; i--, k++)
					{
						if(m[i][c] != '0' && m[i][c] != r[k])
						{
							temp++;
							break;
						}
					}
					if(temp == 0)
					{
						posiciona(m, r, l, c, mov);
						aux++;	
					}
				}
				break;
			case 2: //ND
				if(l - tam >= -1 && c + tam < Colunas)
				{
					for(int i = l, j = c, k = 0; k < tam; i--, j++, k++)
					{
						if(m[i][j] !='0' && m[i][j] != r[k])
						{
							temp++;
							break;
						}
					}
					if(temp == 0)
					{
						posiciona(m, r, l, c, mov);
						aux++;
					}
				}
				break;
			case 3: //O
				if(c - tam >= -1)
				{
					for(int j = c, k = 0; k < tam; j--, k++)
					{
						if(m[l][j] != '0' && m[l][j] != r[k])
						{
							temp++;
							break;
						}
						if(temp == 0)
						{
							posiciona(m, r, l, c, mov);
							aux++;
						}
					}
				}
				break;
			case 4: //L
				if(c + tam < Colunas)
				{
					for(int j = c, k = 0; k < tam; j++, k++)
					{
						if(m[l][j] != '0' && m[l][j] != r[k])
						{
							temp++;
							break;
						}
						if(temp == 0)
						{
							posiciona(m, r, l, c, mov);
							aux++;
						}
					}
				}
				break;
			case 5: //SO
				if(l + tam <= Linhas && c - tam >= -1)
				{
					for(int i = l, j = c, k = 0; k < tam; i++, j--, k++)
					{
						if(m[i][j] != '0' && m[i][j] != r[k])
						{
							temp++;
							break;
						}
						if(temp == 0)
						{
							posiciona(m, r, l, c, mov);
							aux++;
						}
					}
				}
				break;
			case 6: //S
				if(l + tam <= Linhas)
				{
					for(int i = l, k = 0; k < tam; i++, k++)
					{
						if(m[i][c] != '0' && m[i][c] != r[k])
						{
							temp++;
							break;
						}
						if(temp == 0)
						{
							posiciona(m, r, l, c, mov);
							aux++;
						}
					}
				}
				break;
			case 7: //SD
				if(l + tam <= Linhas && c + tam < Colunas)
				{
					for(int i = l, j = c, k = 0; k < tam; i++, j++, k++)
					{
						if(m[i][j] != '0' && m[i][j] != r[k])
						{
							temp++;
							break;
						}
						if(temp == 0)
						{
							posiciona(m, r, l, c, mov);
							aux++;
						}
					}
				}
				break;
		}
	}
	
}

void posiciona(char **m, char *r, int li, int ci, int mov)
{
	int tam = strlen(r) - 1;
	
	switch(mov)
	{
		case 0: //NO
			for(int i = li, j = ci, k = 0; k < tam; i--, j--, k++)
				m[i][j] = r[k];
			break;
		case 1: //N
			for(int i = li, k = 0; k < tam; i--, k++)
				m[i][ci] = r[k];
			break;
		case 2: //ND
			for(int i = li, j = ci, k = 0; k < tam; i--, j++, k++)
				m[i][j] = r[k];
			break;
		case 3: //O
			for(int j = ci, k = 0; k < tam; j--, k++)
				m[li][j] = r[k];
			break;
		case 4: //L
			for(int j = ci, k = 0; k < tam; j++, k++)
				m[li][j] = r[k];
			break;
		case 5: //SO
			for(int i = li, j = ci, k = 0; k < tam; i++, j--, k++)
				m[i][j] = r[k];
			break;
		case 6: //S
			for(int i = li, k = 0; k < tam; i++, k++)
				m[i][ci] = r[k];
			break;
		case 7: //SD
			for(int i = li, j = ci, k = 0; k < tam; i++, j++, k++)
				m[i][j] = r[k];
			break;
	}
}

void imprimeMatriz(char **m, int l)
{
	printf("\n\n");
	for(int i = 0; i < l; i++)
	{
		for(int j = 0; m[i][j] != '\0'; j++)
			printf("%c ", m[i][j]);
		printf("\n");
	}
}

char **liberaMatriz(char **m, int l)
{
	for(int i = 0; i < l; i++)
		free(m[i]);
	free(m);
	
	return NULL;
}
