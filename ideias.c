#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char texto_t[80];

texto_t *nome;
texto_t *endereco;
long long int *telefone_res; 
long long int *telefone_cel;
int *data_nascimento;

int quantos;

void inicializar(int tam)
{
    nome = (texto_t *) malloc(tam * sizeof(texto_t));
    endereco = (texto_t *) malloc(tam * sizeof(texto_t)); 
    telefone_res = (long long int *) malloc(tam * sizeof(long long int)); 
    telefone_cel = (long long int *) malloc(tam * sizeof(long long int)); 
    data_nascimento = (int *) malloc(tam * sizeof(int));
}

void carregar(const char *nome_arq) {
    FILE *arq = fopen(nome_arq, "r");
    char linha[500];
    if (arq != NULL) // arquivo existe
    {
        fscanf(arq, "%d\n", &quantos);
        inicializar(quantos + 10);
        for (int i = 0; i < quantos; i++)
        {
            fgets(linha, 499, arq);
            sscanf(linha, "%[^;]s", nome[i]);
            printf("%s\n", nome[i]);
        }
    }
    else // arquivo não existe
    {
        quantos = 0;
        inicializar(10);
    }
}

int menu ()
{
    int opcao;
    
    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Pesquisar\n");
    printf("4. Alterar\n");
    printf("5. Listar todos\n");
    printf("6. Sair\n");
    printf("Opcao: ");

    scanf("%d", &opcao);
    
    return opcao;
}

int main()
{
    const char *nome_arq = "dados.txt";
    //nome, endereco, telefone_res; telefone_cel; data_nascimento

    // adicionar
    // remover
    // alterar
    // pesquisar por nome
    // listar
    // sair

       //carregar(nome_arq);
    carregar("contatos.txt");
    return 0;
}