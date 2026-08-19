#include <stdio.h>
#include <stdlib.h> // Para free

// Inclui todos os cabeçalhos dos módulos
#include "aluno.h"
#include "disciplina.h"
#include "turma.h"
#include "matricula.h"

// Funções para liberar memória de todos os módulos
void liberar_memoria_todos() {
    if (alunos != NULL) {
        free(alunos);
        alunos = NULL;
    }
    if (disciplinas != NULL) {
        free(disciplinas);
        disciplinas = NULL;
    }
    if (turmas != NULL) {
        free(turmas);
        turmas = NULL;
    }
    if (matriculas_vetor != NULL) {
        free(matriculas_vetor);
        matriculas_vetor = NULL;
    }
}

// Função para carregar todos os dados
void carregar_todos_dados() {
    carregar_alunos();
    carregar_disciplinas();
    carregar_turmas();
    carregar_matriculas();
}

// Função para salvar todos os dados
void salvar_todos_dados() {
    salvar_alunos();
    salvar_disciplinas();
    salvar_turmas();
    salvar_matriculas();
}

void menu_alunos() {
    int opcao;
    do {
        printf("\n--- MENU ALUNOS ---\n");
        printf("1. Inserir Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Buscar Aluno\n");
        printf("4. Atualizar Aluno\n");
        printf("5. Excluir Aluno\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir_aluno(); break;
            case 2: imprimir_alunos(); break;
            case 3: buscar_aluno(); break;
            case 4: atualizar_aluno(); break;
            case 5: excluir_aluno(); break;
            case 0: printf("Voltando ao Menu Principal.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menu_disciplinas() {
    int opcao;
    do {
        printf("\n--- MENU DISCIPLINAS ---\n");
        printf("1. Inserir Disciplina\n");
        printf("2. Listar Disciplinas\n");
        printf("3. Buscar Disciplina\n");
        printf("4. Atualizar Disciplina\n");
        printf("5. Excluir Disciplina\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir_disciplina(); break;
            case 2: imprimir_disciplinas(); break;
            case 3: buscar_disciplina(); break;
            case 4: atualizar_disciplina(); break;
            case 5: excluir_disciplina(); break;
            case 0: printf("Voltando ao Menu Principal.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menu_turmas() {
    int opcao;
    do {
        printf("\n--- MENU TURMAS ---\n");
        printf("1. Inserir Turma\n");
        printf("2. Listar Turmas\n");
        printf("3. Buscar Turma\n");
        printf("4. Atualizar Turma\n");
        printf("5. Excluir Turma\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir_turma(); break;
            case 2: listar_turmas(); break;
            case 3: buscar_turma(); break;
            case 4: atualizar_turma(); break;
            case 5: excluir_turma(); break;
            case 0: printf("Voltando ao Menu Principal.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menu_matriculas() {
    int opcao;
    do {
        printf("\n--- MENU MATRICULAS ---\n");
        printf("1. Inserir Matricula\n");
        printf("2. Listar Matriculas\n");
        printf("3. Buscar Matricula\n");
        printf("4. Atualizar Matricula\n");
        printf("5. Excluir Matricula\n");
        printf("6. Media das disciplinas\n");
        printf("7. Ver Alunos por disciplinas\n");
        printf("8. Alunos aprovdos e reprovados\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir_matricula(); break;
            case 2: listar_matriculas(); break;
            case 3: buscar_matricula(); break;
            case 4: atualizar_matricula(); break;
            case 5: excluir_matricula(); break;
            case 6: mediaPordisciplina_matriculas(); break;
            case 7: agruparPordisciplina_matriculas(); break;
            case 8: mediaporaluno_matriculas(); break;
            case 0: printf("Voltando ao Menu Principal.\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    
    carregar_todos_dados();

    int opcao_principal;
    do {
        printf("\n=== SISTEMA DE GESTAO ACADEMICA ===\n");
        printf("1. Gerenciar Alunos\n");
        printf("2. Gerenciar Disciplinas\n");
        printf("3. Gerenciar Turmas\n");
        printf("4. Gerenciar Matriculas\n");
        printf("0. Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1: menu_alunos(); break;
            case 2: menu_disciplinas(); break;
            case 3: menu_turmas(); break;
            case 4: menu_matriculas(); break;
            case 0:
                printf("Saindo do sistema. Salvando dados...\n");
                salvar_todos_dados();
                liberar_memoria_todos(); // Libera a memória alocada
                break;
            default: printf("Opcao invalida. Por favor, tente novamente.\n");
        }
    } while (opcao_principal != 0);

    return 0;
}