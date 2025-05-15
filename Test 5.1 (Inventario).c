#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>


int inventory[9]; // Array para o invent�rio
int inventorySize = 10; // Tamanho do invent�rio
int playerLocation = 0;

//----- Selec��o do Menu e Sa�da do cr�dito -------

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
int x,y; // - Posi��o dentro da map
int i,j; // - Coordenadas
int item;
// Startup do jogo
void inicializarVariaveis() {
    int playerX = 0; // Posi��o inicial do jogador
    int playerY = 0; // Posi��o inicial do jogador
    int itemCount = 0; // Contador de itens no invent�rio
    for (i = 0; i < 9; i++) {
        inventory[i] = 0; // Inicializa o invent�rio com 0 (vazio)
    }
}





// ======= funcoes de utilidade para o invent�rio ========
// fun��o para exibir o invent�rio
void exibirInventario() {
    system ("cls");
    system ("color 0A");
    printf("Invent�rio:\n");
    const char* item = "";
    for (i = 0; i < inventorySize; i++) {
        if (inventory[i] != 0) { // Verifica se o espa�o do invent�rio n�o est� vazio
            switch (inventory[i]) // Verifica o tipo de item
            {
            case 1:
                item = "Espada Enferrujada";
                break;
            case 2:
                item = "Bandagem";
                break;
            default:
                item = "Item Desconhecido";
                break;
            }
            printf("%s ", item); // Exibe o item no invent�rio
        }
    }
    system ("pause"); // Pausa para o jogador ver o invent�rio
    system ("cls");
    atualizarMatriz(); // Atualiza a matriz ap�s exibir o invent�rio
    system ("color 0A");
}
    // fun��o para remover um item do invent�rio
    void removeItem(item) {
        for (i = 0; i < inventorySize; i++) {
            if (inventory[i] == item) { // Encontra o item no invent�rio
                inventory[i] = 0; // Remove o item do invent�rio
                break;
            }
        }
    }

    // fun��o para verificar se o jogador tem um item no invent�rio
    int hasItem(item) {
        for (i = 0; i < inventorySize; i++) {
            if (inventory[i] == item) {
                return 1; // Item encontrado no invent�rio
            }
        }
        return 0; // Item n�o encontrado no invent�rio
    }
    // fun��o para adicionar um item ao invent�rio
    void addItem(item) {
        for (i = 0; i < inventorySize; i++) {
            if (inventory[i] == 0) { // Encontra um espa�o vazio no invent�rio
                inventory[i] = item; // Adiciona o item ao invent�rio
                break;
            }
        }
    }

// ----- Fun��es gen�ricas de map --------

void inicializarMatriz() {
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            map[i][j] = 0;  // Define todas as c�lulas como vazias
        } 
    }
}

void exibirMatriz() {
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            switch (map[i][j]) {
                case 0:
                    if (i == x && j == y) {
                        printf("B ");  // Jogador
                    } else {
                        printf(". ");  // Espa�o vazio
                    }
                    break;
                case 1:
                    printf("P ");  // NPC
                    break;
                case 4:
                    printf("= ");  // Porta de entrada
                    break;
                case 5:
                    printf("= ");  // Porta de sa�da da casa
                    break;
                case 6:
                    printf("K ");  // Chave
                    break;
                default:
                    printf("? ");  // Caso n�o identificado
                    break;
            }
        }
        printf("\n");
    }
}


// ===== Fun��o do NPC de exibe o Tutorial =====

// --------- Fun��o de Pausa do jogo -----------
void pausa(){
	
	system ("cls");
	
      	
        system ("color 0B");
        printf ("==== Menu ====================\n\n");
        printf ("1. Continuar\n");
        printf ("2. voltar para o menu principal\n\n");
        printf ("=============================="); 
        scanf ("%d", &menuDePause);
        
        switch (menuDePause) {
			case 1:
				return;
				break;
			case 2:
				system ("cls");
                printf ("=======================\n\n"); 
				printf ("Voc� quer mesmo sair?\n");
				printf ("1. Sim\n");
				printf ("2. N�o\n");
				printf ("========================\n\n"); 
				scanf ("%d", &comfirmar);
				if (comfirmar == 1) {
					system ("cls");
					main();
					break;
				} if (comfirmar == 2) {
					system ("cls"); 
				    pausa();
				}   break;
		}
    
    system ("cls");
    
	
}

// ------------------ Fun��o Creditos ------------------------------
void Creditos() {
    
        system ("color 06");
        printf ("===========================================\n");
        printf ("D E S E N V O L V E D O R E S:\n\n");
        printf (". J O � O  P E D R O  M O R A E S\n");
        printf (". J O � O  H E N R I Q U E\n\n");
        printf ("============================================\n");
        system ("cls");
        height = 10;
        width = 10;
        x = 5;
        y = 3; 
        map[5][4] = 1; //NPC
        map[5][3] = 2; //Ativa��o do tutorial
        map[2][5] = 4; //ponto de transi��o
        system ("pause");
        system ("cls");
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
void vila() {
    playerLocation = 1;
    height = 10;
    width = 10;
    x = 5;
    y = 3; 
    map[5][4] = 1; //NPC
    map[5][3] = 2; //Ativa��o do tutorial
    map[2][5] = 4; //ponto de transi��o
    inicializarMatriz(); 
    atualizarMatriz();
}
void casa() {
  height = 5;
  width = 5;
  x = 2;
  y = 3; 
  
  
  inicializarMatriz(); 
  
  map[1][3] = 5; //ponto de transi��o
  map[4][3] = 6; //chave
  
  system ("color 01"); 
  	
  }


//------------ Fun��o Nuclear que gera a map e Controla o Personagem -----------

int atualizarMatriz() {
    
     system ("cls");
     system ("color 02");
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
            if (comando == 'I' || comando == 'i') exibirInventario(); //Exibe o invent�rio
            //interacao
            if (comando == 'E' || comando == 'e') {
                switch (map[x][y])
                {
                case 1:
                    printf("Voc� interagiu com o NPC!\n");
                    break;
                
                default:
                    break;
                }
            }

            
           // ---------- Verifica��o do Limite da matriz e Atualiza��o da posi��o do jogador ------------------------
    
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
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    system ("color 0E");
	Sleep(300);
	printf ("Desenvolvido por dois estudandes de programa��o. . .\n");
	Sleep(300); 
	printf (". . .Apresento o clone fraco do Umoria!!");
	Sleep (1000);
	system ("cls"); 
	

        system ("color 0D");
		printf ("==============================\n\n");
  	    printf ("V I R T U A   R U S H\n\n");
        printf ("1. J O G A R\n");
        printf ("2. C R � D I T O S\n");
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
