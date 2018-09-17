#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

struct Employee
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
    for(int i = 0; i < len; i++)
    {
        list[i].isEmpty = 1;
    }
    return 0;
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
    //if(strlen(name) > 0 && strlen(lastName) > 0 && salary > 0 && sector > 0){
    if(list != NULL)
    {
        if(len <= 0)
        {
            printf("Invalid length\n");
        }
        else
        {
            //Agrego Empleado
            for(int i = 0; i < len; i++)
            {
                if(list[i].isEmpty == 1)
                {
                    list[i].id = id;
                    strcpy(list[i].name, name);
                    strcpy(list[i].lastName, lastName);
                    list[i].salary = salary;
                    list[i].sector = sector;
                    list[i].isEmpty = 0;
                    return 0;
                }
            }
        }
    }
    else
    {
        printf("NULL pointer\n");
    }
    printf("without free\n");
    return -1;
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
    int ix = -1;
    if(len <= 0)
    {
        printf("Invalid length");
    }
    else
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i] == id)
            {
                ix = id;
            }
        }
    }

    return ix;
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
    if(len <= 0)
    {
        printf("Invalid length");
    }
    else
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i] == id)
            {
                list[i] = list[i + 1];
            }
            return 0;
        }
    }
    return -1;
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
    return 0;
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
    printf("ID              Name                  LastName      Salary  Sector\n");
    for(int i = 0; i < length; i++)
    {
        if(list[i].isEmpty == 0)
        {
            fflush(stdin);
            printf("%6d %20s %20s %8.2f %4d\n", list[i].id, list[i].name, list[i].lastName, list[i].salary, list[i].sector);
        }
    }
    return 0;
}

