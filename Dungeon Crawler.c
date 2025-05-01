#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

//A biblioteca conio.he esta aqui para auxiliar na movimentçãoem a necessidade do enter - Funções: _kbhit() e _getch() 

int escolha1; 
int escolha;

// --------- Função que mantém o jogo rodando -------

// void jogar() {
//int jogoRodando = 1 - mantém o jogo ativo 
//int HP = HP_Maximo

// do {

//  int matriz ();
//  int controle ();
//  int vida (); 
//  if (vida == 0) { 
//  jogoRodando = 0 - O jogo para de jogar 

//}


// while (jogoRodando) { 




// ------ Matriz do Jogo ---------------------

//# define Comprimento 10 - Tamanho da matriz
//# define Altura 10 - Tamanho da matriz

//int linha (i), coluna (y); - variaveis para a matriz
//int x, y; - posição do jogador
//x = Comprimento / 2;
//y = Largura / 2; 


//void grid () { 
// system ("cls");
//      for (linha = 0; linha < Altura; linha++) {
// }       for (Coluna = 0; Coluna < Comprimento; j++) {
// }          if (x == i && y == j) {
// }              printf ("P "); - marcando posicao do jogador
// }          else {
// }              printf (". "); - marcando o grid
// }          }
// }      printf ("\n"); 


// ------- Função Controle e Colisão -------

// void controle() {
//int novoX = x;
//int novoY = y; - Atualização das coordenadas na matriz
//char comando; uso do teclado para 

//if (_kbhit()) {
//comando = _getch(); - Lê a tecla pressionad

//if (comando == W || comando == w)
//   novoX++;
// else if (comando == A || comando == a)
//   novoY++; 
// else if (comando == S || comando == s)
//  novoX--
// else if (comando == D || comando == d) 
//  novoy-- 


}

// -------- Função Vida ---------

// #define HP_Maximo 5

// void vidahub (){
// printf ("==============")
// printf ("HP: %d", d) - Hub da vida 
// printf ("==============") 
//}


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






