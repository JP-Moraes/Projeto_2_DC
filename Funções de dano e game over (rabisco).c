int MAX_HP = 3;
int Current_HP = MAX_HP; 

void damagePLAYER(int DMG) {

Current_HP -= DMG; //Recebe o aumento ou diminuição de HP

if (Current_HP > 0) {
	printf ("HP has been decreased"); 
	
	
} else (Current_HP <= 0) {
	printf ("You died"); 
	gameover(); 
	
  }
}

void gameOver() {
	
	system ("cls"); 
	printf ("You've failed in your task to leave the game. . ."); 
	main(); //retorna para o menu principal
	
}