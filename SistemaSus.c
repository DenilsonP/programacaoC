#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de cada pessoa
struct Pessoa {
    char nome[50];
    int idade;
    float altura;
    char familia[50]; // Família a qual pertence
};

// Estrutura para armazenar os agendamentos
struct Agendamento {
    char data[20];
    char horario[10];
    char tipo[50]; // Tipo do agendamento (Consulta, Exame, etc.)
};

// Função para cadastrar uma nova pessoa
void cadastrarPessoa(struct Pessoa **lista, int *total) {
    *lista = (struct Pessoa *) realloc(*lista, (*total + 1) * sizeof(struct Pessoa));
    
    if (*lista == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("\nCadastro da Pessoa %d\n", *total + 1);

    printf("Nome: ");
    scanf(" %[^\n]", (*lista)[*total].nome); // Lê nome com espaços

    printf("Idade: ");
    scanf("%d", &(*lista)[*total].idade);

    printf("Altura (ex: 1.75): ");
    scanf("%f", &(*lista)[*total].altura);

    printf("Família: ");
    scanf(" %[^\n]", (*lista)[*total].familia); // Lê família com espaços

    (*total)++; // Incrementa o número de pessoas cadastradas
}

// Função para listar as pessoas cadastradas
void listarPessoas(struct Pessoa *lista, int total) {
    if (total == 0) {
        printf("\nNenhuma pessoa cadastrada.\n");
        return;
    }
    printf("\nLista de Pessoas Cadastradas:\n");
    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Idade: %d | Altura: %.2f m | Família: %s\n",
               i + 1, lista[i].nome, lista[i].idade, lista[i].altura, lista[i].familia);
    }
}

// Função para alterar os dados cadastrais de uma pessoa
void alterarCadastro(struct Pessoa *lista, int total) {
    int index;
    
    if (total == 0) {
        printf("\nNenhuma pessoa cadastrada para alterar.\n");
        return;
    }

    listarPessoas(lista, total); // Exibe as pessoas cadastradas

    printf("\nDigite o número da pessoa que deseja alterar: ");
    scanf("%d", &index);

    if (index < 1 || index > total) {
        printf("Índice inválido! Tente novamente.\n");
        return;
    }

    index--; // Ajusta para o índice correto no vetor (começa de 0)
    
    printf("\nAlterando dados de %s:\n", lista[index].nome);
    
    printf("Novo nome: ");
    scanf(" %[^\n]", lista[index].nome);

    printf("Nova idade: ");
    scanf("%d", &lista[index].idade);

    printf("Nova altura (ex: 1.75): ");
    scanf("%f", &lista[index].altura);

    printf("Nova família: ");
    scanf(" %[^\n]", lista[index].familia);

    printf("\nDados alterados com sucesso!\n");
}

// Função para consultar pessoas por família
void consultarPorFamilia(struct Pessoa *lista, int total) {
    char familia[50];
    int encontrou = 0;

    printf("\nDigite o nome da família para consultar: ");
    scanf(" %[^\n]", familia);

    printf("\nPessoas da família %s:\n", familia);

    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].familia, familia) == 0) {
            printf("%d. Nome: %s | Idade: %d | Altura: %.2f m | Família: %s\n",
                   i + 1, lista[i].nome, lista[i].idade, lista[i].altura, lista[i].familia);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma pessoa encontrada nessa família.\n");
    }
}

// Função para retirar uma pessoa da lista
void retirarPessoa(struct Pessoa **lista, int *total) {
    int index;

    if (*total == 0) {
        printf("\nNenhuma pessoa cadastrada para remover.\n");
        return;
    }

    listarPessoas(*lista, *total); // Exibe as pessoas cadastradas

    printf("\nDigite o número da pessoa que deseja remover: ");
    scanf("%d", &index);

    if (index < 1 || index > *total) {
        printf("Índice inválido! Tente novamente.\n");
        return;
    }

    index--; // Ajusta para o índice correto no vetor (começa de 0)

    // Realiza a remoção movendo as pessoas após o índice para uma posição anterior
    for (int i = index; i < *total - 1; i++) {
        (*lista)[i] = (*lista)[i + 1];
    }

    // Reduz o total de pessoas e realoca a memória
    *total -= 1;
    *lista = (struct Pessoa *) realloc(*lista, *total * sizeof(struct Pessoa));

    if (*lista == NULL && *total > 0) {
        printf("Erro ao realocar memória!\n");
        exit(1);
    }

    printf("Pessoa removida com sucesso!\n");
}

// Função para cadastrar um agendamento
void agendarExame(struct Agendamento **agenda, int *totalAgenda) {
    *agenda = (struct Agendamento *) realloc(*agenda, (*totalAgenda + 1) * sizeof(struct Agendamento));

    if (*agenda == NULL) {
        printf("Erro ao alocar memória para agendamentos!\n");
        exit(1);
    }

    printf("\nCadastro de Exame %d\n", *totalAgenda + 1);

    printf("Data (dd/mm/aaaa): ");
    scanf(" %[^\n]", (*agenda)[*totalAgenda].data);

    printf("Horário: ");
    scanf(" %[^\n]", (*agenda)[*totalAgenda].horario);

    printf("Tipo de Exame: ");
    scanf(" %[^\n]", (*agenda)[*totalAgenda].tipo);

    (*totalAgenda)++; // Incrementa o número de agendamentos
}

// Função para listar os agendamentos
void listarExames(struct Agendamento *agenda, int totalAgenda) {
    if (totalAgenda == 0) {
        printf("\nNenhum agendamento registrado.\n");
        return;
    }

    printf("\nLista de Exames Agendados:\n");
    for (int i = 0; i < totalAgenda; i++) {
        printf("%d. Data: %s | Horário: %s | Tipo: %s\n",
               i + 1, agenda[i].data, agenda[i].horario, agenda[i].tipo);
    }
}

// Função do menu
void menu() {
    struct Pessoa *lista = NULL; // Ponteiro para armazenar a lista de pessoas
    struct Agendamento *agenda = NULL; // Ponteiro para armazenar os agendamentos
    int total = 0; // Contador de pessoas cadastradas
    int totalAgenda = 0; // Contador de agendamentos
    int opcao;

    while (1) {  // Loop infinito até o usuário escolher sair
        printf("\nMENU SUS:\n");
        printf("1 - Cadastro\n");
        printf("2 - Alterações\n");
        printf("3 - Agendamentos\n");
        printf("4 - Consultas\n");
        printf("5 - Exames\n");
        printf("6 - Consultar Dados Cadastrados\n");
        printf("7 - Listar Exames\n");
        printf("Digite 0 para finalizar atendimento:\n");
        
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("Atendimento finalizado. Obrigado!\n");
            break; // Sai do loop
        }
    
        switch (opcao) {
            case 1:
                printf("Bem-vindo ao Cadastro!\n");
                cadastrarPessoa(&lista, &total); // Chama a função de cadastro
                break;
            case 2:
                printf("Alterando dados cadastrais!\n");
                alterarCadastro(lista, total); // Chama a função para alterar cadastro
                break;
            case 3:
                printf("Agendando Exames!\n");
                agendarExame(&agenda, &totalAgenda); // Chama a função para agendar exame
                break;
            case 4:
                printf("Consultando dados cadastrados!\n");
                consultarPorFamilia(lista, total); // Chama a função para consultar por família
                break;
            case 5:
                printf("Consultando exames!\n");
                listarExames(agenda, totalAgenda); // Chama a função para listar exames
                break;
            case 6:
                listarPessoas(lista, total); // Chama a função para listar pessoas cadastradas
                break;
            case 7:
                listarExames(agenda, totalAgenda); // Chama a função para listar exames
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    }

    // Libera a memória alocada antes de sair
    free(lista);
    free(agenda);
}

int main() {
    menu(); // Chama a função do menu
    printf("Programa encerrado.\n");
    return 0;
}
