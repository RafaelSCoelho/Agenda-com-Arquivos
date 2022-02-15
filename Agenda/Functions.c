
#include "Cabeçalho.h"

typedef struct agenda
{
    char nome[20];
    int celular;
    char email[30];
}agenda;

FILE* arquivo;
errno_t err;
agenda contato;
char nome[20];
char aux[20];

char cabecario()
{
    system("cls");
    printf("\n\n\t--------------    Agenda de Contatos:    --------------\n");
    printf("\t|\t\t[1]Adicionar contato                  |\n");
    printf("\t|\t\t[2]Mostrar lisa de contatos           |\n");
    printf("\t|\t\t[3]Procurar contato pelo Nome         |\n");
    printf("\t|\t\t[4]Modificar contato                  |\n");
    printf("\t|\t\t[5]Remover contato                    |\n");
    printf("\t|\t\t[6]Sair                               |\n");
    printf("\t|-----------------------------------------------------|\n");
    printf("\t|OPCAO: ");
    return (toupper(_getche()));
}

int analisanom(char nome[])
{
    fread(&contato, sizeof(agenda), 1, arquivo);
    while (!feof(arquivo))
    {
        if (strcmp(contato.nome, nome) == 0)

        {
            fseek(arquivo, sizeof(agenda), SEEK_CUR);
            return 1;
        }
        fread(&contato, sizeof(agenda), 1, arquivo);
    }

    return 0;
}

void adicionar()
{
    char nome[20];
    static char email[30] = {'\0'};

    err = fopen_s(&arquivo, "banco.bin", "a+b");
    if (arquivo == NULL)
    {
        printf("\n!!!VAZIO!!!\n");
        return;
    }
    printf("\n\n\tDigite o nome: ");
    fflush(stdin);
    gets(nome);
    if (analisanom(nome) == 1)
    {

        printf("\n\tNome ja existe.\n");
    }
    else
    {
        strcpy_s(contato.nome, sizeof contato.nome, nome);
        printf("\n\tDigite o email: ");
        fflush(stdin);
        gets(email);
        strcpy_s(contato.email, sizeof contato.email, email);
        printf("\n\tDigite o celular: ");
        scanf_s("%d", &contato.celular);
        fwrite(&contato, sizeof(agenda), 1, arquivo);
    }
    fclose(arquivo);
}

void modificar()
{
    char nome[20];
    static char email[30] = { '\0' };

    err = fopen_s(&arquivo, "banco.bin", "r+b");
    if (arquivo == NULL)
    {
        printf("\n!!!VAZIO!!!\n");
        return;
    }
    printf("\n\n\tDigite nome do contato: ");
    fflush(stdin);
    gets(nome);

    if (analisanom(nome) == 1)
    {
        printf("\n\tDigite um novo nome do contato: ");
        fflush(stdin);
        gets(nome);
        strcpy_s(contato.nome, sizeof contato.nome, nome);
        printf("\n\tDigite o email: ");
        fflush(stdin);
        gets(email);
        strcpy_s(contato.email, sizeof contato.email, email);
        printf("\n\tDigite um novo numero do contato: ");
        scanf_s("%d", &contato.celular);
        fwrite(&contato, sizeof(agenda), 1, arquivo);
    }

    else
    {
        printf("\n\tNome nao existe.\n");
    }

    fclose(arquivo);
}

void remover()
{
    static char nome[20] = {'\0'};
    FILE* file;
  

    err = fopen_s(&arquivo, "banco.bin", "r+b");
    if (arquivo == NULL)
    {
        printf("\n\t!!!VAZIO!!!\n");
        return;
    }

    err = fopen_s(&file, "banco.txt", "a+b");
    printf("\n\tDigite nome do contato a deletar: ");
    fflush(stdin);
    gets(nome);

    fread(&contato, sizeof(agenda), 1, arquivo);
    while (!feof(arquivo))
    {

        if (strcmp(contato.nome, nome) != 0)
        {
            fwrite(&contato, sizeof(agenda), 1, file);
        }
        fread(&contato, sizeof(agenda), 1, arquivo);

    }
    fclose(arquivo);
    fclose(file);

    system("del banco.bin");
    system("ren banco.txt banco.bin");
}
void procurar()
{
    char nome[20];

    err = fopen_s(&arquivo, "banco.bin", "r+b");
    if (arquivo == NULL)
    {
        printf("\n\t!!!VAZIO!!!\n");
        return;
    }
    printf("\n\tDigite o nome do contato a procurar: ");
    fflush(stdin);
    gets(nome);

    if (analisanom(nome) == 1)
    {
        fread(&contato, sizeof(agenda), 1, arquivo);
        printf("\n\t|-----------------------------------------------------------------------");
        printf("\t|     NOME     |          CELULAR          |     E-MAIL      \n");
        printf("\t|-----------------------------------------------------------------------\n");
        printf("\t       %-20s   %8d             %-20s\n", contato.nome, contato.celular, contato.email);
        printf("\t------------------------------------------------------------------------\n");

    }

    else
    {
        printf("\n\tContato nao existe.\n");
    }

    fclose(arquivo);
}



void lista()
{
    err = fopen_s(&arquivo, "banco.bin", "r+b");
    if (arquivo == NULL)
    {
        printf("\n\t!!!VAZIO!!!\n");
        return;
    }
    printf("\n\t|-----------------------------------------------------------------------");
    printf("\t|     NOME     |          CELULAR          |     E-MAIL      \n");
    printf("\t|-----------------------------------------------------------------------");

    fread(&contato, sizeof(agenda), 1, arquivo);
    while (!feof(arquivo))
    {

        printf("\t|       %-20s  %8d          %-20s\n", contato.nome, contato.celular, contato.email);
        fread(&contato, sizeof(agenda), 1, arquivo);
    }
    printf("\t|-----------------------------------------------------------------------");

    fclose(arquivo);
}
