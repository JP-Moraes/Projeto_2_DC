#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

//----- Sets para Menu Principal, Creditos e Menu de Pausa -------

int menuDePause; 
int comfirmar; - // Menu de comfirmação para sair dentro da Pausa
int sairCreditos; 
int escolha;

//------ Valores Globais do jogo --------------

//int matriz[40][40]; - // Matriz Fixa pro jogo 
int altura;
int comprimento;
int x,y; // - Posição dentro da Matriz
int i,j; // - Coordenadas 
int VitoriaX, VictoriaY // - coordenadas para passar de fase



// --------- Função de Pausa do jogo -----------
void pausa() {
	
	system ("cls"); 
	printf ("jogo pausando. . .");
	Sleep (1000);
	system ("cls");
	
      while(1) {
      	
        system ("cls");
        system ("color 0B");
        setlocale(LC_ALL, "Portuguese");
        printf ("==== Menu ====================\n\n");
        printf ("1. Continuar\n");
        printf ("2. voltar para o menu principal\n\n");
        printf ("=============================="); 
        scanf ("%d", &menuDePause);
        
        switch (menuDePause) {
			case 1:
				system ("color 02");
				atualizarMatriz();
				break;
			case 2:
				system ("cls");
                setlocale(LC_ALL, "Portuguese");
                printf ("=======================\n\n"); 
				printf ("Você quer mesmo sair?\n");
				printf ("1. Sim\n");
				printf ("2. Não\n");
				printf ("========================\n\n"); 
				scanf ("%d", &comfirmar);
				if (comfirmar == 2) {
					system ("cls");
					pausa();
				} if (comfirmar == 1) {
					system ("cls"); 
				    main();
				}
				break;
		}
       
    }
    
    system ("cls");
    
	
}

// ------------------ Função Creditos ------------------------------
void Creditos() {
	
      do {
        
        system ("color 06");
        setlocale(LC_ALL, "Portuguese");
        printf ("===========================================\n");
        printf ("D E S E N V O L V E D O R E S:\n\n");
        printf (". J O Ã O  P E D R O  M O R A E S\n");
        printf (". J O Ã O  H E N R I Q U E\n\n");
        printf ("Pressione 0 para voltar\n");
        printf ("============================================\n");
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
  

  printf ("carregando. . .\n");
  Sleep (2500);
  printf ("Jogo pronto!"); 
  Sleep (1200); 

  system ("color 0A");
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

    //  ------------ Captura o comando do jogador para movimentar --------------------
    if (_kbhit()) {
        char comando = _getch();
        int novoX = x;
        int novoY = y;

        if (comando == 'W' || comando == 'w') novoX--; //Cima
        if (comando == 'A' || comando == 'a') novoY--; //Direita
        if (comando == 'S' || comando == 's') novoX++; //Baixo
        if (comando == 'D' || comando == 'd') novoY++; //Esquerda
  	    if (comando == 'P' || comando == 'p') pausa(); //Ativa o menu de pause

       // ---------- Verificação do Limite da Matriz e Atualização da posição do jogador ------------------------

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < comprimento) {
            x = novoX;
            y = novoY; 
        }
    }
    
     Sleep (500);
   } 
   
   return 1; 
}

// ------------------ Menu Principal -------------------
int main() {
    
    setlocale(LC_ALL, "Portuguese");
    system ("color 0E");
	Sleep(1000);
	printf ("\n"); 
	printf ("Desenvolvido por dois estudandes de programação. . .\n");
	Sleep(1500); 
	printf (". . .Apresento o clone fraco do Umori!! :D");
	Sleep (2500);
	system ("cls"); 
	
    while (escolha != 3) {

        system ("color 0D");
        setlocale(LC_ALL, "Portuguese");
		printf ("==============================\n\n");
  	    printf ("V I R T U A   R U S H\n\n");
        printf ("1. J O G A R\n");
        printf ("2. C R É D I T O S\n");
        printf ("3. S A I R\n\n");
        printf ("==============================\n\n");
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
       system ("color 04"); 
       printf ("jogo desligado. . . \n"); 
       return 0;
}

