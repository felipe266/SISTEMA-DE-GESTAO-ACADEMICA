#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricula.h" 
#include "disciplina.h"
#include "aluno.h"


Matricula* matriculas_vetor = NULL;
int total_matriculas = 0;
int capacidade_matriculas = 1;

void redimensionar_matriculas(){

    if(total_matriculas >= 0.75*capacidade_matriculas){
        capacidade_matriculas *= 2;
        matriculas_vetor = realloc(matriculas_vetor, capacidade_matriculas * sizeof(Matricula));
    }else if(total_matriculas <= 0.25*capacidade_matriculas){ 
        capacidade_matriculas /= 2;
        matriculas_vetor = realloc(matriculas_vetor, capacidade_matriculas * sizeof(Matricula));
    }
}

void salvar_matriculas() {
    FILE* f = fopen("matriculas.txt", "w");

    fprintf(f, "%d %d\n", capacidade_matriculas, total_matriculas); 
    for (int i = 0; i < total_matriculas; i++) {
        fprintf(f, "%d;%d;%.2f\n", matriculas_vetor[i].id_aluno, matriculas_vetor[i].id_disciplina, matriculas_vetor[i].media);
    }
    fclose(f);
}

void carregar_matriculas(){
    FILE* f = fopen("matriculas.txt", "r");

    fscanf(f, "%d %d\n", &capacidade_matriculas, &total_matriculas); 
    matriculas_vetor = (Matricula *)malloc(capacidade_matriculas * sizeof(Matricula));

    for (int i = 0; i < total_matriculas; i++){
        fscanf(f, "%d;%d;%.2f\n", &matriculas_vetor[i].id_aluno, &matriculas_vetor[i].id_disciplina, &matriculas_vetor[i].media);
    }
    fclose(f);
}


void inserir_matricula(){

    Matricula m;
    while (1){
        int cont = 0;
        printf("ID do aluno: ");
        scanf("%d", &m.id_aluno);
        printf("ID da disciplina: ");
        scanf("%d", &m.id_disciplina);

        int tem_disciplina = 0;
        for (int i = 0; i < quantidade_disciplinas; i++){
            if (disciplinas[i].cod == m.id_disciplina){
                tem_disciplina = 1;
            }
        }
        int tem_aluno = 0;
        for (int i = 0; i < total_alunos; i++){
            if (alunos[i].id == m.id_aluno){
                tem_aluno = 1;
            }
        }
        if (tem_disciplina == 1 && tem_aluno == 1){
            // Verificar se a matrícula (aluno na disciplina) já existe
            for(int i = 0; i < total_matriculas; i++){
                if(matriculas_vetor[i].id_aluno == m.id_aluno && matriculas_vetor[i].id_disciplina == m.id_disciplina){
                    printf("Erro: Ja existe uma matricula para este aluno nesta disciplina.\n");
                    cont++;
                }
            }
            if (cont == 0){
                printf("media: ");
                scanf("%f", &m.media);
                matriculas_vetor[total_matriculas] = m;
                total_matriculas++;
                redimensionar_matriculas(); 
                salvar_matriculas();
                printf("Matricula inserida com sucesso!\n");
                break;
            }
        }else{
            printf("Erro: Disciplna ou aluno nao encontrado");
        }
    }
}


void listar_matriculas(){
    if (total_matriculas == 0) {
        printf("Nenhuma matricula cadastrada.\n");
        return;
    }
    printf("\n--- Lista de Matriculas ---\n");
    for(int i = 0; i < total_matriculas; i++){
        printf("Aluno: %d | disciplina: %d | Nota: %.2f\n", matriculas_vetor[i].id_aluno, matriculas_vetor[i].id_disciplina, matriculas_vetor[i].media);
    }
}

void buscar_matricula(){
    int id_aluno_busca, id_disciplina_busca;
    printf("Digite o ID do aluno para buscar a matricula: ");
    scanf("%d", &id_aluno_busca);
    printf("Digite o ID da disciplina para buscar a matricula: ");
    scanf("%d", &id_disciplina_busca);

    int encontrado = 0;
    for(int i = 0; i < total_matriculas; i++){
        if(matriculas_vetor[i].id_aluno == id_aluno_busca && matriculas_vetor[i].id_disciplina == id_disciplina_busca){
            printf("Matricula encontrada:\n");
            printf("Aluno: %d | disciplina: %d | Nota: %.2f\n", matriculas_vetor[i].id_aluno, matriculas_vetor[i].id_disciplina, matriculas_vetor[i].media);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Nenhuma Matricula para o Aluno %d na disciplina %d nao foi encontrada.\n", id_aluno_busca, id_disciplina_busca);
    }
}

void atualizar_matricula(){
    int id_aluno_atualizar, id_disciplina_atualizar;
    printf("Digite o ID do aluno da matricula para atualizar: ");
    scanf("%d", &id_aluno_atualizar);
    printf("Digite o ID da disciplina da matricula para atualizar: ");
    scanf("%d", &id_disciplina_atualizar);

    int encontrado = 0;
    for(int i = 0; i < total_matriculas; i++){
        if(matriculas_vetor[i].id_aluno == id_aluno_atualizar && matriculas_vetor[i].id_disciplina == id_disciplina_atualizar){
            printf("Matricula encontrada:\n");
            printf("disciplina atual: %d | Nota atual: %.2f\n", matriculas_vetor[i].id_disciplina, matriculas_vetor[i].media);

            printf("Digite a nova nota: "); 
            scanf("%f", &matriculas_vetor[i].media);

            salvar_matriculas();
            printf("Dados da matricula atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Matricula para o Aluno %d na disciplina %d nao encontrada.\n", id_aluno_atualizar, id_disciplina_atualizar);
    }
}

void excluir_matricula(){
    int id_aluno_excluir, id_disciplina_excluir;
    printf("Digite o ID do aluno da matricula para excluir: ");
    scanf("%d", &id_aluno_excluir);
    printf("Digite o ID da disciplina da matricula para excluir: ");
    scanf("%d", &id_disciplina_excluir);

    int encontrado = 0;
    for(int i = 0; i < total_matriculas; i++){
        if(matriculas_vetor[i].id_aluno == id_aluno_excluir && matriculas_vetor[i].id_disciplina == id_disciplina_excluir){
            for(int j = i; j < total_matriculas - 1; j++){
                matriculas_vetor[j] = matriculas_vetor[j + 1];
            }

            total_matriculas--;
            redimensionar_matriculas();
            salvar_matriculas();
            printf("Matricula do Aluno %d na disciplina %d excluida com sucesso.\n", id_aluno_excluir, id_disciplina_excluir);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("Matricula para o Aluno %d na disciplina %d nao encontrada.\n", id_aluno_excluir, id_disciplina_excluir);
    }
}

void mediaporaluno_matriculas(){
    FILE *arquivo = fopen("medias_do_aluno_aprovados.txt", "w");
    FILE *arquivo2 = fopen("medias_do_alunos_reprovados.txt", "w");
    int sucesso = 0;
    for (int i = 0; i < total_alunos; i++){
        int quant_disc = 0; 
        float soma_das_medias = 0;
        for (int n = 0; n < total_matriculas; n++){
            if (alunos[i].id == matriculas_vetor[n].id_aluno){
                quant_disc++;
                soma_das_medias += matriculas_vetor[n].media;
            }
        }
        if (quant_disc != 0){
            float media = soma_das_medias/quant_disc;
            if (media >= 7){
                fprintf(arquivo, "aluno: %s da matricula: %d tem media: %.2f\n", alunos[i].nome, alunos[i].id, media);
            }else{
                fprintf(arquivo2, "aluno: %s da matricula: %d tem media: %.2f\n", alunos[i].nome, alunos[i].id, media);
            }
            sucesso = 1;
        }
    }
    if (sucesso = 1){
        printf("Lista de alunos aprovados e reprovados feita");
    }
    
    fclose(arquivo);
    fclose(arquivo2);
}

void mediaPordisciplina_matriculas() {
    printf("\n--- Media das Disciplinas ---\n");

    if (total_matriculas == 0) {
        printf("Nenhuma matricula para calcular medias.\n");
        return;
    }

    FILE *arquivo = fopen("medias_disciplinas.txt", "r");
    if (arquivo != NULL) {
    
        char linha[256];
        printf("\n--- Medias anteriores no arquivo ---\n");
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            printf("%s", linha);
        }
        fclose(arquivo);
    }

    arquivo = fopen("medias_disciplinas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir ou criar o arquivo de medias.\n");
        return;
    }

    int* disciplinas_unicas = malloc(total_matriculas * sizeof(int));
    if (disciplinas_unicas == NULL) {
        printf("Erro de alocacao de memoria para disciplinas unicas.\n");
        fclose(arquivo);
        return;
    }

    int qtddisciplinasUnicas = 0;

    for (int i = 0; i < total_matriculas; i++) {
        int jaRegistrada = 0;
        for (int j = 0; j < qtddisciplinasUnicas; j++) {
            if (disciplinas_unicas[j] == matriculas_vetor[i].id_disciplina) {
                jaRegistrada = 1;
                break;
            }
        }
        if (!jaRegistrada) {
            disciplinas_unicas[qtddisciplinasUnicas++] = matriculas_vetor[i].id_disciplina;
        }
    }

    fprintf(arquivo, "\n--- Novas medias ---\n");

    for (int i = 0; i < qtddisciplinasUnicas; i++) {
        int disciplina_atual = disciplinas_unicas[i];
        int qtd_alunos_na_disciplina = 0;
        float soma_notas = 0.0;

        for (int j = 0; j < total_matriculas; j++) {
            if (matriculas_vetor[j].id_disciplina == disciplina_atual) {
                soma_notas += matriculas_vetor[j].media;
                qtd_alunos_na_disciplina++;
            }
        }

        if (qtd_alunos_na_disciplina > 0) {
            float media = soma_notas / qtd_alunos_na_disciplina;
            printf("Disciplina %d - Media: %.2f\n", disciplina_atual, media);
            fprintf(arquivo, "Disciplina %d - Media: %.2f\n", disciplina_atual, media);
        }
    }

    free(disciplinas_unicas);
    fclose(arquivo);
    printf("Novas medias gravadas em 'medias_disciplinas.txt'.\n");
}


void agruparPordisciplina_matriculas(){
    printf("\n--- Alunos agrupados por disciplina ---\n");

    if (total_matriculas == 0) {
        printf("Nenhuma matricula para agrupar.\n");
        return;
    }

    
    int* disciplinas_unicas = malloc(total_matriculas * sizeof(int));
    if (disciplinas_unicas == NULL) {
        printf("Erro de alocacao de memoria para disciplinas unicas.\n");
        return;
    }
    int qtddisciplinasUnicas = 0;

    
    for(int i = 0; i < total_matriculas; i++){
        int jaRegistrada = 0;
        for(int j = 0; j < qtddisciplinasUnicas; j++){
            if(disciplinas_unicas[j] == matriculas_vetor[i].id_disciplina){
                jaRegistrada = 1;
                break;
            }
        }
        if(!jaRegistrada){
            disciplinas_unicas[qtddisciplinasUnicas++] = matriculas_vetor[i].id_disciplina;
        }
    }

    
    for(int i = 0; i < qtddisciplinasUnicas; i++){
        int disciplina_atual = disciplinas_unicas[i];
        printf("disciplina %d - Alunos: ", disciplina_atual);

        for(int j = 0; j < total_matriculas; j++){
            if(matriculas_vetor[j].id_disciplina == disciplina_atual){
                printf("%d ", matriculas_vetor[j].id_aluno);
            }
        }
        printf("\n");
    }

    free(disciplinas_unicas); 
}