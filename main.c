#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>


#define tamX 15
#define tamY 15

int verificar_ao_redor(int matriz[tamX][tamY],int x, int y){
  int val = matriz[x][y];
  int soma;
  //################################# cantos #################################
  if (x == 0 && y == 0)
    soma = matriz[x][y+1] + matriz[x+1][y] + matriz[x+1][y+1];

  else if(x == tamX-1 && y == tamY-1)
    soma = matriz[x][y-1] + matriz[x-1][y] + matriz[x-1][y-1];

  else if(x == tamX-1 && y == 0)
    soma = matriz[x][y+1] + matriz[x-1][y] + matriz[x-1][y+1];

  else if(x == 0 && y == tamY-1)
    soma = matriz[x][y-1] + matriz[x+1][y] + matriz[x+1][y-1];
  //################################# cantos #################################
  //################################# bordas #################################
  else if(x == 0)
      soma = matriz[x][y-1] + matriz[x][y+1] + matriz[x+1][y] + matriz[x+1][y-1] + matriz[x+1][y+1];

  else if(y == 0)
      soma = matriz[x-1][y] + matriz[x+1][y] + matriz[x][y+1] + matriz[x-1][y+1] + matriz[x+1][y+1];

  else if(x == tamX-1)
      soma = matriz[x][y-1] + matriz[x][y+1] + matriz[x-1][y] + matriz[x-1][y-1] + matriz[x-1][y+1];

  else if(y == tamY-1)
      soma = matriz[x-1][y] + matriz[x+1][y] + matriz[x][y-1] + matriz[x-1][y-1] + matriz[x+1][y-1];
  //################################# bordas #################################
  //################################# meios #################################
  else
    soma = matriz[x+1][y-1] + matriz[x][y-1]
		 + matriz[x-1][y-1] + matriz[x+1][y]
		 + matriz[x+1][y+1] + matriz[x-1][y]
		 + matriz[x-1][y+1] + matriz[x][y+1];
  //################################# meios #################################
  if (val == 0){
    if (soma == 3)
      return 1;
      return 0;
  }
  if(soma < 2 || soma > 3) return 0;
  return 1;
}

void exibir_matriz_com_jogador(int matriz[tamX][tamY], int x, int y) {
	int i,j;
    for (i = 0; i < tamX; i++) {
        for (j = 0; j < tamY; j++) {
            if (i == x && j == y)
                printf("P "); // PosiÃ§Ã£o do jogador
            else
                printf("%c ",matriz[i][j]*49+32*(1+(-1*matriz[i][j])));
        }
        printf("\n");
    }
}

void navegar_e_modificar_matriz(int matriz[tamX][tamY]) {
    int x = 0, y = 0;
    char comando;

    exibir_matriz_com_jogador(matriz, x, y);

    while (1) {
        comando = _getch();
        system("cls"); // Use "cls" para Windows e "clear" no linux

        if (comando == 'q')
            break;

        switch (comando) {
            case 'w':
                if (x > 0) x--;
                break;
            case 's':
                if (x < tamX - 1) x++;
                break;
            case 'a':
                if (y > 0) y--;
                break;
            case 'd':
                if (y < tamY - 1) y++;
                break;
            case 'e':
            	printf("A cÃ©lula atual [%d][%d] Ã© %d. Alternando valor...\n", x, y, matriz[x][y]);
                matriz[x][y] = (matriz[x][y] == 0) ? 1 : 0; // Alterna entre 0 e 1
                break;
            default:
                printf("Comando invÃ¡lido! Use WASD para se mover, E para editar, e Q para sair.\n");
                break;
        }
        exibir_matriz_com_jogador(matriz, x, y);
    }
}

void exibir_matriz(int matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i < tamX; i++){
    for(j = 0; j < tamY; j++){
      printf("%c ",matriz[i][j]*49+32*(1+(-1*matriz[i][j])));
    }
    printf("\n");
  }
}

void copiar_matriz(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i < tamX; i++)
    for(j = 0; j < tamY; j++)
      matriz[i][j] = nova_matriz[i][j];
}

void ciclar_matriz(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i < tamX; i++)
    for(j = 0; j < tamY; j++)
      nova_matriz[i][j] = verificar_ao_redor(matriz, i,j);
}

void rodar_jogo(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){ //roda o programa 1 rodada
    ciclar_matriz(matriz,nova_matriz); 
    copiar_matriz(matriz,nova_matriz);
    exibir_matriz(matriz);
}

int main(void) {
  int matriz[tamX][tamY] = {0};
  int nova_matriz[tamX][tamY] = {0};
  int a;
  navegar_e_modificar_matriz(matriz);
  exibir_matriz(matriz); 
  
  
  int i;
  for(i = 0; i < 100; i++) {
  	rodar_jogo(matriz,nova_matriz); 
 	Sleep(750); 
 	system("cls");
  }
  	
  
  return 0;
}
