#include <stdio.h>
#include <string.h>
typedef struct{ //id -1 e inexistente.
    int ex;
    double Tpad;
    char nome[128];
} Base;

void criarC(Base *x, int id){
    int o;
    for (int i = 0; i < 100; i++){
        if(x[i].ex == -1){
            printf("Digite o Numero do contato: ");
            scanf("%lf", &x[i].Tpad);
            while(x[i].Tpad > 99999999999 || x[i].Tpad < 9999999999){
                printf("Numero mal escrito, tente novamente: ");
                scanf("%lf", &x[i].Tpad);
            }
            printf("Digite o Nome do contato ");
            scanf(" %s", x[i].nome);
            x[i].ex = 1;
        }
        printf("Deseja listar mais um contato? 1- Sim 2- Não\n");
        scanf("%i", &o);
        if(o != 1){
            break;
        }
    }
}


void procura(Base *x){
    int op;
    double num;
    char nome[128];
    printf("\nDeseja procurar por: 1- Numero 2- Nome\n");
    scanf("%i", &op);
    switch (op){
    case 1:
        printf("\nDigite o numero: ");
        scanf("%lf", &num);
        for(int i = 0; i < 100; i++){
            if(num == x[i].Tpad){
                printf("\nID %i - Nome: %s \nNumero: %.0lf ", i, x[i].nome, x[i].Tpad);
            }
        }
        break;
    case 2:
        printf("\nDigite o nome: ");
        scanf(" %s", nome);
        for(int i = 0; i < 100; i++){
            if(strcmp(nome, x[i].nome) == 0){
                printf("\nID %i - Nome: %s \nNumero: %.0lf ", i, x[i].nome, x[i].Tpad);
            }
        }
        break;
    default:
        printf("\nOpção invalida tente tovamente");
        scanf("%i", &op);
    }
}
void removC(Base *x, int id){
    double xo;
    printf("Qual o numero do contato? ");
    scanf("%lf", &xo);
    for(int i = 0; i < 100; i++){
        if(xo == x[i].Tpad){
            x[id].ex = -1;
        }
    }
}

void salvarCSV(Base *x, int tamanhoL) {
    FILE *f = fopen("contatos.csv", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    for (int i = 0; i < tamanhoL; i++) {
        if (x[i].ex == 1) {
            fprintf(f, "%s,%.0lf\n", x[i].nome, x[i].Tpad);
        }
    }
    fclose(f);
    printf("Contatos salvos em contatos.csv\n");
}

void carregarCSV(Base *x, int tamanho) {
    FILE *f = fopen("contatos.csv", "r");
    if (f == NULL) {
        printf("Arquivo contatos.csv não encontrado!\n");
        return;
    }
    char linha[256];
    int i = 0;
    while (fgets(linha, sizeof(linha), f) && i < tamanho) {
        char nome[128];
        double numero;
        if (sscanf(linha, "%127[^,],%lf", nome, &numero) == 2) {
            x[i].ex = 1;
            x[i].Tpad = numero;
            strcpy(x[i].nome, nome);
            i++;
        }
    }
    fclose(f);
    printf("Contatos carregados do contatos.csv\n");
}

void listC(Base *x){
    int blaah = 0;
    for(int i = 0; i < 100; i++){
        if(x[i].ex == 1){
            printf("\nID %i - Nome: %s \nNumero: %.0lf ", i, x[i].nome, x[i].Tpad);
            blaah = 1;
        }
    }
    if(blaah == 0){
        printf("\nVocê não possui nenhum contato\n");
    }
}


int main(){
    int o, totalC, id = 0;
    Base contatos[100];
    for(int i = 0; i < 100; i++){
        contatos[i].ex = -1;
    }
    while (o != 7){
        printf("\n 1- Inserir um novo contato\n 2- Apagar um contato\n 3- Proucurar um contato(nome ou telefone)\n 4- Listar contatos\n 5- Salvar contatos csv\n 6- Carregar a agenda do disco.\n 7- Sair\n");
        scanf("%i", &o);
        switch (o){
        case 1: //criar contato
            criarC(contatos, id);
            break;
        case 2: //remover contato
           removC(contatos, id);
            break;
        case 3: // procurar (pel nome ou pelo tel)
           procura(contatos);
            break;
        case 4: // lista de contatos
            listC(contatos);
            break;
        case 5: //salvar contatos
            salvarCSV(contatos, 100);
            break;
        case 6: //carregar contatos
            carregarCSV(contatos, 100);
            break;
        default:
       
            break;
        }
    }
}
