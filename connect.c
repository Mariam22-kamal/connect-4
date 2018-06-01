#include<stdio.h>
#include<stdlib.h>
int more(int a,int b)
{
    return (a>b)?a:b;
}
int less(int a,int b)
{
    return a+b-more(a,b);
}
char me='X';
char you='O';
int end(char** arr)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(arr[i][j]=='-')
                return 0;
        }
    }
    return 1;
}
void print(char** arr)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            printf("   %c",arr[i][j]);
        }
        printf("\n");
    }
    return;
}
int evaluate(char** arr)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr[i][j]==arr[i][j+1]  && arr[i][j]==arr[i][j+2]  && arr[i][j]==arr[i][j+3])
            {
                if(arr[i][j]==me)
                return 1000;
                if(arr[i][j]==you)
                return -1000;
            }
        }
    }
    for(int j=0;j<7;j++)
    {
        for(int i=0;i<3;i++)
        {
            if(arr[i][j]==arr[i+1][j]  && arr[i][j]==arr[i+2][j]  && arr[i][j]==arr[i+3][j])
            {
                if(arr[i][j]==me)
                return 1000;
                if(arr[i][j]==you)
                return -1000;
            }
        }
    }
    int count=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr[i][j]==arr[i+1][j+1] && arr[i][j]==arr[i+2][j+2] && arr[i][j]==arr[i+3][j+3])
            {
                if(arr[i][j]==me)
                return 1000;
                if(arr[i][j]==you)
                return -1000;
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=3;j<7;j++)
        {
            if(arr[i][j]==arr[i+1][j-1] && arr[i][j]==arr[i+2][j-2] && arr[i][j]==arr[i+3][j-3])
            {
                if(arr[i][j]==me)
                return 1000;
                if(arr[i][j]==you)
                return -1000;
            }
        }
    }
    return 0;
}
int minmax(char** arr,int depth,int turn,int alpha,int beta)
{
    int score=evaluate(arr);
    //printf("%d\n",score);
    //if(score!=0 && depth==7)  return score*10;
    //if(score!=0 && depth==6)  return score*5;
    //if(score!=0 && depth==5)  return score*3;
    //if(score!=0 && depth==4)  return score*2;
    if(score!=0)  return score;
    if(end(arr)==1)  return 0;
    if(depth==0)  return 0;
    if(turn%2==1)
    {
        int max=-1111111;
        for(int k=0;k<=3;k++)
        {
           int i=3-k;
            for(int j=5;j>=0;j--)
            {
                if(arr[j][i]=='-')
                {
                    arr[j][i]=me;
                    max=more(max,minmax(arr,depth-1,turn+1,alpha,beta));
                    alpha=more(alpha,max);
                    arr[j][i]='-';
                    break;
                }
            }
            if(alpha>=beta)
                break;
            i=3+k;
            for(int j=5;j>=0;j--)
            {
                if(arr[j][i]=='-')
                {
                    arr[j][i]=me;
                    max=more(max,minmax(arr,depth-1,turn+1,alpha,beta));
                    alpha=more(alpha,max);
                    arr[j][i]='-';
                    break;
                }
            }
            if(alpha>=beta)
                break;
        }
        return max+depth;
    }
    else
    {
        int max=11111111;
        for(int k=0;k<=3;k++)
        {
               int i=3-k;
            for(int j=5;j>=0;j--)
            {
                if(arr[j][i]=='-')
                {
                    arr[j][i]=you;
                    max=less(max,minmax(arr,depth-1,turn+1,alpha,beta));
                    beta=less(max,beta);
                    arr[j][i]='-';
                    break;
                }
            }
            if(alpha>=beta)
                break;
        i=3+k;
            for(int j=5;j>=0;j--)
            {
                if(arr[j][i]=='-')
                {
                    arr[j][i]=you;
                    max=less(max,minmax(arr,depth-1,turn+1,alpha,beta));
                    beta=less(max,beta);
                    arr[j][i]='-';
                    break;
                }
            }
            if(alpha>=beta)
                break;
        }
        return max+depth;
    }
}
int chance(char** arr,int f,int luck)
{
    double best=-100000;
    int bestmove=-1;
    double moves[7];
    int curr;
    for(int i=0;i<7;i++)
    {
       // printf("%d",i);
        for(int j=5;j>=0;j--)
        {
            //printf("%d",i);
            moves[i]=-1000000;
            if(arr[j][i]=='-')
            {
                arr[j][i]=me;
                curr=minmax(arr,8 ,0,-99999999,99999999);
                int score=evaluate(arr);
                if(score==1000)  curr=10000;
                moves[i]=curr;
                arr[j][i]='-';
                break;
            }
        }
    }


    for(int i=0;i<=6;i++)
    {
        for(int j=5;j>=0;j--)
        {
            if(arr[j][i]=='-')
            {
                if((6-j)%2==luck)
                {
                    moves[i]+=0.5;

                }
                break;
            }
        }
    }
    for(int i=0;i<7;i++)
    {
        printf("%.1lf ",moves[i]);
    }
    printf("\n");
    for(int i=0;i<=3;i++)
    {
        if(moves[3-i]>best)
        {
            best=moves[3-i];
            bestmove=3-i;
        }
        if(moves[3+i]>best)
        {
            best=moves[3+i];
            bestmove=3+i;
        }
    }
    return bestmove;
}
int isend(char** arr)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr[i][j]==arr[i][j+1]  && arr[i][j]==arr[i][j+2]  && arr[i][j]==arr[i][j+3])
            {
                if(arr[i][j]==me)
                return 1;
                if(arr[i][j]==you)
                return 0;
            }
        }
    }
    for(int j=0;j<7;j++)
    {
        for(int i=0;i<3;i++)
        {
            if(arr[i][j]==arr[i+1][j]  && arr[i][j]==arr[i+2][j]  && arr[i][j]==arr[i+3][j])
            {
                if(arr[i][j]==me)
                return 1;
                if(arr[i][j]==you)
                return 0;
            }
        }
    }
    int count=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr[i][j]==arr[i+1][j+1] && arr[i][j]==arr[i+2][j+2] && arr[i][j]==arr[i+3][j+3])
            {
                if(arr[i][j]==me)
                return 1;
                if(arr[i][j]==you)
                return 0;
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=3;j<7;j++)
        {
            if(arr[i][j]==arr[i+1][j-1] && arr[i][j]==arr[i+2][j-2] && arr[i][j]==arr[i+3][j-3])
            {
                if(arr[i][j]==me)
                return 1;
                if(arr[i][j]==you)
                return 0;
            }
        }
    }
    return -1;
}
int main()
{
    printf("LETS START\n");
     char** arr=(char**)malloc(sizeof(char*)*6);
     for(int i=0;i<6;i++)
     {
         arr[i]=(char*)malloc(sizeof(char)*7);
     }
     for(int i=0;i<6;i++)
        for(int j=0;j<7;j++)
        arr[i][j]='-';
    char your;
    int depth=0;
    print(arr);
     printf("CHOOSE YOUR IDENTITY(O or X):");
     scanf("%c",&your);
     printf("\n");
     if(your=='X' || your=='x')
     {
         me='O';
         you='X';
     }
     //printf("j");
     int t=0;
     if(me=='X')
     {
         t=1;
         int winm=chance(arr,1,t);
         arr[5][winm]='X';
         print(arr);
         depth++;
     }
     int f=1;
     while(depth<45)
     {
         f++;
         int x,y;
         printf("Make your move: ");
         scanf("%d",&x);
         printf("\n");

         if(arr[0][x-1]!='-')
         {
             printf("YOU CHEATER");
             return 0;
         }
         for(int i=5;i>=0;i--)
         {
             if(arr[i][x-1]=='-')
             {
                 arr[i][x-1]=you;
                 break;
             }
         }
         print(arr);
         int con=isend(arr);
         if(con==0)
         {
             printf("YOU WON\n");
             return 0;
         }
         else if(con==1)
         {
             printf("YOU LOSE\n");
             return 0;
         }
         if(end(arr)==1)
         {
             printf("DRAW\n");
             return 0;
         }
         depth++;
         int winm=chance(arr,7+f,t);
         for(int i=5;i>=0;i--)
         {
             if(arr[i][winm]=='-')
             {
                 arr[i][winm]=me;
                 break;
             }
         }
         printf("MY MOVE\n");
         print(arr);
         con=isend(arr);
         if(con==0)
         {
             printf("YOU WON\n");
             return 0;
         }
         else if(con==1)
         {
             printf("YOU LOSE\n");
             return 0;
         }
         if(end(arr)==1)
         {
             printf("DRAW\n");
             return 0;
         }
         depth++;
     }
     return 0;
}
