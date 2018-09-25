#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayEmployees.h"

#define MAX_QTY 1000

void TotalPromedioSalarios (Employee e[], int len);

int main()
{
    Employee e[MAX_QTY];
    int opcion;
    int ix;
    int id;
    char name[20];
    char lastname[20];
    float salary;
    int sector;
    char respuesta;
    int optionedit;

    initEmployees(e, MAX_QTY);

    do
    {
        fflush(stdin);
        system("cls");
        printf("opcion %d", opcion);
        printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n4.INFORMAR\n\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            //Alta
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
            //Modificacion
            fflush(stdin);
            printf("Ingrese el ID del Empleado \n");
            scanf("%d", &id);
            ix = findEmployeeById(e, MAX_QTY, id);

            if(ix >= 0){
                printf("Ingrese un valor segun el  campo que desea modificar: \n\n1 - NOMBRE\n2 - APELLIDO\n3 - SALARIO\n4 - SECTOR\n");
                scanf("%d", &optionedit);
                switch(optionedit)
                {
                case 1:
                    printf("Ingrese un nuevo nombre: ");
                    scanf("%s", name);
                    strcpy(e[ix].name, name);
                    break;
                case 2:
                    printf("Ingrese un nuevo apellido: ");
                    scanf("%s", lastname);
                    strcpy(e[ix].lastName, lastname);
                    break;
                case 3:
                    printf("Ingrese un nuevo salario: ");
                    //scanf("%f", &salary);
                    scanf("%f", &e[ix].salary);
                    printf("indice %d\n", &ix);
                    //e[ix].salary = salary;
                    printf("e[i].salary %f\n", e[ix].salary);
                    printf("salary %f\n", salary);
                    break;
                case 4:
                    printf("Ingrese un nuevo sector: ");
                    scanf("%d", &sector);
                    e[ix].sector = sector;
                    break;
                default:
                    printf("Opcion incorrecta");
                    break;
                }
            }
            break;
        case 3:
            //Baja
            printf("Ingrese el ID a dar de baja.");
            scanf("%d", &ix);
            removeEmployee(e, MAX_QTY, ix);
            break;
        case 4:
            if(e == NULL){
                printf("Debe agregar al menos un Empleado");
            }
            else{

            //Informar

            //1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector
            sortEmployees(e, MAX_QTY, 1);
            printEmployees(e, MAX_QTY);

            //2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio.
            TotalPromedioSalarios(e, MAX_QTY);

            }
            break;
        default:
            break;
        }
        fflush(stdin);
        printf("Desea continuar? [s/n]\n");
        scanf("%c", &respuesta);
    }
    while(respuesta == 's');

    return 0;
}

void TotalPromedioSalarios (Employee e[], int len)
{
    float prom = 0;
    float total = 0;
    int cantEmployee = 0;
    int salariomayorapromedio = 0;

    for(int i = 0; i < len; i++)
    {
        if(e[i].isEmpty == 0){
            cantEmployee++;
            total += e[i].salary;
        }
    }
    prom = total/cantEmployee;

    for(int i = 0; i < len; i++){
        if(e[i].isEmpty == 0){
            if(e[i].salary > prom){
                salariomayorapromedio++;
            }
        }
    }

    printf("Total Salarios: %.2f\n", total);
    printf("Promedio Salarios: %.2f\n", prom);
    printf("Cantidad de Empleados que superan el promedio: %d\n", salariomayorapromedio);
}
