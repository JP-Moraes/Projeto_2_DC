#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

//----- Selecção do Menu e Saída do crédito -------


int sairCreditos; 
int escolha;

//------ Valores Globais do jogo --------------

// int matriz[40][40]; - // Matriz Fixa pro jogo 
int altura;
int comprimento;
int x,y; // - Posição dentro da Matriz
int i,j; // - Coordenadas 

// ------------------ Função Creditos ------------------------------
void Creditos() {
	
      do {
        
        system (color 06);
        setlocale(LC_ALL, "Portuguese");
        printf ("Desenvolvedores:\n\n");
        printf ("João Pedro Moraes\n");
        printf ("João Henrique \n\n");
        printf ("Pressione 0 para voltar\n");
        scanf ("%d", &sairCreditos);
        system ("cls");
       
    } while (sairCreditos != 0);
    
	
}


// ------- Função que Configura a Matriz de cada fase ---------

void vila() {
  altura = 10;
  comprimento = 10;
  x = 5;
  y = 3; 

  printf ("carregando. . .");
  Sleep (2500);
  printf ("Jogo pronto!"); 
  Sleep (1200); 

  system (color 02);
  atualizarMatriz(); 

}


//------------ Função Nuclear que gera a Matriz e Controla o Personagem -----------

int atualizarMatriz() {
    int jogoRodando = 1;
	  

    while (jogoRodando) {
    	
        system ("cls");
        for (i = 0; i < altura; i++) {
            for (j = 0; j < comprimento; j++) {
				if (i == x && j == y) {
                    printf ("P ");
                } else {
                    printf (". ");
                }     
				
			}
			               
           printf ("\n"); 
        }
      printf ("========= Villa ========"); 

    //  ------------ Captura o comando do jogador para movimentar --------------------
    if (_kbhit()) {
        char comando = _getch();
        int novoX = x;
        int novoY = y;

        if (comando == 'W' || comando == 'w') novoX--; //Cima
        if (comando == 'A' || comando == 'a') novoY--; //Direita
        if (comando == 'S' || comando == 's') novoX++; //Baixo
        if (comando == 'D' || comando == 'd') novoY++; //Esquerda

       // ---------- Verificação do Limite da Matriz e Atualização da posição do jogador ------------------------

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < comprimento) {
            x = novoX;
            y = novoY; 
        }
    }
    
     Sleep (2500);
   } 
   
   return 1; 
}

// ------------------ Menu Principal -------------------
int main() {

    
    while (escolha != 3) {

        system (color 01); 
	       printf ("V I R T U A   R U S H\n\n");
	       printf ("1. Jogar\n");
        printf ("2. Creditos\n");
        printf ("3. Sair\n");
        scanf ("%d", &escolha); 		
	system ("cls"); 
		
        switch (escolha) {
            case 1: 
                vila(); 
                break;

            case 2:
                Creditos();
                break;
	   }  

    }
       printf ("jogo desligado. . . \n"); 
       return 0;
}


