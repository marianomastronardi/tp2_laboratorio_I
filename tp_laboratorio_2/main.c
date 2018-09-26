#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayEmployees.h"

#define MAX_QTY 1000

#define FALSE 0
#define TRUE 1
#define RET_ERROR -1
#define RET_SUCCESS 0

#define ALTA 1
#define MODI 2
#define BAJA 3
#define INFO 4

#define EDITNAME 1
#define EDITLASTNAME 2
#define EDITSALARY 3
#define EDITSECTOR 4

void TotalPromedioSalarios (Employee[], int);
int getIDEmployee();
void showMessage(int, int, int);
int hayEmpleados(Employee[], int);
int showMenuAndGetOption();
int getindex(Employee[]);
int getOptionEdit();
int getOrder();
char getRespuesta();

int main()
{
    Employee e[MAX_QTY];
    int opcion;
    int r;
    int ix;
    int orden;
    int flaghayempleado;
    char name[20];
    char lastname[20];
    float salary;
    int sector;
    char respuesta;
    int optionedit;

    initEmployees(e, MAX_QTY);

    do
    {
        r = RET_ERROR;
        opcion = showMenuAndGetOption();

        switch(opcion)
        {

        case ALTA:

            ix = MAX_QTY;
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

            r = addEmployee(e, MAX_QTY, ix, name, lastname, salary, sector);
            if(r == RET_SUCCESS)
            {
                flaghayempleado = TRUE;
            }
            else
            {
                flaghayempleado = FALSE;
            }
            showMessage(r, ALTA, flaghayempleado);
            break;

        case MODI:
            flaghayempleado = hayEmpleados(e, MAX_QTY);

            if(flaghayempleado == TRUE)
            {
                ix = getindex(e);

                if(ix >= 0)
                {
                    optionedit = getOptionEdit();

                    switch((int) optionedit)
                    {
                    case EDITNAME:
                        printf("Ingrese un nuevo nombre: ");
                        scanf("%s", name);
                        strcpy(e[ix].name, name);
                        r = RET_SUCCESS;
                        break;
                    case EDITLASTNAME:
                        printf("Ingrese un nuevo apellido: ");
                        scanf("%s", lastname);
                        strcpy(e[ix].lastName, lastname);
                        r = RET_SUCCESS;
                        break;
                    case EDITSALARY:
                        printf("Ingrese un nuevo salario: ");
                        scanf("%f", &e[ix].salary);
                        r = RET_SUCCESS;
                        break;
                    case EDITSECTOR:
                        printf("Ingrese un nuevo sector: ");
                        scanf("%d", &sector);
                        e[ix].sector = sector;
                        r = RET_SUCCESS;
                        break;
                    default:
                        printf("Opcion incorrecta\n");
                        break;
                    }
                }
            }
            showMessage(r, MODI, flaghayempleado);
            break;

        case BAJA:
            flaghayempleado = hayEmpleados(e, MAX_QTY);

            if(flaghayempleado == TRUE)
            {
                ix = getIDEmployee();
                r = removeEmployee(e, MAX_QTY, ix);
            }
            showMessage(r, BAJA, flaghayempleado);
            break;

        case INFO:
            flaghayempleado = hayEmpleados(e, MAX_QTY);

            if( flaghayempleado == TRUE)
            {

                //Informar
                orden = getOrder();

                //1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector
                r = sortEmployees(e, MAX_QTY, orden);
                if(r == RET_ERROR)
                {
                    printf("Error al ordenar la lista de empleados.");
                }

                r = printEmployees(e, MAX_QTY);
                if(r == RET_ERROR)
                {
                    printf("Error al imprimir los empleados.");
                }

                //2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio.
                TotalPromedioSalarios(e, MAX_QTY);

                r = RET_SUCCESS;
            }
            else
            {
                showMessage(r, INFO, flaghayempleado);
            }
            break;
        default:
            printf("Opcion incorrecta\n");
            break;
        }

        respuesta = getRespuesta();
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
        if(e[i].isEmpty == FALSE)
        {
            cantEmployee++;
            total += e[i].salary;
        }
    }
    prom = total/cantEmployee;

    for(int i = 0; i < len; i++)
    {
        if(e[i].isEmpty == 0)
        {
            if(e[i].salary > prom)
            {
                salariomayorapromedio++;
            }
        }
    }

    printf("Total Salarios: %.2f\n", total);
    printf("Promedio Salarios: %.2f\n", prom);
    printf("Cantidad de Empleados que superan el promedio: %d\n", salariomayorapromedio);
}

int getIDEmployee()
{
    int id;
    printf("Ingrese ID del Empleado ");
    scanf("%d", &id);
    return id;
}

void showMessage(int idret, int from, int hayempleados)
{
    if(idret != RET_ERROR)
    {
        printf("El proceso finalizó exitosamente\n");
    }
    else
    {
        if(hayempleados == TRUE)
        {
            switch(from)
            {
            case ALTA:
                printf("Error al dar de alta el Empleado.");
                break;
            case MODI:
                printf("No se encuentra el ID del Empleado.\n");
                break;
            case BAJA:
                printf("No se encuentra el ID del Empleado.\n");
                break;
            case INFO:
                break;
            default:
                break;
            }
        }
        else
        {
            if(from == ALTA)
            {
                printf("Error al dar de alta el Empleado.\n");
            }
            else
            {
                printf("Error al ejecutar la transacción. Debe dar de alta un Empleado.\n");
            }

        }
    }
}

int hayEmpleados(Employee e[], int tam)
{
    int ret = FALSE;

    for(int i = 0; i < tam; i++)
    {
        if(e[i].isEmpty == FALSE)
        {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

int showMenuAndGetOption()
{
    int opcion;

    fflush(stdin);
    system("cls");
    printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n4.INFORMAR\n\n");
    scanf("%d", &opcion);

    return opcion;
}

int getindex(Employee e[])
{
    int id;
    int ix = RET_ERROR;
    fflush(stdin);
    printf("Ingrese el ID del Empleado \n");
    scanf("%d", &id);
    ix = findEmployeeById(e, MAX_QTY, id);
    return ix;
}

int getOptionEdit()
{
    int option;
    printf("Ingrese un valor segun el  campo que desea modificar: \n\n1 - NOMBRE\n2 - APELLIDO\n3 - SALARIO\n4 - SECTOR\n");
    scanf("%d", &option);
    return option;
}

int getOrder()
{
    int order;
    printf("Ingrese el orden en que quiere ordenar la lista de empleados\n0. DOWN\n1. UP\n");
    scanf("%d", &order);
    return order;
}

char getRespuesta()
{
    char respuesta;

    fflush(stdin);
    printf("Desea continuar? [s/n]\n");
    scanf("%c", &respuesta);

    while(respuesta != 's' && respuesta != 'n')
    {
        fflush(stdin);
        printf("Desea continuar? [s/n]\n");
        scanf("%c", &respuesta);
    }
    return respuesta;
}
