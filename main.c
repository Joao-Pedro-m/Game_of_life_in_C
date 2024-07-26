#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include "./constantes.h"

// Verifica todos os vizinhos da célula atual.
int verificar_celula(int matriz[largura_X][altura_Y], int x, int y);

// Com o resultado de "verificar_celula", atualiza a nova matriz, e retorna se há ou não célula(s) viva(s).
int preencher_nova_matriz(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y]);

// Transforma a "nova_matriz" na "matriz atual".
void ciclar_matriz(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y]);

// Mostra qual célula está selecionada no momento.
void exibir_matriz_com_jogador(int matriz[largura_X][altura_Y], int x, int y, char matriz_char[largura_X][altura_Y][MAX_DIGITOS]);

// Permite o usuário escolher a configuração do jogo.
void navegar_e_modificar_matriz(int matriz[largura_X][altura_Y], char matriz_char[largura_X][altura_Y][MAX_DIGITOS]);

// Mostra as tranformações ocorridas em cada nova geração.
void exibir_matriz_sem_jogador(int matriz[largura_X][altura_Y], char matriz_char[largura_X][altura_Y][MAX_DIGITOS]);

// Loop principal do jogo e verifica se o jogo deve continuar.
int loop_principal(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y], int jogo, int contador_de_geracoes[], char matriz_char[largura_X][altura_Y][MAX_DIGITOS]);

// Cadastra o nome do usuário, ou seja, o jogador.
void cadastrar_jogadores(char *jogadores[], int jogo);

// Limpa a matriz para o próximo jogo.
void limpa_matriz(int matriz[largura_X][altura_Y]);

// Mostra o placar com o rank dos jogadores e o número de gerações.
void mostrar_placar(char *jogadores[CHAR_JOGADORES], int jogo, int contador_de_geracoes[NUM_GERACO]);

// Evita estouro de buffer e bugs de leitura de char.
void limpar_buffer_teclado();

void limpar_buffer_teclado()
{
    while (_kbhit())
    {
        _getch();
    }
}

// Verifica o estado de uma célula com base nos seus vizinhos.
int verificar_celula(int matriz[largura_X][altura_Y], int x, int y)
{

    int valor = matriz[x][y];
    // A soma serve para contabilizar quantos vizinhos a célula tem.
    int soma;

    // Verifica os vizinhos dependendo da posição da célula
    if (x == 0 && y == 0)
        soma = matriz[x][y + 1] + matriz[x + 1][y] + matriz[x + 1][y + 1];

    else if (x == largura_X - 1 && y == altura_Y - 1)
        soma = matriz[x][y - 1] + matriz[x - 1][y] + matriz[x - 1][y - 1];

    else if (x == largura_X - 1 && y == 0)
        soma = matriz[x][y + 1] + matriz[x - 1][y] + matriz[x - 1][y + 1];

    else if (x == 0 && y == altura_Y - 1)
        soma = matriz[x][y - 1] + matriz[x + 1][y] + matriz[x + 1][y - 1];

    else if (x == 0)
        soma = matriz[x][y - 1] + matriz[x][y + 1] + matriz[x + 1][y] + matriz[x + 1][y - 1] + matriz[x + 1][y + 1];

    else if (y == 0)
        soma = matriz[x - 1][y] + matriz[x + 1][y] + matriz[x][y + 1] + matriz[x - 1][y + 1] + matriz[x + 1][y + 1];

    else if (x == largura_X - 1)
        soma = matriz[x][y - 1] + matriz[x][y + 1] + matriz[x - 1][y] + matriz[x - 1][y - 1] + matriz[x - 1][y + 1];

    else if (y == altura_Y - 1)
        soma = matriz[x - 1][y] + matriz[x + 1][y] + matriz[x][y - 1] + matriz[x - 1][y - 1] + matriz[x + 1][y - 1];

    else
    {
        soma = matriz[x + 1][y - 1] + matriz[x][y - 1] + matriz[x - 1][y - 1] + matriz[x + 1][y] + matriz[x + 1][y + 1] + matriz[x - 1][y] + matriz[x - 1][y + 1] + matriz[x][y + 1];
    }

    // Regras para determinar o estado da célula na próxima geração.
    if (valor == 0)
    {
        if (soma == 3)
            return 1;

        return 0;
    }

    if (soma < 2 || soma > 3)
        return 0;

    return 1;
}

int preencher_nova_matriz(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y])
{
    int i, j, soma = 0;

    for (i = 0; i < largura_X; i++)
    {
        for (j = 0; j < altura_Y; j++)
        {
            // Cada célula é verificada e o retorno é se a célula está viva(1) ou não(0).
            nova_matriz[i][j] = verificar_celula(matriz, i, j);

            if (nova_matriz[i][j] == 1)
            {
                soma++;
            }
        }
    }
    // Se a soma for 0 significa que não há sequer uma célula viva.
    // Retorna 0 se não houver células vivas e 1 caso haja.
    if (soma == 0)
    {
        return 0;
    }

    return 1;
}

void ciclar_matriz(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y])
{
    // Copia os valores da nova matriz para a matriz atual que é a nova.
    int i, j;
    for (i = 0; i < largura_X; i++)
        for (j = 0; j < altura_Y; j++)
            matriz[i][j] = nova_matriz[i][j];
}

// Função que preenche um array tridimensional de strings baseado no array bidimensional de inteiros
void preenche_matriz_de_strings(int matriz[largura_X][altura_Y], char matriz_char[largura_X][altura_Y][MAX_DIGITOS])
{

    for (int i = 0; i < largura_X; i++)
    {
        for (int j = 0; j < altura_Y; j++)
        {

            switch (matriz[i][j])
            {
            case 1:
                snprintf(matriz_char[i][j], MAX_DIGITOS + 1, "%s", CELULA_VIVA);
                break;
            case 0:
                snprintf(matriz_char[i][j], MAX_DIGITOS + 1, "%s", CELULA_MORTA);
                break;
            default:

                break;
            }
        }
    }
}

void exibir_matriz_com_jogador(int matriz[largura_X][altura_Y], int x, int y, char matriz_char[largura_X][altura_Y][MAX_DIGITOS])
{
    // Exibe a matriz com o jogador indicando a posição atual.
    // Usada no início do jogo, quando o usuário está escolhendo quais células começarão vivas.
    int i, j;

    preenche_matriz_de_strings(matriz, matriz_char);

    for (i = 0; i < largura_X; i++)
    {
        for (j = 0; j < altura_Y; j++)
        {
            if (i == x && j == y)
                printf("%s ", JOGADOR);
            else
            {
                printf("%s ", matriz_char[i][j]);
            }
        }
        printf("\n");
    }
}

void navegar_e_modificar_matriz(int matriz[largura_X][altura_Y], char matriz_char[largura_X][altura_Y][MAX_DIGITOS])
{
    // Permite ao usuário navegar e modificar a matriz inicial
    int x = 0, y = 0;
    char comando;
    limpar_buffer_teclado();

    exibir_matriz_com_jogador(matriz, x, y, matriz_char);

    while (1)
    {
        comando = _getch();
        system("cls"); // Use "cls" para Windows e "clear" no linux

        if (comando == 'q')
        {
            system("cls");
            break;
        }

        switch (comando)
        {
        case 'w':
            if (x > 0)
                x--;
            break;

        case 's':
            if (x < largura_X - 1)
                x++;
            break;

        case 'a':
            if (y > 0)
                y--;
            break;

        case 'd':
            if (y < altura_Y - 1)
                y++;
            break;

        case 'e':
            matriz[x][y] = (matriz[x][y] == 0) ? 1 : 0; // Alterna entre 0 e 1
            break;

        default:
            printf("Comando invalido! Use 'WASD' para se mover, 'E' para editar, e 'Q' para inciar.\n");
            break;
        }
        exibir_matriz_com_jogador(matriz, x, y, matriz_char);
    }
}

void exibir_matriz_sem_jogador(int matriz[largura_X][altura_Y], char matriz_char[largura_X][altura_Y][MAX_DIGITOS])
{
    // Exibe a matriz sem o jogador, apenas mostrando o progresso do jogo.
    int i, j;
    // O jogo começa e roda sem nenhuma interação do usuário.
    preenche_matriz_de_strings(matriz, matriz_char);

    for (i = 0; i < largura_X; i++)
    {
        for (j = 0; j < altura_Y; j++)
        {
            printf("%s ", matriz_char[i][j]);
        }
        printf("\n");
    }
}

void mostrar_menu()
{
    limpar_buffer_teclado();
    printf("Menu:\n");
    printf("1. Placar de jogos com maior duração\n");
    printf("2. Jogar\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

int loop_principal(int matriz[largura_X][altura_Y], int nova_matriz[largura_X][altura_Y], int jogo, int contador_de_geracoes[], char matriz_char[largura_X][altura_Y][MAX_DIGITOS])
{
    // Controla o ciclo de gerações
    limpar_buffer_teclado();

    int contador = 0;
    char comando = 0;

    // Condição de parada do loop: se não houver nenhuma celula viva.
    while (preencher_nova_matriz(matriz, nova_matriz))
    {

        exibir_matriz_sem_jogador(matriz, matriz_char);
        preencher_nova_matriz(matriz, nova_matriz);
        ciclar_matriz(matriz, nova_matriz);

        // Verifica se uma tecla foi pressionada
        if (_kbhit())
        {
            comando = _getch(); // Captura o caractere sem ecoar na tela
        }

        // Caso o usuário queira interromper antes do fim da jogo.
        if (comando == 'x')
        {
            system("cls");
            printf("Simulação interrompida. Voltando para o menu...");
            Sleep(1500);
            system("cls");
            break;
        }

        Sleep(1250);
        system("cls");
        contador++;
    }
    if (!(preencher_nova_matriz(matriz, nova_matriz)))
    {
        printf("Todas células morreram. Fim de simulação\n\nVoltando para o menu...");
        Sleep(2000);
        system("cls");
    }

    contador_de_geracoes[jogo] = contador;

    return 0;
}

void cadastrar_jogadores(char *jogadores[], int jogo)
{
    limpar_buffer_teclado();
    system("cls");
    printf("Digite seu nome: ");
    fgets(jogadores[jogo], 60, stdin);

    // Remove o caractere de nova linha, se houver
    jogadores[jogo][strcspn(jogadores[jogo], "\n")] = '\0';

    printf("\nJogador cadastrado!\n\nCarregando jogo...");
    Sleep(3000);

    system("cls");
    printf("Use 'WASD' para se mover, 'E' para editar, e 'Q' para inciar e 'X' para interromper após seu início.\n");

    Sleep(4000);
    system("cls");
}

void limpa_matriz(int matriz[largura_X][altura_Y])
{
    for (int i = 0; i < largura_X; i++)
    {
        for (int j = 0; j < altura_Y; j++)
        {
            // Todos os valores se tornam zero, limpando a matriz para o próximo jogo.
            matriz[i][j] = 0;
        }
    }
}

void mostrar_placar(char *jogadores[CHAR_JOGADORES], int jogo, int contador_de_geracoes[NUM_GERACO])
{
    system("cls");

    if (jogo == 0)
    {
        printf("Não há placar por enquanto.");
    }
    else
    {
        // Ordena os vetores de maneira com o que o contador_de_geracoes esteja em ordem decrescente.
        for (int i = 0; i < jogo - 1; i++)
        {
            for (int j = i + 1; j < jogo; j++)
            {
                if (contador_de_geracoes[i] < contador_de_geracoes[j])
                {
                    int temp = contador_de_geracoes[i];
                    contador_de_geracoes[i] = contador_de_geracoes[j];
                    contador_de_geracoes[j] = temp;

                    char temp1[CHAR_JOGADORES];
                    strcpy(temp1, jogadores[i]);
                    strcpy(jogadores[i], jogadores[j]);
                    strcpy(jogadores[j], temp1);
                }
            }
        }

        // Condição para o placar de acordo com a quantidade de jogos.
        if (jogo == 3)
        {
            printf("PLACAR - MELHORES\n");
            printf("TOP 1 - %s\n número de gerações: %d", jogadores[0], contador_de_geracoes[0]);
            printf("\nTOP 2 - %s\n número de gerações: %d", jogadores[1], contador_de_geracoes[1]);
            printf("\nTOP 3 - %s\n número de gerações: %d", jogadores[2], contador_de_geracoes[2]);
        }

        else if (jogo >= 3)
        {
            printf("\nPLACAR - MELHORES\n");
            printf("TOP 1 - %s\n número de gerações: %d", jogadores[0], contador_de_geracoes[0]);
            printf("\nTOP 2 - %s\n número de gerações: %d", jogadores[1], contador_de_geracoes[1]);
            printf("\nTOP 3 - %s\n número de gerações: %d", jogadores[2], contador_de_geracoes[2]);
            printf("\n\nPLACAR - OUTROS JOGADORES\n");
            for (int i = 3; i < jogo; i++)
            {
                printf("%d° jogador: %s\n número de gerações: %d", i + 1, jogadores[i], contador_de_geracoes[i]);
                printf("\n");
            }
        }
        else
        {
            printf("PLACAR\n");
            for (int i = 0; i < jogo; i++)
            {
                printf("%d° jogador: %s\n número de gerações: %d", i + 1, jogadores[i], contador_de_geracoes[i]);
                printf("\n");
            }
        }
    }
}
int main()
{

    system("chcp 65001");
    system("cls");

    // Aloca memória para as strings dos jogadores.
    char *jogadores[CHAR_JOGADORES];
    for (int i = 0; i < CHAR_JOGADORES; i++)
    {
        jogadores[i] = malloc(60 * sizeof(char));
        if (jogadores[i] == NULL)
        {
            fprintf(stderr, "Falha na alocação de memória\n");
            return 1;
        }
    }

    int contador_de_geracoes[NUM_GERACO] = {0};
    int opc, jogo = 0;

    // Inicia as estruturas de dados ultizadas no jogo.
    int matriz[largura_X][altura_Y] = {0};
    int nova_matriz[largura_X][altura_Y] = {0};
    char matriz_char[largura_X][altura_Y][MAX_DIGITOS];

    printf("\nJOGO DA VIDA DE CONWAY\n");

    while (1)
    {
        mostrar_menu();
        char buffer[10];
        fgets(buffer, 10, stdin);
        opc = atoi(buffer);

        switch (opc)
        {
        case 1:
            mostrar_placar(jogadores, jogo, contador_de_geracoes);
            Sleep(4500);
            system("cls");
            break;
        case 2:
            cadastrar_jogadores(jogadores, jogo);
            navegar_e_modificar_matriz(matriz, matriz_char);
            loop_principal(matriz, nova_matriz, jogo, contador_de_geracoes, matriz_char);
            limpa_matriz(matriz);
            limpar_buffer_teclado();
            // Incremento para contabilizar os jogos finalizados.
            jogo++;
            break;
        case 3:
            printf("Saindo...\n");
            return 0;

        default:
            system("cls");
            printf("Opção inválida! Tente novamente.\n");
        }
    }
    // Libera a memória alocada.
    for (int i = 0; i < CHAR_JOGADORES; i++)
    {
        free(jogadores[i]);
    }

    return 0;
}
