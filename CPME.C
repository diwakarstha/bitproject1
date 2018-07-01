#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>
int l=65;		//avoids game mouse from touching screen graphics
long int Plevel=1,Clevel=1,Pscore=0,Lscore=50,Plife=0,Clife=3,speed=10;
FILE *fp,*fp1;

	     //files where name and highscore are scored
struct per
{
char name[100];                 //stores score scored by currently playing player
long Cscore;                    //stores name of player playing
}pl,pl2,pl3;
union REGS i, o;

/**************************DECLEARATION OF FUNCTIONS*************************/
void showcat(int x,int y);
void hidecat(int ex,int ey);
void showobstacle();
void hideobstacle();
void randxy();
void showmouse(int i,int j);
void hidemouse(int i,int j);
void gameover();
int highest();
int help();
int credit();
void screen(long int Iscore,long int Ilife,long int Ilevel);
void missed(int);
void levelup();
void catmove();
int gamemenu();
void body();
void load();
void mainmenu();
void prostart();

/************************Initialization of mouse***********************/
int initmouse()
{
   i.x.ax = 0;
   int86(0X33,&i,&o);
   return ( o.x.ax );
}

void showmouseptr()
{
   i.x.ax = 1;
   int86(0X33,&i,&o);
}

void hidemouseptr()
{
   i.x.ax = 2;
   int86(0X33,&i,&o);
}

void getmousepos(int *button, int *x, int *y)
{
   i.x.ax = 3;
   int86(0X33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}
/**************************CAT GRAPHICS*************************/
void showcat(int x,int y)
{

	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	ellipse(x,y+25/2,45,135,30/4,30/4);  //top head

	ellipse(x,y+25/2,180,250,30/4,30/4);// left chick
	ellipse(x,y+25/2,290,360,30/4,30/4);// right chick

	ellipse(x+17.5/2,y,245,295,40/4,30/4);//right ear up
	ellipse(x+32/2,y+37.5/2,110,150,40/4,50/4);//right ear down

	ellipse(x-17.5/2,y,245,295,40/4,30/4);//left ear up
	ellipse(x-32/2,y+37.5/2,30,70,40/4,50/4);// left ear down

	ellipse(x-30/2,y+45/2,355,6,50/4,100/4);// left neck
	ellipse(x+30/2,y+45/2,173,185,50/4,100/4);// right neck

	ellipse(x,y+72.5/2,100,175,50/4,45/4); // left stomach
	ellipse(x,y+72.5/2,5,80,50/4,45/4);// right stomach

	ellipse(x-20/2,y+80/2,100,225,30/4,20/4);// left leg thai
	ellipse(x+20/2,y+80/2,315,80,30/4,20/4);//right leg thai

	line(x-30/2,y+87.5/2,x+30/2,y+87.5/2);
	floodfill(x,y+25/2,RED);

	setcolor(8);            //color
	setfillstyle(SOLID_FILL,8);
	pieslice(x-25/2,y+87.5/2,0,180,5/2);  // left leg second
	pieslice(x+25/2,y+87.5/2,0,180,5/2);  // right leg second
	pieslice(x+5/2,y+87.5/2,0,180,5/2);  // right leg first
	pieslice(x-5/2,y+87.5/2,0,180,5/2);  // left leg first

	setcolor(BLACK);
	arc(x-5/2,y+25/2,175,310,10/4);   // left eye down
	line(x-1.5/2,y+28.5/2,x-9.5/2,y+25/2);    // left eye up

	arc(x+5/2,y+25/2,230,5,10/4);   // left eye down
	line(x+1.5/2,y+28.5/2,x+9.5/2,y+25/2);    // left eye up

	pieslice(x,y+32.5/2,0,180,1/4);  // nose

	line(x-1,y+36.5/2,x+1,y+36.5/2); // mouth

	setcolor(WHITE);
	settextstyle(2,HORIZ_DIR,0);  //font
	outtextxy(x-16/2,y+60/2,"CAT");




}

/**************************MAsKING OF CAT GRAPHICS*************************/
void hidecat(int ex,int ey)
{
	int x=ex,y=ey;
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	rectangle(x-19,y+3,x+19,y+45);
	floodfill(x,y+10,BLACK);

}

/**************************OBSTACLE GRAPHICS*************************/
void showobstacle(int a,int b)
{
setcolor(RED);
setfillstyle(SOLID_FILL,RED);
circle(a+26,b+75,5);
floodfill(a+26,b+75,RED);
}

/**************************MASKING OF OBSTACLE GRAPHICS*************************/
void hideobstacle(int a,int b)
{
setcolor(BLACK);
setfillstyle(SOLID_FILL,BLACK);
circle(a+26,b+75,5);
floodfill(a+26,b+75,BLACK);
}

/**************************GENERATES RANDOM POSITION FOR OBSTACLES*************************/
void ranxy(int *rx,int *ry)
{
		int Rgenx=0,Rgeny=0;
		time_t t;
		srand((unsigned)time(&t));
		Rgenx=rand()%10;
		*rx=49*Rgenx;
		Rgeny=rand()%9;
		*ry=49*Rgeny;

}


/**************************MOUSE GRAPHICS*************************/
void showmouse(int i,int j)
{
	setcolor(WHITE);
	line(i-19/3,l+j,i,l+j);//head
	line(i-19/3,l+j,i,l+j-19/3);//head

	line(i,l+j-19/3,i,l+j-39/3);//F ear
	line(i+20/3,l+j-19/3,i+20/3,l+j-39/3);//B ear
	line(i,l+j-39/3,i+10/3,l+j-29/3);//F ear CU
	line(i+20/3,l+j-39/3,i+10/3,l+j-29/3);//B ear CU
	line(i+20/3,l+j-19/3,i+15,l+j-35/3);//up body line

	line(i,l+j,i+18,l+j);//down body line

	arc(i,l+j+6/3,270,90,5/3);//down frontleg
	arc(i-4/3,l+j+1/3,270,360,5/3);//up frontleg

	arc(i+15,l+j+6/3,270,90,5/3);// down back leg
	line(i+15,l+j+11/3,i+35/3,l+j+11/3);// down back leg
	arc(i+15,l+j+1/3,270,360,5/3);// up back leg
	line(i+15,l+j+6/3,i+35/3,l+j+6/3);// up back leg

	arc(i+12,l+j-25/3+3,330,75,25/3);// tail main part
	line(i+20,l+j-4,i+28,l+j-4);//tail

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	circle(i,l+j-9/3,2/3);//eye
	floodfill(i,l+j-4,WHITE);
}

/**************************MAKING MOUSE GRAPHICS*************************/
void hidemouse(int i,int j)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	line(i-19/3,l+j,i,l+j);//head
	line(i-19/3,l+j,i,l+j-19/3);//head

	line(i,l+j-19/3,i,l+j-39/3);//F ear
	line(i+20/3,l+j-19/3,i+20/3,l+j-39/3);//B ear
	line(i,l+j-39/3,i+10/3,l+j-29/3);//F ear CU
	line(i+20/3,l+j-39/3,i+10/3,l+j-29/3);//B ear CU
	line(i+20/3,l+j-19/3,i+16,l+j-35/3);//up body line

	line(i,l+j,i+18,l+j);//down body line

	arc(i,l+j+6/3,270,90,5/3);//down frontleg
	arc(i-4/3,l+j+1/3,270,360,5/3);//up frontleg

	arc(i+15,l+j+6/3,270,90,5/3);// down back leg
	line(i+15,l+j+11/3,i+35/3,l+j+11/3);// down back leg
	arc(i+15,l+j+1/3,270,360,5/3);// up back leg
	line(i+15,l+j+6/3,i+35/3,l+j+6/3);// up back leg

	arc(i+12,l+j-25/3+3,330,75,25/3);// tail main part
	floodfill(i+10,l+j-10,BLACK);

	line(i+20,l+j-4,i+28,l+j-4);//tail
	arc(i,l+j+6/3,270,90,5/3);//down frontleg
	arc(i-4/3,l+j+1/3,270,360,5/3);//up frontleg

	arc(i+15,l+j+6/3,270,90,5/3);// down back leg
	line(i+15,l+j+11/3,i+35/3,l+j+11/3);// down back leg
	arc(i+15,l+j+1/3,270,360,5/3);// up back leg
	line(i+15,l+j+6/3,i+35/3,l+j+6/3);// up back leg

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	circle(i,l+j-9/3,2/3);//eye
	floodfill(i,l+j-4,BLACK);
}

/**************************AFTER GAME IS OVER*************************/
void gameover()
{
	long int z;
	char HS[10],dis[10],ch;
	cleardevice();
	for(z=1;z<10;z++){
				setcolor(BLACK);
				settextstyle(4,HORIZ_DIR,z-1);
				outtextxy(200-(10*(z-1)),100,"game over");
				setcolor(RED);
				settextstyle(4,HORIZ_DIR,z);
				outtextxy(200-(10*z),100,"game over");
				delay(100);
				sound(500);
				delay(10);
				sound(700);
				delay(10);
				sound(1500);
	}


	nosound();
	getch();
	fp=fopen("high3.txt","r");

	if(fp==NULL)
	{
		fp1=fopen("high3.txt","w");
		strcpy(pl3.name,"Robot");
		pl3.Cscore=0;
		fwrite(&pl3,sizeof(struct per),1,fp1);
		fclose(fp1);
	}

	fseek(fp,0,SEEK_SET);
	fread(&pl2,sizeof(struct per),1,fp);
	if(pl.Cscore>pl2.Cscore){

			fclose(fp);
			fp=fopen("high2.txt","r");

			if(fp==NULL)
			{
			fp1=fopen("high2.txt","w");
			strcpy(pl3.name,"Robot");
			pl3.Cscore=0;
			fwrite(&pl3,sizeof(struct per),1,fp1);
			fclose(fp1);
			}

			fseek(fp,0,SEEK_SET);
			fread(&pl2,sizeof(struct per),1,fp);

			if(pl.Cscore>pl2.Cscore){

					fp1=fopen("high3.txt","w");
					fwrite(&pl2,sizeof(struct per),1,fp1);
					fclose(fp1);
					fclose(fp);
					fp=fopen("high1.txt","r");

					if(fp==NULL)
					{
					fp1=fopen("high1.txt","w");
					strcpy(pl3.name,"Robot");
					pl3.Cscore=0;
					fwrite(&pl3,sizeof(struct per),1,fp1);
					fclose(fp1);
					}

					fseek(fp,0,SEEK_SET);
					fread(&pl2,sizeof(struct per),1,fp);

					if(pl.Cscore>pl2.Cscore){

							setcolor(GREEN);
							settextstyle(3,HORIZ_DIR,0);
							outtextxy(50,50,"YOU HAVE SCORED FIRST HIGH SCORE");
							settextstyle(1,HORIZ_DIR,0);
							outtextxy(219,219,"YOUR SCORE");
							outtextxy(219,249,pl.name);
							ltoa(pl.Cscore,dis,10);
							outtextxy(219,289,dis);

							fp1=fopen("high2.txt","w");
							fwrite(&pl2,sizeof(struct per),1,fp1);
							fclose(fp1);

							fp1=fopen("high1.txt","w");
							fwrite(&pl,sizeof(struct per),1,fp1);
							fclose(fp1);

					}

					else{

							setcolor(GREEN);
							settextstyle(3,HORIZ_DIR,0);
							outtextxy(30,50,"YOU HAVE SCORED SECOND HIGH SCORE");
							settextstyle(1,HORIZ_DIR,0);
							outtextxy(219,219,"YOUR SCORE");
							outtextxy(219,249,pl.name);
							ltoa(pl.Cscore,dis,10);
							outtextxy(219,289,dis);


							fp1=fopen("high2.txt","w");
							fwrite(&pl,sizeof(struct per),1,fp1);
							fclose(fp1);

					}
			}

			else{

					setcolor(GREEN);
					settextstyle(3,HORIZ_DIR,0);
					outtextxy(50,50,"YOU HAVE SCORED THIRD HIGH SCORE");
					settextstyle(1,HORIZ_DIR,0);
					outtextxy(219,219,"YOUR SCORE");
					outtextxy(219,249,pl.name);
					ltoa(pl.Cscore,dis,10);
					outtextxy(219,289,dis);

					fp1=fopen("high3.txt","w");
					fwrite(&pl,sizeof(struct per),1,fp1);
					fclose(fp1);

			}

		}

		else{

		setcolor(RED);
		settextstyle(2,HORIZ_DIR,5);
		outtextxy(100,50,"YOU WERE UNABLE TO SET HIGH SCORRE BETTER LUCK NEXT TIME");
		settextstyle(1,HORIZ_DIR,0);
		outtextxy(219,219,"YOUR SCORE");
		outtextxy(219,249,pl.name);
		ltoa(pl.Cscore,dis,10);
		outtextxy(219,289,dis);

		}
		fclose(fp);
	enter:
	//printf("");
	outtextxy(89,319,"DO YOU WANT TO PLAY AGAIN?");

	outtextxy(139,359,"Press (Y) to Play Again");

	outtextxy(139,399,"   Press (N) to Exit");
	ch=getch();
	if(ch=='y'||ch=='Y')
	mainmenu();
	else if(ch=='n'||ch=='N')
	exit();
	else
	goto enter;

}

/**************************DISPLAYS HIGHEST SCORE SAVED*************************/
int highest()
{
	int button,mx,my;
	char array[100],HS[100],ch;
	high:
	cleardevice();


	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(100,100,538,378);
	floodfill(200,200,WHITE);

	settextstyle(3,HORIZ_DIR,0);
	outtextxy(250,125,"HIGHSCORE");

	//reset box
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(420,278,520,328);
	floodfill(500,300,WHITE);

	settextstyle(3,HORIZ_DIR,0);
	outtextxy(430,280,"RESET");

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(120,278,220,328);
	floodfill(200,300,WHITE);

	settextstyle(3,HORIZ_DIR,0);
	outtextxy(125,280,"TOP 3");

	//read high score from file
	setcolor(GREEN);
	fp=fopen("high1.txt","r");
	if(fp==NULL)
	{
	fp1=fopen("high1.txt","w");
	strcpy(pl3.name,"Robot");
	pl3.Cscore=0;
	fwrite(&pl3,sizeof(struct per),1,fp);
	fclose(fp1);
	}

	fseek(fp,0,SEEK_SET);
	fread(&pl2,sizeof(struct per),1,fp);
	strcpy(array,pl2.name);
	ltoa(pl2.Cscore,HS,10);
	outtextxy(200,175,array);
	outtextxy(200,225,HS);
	fclose(fp);



	setcolor(BLACK);
	settextstyle(2,HORIZ_DIR,0);
	outtextxy(250,325,"PREES ANY KEY TO RETURN");
	showmouseptr();
	while(!kbhit())
	{
		getmousepos(&button,&mx,&my);
		if( button==1 && mx>420 && mx<520 && my>278 && my<328 )
		{
			button=-1;
			delay(100);

			strcpy(pl3.name,"Robot");
			pl3.Cscore=0;

			fp1=fopen("high1.txt","w");
			fwrite(&pl3,sizeof(struct per),1,fp);
			fclose(fp1);

			fp1=fopen("high2.txt","w");
			fwrite(&pl3,sizeof(struct per),1,fp);
			fclose(fp1);

			fp1=fopen("high3.txt","w");
			fwrite(&pl3,sizeof(struct per),1,fp);
			fclose(fp1);

			outtextxy(250,300,"HIGHSCORE HAS BEEN RESET");
		}
		if( button==1 && mx>120 && mx<220 && my>278 && my<328 )
		{
			hidemouseptr();
			cleardevice();
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,RED);
			rectangle(100,100,538,378);
			floodfill(200,200,WHITE);

			settextstyle(3,HORIZ_DIR,0);
			outtextxy(250,125,"HIGHSCORE");

			//display top three highscore
			fp=fopen("high1.txt","r");
			fseek(fp,0,SEEK_SET);
			fread(&pl2,sizeof(struct per),1,fp);
			strcpy(array,pl2.name);
			ltoa(pl2.Cscore,HS,10);
			settextstyle(2,HORIZ_DIR,5);
			outtextxy(220,200,array);
			outtextxy(450,200,HS);
			fclose(fp);

			fp=fopen("high2.txt","r");
			fseek(fp,0,SEEK_SET);
			fread(&pl2,sizeof(struct per),1,fp);
			strcpy(array,pl2.name);
			ltoa(pl2.Cscore,HS,10);
			outtextxy(220,220,array);
			outtextxy(450,220,HS);
			fclose(fp);

			fp=fopen("high3.txt","r");
			fseek(fp,0,SEEK_SET);
			fread(&pl2,sizeof(struct per),1,fp);
			strcpy(array,pl2.name);
			ltoa(pl2.Cscore,HS,10);
			outtextxy(220,240,array);
			outtextxy(450,240,HS);
			fclose(fp);

			outtextxy(250,325,"PREES ANY KEY TO RETURN");
			showmouseptr();
			getch();
			hidemouseptr();
			goto high;
		}

	}

	return 0;
}

/**************************DISPLAYS HOME SCREEN*************************/
int help()
{
	cleardevice();
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(90,90,578,388);
	rectangle(100,100,568,378);
	floodfill(95,95,WHITE);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,7);
	rectangle(100,100,568,378);
	floodfill(200,200,WHITE);

	setcolor(BLUE);
	settextstyle(3,HORIZ_DIR,0);
	outtextxy(305,110,"HELP");

	setcolor(BLUE);
	settextstyle(2,HORIZ_DIR,5);
	outtextxy(110,160,"-> use arrow keys or w,s,a,d to move the cat.");

	outtextxy(110,190,"-> Eating mouse will give you 10 points.");

	outtextxy(110,220,"-> Missing mouse will make you loose 2 points and a life.");

	outtextxy(110,250,"-> Avoid red dot touching it will make you loose 5 points");
	outtextxy(130,270,"and a life.");

	outtextxy(110,300,"-> Level start increasing when score reach 50 and continue");
	outtextxy(130,320,"increasing at every score difference of 50 until you");
	outtextxy(130,340,"reach level 10.");
	showmouseptr();

	return 0;
}

/**************************CREDIT SCREEN*************************/
int credit()
{
	cleardevice();
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(190,40,448,428);
	rectangle(200,50,438,418);
	floodfill(200,45,WHITE);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,7);
	rectangle(200,50,438,418);
	floodfill(300,200,WHITE);

	setcolor(BLUE);
	settextstyle(3,HORIZ_DIR,0);
	outtextxy(280,55,"CREDIT");

	setcolor(BLUE);
	settextstyle(2,HORIZ_DIR,6);
	outtextxy(270,120,"GROUP MEMBER");
	outtextxy(270,121,"_____ ______");
	settextstyle(2,HORIZ_DIR,5);
	outtextxy(267,140,"Diwakar Shrestha");
	outtextxy(269,155,"Mausam Shrestha");
	outtextxy(285,170,"Biplop Lama");

	setcolor(BLUE);
	settextstyle(2,HORIZ_DIR,6);
	outtextxy(277,200,"SUPERVISOR");
	outtextxy(277,201,"__________");
	settextstyle(2,HORIZ_DIR,5);
	outtextxy(272,220,"Bikash Neupane");

	setcolor(BLUE);
	settextstyle(2,HORIZ_DIR,6);
	outtextxy(277,250,"SUPPORTER");
	outtextxy(277,251,"_________");
	settextstyle(2,HORIZ_DIR,5);
	outtextxy(286,270,"Akash Rai");
	outtextxy(286,285,"Amit Lama");

	settextstyle(2,HORIZ_DIR,8);
	outtextxy(251,350,"THANK YOU");
	showmouseptr();
	return 0;
}

/**************************GAME SCREEN REBUILT*************************/
void screen(long int Iscore,long int Ilife,long int Ilevel)
{
	//long int Ilevel=1,Ilife=3,Iscore=0;
	char dis[10],array[100],HS[100];

	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(0,0,639,23);
	floodfill(50,15,BLUE);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,GREEN);
	rectangle(0,23,639,39);
	floodfill(50,30,WHITE);

	setcolor(WHITE);
	line(0,39,639,39);

	setcolor(WHITE);
	line(0,23,639,23);

	settextstyle(2,HORIZ_DIR,0); //font
	setcolor(WHITE);
	outtextxy(10,5,"MOUSE EATER");

	settextstyle(2,HORIZ_DIR,0);
	outtextxy(200,5,"HIGHSCORE : ");

	fp=fopen("high1.txt","r");
	if(fp==NULL)
	{
	fp=fopen("high1.txt","w");
	strcpy(pl3.name,"Robot");
	pl3.Cscore=0;
	fwrite(&pl3,sizeof(struct per),1,fp);
	fclose(fp);
	}

	fseek(fp,0,SEEK_SET);
	fread(&pl2,sizeof(struct per),1,fp);
	strcpy(array,pl2.name);
	outtextxy(300,5,array);
	ltoa(pl2.Cscore,HS,10);
	//outtextxy(400,5,HS);
	fclose(fp);

	//outtextxy(400,5,"  ");

	setcolor(GREEN);
	outtextxy(400,5,HS);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(614,0,639,23);
	floodfill(620,15,WHITE);
	outtextxy(624.5,5,"X");

	//MENU text display
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	rectangle(0,23,270,39);
	floodfill(20,30,RED);
	setcolor(WHITE);
	outtextxy(10,25,"PRESS 'P' to pause game and 'Esc'/'X' to exit ");

	//level text display
	ltoa(Ilevel,dis,10);
	setcolor(RED);
	outtextxy(400,25,dis);
	outtextxy(350,25,"LEVEL");

	//score text display
	ltoa(Iscore,dis,10);
	setcolor(BLUE);
	outtextxy(500,25,dis);
	outtextxy(450,25,"score");

	//life text display
	ltoa(Ilife,dis,10);
	setcolor(RED);
	outtextxy(600,25,dis);
	outtextxy(550,25,"life");

}

void missed(int decrease)
{
	char dis[10];
	if(Clife!=0)
	{
		Plife=Clife;
		Clife--;
		settextstyle(2,HORIZ_DIR,0);
		//life masking text display
		ltoa(Plife,dis,10);
		setcolor(GREEN);
		outtextxy(600,25,dis);

		//life text display
		ltoa(Clife,dis,10);
		setcolor(RED);
		outtextxy(600,25,dis);
		if(pl.Cscore!=0)
		{
		Pscore=pl.Cscore;
		pl.Cscore-=decrease;
		ltoa(Pscore,dis,10);
		setcolor(GREEN);
		outtextxy(500,25,dis);
		ltoa(pl.Cscore,dis,10);
		setcolor(BLUE);
		outtextxy(500,25,dis);
		}
	}
	else
	{
	gameover(pl.Cscore);
	}
}

void levelup()
{
	char dis[10];
	//increses score
	Pscore=pl.Cscore;
	pl.Cscore+=10;				//adds score by 10

	settextstyle(2,HORIZ_DIR,0);
	ltoa(Pscore,dis,10);
	setcolor(GREEN);
	outtextxy(500,25,dis);

	ltoa(pl.Cscore,dis,10);
	setcolor(BLUE);
	outtextxy(500,25,dis);

	//increses level
	if(speed>1&&pl.Cscore>=Lscore)
	{
	Lscore+=50;
	speed--;
		if(Clevel<=10)
		{
			Plevel=Clevel;
			Clevel++;    	//add level by 1
			ltoa(Plevel,dis,10);
			setcolor(GREEN);
			outtextxy(400,25,dis);
			ltoa(Clevel,dis,10);
			setcolor(RED);
			outtextxy(400,25,dis);
		}
	}
}

void catmove(int *x,int *y,int *ex,int *ey)
{
		int a,b;
		char ch;
		paused:
		if(kbhit())                                            //check if a key is pressed
				{
						ch=getch();
						if(ch=='w'||ch==72)                           	//move upward
						{
								a=0;
								b=-49;
								*x=*x+a;
								*y=*y+b;
								//printf("x%d\ty%d",x,y);printf("ex%d\tey%d",ex,ey);
						}

						if(ch=='a'||ch==75)                           	//move left
						{
								a=-49;
								b=0;
								*x=*x+a;
								*y=*y+b;
								//printf("ex%d\tey%d",x,y);printf("ex%d\tey%d",ex,ey);

						}

						if(ch=='d'||ch==77)                          	//move right
						{
								a=49;
								b=0;
								*x=*x+a;
								*y=*y+b;
								//printf("ex%d\tey%d",x,y);printf("ex%d\tey%d",ex,ey);
						}

						if(ch=='s'||ch==80)                           	//move downward
						{
								a=0;
								b=49;
								*x=*x+a;
								*y=*y+b;
								//printf("ex%d\tey%d",x,y);printf("ex%d\tey%d",ex,ey);
						}
						if(ch=='p')					//pause the game and takes to gamemenu
						{
						gamemenu();
						screen(pl.Cscore,Clife,Clevel);			//builts the erased game screen
						}

						if(ch==27||ch=='x'||ch=='X')                           //exit when esc pressed
						exit(0);


				}
				//shows cat and creates the border area for cat to move
				if(*x>0&&*x<638&&*y>0&&*y<453){

				showcat(*x,*y);
				if(*ex!=*x||*ey!=*y)
				hidecat(*ex,*ey);
				}
		 		else{
					*x=*ex;
					*y=*ey;
				}

}

/**************************gamemenu*************************/
int gamemenu()
{
	int button,mx,my;
	char ch;
	cleardevice();

	keyhit:
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,GREEN);
	rectangle(150,80,500,400);
	floodfill(200,100,WHITE);

	setcolor(RED);
	settextstyle(4,VERT_DIR,5);
	outtextxy(200,155,"MENU");

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(275,150,470,190);
	floodfill(300,180,WHITE);
	setcolor(GREEN);
	settextstyle(3,HORIZ_DIR,0);
	outtextxy(295,150,"MAIN MENU");

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(275,200,470,240);
	floodfill(300,220,WHITE);
	setcolor(GREEN);
	settextstyle(3,HORIZ_DIR,0);
	outtextxy(335,200,"HELP");

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,RED);
	rectangle(275,250,470,290);
	floodfill(300,260,WHITE);
	setcolor(GREEN);
	settextstyle(3,HORIZ_DIR,0);
	outtextxy(315,250,"RESUME");

	setcolor(BLUE);
	settextstyle(5,HORIZ_DIR,1);
	outtextxy(190,340,"   CLICK ON ANY OPTION");
	outtextxy(190,370,"     OF YOUR CHOICE");
	showmouseptr();


	//detects mouse position and make decision according to choice made
	while(!kbhit())
	{
		getmousepos(&button,&mx,&my);
		if(button==1 && mx<=470 && mx>=275 && my<=190 && my>=150)
		{
			button = -1;
			hidemouseptr();
			mainmenu();		//goes bcak to main menu
		}

		if(button==1 && mx<=470 && mx>=275 && my<=240 && my>=200)
		{
			button = -1;
			hidemouseptr();
			help();			//displays help screen
			getch();
			hidemouseptr();
			cleardevice();
			goto keyhit;
		}

		if(button==1 && mx<=470 && mx>=275 && my<=280 && my>=250)
		{
			button = -1;
			hidemouseptr();
			cleardevice();		//resumes the game
			return 0;
		}
	}

if(kbhit())
getch();
goto keyhit;
}

/**************************BODY OF GAME*************************/
void body()
{
	int i,p=0,j=0;
	int rx=0,ry=0;
	//int a=0,b=0;
	static int x=320,y=235,ex=320,ey=235;
	//char ch;
	char dis[10];
	time_t t;
	srand((unsigned)time(&t));

	ate:
	p=rand()%9;		//creates random number for mouse apearing point
	j=49*p;			//creates position of mouse with random number
	ranxy(&rx,&ry);		//pass address of rx and ry to get andom position of obstacle
	for(i=660;i>-50;i--)
	{


		//detects if mouse touched end position of screen
		if((i-8)==-20)
		{
			missed(2);
		}

		//detects if cat touched the obstacle
		else if( x==(rx+26) && y==(ry+39))
		{
			sound(1500);
			hideobstacle(rx,ry);
			delay(100);
			nosound();
			hidecat(x,y);
			ranxy(&rx,&ry);
			showobstacle(rx,ry);
			missed(5);

		}

		//detects if cat touched mouse
		else if( ( (i+30)<=(x+19) && (i+30)>=(x-19) && (l+j+19)<=(y+45) && (l+j+19)>=(y+3) )||
		( (i-8)<=(x+19) && (i-8)>=(x-19) && (l+j-23)<=(y+45) && (l+j-23)>=(y+3) ) )
		{
			sound(700);
			delay(50);
			sound(1500);
			hideobstacle(rx,ry);
			delay(100);
			nosound();

			hidecat(x,y);
			hidemouse(i,j);

			levelup();
			goto ate;//takes back to random of mouse position





		}


		//shoes mouse, obstacle and moves cat
		else
		{
		showobstacle(rx,ry);
		showmouse(i,j);		//calls mouse graphics
		delay(speed);
		hidemouse(i,j);		//masks the screen coloured by mouse
		ex=x;
		ey=y;
		catmove(&x,&y,&ex,&ey);

		}
	}
	hideobstacle(rx,ry);		//hides obstacle

}



/**************************load screen*************************/
void load()
{       int a,x,y,i;
	x=getmaxx()/2;
	y=getmaxy()/2;

	//loading outline and text
	setcolor(CYAN);
	arc(162,239,90,270,13);
	arc(500,239,270,90,13);
	line(162,252,500,252);
	line(162,226,500,226);
	outtextxy(300,200,"LOADING.....");


	// name of game
	setcolor(RED);
	settextstyle(4,HORIZ_DIR,6);
	outtextxy(134,19,"MOUSE EATER");
	setcolor(WHITE);
	settextstyle(4,HORIZ_DIR,6.62);
	outtextxy(136,17,"MOUSE EATER");

	//name of programmers
	setcolor(WHITE);
	settextstyle(2,HORIZ_DIR,0);
	outtextxy(500,300,"PROJECT BY:");
	outtextxy(500,330,"DIWAKAR SHRESTHA");
	outtextxy(500,360,"MAUSAM SHRESTHA");
	outtextxy(500,390,"BIPLOP LAMA");

	//shows loding bar
	for(a=162;a<=500;a++)
	{
	setcolor(WHITE);
	setfillstyle(1,WHITE);
	circle(a,239,10);
	floodfill(a,239,WHITE);
	delay(4);
	}

	//asking to press any key
	setcolor(CYAN);
	settextstyle(5,HORIZ_DIR,2);
	outtextxy(x-60,y+100,"Enter Any Key");
	getch();

}


/**************************mainmenu*************************/
void mainmenu()
{

	int button,mx,my;
	cleardevice();
	Plevel=1;
	Clevel=1;
	Pscore=0;
	Lscore=50;
	Plife=0;
	Clife=3;
	speed=10;

	menu:
	//showmouseptr();//shows mouse pointer

	//menu topic
	setcolor(RED);
	settextstyle(10,HORIZ_DIR,3);
	outtextxy(160,19,"MENU");

	//shows choices
	setcolor(WHITE);
	//rectangle(160,130,252,155);
	settextstyle(10,HORIZ_DIR,1);
	outtextxy(160,119,"START");

	//rectangle(160,180,326,205);
	settextstyle(10,HORIZ_DIR,1);
	outtextxy(160,169,"HIGH SCORE");

	//rectangle(160,230,221,255);
	settextstyle(10,HORIZ_DIR,1);
	outtextxy(160,219,"HELP");

	//rectangle(160,280,283,305);
	settextstyle(10,HORIZ_DIR,1);
	outtextxy(160,269,"CREDIT");

	//rectangle(160,330,221,355);
	settextstyle(10,HORIZ_DIR,1);
	outtextxy(160,319,"EXIT");

	showmouseptr();//shows mouse pointer
	//detects mouse position and make decision according to choice made

	while(!kbhit())
	{
		getmousepos(&button,&mx,&my);
		if(button==1 && mx<=252 && mx>=160 && my<=155 && my>=130)
		{
		button = -1;
		hidemouseptr();
		cleardevice();
		//screen(Iscore,Ilife,Ilevel);
		prostart();	//calls starting of game to perform infinite loop
		}
		if(button==1 && mx<=326 && mx>=160 && my<=205 && my>=180)
		{
		button = -1;
		delay(100);
		hidemouseptr();
		highest();	//calls higest score saved in program
		getch();
		hidemouseptr();
		cleardevice();
		goto menu;
		}
		if(button==1 && mx>=160 && mx<=221 && my>=230 && my<=255)
		{
		button = -1;
		cleardevice();
		hidemouseptr();
		help();		//directs to help function
		getch();
		hidemouseptr();
		cleardevice();
		goto menu;
		}
		if(button==1 && mx>=160 && mx<=283 && my>=280 && my<=305)
		{
		button = -1;
		cleardevice();
		hidemouseptr();
		credit();      //gives information about programmers
		getch();
		hidemouseptr();
		cleardevice();
		goto menu;
		}
		if(button==1 && mx>=160 && mx<=221 && my>=330 && my<=355)
		{
		button = -1;
		hidemouseptr();
		cleardevice();
		delay(500);
		exit();		//exits from program
		}
	}

	//holds screen if any key is pressed and goes back to menu to position using goto

	//if(kbhit())
	getch();
	goto menu;

}
/**************************start*************************/
void prostart()
{
	long int Ilevel=1,Ilife=3,Iscore=0;
	//asks name of player
	cleardevice();
	printf("\n\n\n\n\n\n\t\t\tENTER YOU NAME:");
	gets(pl.name);
	clrscr();
	cleardevice();

	screen(Iscore,Ilife,Ilevel);
	pl.Cscore=0;

	//performs infinite loop

	while(1){
		body();		//goes to body parts of program where every action is controlled
	}
	//exit(0);
}

void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..\\bgi");
	initmouse();

	//main part of program where execution is started
	load();		//calls loading page
	mainmenu();	//calls menu page
}
