#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaração de variáveis constantes globais.
// MIN: valor mínimo que a variável numero_resposta poderá atingir.
// MAX: valor máximo que a variável numero_resposta poderá atingir.
#define MAX 100
#define MIN 0

int main(){
    time_t tempo_atual;
    char* tempo_atual_string;
    tempo_atual = time(NULL);
    tempo_atual_string = ctime(&tempo_atual);
    

    // A função srand cria() números aleatórios para a função rand() baseados no valor dado nela.
    // O valor atribuido dentro é o valor retornado da função time(), com valor 0, que sempre retorna um valor diferente, baseado no tempo do computador.
    srand(time(0));

    // Declaração de varíaveis.
    // dificuldade: guarda o nível de dificuldade do jogo.
    // numero_de_tentativas: guarda o número de tentativas que o usuário tem no jogo, baseado na dificuldade.
    // numero_resposta: guarda o número secreto aleatório que será a resposta do jogo.
    int dificuldade, numero_de_tentativas, numero_resposta, tentativas[100], numero_chutado, contador;
    int selecionar_dificuldade, acertou, salvar;
    double taxa_de_acerto;
    FILE * arquivo;
    

    // Essa linha define o número resposta, onde o MAX e MIN são, respectivamente, os maiores números que eles podem assumir.
    // Os números MAX e MIN foram definidos como constantes no escopo global.
    numero_resposta = rand() % (MAX + 1 - MIN) + MIN;

    printf("#####################################\n");
    printf("# Bem-vindo ao jogo de adivinhação! #\n");
    printf("#####################################\n\n");
    printf("Foi gerado um número aleatório. Você consegue adivinhar qual é?\n");
    printf("Selecione uma dificuldade: Fácil (1), Médio (2), Difícil (3), Customizado (4).\n");

    scanf("%d", &dificuldade);
    
    switch(dificuldade) {
        case 1:
            numero_de_tentativas = 20;
            break;
        case 2:
            numero_de_tentativas = 10;
            break;
        case 3:
            numero_de_tentativas = 6;
            break;
        case 4:
            selecionar_dificuldade = 1;
            break;
        default:
            printf("Dificuldade inválida! Por favor, selecione uma das seguintes dificuldades:\n");
            printf("Fácil (1), Médio (2), Difícil (3), Customizado (4).\n");
    }
    
    // Sequência para caso o usuário queira customizar a dificuldade:
    while (selecionar_dificuldade == 1){
        printf("Digite o número de tentativas que você quer (mínimo 1, máximo 100):\n");
        scanf("%d", &numero_de_tentativas);

        if (numero_de_tentativas > 100 || numero_de_tentativas <= 0) {
            printf("Digite um número válido, de 1 a 100!\n");
            numero_de_tentativas = 0;
        } else {
            selecionar_dificuldade = 0;
        }
    }

    printf("\nO nível de dificuldade foi selecionado (%d)! Você terá o total de %d tentativas!\n", dificuldade, numero_de_tentativas);
    printf("Lembre-se, o número está entre 0 e 100.\n\n");
    
    // Loop principal do jogo:
    for(contador = 1; contador <= numero_de_tentativas; contador++){
        printf("TENTATIVA #%d de %d:\n", contador, numero_de_tentativas);
        printf("\tChute um número: ");
        scanf("%d", &numero_chutado);

        if (numero_chutado > 100 || numero_chutado < 0){
            printf("\tNúmero inválido! Por favor, digite um número de 0 a 100!\n");
            contador--;
            continue;
        }

        tentativas[contador] = numero_chutado;
        acertou = numero_chutado == numero_resposta;

        if (acertou == 1) {
            printf("\n\nParabéns! Você acertou!\n");
            break;
        } else {
            if (numero_chutado > numero_resposta) {
                printf("\tSeu chute foi maior do que o número secreto!\n\n");
            } else if (numero_chutado < numero_resposta) {
                printf("\tSeu chute foi menor do que o número secreto!\n\n");
            }
        }
    }

    taxa_de_acerto = (1.0/contador)*100;

    printf("\n\nFIM DE JOGO!\n");
    printf("ESTATÍSTICAS:\n");
    printf("\t- Data de início: %s", tempo_atual_string);
    if (acertou == 1){
        printf("\t- Ganhou: SIM;");
    } else {
        printf("\t- Ganhou: NÃO;");
    }
    printf(" \n\t- Dificuldade selecionada: %d;\n\t- Número resposta: %d;\n\t- Número de tentativas: %d;\n\t- Taxa de acerto: %.2f%%;\n\t- Tentativas: ", dificuldade, numero_resposta, numero_de_tentativas, taxa_de_acerto);
    printf("[");
    for(int j = 1; j < 100; j++){
        if (tentativas[j] != 0) {
            printf("%d", tentativas[j]);
            if (tentativas[j+1] == 0) {
                break;
            } else {
                printf(", ");
            }
        }
    }
    printf("].");
    printf("\n\nVocê gostaria de salvar suas estatísticas em um arquivo placares.txt? Sim (1), Não (0):");
    
    scanf("%d", &salvar);

    while (1){
        if (salvar == 1){
            arquivo = fopen("placares.txt","w");
                fprintf(arquivo, "Data de início: %s", tempo_atual_string);
                if (acertou == 1){
                    fprintf(arquivo, "\t- Ganhou: SIM;");
                } else {
                    fprintf(arquivo, "\t- Ganhou: NÃO;");
                }
                fprintf(arquivo, " \n\t- Dificuldade selecionada: %d;\n\t- Número resposta: %d;\n\t- Número de tentativas: %d;\n\t- Taxa de acerto: %.2f%%;\n\t- Tentativas: ", dificuldade, numero_resposta, numero_de_tentativas, taxa_de_acerto);
                fprintf(arquivo, "[");
                for(int j = 1; j < 100; j++){
                    if (tentativas[j] != 0) {
                        fprintf(arquivo, "%d", tentativas[j]);
                        if (tentativas[j+1] == 0) {
                            break;
                        } else {
                            fprintf(arquivo, ", ");
                        }
                    }
                }
                fprintf(arquivo, "].\n\n");
            fclose(arquivo);
            printf("Estatísticas salvas! Te vejo no próximo jogo! :)\n\n");
            break;
        } else if (salvar == 0) {
            printf("OK, não salvo! Te vejo no próximo jogo! :)\n\n");
            break;
        } else {
            printf("Opção inválida!\n");
            printf("Você gostaria de salvar suas estatísticas em um arquivo placares.txt? Sim (1), Não (0)\n");
            scanf("%d", &salvar);
        }
    }
    return 0;
}