#include <stdio.h>
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
    /*
    empleado.id = 0;
    strcpy(empleado.name, "mariano");
    strcpy(empleado.lastName , "mastronardi");
    empleado.salary = 2.4;
    empleado.sector = 54;
    empleado.isEmpty = 0;
    */

    initEmployees(e, MAX_QTY);

    opcion = gets(printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n\n"));

    switch(opcion)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
    /*
    e[0].id = 0;
    strcpy(e[0].name, "mariano");
    strcpy(e[0].lastName , "mastronardi");
    e[0].salary = 2.4;
    e[0].sector = 54;
    e[0].isEmpty = 0;
    */

    //printf("id %d - name %s - lastname %s - salary %.2f - sector %d isEmpty %d", empleado.id, empleado.name, empleado.lastName, empleado.salary, empleado.sector, empleado.isEmpty);

    printf("id %d - name %s - lastname %s - salary %.2f - sector %d isEmpty %d", e[0].id, e[0].name, e[0].lastName, e[0].salary, e[0].sector, e[0].isEmpty);
    return 0;
}
