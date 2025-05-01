#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//--- int dos menu e creditos ---
int sairCreditos; 
int escolha;

//--- Valores da Matriz e Posição do jogador ---
int altura;
int comprimento;
int x;
int y;
int i;
int j;

// ------------------ Função Creditos ------------------------------
void Creditos() {

    do
    {
        printf ("Desenvolvedores:\n");
        printf ("Joao Pedro Moraes\n");
        printf ("Pressione 0 para voltar\n");
        scanf ("%d", &sairCreditos);
        system ("cls");
       
    } while (sairCreditos != 0);
    
	
}

//------------ Função para gerar a matriz e movimentar o personagem-----------

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
    

    //Captura o comando do jogador 
    if (_kbhit()) {
        char comando = _getch();
        int novoX = x;
        int novoY = y;

        if (comando == 'W' || comando == 'w') novoX--; //Cima
        if (comando == 'A' || comando == 'a') novoY--; //Direita
        if (comando == 'S' || comando == 's') novoX++; //Baixo
        if (comando == 'D' || comando == 'd') novoY++; //Esquerda

       //Verifica os limites da matriz 
        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < comprimento) {
            x = novoX;
            y = novoY; 
        }
    }
    
     Sleep (150);
   } 
   
   return 1; 
   
}


int main() {

    
    while (escolha != 3) {


		printf ("1. Jogar\n");
        printf ("2. Creditos\n");
        printf ("3. Sair\n");
        scanf ("%d", &escolha); 
			
	    system ("cls"); 
		
        switch (escolha) {
            case 1: 
                altura = 20;
				comprimento = 10;
                x = 1;
                y = 1; 
                
                atualizarMatriz(altura, comprimento, x, y);
                break;

            case 2:
                Creditos();
                break;


	   }  

    
    }
       printf ("jogo desligado. . . \n"); 

       return 0;
   }

;
