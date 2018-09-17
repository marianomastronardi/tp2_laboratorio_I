#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define MAX_QTY 1000

struct Employee
{
    int id;
    char name[51];
    char lastName[51];
    float salary;
    int sector;
    int isEmpty;
};

int main()
{
    struct Employee empleado, e[MAX_QTY];
    int opcion;
    int ix;
    char name[20];
    char lastname[20];
    float salary;
    int sector;
    char respuesta;

    initEmployees(e, MAX_QTY);

    do
    {
        printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            ix = rand();
            printf("Ingrese un nombre\n");
            scanf("%s", name);
            fflush(stdin);
            printf("Ingrese un apellido\n");
            scanf("%s", lastname);
            fflush(stdin);
            printf("Ingrese un salario\n");
            scanf("%f", &salary);
            printf("Ingrese un sector\n");
            scanf("%d", &sector);
            addEmployee(e, MAX_QTY, ix, name, lastname, salary, sector);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
        fflush(stdin);
        printf("Desea continuar? [s/n]\n");
        scanf("%c", &respuesta);
    }
    while(respuesta == 's');

    printf("ID          Name                    LastName    Salary  Sector\n");
    for(int i = 0; i < MAX_QTY; i++)
    {
        if(e[i].isEmpty == 0)
        {
            fflush(stdin);
            printf("%4d %20s %20s %6.2f %4d\n", e[i].id, e[i].name, e[i].lastName, e[i].salary, e[i].sector);
        }
    }
    return 0;
}
