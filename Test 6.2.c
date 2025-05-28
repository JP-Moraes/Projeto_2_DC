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
        int joeTalked = 0; // Vari?vel para verificar se o jogador já conversou com Joe
        

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
void textOnScreen(const char* text);
void drawFrom(int x1, int y1, int x2, int y2, int value);



void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

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
    printf("\n\n\n\n\n\n\n\n");
    for (y = 0; y < height; y++) {
        printf("                                      "); // Espaçamento para alinhar a matriz
        for (x = 0; x < width; x++) {
            if (x == playerX && y == playerY || x == monsterRandomX2 && y == monsterRandomY2 || x == monsterRandomX && y == monsterRandomY){
                if (x == monsterRandomX && y == monsterRandomY) { // Se for a criatura que se move aleatoriamente
                    printf("\033[31m @ \033[0m"); // Criatura que se move aleatoriamente
                } else if (x == monsterRandomX2 && y == monsterRandomY2) { // Se for a criatura que se move aleatoriamente
                    printf("\033[31m @ \033[0m"); // Criatura que se move aleatoriamente
                } else if (x == playerX && y == playerY) {
                    printf("\\o/");  // Jogador
                }
            } 
            else {
                    switch (map[x][y]) {
                        case 0: // Espaço vazio
                            switch (playerLocation)  // Verifica a localiza??o do jogador
                            {
                            case 1: // Vila
                                printf("\033[32m . \033[0m");
                                break;
                            case 2: // Casa
                                printf("\033[90m . \033[0m");
                                break;
                            case 3: // Fase 1
                                printf("\033[90m . \033[0m");
                                break;
                            case 4: // Fase 2  
                                printf("\033[90m . \033[0m");
                                break;
                            case 5: // Fase 3
                                printf("\033[90m . \033[0m");
                                break;
                                
                            default:
                                break;
                            }
                            
                            break;
                        case 1:
                            printf("_O_");  // NPC
                            break;
                        case 4:
                            printf("\033[33mT T\033[0m");  // Porta de entrada da casa
                            break;
                        case 5:
                            printf("\033[33mT T\033[0m");  // Porta de saída da casa
                            break;
                        case 6:
                            printf("\033[93m K \033[0m");  // Chave
                            break;
                        case 7:
                            printf("\033[94m<O>\033[0m");  // Monstro que segue o jogador
                            break;
                        case 8:
                            printf("\033[31mXXX\033[0m");  // Espinho
                            break;
                        case 10:
                            printf("^v^");  // Monstro que segue o jogador e atravessa o mapa
                            break;
                        case 11:
                            printf("\033[37m###\033[0m"); // Paredes
                            break;
                        case 12:
                            printf("\033[37m\\\\\\\033[0m"); // Telhado
                            break;
                        case 13:
                            printf("\033[36m~~~\033[0m"); // Água
                            break;
                        case 14:
                            printf("[ ]"); // Barril
                            break;
                        case 15:
                            printf("\033[35mT+T\033[0m"); // Porta Trancada
                            break;
                        case 16:
                            printf("\033[35mT T\033[0m"); // Porta Destrancada
                            break;
                        case 17:   
                            printf("\033[90m###\033[0m"); // Canto do mapa
                            break;
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
    map[8][6] = 15; //Porta Trancada
    drawFrom(0, 0, 0, 9, 17); // Cantos do mapa
    drawFrom(0, 0, 9, 0, 17); // Cantos do mapa
    drawFrom(9, 0, 9, 9, 17); // Cantos do mapa
    drawFrom(0, 9, 9, 9, 17); // Cantos do mapa
    drawFrom(1, 2, 4, 3, 11); // Desenha as paredes
    drawFrom(1, 1, 4, 1, 12); // Desenha o telhado
    map[3][3] = 4; //porta da casa
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
    drawFrom(0, 0, 0, 4, 17); // Cantos do mapa
    drawFrom(0, 0, 4, 0, 17);
    drawFrom(4, 0, 4, 4, 17);
    drawFrom(0, 4, 4, 4, 17);
    map[1][4] = 5; //ponto de transição
    if (hasHouseKey == 0) {
        map[3][3] = 6; //chave
    } else {
        map[3][3] = 0; //Remove a chave se o jogador já pegou
    }
    atualizarMatriz();
  	
}
void fase1 (int newPlayerX, int newPlayerY) {
	playerLocation = 3;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 20;
	width = 15;
    inicializarMatriz();
    drawFrom(0, 0, 0, 19, 17); // Cantos do mapa
    drawFrom(0, 0, 14, 0, 17);
    drawFrom(14, 0, 14, 19, 17);
    drawFrom(0, 19, 14, 19, 17);
    drawFrom(1, 6, 13, 6, 8); // Desenha os espinhos
	//playerX = 
	//playerY = 
	
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
		
        setColor(13);
		printf ("\n");
		printf ("B: Use W,A,S,D para movimentar\n");
		printf ("B: Pressione P para pausar o jogo quando quiser\n");
		printf ("B: Boa sorte em sua jornada\n\n");
		system ("pause");
		tutorialShown = 1;
        setColor(7);
        vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
	} else {
        vila(5, 5);
    }


}
//------------ Fun??o Nuclear que gera a map e Controla o Personagem -----------

int atualizarMatriz() {
    
     system ("cls");
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
                    if (joeTalked == 0) {
                        if(hasHouseKey == 1) { // Se o jogador tiver a chave da casa
                        textOnScreen("Joe: Então você pegou a chave.");
                        textOnScreen("Joe: Boa sorte lá embaixo, você vai precisar.");
                        textOnScreen("Joe: Que Deus tenha piedade da sua alma.");
                        joeTalked = 1;
                    } else {
                        textOnScreen("Joe: Você vai mesmo descer..?");
                        textOnScreen("Joe: Isso é loucura...");
                        textOnScreen("Joe: Mas se é mesmo o único jeito de acabar com isso...");
                        textOnScreen("Joe: A chave ficou lá dentro.");
                        textOnScreen("Joe: Só, toma cuidado com a criatura.");
                        joeTalked = 1;
                    }
                        
                    } else {
                        textOnScreen("Ele olha sem parar para os lados, nervoso.");
                    }
                    
                    
                    break;
                case 4:
                    textOnScreen("Você entrou na casa...");
                    textOnScreen("O cheiro pútrido infesta suas narinas.");
                    playerLocation = 0;
                    casa(1, 3);
                    break;
                case 5:
                    textOnScreen("Você saiu da casa.");
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
                            joeTalked = 0; // Reseta a conversa com Joe
                            break;
                        }
                        textOnScreen("Você pegou a chave!");
                        
                    } else {
                        textOnScreen("Inventário cheio!");
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
                    textOnScreen("Uma pessoa está bloqueando o caminho!");
                    break;
                case 2:
                    tutorial(); 
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                case 4:
                    textOnScreen("Você entrou na casa!");
                    textOnScreen("O cheiro pútrido infesta suas narinas.");
                    playerLocation = 0;
                    casa(1, 3);
                    break;
                case 5:
                    textOnScreen("Você saiu da casa!");
                    playerLocation = 0;
                    vila(3, 4);
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
                        textOnScreen("Você pegou a chave!");
                        joeTalked = 0; // Reseta a conversa com Joe
                    } else {
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        textOnScreen("Inventário cheio!");
                    }
                    break;
                case 8:
                    textOnScreen("Você cai nos espinhos.");
                    textOnScreen("Seu corpo é perfurado em vários pontos vitais.");
                    textOnScreen("A dor é insuportável.");
                    textOnScreen("Você tenta se levantar, mas não consegue.");
                    textOnScreen("Lentamente, o mundo ao seu redor vai escurecendo.");
                    system("cls");
                    Sleep(2000);
                    respawnPlayer(); // Reseta o jogador para a vila
                    atualizarMatriz(); 
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
                case 15:   
                    if (hasHouseKey == 1) { // Se o jogador tiver a chave da vila
                        textOnScreen("Você destrancou a porta.");
                        textOnScreen("Uma sensação terrível invade seu corpo.");
                        map[newX][newY] = 16; // Muda o tile da porta trancada para porta destrancada
                    } else {
                        textOnScreen("Preciso de uma chave para abrir essa porta.");
                    }
                    monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                    monstersFollowStep(); // Move os monstros que seguem o jogador
                    atualizarMatriz(); 
                    break;
                case 16:
                    textOnScreen("Seu corpo tenta te impedir de entrar...");
                    textOnScreen("Porém, você prossegue.");
                    playerLocation = 0;
                    fase1(5, 1); // Chama a função fase1 com as coordenadas iniciais do jogador
                    break;
                case 17:
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
        setColor(13);
		printf ("==============================\n\n");
  	    printf ("V I R T U A   R U S H\n\n");
        printf ("1. J O G A R\n");
        printf ("2. C R É D I T O S\n");
        printf ("3. S A I R\n\n");
        printf ("==============================\n\n");
        setColor(7);
        scanf ("%d", &escolha); 		
	    system ("cls"); 
		
        switch (escolha) {
            case 1: 
                switch (playerLocation)
                {
                case 1:
                    vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
                    break;
                case 2:
                    casa(1, 3); // Chama a função casa com as coordenadas iniciais do jogador
                    break;
                case 3:
                    fase1(5, 1); // Chama a função fase1 com as coordenadas iniciais do jogador
                    break;
                case 4:
                    fase2(10, 10); // Chama a função fase2 com as coordenadas iniciais do jogador
                    break;
                default:
                    tutorial(); // Chama a função tutorial se o jogador estiver em uma localização desconhecida
                    break;
                }
                tutorial(); 
                break;
            case 2:
                Creditos();
                break;
            default:
                printf ("jogo desligado. . . \n"); 
                return 0;
                break;
	   }  
}

// ------------------ Funcao dos Creditos ------------------------------
void Creditos() {
    
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
	
      	setColor(13);
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
                    setColor(7);
					break;
				} if (menuQuitConfirm == 2) {
					system ("cls"); 
				    pausa();
                    setColor(7);
				}   break;
		}
        
    
    system ("cls");
    
	
}
// ======= funcoes de utilidade para o invent?rio ========
    // fun??o para exibir o invent?rio
    void exibirInventario() {
        system ("cls");
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
            printf("O pesadelo ainda não acabou.\n\n");
            system("pause");
            vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
        }

        void textOnScreen(const char* text) {
            system("cls");      // Limpa a tela
            exibirMatriz();     // Exibe a matriz atualizada
            printf("\n\n                                    %s\n\n", text); // Mostra a mensagem
            system("pause");    // Espera o jogador apertar uma tecla
            system("cls");      // Limpa novamente para evitar sobreposição
            exibirMatriz();     // Exibe a matriz novamente após a mensagem
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
	srand (time(NULL)); // Inicializa o gerador de n?meros aleat?rios
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    mainMenu();
}