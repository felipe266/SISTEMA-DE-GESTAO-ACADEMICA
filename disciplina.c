#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h" // Inclui o cabeçalho da disciplina
#include "matricula.h"
#include "turma.h"

// Definição das variáveis globais (sem o 'extern' aqui)
Turma *turma = NULL;
Disciplina *disciplinas = NULL;
int quantidade_disciplinas = 0;
int tamanhoVetor_disciplinas = 1;

void redimensionar_disciplinas() {
    // Aumenta a capacidade se a ocupação for >= 75%
    if (quantidade_disciplinas >= 0.75*tamanhoVetor_disciplinas) {
        tamanhoVetor_disciplinas *= 2;
        disciplinas = realloc(disciplinas, tamanhoVetor_disciplinas * sizeof(Disciplina));
    }
    
    else if (quantidade_disciplinas <= 0.25*tamanhoVetor_disciplinas) {  
        tamanhoVetor_disciplinas /= 2;
        disciplinas = realloc(disciplinas, tamanhoVetor_disciplinas * sizeof(Disciplina));
    }
}

void salvar_disciplinas() {
    FILE *arq = fopen("disciplinas.txt", "w");
    
    fprintf(arq, "%d %d\n", tamanhoVetor_disciplinas, quantidade_disciplinas);
    for (int i = 0; i < quantidade_disciplinas; i++) {
        fprintf(arq, "%d;%s\n", disciplinas[i].cod, disciplinas[i].nome);
    }
    fclose(arq);
}

void carregar_disciplinas() {
    FILE *arq = fopen("disciplinas.txt", "r");

    // Lê a capacidade e a quantidade salvas
    fscanf(arq, "%d %d", &tamanhoVetor_disciplinas, &quantidade_disciplinas);
    
    disciplinas = (Disciplina *)malloc(tamanhoVetor_disciplinas * sizeof(Disciplina));

    for (int i = 0; i < quantidade_disciplinas; i++) {
        fscanf(arq, "%d;%[^\n]", &disciplinas[i].cod, disciplinas[i].nome);
    }

    fclose(arq);
}

void inserir_disciplina() {

    Disciplina nova;
    while (1){
        int cont = 0;
        printf("Nome da disciplina: ");
        scanf(" %[^\n]", nova.nome);
        printf("Codigo da disciplina: ");
        scanf("%d", &nova.cod);
   
        // Verificar se a disciplina já existe
        for (int i = 0; i < quantidade_disciplinas; i++) {
            if (disciplinas[i].cod == nova.cod) {
                printf("Erro: Ja existe uma disciplina com esse codigo.\n");
            }
        }
        if (cont == 0){
            break;
        }
    }
    disciplinas[quantidade_disciplinas] = nova;
    quantidade_disciplinas++;
    redimensionar_disciplinas(); 
    salvar_disciplinas();
    printf("Disciplina cadastrada com sucesso.\n");
}

void imprimir_disciplinas() {
    if (quantidade_disciplinas == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    printf("\n--- Lista de Disciplinas ---\n");
    for (int i = 0; i < quantidade_disciplinas; i++) {
        printf("Codigo: %d - Nome: %s\n", disciplinas[i].cod, disciplinas[i].nome);
    }
}

void buscar_disciplina() {
    int cod, cont = 0;
    printf("Digite o codigo da disciplina para buscar: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade_disciplinas; i++) {
        if (disciplinas[i].cod == cod) {
            printf("Encontrado: Codigo: %d - Nome: %s\n", disciplinas[i].cod, disciplinas[i].nome);
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
}

void atualizar_disciplina() {
    int cod, cont = 0;
    printf("Digite o codigo da disciplina para atualizar: ");
    scanf("%d", &cod);
    
    for (int i = 0; i < quantidade_disciplinas; i++) {
        if (disciplinas[i].cod == cod) {
            printf("Digite o novo nome: ");
            scanf("%[^\n]", disciplinas[i].nome);
            salvar_disciplinas();
            printf("Disciplina atualizada com sucesso!\n");
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
}

void excluir_matricula2(int id_disciplina_excluir){
    salvar_matriculas();
    carregar_matriculas();
    int encontrado = 0;
    for(int i = 0; i < total_matriculas; i++){
        if(matriculas_vetor[i].id_disciplina == id_disciplina_excluir){
            for(int j = i; j < total_matriculas - 1; j++){
                matriculas_vetor[j] = matriculas_vetor[j + 1];
            }
            total_matriculas--;
            redimensionar_matriculas();
            salvar_matriculas();
            printf("Matricula do Aluno %d excluida com sucesso.\n", id_disciplina_excluir);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("Matricula para o Aluno %d nao encontrada.\n", id_disciplina_excluir);
    }
}

void excluir_disciplina_na_turma(int id_disciplina_excluir){
    int id, cont = 0;
    int i = 0;
    while (i < total_turmas){
        if (turmas[i].cod_disciplina == id_disciplina_excluir){
            for(int j = i; j < total_turmas - 1; j++){
                turmas[j] = turmas[j + 1];
            }
            cont++;
            total_turmas--;
        }
        i++;
    }
    if (cont == 0){
        printf("Turma nao encontrada.\n");
    }else{
        redimensionar_turma(); 
        salvar_turmas();
        printf("Turma excluida com sucesso.\n");
    }
}

void excluir_disciplina() {
    int cod, cont = 0;
    printf("Digite o codigo da disciplina para excluir: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade_disciplinas; i++) {
        if (disciplinas[i].cod == cod) {
            excluir_matricula2(cod);
            excluir_disciplina_na_turma(cod);
            for (int j = i; j < quantidade_disciplinas - 1; j++) {
                disciplinas[j] = disciplinas[j + 1];
            }
            quantidade_disciplinas--;
            redimensionar_disciplinas();
            salvar_disciplinas();
            printf("Disciplina excluida com sucesso!\n");
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
}