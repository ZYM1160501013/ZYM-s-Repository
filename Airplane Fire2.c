/*����������ǲ���ֱ����ָ��λ������ɻ��ķ�ʽ����ɻ��͵л���״���ܺõ�
  ����˹��������������Ҹó�������л��Ǻ�˳���ģ�ֻ����һ��bug�����޷�
  �޸��������ڲ����л���ͬʱ�ֻ��ڵл��������һ���ӵ���ͼ��һ��ʼ�ǽ�����
  �л��������Ǽ�һ������������л������Ų������ӵ�bugʱ���ֻ������ӵ����һ
  ��λ�õĵط������ӵ�ͼ�Σ����bug�޷��޸�������Ҳ�͵���������뱻����
  */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include <windows.h>
#pragma comment(lib, "Winmm.lib")

// ȫ�ֱ���
int position_x,position_y; // �ɻ�λ��
int bullet_x,bullet_y; // �ӵ�λ��
int enemy_x,enemy_y; // �л�λ��
int high,width; //  ��Ϸ����ߴ�
int score; // �÷�
int speed; //�л��ٶ�
int speed1=10; //�ٶȲ���
int flag=0; //ѭ��ִ�б�ʾ
int flag1=0; //��ʾ����
int life=5; //������

void gotoxy(int x,int y)//��������������,����ƶ���ԭ��λ�ý����ػ�
{
    HANDLE hOut;
    COORD pos= {x,y};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void GameStart()//��Ϸ��ʼ
{
	drawborder();
	gotoxy(6, 7); printf("Airplane Fire Game");
	gotoxy(11, 9); printf("Welcome!");
	gotoxy(12, 11); printf("Hello!");
	gotoxy(8, 14); system("pause");
}

void GameOver()//��Ϸ����
{
	system("cls");
	drawborder();
	gotoxy(9, 8); printf("Game Over");
	gotoxy(10, 10); printf("score:%d", score);
	gotoxy(2, 12);
	printf("Press any key to continue.");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	getch();
	exit(0);
}

void startup() // ���ݳ�ʼ��
{
	high = 20;
	width = 30;
	position_x = high-4;
	position_y = width/2;
	bullet_x = -10;
	bullet_y = position_y;
	enemy_x = 1;
	enemy_y = position_y;
	score = 0;
	flag = 0;
}

int drawborder() //���߿�
{
    int i,j;
    for(i=0;i<=30;i++)
    {
      gotoxy(i,0);
      printf("#");
      gotoxy(i,20);
      printf("#");
    }

    for(j=0;j<=19;j++)
    {
      gotoxy(0,j);
      printf("#");
      gotoxy(30,j);
      printf("#");
    }
    return 0;
}

void drawplane() //���ɻ�ͼ��
{
   gotoxy(position_y,position_x);
   printf("*");
   gotoxy(position_y-1,position_x+1);
   printf("***");
   gotoxy(position_y-2,position_x+2);
   printf("*****");
   gotoxy(position_y-1,position_x+3);
   printf("* *");
}

void drawenemy() //���л�ͼ��
{
   gotoxy(enemy_y,enemy_x);
   printf("*");
}

void coverplane() //����ԭ�ɻ�ͼ��
{
   gotoxy(position_y,position_x);
   printf(" ");
   gotoxy(position_y-1,position_x+1);
   printf("   ");
   gotoxy(position_y-2,position_x+2);
   printf("     ");
   gotoxy(position_y-1,position_x+3);
   printf("    ");
}

void coverenemy() //����ԭ�л�ͼ��
{
   gotoxy(enemy_y,enemy_x);
   printf(" ");
}

void drawbullet() //���ӵ�ͼ��
{
    gotoxy(bullet_y,bullet_x);
    printf("|");
}

void coverbullet() //����ԭ�ӵ�ͼ��
{
    gotoxy(bullet_y,bullet_x);
    printf(" ");
}

void show()  // ��ʾ����
{
    /*int i,j;*/
    drawplane();
    coverenemy();
    drawenemy();
    drawbullet();
    Sleep(50);
    coverbullet();
	/*gotoxy(0,0);  // ����ƶ���ԭ��λ�ý����ػ�����

	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==position_x-4) && (j==position_y)||(i==position_x-3) && (j==position_y-1))
				printf("*");  //   ����ɻ�*
			else if ((i==position_x-3) && (j==position_y)||(i==position_x-3) && (j==position_y+1))
                printf("*");  //   ����ɻ�*
            else if ((i==position_x-2) && (j==position_y-2)||(i==position_x-2) && (j==position_y-1))
                printf("*");  //   ����ɻ�*
            else if ((i==position_x-2) && (j==position_y)||(i==position_x-2) && (j==position_y+1))
                printf("*");  //   ����ɻ�*
            else if ((i==position_x-2) && (j==position_y+2)||(i==position_x-1) && (j==position_y-1)||(i==position_x-1) && (j==position_y+1))
                printf("*");  //   ����ɻ�*
			else if ((i==enemy_x) && (j==enemy_y))
				printf("*");  //   ����л�@
			else if ((i==bullet_x) && (j==bullet_y))
				printf("|");  //   ����ӵ�|
			else
				printf(" ");  //   ����ո�
		}
		printf("\n");
	}*/
}

void static_info()//��̬��Ϣ������Ϸ����������ʾ
{
    drawborder();
    dynamic_info();
	gotoxy(high+14, 0); printf("%c %c %c %c �����ƶ�����", 'w', 'a', 's', 'd');
	gotoxy(width + 4, 2); printf("��p����ͣ");
	gotoxy(width + 4, 4); printf("F1����,F2����");
	gotoxy(width + 4, 6); printf("�÷�:");
	gotoxy(width + 4, 8); printf("����:");
	gotoxy(width + 4, 10); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
        FOREGROUND_INTENSITY); printf("F4:��");//��ɫ
	gotoxy(width + 4, 12); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED |
		FOREGROUND_INTENSITY); printf("F5:��");//��ɫ
	gotoxy(width + 4, 14); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
        FOREGROUND_INTENSITY); printf("F6:��");//�� ɫ
	gotoxy(width + 4, 16); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED |
		FOREGROUND_INTENSITY); printf("F7:��");//��ɫ
	gotoxy(width + 4, 18); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED |
		FOREGROUND_INTENSITY); printf("F8:��");//����ɫ
	gotoxy(width + 4, 20); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |
        FOREGROUND_RED);printf("F9:��");//��ɫ*/
}

int dynamic_info()//��̬��Ϣ������Ϸ�÷�
{
	gotoxy(width + 10, 6); printf("%d", score);
	gotoxy(width + 10, 8); printf("%d", life);
	return 0;
}

void updateWithoutInput()  // ���û������޹صĸ���
{
	if (bullet_x>1)
		bullet_x--;
    if (bullet_x==1)
        coverbullet();
	if ((bullet_x==enemy_x) && (bullet_y==enemy_y))  // �ӵ����ел�
	{
	    coverenemy();
	    coverbullet();
		score++;
		dynamic_info();               // ������1
		enemy_x = 1;           // �����µķɻ�
		enemy_y =rand()%width;
		if(enemy_y==1)enemy_y++;
		if(enemy_y==29)enemy_y=enemy_y-3;
		if(enemy_y==28)enemy_y--;
		bullet_x = -2;          // �ӵ���Ч
	}
	if (enemy_x>=high-1)   // �л��ܳ���ʾ��Ļ
	{
	    coverenemy();
	    life--;
	    dynamic_info();
	    flag1++;
		enemy_x = 1;           // �����µķɻ�
		enemy_y = rand()%width;
		if(enemy_y==1)enemy_y++;
		if(enemy_y==29)enemy_y=enemy_y-3;
		if(enemy_y==28)enemy_y--;
	}

	// �������Ƶл������ƶ����ٶȡ�ÿ������ѭ�������ƶ�һ�εл�
	// �����޸ĵĻ����û����������ٶȻ��Ǳ��ֺܿ죬������NPC���ƶ���ʾ���Խ���
	static int speed = 0;
	    if (speed<speed1)
		    speed++;
	    if (speed==speed1)
	    {
	        coverenemy();
		    enemy_x++;
		    speed = 0;
	    }
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a')
			{coverplane();
			 position_y--;
			  if(position_y==2)position_y++;
            }              // λ������
		if (input == 'd')
			{coverplane();
			 position_y++;
			  if(position_y==28)position_y--;
			}              // λ������
		if (input == 'w')
			{coverplane();
			 position_x--;
			  if(position_x==0)position_x++;
			}              // λ������
		if (input == 's')
			{coverplane();
			 position_x++;
			  if(position_x==17)position_x--;
			}              // λ������
        if (input == 'p')while(getch()!='p');
        if (input == 59 )
            {
                speed1=speed1-2;
                if(speed1==6)speed1=speed1+2;
            }
        if (input == 60 )
            {   speed1=speed1+2;
                if(speed1==36)speed1=speed1-2;
            }
        if (input == 62 )
            {system("color 0C"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input == 63 )
            {system("color 0E"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input == 64 )
            {system("color 0A"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
		FOREGROUND_INTENSITY); }
        if (input == 65 )
            {system("color 0D"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED |
		FOREGROUND_INTENSITY); }
        if (input == 66 )
            {system("color 0F"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |
		FOREGROUND_RED | FOREGROUND_INTENSITY); }
        if (input == 67 )
            {system("color 08"); static_info(); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |
		FOREGROUND_RED);}
		if (input == ' ')  // �����ӵ�
		{
			bullet_x = position_x-2;  // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
			bullet_y = position_y;
		}

	}
}

void sweep()//����
{
   HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO cci;
   GetConsoleCursorInfo(hOut,&cci);//��ȡ�����Ϣ
   cci.bVisible = FALSE;//���ع��
   SetConsoleCursorInfo(hOut,&cci);//���ù����Ϣ
}

void main()
{
    GameStart();
    system("cls");
    /*PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);*/
	startup();  // ���ݳ�ʼ��
	static_info();
	sweep();
	while (!flag) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		if(flag1==5)flag=!flag;
		updateWithInput();  // ���û������йصĸ���
	}
    GameOver();
}
