#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno {
 int mat;
 char nome[81];
 char email[41];
};
typedef struct aluno Aluno;

#define N 10
typedef Aluno* Hash[N];


int hash (int mat)
{
 return (mat%N);
}

Aluno* busca (Hash tab, int mat)
{
 int h = hash(mat);
 while (tab[h] != NULL) {
	 if (tab[h]->mat == mat)
	 	return tab[h];
	 h = (h+1) % N;
 }
 return NULL;
}

Aluno* insere (Hash tab, int mat, char nome[], char email[])
{
 int h = hash(mat);
 while (tab[h] != NULL) {
	 if (tab[h]->mat == mat)
	 	break;
 	h = (h+1) % N;
 }
 if (tab[h]==NULL) { /* não encontrou o elemento */
 	tab[h] = (Aluno*) malloc(sizeof(Aluno));
 	tab[h]->mat = mat;
 }
 /* atribui informação */
 strcpy(tab[h]->nome,nome);
 strcpy(tab[h]->email,email);
 return tab[h];
}

int menu(){
	int opcao;
	printf("\n1 - Inserir Aluno\n");
	printf("2 - Buscar Aluno\n");
	printf("0 - Sair\n");
	scanf("%i",&opcao);
	return(opcao);
}


int main(){
	int opcao, mat, i;
	Hash tab;
	for (i = 0;i<N;i++)
		tab[i] = NULL;
	Aluno *aux = (Aluno*) malloc(sizeof(Aluno));
	char nome[20], email[20], turma[1];
	do{
		opcao = menu();
//		for (i = 0;i<N;i++)
//			printf("%i \n", tab[i]);
		switch(opcao){
			case 1: printf("Matricula: ");
                    scanf("%d",&mat);
                    printf("Nome: ");
                    scanf("%s",&nome);
                    printf("E-mail: ");
                    scanf("%s",&email);
                    insere(tab,mat,nome,email);
                    break;
			case 2: printf("Matricula: ");
                    scanf("%d",&mat);
					aux = busca(tab, mat);
					if (aux != NULL)
                    	printf("Aluno %s encontrado \n", aux->nome);
					break;
			case 0: exit(1);
    	}
	}while(opcao !=0);
}

