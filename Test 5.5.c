#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>


// ------ Setup do jogo ------

    //---- Variaveis globais ----

        int i; // Vari?vel de controle
        int j; // Vari?vel de controle

        //----- Variaveis Base do Jogador ------
        int itemCount = 0; // Contador de itens no invent?rio
        int inventory[10]; // Array para o invent?rio
        int inventorySize = 10; // Tamanho do invent?rio
        int item;
        int playerLocation = 0;
        int playerFacing = 0; // Dire??o que o jogador est? olhando
        

        //----- Selec??o do Menu e Sa?da do cr?dito -------

        int tutorialShown = 0; //Tutorial ser executado uma vez
        int startScreenShown = 0;
        int menuDePause; 
        int menuQuitConfirm; 
        int sairCreditos; 
        int escolha; 


        //------ Coordenadas --------------

        int map[40][40]; // map Fixa pro jogo 
        int height;
        int width;
        int y = 0;
        int x = 0;
        int playerX,playerY; // - Posicao do jogador dentro do mapa
        int gridX,gridY; // - Coordenadas

        //----- Save Data ------
        int hasVilaKey = 0; // Vari?vel para verificar se o jogador tem a chave determinada
        int hasHouseKey = 0; // Vari?vel para verificar se o jogador tem a chave da casa

        
typedef struct {
    int playerFacingX;
    int playerFacingY;
} Coordenada;





// Definicao de Funcoes
int atualizarMatriz();
void Creditos();
int removeItem(int item);
int addItem(int item);
int hasItem(int item);
void exibirInventario();
void pausa();
Coordenada verificaDirecaoDaInteracao();





// Startup do jogo
void inicializarVariaveis() {
    playerX = 0; // Posi??o inicial do jogador
    playerY = 0; // Posi??o inicial do jogador
    itemCount = 0; // Contador de itens no invent?rio
    for (i = 0; i < inventorySize; i++) {
        inventory[i] = 0; // Inicializa o invent?rio com 0 (vazio)
    }
}






// ----- Fun??es gen?ricas de map --------

void inicializarMatriz() {
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            map[i][j] = 0;  // Define todas as celulas como vazias
        } 
    }
}

void exibirMatriz() {
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (x == playerX && y == playerY) {
                printf("B ");  // Jogador
            } else {
                switch (map[x][y]) {
                    case 0:
                        printf(". ");  // Espa?o vazio
                        break;
                    case 1:
                        printf("P ");  // NPC
                        break;
                    case 4:
                        printf("= ");  // Porta de entrada
                        break;
                    case 5:
                        printf("= ");  // Porta de sa?da da casa
                        break;
                    case 6:
                        printf("K ");  // Chave
                        break;
                    default:
                        printf("? ");  // Caso n?o identificado
                        break;
                }
            }
        }
        printf("\n");
    }
}



void vila() {
    playerLocation = 1;
    height = 10;
    width = 10;
    playerX = 5;
    playerY = 3; 
    inicializarMatriz(); 
    map[5][4] = 1; //NPC
    map[2][5] = 4; //ponto de transicao
    if (hasVilaKey == 0) {
        map[2][3] = 6; //Chave
    } else {
        map[2][3] = 0; //Remove a chave se o jogador j? pegou
    }
    atualizarMatriz();
}
void casa() {
    playerLocation = 2;
    height = 5;
    width = 5;
    playerX = 2;
    playerY = 3; 
    inicializarMatriz(); 
    map[1][3] = 5; //ponto de transi??o
    if (hasHouseKey == 0) {
        map[4][3] = 6; //chave
    } else {
        map[4][3] = 0; //Remove a chave se o jogador j? pegou
    }
    atualizarMatriz();
    system ("color 01"); 
  	
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
//------------ Fun??o Nuclear que gera a map e Controla o Personagem -----------

int atualizarMatriz() {
    
     system ("cls");
     system ("color 02");
     exibirMatriz(); 
     Sleep(50);


    //  ------------ Captura o comando do jogador para movimentar --------------------
    while (playerLocation != 0)
    {
        // playerFacing ? a dire??o que o jogador est? olhando, de acordo com o comando. E W, A, S, D s?o as teclas de movimenta??o.
        // playerX e playerY s?o as coordenadas do jogador na matriz.
        if (_kbhit()) {
            char comando = _getch();
            int newX = playerX;
            int newY = playerY;
            if (comando == 'W' || comando == 'w') {
                newY--; //Cima
                playerFacing = 0;
            }
            if (comando == 'A' || comando == 'a') {
                newX--; //Esquerda
                playerFacing = 1;
            }
            if (comando == 'S' || comando == 's') {
                newY++; //Baixo
                playerFacing = 2;
            }
            if (comando == 'D' || comando == 'd') {
                newX++; //Direita
                playerFacing = 3;
            }
            if (comando == 'P' || comando == 'p') pausa(); //Ativa o menu de pause
            if (comando == 'I' || comando == 'i') exibirInventario(); //Exibe o inventario

            //interacao
            if (comando == 'E' || comando == 'e') {
                Coordenada frente = verificaDirecaoDaInteracao();
                int facingTile = map[frente.playerFacingX][frente.playerFacingY]; // Tile que o jogador est? olhando
                switch (facingTile)
                {
                case 1:
                    printf("Voc? interagiu com o NPC!\n");
                    break;
                case 4:
                    printf("Voc? entrou na casa!\n");
                    playerLocation = 0;
                    casa();
                    break;
                case 5:
                    printf("Voc? saiu da casa!\n");
                    playerLocation = 0;
                    vila();
                    break;
                case 6:
                    if (addItem(3)) { // Adiciona a chave ao invent?rio
                        map[frente.playerFacingX][frente.playerFacingY] = 0; // Remove o tile da chave do mapa
                        switch (playerLocation)
                        {
                        case 1:
                            hasVilaKey = 1; // A chave da vila foi pega
                            break;
                        case 2:
                            hasHouseKey = 1; // A chave da casa foi pega
                            break;
                        }
                        atualizarMatriz(); 
                        printf("Voc? pegou a chave!\n");
                    } else {
                        atualizarMatriz(); 
                        printf("Invent?rio cheio!\n");
                    }
                    break;
                default:
                    break;
                }
            }

            
           // ---------- Verifica??o do Limite da matriz e Atualizacao da posicao do jogador ------------------------
    
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                switch (map[newX][newY])
                {
                case 1:
                    printf("\nUma pessoa est? bloqueando o caminho!\n");
                    break;
                case 2:
                    tutorial(); 
                    atualizarMatriz(); 
                    break;
                case 4:
                    printf("Voc? entrou na casa!\n");
                    playerLocation = 0;
                    casa();
                    break;
                case 5:
                    printf("Voc? saiu da casa!\n");
                    playerLocation = 0;
                    vila();
                    break;
                case 6:
                    
                    if (addItem(3)) { // Adiciona a chave ao invent?rio
                        map[newX][newY] = 0; // Remove o tile da chave do mapa
                        switch (playerLocation)
                        {
                        case 1:
                            hasVilaKey = 1; // A chave da vila foi pega
                            break;
                        case 2:
                            hasHouseKey = 1; // A chave da casa foi pega
                            break;
                        }
                        playerX = newX;
                        playerY = newY;
                        atualizarMatriz(); 
                        printf("Voc? pegou a chave!\n");
                    } else {
                        atualizarMatriz(); 
                        printf("Invent?rio cheio!\n");
                    }
                    break;
                default:
                    playerX = newX;
                    playerY = newY;
                    atualizarMatriz(); 
                    break;
                }    
            } 
        }
    }
    
    
     
}

// ------------------ Menu Principal -------------------
void mainMenu() {
        escolha = 0;
        system ("color 0D");
		printf ("==============================\n\n");
  	    printf ("V I R T U A   R U S H\n\n");
        printf ("1. J O G A R\n");
        printf ("2. C R ? D I T O S\n");
        printf ("3. S A I R\n\n");
        printf ("==============================\n\n");
        scanf ("%d", &escolha); 		
	    system ("cls"); 
		
        switch (escolha) {
            case 1: 
                tutorial(); 
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

// ------------------ Funcao dos Creditos ------------------------------
void Creditos() {
    
        system ("color 06");
        printf ("===========================================\n");
        printf ("D E S E N V O L V E D O R E S:\n\n");
        printf (". J O ? O  P E D R O  M O R A E S\n");
        printf (". J O ? O  H E N R I Q U E  P I N H E I R O\n\n");
        printf ("============================================\n");
        system ("pause");
        system ("cls");
        mainMenu();
}

// --------- Funcao de Pausa do jogo -----------
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
				printf ("Voc? quer mesmo sair?\n");
				printf ("1. Sim\n");
				printf ("2. N?o\n");
				printf ("========================\n\n"); 
				scanf ("%d", &menuQuitConfirm);
				if (menuQuitConfirm == 1) {
					system ("cls");
					mainMenu();
					break;
				} if (menuQuitConfirm == 2) {
					system ("cls"); 
				    pausa();
				}   break;
		}
    
    system ("cls");
    
	
}
// ======= funcoes de utilidade para o invent?rio ========
    // fun??o para exibir o invent?rio
    void exibirInventario() {
        system ("cls");
        system ("color 0A");
        printf("Invent?rio:\n");
        const char* item = "";
        for (i = 0; i < inventorySize; i++) {
            if (inventory[i] != 0) { // Verifica se o espa?o do invent?rio n?o est? vazio
                switch (inventory[i]) // Verifica o tipo de item
                {
                case 1:
                    item = "Espada Enferrujada";
                    break;
                case 2:
                    item = "Bandagem";
                    break;
                case 3:
                    item = "Chave";
                    break;
                default:
                    item = "Item Desconhecido";
                    break;
                }
                printf("%s\n", item); // Exibe o item no inventario
            }
        }
        system ("pause"); // Pausa para o jogador ver o inventario
        system ("cls");
        atualizarMatriz(); // Atualiza a matriz apos exibir o inventario
        system ("color 0A");
    }
        // funcao para remover um item do inventario
        int removeItem(int itemReference) {
            for (i = 0; i < inventorySize; i++) {
                if (inventory[i] == itemReference) { // Encontra o item no inventario
                    inventory[i] = 0; // Remove o item do inventario
                    break;
                }
            }
        }

        // funcao para verificar se o jogador tem um item no inventario
        int hasItem(int itemReference) {
            for (i = 0; i < inventorySize; i++) {
                if (inventory[i] == itemReference) {
                    return 1; // Item encontrado no inventario
                }
            }
            return 0; // Item nao encontrado no inventario
        }
        // funcao para adicionar um item ao inventario
        int addItem(int itemReference) {
            for (i = 0; i < inventorySize; i++) {
                if (inventory[i] == 0) { // Encontra um espaco vazio no inventario
                    inventory[i] = itemReference; // Adiciona o item ao inventario
                    return 1; // Retorna sucesso. Jogador pegou o item.
                }
            }
        }
        Coordenada verificaDirecaoDaInteracao() {
        Coordenada tile;
        tile.playerFacingX = playerX;
        tile.playerFacingY = playerY;
        switch (playerFacing) {
            case 0: // Cima
                tile.playerFacingY--;
                break;
            case 1: // Esquerda
                tile.playerFacingX--;
                break;
            case 2: // Baixo
                tile.playerFacingY++;
                break;
            case 3: // Direita
                tile.playerFacingX++;
                break;
        }
        return tile;
        }

// ------------------ Fun??o Principal -------------------
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    mainMenu();
}