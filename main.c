#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define tamX 5
#define tamY 5

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
    soma = matriz[x+1][y-1] + matriz[x][y-1] + matriz[x-1][y-1] 
         + matriz[x+1][y  ] +                  matriz[x-1][y  ]
         + matriz[x+1][y+1] + matriz[x][y+1] + matriz[x-1][y+1];
  //################################# meios #################################
  if (val == 0){
    if (soma == 3)
      return 1;
      return 0;
  }
  if(soma < 2 || soma > 3) return 0;
  return 1;
}

void exibir_matriz(int matriz[tamX][tamY]){
  int i,j;
  for(i = 0; i < tamX; i++){
    printf("\n");
    for(j = 0; j < tamY; j++){
      printf("%d ",matriz[i][j]);
    }
  }
}

int main(void) {
  int matriz[tamX][tamY] ={ 
    {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, 
    {0, 1, 1, 1, 0}, 
    {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0} };
  int nova_matriz[tamX][tamY] = {0};
  int x,y;
  int a;
  for(a=0; a < 50; a++){
    for(x = 0; x < tamX; x++)
      for(y = 0; y < tamY; y++)
        nova_matriz[x][y] = verificar_ao_redor(matriz, x,y);
  
  
    for(x = 0; x < tamX; x++)
      for(y = 0; y < tamY; y++)
        matriz[x][y] = nova_matriz[x][y];
  
    exibir_matriz(matriz);
    usleep(1000000);
    system("clear"); 
  }
  return 0;
}