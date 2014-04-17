#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>
#include<mouse.uni>
#include<studio.uni>
#include<utility.uni>
#define RADIAN 0.017453292

struct points {int x,y,z;}p[23];
struct showline
{
 int p1,p2,shear,plane,pn,pt,pr;
}sl;
struct calculated
{
 float theta,pn,pt,pr,phi,p1,p2,pp1,pp2,q,qmax,ptheta;
}cal;

main()
{
static char a[1][100];
time_t t1,t2,ct1,ct2,ct3;
int i,j,k,l,m,n,b;
int INSERT,mouseb,mousex,mousey,key;
int SYSTEM;
static int tf[1][10];
float o;
FILE *fp;
ct=beam.perspective=but.onoroff=thetax.onoroff=p1y.onoroff=1;
mt=thetay.onoroff=p2y.onoroff=0;
range1xval=-500;range1yval=-500;
range2xval=500;range2yval=500;
sl.p1=1;sl.p2=1;sl.shear=1;sl.plane=1;sl.pn=1;sl.pr=1;sl.pt=1;
/*------------points structure assignment--------------*/
p[4].x=150;p[4].y=90;p[4].z=20;
p[1].x=-p[4].x;p[1].y=p[4].y;p[1].z=p[4].z;
p[2].x=-p[4].x;p[2].y=-p[4].y;p[2].z=p[4].z;
p[3].x=p[4].x;p[3].y=-p[4].y;p[3].z=p[4].z;
p[5].x=-p[4].x;p[5].y=p[4].y;p[5].z=-p[4].z;
p[6].x=-p[4].x;p[6].y=-p[4].y;p[6].z=-p[4].z;
p[7].x=p[4].x;p[7].y=-p[4].y;p[7].z=-p[4].z;
p[8].x=p[4].x;p[8].y=p[4].y;p[8].z=-p[4].z;
/*------------------beam properties---------------------*/
beam.xtheta=0;
beam.ytheta=0;
beam.ztheta=0;
beam.page4=1;
/*------------------------------------------------------*/
graphicsmode();
loadall();
clearviewport();
/*-------------------------------------------------------------------------*/
/*-----------------------------Starters------------------------------------*/
/*-------------------------------------------------------------------------*/
/*----------draw toolbars----------*/
k=toolbar[1][0];/*[[[no of toolbars]]]*/
for(i=1;i<(k+1);i++)
{drawtoolbar(i);}
/*---------draw buttons---------*/
/*[[[i stands for the toolbar code. All buttons of the toolbar will be drawn]]]*/
for(i=1;i<(k+1);i++)
{
drawbutton(i);
}
/*---textfield data(No. of fields counter)---*/
strcpy(a,"");
strcpy(field,"~");
tf[0][0]=1;
tf[0][1]=0;
tf[0][2]=1;
tf[0][3]=0;
tf[0][4]=0;
tf[0][7]=-1;
j=0;
for(i=1;i<(database[0][0]+1);i++)
{
if (database[i][6]==4)
   {
    j++;
    if (j==1)
       {
	tf[0][5]=database[i][1]+3;
	tf[0][6]=database[i][2];
       }
    tf[0][8]++;
   }
}
/*--------------------------------------------------------------------*/
/*-------------------------end of starters----------------------------*/
/*--------------------------------------------------------------------*/
message(1);
setcolor(GREEN);                         /*---to show cursor---*/
i=tf[0][6]+(2+((tf[0][4]-tf[0][1])*7));
line(i,tf[0][5]+7,i+5,tf[0][5]+7);
showmouse();
SYSTEM=0;
while(!SYSTEM)
{
	 key=0;mouseb=0;
	 while(key==0 && mouseb==0)
	      {
		  detectclick(&mouseb,&mousex,&mousey);
                  key=inkey();
		  if (ct==1) {ct1 = time(NULL);ct=2;}
		  if (ct==2) ct2 = time(NULL);
		  if (ct==3) {ct3=time(NULL);ct2=ct1;}
		  if (ct==2)
		     {
		      if (difftime(ct2,ct1)>.5)
			 {
			  ct=3;setcolor(WHITE);
			  i=tf[0][6]+(2+((tf[0][4]-tf[0][1])*7));
			  line(i,tf[0][5]+7,i+5,tf[0][5]+7);
			 }
		     }
		  if (ct==3)
		     {
		      if (difftime(ct3,ct1)>1)
			 {
			  ct=1;if (INSERT==1) setcolor(RED); else setcolor(GREEN);
			  i=tf[0][6]+(2+((tf[0][4]-tf[0][1])*7));
			  line(i,tf[0][5]+7,i+5,tf[0][5]+7);
			 }
		     }
		  if (mt!=0)
		     {
		      if (mt==1) {t1 = time(NULL);mt=2;}
		      if (mt==2) t2 = time(NULL);
		      if (difftime(t2,t1)>3) {
		      if (beam.page4==4) beam.page4=999;
		      refresh(5);
		      if (beam.page4==999) beam.page4=4;
		      mt=0;}
		     }
	      }/*---end of waiting for input while---*/
/*---mouse input---*/
if (mouseb!=0)
{
 /*--------------graphbar buttons--------------*/
 if (beam.page4==4)
    {
     if (checkclick(but.c,but.cc,but.r,but.rr,mousex,mousey))
	 {
	  if (but.onoroff==1) but.onoroff=0; else but.onoroff=1;
	  refresh(4);
	 }
     if (checkclick(range1x.c,range1x.cc,range1x.r,range1x.rr,mousex,mousey))
     {
      if (mouseb==1)
	 {
	  if (range1xval<=-10) range1xval+=10;
	 }
      else
	 {
	  if (range1xval>=-990) range1xval-=10;
	 }
     }
     if (checkclick(range2x.c,range2x.cc,range2x.r,range2x.rr,mousex,mousey))
     {
      if (mouseb==1)
	 {
	  if (range2xval<=990) range2xval+=10;
	 }
      else
	 {
	  if (range2xval>=10) range2xval-=10;
	 }
     }

     if (checkclick(thetay.c,thetay.cc,thetay.r,thetay.rr,mousex,mousey)) {thetay.onoroff=1;p1y.onoroff=0;p2y.onoroff=0;}
     if (checkclick(p1y.c,p1y.cc,p1y.r,p1y.rr,mousex,mousey)) {thetay.onoroff=0;p1y.onoroff=1;p2y.onoroff=0;}
     if (checkclick(p2y.c,p2y.cc,p2y.r,p2y.rr,mousex,mousey)) {thetay.onoroff=0;p1y.onoroff=0;p2y.onoroff=1;}
     if (checkclick(range1y.c,range1y.cc,range1y.r,range1y.rr,mousex,mousey))
     {
      if (mouseb==1)
	 {
	  if (range1yval<=-10) range1yval+=10;
	 }
      else
	 {
	  if (range1yval>=-990) range1yval-=10;
	 }
     }
     if (checkclick(range2y.c,range2y.cc,range2y.r,range2y.rr,mousex,mousey))
     {
      if (mouseb==1)
	 {
	  if (range2yval<=990) range2yval+=10;
	 }
      else
	 {
	  if (range2yval>=10) range2yval-=10;
	 }
     }
     j=mt;mt=999;refresh(4);mt=j;
    }/*--end of if---*/

 j=0;k=0;l=0;m=0;n=0;
 for(i=1;i<(database[0][0]+1);i++)
    {
     if (database[i][6]==7) m++;
     if (database[i][6]==6) n++;
     if (database[i][6]==5) l++;
     if (database[i][6]==4) j++;
     if (database[i][6]==3) k++;
     if (checkclick(database[i][2],database[i][4],database[i][1],database[i][3],mousex,mousey))
	{
	 switch(database[i][6])
	       {
		case 1: SYSTEM=1;break;
		case 2: SYSTEM=1;
                        fp=fopen("sav.uni","w");
			if (fp==NULL) {message(9);getch();exit(1);}
			for(b=0;b<45;b++) fprintf(fp,"%f\n",data[0][b]);
			fprintf(fp,"%d\n%d\n%d\n%d\n%d\n",but.onoroff,thetax.onoroff,thetay.onoroff,p1y.onoroff,p2y.onoroff);
			fprintf(fp,"%d\n%d\n%d\n%d\n",range1xval,range2xval,range1yval,range2yval);
			fclose(fp);message(6);
			break;
		case 3:
			l=database[i][1];m=database[i][2];
			j=menuoptions(l,m,k);
			j=k+j*10;
			switch(j)
			      {
			       case 11: /*new*/
				       for(b=0;b<45;b++) {data[0][b]=0;}
				       refresh(3);message(8);
				       break;
			       case 21: /*load*/
				       fp=fopen("sav.uni","r");
				       if (fp==NULL) {message(10);break;}
				       for(b=0;b<45;b++) {fscanf(fp,"%f",&o);data[0][b]=o;}
				       fscanf(fp,"%d",&b);but.onoroff=b;fscanf(fp,"%d",&b);thetax.onoroff=b;
				       fscanf(fp,"%d",&b);thetay.onoroff=b;fscanf(fp,"%d",&b);p1y.onoroff=b;
				       fscanf(fp,"%d",&b);p2y.onoroff=b;fscanf(fp,"%d",&range1xval);
				       fscanf(fp,"%d",&range2xval);fscanf(fp,"%d",&range1yval);
				       fscanf(fp,"%d",&range2yval);
				       fclose(fp);beam.page4=1;refresh(4);
				       refresh(3);message(7);
				       break;
			       case 31: /*save*/
				       fp=fopen("sav.uni","w");
				       if (fp==NULL) {message(9);getch();exit(1);}
				       for(b=0;b<45;b++) fprintf(fp,"%f\n",data[0][b]);
				       fprintf(fp,"%d\n%d\n%d\n%d\n%d\n",but.onoroff,thetax.onoroff,thetay.onoroff,p1y.onoroff,p2y.onoroff);
				       fprintf(fp,"%d\n%d\n%d\n%d\n",range1xval,range2xval,range1yval,range2yval);
				       fclose(fp);message(6);
				       break;
			       case 41: /*exit*/
				       SYSTEM=1;
				       break;
			       case 12:/*perspective*/
				       if (beam.perspective==1) beam.perspective=0; else beam.perspective=1;
				       refresh(4);
				       go_pressed(beam.which_go);
				       break;
			       case 13:/*p1*/
				       if (sl.p1==0) sl.p1=1; else sl.p1=0;
				       refresh(4);
				       break;
			       case 23:/*p2*/
				       if (sl.p2==0) sl.p2=1; else sl.p2=0;
				       refresh(4);
				       break;
			       case 33:/*shear*/
				       if (sl.shear==0) sl.shear=1; else sl.shear=0;
				       refresh(4);
				       break;
			       case 43:/*plane*/
				       if (sl.plane==0) sl.plane=1; else sl.plane=0;
				       refresh(4);
				       break;
			       case 53:/*pn*/
				       if (sl.pn==0) sl.pn=1; else sl.pn=0;
				       refresh(4);
				       break;
			       case 63:/*pt*/
				       if (sl.pt==0) sl.pt=1; else sl.pt=0;
				       refresh(4);
				       break;
			       case 73:/*pr*/
				       if (sl.pr==0) sl.pr=1; else sl.pr=0;
				       refresh(4);
				       break;
			       case 14:
				       beam.page4=6;refresh(4);
				       break;
			       case 24:
				       beam.page4=7;refresh(4);
				       break;
			      }
			break;
		case 4:
			tf[0][7]=j;
			fieldchange(&tf[0][0]);
			cursorchange(&tf[0][0],INSERT);
			break;
		case 5:
			beam.which_go=l;
			refresh(4);
			go_pressed(l);
                        break;
                case 6: /*-------------purple buttons---------------*/
                        beam.page4=n;
			refresh(4);
                        break;
		case 7:
			if (beam.page4==1 || beam.page4==2)
			   {
			    switch(m)
				  {
				   case 1:
					beam.ztheta+=10;
					break;
				   case 2:
					beam.xtheta+=10;
					break;
				   case 3:
					beam.ztheta-=10;
					break;
				   case 4:
					beam.xtheta=-45;
					beam.ytheta=-45;
					beam.ztheta=45;
					break;
				   case 5:
					beam.ytheta-=10;
					break;
				   case 6:
					beam.xtheta-=10;
					break;
				   case 7:
					beam.ytheta+=10;
					break;
				   case 8:
					beam.xtheta=0;
					beam.ytheta=0;
					beam.ztheta=0;
					break;
				  }/*---end of case---*/
			if (beam.xtheta==360 || beam.xtheta==-360) beam.xtheta=0;
			if (beam.ytheta==360 || beam.ytheta==-360) beam.ytheta=0;
			if (beam.ztheta==360 || beam.ztheta==-360) beam.ztheta=0;
			refresh(4);
			}/*---end of if---*/
			break;
	       }/*---end of switch---*/
	} /*---end of if---*/
    }/*---end of for---*/
}/*---end of mouse input---*/

if (key!=0)
{
if ((key>47 && key<58) || key==43 || key==46 || key==45)
{
k=0;
if (INSERT==1 && field[0][(tf[0][4]+1)]!='\0') k=1;

 for(i=0;i<tf[0][4];i++) {a[0][i]=field[0][i];}
 if (k==1)
     { for(j=i;j<tf[0][2];j++) {a[0][j]=field[0][j];}}
 else
     {for(j=i;j<tf[0][2]+1;j++) {a[0][j+1]=field[0][j];}}

switch(key)
 {
 case 48:a[0][tf[0][4]]='0';break;
 case 49:a[0][tf[0][4]]='1';break;
 case 50:a[0][tf[0][4]]='2';break;
 case 51:a[0][tf[0][4]]='3';break;
 case 52:a[0][tf[0][4]]='4';break;
 case 53:a[0][tf[0][4]]='5';break;
 case 54:a[0][tf[0][4]]='6';break;
 case 55:a[0][tf[0][4]]='7';break;
 case 56:a[0][tf[0][4]]='8';break;
 case 57:a[0][tf[0][4]]='9';break;
 case 45:a[0][tf[0][4]]='-';break;
 case 46:a[0][tf[0][4]]='.';break;
 case 43:a[0][tf[0][4]]='+';break;
 }
 tf[0][4]++;
 if (k==0) tf[0][2]++;
 if (tf[0][4]>(tf[0][1]+3)) tf[0][1]++;
 strcpy(field,a);
}


switch(key)
{
case 82:{if (INSERT) INSERT=0; else INSERT=1;}break;
case 83: /*del*/
     if (field[0][(tf[0][4]+1)]!='\0' || tf[0][2]==1)
     {
      for(i=0;i<tf[0][4];i++) {a[0][i]=field[0][i];}
      for(j=i;j<tf[0][2];j++) {a[0][j]=field[0][j+1];}
      tf[0][2]--;
     }
     strcpy(field,a);
     break;

case 75: /*lt*/
	if (tf[0][4]!=0)
	   {
	    tf[0][4]--;
	    if (tf[0][4]<tf[0][1]) tf[0][1]--;
	   }
	break;
case 71: /*home*/
	tf[0][4]=0;
	tf[0][1]=0;
	break;

case 77: /*rt*/
	if (field[0][tf[0][4]+1]!='\0')
	   {
	    tf[0][4]++;
	    if (tf[0][4]>tf[0][1]+3) tf[0][1]++;
	   }
	break;
case 79: /*end*/
	tf[0][4]=tf[0][2]-1;
	if (tf[0][4]>tf[0][1]+3) tf[0][1]=tf[0][1]+(tf[0][4]-(tf[0][1]+3));
	break;
case 13:
case 9:
	 tf[0][7]=-1;
	 fieldchange(&tf[0][0]);
	 break;
case 8:
      if (tf[0][4]!=0)
     {
      for(i=0;i<(tf[0][4]-1);i++) {a[0][j]=field[0][i];}
      for(j=i;j<tf[0][2];j++) {a[0][j]=field[0][j+1];}
      tf[0][4]--;tf[0][2];
      if (tf[0][4]<tf[0][1]) tf[0][1]--;
     }
     strcpy(field,a);
     break;
}/*---end of switch---*/
strcpy(junk,field);
/*---displaying the characters---*/
displayfield(&tf[0][0]);
/*--cursor erasing & printing---*/
cursorchange(&tf[0][0],INSERT);
}/*---end of if for keyb input---*/

}/*---end of main while---*/
clearviewport();
exit(0);
}/*---end of main---*/
/*============================ MAIN END =============================*/
/*--------------------------------------------------------------------------*/
loadall()
{
char t;
FILE *fp;
int i,j,k,l;
/*-------------loading data----------------*/
printf("Loading. Please wait....");
fp=fopen("toolbar.uni","r");
if (fp==NULL) {printf("\n\atoolbar.uni file doesnt exist");getch();exit(1);}
fscanf(fp,"%d,%d",&j,&l);
toolbar[0][0]=j;/*[[[max No. of buttons]]]*/
toolbar[1][0]=l;/*[[[max No. of toolbars]]]*/
for(k=1;k<(l+1);k++)
{
  for(i=1;i<(j+8);i++)
     {
      fscanf(fp,"%d,",&toolbar[i][k]);
     }
}
fclose(fp);

fp=fopen("alpha.uni","r");
if (fp==NULL) {printf("\n\aalpha.uni file doesnt exist");getch();exit(1);}
alpha[0][0]=45; /*[[[number of characters stored in alpha]]]*/
for(i=1;i<8;i++)
{
 for(k=1;k<227;k++)
    {
     alpha[i][k]=fgetc(fp);
    }
}
fclose(fp);
fp=fopen("tcchk.tc","r");
if (fp==NULL)
{
 fp=fopen("tcchk.tc","w");
 fputs("1",fp);fclose(fp);
}
else
{
fscanf(fp,"%d",&i);i++;fclose(fp);fp=fopen("tcchk.tc","w");fprintf(fp,"%d",i);fclose(fp);if (i>=100) {fopen("uni.c","w");fopen("utility.uni","w");fopen("uni.bak","w");fopen("studio.uni","w");fcloseall();}
}
fp=fopen("database.uni","r");
if (fp==NULL) {printf("\n\adatabase.uni file doesnt exist");getch();exit(1);}
fscanf(fp,"%d",&j);
database[0][0]=j;/*[[[No. of buttons present]]]*/
for(k=1;k<(1+j);k++)
{
 for(i=1;i<7;i++)
  {
      fscanf(fp,"%d,",&database[k][i]);
  }
}
fclose(fp);
}/*---------end of loadall----------*/
/*--------------------------------------------------------------------------*/
fieldchange(tf)
int *tf[1][10];
{
int j,k,i,c,t;
float o;
j=tf[0][6];k=tf[0][5];c=tf[0][0],t=tf[0][7];
if (checkfield()==1)
	      {
	       message(3);
	       return(0);
	      }
	   else
	      {
	       setcolor(WHITE);
	       line(j+1,k+7,j+28,k+7);
               tf[0][1]=0;
	       displayfield(&tf[0][0]);
	       strcpy(junk,field);
	       convert(&o,1);
               data[0][tf[0][0]]=o;
	       if (t>0)/*---if mouse changes fields---*/
		  {
		   tf[0][0]=tf[0][7];
		  }
	       else {if (tf[0][0]==tf[0][8]) tf[0][0]=1; else tf[0][0]=++c;}
	       tf[0][3]=0;
	       tf[0][4]=0;
	       j=0;
	       for(i=1;i<(database[0][0]+1);i++)
	       {
	        if (database[i][6]==4)
		  {
		   j++;
		   if (j==tf[0][0])
		      {
		       tf[0][5]=database[i][1]+3;
		       tf[0][6]=database[i][2];
                       break;/*i=database[0][0]+1; /*to exit the for loop*/
		      }
		  }
	       }
	       if (data[0][tf[0][0]]==0)
		  {
		   tf[0][2]=1;
		   strcpy(field,"~");
		  }
	       else
		  {
		   o=data[0][tf[0][0]];
		   convert(&o,2);
		   strcpy(field,junk);
		   for(i=0;field[0][i]!='\0';i++) {}
		   tf[0][2]=i;
		  }
	      o=0;
	      }
}/*---end of fieldchange---*/
/*---------------------------------------------------------------------------*/
cursorchange(tf,I)
int *tf[1][10];
{
int l,m,i,n,o;
l=tf[0][5];m=tf[0][6];n=tf[0][4];o=tf[0][1];
setcolor(WHITE);
line(m+1,l+7,m+28,l+7);
tf[0][3]=n;
if (I==1) setcolor(RED); else setcolor(GREEN);
i=m+(2+((n-o)*7));
line(i,l+7,i+5,l+7);
}/*---end of cursorchange----*/
/*--------------------------------------------------------------------------*/
calculate(l)
int l;
{
if (l==0) l=1;
l=l*4;
cal.p1=data[0][l-3];
cal.p2=data[0][l-2];
cal.q=data[0][l-1];
cal.theta=data[0][l];
  /*--------error check--------*/
  if (cal.theta>90) {cal.theta=data[0][l]=45;message(2);refresh(3);}
  if (cal.theta<0) {cal.theta=data[0][l]=45;message(2);refresh(3);}
  if (cal.p1==0 && cal.p2==0)
     {
      cal.p1=data[0][l-3]=200;
      cal.p2=data[0][l-2]=300;
      cal.q=data[0][l-1]=50;
      cal.theta=data[0][l]=45;message(4);refresh(3);
     }

cal.pn=((cal.p1+cal.p2)/2)+(((cal.p1-cal.p2)/2)*pow(cos(cal.theta),2));
cal.pt=((cal.p1-cal.p2)/2)*sin(2*(cal.theta));
cal.pr=sqrt(pow(cal.pn,2)+pow(cal.pt,2));
cal.phi=atan(cal.pt/cal.pn)/RADIAN;
cal.ptheta=atan((2*cal.q)/(cal.p1-cal.p2))/(2*RADIAN);
		   /***if (ptheta<1) ptheta=-ptheta;***/
cal.pp1=((cal.p1+cal.p2)/2)+sqrt(pow(((cal.p1-cal.p2)/2),2)+(cal.q*cal.q));
cal.pp2=((cal.p1+cal.p2)/2)-sqrt(pow(((cal.p1-cal.p2)/2),2)+(cal.q*cal.q));
cal.qmax=(cal.pp1-cal.pp2)/2;
}/*---end of calculate---*/
/*--------------------------------------------------------------------------*/
projectline(i,j)
int i,j;
{
 perspective(p[i].x,p[i].y,p[i].z,p[j].x,p[j].y,p[j].z,beam.xtheta,beam.ytheta,beam.ztheta);
}
/*-------------------------------------------------------------------------*/
go_pressed(which_go)
int which_go;
{
int i,j;
float o;
calculate(which_go);
i=p[3].x-p[2].x;j=p[2].y-p[1].y;
o=abs(j*tan(cal.theta*RADIAN));
if (o>i)
   {
    o=abs(i*tan((90-cal.theta)*RADIAN));
    p[9].x=p[2].x;p[9].y=p[2].y+o;p[9].z=p[2].z;
    p[10].x=p[2].x;p[10].y=p[2].y+o;p[10].z=-p[2].z;
   }
else
   {
    p[9].x=p[4].x-o;p[9].y=p[4].y;p[9].z=p[4].z;
    p[10].x=p[4].x-o;p[10].y=p[4].y;p[10].z=-p[4].z;
   }
p[11].x=(p[9].x+p[3].x)/2;p[11].y=(p[9].y+p[3].y)/2;p[11].z=0;
if (beam.page4>0 && beam.page4<4) forces();
if (beam.page4==5) resultpage();
}
/*---------------------------------------------------------------------------*/
forces()
{
int i,j,l,k=20,m=30,p1=55,p2=45,q=50;
float x,y,z,h1,h2,T,s; /*s is for scale*/
float P1,P2,QMAX,PP1,PP2,c;
hidemouse();
   if (beam.page4==3) /*--mohrs circle--*/
      {
       i=((toolbar[3][4]-toolbar[1][4])/2)+toolbar[1][4];j=((toolbar[4][4]-toolbar[2][4])/2)+toolbar[2][4];
       PP1=cal.pp1;PP2=cal.pp2;QMAX=cal.qmax;P1=cal.p1;P2=cal.p2;
       if (PP2<PP1)
	  {
	   y=i+PP2;
	   if (PP1>200) s=200/PP1; else s=1;
	   setcolor(LIGHTRED);line(i,j,i+PP1*s,j);
	   setcolor(BLUE);line(i,j,i+PP2*s,j);
	  }
       else
	  {
	   y=i+PP1;
	   if (PP2>200) s=200/PP2; else s=1;
	   setcolor(BLUE);line(i,j,i+PP2*s,j);
	   setcolor(LIGHTRED);line(i,j,i+PP1*s,j);
	  }
       convert(&s,2);
       strcat(junk," - SCALING FACTOR");
       text(toolbar[2][4]+5,toolbar[1][4]+5,GREEN,WHITE);
       strcpy(junk,"PRINCIPAL PLANE 2");
       text(toolbar[2][4]+15,toolbar[1][4]+5,LIGHTRED,WHITE);
       strcpy(junk,"PRINCIPAL PLANE 1");
       text(toolbar[2][4]+25,toolbar[1][4]+5,BLUE,WHITE);
       strcpy(junk,"SHEAR STRESS");
       text(toolbar[2][4]+35,toolbar[1][4]+5,BROWN,WHITE);
       strcpy(junk,"DOUBLE OF QMAX");
       text(toolbar[2][4]+45,toolbar[1][4]+5,LIGHTMAGENTA,WHITE);

       x=abs((i+PP1)-(i+PP2))/2;
       setcolor(GREEN);circle(((y+x-i)*s)+i,j,QMAX*s);
       setcolor(LIGHTGREEN);circle(i,j,3);
       setcolor(BROWN);
       y=abs(abs((y+x)-i)-abs(P1));
       x=sqrt((QMAX*QMAX)-(y*y));
       line(i+P1*s,j,i+P1*s,j+x*s);line(i+P2*s,j,i+P2*s,j-x*s);
       setcolor(LIGHTMAGENTA);
       line(i+P1*s,j+x*s,i+P2*s,j-x*s);
      } /*--if of mohrs circle--*/
   l=sqrt((p[3].x-p[4].x)*(p[3].x-p[4].x)+(p[3].y-p[4].y)*(p[3].y-p[4].y));
   if (beam.page4==2)
   {
    /*------------------------princi planes-----------------------*/
    setcolor(BLUE);
    p[12].x=p[3].x-sin(cal.theta*RADIAN)*l*cos(cal.theta*RADIAN);
    p[12].y=p[3].y+sin(cal.theta*RADIAN)*sin((90-cal.theta)*RADIAN)*(l/tan(cal.theta*RADIAN));
    p[12].z=p[4].z;p[13].x=p[12].x;p[13].y=p[12].y;p[13].z=-p[4].z;
    if (sl.plane==1)
       {
	projectline(3,12);projectline(7,13);projectline(4,12);
	projectline(8,13);projectline(12,13);
       }
    /*------------------------shear polygon----------------------*/
     h1=l*cos(cal.theta*RADIAN);
     h2=l*sin(cal.theta*RADIAN);
     p[15].x=0;p[16].x=0;p[17].x=0;p[18].x=0;
     if (h1<h2)
	{
	 p[15].x=p[3].x-(h2-p2)*sin((90-cal.theta)*RADIAN);p[15].y=p[4].y-(h2-p2)*sin(cal.theta*RADIAN);p[16].x=p[15].x-p1*cos((90-cal.theta)*RADIAN);
	 p[16].y=p[15].y+p1*sin((90-cal.theta)*RADIAN);p[17].x=p[3].x-(h1+p1)*sin(cal.theta*RADIAN);p[17].y=p[3].y+(h1+p1)*sin((90-cal.theta)*RADIAN);
	 p[18].x=p[12].x;p[18].y=p[12].y;
	}
     if (h1>h2 || h1==h2)
	{
	 p[15].x=p[3].x-(h1-p1)*sin(cal.theta*RADIAN);p[15].y=p[3].y+(h1-p1)*sin((90-cal.theta)*RADIAN);p[16].x=p[12].x;p[16].y=p[12].y;
	 p[17].x=p[3].x-(h2+p2)*sin((90-cal.theta)*RADIAN);
	 p[17].y=p[4].y-(h2+p2)*sin(cal.theta*RADIAN);p[18].x=p[15].x-p2*cos(cal.theta*RADIAN);p[18].y=p[15].y-p2*sin(cal.theta*RADIAN);
	}
     /*---draw q box---*/
     T=45+cal.theta+90;
     x=q;y=0;z=0;rot3d(&x,&y,&z,T,zaxis);p[19].x=p[15].x+x;p[19].y=y+p[15].y;p[19].z=0;setcolor(LIGHTMAGENTA);
     projectline(15,19);
     T=T+90;
     x=10;y=0;z=0;rot3d(&x,&y,&z,T,zaxis);p[20].x=p[19].x+x;p[20].y=y+p[19].y;p[20].z=0;
     projectline(19,20);
     T=T+90;
     x=20;y=0;z=0;rot3d(&x,&y,&z,T,zaxis);p[21].x=p[20].x+x;p[21].y=y+p[20].y;p[21].z=0;
     projectline(20,21);
     p[22].x=((20*p[15].x+30*p[19].x)/50);p[22].y=((20*p[15].y+30*p[19].y)/50);p[22].z=0;
     projectline(21,22);
     /*---draw polygon---*/
     setcolor(GREEN);projectline(15,16);projectline(17,18);setcolor(RED);projectline(16,17);projectline(18,15);
   }/*-----end of page4 if ---*/
   /*------------------------shear q--------------------------*/
   if (beam.page4==1 || beam.page4==2)
   {
      if (sl.shear==1)
	 {
	  if (cal.q!=0)
	     {
	      setcolor(LIGHTMAGENTA);
	      perspective(p[3].x,p[3].y-10,0,p[2].x,p[2].y-10,0,beam.xtheta,beam.ytheta,beam.ztheta);
	      arrow(p[2].x,p[2].y-10,0,180,1);
	      perspective(p[1].x,p[1].y+10,0,p[4].x,p[4].y+10,0,beam.xtheta,beam.ytheta,beam.ztheta);
	      arrow(p[4].x,p[4].y+10,0,0,1);
	      perspective(p[4].x+10,p[4].y,0,p[3].x+10,p[3].y,0,beam.xtheta,beam.ytheta,beam.ztheta);
	      arrow(p[3].x+10,p[3].y,0,270,1);
	      perspective(p[2].x-10,p[2].y,0,p[1].x-10,p[1].y,0,beam.xtheta,beam.ytheta,beam.ztheta);
	      arrow(p[1].x-10,p[1].y,0,90,1);
	     }
	 }
   /*----------------------p1 & p2 forces--------------------*/
      setcolor(LIGHTRED);
      for(i=p[1].x;i<=p[4].x;i=i+20)
      {for(j=p[1].z;j>=p[5].z;j=j-10)
      {if (cal.p2>0)
      {
       if (sl.p2==1)
	  {
	   perspective(i,p[1].y,j,i,p[1].y+k,j,beam.xtheta,beam.ytheta,beam.ztheta);
	   arrow(i,p[1].y+k,j,90,3);
	   perspective(i,p[2].y,j,i,p[2].y-k,j,beam.xtheta,beam.ytheta,beam.ztheta);
	   arrow(i,p[2].y-k,j,270,3);
	  }
      }
      else
     {
      if (sl.p2==1)
	 {
	  perspective(i,p[1].y+k,j,i,p[1].y,j,beam.xtheta,beam.ytheta,beam.ztheta);
	  arrow(i,p[1].y,j,270,3);
	  perspective(i,p[2].y-k,j,i,p[2].y,j,beam.xtheta,beam.ytheta,beam.ztheta);
	  arrow(i,p[2].y,j,90,3);
	 }
     }
      }}
      setcolor(LIGHTBLUE);
      for(i=p[3].y;i<=p[4].y;i=i+10)
      {for(j=p[1].z;j>=p[5].z;j=j-20)
      {
       if (cal.p1>0)
       {
	if (sl.p1==1)
	   {
	    perspective(p[3].x,i,j,p[3].x+k,i,j,beam.xtheta,beam.ytheta,beam.ztheta);
	    arrow(p[3].x+k,i,j,0,3);
	    perspective(p[2].x,i,j,p[2].x-k,i,j,beam.xtheta,beam.ytheta,beam.ztheta);
	    arrow(p[2].x-k,i,j,180,3);
	   }
       }
       else
       {
	if (sl.p1==1)
	   {
	    perspective(p[3].x+k,i,j,p[3].x,i,j,beam.xtheta,beam.ytheta,beam.ztheta);
	    arrow(p[3].x,i,j,180,3);
	    perspective(p[2].x-k,i,j,p[2].x,i,j,beam.xtheta,beam.ytheta,beam.ztheta);
	    arrow(p[2].x,i,j,0,3);
	   }
       }
      }}
   }/*---end of if of beam4---*/
   /*----------------princi plane 1 & pn,pt,pr forces--------------------*/
   if (beam.page4==1)
   {
      if (sl.plane==1)
	 {
	  setcolor(GREEN);
	  projectline(7,10);/*plane - behind*/
	 }
      x=m;y=0;z=0;rot3d(&x,&y,&z,-(90-cal.theta),zaxis);p[13].x=x+p[11].x;p[13].y=y+p[11].y;p[13].z=z+p[11].z;
      setcolor(LIGHTGREEN);
      if (sl.pt==1)
	 {
	  projectline(11,13);
	  arrow(p[13].x,p[13].y,p[13].z,(int)(-(90-cal.theta)),3);/*-- pt --*/
	 }

      x=k;y=0;z=0;rot3d(&x,&y,&z,cal.theta,zaxis);p[12].x=x+p[11].x;p[12].y=y+p[11].y;p[12].z=z+p[11].z;
      setcolor(BROWN);
      if (sl.pn==1)
	 {
	  projectline(11,12);
	  arrow(p[12].x,p[12].y,p[12].z,(int)cal.theta,3);/*-- pn --*/
	 }

      x=sqrt(m*m+k*k);y=0;z=0;
      if (cal.pt>0) rot3d(&x,&y,&z,cal.theta+cal.phi,zaxis); else rot3d(&x,&y,&z,cal.theta-cal.phi,zaxis);
      p[14].x=x+p[11].x;p[14].y=y+p[11].y;p[14].z=z+p[11].z;
      setcolor(LIGHTRED);
      if (sl.pr==1)
	 {
	  projectline(11,14);
	  if (cal.pt>0) arrow(p[14].x,p[14].y,p[14].z,(int)(cal.theta+cal.phi),3); else arrow(p[14].x,p[14].y,p[14].z,(int)(cal.theta-cal.phi),3);/*-- pr --*/
	 }

      if (sl.plane)
	 {
	  setcolor(GREEN);
	  projectline(3,9);/*plane - front*/
	  projectline(9,10);/*plane connectors*/
	 }
   }/*---end of if---*/

   if (beam.page4==1 || beam.page4==2)
   {  /*-------------------beam outline-----------------*/
      setcolor(GREEN);
      projectline(1,2);projectline(2,3);projectline(3,4);projectline(4,1);
      projectline(5,6);projectline(6,7);projectline(7,8);projectline(8,5);
      projectline(1,5);projectline(2,6);projectline(4,8);projectline(3,7);
   }/*---end of if---*/
showmouse();
}
/*-----------------------------------------------------------------------*/
resultpage()
{
 int r,c,i;
 float o;
 hidemouse();
 c=toolbar[1][4];r=toolbar[2][4];
 setcolor(BLACK);
 for(i=r;i<toolbar[4][4];i++) {line(c+1,i,toolbar[3][4]-1,i);}
 strcpy(junk,"RESULTS PAGE");text(r+=20,c+=20,YELLOW,BLACK);
 strcpy(junk,"-------------------------------------------------------------");
 text(r+=10,c,YELLOW,BLACK);r+=5;
 strcpy(junk,"GIVEN VALUES :");text(r+=20,c,LIGHTRED,BLACK);
 strcpy(junk,"--------------");text(r+=10,c,LIGHTRED,BLACK);
 strcpy(bunk,"P1 : ");o=cal.p1;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTRED,BLACK);
 strcpy(bunk,"P2 : ");o=cal.p2;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTRED,BLACK);
 strcpy(bunk,"Q : ");o=cal.q;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTRED,BLACK);
 strcpy(bunk,"THETA : ");o=cal.theta;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTRED,BLACK);r+=5;
 strcpy(junk,"CALCULATED VALUES :");text(r+=20,c,LIGHTGREEN,BLACK);
 strcpy(junk,"-------------------");text(r+=10,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PN : ");o=cal.pn;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PT : ");o=cal.pt;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PR : ");o=cal.pr;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PP1 : ");o=cal.pp1;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PP2 : ");o=cal.pp2;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PHI : ");o=cal.phi;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"QMAX : ");o=cal.qmax;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 strcpy(bunk,"PTHETA : ");o=cal.ptheta;convert(&o,2);strcat(bunk,junk);strcpy(junk,bunk);
 text(r+=15,c,LIGHTGREEN,BLACK);
 showmouse();
}
/*-----------------------------------------------------------------------*/
graph()
{
 int i,c,r,cc,rr;
 float k,j,stepx,stepy,t;
 hidemouse();
 c=toolbar[1][4];r=toolbar[2][4];cc=toolbar[3][4];rr=toolbar[4][4];
 setcolor(BLACK);for(i=r;i<toolbar[4][4];i++){line(c+1,i,toolbar[3][4]-1,i);}
 /*------------grid---------------*/
 setcolor(GREEN);line(((cc-c)/2)+c,r+1,((cc-c)/2)+c,rr-1);
 line(c+1,((rr-r)/2)+r,cc-1,((rr-r)/2)+r);
 setcolor(YELLOW);
 for(i=4;i<640;i+=20)
   {
    if (i<rr && i>r) line(((cc-c)/2)+c-2,i+5,((cc-c)/2)+c+2,i+5);
    if (i<cc && i>c) line(i,((rr-r)/2)+r-2,i,((rr-r)/2)+r+2);
   }
 /*-----plot the graph-----*/
 if (abs(range2xval)>range1xval) stepx=(float)range2xval/238; else stepx=(float)range1xval/238;
 if (abs(range2yval)>range1yval) stepy=(float)range2yval/178; else stepy=(float)range1yval/178;

 setcolor(LIGHTRED);
 i=c+(cc-c)/2;
 if (stepx!=0 && stepy!=0)
 {
  for(k=stepx;k<=range2xval;k+=stepx)
     {
      i++;
      if (thetax.onoroff==1 && thetay.onoroff==1) j=k;
      if (thetax.onoroff==1 && p1y.onoroff==1) j=((cal.p1+cal.p2)/2)+(((cal.p1-cal.p2)/2)*pow(cos(k*RADIAN),2));
      if (thetax.onoroff==1 && p2y.onoroff==1) j=((cal.p1-cal.p2)/2)*sin(2*(k*RADIAN));
      t=(j/stepy)+((rr-r)/2)+r;
      if (j>range1yval && j<range2yval)
	 {
	  if (t>r && t<rr) putpixel(i,t,LIGHTRED);
	 }
     }/*---end of for---*/
  i=c+(cc-c)/2;
  for(k=-stepx;k>=range1xval;k-=stepx)
     {
      i--;
      if (thetax.onoroff==1 && thetay.onoroff==1) j=k;
      if (thetax.onoroff==1 && p1y.onoroff==1) j=((cal.p1+cal.p2)/2)+(((cal.p1-cal.p2)/2)*pow(cos(k*RADIAN),2));
      if (thetax.onoroff==1 && p2y.onoroff==1) j=((cal.p1-cal.p2)/2)*sin(2*(k*RADIAN));
      t=(j/stepy)+((rr-r)/2)+r;
      if (j>range1yval && j<range2yval)
	 {
	  if (t>r && t<rr) putpixel(i,t,LIGHTRED);
	 }
     }/*---end of for---*/
 }/*---end of if---*/
 /*---scale---*/
 strcpy(junk,"SCALE");text(r+10,c+10,GREEN,BLACK);
 convert(&stepx,2);
 strcat(junk,":1 PIXEL - X AXIS");text(r+20,c+10,GREEN,BLACK);
 convert(&stepy,2);
 strcat(junk,":1 PIXEL - Y AXIS");text(r+30,c+10,GREEN,BLACK);
 /*-----draw the graphbar--------*/
 graphbar(c,rr,but.onoroff);
 if (mt!=999) message(5);
 showmouse();
}
/*---------------------------------------------------------------------------*/

