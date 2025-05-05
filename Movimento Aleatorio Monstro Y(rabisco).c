void randomMovementMonsterY() {
	
	rand() % 4 //0,1,2,3 
	
	switc (rand()) {
		
		case 0:
			monsterBY--; //cima
			break;
		case 1:
			monsterBX--; //direita
			break;
		case 0:
			monsterBY--; //baixo
			break;
		case 0:
			monsterBX--; //esquerda
			break;
		
		
	}
	
}