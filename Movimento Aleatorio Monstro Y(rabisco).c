void randomMovementMonsterY() {
	
	rand() % 4 //0,1,2,3 
	
	switc (rand()) {
		
		case 0:
			monsterBY--; //cima
			break;
		case 1:
			monsterBX--; //direita
			break;
		case 2:
			monsterBY--; //baixo
			break;
		case 3:
			monsterBX--; //esquerda
			break;
		
		
	}
	
}
