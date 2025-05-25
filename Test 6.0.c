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
        

        //----- Monstro -----
        int monsterRandomX = 999; // Coordenada X do monstro
        int monsterRandomY = 999; // Coordenada Y do monstro
        int monsterRandomX2 = 999; // Coordenada X do monstro 2
        int monsterRandomY2 = 999; // Coordenada Y do monstro 2
        int monsterFollowX = 999; // Coordenada X do monstro que segue o jogador
        int monsterFollowY = 999; // Coordenada Y do monstro que segue o jogador
        int monsterFollowX2 = 999; // Coordenada X do monstro que segue o jogador e atravessa o mapa
        int monsterFollowY2 = 999; // Coordenada Y do monstro que segue o jogador e atravessa o mapa

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
    //monsterRandomX = 0; 
    //monsterRandomY = 0;
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
            if (x == playerX && y == playerY || x == monsterRandomX2 && y == monsterRandomY2 || x == monsterRandomX && y == monsterRandomY){
                if (x == monsterRandomX && y == monsterRandomY) { // Se for a criatura que se move aleatoriamente
                    printf(" @ "); // Criatura que se move aleatoriamente
                } else if (x == monsterRandomX2 && y == monsterRandomY2) { // Se for a criatura que se move aleatoriamente
                    printf(" @ "); // Criatura que se move aleatoriamente
                } else if (x == playerX && y == playerY) {
                    printf(" & ");  // Jogador
                }
            } 
            else {
                    switch (map[x][y]) {
                        case 0:
                            printf(" . ");  // Espaço vazio
                            break;
                        case 1:
                            printf(" P ");  // NPC
                            break;
                        case 4:
                            printf("T T");  // Porta de entrada da casa
                            break;
                        case 5:
                            printf("T T");  // Porta de saída da casa
                            break;
                        case 6:
                            printf(" K ");  // Chave
                            break;
                        case 7:
                            printf("<O>");  // Monstro que segue o jogador
                            break;
                        case 8:
                            printf("XXX");  // Espinho
                            break;
                        case 10:
                            printf("^v^");  // Monstro que segue o jogador e atravessa o mapa
                            break;
                        case 11:
                            printf("###"); // Paredes
                            break;
                        case 12:
                            printf("\\\\\\"); // Telhado
                            break;
                        case 13:
                            printf("???"); // Água
                            break;
                        case 14:
                            printf("[ ]"); // Barril
                            break;
                        case 15:
                            printf(" @ "); // Criatura que se move aleatoriamente
                            default:
                            printf(" ? ");  // Caso não identificado
                            break;
                    }
                }
        }
        printf("\n");
    }
}



void vila(int newPlayerX, int newPlayerY) {
    playerLocation = 1;
    playerX = newPlayerX;
    playerY = newPlayerY;
    monsterRandomX = 999; // Reseta a coordenada do monstro que se move aleatoriamente
    monsterRandomY = 999; // Reseta a coordenada do monstro que se move aleatoriamente
    height = 10;
    width = 10;
    inicializarMatriz(); 
    map[5][4] = 1; //NPC
    drawFrom(0, 1, 3, 2, 11); // Desenha as paredes
    drawFrom(0, 0, 3, 0, 12); // Desenha o telhado
    map[2][2] = 4; //porta da casa
    atualizarMatriz();
}
void casa(int newPlayerX, int newPlayerY) {
    playerLocation = 2;
    playerX = newPlayerX;
    playerY = newPlayerY;
    height = 5;
    width = 5; 
    monsterRandomX = 1;
    monsterRandomY = 1;
    inicializarMatriz(); 
    drawFrom(0, 0, 0, 4, 11);
    drawFrom(0, 0, 4, 0, 11);
    drawFrom(4, 0, 4, 4, 11);
    drawFrom(0, 4, 4, 4, 11);
    map[1][4] = 5; //ponto de transição
    if (hasHouseKey == 0) {
        map[3][3] = 6; //chave
    } else {
        map[3][3] = 0; //Remove a chave se o jogador já pegou
    }
    atualizarMatriz();
    system ("color 01"); 
  	
}
void fase1 (int newPlayerX, int newPlayerY) {
	playerLocation = 3;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 10;
	width = 10; 
	//playerX = 
	//playerY = 
	inicializarMatriz();
    atualizarMatriz();
}
void fase2(int newPlayerX, int newPlayerY) {
	playerLocation = 4;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 20;
	width = 20;
	//playerX = 
	//playerY = 
	inicializarMatriz();
	map[6][4] = 10;  //Demonio de movimento aleatorio
	atualizarMatriz();
}
void fase3(int newPlayerX, int newPlayerY) {
	playerLocation = 5;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 40;
	width = 40;
	//playerX = 
	//playerY =
	inicializarMatriz();
	//map[][] = Demonio que segue o jogador;
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
        vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
	} else {
        vila(5, 5);
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
        // playerFacing ? a dire??o que o jogador est? olhando, de acordo com o comando. E W, A, S, D são as teclas de movimentação.
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
                int facingTile = map[frente.playerFacingX][frente.playerFacingY]; // Tile que o jogador está olhando
                switch (facingTile)
                {
                case 1:
                    printf("Voc? interagiu com o NPC!\n");
                    break;
                case 4:
                    printf("Voc? entrou na casa!\n");
                    playerLocation = 0;
                    casa(1, 3);
                    break;
                case 5:
                    printf("Voc? saiu da casa!\n");
                    playerLocation = 0;
                    vila(2,3);
                    break;
                case 6:
                    if (addItem(3)) { // Adiciona a chave ao inventário
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
                        printf("Você pegou a chave!\n");
                    } else {
                        printf("Inventário cheio!\n");
                    }
                default:
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz();
                    break;
                }
            }
            
            

            
           // ---------- Verifica??o do Limite da matriz e Atualizacao da posicao do jogador ------------------------
    
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                switch (map[newX][newY])
                {
                case 1:
                    printf("\nUma pessoa está bloqueando o caminho!\n");
                    break;
                case 2:
                    tutorial(); 
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                case 4:
                    printf("Você entrou na casa!\n");
                    playerLocation = 0;
                    casa(1, 3);
                    break;
                case 5:
                    printf("Você saiu da casa!\n");
                    playerLocation = 0;
                    vila(2, 3);
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
                        printf("Você pegou a chave!\n");
                    } else {
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        printf("Inventário cheio!\n");
                    }
                    break;
                case 11: 
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                	break;
                case 12:
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                case 13:
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                case 14:
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                default:
                    playerX = newX;
                    playerY = newY;
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
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
        printf ("2. C R É D I T O S\n");
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
        printf (". J O Ã O  P E D R O  M O R A E S\n");
        printf (". J O Ã O  H E N R I Q U E  P I N H E I R O\n\n");
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
				printf ("2. Não\n");
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
        printf("Inventário:\n");
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

        // Função para preencher um bloco no mapa com um valor específico
        void drawFrom(int x1, int y1, int x2, int y2, int value) {
            for (i = x1; i <= x2; i++) {
                for (j = y1; j <= y2; j++) {
                    if (i >= 0 && i < width && j >= 0 && j < height) {
                        map[i][j] = value;
                    }
                }
            }
        }

        void moveTheRandomCreature(int *creatureX, int *creatureY) {
            int directionToGo = rand() % 4;
            int newX = *creatureX;
            int newY = *creatureY;

            if (directionToGo == 0 && *creatureY > 0) newY--;
            if (directionToGo == 1 && *creatureY < height-1) newY++;
            if (directionToGo == 2 && *creatureX > 0) newX--;
            if (directionToGo == 3 && *creatureX < width-1) newX++;
            
            if (newX == playerX && newY == playerY) {
                respawnPlayer();
            } else if (map[newX][newY] == 0) {
                *creatureX = newX;
                *creatureY = newY;
            }
        }
        void monstersRandomStep() {
            // Move o monstro que se move aleatoriamente
            if (monsterRandomX != 999 && monsterRandomY != 999) {
                moveTheRandomCreature(&monsterRandomX, &monsterRandomY);
            }

            // Move o segundo monstro que se move aleatoriamente
            if (monsterRandomX2 != 999 && monsterRandomY2 != 999) {
                moveTheRandomCreature(&monsterRandomX2, &monsterRandomY2);
            }
        }

        void monstersFollowStep() {
            // Move o monstro que segue o jogador
            if (monsterFollowX != 999 && monsterFollowY != 999) {
                if (monsterFollowX < playerX) monsterFollowX++;
                else if (monsterFollowX > playerX) monsterFollowX--;
                if (monsterFollowY < playerY) monsterFollowY++;
                else if (monsterFollowY > playerY) monsterFollowY--;
            }

            // Move o monstro que segue e atravessa o mapa
            if (monsterFollowX2 != 999 && monsterFollowY2 != 999) {
                if (monsterFollowX2 < playerX) monsterFollowX2++;
                else if (monsterFollowX2 > playerX) monsterFollowX2--;
                if (monsterFollowY2 < playerY) monsterFollowY2++;
                else if (monsterFollowY2 > playerY) monsterFollowY2--;
            }
        }

        void respawnPlayer() {
            playerLocation = 1;
            vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
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
	//srand (time(0));
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    mainMenu();
}