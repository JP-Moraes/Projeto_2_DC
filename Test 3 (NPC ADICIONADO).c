#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

//----- Selecção do Menu e Saída do crédito -------

int tutorialExecutado = 0;
int menuDePause; 
int comfirmar; 
int sairCreditos; 
int escolha;

//------ Valores Globais do jogo --------------

int matriz[40][40]; // Matriz Fixa pro jogo 
int altura;
int comprimento;
int x,y; // - Posição dentro da Matriz
int i,j; // - Coordenadas 


// ----- Funções genéricas de Matriz --------

void inicializarMatriz() {
    for (j = 0; j < altura; j++) {
        for (i = 0; i < comprimento; i++) {
            matriz[i][j] = 0;  // Define todas as células como vazias
        }
    }
}

void exibirMatriz() {
    for (j = 0; j < altura; j++) {
        for (i = 0; i < comprimento; i++) {
            if (i == x && j == y) {
                printf("B ");  // Jogador
            } else if (matriz[i][j] == 1) {
                printf("P ");  // NPC
            } else {
                printf(". ");  // Espaço vazio
            }
        }
        printf("\n");
    }
}


===== Função do NPC de exibe o Tutorial =====
void npc(){
	
	system ("cls"); 
	
	if (tutorialExecutado == 0)  {
		
		system ("color 0C");
		setlocale(LC_ALL, "Portuguese");
		printf ("\n"); 
		printf ("B: Use W,A,S,D para movimentar\n");
		Sleep (2000);
		printf ("B: Pressione P para pausar o jogo quando quiser\n"); 
		Sleep (2000);
		printf ("B: Boa sorte em sua jornada\n\n"); 
		Sleep (2000);
	    printf ("\n\n"); 
	    printf ("Jogo pronto!\n\n");
		system ("pause");
		tutorialExecutado = 1; 
	}
	 
     system ("color 0A");
	 atualizarMatriz(); 
	
}




// --------- Função de Pausa do jogo -----------
void pausa() {
	
	system ("cls"); 
	printf ("jogo pausando. . .");
	Sleep (1000);
	system ("cls");
	
      while(1) {
      	
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


// ------- Funções que Configura a Matriz de cada fase ---------

void vila() {
  altura = 10;
  comprimento = 10;
  x = 5;
  y = 3; 
  
  inicializarMatriz(); 
  
  matriz[5][4] = 1; //NPC
  matriz[5][3] = 2; //Ativação do tutorial
  

  printf ("carregando. . .\n");
  Sleep (2500);
  printf ("preparando Tutorial. . ."); 
  Sleep (1200); 
  
  npc();

  system ("color 0A");
  atualizarMatriz(); 

}


//------------ Função Nuclear que gera a Matriz e Controla o Personagem -----------

int atualizarMatriz() {
     system ("cls");
     exibirMatriz(); 


    //  ------------ Captura o comando do jogador para movimentar --------------------
    if (_kbhit()) {
        char comando = _getch();
        int novoX = x;
        int novoY = y;

        if (comando == 'W' || comando == 'w') novoY--; //Cima
        if (comando == 'A' || comando == 'a') novoX--; //Direita
        if (comando == 'S' || comando == 's') novoY++; //Baixo
        if (comando == 'D' || comando == 'd') novoX++; //Esquerda
  	    if (comando == 'P' || comando == 'p') pausa(); //Ativa o menu de pause
  	    	
       // ---------- Verificação do Limite da Matriz e Atualização da posição do jogador ------------------------

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < comprimento) {
        	if (matriz[novoX][novoY] != 1) {
			   x = novoX;
               y = novoY;
			} else (matriz[novoX][novoY] == 2); {
				npc(); 
			}
   	       
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
	printf ("Desenvolvido por dois estudandes de programação. . .\n");
	Sleep(1500); 
	printf (". . .Apresento o clone fraco do Umori!! :3");
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

