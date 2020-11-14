//FUN��O HASH UTILIZADA: DIVIS�O

/**---------------ESTRATEGIA PARA RESOLVER O PROBLEMA------------------**/
//                                                                      //
//  -> ESTABELECER UM PADR�O PARA O NUMERO DE MATRICULA                 //
//  -> UTILIZAR A FUN��O HASH DE DIVIS�O                                //
//     * A POSI��O DO ALUNO NA TABELA HASH SER� "matricula mod TAM"     //
//  -> EM CASO DE COLIS�O, O NOVO ELEMENTO SER� O PRIMEIRO NA LISTA     //
//     ENCADEADA CONTIDA NA POSI��O h DA TABELA HASH                    //
//                                                                      //
/**--------------------------------------------------------------------**/

/**------------------------SUGEST�ES DE TESTE---------------------------**/
//                                                                       //
// Por estrat�gia, realizei a programa��o estabelecendo um intervalo     //
// para o numero de matr�cula a ser informado pelo usu�rio. Dessa forma, //
// a matr�cula informada deve estar contida no intervalo de 100 a 999,   // 
// caso se queira ampliar o intervalo ser� necess�rio modificar a        //
// constante TAM.                                                        //
//                                                                       //
// Note que para obter colis�es ser� necess�rio informar matr�culas que  //
// contenham os mesmos dois �ltimos n�meros. Em outras palavras, os      //
// alunos de matriculas 115, 215, 315, 415... resultar�o em colis�o na   //
// tabela hash.                                                          //
//                                                                       //
/**--------------------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

typedef struct aluno{
    int mat;
    char nome[40];
    char email[41];
    struct aluno* prox;
}Aluno;

typedef Aluno* Hash[TAM];

int hash(int mat){
    return mat%100;
}

void imprimeBusca(Aluno* aluno)
{
    printf("\n");
    printf("-----------------ALUNO DE MATRICULA %d---------------", aluno->mat);
    printf("\n|  nome: %s", aluno->nome);
    printf("\n|  email: %s\n", aluno->email);
    printf("------------------------------------------------------\n");
}

/****************FUN��O DE BUSCA DE ALUNOS NA TABELA DE HASH****************/
Aluno* busca(Hash tab, int mat)
{
/*---------------h RECEBE RESTO DA DIVIS�O DE mat POR 100---------------*/
    int h = hash(mat);

    //vari�vel que vai percorrer os nodos das lista encadeadas da tabela hash
    Aluno* node = tab[h];

/*---ENQUANTO O ALUNO N�O FOR ENCONTRADO E node->prox N�O FOR NULL...---*/
    while (node != NULL)
    {
        //Se o aluno foi encontrado...
        if(node->mat == mat)
        {
            imprimeBusca(node);
            return node;
        }

        /*Se o aluno ainda n�o foi encontrado, partimos
          para o pr�ximo nodo da lista*/
        node = node->prox;
    }

    if(node==NULL)
        printf("\n*****O aluno de matricula %d ainda nao foi registrado.*****\n", mat);

    return NULL;
}

/****************FUN��O DE INSER��O DE ALUNOS NA TABELA DE HASH****************/
Aluno* insere(Hash tab, int mat, char* nome, char* email)
{
/*----------h RECEBE RESTO DA DIVIS�O DE mat POR 100---------*/
    int h = hash(mat);

/*----------------NODO PARA O ALUNO--------------------------*/
    //Aloca espa�o na mem�ria
    Aluno* node = (Aluno*) malloc(sizeof(Aluno));

    /*preenche os atributos da struct com o que foi informado
      pelo usu�rio*/
    node->mat = mat;
    strcpy(node->email, email);
    strcpy(node->nome, nome);

/*---------POSICIONANDO O NODO NA TABELA DE HASH-------------*/
    //se a tabela de hash ainda n�o tem alunos no �ndice h...
    if(tab[h]==NULL)
    {
        //O �ndice h da tabela de hash recebe o novo aluno
        tab[h] = node;
        //O prox do novo aluno aponta para NULL, pois n�o tem mais elementos na lista
        node->prox = NULL;
    }
    else{ //Caso contr�rio, se j� tem aluno no �ndice h...
        //O prox do novo aluno recebe o que era a cabe�a da lista at� ent�o
        node->prox = tab[h];

        /*O novo aluno passa a ser a nova cabe�a da lista, ou seja,
          � o primeiro elemento na lista encadeada do �ndice h da tabela de hash*/
        tab[h] = node;
    }
}

int menu(){
	int opcao;
	printf("\n1 - Inserir Aluno\n");
	printf("2 - Buscar Aluno por matricula\n");
	printf("0 - Sair\n");
	scanf("%i",&opcao);
	return(opcao);
}

int main(){
    Hash tab;
	int opcao, i;
	Aluno aluno;

	for(i = 0; i < TAM; i++)
        tab[i] = NULL;

	do{
		opcao = menu();

		switch(opcao){
			case 1: printf("Digite o nome do aluno: ");
                    scanf("%s", &(aluno.nome));
                    printf("Digite o email do aluno: ");
                    scanf("%s", &(aluno.email));
                    printf("Digite a matricula do aluno: ");
                    scanf("%i", &(aluno.mat));
                    insere(tab, (aluno.mat), (aluno.nome), (aluno.email));
                    break;
			case 2: printf("Digite a matricula do aluno: ");
                    scanf("%d", &(aluno.mat));
                    busca(tab, aluno.mat);
					break;
			case 0: exit(1);
    	}
	}while(opcao !=0);
}

