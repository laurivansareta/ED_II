#include <stdio.h>
#include <stdlib.h>
/*
    Trabalho 01 estrutura de dados II
    LAURIVAN SARETA - laurivan_sareta@hotmail.com
*/

struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
};

void inicializaABP(struct nodo* arvore){
    arvore = NULL;
}

int altura(struct nodo* arvore){
    if (arvore==NULL)
        return 0;
    else {
        int escAltura = altura(arvore->esq);
        int dirAltura = altura(arvore->dir);
        if (escAltura > dirAltura)
            return(escAltura + 1);
        else
            return(dirAltura + 1);
   }
}


struct nodo* novoNodo(int valor){
    struct nodo* aux;
    aux = (struct nodo*)malloc(sizeof(struct nodo));
    aux-> dir = NULL;
    aux-> esq = NULL;
    aux-> valor = valor;
    return aux;

}


struct nodo* insereNodo(struct nodo* arvore, int valor) {
    if (arvore == NULL){
        return(novoNodo(valor));
    }else {
        if (valor <= arvore->valor)
            arvore->esq = insereNodo(arvore->esq, valor);
        else
            arvore->dir = insereNodo(arvore->dir, valor);
        return(arvore);
    }
}


int fator(struct nodo* arvore){
    if (arvore == NULL)
        return 0;
    return (altura(arvore->esq) - altura(arvore->dir));
}

struct nodo* buscarNodo(struct nodo* arvore, int valor){
    if (arvore == NULL || arvore->valor == valor)
        return arvore;

    if (arvore->valor < valor)
        return buscarNodo(arvore->dir, valor);

    return buscarNodo(arvore->esq, valor);
}

int buscarFatorNodo(struct nodo* arvore, int valor){
    if (arvore == NULL)
        return 0;
    return fator( buscarNodo(arvore, valor) );
}

/*
    @RETORNA
    0 - NÃO É AVL E
    1 - É AVL
*/
int verificaAVL(struct nodo* arvore){
    if (arvore == NULL)
        return 0;

    verificaAVL(arvore->esq);

    int esqFator =  fator(arvore->esq);
    if ( (esqFator > 1) || (esqFator < -1) )
        return 0;

    verificaAVL(arvore->dir);

    int dirFator = fator(arvore->dir);
    if ((dirFator > 1) || (dirFator < -1) )
        return 0;
    return 1;
}
/*
    @RETORNA
    0 - NÃO ESTA BALANCEADA
    1 - ESTA BALANCEADA
*/
int verificaBalanceamento(struct nodo* arvore){
    if (arvore == NULL)
        return 0;

    verificaBalanceamento(arvore->esq);
    if (fator(arvore->esq) != 0)
        return 0;

    verificaBalanceamento(arvore->dir);
    if (fator(arvore->dir) != 0 )
        return 0;
    return 1;
}

int menu(){
    int opcao = 0;

    do{
        printf("Digite uma das opções a seguir: \n\n");
        printf("\n");
        printf("1 - inserção de nós na arvore. \n");
        printf("2 - buscar um valor e seu respectivo fator. \n");
        printf("3 - Saber se a árvore é uma AVL. \n");
        printf("4 - Saber se a árvore está completamente balanceada. \n");
        printf("5 - inserção automatica na arvore!. \n");
        printf("\n");
        printf("Qualquer tecla diferente de '0' para fechar.\n");
        printf("\n\n");
        scanf("%d", &opcao);
    }while (!(opcao <= 5) && !(opcao >= 0));

    if ((opcao <= 5) && (opcao > 0))
        return opcao;
    else
        return 0;
}

struct nodo* insercaoManual(struct nodo* arvore){
    arvore = insereNodo(arvore, 5);
    arvore = insereNodo(arvore, 11);
    arvore = insereNodo(arvore, 12);
    arvore = insereNodo(arvore, 13);
    arvore = insereNodo(arvore, 14);
    arvore = insereNodo(arvore, 15);
    arvore = insereNodo(arvore, 10);
    return arvore;
}

int main(){
    int temp, resultado;
    char charTemp;
    struct nodo *arvore;

    //Inicializa a arvore;
    inicializaABP(arvore);
    if (arvore-> esq == NULL)
        printf("vazio");
    else
        printf("cheio");

    //Inicializa Menu.
    while ( 1 ) {
        //Limpa variável para reutilizar;
        temp,resultado = 0;
        printf("\n -------------------------------------------------\n");
        switch (menu()){
            case 1 :
                //QUESTÃO 01;
                system("clear");
                printf("\nDigite um número intero para ser inserido \n\n");
                scanf("%d", &temp);
                arvore = insereNodo(arvore, temp);
                printf("\n\n Inserido com sucesso! \n\n\n");
                break;
            case 2:
                //QUESTÃO 02;
                system("clear");
                printf("\n Digite um número intero para verificarmos o seu fator caso exista! \n");
                scanf("%d", &temp);
                if (buscarNodo(arvore, temp))
                    printf("\n\n Fator do valor: %d \n\n\n", buscarFatorNodo(arvore, temp) );
                else
                    printf("\n\n Não foi encontrado o nodo! \n\n\n");
                break;
            case 3 :
                //QUESTÃO 03;
                system("clear");
                if (verificaAVL(arvore))
                    printf("\n\n Esta arvore é uma AVL \n\n\n");
                else
                    printf("\n\n Esta arvore não é uma AVL \n\n\n");
                break;
            case 4 :
                //QUESTÃO 04;
                system("clear");
                if (verificaBalanceamento(arvore))
                    printf("\n\n Esta arvore está completamente balanceada! \n\n\n");
                else
                    printf("\n\n Esta arvore não está completamente balanceada! \n\n\n");
                break;
            case 5 :
                system("clear");
                arvore = insercaoManual(arvore);
                printf("\n\n Inserido todos os valores com sucesso! \n\n\n");
                break;
            case 0 :
                return 0;
                break;
        }
    }

    return 0;
}
