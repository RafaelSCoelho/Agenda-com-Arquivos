
#include "Cabeçalho.h"

int main()
{
    char opcao = 0;

    do
    {
        opcao = cabecario();

        switch (opcao)
        {
        case '1':
            adicionar();
            break;
        case '2':
            lista();
            break;
        case '3':
            procurar();
            break;
        case '4':
            modificar();
            break;
        case '5':
            remover();
            break;
        }

        printf("\n");
        system("PAUSE");

    } while (opcao != '6');

    return 0;
}

