#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>

#define espinhos1 8 // Espinhos horizontais
#define espinhos2 9 // Espinhos horizontais2
#define alavancaEspinhos1 18 // Alavanca de espinhos
#define alavancaEspinhos2 19 // Alavanca de espinhos2
#define alavancaReversaItem1 20 // Alavanca de espinhos Reversa
#define alavancaReversaItem2 21 // Alavanca de espinhos Reversa2
#define espinhosReversos1 22 // Espinhos reversos1
#define espinhosReversos2 23 // Espinhos reversos2
// ------ Setup do jogo ------

    //---- Variaveis globais ----

        int i; // Variável de controle
        int j; // Variável de controle
        int playerInputPermission = 1; // Variável que controla a entrada do jogador

        //----- Variaveis Base do Jogador ------
        int itemCount = 0; // Contador de itens no inventário
        int inventory[10]; // Array para o inventário
        int inventorySize = 10; // Tamanho do inventário
        int item;
        int playerLocation = 0;
        int playerFacing = 0; // Direção que o jogador está olhando
        // 0 = Cima, 1 = Esquerda, 2 = Baixo, 3 = Direita

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
        
        //----- Level Data -----
        int espinhosAtivos = 1; // Vari?vel para verificar se os espinhos est?o ativos ou inativos
        int espinhosAtivos2 = 1; // Vari?vel para verificar se os espinhos2 est?o ativos ou inativos
        int portalAtivo = 0; // Vari?vel para verificar se o portal est? ativo ou inativo
        int alavancaReversa = 0; // Vari?vel para verificar se a alavanca reversa est? ativa ou inativa
        int alavancaReversa2 = 0; // Vari?vel para verificar se a alavanca reversa2 est? ativa ou inativa

        //----- Menu Data -----
        int menuOpen = 0; // Vari?vel para verificar se o menu est? aberto ou fechado
        int selectedOption = 0; // Vari?vel para verificar a op??o selecionada no menu
        int optionsCount = 0; // Contador de op??es no menu
        int options[10]; // Array para armazenar as op??es do menu

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
void moveTheRandomCreature(int *creatureX, int *creatureY);
void monstersRandomStep();
void monstersFollowStep();
void respawnPlayer();



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
            if (x == playerX && y == playerY || x == monsterRandomX2 && y == monsterRandomY2 || x == monsterRandomX && y == monsterRandomY || x == monsterFollowX && y == monsterFollowY || x == monsterFollowX2 && y == monsterFollowY2) {
                if (x == monsterRandomX && y == monsterRandomY) { // Se for a criatura que se move aleatoriamente
                    printf("\033[31m @ \033[0m"); // Criatura que se move aleatoriamente
                } else if (x == monsterRandomX2 && y == monsterRandomY2) { // Se for a criatura que se move aleatoriamente
                    printf("\033[31m @ \033[0m"); // Criatura que se move aleatoriamente
                } else if (x == monsterFollowX && y == monsterFollowY) { // Se for a criatura que segue o jogador
                    printf("\033[31m(-)\033[0m"); // Criatura que segue o jogador
                } else if (x == monsterFollowX2 && y == monsterFollowY2) { // Se for a criatura que segue o jogador e atravessa o mapa
                    printf("\033[31m(O)\033[0m"); // Persegue e atravessa o mapa
                }
                 else if (x == playerX && y == playerY) {
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
                            printf(".o.");  // NPC
                            break;
                        case 4:
                            printf("\033[33mT T\033[0m");  // Porta de entrada
                            break;
                        case 5:
                            printf("\033[33mT T\033[0m");  // Porta de saída
                            break;
                        case 6:
                            printf("\033[93m K \033[0m");  // Chave
                            break;
                        case 7:
                            printf("\033[94m<O>\033[0m");  // Monstro que segue o jogador
                            break;
                        case 8:
                            if (espinhosAtivos == 1) {
                                printf("\033[31mXXX\033[0m");  // Espinhos ativos
                            } else {
                                printf("\033[90mxxx\033[0m");  // Espinhos inativos
                            }
                            break;
                        case 9:
                            if (espinhosAtivos2 == 1) {
                                printf("\033[31mXXX\033[0m");  // Espinhos ativos
                            } else {
                                printf("\033[90mxxx\033[0m");  // Espinhos inativos
                            }
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
                            printf("\033[95mT+T\033[0m"); // Porta Trancada
                            break;
                        case 16:
                            printf("\033[95mT T\033[0m"); // Porta Destrancada
                            break;
                        case 17:   
                            printf("\033[90m###\033[0m"); // Canto do mapa
                            break;
                        case 18:
                            if (espinhosAtivos == 1)
                                printf("\033[93m_/_\033[0m"); // Alavanca de espinhos
                            else
                                printf("\033[93m_\\_\033[0m"); // Alavanca de espinhos
                            break;
                        case 19:
                            if (espinhosAtivos2 == 1)
                                printf("\033[93m_/_\033[0m"); // Alavanca de espinhos2
                            else
                                printf("\033[93m_\\_\033[0m"); // Alavanca de espinhos2
                            break;
                        case 20:
                            if (alavancaReversa == 1)
                                printf("\033[93m_/_\033[0m"); // Alavanca de espinhos Reversa
                            else
                                printf("\033[93m_\\_\033[0m"); // Alavanca de espinhos Reversa
                            break;
                        case 21:
                            if (alavancaReversa2 == 1)
                                printf("\033[93m_/_\033[0m"); // Alavanca de espinhos Reversa2
                            else
                                printf("\033[93m_\\_\033[0m"); // Alavanca de espinhos Reversa2
                            break;
                        case 22:
                            if (espinhosAtivos == 0) {
                                printf("\033[31mXXX\033[0m");  // Espinhos reversos1 ativos
                            } else {
                                printf("\033[90mxxx\033[0m");  // Espinhos reversos1 inativos
                            }
                            break;
                        case 23:
                            if (espinhosAtivos2 == 0) {
                                printf("\033[31mXXX\033[0m");  // Espinhos reversos2 ativos
                            } else {
                                printf("\033[90mxxx\033[0m");  // Espinhos reversos2 inativos
                            }
                            break;
                        case 24:
                            printf("\033[93m___\033[0m"); // Botão1
                            break;
                        case 25:
                            printf("\033[93m___\033[0m"); // Botão2
                            break;
                        case 26:
                            printf("\033[93m(~)\033[0m");// Portal1
                            break;
                        case 27:
                            printf("\033[93m(~)\033[0m");// Portal2
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
    espinhosAtivos = 1; // Reseta os espinhos para ativos
    espinhosAtivos2 = 1; // Reseta os espinhos2 para ativos
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

    // Paredes
    drawFrom(0, 0, 0, 19, 17); // Esquerda
    drawFrom(0, 0, 14, 0, 17); // Topo
    drawFrom(14, 0, 14, 19, 17); // Direita
    drawFrom(0, 19, 14, 19, 17); // Base

    // Espinhos horizontais (linha 6 e 13)
    drawFrom(6, 6, 13, 6, 8);  // Espinhos 1
    drawFrom(1, 6, 5, 6, 9);  // Espinhos 2
    drawFrom(5, 6, 5, 12, 9);  // Espinhos 2
    drawFrom(6, 6, 6, 12, 8);  // Espinhos 2
    drawFrom(5, 13, 13, 13, espinhosReversos1); // Espinhos 2
    drawFrom(1, 13, 5, 13, 11); // Parede
    map[3][8] = 18; // Alavanca de espinhos 1
    map[3][12] = 6;//chave

    // Alavancas próximas dos espinhos
    map[1][5] = 18;  // Alavanca para espinhos 1 (linha 6)
    map[13][10] = 18; // Alavanca para espinhos 1 (linha 13)
    map[13][12] = 19; // Alavanca para espinhos 2 (linha 13)
    map[6][18] = 15; // Porta trancada
    
    atualizarMatriz();
}
void fase2(int newPlayerX, int newPlayerY) {
    espinhosAtivos = 1; // Reseta os espinhos para ativos
    espinhosAtivos2 = 1; // Reseta os espinhos2 para ativos
	playerLocation = 4;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 20;
	width = 20;
	inicializarMatriz();
    drawFrom(0, 0, 0, 19, 17); // Esquerda
    drawFrom(0, 0, 19, 0, 17); // Topo
    drawFrom(19, 0, 19, 19, 17); // Direita
    drawFrom(0, 19, 19, 19, 17); // Base
    
    drawFrom(4, 1, 4, 3, espinhosReversos1);
    drawFrom(5, 7, 9, 7, espinhosReversos1);
    drawFrom(4, 4, 4, 18, 11); //parede
    drawFrom(4, 14, 4, 17, espinhosReversos2); 
    drawFrom(1, 10, 3, 10, espinhos1);
    drawFrom(1, 2, 2, 2, espinhos1);
    map[1][2] = espinhos1;
    drawFrom(2, 1, 2, 1, espinhos1);
    drawFrom(10, 1, 10, 6, espinhos2); // Espinhos

    drawFrom(10, 7, 10, 15, 11); // Parede
    monsterRandomX = 14; // Coordenada X do monstro que se move aleatoriamente
    monsterRandomX2 = 16; // Coordenada X do monstro que se move aleatoriamente
    monsterRandomY = 10; // Coordenada Y do monstro que se move aleatoriamente
    monsterRandomY2 = 10; // Coordenada Y do monstro que se move aleatoriamente

    map[7][3] = alavancaEspinhos1; // Alavanca de espinhos1
    map[7][10] = alavancaEspinhos2; // Alavanca de espinhos2

    drawFrom(5, 13, 9, 13, espinhos1);

    map[1][1] = 6;
    map[18][9] = 15; // Porta trancada

	atualizarMatriz();
}
void fase3(int newPlayerX, int newPlayerY) {
    espinhosAtivos = 1; // Reseta os espinhos para ativos
    espinhosAtivos2 = 1; // Reseta os espinhos2 para ativos
	playerLocation = 5;
    playerX = newPlayerX;
    playerY = newPlayerY;
	height = 40;
	width = 40;
	inicializarMatriz();
    drawFrom(0, 0, 0, 39, 17); // Esquerda
    drawFrom(0, 0, 39, 0, 17); // Topo
    drawFrom(39, 0, 39, 39, 17); // Direita
    drawFrom(0, 39, 39, 39, 17); // Base
    drawFrom(4, 1, 8, 20, 11); // Parede
    drawFrom(4, 26, 8, 38, 11); // Parede
    drawFrom(4, 21, 4, 25, espinhosReversos1); // Espinhos Reversos1
    drawFrom(8, 1, 12, 20, 11); // Parede
    drawFrom(8, 26, 12, 38, 11); // Parede
    drawFrom(8, 21, 8, 25, espinhos1); // Espinhos1
    drawFrom(12, 1, 12, 20, 11); // Parede
    drawFrom(12, 26, 12, 38, 11); // Parede
    drawFrom(12, 21, 12, 25, espinhos2); // Espinhos2
    map[10][21] = 26; // Portal 1
    map[6][23] = alavancaEspinhos1; // Alavanca de espinhos1
    map[29][23] = alavancaEspinhos2; // Alavanca de espinhos2

    drawFrom(31, 1, 35, 20, 11); // Parede
    drawFrom(31, 26, 35, 38, 11); // Parede
    drawFrom(35, 21, 35, 25, espinhosReversos1); // Espinhos Reversos1
    drawFrom(31, 1, 12, 20, 11); // Parede
    drawFrom(31, 26, 12, 38, 11); // Parede
    drawFrom(35, 21, 35, 25, espinhos1); // Espinhos1
    drawFrom(27, 1, 31, 20, 11); // Parede
    drawFrom(27, 26, 31, 38, 11); // Parede
    drawFrom(31, 21, 31, 25, espinhos2); // Espinhos1
    map[33][23] = 6;   
    drawFrom(27, 1, 23, 20, 11); // Parede
    drawFrom(27, 26, 23, 38, 11); // Parede
    drawFrom(27, 21, 27, 25, 11); // Espinhos1
    monsterFollowX = 22; // Coordenada X do monstro que segue o jogador
    monsterFollowX2 = 23; // Coordenada X do monstro que segue o jogador e atravessa o mapa
    monsterFollowY = 20; // Coordenada Y do monstro que segue o jogador
    monsterFollowY2 = 20; // Coordenada Y do monstro que segue o jogador e atravessa o mapa
    map[29][21] = 27; // Portal 2
    map[16][20] = 15;
    

	atualizarMatriz();
}

void tutorial()
{
    system ("cls"); 
	
	if (tutorialShown == 0)  {
		
        setColor(13);
		printf ("\n");
		printf ("?: Use W,A,S,D para movimentar\n");
		printf ("?: Pressione P para pausar o jogo quando quiser\n");
		printf ("?: Pressione E para interagir com objetos em sua frente\n");
        printf ("?: Pressione I para abrir o inventário\n");
        printf ("?: E salve ele.\n");
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
    while (playerInputPermission == 1)  // playerInput é a variável que controla o loop de entrada do jogador
    {
        // playerFacing é a direção que o jogador está olhando, de acordo com o comando. E W, A, S, D são as teclas de movimentação.
        // playerX e playerY são as coordenadas do jogador na matriz.
        if (menuOpen == 0) { // Verifica se o menu não está aberto
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
                            textOnScreen("Joe: Volta logo por favor.");
                            textOnScreen("Joe: Eu não sei o que pode acontecer se o monstro se irritar.");
                            joeTalked = 1;
                        } else {
                            textOnScreen("Joe: Você vai mesmo descer, irmão..?");
                            textOnScreen("Joe: Isso é loucura...");
                            textOnScreen("Joe: Mas se é mesmo o único jeito de acabar com isso...");
                            textOnScreen("Joe: A chave ficou lá dentro.");
                            textOnScreen("Joe: Só, toma cuidado com o monstro.");
                            textOnScreen("Joe: Ele me bateu. Pode bater em você também.");
                            joeTalked = 1;
                        }
                            
                        } else {
                            textOnScreen("Ele olha sem parar para os lados, nervoso.");
                            textOnScreen("Não posso permitir que isso continue assim.");
                            textOnScreen("Vou te salvar, maninho.");
                        }
                        
                        
                        break;
                    case 4:
                        textOnScreen("Você entrou na casa...");
                        textOnScreen("O cheiro pútrido infesta suas narinas.");
                        textOnScreen("A criatura está ali, como sempre esteve.");
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
                    case 18:
                        if (espinhosAtivos == 1) {
                            espinhosAtivos = 0; // Desativa os espinhos
                        } else {
                            espinhosAtivos = 1; // Ativa os espinhos
                        }
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 19:
                        if (espinhosAtivos2 == 1) {
                            espinhosAtivos2 = 0; // Desativa os espinhos
                        } else {
                            espinhosAtivos2 = 1; // Ativa os espinhos
                        }
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 20:
                        if (alavancaReversa == 1) {
                            alavancaReversa = 0; // Desativa a alavanca reversa
                        } else {
                            alavancaReversa = 1; // Ativa a alavanca reversa
                        }
                        if (espinhosAtivos == 1) {
                                espinhosAtivos = 0; // Desativa os espinhos
                            } else {
                                espinhosAtivos = 1; // Ativa os espinhos
                            }
                    case 21:
                        if (alavancaReversa2 == 1) {
                            alavancaReversa2 = 0; // Desativa a alavanca reversa
                        } else {
                            alavancaReversa2 = 1; // Ativa a alavanca reversa
                        }
                        if (espinhosAtivos2 == 1) {
                                espinhosAtivos2 = 0; // Desativa os espinhos
                            } else {
                                espinhosAtivos2 = 1; // Ativa os espinhos
                            }
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
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
                        textOnScreen("A criatura está ali, como sempre esteve.");
                        playerLocation = 0;
                        casa(1, 3);
                        break;
                    case 5:
                        textOnScreen("Você saiu da casa!");
                        playerLocation = 0;
                        vila(3, 4);
                        break;
                    case 6:

                        if (addItem(3)) { // Adiciona a chave ao inventário
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
                        if (espinhosAtivos == 1) {
                            textOnScreen("Você cai nos espinhos.");
                            textOnScreen("Seu corpo é perfurado em vários pontos vitais.");
                            textOnScreen("A dor é insuportável.");
                            textOnScreen("Você tenta se levantar, mas não consegue.");
                            textOnScreen("Se engasgando com seu próprio sangue, você perde as forças.");
                            textOnScreen("Lentamente, o mundo ao seu redor vai escurecendo.");
                            system("cls");
                            Sleep(2000);
                            respawnPlayer(); // Reseta o jogador para a vila
                            atualizarMatriz(); 
                        } else {
                            playerX = newX;
                            playerY = newY;
                            monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                            monstersFollowStep(); // Move os monstros que seguem o jogador
                            atualizarMatriz(); 
                        }
                        break;
                    case 9:
                        if (espinhosAtivos2 == 1) {
                            textOnScreen("Você cai nos espinhos.");
                            textOnScreen("Seu corpo é perfurado em vários pontos vitais.");
                            textOnScreen("A dor é insuportável.");
                            textOnScreen("Você tenta se levantar, mas não consegue.");
                            textOnScreen("Se engasgando com seu próprio sangue, você perde as forças.");
                            textOnScreen("Lentamente, o mundo ao seu redor vai escurecendo.");
                            system("cls");
                            Sleep(2000);
                            respawnPlayer(); // Reseta o jogador para a vila
                            atualizarMatriz(); 
                        } else {
                            playerX = newX;
                            playerY = newY;
                            monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                            monstersFollowStep(); // Move os monstros que seguem o jogador
                            atualizarMatriz(); 
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
                    case 15:   
                        switch (playerLocation)
                        {
                        case 1:
                            if (hasItem(3) == 1) {
                                textOnScreen("Você destrancou a porta.");
                                textOnScreen("Um mau presságio invade seu corpo.");
                                removeItem(3); // Remove a chave do inventário
                                map[newX][newY] = 16; // Muda o tile da porta trancada para porta destrancada
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            } else {
                                textOnScreen("Preciso de uma chave para abrir essa porta.");
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            }
                            break;
                        case 3:
                            if (hasItem(3) == 1) {
                                textOnScreen("Você destrancou a porta.");
                                textOnScreen("Sua mão treme sem parar.");
                                removeItem(3); // Remove a chave do inventário
                                map[newX][newY] = 16; // Muda o tile da porta trancada para porta destrancada
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            } else {
                                textOnScreen("Preciso de uma chave para abrir essa porta.");
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            }
                        case 4:
                            if (hasItem(3) == 1) {
                                textOnScreen("Você destrancou a porta.");
                                textOnScreen("Você está mesmo fazendo isso por ele?");
                                removeItem(3); // Remove a chave do inventário
                                map[newX][newY] = 16; // Muda o tile da porta trancada para porta destrancada
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            } else {
                                textOnScreen("Preciso de uma chave para abrir essa porta.");
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            }
                        case 5:
                            if (hasItem(3) == 1) {
                                textOnScreen("Você destrancou a porta.");
                                textOnScreen("É agora, não é?");
                                removeItem(3); // Remove a chave do inventário
                                map[newX][newY] = 16; // Muda o tile da porta trancada para porta destrancada
                                atualizarMatriz(); 
                            } else {
                                textOnScreen("Preciso de uma chave para abrir essa porta.");
                                monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                                monstersFollowStep(); // Move os monstros que seguem o jogador
                                atualizarMatriz(); 
                            }
                        default:
                            break;
                        }
                            
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 16:
                        switch (playerLocation)
                        {
                        case 1:
                            textOnScreen("Seu corpo tenta te impedir de entrar...");
                            textOnScreen("Ele já sabe o que vai acontecer.");
                            textOnScreen("Porém, você prossegue.");
                            playerLocation = 0;
                            fase1(5, 1); // Chama a função fase1 com as coordenadas iniciais do jogador
                            break;
                        case 3:
                            textOnScreen("Seu corpo por um instante parece negar seu movimento...");
                            textOnScreen("Não tem mais volta.");
                            textOnScreen("Você prossegue.");
                            playerLocation = 4; // Muda a localização do jogador para fase 2
                            fase2(2, 4); // Chama a função fase1 com as coordenadas iniciais do jogador
                            break;
                        case 4:
                            textOnScreen("Por ele, você faria qualquer coisa.");
                            textOnScreen("Você sabe que não tem volta.");
                            textOnScreen("Você prossegue.");
                            playerLocation = 5; // Muda a localização do jogador para fase 3
                            fase3(2,20); // Chama a função fase1 com as coordenadas iniciais do jogador
                            break;
                        case 5:
                            textOnScreen("Você sente que está perto do fim.");
                            textOnScreen("Por ele, você faria qualquer coisa.");
                            textOnScreen("Você prossegue.");
                            textOnScreen("Até que...");
                            textOnScreen("Uma luz ofusca sua visão.");
                            textOnScreen("Uma buzina estridente ecoa por todo o lugar.");
                            system("cls");
                            Sleep(2000);
                            textOnClearScreen("Você fez tudo o que podia.");
                            textOnClearScreen("Não há mais nada que possa fazer.");
                            textOnClearScreen("Aceite o que aconteceu.");
                            textOnClearScreen("Você não pode mudar o passado.");
                            textOnClearScreen("Você não pode mudar o que aconteceu.");
                            textOnClearScreen("Você não pode mudar o que aconteceu com ele.");
                            textOnClearScreen("Você não pode mudar o que aconteceu com você.");
                            textOnClearScreen("Você não pode mudar o que aconteceu com vocês.");
                            textOnClearScreen("Você está morto.");
                            system("cls");
                            Sleep(2000);
                            printf("1. Aceitar\n2. Recomeçar\n");
                            int choice;
                            scanf("%d", &choice);
                            if (choice == 1) {
                                Creditos();
                            } else if (choice == 2) {
                                textOnScreen("Você sabe que não pode mudar o passado.");
                                textOnScreen("Pare de se torturar.");
                                system("cls");
                                tutorial();
                            }
                            Creditos();
                            break;
                        }
                    case 17:
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 18:
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 19:
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 20:
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 21:
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 22:
                        if (espinhosAtivos == 0) {
                            textOnScreen("Você cai nos espinhos.");
                            textOnScreen("Seu corpo é perfurado em vários pontos vitais.");
                            textOnScreen("A dor é insuportável.");
                            textOnScreen("Você tenta se levantar, mas não consegue.");
                            textOnScreen("Se engasgando com seu próprio sangue, você perde as forças.");
                            textOnScreen("Lentamente, o mundo ao seu redor vai escurecendo.");
                            system("cls");
                            Sleep(2000);
                            respawnPlayer(); // Reseta o jogador para a vila
                            atualizarMatriz(); 
                        } else {
                            playerX = newX;
                            playerY = newY;
                            monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                            monstersFollowStep(); // Move os monstros que seguem o jogador
                            atualizarMatriz(); 
                        }
                        break;
                    case 23:
                        if (espinhosAtivos2 == 0) {
                            textOnScreen("Você cai nos espinhos.");
                            textOnScreen("Seu corpo é perfurado em vários pontos vitais.");
                            textOnScreen("A dor é insuportável.");
                            textOnScreen("Você tenta se levantar, mas não consegue.");
                            textOnScreen("Se engasgando com seu próprio sangue, você perde as forças.");
                            textOnScreen("Lentamente, o mundo ao seu redor vai escurecendo.");
                            system("cls");
                            Sleep(2000);
                            respawnPlayer(); // Reseta o jogador para a vila
                            atualizarMatriz(); 
                        } else {
                            playerX = newX;
                            playerY = newY;
                            monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                            monstersFollowStep(); // Move os monstros que seguem o jogador
                            atualizarMatriz(); 
                        }
                        break;
                    case 24:
                        if (espinhosAtivos == 1) {
                            espinhosAtivos = 0; // Desativa os espinhos
                        } else {
                            espinhosAtivos = 1; // Ativa os espinhos
                        }
                        playerX = newX;
                        playerY = newY;
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 25:
                        if (espinhosAtivos2 == 1) {
                            espinhosAtivos2 = 0; // Desativa os espinhos
                        } else {
                            espinhosAtivos2 = 1; // Ativa os espinhos
                        }
                        playerX = newX;
                        playerY = newY;
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                        break;
                    case 26:
                        playerX = 29;
                        playerY = 22;
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
                    case 27:
                        playerX = 10;
                        playerY = 22;
                        monstersRandomStep(); // Move os monstros que se movem aleatoriamente
                        monstersFollowStep(); // Move os monstros que seguem o jogador
                        atualizarMatriz(); 
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
        } else {
            // Se o menu estiver aberto, aguarda a escolha do jogador
            if (_kbhit()) {
                char comando = _getch();
                if (comando == 'w' || comando == 'W') {
                    if (selectedOption < optionsCount - 1 && selectedOption >= 0) {
                        selectedOption++; // Move para a próxima opção
                    }   
                } else if (comando == 's' || comando == 'S') {
                    if (selectedOption < optionsCount - 1 && selectedOption >= 0) {
                        selectedOption--; // Move para a opção anterior
                    }
                } else if (comando == 13) { // Se pressionar Enter
                    options[selectedOption] = 1; // Marca a opção selecionada como 1
                }
                
            }
        }
    }
}

// ------------------ Menu Principal -------------------
void mainMenu() {
        escolha = 0;
        setColor(13);
		printf ("                   ==============================\n\n");
  	    printf ("                   SEM SAÍDA\n\n");
        printf ("                   1. J O G A R\n");
        printf ("                   2. C R É D I T O S\n");
        printf ("                   3. S A I R\n\n");
        printf ("                   ===============================\n\n");
        setColor(7);
        scanf ("%d", &escolha); 		
	    system ("cls"); 
		
        switch (escolha) {
            case 1: 
                menuOpen = 0; // Menu Fechado
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
                    fase2(2, 4); // Chama a função fase2 com as coordenadas iniciais do jogador
                    break;
                case 5:
                    fase3(2,20); // Chama a função fase3 com as coordenadas iniciais do jogador
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
    
        printf ("                   ===========================================\n");
        printf ("                   D E S E N V O L V E D O R E S:\n\n");
        printf ("                   . J O Ã O  P E D R O  M O R A E S\n\n");
        printf ("                       Sistema de Movimentação, mapa e interação base.\n");
        printf ("                   . J O Ã O  H E N R I Q U E  P I N H E I R O\n\n");
        printf ("                       Todo o Resto\n");
        printf ("                   ============================================\n");
        system ("pause");
        system ("cls");
        mainMenu();
}

// --------- Funcao de Pausa do jogo -----------
void pausa(){
	
	system ("cls");
        menuOpen = 1; // Abre o menu de pausa

      	setColor(13);
        printf ("                   ==== Menu ====================\n\n");
        printf ("                   1. Continuar\n");
        printf ("                   2. voltar para o menu principal\n\n");
        printf ("                   ============================== \n");
        switch (menuDePause) {
			case 1:
                menuOpen = 0; // Fecha o menu de pausa
				return;
				break;
			case 2:
				system ("cls");
                printf ("                   =======================\n\n");
				printf ("                   Você quer mesmo sair?\n");
				printf ("                   Sim\n");
				printf ("                   Não\n");
				printf ("                   ========================\n\n");
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
                int monsterNextX = monsterFollowX;
                int monsterNextY = monsterFollowY;
                if (monsterFollowX < playerX) monsterNextX++;
                else if (monsterFollowX > playerX) monsterNextX--;
                else if (monsterFollowY < playerY) monsterNextY++;
                else if (monsterFollowY > playerY) monsterNextY--;
                if (map[monsterNextX][monsterNextY] == 0) {
                    monsterFollowX = monsterNextX;
                    monsterFollowY = monsterNextY;
                } else if (monsterNextX == playerX && monsterNextY == playerY) {
                    respawnPlayer(); // Se o monstro colidir com um NPC, reseta o jogador
                }
            }

            // Move o monstro que segue e atravessa o mapa
            if (monsterFollowX2 != 999 && monsterFollowY2 != 999) {
                if (monsterFollowX2 < playerX) monsterFollowX2++;
                else if (monsterFollowX2 > playerX) monsterFollowX2--;
                else if (monsterFollowY2 < playerY) monsterFollowY2++;
                else if (monsterFollowY2 > playerY) monsterFollowY2--;
            }
        }

        void respawnPlayer() {
            if(playerLocation == 1) {
                vila(5, 5); // Reseta a posi??o do jogador para a vila
            } else if (playerLocation == 2) {
                casa(1, 3); // Reseta a posi??o do jogador para a casa
            } else if (playerLocation == 3) {
                fase1(5, 1); // Reseta a posi??o do jogador para a fase 1
            } else if (playerLocation == 4) {
                fase2(2, 4); // Reseta a posi??o do jogador para a fase 2
            } else if (playerLocation == 5) {
                fase3(2,20);
            } else {
                vila(5, 5); // Reseta a posi??o do jogador para a vila por padr??o
            }
            printf("Ainda não posso desistir.\n\n");
            system("pause");
            vila(5, 5); // Chama a função vila com as coordenadas iniciais do jogador
        }

        void textOnScreen(const char* text) {
            system("cls");      // Limpa a tela
            exibirMatriz();     // Exibe a matriz atualizada
            printf("\n\n                                    %s\n\n\n", text); // Mostra a mensagem
            system("pause");    // Espera o jogador apertar uma tecla
            system("cls");      // Limpa novamente para evitar sobreposição
            exibirMatriz();     // Exibe a matriz novamente após a mensagem
        }
        void textOnClearScreen(const char* text) {
            system("cls");      // Limpa a tela
            printf("\n\n                                    %s\n\n\n", text); // Mostra a mensagem
            system("pause");    // Espera o jogador apertar uma tecla
            system("cls");      // Limpa novamente para evitar sobreposição
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