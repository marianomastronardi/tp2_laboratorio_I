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
int findFreePlace(Employee[], int);

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

            if(findFreePlace(e, MAX_QTY) == RET_SUCCESS)
            {
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
            }
            else
            {
                printf("Array lleno.\n\n");
            }

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

                //1. Listado de los empleados ordenados alfab�ticamente por Apellido y Sector
                r = sortEmployees(e, MAX_QTY, orden);
                if(r == RET_ERROR)
                {
                    printf("Error al ordenar la lista de empleados.\n\n");
                }

                r = printEmployees(e, MAX_QTY);
                if(r == RET_ERROR)
                {
                    printf("Error al imprimir los empleados.\n\n");
                }

                //2. Total y promedio de los salarios, y cu�ntos empleados superan el salario promedio.
                TotalPromedioSalarios(e, MAX_QTY);

                r = RET_SUCCESS;
            }
            else
            {
                showMessage(r, INFO, flaghayempleado);
            }
            break;
        default:
            break;
        }

        respuesta = getRespuesta();
    }
    while(respuesta == 's');

    return 0;
}

/** \brief muestra el monto total de salarios, el promedio de salarios y todos los empleados que superen el promedio con su salario
 *
 * \param lista de empleados
 * \param tama�o
 * \return void
 *
 */

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
        if(e[i].isEmpty == FALSE)
        {
            if(e[i].salary > prom)
            {
                salariomayorapromedio++;
            }
        }
    }

    printf("Total Salarios: %.2f\n\n", total);
    printf("Promedio Salarios: %.2f\n\n", prom);
    printf("Cantidad de Empleados que superan el promedio: %d\n\n", salariomayorapromedio);
}

/** \brief devuelve el ID ingresado por el usuario
 * \return  int id
 *
 */
int getIDEmployee()
{
    int id;
    printf("Ingrese ID del Empleado ");
    scanf("%d", &id);
    return id;
}

/** \brief muestra el mensaje segun de donde provenga la llamada
 *
 * \param int id de retorno
 * \param int origen de la llamada
 * \param int [0] - No hay empleados // [1] - hay empleados
 * \return
 *
 */

void showMessage(int idret, int from, int hayempleados)
{
    if(idret != RET_ERROR)
    {
        printf("El proceso finaliz� exitosamente\n");
    }
    else
    {
        if(hayempleados == TRUE)
        {
            switch(from)
            {
            case ALTA:
                printf("Error al dar de alta el Empleado.\n\n");
                break;
            case MODI:
                printf("No se encuentra el ID del Empleado.\n\n");
                break;
            case BAJA:
                printf("No se encuentra el ID del Empleado.\n\n");
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
                printf("Error al dar de alta el Empleado.\n\n");
            }
            else
            {
                printf("Error al ejecutar la transacci�n. Debe dar de alta un Empleado.\n\n");
            }

        }
    }
}

/** \brief verifica si hay empleados en el array
 *
 * \param lista de empleados
 * \param int tama�o
 * \return [0] - NO hay empleados // [1] - hay empleados
 *
 */

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

/** \brief muestra el menu y devuelve la opcion ingresada por el usuario
 *
 * \return int opcion
 *
 */

int showMenuAndGetOption()
{
    int opcion;

    fflush(stdin);
    system("cls");
    printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n4.INFORMAR\n\n");
    scanf("%d", &opcion);

    while(opcion < 1 || opcion > 4)
    {
        printf("Opcion incorrecta\n\n");
        system("pause");
        fflush(stdin);
        system("cls");
        printf("Ingrese una opcion \n1.ALTAS\n2.MODIFICAR\n3.BAJA\n4.INFORMAR\n\n");
        scanf("%d", &opcion);
    }

    return opcion;
}

/** \brief devuelve el indice del array donde se aloja el id de empleado ingresado por el usuario
 *
 * \param lista de empleados
 * \return int indice
 *
 */

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

/** \brief devuelve la opcion ingresada por el usuario para modificar un campo del empleado
 * \return int opcion del campo a editar
 *
 */

int getOptionEdit()
{
    int option;
    printf("Ingrese un valor segun el  campo que desea modificar: \n\n1 - NOMBRE\n2 - APELLIDO\n3 - SALARIO\n4 - SECTOR\n\n");
    scanf("%d", &option);

    while(option < 1 || option > 4)
    {
        printf("Opcion incorrecta.\nIngrese un valor segun el  campo que desea modificar: \n\n1 - NOMBRE\n2 - APELLIDO\n3 - SALARIO\n4 - SECTOR\n\n");
        scanf("%d", &option);
    }

    return option;
}

/** \brief devuelve el orden en que el usuario selecciono ordenar la lista
 *
 * \return int [0] - DOWN // [1] UP
 *
 */

int getOrder()
{
    int order;
    printf("Ingrese el orden en que quiere ordenar la lista de empleados\n0. DOWN\n1. UP\n");
    scanf("%d", &order);
    return order;
}

/** \brief devuelve la respuesta seleccionada por el usuario
 *
 * \return char respuesta [s/n]
 *
 */

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

int findFreePlace(Employee e[], int tam)
{
    int ret = RET_ERROR;

    for(int i = 0; i < tam; i++)
    {
        if(e[i].isEmpty == TRUE)
        {
            ret = RET_SUCCESS;
        }
    }

    return ret;
}
