#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

//A biblioteca conio.he esta aqui para auxiliar na movimentçãoem a necessidade do enter - Funções: _kbhit() e _getch()

int escolha1; 
int escolha;

// ---------------------------- Matriz do Jogo -------------------------------

//# define Comprimento 10 - Tamanho da matriz
//# define Altura 10 - Tamanho da matriz

//int Matrix[Comprimento][Largura] 
//int linha (i), coluna (y); - variaveis para a matriz
//int x, y; - posição do jogador
// x = Comprimento / 2; - posiçao inicial
// y = Largura / 2; - posiçao inicial 
// grid [Comprimento][Largura] = 0 - outra forma de posição inicial 



//void grid () {
// system ("cls");
//      for (linha = 0; linha < Altura; linha++) {
// }       for (Coluna = 0; Coluna < Comprimento; j++) {
// }          if (x == i && y == j) {
// }              printf ("P "); - marcando a posicao do jogador
// }          else {
// }              printf (". "); - marcando o grid
// }          }
// }      printf ("\n"); 



void Creditos() {

    do
    {
        printf ("Desenvolvedores:\n");
        printf ("Joao Pedro Moraes\n");
        printf ("Pressione 0 para voltar\n");
        scanf ("%d", &escolha1);
        system ("cls");
       
    } while (escolha1 != 0);
    
	
}

int main() {

    
    while (escolha != 3) {


	printf ("1. Jogar\n");
        printf ("2. Creditos\n");
        printf ("3. Sair\n");
        scanf ("%d", &escolha); system ("cls"); 
		
        switch (escolha) {

	    case 1: 
		//Jogar(); 
		//break;
            case 2:
                Creditos();
                break;
	   }  

    printf ("jogo desligado. . . \n"); 
    
       }


       return 0;
   }

;






