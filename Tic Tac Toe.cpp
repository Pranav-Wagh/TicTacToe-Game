#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define EMPTY 0
#define EX 1
#define OH 2
int arr[9],nextchar=EX;
struct rect
{
	int x1,y1,x2,y2;
};
struct rect square[]={
	10,10,49,49,
	60,10,99,49,
	110,10,149,49,
	10,60,49,99,
	60,60,99,99,
	110,60,149,99,
	10,110,49,149,
	60,110,99,149,
	110,110,149,149
	};
int initmouse();
int hidemouseptr();
int resetgame();
int drawgrid();
int showmouseptr();
int onlbuttondown(int , int );
int getmousepos(int *button,int *x,int *y);
int drawexsandohs();
int isgameover();
int onrbuttondown(int x,int y);
int drawx(int i);
int drawoh(int i);
int findwinner();
int isdrawn();
int main ()
{
	int gd=DETECT,gm,button;
	int x,y,over,i,flag;
	char reset='y';
	initgraph(&gd,&gm,"C:\\turboc3\\BGI");
	while(reset=='y')
	{
		drawgrid();
		showmouseptr();
		for(i=0;i<=8;i++)
		arr[i]=EMPTY;
		over=FALSE;
		while(over==FALSE)
		{
			getmousepos(&button,&x,&y);
			if((button & 1)==1)
			{
				onlbuttondown(x,y);
				drawexsandohs();
				over=isgameover();
			}
			if((button & 2)==2)
			{
				onrbuttondown(x,y);
				drawexsandohs();
				over=isgameover();
			}

		}
		reset=resetgame();
		hidemouseptr();

	}
	closegraph();
	restorecrtmode();
	getch();
	return 0;
}
	initmouse()
	{
		union REGS i,o;
		i.x.ax=0;
		int86(0x33,&i,&o);
		return(o.x.ax);
	}
	showmouseptr()
	{
		union REGS i,o;
		i.x.ax=1;
		int86(0x33,&i,&o);
		return 0;
	}
	hidemouseptr()
	{
		union REGS i,o;
		i.x.ax=2;
		int86(0x33,&i,&o);
		return 0;
	}
	drawgrid()
	{
		setcolor(BLUE);
		setfillstyle(BLUE,BLUE);
		bar(54,10,60,149);
		floodfill(55,15,BLUE);
		bar(10,54,149,60);
		floodfill(11,55,BLUE);
		bar(10,104,149,110);
		floodfill(11,109,BLUE);
		bar(104,10,110,149);
		floodfill(105,11,BLUE);
		return 0;
	}
	getmousepos(int *button,int *x,int *y)
	{
		union REGS i,o;
		i.x.ax=3;
		int86(0x33,&i,&o);
		*button=o.x.bx;
		*x=o.x.cx;
		*y=o.x.dx;
		return 0;
	}
	onlbuttondown(int x,int y)
	{
		int i;
		if(nextchar==OH)
		return 0;
		for(i=0;i<=8;i++)
		{
			if((x>=square[i].x1&&x<=square[i].x2&&y>=square[i].y1&&y<=square[i].y2&&arr[i]==EMPTY))
			{
				arr[i]=EX ;
				nextchar=OH;
				break;
			}
		}
		return 0;
	}
	onrbuttondown(int x,int y)
	{
		int i;
		if(nextchar==EX)
		return 0;
		for(i=0;i<=8;i++)
		{
			if((x>=square[i].x1&&x<=square[i].x2&&y>=square[i].y1&&y<=square[i].y2&&arr[i]==EMPTY))
			{
				arr[i]=OH;
				nextchar=EX;
				break;
			}
		}
		return 0;
	}
	drawexsandohs()
	{
		int i;
		for(i=0;i<=8;i++)
		{
			if(arr[i]==EX)
			drawx(i);
			if(arr[i]==OH)
			drawoh(i);
		}
		return 0;
	}
	drawx(int i)
	{
		setcolor(MAGENTA);
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);
		hidemouseptr();
		line(square[i].x1+10,square[i].y1+10,square[i].x2-10,square[i].y2-10);
		line(square[i].x2-10,square[i].y1+10,square[i].x1+10,square[i].y2-10);
		showmouseptr();
	 return 0;
	}
	drawoh(int i)
	{
		hidemouseptr();
		setcolor(YELLOW);
		circle((square[i].x1+square[i].x2)/2,(square[i].y1+square[i].y2)/2,10);
		showmouseptr();
	 return 0;
	}
	isgameover()
	{
		int winner;
		winner=findwinner();
		settextstyle(1,0,2);
		setcolor(GREEN);
		if(winner==EX)
		{
			outtextxy(10,250,"X won the game!!");
			return (TRUE);
		}
		else
		{
			if(winner==OH)
			{
				outtextxy(10,250,"O won th game!!");
				return (TRUE);
			}
			else
			{
			if(isdrawn())
			{
				outtextxy(10,250,"Game is draw!!");
				return (TRUE);
			}
			else
			return(FALSE);
		}
		}
	}
	int findwinner()
	{
		static int pattern[8][3]={
						0,1,2,
						3,4,5,
						6,7,8,
						0,3,6,
						1,4,7,
						2,5,8,
						0,4,8,
						2,4,6
					};
		int i;
		for(i=0;i<=7;i++)
		{
			if(arr[pattern[i][0]]==EX&&arr[pattern[i][1]]==EX&&arr[pattern[i][2]]==EX)
			{       setcolor(MAGENTA);
				setlinestyle(SOLID_LINE,0,THICK_WIDTH);
				if(i==0)
				line(10,30,149,30);
				if(i==1)
				line(10,80,149,80);
				if(i==2)
				line(10,130,149,130);
				if(i==3)
				line(30,10,30,149);
				if(i==4)
				line(80,10,80,149);
				if(i==5)
				line(130,10,130,149);
				if(i==6)
				line(10,10,149,149);
				if(i==7)
				line(10,149,149,10);
				return (EX);
			}
			if(arr[pattern[i][0]]==OH&&arr[pattern[i][1]]==OH&&arr[pattern[i][2]]==OH)
			{
				 setcolor(YELLOW);
				setlinestyle(SOLID_LINE,0,THICK_WIDTH);
				 if(i==0)
				line(10,30,149,30);
				if(i==1)
				line(10,80,149,80);
				if(i==2)
				line(10,130,149,130);
				if(i==3)
				line(30,10,30,149);
				if(i==4)
				line(80,10,80,149);
				if(i==5)
				line(130,10,130,149);
				if(i==6)
				line(10,10,149,149);
				if(i==7)
				line(10,149,149,10);
				return (OH);
			}
		}
		return 0;
	}
	isdrawn()
	{
		int i;
		for(i=0;i<=8;i++)
		{
			if(arr[i]==EMPTY)
			return (0);
		}
		return (1);
	}
	resetgame()
	{
		char ch;
		int i;
		outtextxy(10,300,"Do you want to continue(Y/N)? Please type...");
		fflush(stdin);
		ch=getch();
		if((ch=='y')||(ch=='Y'))
		{
			nextchar=EX;
			return('y');
		}
		else
		return('n');
	}
