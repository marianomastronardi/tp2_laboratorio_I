#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define RET_ERROR -1
#define RET_SUCCESS 0
#define DOWN 0
#define UP 1

struct
{
    int id;
    char name[51];
    char lastName[51];
    float salary;
    int sector;
    int isEmpty;
} typedef Employee;

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int initEmployees(Employee* list, int len)
{
    int ret = RET_ERROR;
    if(list != NULL && len > 0)
    {
        for(int i = 0; i < len; i++)
        {
            list[i].isEmpty = TRUE;
        }
        ret = RET_SUCCESS;
    }
    return ret;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without free
 */
int addEmployee(Employee* list, int len, int id, char name[],char lastName[],float salary,int sector)
{
    int ret = RET_ERROR;
    if(list != NULL && len > 0)
    {
        //Agrego Empleado
        for(int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == TRUE)
            {
                list[i].id = id + i;
                strcpy(list[i].name, name);
                strcpy(list[i].lastName, lastName);
                list[i].salary = salary;
                list[i].sector = sector;
                list[i].isEmpty = FALSE;
                ret = RET_SUCCESS;
                break;
            }
        }
    }

    return ret;
}

/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */
int findEmployeeById(Employee* list, int len,int id)
{
    int ret = RET_ERROR;
    if(list != NULL && len > 0)
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i].id == id && list[i].isEmpty == FALSE)
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */
int removeEmployee(Employee* list, int len, int id)
{
    int ret = RET_ERROR;
    if(len > 0 && list != NULL)
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i].id == id)
            {
                list[i].isEmpty = TRUE;
                ret = RET_SUCCESS;
                break;
            }
        }
    }
    return ret;
}

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployees(Employee* list, int len, int order)
{
    int ret = RET_ERROR;
    Employee aux;
    if(len > 0 && list != NULL)
    {
        switch(order)
        {
        case DOWN:
            for(int i = 0; i < len - 1; i++)
            {
                for(int j = i + 1; j < len; j++)
                {
                    if(strcmp(list[j].lastName, list[i].lastName) > 0)
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                    else if(strcmp(list[j].lastName, list[i].lastName) == 0 && list[j].sector > list[i].sector)
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                }
            }
            ret = RET_SUCCESS;
            break;
        case UP:
            for(int i = 0; i < len - 1; i++)
            {
                for(int j = i + 1; j < len; j++)
                {
                    if(strcmp(list[j].lastName, list[i].lastName) < 0)
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                    else if(strcmp(list[j].lastName, list[i].lastName) == 0 && list[j].sector < list[i].sector)
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                }
            }
            ret = RET_SUCCESS;
            break;
        default:
            printf("Invalid order option");
        }
    }
    return ret;
}

/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int printEmployees(Employee* list, int length)
{
    int ret = RET_ERROR;
    if(length > 0)
    {
        printf("ID              Name                  LastName      Salary  Sector\n");
        for(int i = 0; i < length; i++)
        {
            if(list[i].isEmpty == FALSE)
            {
                fflush(stdin);
                printf("%6d %20s %20s %8.2f %4d\n", list[i].id, list[i].name, list[i].lastName, list[i].salary, list[i].sector);
            }
        }
        ret = RET_SUCCESS;
    }

    return ret;
}

