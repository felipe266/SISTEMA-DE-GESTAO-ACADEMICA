#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turma.h"
#include "disciplina.h"
#include "matricula.h"


Turma *turmas = NULL;
int total_turmas = 0;
int tamanho_turma = 1; 

void redimensionar_turma(){
    if(total_turmas >= 0.75*tamanho_turma){
        tamanho_turma *= 2;
        turmas = realloc(turmas, tamanho_turma * sizeof(Turma));
    }else if(total_turmas <= 0.25*tamanho_turma){ 
        tamanho_turma /= 2;
        turmas = realloc(turmas, tamanho_turma * sizeof(Turma));
    }
}

void salvar_turmas(){
    FILE *arquivo = fopen("turmas.txt", "w");

    fprintf(arquivo, "%d %d\n", tamanho_turma, total_turmas); 
    for(int i = 0; i < total_turmas; i++){
        fprintf(arquivo, "%d;%d\n", turmas[i].cod_disciplina, turmas[i].id);
    }
    fclose(arquivo);
}

void carregar_turmas(){
    FILE *arquivo = fopen("turmas.txt", "r");
    
    fscanf(arquivo, "%d %d\n", &tamanho_turma, &total_turmas); 
    turmas = (Turma *)malloc(tamanho_turma * sizeof(Turma)); 
    
    for(int i = 0; i < total_turmas; i++){
        fscanf(arquivo, "%d;%d\n", &turmas[i].cod_disciplina, &turmas[i].id);
    }
    fclose(arquivo);
}

void inserir_turma(){
    while (1){
        Turma nova;
        printf("ID da turma: ");
        scanf("%d", &nova.id);

        printf("Codigo da disciplina: ");
        scanf("%d", &nova.cod_disciplina);

        carregar_disciplinas();
        int tem = 0;
        for (int i = 0; i < quantidade_disciplinas; i++){
            if (disciplinas[i].cod == nova.cod_disciplina){
                tem = 1;
            }
        }
        if (tem == 1){
            int cont = 0;
            for (int i = 0; i < total_turmas; i++) {
                if (turmas[i].id == nova.id && turmas[i].cod_disciplina == nova.cod_disciplina) {
                    printf("Erro: Ja existe uma disciplina cadastrada nessa turma.\n");
                    cont++;
                    break;

                }
            }
            turmas[total_turmas] = nova;
            total_turmas++;
            redimensionar_turma(); 
            salvar_turmas();
            printf("Turma cadastrada com sucesso.\n");
            break;
        }else{
            printf("Nao tem disciplia com esse codigo");
            break;       
        }
    }
}

void listar_turmas(){
    if(total_turmas == 0){
        printf("Nenhuma turma cadastrada.\n");
        return;
    }
    printf("\n--- Lista de Turmas ---\n");
    int *turmas_unicas = malloc(total_turmas * sizeof(int));
    int quat_turmas_unicas = 0;
    for(int i = 0; i < total_turmas; i++){
        int tem_salvo = 0;
        for (int j = 0; j < quat_turmas_unicas; j++){
            if (turmas_unicas[j] == turmas[i].id){
                tem_salvo = 1;
                break;
            }
        }
        if(tem_salvo == 0){
            printf("--------------\n");
            printf("ID da Turma tem essas disc: %d\n", turmas[i].id);
            for (int n = i; n < total_turmas; n++){
                if (turmas[n].id == turmas[i].id){
                    printf("Codigo Disciplina: %d\n", turmas[n].cod_disciplina);   
                }   
            }
            turmas_unicas[quat_turmas_unicas] = turmas[i].id;
            quat_turmas_unicas++;
        }
    }
}    

//terminar mais tarde
void buscar_turma(){
    int id, cont = 0;
    printf("ID da turma para buscar: ");
    scanf("%d", &id);
    for(int i = 0; i < total_turmas; i++){
        if(turmas[i].id == id){
            printf("Turma encontrada:\n");
            printf("ID: %d\n", turmas[i].id);
            for (int n = i; n < total_turmas; n++){
                if (turmas[n].id == turmas[i].id){
                    printf("Codigo Disciplina: %d\n", turmas[n].cod_disciplina);   
                }   
            }
            cont++;
            break;
        }
    }
    if (cont == 0){
        printf("Turma nao encontrada.\n");
    }
}

void atualizar_turma(){
    int id, cod, cont = 0;
    printf("ID da turma para atualizar: ");
    scanf("%d", &id);
    printf("Codigo de disciplina para atualizar: ");
    scanf("%d", &cod);
    for(int i = 0; i < total_turmas; i++){
        if(turmas[i].id == id && turmas[i].cod_disciplina == cod){
            printf("Novo codigo: ");
            scanf("%d", turmas[i].cod_disciplina);
            cont++;
            break;
        }
    }
    if (cont == 0){
         printf("Turma nao encontrada.\n");
    }else{
        salvar_turmas();
        printf("Turma atualizada com sucesso.\n");
    }
}

void excluir_turma(){
    int id, cont = 0;
    printf("ID da turma para excluir: ");
    scanf("%d", &id);
    int i = 0;
    while (i < total_turmas){
        if (turmas[i].id == id){
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