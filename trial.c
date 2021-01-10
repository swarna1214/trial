#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int i=0,j=0;
struct stack
{
    int size,top,*array2,top2;
        char *array;
};
char infix[1000];
int is_empty(struct stack *s)
{
    if(s->top == -1)
        return 1;
    else
        return 0;

}//to check before popping if it is empty or not


int is_full(struct stack *s)
{
    if(s->top == s->size-1)
        return 1;
    else
        return 0;

}//to check before pushing if it is full or not

void push(struct stack *s,char value)
{
    if(is_full(s))
    {
        printf("Stack overflow\n");
    }
    else
    {
        s->top++;//if stack is not full moving top to input
        s->array[s->top] = value;//assigning value on top
    }
}

void push2(struct stack *s,int value)
{

        s->top2++;//if stack is not full moving top to input
        s->array2[s->top2] = value;//assigning value on top

}
char pop(struct stack *s)
{
    if(is_empty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    else//if stack is not empty
    {
        char value=0;
        value = s->array[s->top];//assigning the value from top
        s->top--;//shifting the top location
        return value;
    }

}
int pop2(struct stack *s)
{


        int value=0;
        value = s->array2[s->top2];//assigning the value from top
        s->top2--;//shifting the top location
        return value;


}
char top(struct stack *s)
{
    return s->array[s->top];
}
int top2(struct stack *s)
{
    return s->array2[s->top2];
}

int precedence(char value)
{
    if(value == '^')
        return 3;
    else if(value == '/'  || value == '%' || value == '*')
        return 2;
    else if(value == '+' || value == '-')
        return 1;
    else
        return 0;
}

int is_operator(char value)
{
    if(value == '*' || value == '/' || value == '+' || value == '-')
        return 1;
    else
        return 0;
}


char *Final(char *infix)
{
    struct stack *s = (struct stack*)malloc(1000*sizeof(struct stack));;//allocating memory space for struct stack
    s->size = 100;
    s->top = -1;//as memory allocation will be from 0
    s->array = (char*)malloc(s->size*sizeof(char));//allocating memory space for array

    char *postfix = (char*)malloc(sizeof(char) * strlen(infix+1)); //memory allocation for postfix equal to the size of infix

    while(infix[i]!= NULL)//loop will run until infix[i] is null
    {
        if(infix[i]=='(')
        {
            push(s,infix[i]);
            i++;
        }
        else if(infix[i]==')')
        {
            int k=i-1;
            i++;
            while(top(s)!='(')
            {

                if(is_operator(infix[k]))//if infix[i] is an operator
                {
                          //printf("e1%c ",top(s));
                    if(precedence(infix[k])> precedence(top(s)))//if infix[i] is greater than the previous operator stored in top
                    {
                              postfix[j]=' ';
                              j++;
                              //printf("e2%c",infix[k]);
                        push(s,infix[k]);//pushing operator in stack
                        k--;
                    }
                    else//if infix[i] is smaller than the previous operator stored in top
                    {
                              postfix[j]=' ';
                              j++;
                        postfix[j] = pop(s);//will pop the operator into
                        j++;
                        postfix[j]=' ';
                        j++;
                    }
                }
                else{k--;}
            }
            pop(s);
        }
        else if(!is_operator(infix[i]))//if infix[i] is not an operator
        {
            postfix[j]=infix[i];
            i++;
            j++;
        }
        else//if infix[i] is an operator
        {
            if(precedence(infix[i])> precedence(top(s)))//if infix[i] is greater than the previous operator stored in top
            {
                      postfix[j]=' ';
                      j++;
                push(s,infix[i]);//pushing operator in stack
                i++;
            }
            else//if infix[i] is smaller than the previous operator stored in top
            {
                      postfix[j]=' ';
                      j++;
                postfix[j] = pop(s);//will pop the operator into
                j++;
                 postfix[j]=' ';
                 j++;
            }
        }
    }
    while(!is_empty(s))
    {
        postfix[j] = pop(s);
        j++;
         postfix[j]=' ';
          j++;
    }
    postfix[j] = NULL;
    return postfix;
}
int rev(int a)
{
    int rev=0,rem=0;
    while(a!=0)
    {
        rem=a%10;
        rev=rev*10+rem;
        a=a/10;
    }
    return rev;
}
int evaluate(char *postfix)
{
          printf("Postfix:%s\n",postfix);
    struct stack *s = (struct stack*)malloc(10000*sizeof(struct stack));//allocating memory space for struct stack
    s->size = 10000;
    s->top2 = -1;//as memory allocation will be from 0
    s->array2 = (int*)malloc(s->size*sizeof(int));//allocating memory space for array
    i=0;
    int r=0;
    while(postfix[i]!='\0')
    {
          //printf("%c",postfix[i]);
        if(postfix[i]== ' ')
            {i++;continue;}
        else if(!is_operator(postfix[i]))
        {
         //printf("%c ",postfix[i]);
            int num=0,n1=0,k=1;
            while(postfix[i]!=' '&&!is_operator(postfix[i]))
            {
                     // printf("%c ",postfix[i]);
                n1=(postfix[i]-48);
                num=num+k*n1;
                k=k*10;
                i++;
            }
            num=rev(num);
            //printf("e1%d\n",num);
            push2(s,num);
        }
        else
            {
                      int n1=0,n2=0;

                n1=pop2(s);
                n2=pop2(s);
                if(postfix[i]=='+')
                    {
                        r=n2+n1;
                    }
                if(postfix[i]=='-')
                    {
                        r=n2-n1;
                    }
                if(postfix[i]=='*')
                    {
                        r=n2*n1;
                    }
                if(postfix[i]=='/')
                    {
                        r=n2/n1;
                    }
                if(postfix[i]=='%')
                    {
                        r=n2%n1;
                    }
                if(postfix[i]=='^')
                    {
                        r=pow(n2,n1);
                    }

                push2(s,r);
                i++;
            }


    }
        return pop2(s);
    }

int main(void)
{
    int i,a=0;
    char post[3000]="";
    scanf("%s",&*infix);
    //printf("%s\n",Final(infix));
    a=evaluate(Final(infix));
    printf("\n%d",a);
    return 0;
}
