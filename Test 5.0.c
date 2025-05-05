#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>


int playerLocation = 0;

//----- Selecção do Menu e Saída do crédito -------

int tutorialShown = 0; //Tutorial ser executado uma vez
int startScreenShown = 0;
int menuDePause; 
int comfirmar; 
int sairCreditos; 
int escolha; 


//------ Valores Globais do jogo --------------

int map[40][40]; // map Fixa pro jogo 
int height;
int width;
int x,y; // - Posição dentro da map
int i,j; // - Coordenadas

// ----- Funções genéricas de map --------

void inicializarMatriz() {
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            map[i][j] = 0;  // Define todas as células como vazias
        } 
    }
}

void exibirMatriz() {
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (i == x && j == y) {
                printf("B ");  // Jogador
            } else if (map[i][j] == 1) {
                printf("P ");  // NPC
            } else if (map[i][j] == 4){
                printf("= ");  // porta de entrada
            } else if (map[i][j] == 6){
            	printf ("K "); //chave
			} else if (map[i][j] == 5) {
				printf("= "); //porta de saida da casa
			} else {
				printf (". "); 
			}
        }
        printf("\n");
    }
}


// ===== Função do NPC de exibe o Tutorial =====

// --------- Função de Pausa do jogo -----------
void pausa(){
	
	system ("cls");
	
      while(1) {
      	
        system ("color 0B");
        printf ("==== Menu ====================\n\n");
        printf ("1. Continuar\n");
        printf ("2. voltar para o menu principal\n\n");
        printf ("=============================="); 
        scanf ("%d", &menuDePause);
        
        switch (menuDePause) {
			case 1:
				system ("color 02");
				return;
				break;
			case 2:
				system ("cls");
                printf ("=======================\n\n"); 
				printf ("Você quer mesmo sair?\n");
				printf ("1. Sim\n");
				printf ("2. Não\n");
				printf ("========================\n\n"); 
				scanf ("%d", &comfirmar);
				if (comfirmar == 1) {
					system ("cls");
					pausa();
					break;
				} if (comfirmar == 2) {
					system ("cls"); 
				    main();
				}   break;
		}
       
    }
    
    system ("cls");
    
	
}

// ------------------ Função Creditos ------------------------------
void Creditos() {
	
      do {
        
        system ("color 06");
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


// ------- Funções que Configura a map de cada fase ---------

void vila() {
    playerLocation = 1;
    height = 10;
    width = 10;
    x = 5;
    y = 3; 
    map[5][4] = 1; //NPC
    map[5][3] = 2; //Ativação do tutorial
    map[2][5] = 4; //ponto de transição
    inicializarMatriz(); 
    atualizarMatriz();
}
void tutorial()
{
    system ("cls"); 
	
	if (tutorialShown == 0)  {
		
		system ("color 0C");
		printf ("\n"); 
		printf ("B: Use W,A,S,D para movimentar\n");
		printf ("B: Pressione P para pausar o jogo quando quiser\n"); 
		printf ("B: Boa sorte em sua jornada\n\n"); 
	    printf ("\n\n"); 
	    printf ("Jogo pronto!\n\n");
		system ("pause");
		tutorialShown = 1;
        vila();
	} else {
        vila();
    }


}

void casa() {
  height = 5;
  width = 5;
  x = 2;
  y = 3; 
  
  
  inicializarMatriz(); 
  
  map[1][3] = 5; //ponto de transição
  map[4][3] = 6; //chave
  
  system ("color 01"); 
  	
  }


//------------ Função Nuclear que gera a map e Controla o Personagem -----------

int atualizarMatriz() {
    
     system ("cls");
     exibirMatriz(); 
     Sleep(50);


    //  ------------ Captura o comando do jogador para movimentar --------------------
    while (playerLocation != 0)
    {
        if (_kbhit()) {
            char comando = _getch();
            int newX = x;
            int newY = y;
    
            if (comando == 'W' || comando == 'w') newY--; //Cima
            if (comando == 'A' || comando == 'a') newX--; //Direita
            if (comando == 'S' || comando == 's') newY++; //Baixo
            if (comando == 'D' || comando == 'd') newX++; //Esquerda
            if (comando == 'P' || comando == 'p') pausa(); //Ativa o menu de pause
                  
           // ---------- Verificação do Limite da matriz e Atualização da posição do jogador ------------------------
    
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                switch (map[newX][newY])
                {
                case 2:
                    tutorial(); 
                    atualizarMatriz(); 
                    break;
                default:
                    x = newX;
                    y = newY;
                    atualizarMatriz(); 
                    break;
                }
                
            } 
        }
    }
    
    
     
}

// ------------------ Menu Principal -------------------
int main(){
    
    setlocale(LC_ALL, "Portuguese_Brazil");
    system ("color 0E");
	Sleep(300);
	printf ("Desenvolvido por dois estudandes de programação. . .\n");
	Sleep(300); 
	printf (". . .Apresento o clone fraco do Umoria!!");
	Sleep (1000);
	system ("cls"); 
	

        system ("color 0D");
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
            default:
                system ("color 04"); 
                printf ("jogo desligado. . . \n"); 
                return 0;
                break;
	   }  
}
