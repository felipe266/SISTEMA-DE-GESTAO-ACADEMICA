#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "matricula.h"

Aluno *alunos = NULL;
int total_alunos = 0;
int total_vetor = 1;

void redimensionar_alunos() {
    if (total_alunos >= 0.75*total_vetor) {
        total_vetor *= 2;
        alunos = realloc(alunos, total_vetor * sizeof(Aluno));
    } else if (total_alunos <= 0.25*total_vetor) {
        total_vetor /= 2;
        alunos = realloc(alunos, total_vetor * sizeof(Aluno));
    }
}

void salvar_alunos() {
    FILE *arquivo = fopen("alunos.txt", "w");

    fprintf(arquivo, "%d %d\n", total_vetor, total_alunos); 
    for (int i = 0; i < total_alunos; i++) {
        fprintf(arquivo, "%s;%d\n", alunos[i].nome, alunos[i].id);
    }
    fclose(arquivo);
}

void carregar_alunos() {
    FILE *arquivo = fopen("alunos.txt", "r");
    
    fscanf(arquivo, "%d %d\n", &total_vetor, &total_alunos); 
    alunos = (Aluno *)malloc(total_vetor * sizeof(Aluno)); 

    // Leitura dos dados dos alunos
    for (int i = 0; i < total_alunos; i++) {
        fscanf(arquivo, "%[^;];%d\n", &alunos[i].nome, &alunos[i].id);
    }
    fclose(arquivo);
}

void inserir_aluno() {

    Aluno novo_aluno;

    while (1){
        int cont = 0;

        printf("Nome do aluno: ");
        scanf(" %[^\n]", novo_aluno.nome); 

        printf("ID do aluno: ");
        scanf("%d", &novo_aluno.id);

        // Verificar se o ID já existe
        for (int i = 0; i < total_alunos; i++) {
            if (alunos[i].id == novo_aluno.id) {
                printf("Erro: Ja existe um aluno com esse ID.\n");
                cont ++;
            }
        }
        if (cont == 0){
            break;
        }
    }
    alunos[total_alunos] = novo_aluno;
    total_alunos++;
    redimensionar_alunos(); 
    salvar_alunos();
    printf("Aluno cadastrado com sucesso.\n");
}

void imprimir_alunos() {
    if (total_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        printf("\nLista de Alunos:\n");
        for (int i = 0; i < total_alunos; i++) {
            printf("------------\n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matricula: %d\n", alunos[i].id);
        }
    }
}

void buscar_aluno() {
    int id, cont = 0;
    printf("ID do aluno para buscar: ");
    scanf("%d", &id);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].id == id) {
            printf("Aluno encontrado: %s (ID: %d)\n", alunos[i].nome, alunos[i].id);
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
}

void atualizar_aluno() {
    int id, cont = 0;
    printf("ID do aluno para atualizar: ");
    scanf("%d", &id);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].id == id) {
            printf("Novo nome: ");
            scanf("%[^\n]", alunos[i].nome); 
            salvar_alunos();
            printf("Aluno atualizado com sucesso.\n");
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
}

void excluir_matricula4(int id_aluno_excluir){
    carregar_matriculas();
    int encontrado = 0;
    for(int i = 0; i < total_matriculas; i++){
        if(matriculas_vetor[i].id_aluno == id_aluno_excluir){
            for(int j = i; j < total_matriculas - 1; j++){
                matriculas_vetor[j] = matriculas_vetor[j + 1];
            }
            total_matriculas--;
            redimensionar_matriculas();
            salvar_matriculas();
            printf("Matricula do Aluno %d excluida com sucesso.\n", id_aluno_excluir);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("Matricula para o Aluno %d nao encontrada.\n", id_aluno_excluir);
    }
}

void excluir_aluno() {
    int id, cont = 0;
    printf("ID do aluno para excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].id == id){
            excluir_matricula4(id);
            for (int j = i; j < total_alunos - 1; j++) {
                alunos[j] = alunos[j+1];
            }
            total_alunos--;
            redimensionar_alunos(); 
            salvar_alunos();
            printf("Aluno excluido com sucesso.\n");
            cont++;
            break;
        }
    }
    if (cont==0){
        printf("Aluno nao encontrado.\n");   
    }
    
}