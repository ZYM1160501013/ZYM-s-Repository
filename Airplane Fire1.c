/*这是最开始的程序，由于对敌机产生的原理分析的不到位和代码逻辑
  不准确，导致要使用多线程来操作敌机的产生，这就产生很多我们无法
  理解的冲突，bug越来越多且难以修复，所以该代码最终被放弃*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<pthread.h>
#pragma comment(lib, "Winmm.lib")
#define max_Number 86
#define min_Number 32
void gotoxy(int ,int );
void cover(int ,int );
void pattern(int ,int );
void key();
void enemy(int ,int );
int x=60,y=23;
int main()
{
  int i,j;
  int isKilled=0;

  for(i=30;i<=89;i++)
    {
      gotoxy(i,0);
      printf("*");
      gotoxy(i,27);
      printf("*");
    }

  for(j=1;j<=26;j++)
    {
      gotoxy(30,j);
      printf("*");
      gotoxy(89,j);
      printf("*");
    }

    pattern(x,y);

    pthread_t t1,t2;

    pthread_create(&t1,NULL,key,NULL);
    pthread_create(&t2,NULL,enemy,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
  return 0;
}

void key()
{
    int isFire=0;
    int x=60,y=23,j;
    char input;

    while(1)
  {

     if(isFire==1)
        {
            for(j=1;j<y;j++)
            {
            gotoxy(x,j);
            printf("|");
            }
            Sleep(100);
            for(j=1;j<y;j++)
            {
            gotoxy(x,j);
            printf(" ");
            }
            isFire=0;
        }
     if(kbhit())
        {
           input=getch();
           if(input=='a')
            {
               cover(x,y);
               x--;
               if(x==32)x++;
               pattern(x,y);
            }
           if(input=='d')
            {
               cover(x,y);
               x++;
               if(x==87)x--;
               pattern(x,y);
            }
           if(input=='w')
            {
               cover(x,y);
               y--;
               if(y==0)y++;
               pattern(x,y);
            }
           if(input=='s')
            {
               cover(x,y);
               y++;
               if(y==24)y--;
               pattern(x,y);
            }
           if(input==' ')
               isFire=1;

       }
  }
}

void gotoxy(int x,int y)
{
    HANDLE hOut;
    COORD pos= {x,y};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void cover(int x,int y)
{
   gotoxy(x,y);
   printf(" ");
   gotoxy(x-1,y+1);
   printf("   ");
   gotoxy(x-2,y+2);
   printf("     ");
   gotoxy(x-1,y+3);
   printf("   ");
}

void pattern(int x,int y)
{
   gotoxy(x,y);
   printf("*");
   gotoxy(x-1,y+1);
   printf("***");
   gotoxy(x-2,y+2);
   printf("*****");
   gotoxy(x-1,y+3);
   printf("* *");
}

void enemy(int x,int isFire)
{
    int k,ene;
    srand((unsigned)time(NULL));
    while(1)
    {
     do
        ene=rand();
     while(ene>max_Number||ene<min_Number);
        for(k=1;k<27;k++)
        {if(x==ene&&isFire==1)break;
         gotoxy(ene,k);
         printf("*");
         Sleep(1000);
         gotoxy(ene,k);
         if(k!=26)
         printf(" ");
         else break;
        }
         gotoxy(ene,k);
         printf(" ");
         Sleep(1000);
    }
}
