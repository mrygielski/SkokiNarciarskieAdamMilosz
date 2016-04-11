#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>


#include "..\files.h"
#include "..\ggate.h"
#include "..\tga.h"
#include "..\cameraGG.h"

CCamera g_Camera;
float x01f[11001];
float teren[4000][1000];

struct Tslup
{
	int X;
	float H;
	bool alive;
};

struct Tmapa
{
	float punkt;
	float skocznia[1000];
    float teren[10000];
    float k_point,r_point;
	int dl_skoczni;
    int dl_terenu;
	float start;
    float K,K2,K3,K4,K5,K6,K35,K53;
	Tslup slupy[11];
};

struct XYsnow
{
	float x;
	float y;
	float z;
	float speed;
};

struct XYdym
{
	float x;
	float y;
	float z;
	bool is;
	float color;
};


struct XYTree
{
	float x;
	float y;
	float z;
	int wys;
};

struct XYKibic
{
	float x;
	float y;
	float z;
	int nr;
};


Tmapa mapa;
int length;
int i,j;
int texture[50];
int textureL[50];
TextureImage textureT[50];
TextureImage fonttexture,fonttexture2;
float ftemp,ftemp2,ftemp3,ftemp4,kolor,low;
int itemp,itemp2,itemp3,itemp4;
int fps;

float mapZ,mapY=-15,mapX=-30,mapX2,mapY2,mapZ2;
float RotY=-90,RotZ,RotX;
float klatka;

bool doing=false;
///////////////////////////////

float xpos=2,ypos,xpos2,ypos2,ypos3,ypos4,ypos5,predkosc,lot=0.0f,wzbicie=0,spadanie=0;
bool wybicie=false,lotend=false,ladowanie=false,crash=false,lad=false;
float wiatr=3.0f,kat=0;
int laduje=0,maxlad,midlad,crasher;
char* strtemp;
float wysokosc,landing=-1.0f,prog,odleglosc;

///////////////////////////////
const int ilesniegu=3000;

XYsnow snow[ilesniegu];
///////////////////////////////
int myszY,pozycjaY=1;
int k=16;
bool lewy=false,prawy=false;

float camX,camY,camZ;

// drzewa
const int iledrzew=100;
XYTree tree[iledrzew];

// kibice
const int ilekibicow=60;
XYKibic kibic[ilekibicow];


float DETALE[3];
int wielkosc_sky;

GLUquadricObj *sky;
float sky_rot;

float punkty[6],pkt[6],zalicz[6],
      iksy[6]={0,-2.05f,-1.15f,-0.25f,0.65f,1.55f};
bool czyshow[6]={0,0,0,0,0,0};
int wsk[6]={0,1,2,3,4,5},lot_poz,sortok=0;
bool notyok=false;

char* imie="Sfen Sranavald";
float punkty_all;


int ile_dymu=100;
XYdym dym[101];

int speed_min;
int nrcienia=12;


#include "ludek.h"
#include "rysowanie.h"
#include "init.h"

int kamera=0;


void Dodaj_dymek(float x, float y, float z)
{
	for (i=1;i<=ile_dymu;i++)
	{
		if (dym[i].is==false)
		{
			dym[i].x=x;
			dym[i].y=y;
			dym[i].z=z;
			dym[i].is=true;
			dym[i].color=0.0f; 
			return;
		}
	}
}

void Rysuj_Snieg(int nr)
{
/*	glPolygonMode(GL_BACK,GL_FILL);
	glPolygonMode(GL_FRONT,GL_FILL);
	BarT(snow[nr].x+0.05f,snow[nr].y,snow[nr].z,
		 snow[nr].x+0.05f,snow[nr].y+0.05f,
		 snow[nr].z,snow[nr].x,snow[nr].y+0.05f,
		 snow[nr].z,snow[nr].x,snow[nr].y,snow[nr].z,255,255,255,255,textureT[14].texID);
	BarT(snow[nr].x+0.025f,snow[nr].y,snow[nr].z+0.025f,
		 snow[nr].x+0.025f,snow[nr].y+0.05f,snow[nr].z+0.025f,
		 snow[nr].x+0.025f,snow[nr].y+0.05f,snow[nr].z-0.025f,
		 snow[nr].x+0.025f,snow[nr].y,snow[nr].z-0.025f,255,255,255,255,textureT[14].texID);*/
	glPolygonMode(GL_BACK,GL_FILL);
	glPolygonMode(GL_FRONT,GL_FILL);
	BarT(snow[nr].x+0.5f,snow[nr].y,snow[nr].z,
		 snow[nr].x+0.5f,snow[nr].y+0.5f,
		 snow[nr].z,snow[nr].x,snow[nr].y+0.5f,
		 snow[nr].z,snow[nr].x,snow[nr].y,snow[nr].z,255,255,255,255,textureT[14].texID);
	BarT(snow[nr].x+0.25f,snow[nr].y,snow[nr].z+0.025f,
		 snow[nr].x+0.25f,snow[nr].y+0.5f,snow[nr].z+0.25f,
		 snow[nr].x+0.25f,snow[nr].y+0.5f,snow[nr].z-0.25f,
		 snow[nr].x+0.25f,snow[nr].y,snow[nr].z-0.025f,255,255,255,255,textureT[14].texID);
}

void Draw_Snow()
{
	for (i=0; i<ilesniegu; i++)
	{
		Rysuj_Snieg(i);
		snow[i].y=snow[i].y-snow[i].speed;
		if (snow[i].y<=-72)
		{
			snow[i].y=50;
		}
	}
}

void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	g_Camera.Look();
	
    if (xpos2>0 && xpos2<mapa.dl_skoczni) ypos2=mapa.skocznia[(int)xpos2-2]+0.95f-lot;
	if (xpos2>=mapa.dl_skoczni && xpos2<mapa.dl_terenu-1) ypos2=mapa.teren[(int)xpos2+4]+3.04f-lot;
    ypos4=ypos2+(ypos-ypos2);

    // Rysowanie œwiata

	Rysuj_Stadion();
	RysujKibicow();
	Rysuj_Skocznie(mapa);	
	Rysuj_Domek(mapa);
    Rysuj_Teren(mapa);
	Draw_Snow();
    
    Rysuj_Linie(mapa);
//	
	if (!ladowanie && xpos2>mapa.dl_skoczni+6) Rysuj_cien_gracza(mapa);

	Rysuj_reklamy();

	Rysuj_dym(0.2f);

//	PokazDrzewa();
	
	Rysuj_gory((int)DETALE[0],DETALE[1],(int)DETALE[2]);

	Draw_SKY();

	Rysuj_Swiat(mapa);
	
	// Rysowanie skoczka
	glTranslatef(0.4f+(xpos2*0.1f),ypos4+(ludek[frame].Y)-0.8f,0); // ustawienia  
	if (xpos2>mapa.dl_skoczni) glTranslatef(0,-0.1f,0);
	glRotatef(-90,0,0,1);
	glRotatef(90,0,1,0);
	glRotatef(-kat+90,1,0,0);
	glRotatef(ludek[frame].rotY,0,1,0);
	glRotatef(-ludek[frame].rotX,1,0,0);

	
	if (lad==true && ladowanie==true)
	{
		if (crash==false) glRotatef(-90,1,0,0); //else glRotatef(20,1,0,0);
	}
	if (xpos2>mapa.dl_skoczni)
	{
		glRotatef(ludek[frame].rotX-kat-75,1,0,0);
		if (crash==false) glTranslatef(0,0.1f,0);
	}

    DrawSkiJumper((xpos2*0.1f)+0.6f,0,0);
	
   




	// Rysowanie HUDa
	if (notyok==true) Rysuj_noty();
	Rysuj_Wiatr();
    Rysuj_Wysokosc();
	glLoadIdentity();
    glDisable(GL_FOG);
	glTranslatef(-0.5f,0.4f,-1);
	glDisable(GL_DEPTH_TEST);
	piszTXT(0,-0.0f,0.03f,0.03f,0.03f,0,0,255, fonttexture.texID,"FPS: %d",fps);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
}

void SetFog(float r, float g, float b, float a)
{
	GLfloat fogColor[4]= {(float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f};
	glClearColor(r,g,b,a);
	glFogi(GL_FOG_MODE,GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glHint(GL_FOG_HINT, GL_FASTEST);
	glEnable(GL_FOG);
}




void LoadScreen(char* str_)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	piszTXT(-5,-3.5f,0.2f,0.3f,0.6f,0,0,255, fonttexture.texID,"%s",str_);
	SwapBuffers(hDC);
}

void CHCamera(int nr)
{
	if (kamera==nr) return;
	kamera=nr;
	g_Camera.m_vPosition.x=0;
	g_Camera.m_vPosition.y=0;
	g_Camera.m_vPosition.z=0;
	g_Camera.m_vStrafe.x=0;
	g_Camera.m_vStrafe.y=0;
	g_Camera.m_vStrafe.z=0;
	g_Camera.m_vUpVector.x=0;
	g_Camera.m_vUpVector.y=0;
	g_Camera.m_vUpVector.z=0;
	g_Camera.m_vView.x=0;
	g_Camera.m_vView.y=0;
	g_Camera.m_vView.z=0;
	g_Camera.PositionCamera(0,0,0,0,0,0,1,1,1);
	if (nr==1)
	{
	  g_Camera.PositionCamera(xpos2*0.1f, ypos4+2, 8,   xpos2*0.1f, ypos4+2, 0,   0, 1, 0);
	  g_Camera.RotateView(-0.1f,1,0,0);
	}
	if (nr==2)
	{
	  g_Camera.PositionCamera(xpos2*0.1f, ypos4+5, 12,   xpos2*0.1f, ypos4+7, 0,   0, 1, 0);
	  g_Camera.RotateView(-0.3f,1,0,0);
	}
	if (nr==3)
	{
	  g_Camera.PositionCamera(xpos2*0.1f, ypos4+13, 12,   xpos2*0.1f, ypos4+15, 0,   0, 1, 0);
	  g_Camera.RotateView(-1.0f,1,0,0);
	}
	if (nr==4)
	{
	  g_Camera.PositionCamera(xpos2*0.1f, ypos4+15, 12,   xpos2*0.1f, ypos4+17, 0,   0, 1, 0);
	  g_Camera.RotateView(-1.5f,1,0,0);
	  g_Camera.MoveCamera(12*3.5f);
	}
	if (nr==5)
	{
	  g_Camera.PositionCamera(xpos2*0.1f, ypos4+15, 0,   xpos2*0.1f, ypos4+10, 12,   0, 1, 0);
	  g_Camera.RotateView(1.5715f,0,1,0);
	  g_Camera.RotateView(-1.0f,0,0,1);
	  g_Camera.UpDownCamera(2);
	}
}


int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	INITALL();
	MSG	msg;
	BOOL done=FALSE;
	if (CreateGLWindow("GG ENGINE",640,480,16,fullscreen)==FALSE)
	{
		return 0;
	}
    glAlphaFunc(GL_GREATER, 0.0f);
    SetFog(200,200,200,255);
    glFogf(GL_FOG_DENSITY, 0.040f);
	LoadTGAFile(&fonttexture,"textures/courier.tga",false,1);
    glLoadIdentity();
	glTranslatef(0,0,-10);
	
	LoadScreen("Loading: textures...");
	Load_Textures();
	
	LoadScreen("Loading: landscape...");
	
    for (i=0;i<11001;i++) x01f[i]=i*0.1f;
	Make_World(95); 
	mapa.slupy[0].X=50;
	mapa.slupy[0].H=(float)abs(mapa.skocznia[mapa.dl_skoczni-(int)1.0f]-2.f)+(float)
		            mapa.skocznia[mapa.slupy[0].X]+1.0f;
	mapa.slupy[0].alive=true;	
	mapa.slupy[1].X=70;
	mapa.slupy[1].H=(float)abs(mapa.skocznia[mapa.dl_skoczni-(int)1.0f]-2.f)+(float)
		            mapa.skocznia[mapa.slupy[1].X]+1.0f;
	mapa.slupy[1].alive=true;
	Make_Teren();

	DETALE[0]=70;
	DETALE[1]=DETALE[0]/10;DETALE[1]=DETALE[1]/2;
	DETALE[2]=DETALE[0]/2;

    ypos4=mapa.skocznia[1]*2.15f;
	CHCamera(2);

	for (i=0; i<ilesniegu; i++)
	{
		snow[i].x=(Random(0,length)*0.1f)-47;
		//snow[i].y=50;
		snow[i].y=50-Random(0,72);
		snow[i].z=(Random(0,42)*2.0f)-42;
		ftemp=Random(0,5);
		if (ftemp=0) snow[i].speed=0.1f;
		if (ftemp=1) snow[i].speed=0.14f;
		if (ftemp=2) snow[i].speed=0.17f;
		if (ftemp=3) snow[i].speed=0.20f;
		if (ftemp=4) snow[i].speed=0.34f;
	}

	
	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (ladowanie==true && predkosc!=0) Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
			if (keys['D']) Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
			if (keys['1']) CHCamera(1);
			if (keys['2']) CHCamera(2);
			if (keys['3']) CHCamera(3);
			if (keys['4']) CHCamera(4);
			if (keys['5']) CHCamera(5);
			

			mapY2=mapY;
			mapX2=mapX;
            mapZ2=mapZ;
            mapZ2=mapZ+camX;

            DrawGLScene();
			g_Camera.Update();
		//	g_Camera.SetViewByMouse();
			Get_FPS(fps);
			SwapBuffers(hDC);
            
			if (kamera==1 || kamera==2 || kamera==3 || kamera==4)
			{
			  if (xpos<xpos2) g_Camera.StrafeCamera(-(xpos-xpos2)/10);
			  if (xpos>xpos2) g_Camera.StrafeCamera((xpos-xpos2)/10);
			  if (ypos>ypos2-wysokosc) g_Camera.UpDownCamera((ypos2-ypos));
			  if (ypos<ypos2-wysokosc) g_Camera.UpDownCamera(-(ypos2-ypos));
			}
			if (kamera==5)
			{
			  if (xpos<xpos2) g_Camera.MoveCamera(-(xpos-xpos2)/1.75f);
			  if (xpos>xpos2) g_Camera.MoveCamera((xpos-xpos2)/1.75f);
			  if (ypos>ypos2-wysokosc) g_Camera.UpDownCamera((ypos2-ypos));
			  if (ypos<ypos2-wysokosc) g_Camera.UpDownCamera(-(ypos2-ypos));
			}
                    
            mapZ=-(xpos2*0.1f)+predkosc+camZ;
            mapY=-ypos2-2.0f+camY;
            
            xpos2=xpos;
			ypos=ypos2;
            
			if (keys[VK_RIGHT]) g_Camera.StrafeCamera(kSpeed*8);
			if (keys[VK_LEFT]) g_Camera.StrafeCamera(-kSpeed*8);
			if (keys['Q']) g_Camera.MoveCamera(kSpeed*8);
			if (keys['A']) g_Camera.MoveCamera(-kSpeed*8);
			if (keys[VK_UP]) g_Camera.UpDownCamera(1.f);
			if (keys[VK_DOWN]) g_Camera.UpDownCamera(-1.f);

			if (ladowanie==true && notyok==false && predkosc==0)
			{
				notyok=true;
				if (pozycjaY==1) lot_poz=2;
				if (pozycjaY==2) lot_poz=1;
				if (pozycjaY==3) lot_poz=0;
				if (pozycjaY==4) lot_poz=1;
				if (pozycjaY==5) lot_poz=2;
				if (crash==true) lot_poz+=8;
				punkty[1]=20-lot_poz-(landing*0.2f)-(prog*0.075f)+((Random(0,3)-2)*0.5f);
				punkty[2]=20-lot_poz-(landing*0.2f)-(prog*0.075f)+((Random(0,3)-2)*0.5f);
				punkty[3]=20-lot_poz-(landing*0.2f)-(prog*0.075f)+((Random(0,3)-2)*0.5f);
				punkty[4]=20-lot_poz-(landing*0.2f)-(prog*0.075f)+((Random(0,3)-2)*0.5f);
				punkty[5]=20-lot_poz-(landing*0.2f)-(prog*0.075f)+((Random(0,3)-2)*0.5f);
				pkt[1]=punkty[1]-(int)punkty[1];
				pkt[2]=punkty[2]-(int)punkty[2];
				pkt[3]=punkty[3]-(int)punkty[3];
				pkt[4]=punkty[4]-(int)punkty[4];
				pkt[5]=punkty[5]-(int)punkty[5];
				punkty[1]=(int)punkty[1];
				punkty[2]=(int)punkty[2];
				punkty[3]=(int)punkty[3];
				punkty[4]=(int)punkty[4];
				punkty[5]=(int)punkty[5];
				for (i=1;i<=5;i++) if (pkt[i]>=0.5f) punkty[i]+=0.5f;
			}
            

			if (keys['W']) RotY+=0.55f;
			if (keys['S']) RotY-=0.55f;
			if (keys['D']) RotX+=0.55f;
			if (keys['F']) RotX-=0.55f;
			if (keys['Z']) mapa.r_point+=0.5f;
            if (keys['X']) mapa.r_point-=0.5f;

            if (keys['B']) xpos+=0.05f;
            if (keys['N']) xpos-=0.05f;
            if (keys['1']) Sleep(50);

            if (keys['0'] && wiatr<3) wiatr+=0.1f;
            if (keys['9'] && wiatr>-3) wiatr-=0.1f;

            if (predkosc>0 && LBM==true && lewy==false && wybicie==false && xpos<=mapa.dl_skoczni+5 && xpos2>=mapa.start) 
			{
				wybicie=true;
				wzbicie=mapa.K/1500;
				lewy=true;
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
				Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);Dodaj_dymek((xpos2*0.1f)-0.2f,ypos4-0.4f,(Random(0,5)-3)*0.1f);
			}
            if (wybicie==false && ladowanie==false) klatka=0;
            if (wybicie==true && klatka<11) klatka+=0.5f;

            if (wybicie==true && wzbicie>0)
            {
                wzbicie=wzbicie-mapa.K35;
                lot=lot-wzbicie;
            }
            if (xpos>mapa.dl_skoczni && wzbicie<=0 && lot<2.0f)
            {
                spadanie=spadanie+mapa.K53;
                if (wybicie==false) spadanie=spadanie+mapa.K53+mapa.K53;
                lot=lot+spadanie;
                if (frame==11) lot=lot+Procent(spadanie,100);
                if (frame==12) lot=lot+Procent(spadanie,50);
                if (frame==13) lot=lot+Procent(spadanie,0);
                if (frame==14) lot=lot+Procent(spadanie,50);
                if (frame==15) lot=lot+Procent(spadanie,100);
            }
            if (lot>=2.0f && predkosc>0 && ladowanie==false)
            {
                //if (laduje==0) crash=true;
                ladowanie=true;
            }
            if (ladowanie==true) {predkosc-=0.003f;}
	

			if (predkosc<0) predkosc=0;

	


			if (LBM==true && predkosc==0 && lewy==false) 
			{				
				predkosc=0.002f;
                lewy=true;
			}
			if (predkosc>0 && xpos<mapa.dl_skoczni) predkosc+=0.002f;
			xpos+=predkosc;
            
            if (xpos>mapa.dl_skoczni && predkosc>0 && ladowanie==false) predkosc-=0.001f;
            if (xpos>mapa.dl_skoczni && predkosc>0 && ladowanie==false && xpos>mapa.dl_skoczni+5)
            {
                predkosc=predkosc-(((wiatr-(Random(10,20)/10.f)))/5000);
            }
            Ustalanie_kata();    

            if (mouseY!=myszY && wybicie==true && klatka>=10 && ladowanie==false && lad==false) 
            {
                if (mouseY<windowY2-5 && pozycjaY>1) {pozycjaY-=1; SetCursorPos(windowX2,windowY2);}
                if (mouseY>windowY2+5 && pozycjaY<5) {pozycjaY+=1; SetCursorPos(windowX2,windowY2);}
				if (mouseY<windowY2-5) {SetCursorPos(windowX2,windowY2);}
				if (mouseY>windowY2+5) {SetCursorPos(windowX2,windowY2);}
                klatka=pozycjaY+10.0f;
            }
			if (LBM==true && lewy==false && lad==false && predkosc>0 && wybicie==true)
			{
				nrcienia=13;
                lewy=true;
				lad=true;
                landing=wysokosc;
				klatka=16;
                midlad=20;
                maxlad=35;
			}
			if (RBM==true && prawy==false && lad==false && predkosc>0 && wybicie==true)
			{
			 	nrcienia=13;
                prawy=true;
				lad=true;
                landing=wysokosc;
				klatka=36;
                midlad=40;
                maxlad=68;
			}
            if (lad==true && crash==false && klatka>=maxlad && klatka<79)
            {
                if (klatka<69) klatka=69;
                klatka+=0.1f;
            }

			if (lad==true && klatka<maxlad)
			{
				if ((klatka<midlad && ladowanie==false) || (klatka>midlad && ladowanie==true) || ladowanie==true) klatka+=0.5f;
			}

            if (lad==true && crash==false)
            {
                if (klatka==midlad && ladowanie==false) crasher++;
                if (crasher>50) crash=true;
            }

			if (ladowanie==true && lad==true && klatka<midlad)
			{
				crash=true;
				klatka=80;
			}
            if (ladowanie==false && lad==true && klatka>=maxlad) {crash=true;}
			if (crash==true && klatka<80) klatka=80.0f;
            if (ladowanie==true && lad==false && crash==false) {crash=true; klatka=80;}

			if (klatka<88.0f && klatka>=80.0f) klatka+=0.25f;

            if (predkosc<=0 && lad==true && crash==false && klatka<128)
            {
                if (klatka<89) klatka=89;
                klatka+=0.2f;
            }

            frame=(int)klatka;

            wysokosc=mapa.teren[(int)xpos2+5]+((2+(mapY2-camY)-0.9f+ludek[frame].Y)+1.82f);
            wysokosc=wysokosc-0.0f;
            wysokosc=-wysokosc;            
            if (wysokosc<0.4f) wysokosc=0.0f;
            if (xpos2<mapa.dl_skoczni) wysokosc=0.0f;

			if (xpos2<mapa.dl_skoczni && wybicie==false)
			{
				prog=mapa.dl_skoczni-xpos2;
			}
			if (xpos2>mapa.dl_skoczni && ladowanie==false) odleglosc=(xpos2-mapa.dl_skoczni)/4.0f;


            if (LBM==false) lewy=false;
            if (RBM==false) prawy=false;

			if (keys[VK_ESCAPE])
			{
				done=TRUE;
			}
			
		}
	}

	KillGLWindow();

	return (msg.wParam);
} 






/*
0 zjazd
1-10 wybicie
11 pozycja z³a
12 pozycja srednia
13 pozycja dobra
14 pozycja srednia
15 pozycja zla
16-35 ladowanie na dwie nogi
36-68 ladowanie telemarkiem
69-79 hamowanie
80-88 upadek
89-128 radoœæ

if punkt_k<100 then punkt:=2;
if punkt_k>100 then punkt:=1.8;
if punkt_k>150 then punkt:=1.2;

*/