#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//A biblioteca conio.he esta aqui para auxiliar na movimentçãoem a necessidade do enter - Funções: _kbhit() e _getch() 

int escolha1; 
int escolha;

//int x, u - posição do jogador 
//int Altura, Comprimento - coordenadas na matriz

// os dados acima serão utilizados no case 1 jogar para gerar a matriz ao selecionar 


// ------ Matriz do Jogo ---------------------


//int atualizarMatriz() { 
// int jogoRodando = 1

// while (jogoRodando) 
// system ("cls");
//      for (linha = 0; linha < Altura; linha++) {
// }       for (Coluna = 0; Coluna < Comprimento; j++) {
// }          if (x == i && y == j) {
// }              printf ("P "); - marcando posicao do jogador
// }          else {
// }              printf (". "); - marcando o espaço vazio 
// }          }
// }      printf ("\n");

// -- Capturar o teclado para movimento --

//int novoX = x;
//int novoY = y; - Atualização das coordenadas na matriz
//char comando;- uso do teclado para movimentar

//if (_kbhit()) {
//comando = _getch(); - Lê a tecla pressionada
//if (comando == W || comando == w)
//   novoX++;
// else if (comando == A || comando == a)
//   novoY++; 
// else if (comando == S || comando == s)
//  novoX--;
// else if (comando == D || comando == d) 
//  novoy--;

-- Limitação da movimentação e colisão -- 
// if (novoX >= 0 && novoX < Altura && novoY >= 0 && novoY < Comprimento)
// x = novoX; 
// y = novoY; - Atualiza para a nova posição 



void Creditos() {

    do
    {
        printf ("Desenvolvedores:\n");d
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






