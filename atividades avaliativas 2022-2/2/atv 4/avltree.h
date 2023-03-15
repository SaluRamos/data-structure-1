//Feito sozinho por: Salu Conteratto Ramos
//RA: 2150352

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node{
    struct node *lchild;
    char info[200];
    int page;
    struct node *rchild;
    int balance;
};

void inorder(struct node *ptr);
struct node *RotateLeft(struct node *pptr);
struct node *RotateRight(struct node *pptr);

struct node *insert(struct node *pptr, char ikey[], int page);
struct node *insert_left_check(struct node *pptr, int *ptaller);
struct node *insert_right_check(struct node *pptr, int *ptaller);
struct node *insert_LeftBalance(struct node *pptr);
struct node *insert_RightBalance(struct node *pptr);

struct node *del(struct node *pptr, char dkey[]);
struct node *del_left_check(struct node *pptr, int *pshorter);
struct node *del_right_check(struct node *pptr, int *pshorter);
struct node *del_LeftBalance(struct node *pptr, int *pshorter);
struct node *del_RightBalance(struct node *pptr, int *pshorter);


void display(struct node *ptr, int level)
{
    int i;
    if (ptr == NULL)
        return;
    else
    {
        display(ptr->rchild, level + 1);
        printf("\n");
        for (i = 0; i < level; i++)
            printf("    ");
        printf("%s", ptr->info);
        display(ptr->lchild, level + 1);
    }
}

struct node *insert(struct node *pptr, char ikey[], int page)
{
    static int taller;
    if (pptr == NULL)
    {
        pptr = (struct node *)malloc(sizeof(struct node));
        strcpy(pptr->info, ikey);
        pptr->page = page;
        pptr->lchild = NULL;
        pptr->rchild = NULL;
        pptr->balance = 0;
        taller = true;
    }
    else if (strcmp(ikey, pptr->info) < 0)
    {
        pptr->lchild = insert(pptr->lchild, ikey, page);
        if (taller == true)
            pptr = insert_left_check(pptr, &taller);
    }
    else if (strcmp(ikey, pptr->info) > 0)
    {
        pptr->rchild = insert(pptr->rchild, ikey, page);
        if (taller == true)
            pptr = insert_right_check(pptr, &taller);
    }
    else
    {
        printf("Duplicate key\n");
        taller = false;
    }
    return pptr;
}

struct node *insert_left_check(struct node *pptr, int *ptaller)
{
    switch (pptr->balance)
    {
    case 0:
        pptr->balance = 1;
        break;
    case -1:
        pptr->balance = 0;
        *ptaller = false;
        break;
    case 1:
        pptr = insert_LeftBalance(pptr);
        *ptaller = false;
    }
    return pptr;
}

struct node *insert_right_check(struct node *pptr, int *ptaller)
{
    switch (pptr->balance)
    {
    case 0:
        pptr->balance = -1;
        break;
    case 1:
        pptr->balance = 0;
        *ptaller = false;
        break;
    case -1:
        pptr = insert_RightBalance(pptr);
        *ptaller = false;
    }
    return pptr;
}

struct node *insert_LeftBalance(struct node *pptr)
{
    struct node *aptr, *bptr;

    aptr = pptr->lchild;
    if (aptr->balance == 1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RotateRight(pptr);
    }
    else
    {
        bptr = aptr->rchild;
        switch (bptr->balance)
        {
        case -1:
            pptr->balance = 0;
            aptr->balance = 1;
            break;
        case 1:
            pptr->balance = -1;
            aptr->balance = 0;
            break;
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
        }
        bptr->balance = 0;
        pptr->lchild = RotateLeft(aptr);
        pptr = RotateRight(pptr);
    }
    return pptr;
}

struct node *insert_RightBalance(struct node *pptr)
{
    struct node *aptr, *bptr;

    aptr = pptr->rchild;
    if (aptr->balance == -1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RotateLeft(pptr);
    }
    else
    {
        bptr = aptr->lchild;
        switch (bptr->balance)
        {
        case -1:
            pptr->balance = 1;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = 0;
            aptr->balance = -1;
            break;
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
        }
        bptr->balance = 0;
        pptr->rchild = RotateRight(aptr);
        pptr = RotateLeft(pptr);
    }
    return pptr;
}

struct node *RotateLeft(struct node *pptr)
{
    struct node *aptr;
    aptr = pptr->rchild;
    pptr->rchild = aptr->lchild;
    aptr->lchild = pptr;
    return aptr;
}

struct node *RotateRight(struct node *pptr)
{
    struct node *aptr;
    aptr = pptr->lchild;
    pptr->lchild = aptr->rchild;
    aptr->rchild = pptr;
    return aptr;
}

struct node *del(struct node *pptr, char dkey[])
{
    struct node *tmp, *succ;
    static int shorter;

    if (pptr == NULL)
    {
        printf("Key not present \n");
        shorter = false;
        return (pptr);
    }
    if (dkey < pptr->info)
    {
        pptr->lchild = del(pptr->lchild, dkey);
        if (shorter == true)
            pptr = del_left_check(pptr, &shorter);
    }
    else if (dkey > pptr->info)
    {
        pptr->rchild = del(pptr->rchild, dkey);
        if (shorter == true)
            pptr = del_right_check(pptr, &shorter);
    }
    else
    {
        if (pptr->lchild != NULL && pptr->rchild != NULL)
        {
            succ = pptr->rchild;
            while (succ->lchild)
                succ = succ->lchild;
            strcpy(pptr->info, succ->info);
            pptr->rchild = del(pptr->rchild, succ->info);
            if (shorter == true)
                pptr = del_right_check(pptr, &shorter);
        }
        else
        {
            tmp = pptr;
            if (pptr->lchild != NULL){
                pptr = pptr->lchild;
            }
            else if (pptr->rchild != NULL){
                pptr = pptr->rchild;
            }
            else{
                pptr = NULL;
            }
            free(tmp);
            shorter = true;
        }
    }
    return pptr;
}

struct node *del_left_check(struct node *pptr, int *pshorter)
{
    switch (pptr->balance)
    {
    case 0:
        pptr->balance = -1;
        *pshorter = false;
        break;
    case 1:
        pptr->balance = 0;
        break;
    case -1:
        pptr = del_RightBalance(pptr, pshorter);
    }
    return pptr;
}

struct node *del_right_check(struct node *pptr, int *pshorter)
{
    switch (pptr->balance)
    {
        case 0:
            pptr->balance = 1;
            *pshorter = false;
            break;
        case -1:
            pptr->balance = 0;
            break;
        case 1:
            pptr = del_LeftBalance(pptr, pshorter);
    }
    return pptr;
}

struct node *del_LeftBalance(struct node *pptr, int *pshorter)
{
    struct node *aptr, *bptr;
    aptr = pptr->lchild;
    if (aptr->balance == 0)
    {
        pptr->balance = 1;
        aptr->balance = -1;
        *pshorter = false;
        pptr = RotateRight(pptr);
    }
    else if (aptr->balance == 1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RotateRight(pptr);
    }
    else
    {
        bptr = aptr->rchild;
        switch (bptr->balance)
        {
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = -1;
            aptr->balance = 0;
            break;
        case -1:
            pptr->balance = 0;
            aptr->balance = 1;
        }
        bptr->balance = 0;
        pptr->lchild = RotateLeft(aptr);
        pptr = RotateRight(pptr);
    }
    return pptr;
}

struct node *del_RightBalance(struct node *pptr, int *pshorter)
{
    struct node *aptr, *bptr;

    aptr = pptr->rchild;
    if (aptr->balance == 0)
    {
        pptr->balance = -1;
        aptr->balance = 1;
        *pshorter = false;
        pptr = RotateLeft(pptr);
    }
    else if (aptr->balance == -1)
    {
        pptr->balance = 0;
        aptr->balance = 0;
        pptr = RotateLeft(pptr);
    }
    else
    {
        bptr = aptr->lchild;
        switch (bptr->balance)
        {
        case 0:
            pptr->balance = 0;
            aptr->balance = 0;
            break;
        case 1:
            pptr->balance = 0;
            aptr->balance = -1;
            break;
        case -1:
            pptr->balance = 1;
            aptr->balance = 0;
        }
        bptr->balance = 0;
        pptr->rchild = RotateRight(aptr);
        pptr = RotateLeft(pptr);
    }
    return pptr;
}

void inorder(struct node *ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->lchild);
        printf("%s  ", ptr->info);
        inorder(ptr->rchild);
    }
}

int binarySearch(struct node *ptr, char key[]){
    if(strcmp(ptr->info, key) > 0){
        return binarySearch(ptr->lchild, key);
    }
    else if(strcmp(ptr->info, key) < 0){
        return binarySearch(ptr->rchild, key);
    }
    return ptr->page;
}