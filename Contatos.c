#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **nome;
char **endereco;
long long int *telefone_res;
long long int *telefone_cel;
int *data_nascimento;
int n_contatos;


void reconhecer(int n_n_contatos){
    nome = (char **)malloc(n_n_contatos * sizeof(char*));
    for(int i=0;i<n_n_contatos;i++)
        nome[i] = malloc(80 * sizeof(char));
    endereco = (char **) malloc(n_n_contatos * sizeof(char*));
    for(int i=0;i<n_n_contatos;i++)
        endereco[i] = malloc(80 * sizeof(char));
    telefone_res = (long long int *) malloc(n_n_contatos * sizeof(long long int)); 
    telefone_cel = (long long int *) malloc(n_n_contatos * sizeof(long long int)); 
    data_nascimento = (int *) malloc(n_n_contatos * sizeof(int));
}
void carregar(const char *contatos){
    FILE *file = fopen("contatos.txt", "r");
    if (file == NULL){
        printf("Nao foi possivel acessar lista de contatos");
        exit(0);
    }
    char linha[500];
    fscanf(file,"%d\n", &n_contatos);
    reconhecer(n_contatos + 5);
    for(int i=0;i<n_contatos;i++){
        fgets(linha, 499, file);
        sscanf(linha, "%[^;]s", nome[i]);
    }
    fclose(file);
}
void adicionarContato(const char *contatos){
    fflush(stdin);
    char *contato = (char *)malloc(500 * sizeof(char));
    FILE *file = fopen(contatos, "r");
    FILE *file2 = fopen("temp.dat", "w");
    char linha[500];
    int linhaAtual=1;

    escrever("Adicionar Contato", "Digite o novo Contato da seguinte maneira:", "<Nome>;<Endereco>;<Telefone>;<Celular>;<Nascimento>", "void");

    fgets(contato, 499, stdin);
    fprintf(file2,"%d\n", n_contatos+1);
    fclose(file2);

    file2 = fopen("temp.dat", "a");
    while(fgets(linha,499,file)!=NULL){
        if(linhaAtual != 1)
            fputs(linha, file2);
        linhaAtual++;
    }
    fprintf(file2,"%s",contato);

    fclose(file);
    fclose(file2);
    file = fopen(contatos, "w");
    file2 = fopen("temp.dat", "r");
    while(fgets(linha,499,file2)!=NULL){
        fputs(linha,file);
    }
    fclose(file);
    fclose(file2);
    voltarMenu();
}
void removerContato(const char *contatos){
    char *contato = (char *)malloc(100 * sizeof(char));
    char linha[500];
    int listar;

    escrever("Excluir Contato", "Deseja listar os contatos?", "(1)Sim", "(2)Nao");
    scanf("%d",&listar);
    if(listar == 1)
        listarContatos(contatos, 0);

    printf("Digite o nome do contato que deseja excluir:");
    scanf("%s", contato);

    FILE *file = fopen("contatos.txt", "r+");
    FILE *file2 = fopen("temp.dat", "w");
    fgets(linha,499,file);
    fputs(linha,file2);
    for(int i=0;i<n_contatos; i++){
        fgets(linha,499,file);
        if(strcmp(contato, nome[i])!=0)
            fputs(linha,file2);
    }
    fclose(file);
    fclose(file2);
    file = fopen(contatos, "w");
    fprintf(file, "%d\n", n_contatos-1);
    fclose(file);

    file = fopen(contatos, "a");
    file2 = fopen("temp.dat", "r");
    for(int linhaAtual=1;fgets(linha, 499, file2) != NULL;linhaAtual++)
        if(linhaAtual != 1)
            fputs(linha, file);
    fclose(file);
    fclose(file2);
    voltarMenu();
}
void pesquisarPorNome(const char *contatos){
    FILE *file = fopen(contatos, "r");
    char *contato = (char *)malloc(100 * sizeof(char));
    char *linha = (char *)malloc(500 * sizeof(char));
    int achou=0;

    escreverTitulo("Pesquisa por Nome");
    printf("Digite o nome do Contato que deseja procurar:");
    scanf("%s", contato);

    fgets(linha, 499, file);
    for(int i=0;i<n_contatos;i++){
        fgets(linha, 499, file);
        if(strcmp(contato, nome[i])==0){
            linha[strlen(linha)-1] = linha[strlen(linha)];
            escrever("Contato encontrado!", linha, "void","void");
            achou=1;
        }
    }
    
    if(achou == 0)
        printf("Nao foi possivel localizar este contato! Verifique a lista e tente novamente.\n");
    fclose(file);
    voltarMenu();
}
void alterarContato(const char *contatos){
    FILE *file = fopen(contatos, "r");
    FILE *file2 = fopen("temp.dat", "w");
    char *contato = (char *)malloc(100 * sizeof(char));
    char *linha = (char *)malloc(500 * sizeof(char));
    int achou=0, listar;

    escrever("Alterar Contato","Deseja listar os contatos?", "(1)Sim", "(2)Nao");
    scanf("%d",&listar);
    if(listar == 1)
        listarContatos(contatos, 0);

    printf("Digite o nome do contato que deseja alterar:");
    
    scanf("%s",contato);
    
    fgets(linha, 499, file);
    fprintf(file2, linha);
    fclose(file2);
    file2 = fopen("temp.dat", "a+");
    for(int i=0;i<n_contatos;i++){
        fgets(linha, 499, file);
        if(strcmp(contato, nome[i]) != 0){
            fputs(linha,file2);
        }
        else {
            linha[strlen(linha)-1] = linha[strlen(linha)];
            escrever("Contato achado!", linha, "Digite-o com as alteracoes desejadas:","<Nome>;<Endereco>;<Telefone>;<Celular>;<Nascimento>");
            fflush(stdin);
            fgets(linha, 499, stdin);
            fputs(linha,file2);
            escreverTitulo("Alterado com sucesso!");
        }
    }
    fclose(file);
    file = fopen(contatos, "w");
    rewind(file2);
    for(int i=0;i<=n_contatos;i++){
        fgets(linha, 499, file2);
        fputs(linha, file);
    }
    fclose(file);
    fclose(file2);
    voltarMenu();
}
void listarContatos(const char *contatos, int voltar){
    FILE *file = fopen("contatos.txt", "r");
    char linha[80];
    escreverTitulo("Lista de contatos");
    
    while(fgets(linha, 80, file) != NULL){
        printf("%s", linha);
    }
    printf("\n________________________________________________________________________\n\n");
    fclose(file);
    if(voltar == 1)
        voltarMenu();
}
void printMenu(int banner){
    if(banner == 1){
        printf("________________________________________________________________________\n\n");
        printf(" _______  _______  _       _________ _______ _________ _______  _______ \n(  ____ \\(  ___  )( (    /|\\__   __/(  ___  )\\__   __/(  ___  )(  ____ \\\n| (    \\/| (   ) ||  \\  ( |   ) (   | (   ) |   ) (   | (   ) || (    \\/\n| |      | |   | ||   \\ | |   | |   | (___) |   | |   | |   | || (_____ \n| |      | |   | || (\\ \\) |   | |   |  ___  |   | |   | |   | |(_____  )\n| |      | |   | || | \\   |   | |   | (   ) |   | |   | |   | |      ) |\n| (____/\\| (___) || )  \\  |   | |   | )   ( |   | |   | (___) |/\\____) |\n(_______/(_______)|/    )_)   )_(   |/     \\|   )_(   (_______)\\_______)\n");
    }
    printf("\n________________________________________________________________________\n\n");
    printf("                           Selecione sua opcao:\n\n");
    printf("        (1)Adicionar  (2)Remover  (3)Pesquisar  (4)Alterar\n");
    printf("                     (5)Listar todos  (6)Sair\n");
    printf("\n________________________________________________________________________\n\n");
}
void escrever(char *titulo, char *linha1, char *linha2, char *linha3){
    escreverTitulo(titulo);
    bordasTexto(linha1);
    if(linha2 != "void")
        bordasTexto(linha2);
    if(linha3 != "void") {
        bordasTexto(linha3);
        printf("\n");
    }
    printf("________________________________________________________________________\n\n");
}
void bordasTexto(char *texto2){
    int espaco = 69 - strlen(texto2);
    printf("= %s", texto2);
    for(int i=0;i<espaco;i++)
        printf(" ");
    printf("=\n");
}
void escreverTitulo(char *titulo){

    int espaco = 36 - (strlen(titulo)/2);
    printf("========================================================================\n");
    for(int i=0; i<espaco; i++)
        printf(" ");
    puts(titulo);
    printf("========================================================================\n\n");
}
void voltarMenu(){
    int escolha;
    escrever("Deseja voltar ao Menu?", "(1)Sim", "(2)Nao","void");
    scanf("%d", &escolha);
    if(escolha==1){
        system("cls");
        menu(0);
    }
}
int menu(int banner) {
    system("cls");
    int entrada;
    printMenu(banner);
    carregar("contatos.txt");

    scanf("%d", &entrada);
    switch (entrada)
    {
    case 1: adicionarContato("contatos.txt");
        break;
    case 2: removerContato("contatos.txt");
        break;
    case 3: pesquisarPorNome("contatos.txt");
        break;
    case 4: alterarContato("contatos.txt");
        break;
    case 5: listarContatos("contatos.txt", 1);
        break;
    case 6: exit(0);
    }
}
int main() {
    menu(1);
}