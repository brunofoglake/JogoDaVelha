#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

char coordenadas[3][3];
const char jogador = 'X'; //Criei 2 constantes globais para o acesso facil dos X e O
const char computador = 'O';

void estruturaJogo(){ // Grade onde vai ser jogado o game
	printf(" %c | %c | %c ",coordenadas[0][0],coordenadas[0][1],coordenadas[0][2]);
	printf("\n---+---+---\n");
	printf(" %c | %c | %c ",coordenadas[1][0],coordenadas[1][1],coordenadas[1][2]);
	printf("\n---+---+---\n");
	printf(" %c | %c | %c ",coordenadas[2][0],coordenadas[2][1],coordenadas[2][2]);
}
void resetarEstrutura(){ // Simplesmente substitui os caracteres dentro da grade por espaços em branco
	int i, j;
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			coordenadas[i][j] = ' ';
		}
	}
}
int verificarEspacos(){ // Verifica quantos espaços disponíveis a grade possui para finalização do game caso não haja espaço
	int espacos = 9;
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(coordenadas[i][j] != ' '){
				espacos--;
			}
		}
	}

	return espacos;
}
void vezJogador(){ // Função que representa a vez em que o jogador joga
	int linha;
	int coluna;
	
	do{
		printf("\nDigite a linha(1 a 3): ");
		scanf("%d",&linha);
		linha--;
		printf("Digite a coluna(1 a 3): ");
		scanf("%d",&coluna);
		coluna--;
		
		if(coordenadas[linha][coluna] != ' '){
			printf("\nLugar ja ocupado! Perdeu a vez!\n");
		}else{
			coordenadas[linha][coluna] = jogador;
		}
	}while(coordenadas[linha][coluna] == ' ');
}
void printVencedor(int flagJogador, int flagComputador, int flagEmpate){ // Verifica quem venceu ou se foi empate e mostra na tela
	if(flagJogador == 1){
		printf("\n\nVoce venceu!");
	}else if(flagComputador == 1){
		printf("\n\nVoce perdeu!");
	}else if(flagEmpate == 1){
		printf("\n\nEmpatou!");
	}
}
int verificarVenceu(){ // Verifica se alguém venceu o jogo a cada rodada, independente se é a vez do jogador ou do computador
	int vencedor = 0;
	int i;
	
	//verificar horizontais
	for(i=0; i<3; i++){
		if((coordenadas[i][0] == jogador && coordenadas[i][1] == jogador && coordenadas[i][2] == jogador) || (coordenadas[i][0] == computador && coordenadas[i][1] == computador && coordenadas[i][2] == computador)){
			vencedor = 1;
			break;
		}
	}
	//verificar verticais
	for(i=0; i<3; i++){
		if((coordenadas[0][i] == jogador && coordenadas[1][i] == jogador && coordenadas[2][i] == jogador) || (coordenadas[0][i] == computador && coordenadas[1][i] == computador && coordenadas[2][i] == computador)){
			vencedor = 1;
			break;
		}
	}
	//verificar diagonal principal
	if((coordenadas[0][0] == jogador && coordenadas[1][1] == jogador && coordenadas[2][2] == jogador) || (coordenadas[0][0] == computador && coordenadas[1][1] == computador && coordenadas[2][2] == computador)){
		vencedor = 1;
	}
	//verificar diagonal secundária
	if((coordenadas[0][2] == jogador && coordenadas[1][1] == jogador && coordenadas[2][0] == jogador) || (coordenadas[0][2] == computador && coordenadas[1][1] == computador && coordenadas[2][0] == computador)){
		vencedor = 1;
	}
	
	return vencedor;
}
void vezComputador(){ // Função que representa a vez do computador, que irá jogar em casas aleatórias
	srand(time(0));
	int linhaComputador;
	int colunaComputador;
	
	if(verificarEspacos() > 0){
		do{
			linhaComputador = rand()%3;
			colunaComputador = rand()%3;
		}while(coordenadas[linhaComputador][colunaComputador] != ' ');
		
		coordenadas[linhaComputador][colunaComputador] = computador;
	}else{
		printVencedor(0,0,0);
	}
}


int main(){
   setlocale(LC_ALL, "Portuguese");
   int vencedor;
   char decidir = 's';
   int flagComputador;
   int flagJogador;
   int flagEmpate;

   do{
	  vencedor = 0;
      flagComputador = 0;
      flagJogador = 0;
      flagEmpate = 0;
      
      printf("Bem vindo ao jogo da velha!\n");
      printf("- Seu símbolo é o X, enquanto o computador jogará com o O\n");
      printf("- Para jogar, digite o primeiro numero para decidir a linha, e outro para decidir a coluna\n");
      printf("- Os números vão de 1 a 3, assim como os slots da grade\n");
      printf("Boa sorte!\n\n");
      resetarEstrutura();
      while(vencedor == 0 && verificarEspacos() != 0){
        estruturaJogo();
		vezJogador();
        vencedor = verificarVenceu();
        if(vencedor == 1){
        	flagJogador++;
        	break;
        }
        vezComputador();
        vencedor = verificarVenceu();
        if(vencedor == 1){
        	flagComputador++;
        	break;
        }
        if(verificarEspacos() == 0){
        	flagEmpate++;
        	break;
		}
     }
    estruturaJogo();
    printVencedor(flagJogador,flagComputador,flagEmpate);
    fflush(stdin);
    printf("\nVoce gostaria de jogar novamente? S para Sim e N para Nao:\n");
    scanf("%c",&decidir);
    system("cls");
   }while(tolower(decidir) == 's');
   printf("Jogo encerrado");

   return 0;
}
