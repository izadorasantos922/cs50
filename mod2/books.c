#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define tam 3

	struct book {
		int code;
		char title[50];
		char author[30];
		char area[50];
		int ano;
		char editora[20];
	};
	
int main(){
	int opcao, busca,isearch, achar;
	setlocale(LC_ALL, "Portuguese");
	struct book books[tam];
	struct book troca;
	do{
		printf("1- Cadastrar livros\n");
		printf("2- Imprimir informações dos livros\n");
		printf("3- Pesquisar livros por código\n");
		printf("4- Ordenar livros por ano\n");
		printf("5- Sair do programa \n");
		printf("Escolha sua opção\n");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				system("cls");
				fflush(stdin);
				for(int i = 0; i < tam; i++){
					printf("Escreva o codigo ");
					scanf("%d", &books[i].code);
					fflush(stdin);
					printf("Escreva o titulo ");
					fflush(stdin);
					scanf("%50[^\n]s", &books[i].title);
					fflush(stdin);
					printf("Escreva o autor ");
					scanf("%30[^\n]s", &books[i].author);
					fflush(stdin);
					printf("Escreva o area ");
					scanf("%50[^\n]s", &books[i].area);
					fflush(stdin);
					printf("Escreva o ano ");
					scanf("%d", &books[i].ano);
					fflush(stdin);
					printf("Escreva o editora ");
					scanf("%50[^\n]s", &books[i].editora);
					fflush(stdin);
				}
				break;
			case 2:
				system("cls");
				for(int i = 0; i < tam; i++){
					printf("####################################################\n");
					printf("Codigo %d\n", books[i].code + 1);
					printf("Titulo %s\n", books[i].title);
					printf("Autor %s\n", books[i].author);
					printf("Area %s\n", books[i].area);
					printf("Ano %d\n", books[i].ano);
					printf("Editora %s\n", books[i].editora);
					printf("####################################################\n");
				}
				break;
			case 3:
				system("cls");
				printf("Digite o codigo do livro que você quer achar ");
				scanf("%d", &busca);
				 isearch = 0;
				 achar = 0;
				while((isearch < tam) && (achar == 0)){
					if(books[isearch].code == busca){
						achar++;
					}else{
						isearch++;
					}
					if(achar == 1){
						printf("Codigo %d\n", books[isearch].code + 1);
						printf("Titulo %s\n", books[isearch].title);
						printf("Autor %s\n", books[isearch].author);
						printf("Area %s\n", books[isearch].area);
						printf("Ano %d\n", books[isearch].ano);
						printf("Editora %s\n", books[isearch].editora);
					}else{
						printf("Livro não encontrado!!!");
					}
				}
				break;
			case 4:
				for(int i = 0; i < tam; i++){
					
					for (int j = i + 1; j < tam; j++){
						if(books[i].ano > books[j].ano ){
							troca = books[i];
							books[i] = books[j];
							books[j] = troca;
						}
					}
				}
				for(int i = 0; i < tam; i++){
					printf("####################################################\n");
					printf("Codigo: %d, titulo: %s e ano: %d", books[i].code, books[i].title, books[i].ano);
					printf("####################################################\n");
				}
				break;
		}
	}while(opcao != 5);
	return 0;
}