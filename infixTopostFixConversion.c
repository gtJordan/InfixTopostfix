//Gt-Jordan 23/12/16
#include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    #define N 30

    typedef struct StackSkelleton
    {
        char mStack[N];
        int top;
    }stk;

void initialize(stk *pSt);
int isFull(stk *pSt);
int isEmpty(stk *pSt);
int getTop(stk *pSt);
int pop(stk *pSt);
void push(stk* pSt, int token);
int priority(char token);
void transfer(stk *pSt, char* in, char *out);
int compute(stk *pSt,char *out);
int operate(int a,int b, char token);
void display(char *targAr);

int main(void)
{
    stk newStk;
    stk *pNewStk=&newStk;
    char input[N],output[N],choice;
    int solution;
    do
    {
        system("cls");
        printf("Insert the expression || No spaces || 1 digit numbers only\n=>: ");
        scanf("%s",input);
        initialize(pNewStk);
        transfer(pNewStk,input,output);
        display(output);
        solution=compute(pNewStk,output);
        printf("\nSolution:--> %d \n",solution);
        printf("\nCompute another expression? (Y/N): ");
        scanf(" %c",&choice);
    }while(choice=='Y'||choice=='y');

    return 0;
}

////////////////////////////////////////////////////////
//----------initialize--------------------------------
void initialize(stk *pSt)
{
    pSt->top=-1;
    return;
}
////////////////////////////////////////////////////////
//----------IsFull-------------------------------------
int isFull(stk *pSt)
{
    if(pSt->top>=N-1)
    {

        return 1;
    }
    else return 0;
}
////////////////////////////////////////////////////////
//----------isEmpty------------------------------------
int isEmpty(stk *pSt)
{
    if(pSt->top<=-1)
    {

        return 1;
    }
    else return 0;
}
////////////////////////////////////////////////////////
//----------GetTop-------------------------------------
int getTop(stk *pSt)
{
    if(!isEmpty(pSt))
    {
        return(pSt->mStack[pSt->top]);

    }
    else
    {
        int z=(int)'!';
        return z;
    }
}
////////////////////////////////////////////////////////
//----------PoP----------------------------------------
int pop(stk *pSt)
{
    if(!isEmpty(pSt))
    {
        int elem=pSt->mStack[pSt->top--];
        return(elem);
    }
    else
    {
        printf("Error: stack Empty\n");
        return -1;
    }
}
////////////////////////////////////////////////////////
//----------pUsh---------------------------------------
void push(stk *pSt,int token)
{
    if(!isFull(pSt))
    {
        pSt->top++;
        pSt->mStack[pSt->top]=token;
    }
    else
    {
        printf("Error: Stack is Full\n");
        return;
    }
}
////////////////////////////////////////////////////////
//----------priority-----------------------------------
int priority(char token)
{
    if(token=='(')
    {
        return 0;
    }
    else if (token=='-'||token=='+')
    {
        return 1;
    }
    else if (token=='*'||token=='/')
    {
        return 2;
    }
    return 4;
}
////////////////////////////////////////////////////////
//----------transfer-----------------------------------
void transfer(stk *pSt,char *input, char *output)
{
    char token;
    int i=0, j=0;
    size_t len=strlen(input);
    while(i<len)
    {
        token=input[i++];
        if(isalnum(token))
        {
            output[j++]=token;

        }
        else
        {
            if (token==')')
            {
                while(getTop(pSt)!='(')
                {
                    output[j++]=(char)pop(pSt);
                }
                pop(pSt);

            }
            else
            {

                while(priority(token)<=priority(getTop(pSt)) && !isEmpty(pSt)&&token!='(')
                {

                    output[j++]=(char)(pop(pSt));
                }
                push(pSt,(int)token);

            }
        }
    }
    while(!isEmpty(pSt))
    {
        output[j++]=pop(pSt);
    }
    output[j]='\0';

}
////////////////////////////////////////////////////////
//----------Compute------------------------------------
int compute(stk *pSt, char *out)
{
    int i=0,temp1=0,temp2=0,tempSum=0;
    char token,token1[2];
    size_t len=strlen(out);
    initialize(pSt);

    while(i<len)
    {
        token=out[i++];

        if(isalnum(token))
        {
            token1[0]=token;
            push(pSt,atoi(token1));
        }
        else
        {
            temp2=pop(pSt);
            temp1=pop(pSt);
            tempSum=operate(temp1,temp2,token);
            push(pSt,tempSum);
        }
    }
    tempSum=pop(pSt);
    return (tempSum);
}
////////////////////////////////////////////////////////
//----------Operate------------------------------------
int operate(int a,int b, char token)
{
    switch(token)
    {
        case '+':
            {
                return(a+b);
                break;
            }
        case '-':
            {
                return(a-b);
                break;
            }
        case '*':
            {
                return(a*b);
                break;
            }
        case '/':
            {
                if(b!=0)
                {
                    return(a/b);
                }
                else
                {
                    puts("Error: Zero devisor -> Exiting");
                    return(-999);
                }

                break;
            }
        default:
            {
                puts("Error: Operand unrecognized -> Exiting");
                return(-999);
                break;
            }

    }
}
////////////////////////////////////////////////////////
//----------Display------------------------------------
void display(char* targAr)
{
    printf("\nPostfix: %s\n",targAr);
    return;
}
