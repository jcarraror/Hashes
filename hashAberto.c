//FUNÇÃO HASH UTILIZADA: DIVISÃO

/**---------------ESTRATEGIA PARA RESOLVER O PROBLEMA------------------**/
//                                                                      //
//  -> ESTABELECER UM PADRÃO PARA O NUMERO DE MATRICULA                 //
//  -> UTILIZAR A FUNÇÃO HASH DE DIVISÃO                                //
//     * A POSIÇÃO DO ALUNO NA TABELA HASH SERÁ "matricula mod TAM"     //
//  -> EM CASO DE COLISÃO, O NOVO ELEMENTO SERÁ O PRIMEIRO NA LISTA     //
//     ENCADEADA CONTIDA NA POSIÇÃO h DA TABELA HASH                    //
//                                                                      //
/**--------------------------------------------------------------------**/

/**------------------------SUGESTÕES DE TESTE---------------------------**/
//                                                                       //
// Por estratégia, realizei a programação estabelecendo um intervalo     //
// para o numero de matrícula a ser informado pelo usuário. Dessa forma, //
// a matrícula informada deve estar contida no intervalo de 100 a 999,   // 
// caso se queira ampliar o intervalo será necessário modificar a        //
// constante TAM.                                                        //
//                                                                       //
// Note que para obter colisões será necessário informar matrículas que  //
// contenham os mesmos dois últimos números. Em outras palavras, os      //
// alunos de matriculas 115, 215, 315, 415... resultarão em colisão na   //
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

/****************FUNÇÃO DE BUSCA DE ALUNOS NA TABELA DE HASH****************/
Aluno* busca(Hash tab, int mat)
{
/*---------------h RECEBE RESTO DA DIVISÃO DE mat POR 100---------------*/
    int h = hash(mat);

    //variável que vai percorrer os nodos das lista encadeadas da tabela hash
    Aluno* node = tab[h];

/*---ENQUANTO O ALUNO NÃO FOR ENCONTRADO E node->prox NÃO FOR NULL...---*/
    while (node != NULL)
    {
        //Se o aluno foi encontrado...
        if(node->mat == mat)
        {
            imprimeBusca(node);
            return node;
        }

        /*Se o aluno ainda não foi encontrado, partimos
          para o próximo nodo da lista*/
        node = node->prox;
    }

    if(node==NULL)
        printf("\n*****O aluno de matricula %d ainda nao foi registrado.*****\n", mat);

    return NULL;
}

/****************FUNÇÃO DE INSERÇÃO DE ALUNOS NA TABELA DE HASH****************/
Aluno* insere(Hash tab, int mat, char* nome, char* email)
{
/*----------h RECEBE RESTO DA DIVISÃO DE mat POR 100---------*/
    int h = hash(mat);

/*----------------NODO PARA O ALUNO--------------------------*/
    //Aloca espaço na memória
    Aluno* node = (Aluno*) malloc(sizeof(Aluno));

    /*preenche os atributos da struct com o que foi informado
      pelo usuário*/
    node->mat = mat;
    strcpy(node->email, email);
    strcpy(node->nome, nome);

/*---------POSICIONANDO O NODO NA TABELA DE HASH-------------*/
    //se a tabela de hash ainda não tem alunos no índice h...
    if(tab[h]==NULL)
    {
        //O índice h da tabela de hash recebe o novo aluno
        tab[h] = node;
        //O prox do novo aluno aponta para NULL, pois não tem mais elementos na lista
        node->prox = NULL;
    }
    else{ //Caso contrário, se já tem aluno no índice h...
        //O prox do novo aluno recebe o que era a cabeça da lista até então
        node->prox = tab[h];

        /*O novo aluno passa a ser a nova cabeça da lista, ou seja,
          é o primeiro elemento na lista encadeada do índice h da tabela de hash*/
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

