/**
 * Tic Tac Toe em C
 * Programação 101 (https://www.programacao101.com)
 *
 * A ideia aqui é ter um loop infinito que imprime o jogo na tela do usuário.
 * Algumas variáveis controlam a execução do jogo, como por exemplo estado. Esta
 * variável indica se o jogo está sendo jogado, se jogador X ganhou, jogador O
 * ganhou ou empate. Utiliza-se estas variáveis para imprimir informações de
 * acordo com o jogo.
 *
 * A grade é uma matriz 3x3, inicializada com caracteres numéricos indicando
 * jogadas. Quando o jogador escolhe um destes números para preencher, é
 * verificado se a posição já não estava preenchida com um X ou O. Para
 * otimizar o código, dois vetores (coordLinha e coordColuna) foram criados
 * contendo na posição i a coordenada do bloco i+1 na linha e coluna, respectivamente.
 * Por exemplo, o bloco 7 tem coordenadas i=2 e j=0, desta forma, coordLinha[6] = 2 e
 * coordColuna[6] = 0. Estes dois vetores auxiliam quando é necessário modificar
 * o conteúdo do bloco pela entrada do usuário. Ao invés de utilizar ifs ou um switch
 * para decidir os valores de i e j, basta utilizar os valores anotados nestes vetores.
 *
 * Este jogo foi feito utilizando somente conceitos abordados no Programação 101. São eles:
 * - Variáveis
 * - Comandos condicionais
 * - Comandos de repetição
 * - Vetores
 * - Matrizes
 *
 * O único conteúdo não abordado do curso foi strings. Foram utilizados
 * caracteres especiais para limpar a tela e colorir os caracteres.
 */

#include <stdio.h>
#include <stdlib.h> // para system("cls")

int main (void)
{
    // esta matriz é a grade vista pelo jogador
    // quadros não marcados têm um dígito como valor
    char grade[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    // coordenadas dos números
	// o número n está na coordenada (coordLinha[n - 1], coordColuna[n - 1])
    int coordLinha[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    int coordColuna[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    // letra do jogador por indice (0 é X, 1 é O)
    char letraJogador[] = {'X', 'O'};

    int estado = 1; // 1 -> jogando; 2 -> jogador 1 (X) ganhou; 3 -> jogador 2 (O) ganhou; 4 -> empate
    int turno = 1; // 0 -> jogador 1 (X); 1 -> jogador 2 (O)
    int primeiro = 1; // flag auxiliar para imprimir jogadas possíveis
    int jogada; // jogada escolhida pelos jogadores, utilizada no scanf maix abaixo
    int escolhaInvalida = 0; // flag que indica se a jogada foi inválida
    int jogadasRestantes = 9; // contador de jogadas restantes para determinar empate
    char jogarNovamente; // escolha de jogar novamente

    while (1)
    {
        system("cls || tput reset"); // executa comando do Windows || Linux para limpar terminal
        primeiro = 1; // variável para uso estético ao imprimir as jogadas possíveis

        // verificamos se alguém ganhou, de acordo com a configuração do tabuleiro
        if (grade[0][0] == grade[1][1] && grade[1][1] == grade[2][2]) // verifica se os caracteres na diagonal principal são todos iguais
        {
            if (grade[0][0] == 'X')
            {
                estado = 2; // jogador 1 (X) ganhou
            }
            else
            {
                estado = 3; // jogador 2 (O) ganhou
            }
        }
        else if (grade[0][2] == grade[1][1] && grade[1][1] == grade[2][0]) // verifica se os caracteres na diagonal secundária são todos iguais
        {
            if (grade[0][0] == 'X')
            {
                estado = 2; // jogador 1 (X) ganhou
            }
            else
            {
                estado = 3; // jogador 2 (O) ganhou
            }
        }
        else
        {
            // verificar as linhas e colunas
            for (int i = 0; i < 3; i++)
            {
                if (grade[i][0] == grade[i][1] && grade[i][1] == grade[i][2]) // verifica se todos os caracteres na linha i são iguais
                {
                    if (grade[i][0] == 'X')
                    {
                        estado = 2; // jogador 1 (X) ganhou
                    }
                    else
                    {
                        estado = 3; // jogador 2 (O) ganhou
                    }

                    break;
                }
                else if (grade[0][i] == grade[1][i] && grade[1][i] == grade[2][i]) // verifica se todos os caracteres na coluna i são iguais
                {
                    if (grade[i][0] == 'X')
                    {
                        estado = 2; // jogador 1 (X) ganhou
                    }
                    else
                    {
                        estado = 3; // jogador 2 (O) ganhou
                    }

                    break;
                }
            }
        }

        if (jogadasRestantes == 0 && estado == 1) estado = 4; // se ninguém ganhou e não há mais jogadas disponíveis, empate

        // se a última jogada não foi inválida, trocar o jogador da vez
        // como os valores possíveis são 0 e 1, se a ultima jogada foi do jogador 0, !0 é 1 e se foi do 1, !1 é 0
        if (!escolhaInvalida) turno = !turno;

        // imprime no topo da tela do terminal de quem é a vez
        // os printfs que imprimem quebras de linha são por pura estética
        if (estado == 1) printf("Vez de: Jogador %d (%c)\n\n", turno + 1, letraJogador[turno]);
        else printf("\n\n");

        // verifica se a última escolha feita pelo jogador foi inválida (escolheu marcar um quadrado marcado)
        if (escolhaInvalida == 1)
        {
            printf("Escolha invalida!");
            escolhaInvalida = 0;
        }
        else if (estado == 1)
        {
            jogadasRestantes--;
        }

        printf("\n"); // estética

        // verifica se o jogo acabou e exibe frase de acordo
        if (estado == 2) printf("Jogador 1 (X) venceu!\n");
        else if (estado == 3) printf("Jogador 2 (O) venceu!\n");
        else if (estado == 4) printf("Empate!\n");

        // imprimimos a grade
        for (int i = 0; i < 3; i++)
        {
            printf("\n");

            for (int j = 0; j < 3; j++)
            {
                printf("|‾‾‾‾‾|");
            }

            printf("\n");

            for (int j = 0; j < 3; j++)
            {
                printf("|  %c  |", grade[i][j]);
            }

            printf("\n");

            for (int j = 0; j < 3; j++)
            {
                printf("|_____|");
            }

            printf("\n");
        }

        // se o jogo não acabou ainda, imprimir possibilidades e pedir jogada do jogador
        if (estado == 1)
        {
            printf("\n\nJogadas disponiveis: ");

            // verifica em toda a grade quais quadrados não são X nem O
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (grade[i][j] != 'X' && grade[i][j] != 'O')
                    {
                        // por questões de estética, verifico se é o primeiro
                        if (primeiro) // a primeira opção não deve ter vírgula à frente
                        {
                            printf("%c", grade[i][j]);
                            primeiro = 0;
                        }
                        else
                        {
                            printf(", %c", grade[i][j]);
                        }
                    }
                }
            }

            printf("\n"); // estética

            // pedimos a jogada a ser feita
            printf("Digite sua jogada: ");
            scanf("%d", &jogada);

            // verificamos se o bloco escolhido não estava preenchido
            char bloco = grade[coordLinha[jogada - 1]][coordColuna[jogada - 1]];
            if (bloco == 'X' || bloco == 'O')
            {
                // bloco estava preenchido, jogada é marcada como inválida e pedirá ao jogador uma nova jogada
                escolhaInvalida = 1;
                continue;
            }

            // se chegou aqui é porque não passou pelo continue acima, então o bloco pode ser marcado
            grade[coordLinha[jogada - 1]][coordColuna[jogada - 1]] = letraJogador[turno];
        }
        else // o jogo acabou, perguntar se quer jogar novamente
        {
            printf("\n\nJogar novamente (S/N)? ");
            scanf(" %c", &jogarNovamente);

            char caractereGrade = '1';

            if (jogarNovamente == 'S') // jogar novamente, resetar a grade e as variáveis que controlam o jogo
            {
                // reiniciando grade
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        grade[i][j] = caractereGrade++;
                    }
                }

                estado = 1;
                turno = 1;
                jogadasRestantes = 9;
            }
            else if (jogarNovamente == 'N') // sair do programa
            {
                break;
            }
            else // não é uma escolha válida
            {
                escolhaInvalida = 1;
            }
        }
    }

    return 0;
}
