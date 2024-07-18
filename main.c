#include stdio.h
#include stdlib.h
#include unistd.h


#define tamX 50
#define tamY 50

int verificar_ao_redor(int matriz[tamX][tamY],int x, int y){
  int val = matriz[x][y];
  int soma;
  ################################# cantos #################################
  if (x == 0 && y == 0)
    soma = matriz[x][y+1] + matriz[x+1][y] + matriz[x+1][y+1];

  else if(x == tamX-1 && y == tamY-1)
    soma = matriz[x][y-1] + matriz[x-1][y] + matriz[x-1][y-1];

  else if(x == tamX-1 && y == 0)
    soma = matriz[x][y+1] + matriz[x-1][y] + matriz[x-1][y+1];

  else if(x == 0 && y == tamY-1)
    soma = matriz[x][y-1] + matriz[x+1][y] + matriz[x+1][y-1];
  ################################# cantos #################################
  ################################# bordas #################################
  else if(x == 0)
      soma = matriz[x][y-1] + matriz[x][y+1] + matriz[x+1][y] + matriz[x+1][y-1] + matriz[x+1][y+1];

  else if(y == 0)
      soma = matriz[x-1][y] + matriz[x+1][y] + matriz[x][y+1] + matriz[x-1][y+1] + matriz[x+1][y+1];

  else if(x == tamX-1)
      soma = matriz[x][y-1] + matriz[x][y+1] + matriz[x-1][y] + matriz[x-1][y-1] + matriz[x-1][y+1];

  else if(y == tamY-1)
      soma = matriz[x-1][y] + matriz[x+1][y] + matriz[x][y-1] + matriz[x-1][y-1] + matriz[x+1][y-1];
  ################################# bordas #################################
  ################################# meios #################################
  else
    soma = matriz[x+1][y-1] + matriz[x][y-1]
		 + matriz[x-1][y-1] + matriz[x+1][y]
		 + matriz[x+1][y+1] + matriz[x-1][y]
		 + matriz[x-1][y+1] + matriz[x][y+1];
  ################################# meios #################################
  if (val == 0){
    if (soma == 3)
      return 1;
      return 0;
  }
  if(soma  2  soma  3) return 0;
  return 1;
}

void exibir_matriz(int matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i  tamX; i++){
    for(j = 0; j  tamY; j++){
      printf(%d ,matriz[i][j]);
    }
    printf(n);
  }
}

void copiar_matriz(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i  tamX; i++)
    for(j = 0; j  tamY; j++)
      matriz[i][j] = nova_matriz[i][j];
}

void ciclar_matriz(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i  tamX; i++)
    for(j = 0; j  tamY; j++)
      nova_matriz[i][j] = verificar_ao_redor(matriz, i,j);
}

void rodar_jogo(int matriz[tamX][tamY],int nova_matriz[tamX][tamY]){ roda o programa 1 rodada
    ciclar_matriz(matriz,nova_matriz); 
    copiar_matriz(matriz,nova_matriz);
    exibir_matriz(matriz);
}

int main(void) {
  char input;
  input = getchar();
  
  int matriz[tamX][tamY] ={ 
    {0, 0, 0, 0, 0}, 
    {0, 1, 0, 0, 0}, 
    {0, 0, 1, 1, 0}, 
    {0, 1, 1, 0, 0}, 
    {0, 0, 0, 0, 0} };
  int nova_matriz[tamX][tamY] = {0};
  int x,y;
  int a;
  exibir_matriz(matriz); 
  rodar_jogo(matriz,nova_matriz); 
  Sleep(1000); 
  
  return 0;
}
