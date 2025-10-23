//  BIBLIOTECAS - PROGRAMA
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  CONSTANTES
#define ITENS_MAX 5

//  STRUCTS
typedef struct {
    char nome[2];  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;
}Peca;

typedef struct {
    Peca itens[ITENS_MAX];
    int inicio;
    int fim;
    int total;
} Fila;

//  FUNÇÕES

// MICRO-FUNÇÕES
    int filacheia(Fila *f) {
        return f->total == ITENS_MAX;
    }

    int filavazia(Fila *f) {
        return f->total == 0;
    }

// FUNÇÕES PRINCIPAIS
    void InicializarFila(Fila *f){
        f->inicio = 0;
        f->fim = 0;
        f->total = 0;
    }

    Peca GerarPeca(int id){
        char tipos[] = {'I', 'O', 'T', 'L'};
        Peca nova;
        nova.nome[0] = tipos[rand() % 4];  // escolhe um tipo aleatório
        nova.nome[1] = '\0';               // garante que seja uma string válida
        nova.id = id;                      // atribui o ID passado
        return nova;                       // retorna a peça criada
    }

    void Inserir(Fila *f, Peca e){
        if(filacheia(f)){
            return;
        }

        f->itens[f->fim] = e;
        f->fim = (f->fim +1) % ITENS_MAX;
        f->total++;
    }

    Peca Retirar(Fila *f){
        Peca vazio = {{'-'}, -1};

        if(filavazia(f)){
            return vazio;
        }

        Peca e = f->itens[f->inicio];
        f->inicio = (f->inicio + 1) % ITENS_MAX;
        f->total--;
        return e;
    } 

    void ExibirFila(Fila *f) {
        printf("Fila de peças:\n");
        for (int i = 0; i < f->total; i++) {
            int pos = (f->inicio + i) % ITENS_MAX;
            printf("[%c %d]\n", f->itens[pos].nome[0], f->itens[pos].id);
        }
    }

//  ÁREA PRINCIPAL DO PROGRAMA
int main(){

    //VARIÁVEIS IMPORTANTES
    int contador_id = 0;
    int opcao_usuario;
    Fila fila;
    InicializarFila(&fila);

    do{
        printf("\n===== SEJA BEM VINDO A TETRIS STRACK =====\n");
        printf("Opções:\n");
        printf("1 - Inserir nova peça\n");
        printf("2 - Remover peça\n");
        printf("3 - Sair do jogo\n");
        printf("Escolha a sua opção:");
        scanf("%d", &opcao_usuario);

        switch (opcao_usuario){
        case 1:
            printf("-Você escolheu inserir uma nova peça\n");

            if (filacheia(&fila)) {
                printf("Fila cheia! Não é possível inserir nova peça.\n");
            } else {
                Peca nova = GerarPeca(contador_id++);
                Inserir(&fila, nova);
                printf("Peça inserida: [%c %d]\n", nova.nome[0], nova.id);
            }

            ExibirFila(&fila);
            break;
        case 2:
            printf("-Você escolheu remover uma peça\n");

            Peca removida = Retirar(&fila);
            if (removida.id != -1) {
                printf("Peça removida: [%c %d]\n", removida.nome[0], removida.id);
            } else {
                printf("Fila está vazia. Nenhuma peça removida.\n");
            }

            ExibirFila(&fila);
            break;
        case 3:
            printf("-Você escolheu sair do programa\n");
            break;        
        default:
            printf("-Você escolheu uma opção inválida\nTente outras opções\n");
        }

    }while(opcao_usuario != 3);
    return 0;
}
