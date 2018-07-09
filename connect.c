#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
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
    for(int i=1;i<8;i++)
    {
       printf("   %d",i);
    }
    printf("   <---- INDEXES");
    printf("\n");
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            printf("   %c",arr[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    return;
}
int count(char** arr,char ch)
{
    int num=0;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<4;j++)
        {
            if((arr[i][j]==ch  && ch==arr[i][j+1] && arr[i][j+2]=='-'  && ch==arr[i][j+3] ) || (arr[i][j]==ch  && '-'==arr[i][j+1] && arr[i][j+2]==ch  && ch==arr[i][j+3] ))
            {

                num++;

            }
            else if((arr[i][j]==ch  && ch==arr[i][j+1] && arr[i][j+2]==ch  && '-'==arr[i][j+3] ) || (arr[i][j]=='-'  && ch==arr[i][j+1] && arr[i][j+2]==ch  && ch==arr[i][j+3] ))
            {

                num++;

            }
        }
    }
    for(int j=0;j<7;j++)
    {
        for(int i=0;i<3;i++)
        {
           if((arr[i][j]==ch  && ch==arr[i+1][j] && arr[i+2][j]=='-'  && ch==arr[i+3][j] ) || (arr[i][j]==ch  && '-'==arr[i+1][j] && arr[i+2][j]==ch  && ch==arr[i+3][j] ))
            {

                num++;
            }
            else if((arr[i][j]==ch  && ch==arr[i+1][j] && arr[i+2][j]==ch  && '-'==arr[i+3][j] ) || (arr[i][j]=='-' && ch==arr[i+1][j] && arr[i+2][j]==ch  && ch==arr[i+3][j] ))
            {

                num++;
            }
        }
    }
    int count=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
             if((arr[i][j]==ch  && ch==arr[i+1][j+1] && arr[i+2][j+2]=='-'  && ch==arr[i+3][j+3] ) || (arr[i][j]==ch  && '-'==arr[i+1][j+1] && arr[i+2][j+2]==ch  && ch==arr[i+3][j+3] ))
            {

                num++;
            }
            else if((arr[i][j]==ch  && ch==arr[i+1][j+1] && arr[i+2][j+2]==ch && '-'==arr[i+3][j+3] ) || (arr[i][j]=='-'   && ch==arr[i+1][j+1] && arr[i+2][j+2]==ch  && ch==arr[i+3][j+3] ))
            {

                num++;
            }
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=3;j<7;j++)
        {
            if((arr[i][j]==ch  && ch==arr[i+1][j-1] && arr[i+2][j-2]=='-'  && ch==arr[i+3][j-3] ) || (arr[i][j]==ch  && '-'==arr[i+1][j-1] && arr[i+2][j-2]==ch  && ch==arr[i+3][j-3] ))
            {

               num++;
            }
            else if((arr[i][j]==ch  && ch==arr[i+1][j-1] && arr[i+2][j-2]==ch  && '-'==arr[i+3][j-3] ) || (arr[i][j]=='-'  && ch==arr[i+1][j-1] && arr[i+2][j-2]==ch  && ch==arr[i+3][j-3] ))
            {

               num++;
            }
        }
    }
    return num;
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
    return count(arr,me)*10-2*count(arr,you)*10;
}
int minmax(char** arr,int depth,int turn,int alpha,int beta)
{
    int score=evaluate(arr);
    if(score==1000 || score==-1000)  return score;
    if(end(arr)==1)  return 0;
    if(depth==0)  return score;
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
double on=0;
int chance(char** arr,int f,int luck,int level)
{
    double inc=1/5.0;
    double best=-100000;
    int bestmove=-1;
    double moves[7];
    int curr;
    if(on>=3)  inc=0.25;
    if(on>=2)  inc=1/3.0;
    if(on>=3)  inc=0.5;
    on+=inc;
    printf("\n#current depth: %d#\n",level+(int)on);
    printf("PROGRESS : /");

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
                curr=minmax(arr,level+(int)on ,0,-99999999,99999999);
                int score=evaluate(arr);
                if(score==1000)  curr=10000;
                moves[i]=curr;
                arr[j][i]='-';
                break;
            }
        }
        printf("#");
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
    printf("/");
    Sleep(1000);
    printf("\n");
    printf("\nCOMPLETED played at %d\n\n",bestmove+1);
    printf("SCORES:- ");
    for(int i=0;i<7;i++)
    {
        if(moves[i]!=-1000000)
        printf("|$%d~~%.1lf| ",i+1,moves[i]);
        else
           printf("|$%d~~NAN| ",i+1);
    }
    printf("\n\n\n");
    Sleep(1000);
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
int isCorr(char** arr,int pos)
{
    if(pos>7 || pos<=0){ printf("ERROR : WRONG INDEX ! \n\n"); return 1;}
    if(arr[0][pos-1]!='-') { printf("ERROR : COLUMN ALREADY FULL ! \n\n"); return 1;}
    return 0;
}
int main()
{

    printf("          GAME BOARD\n");

      printf("                   \n");
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
    printf("Do you want instructions(Press Y for yes or any other key to skip): ");
    char con;
    scanf("%c",&con);

    printf("\n");
    if(con=='y'|| con=='Y')
   {
       printf("                                            -:RULES:-\n");
       char rules[]="~Above you can see the game-board which is a 6*7 grid.\n~So,you have to make a 4-in-a-line vertically, horizontally or diagonally using your piece.\n~But remember you can put your piece in a row only after the row below it is filled.In simple terms think as if gravity is working i.e. your piece will fall to the bottom of the column.\n~While choosing your piece keep in mind X does the first chance.\n~During runtime win places tell how many active 3-in-a-line are present in game.\n~Score tells about the feasibility of placing the piece at that column.\n\n";
       int i=0;
       while(rules[i]!='\0')
       {
           printf("%c",rules[i]);
           Sleep(80);
           i++;
       }
   }
   printf("LETS START\n");
   printf("Enter your name: ");
   char name[100];
   scanf("\n%s",name);
   printf("SELECT GAME DIFFICULTY (1 for BEGGINERS, 2 for INTERMEDIATE, 3 for ADVANCED ,others for PRO): ");
   char diff;
   scanf("\n%c",&diff);
   printf("\n\n");
   int level;
   if(diff=='1')   level=2;
   else if(diff=='2')  level=4;
   else if(diff=='3')  level=6;
   else   level=8;
     printf("CHOOSE YOUR IDENTITY(O or X): ");
     scanf("\n%c",&your);
     //printf("%c",your);
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
         int winm=chance(arr,1,t,level);
         arr[5][winm]='X';
         print(arr);
         printf("#win places:- |computer:%d| |%s:%d|#\n\n",count(arr,me),name,count(arr,you));
         depth++;
     }
     int f=1;
     while(depth<45)
     {

         f++;
         int x,y;
         while(1)
         {
             printf("Make your move: ");
             scanf("%d",&x);

             if(isCorr(arr,x)==0)  break;
         }
         printf("\n");

         for(int i=5;i>=0;i--)
         {
             if(arr[i][x-1]=='-')
             {
                 arr[i][x-1]=you;
                 break;
             }
         }
         print(arr);
         printf("#win places:- |computer:%d| |%s:%d|#\n\n",count(arr,me),name,count(arr,you));
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
         int winm=chance(arr,7+f,t,level);
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
         printf("#win places:- |computer:%d| |%s:%d|#\n\n",count(arr,me),name,count(arr,you));
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
