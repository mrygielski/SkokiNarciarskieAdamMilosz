int frame=0;

float RAD=180.0f/3.1415926535897932385f;
int BAR1=0; int BAR2=1;
int LOKIEC1=2; int LOKIEC2=3;
int KOLANO1=4; int KOLANO2=5;
int STOPA1=6; int STOPA2=7;
int NARTA1=8; int NARTA2=9;
struct Tludek
{
    float rx[10],ry[10],rz[10];
    float rotX,rotY,Y;
};

Tludek ludek[501];
// pomocnicze dla ludka
float wys_glowa, wys_tulow, wys_nogi;
float x,y,xx,yy,zz,rxx,ryy,rzz,nxx,nyy,nzz;
float ypos_L1, xpos_L1, zpos_L1,
      ypos_L2, xpos_L2, zpos_L2,
      ypos_L3, xpos_L3, zpos_L3,
      ypos_L4, xpos_L4, zpos_L4,
      szer_1, szer_2, szer_3;
int plik;
void QUAD(float x1,float y1,float z1,
          float x2,float y2,float z2,
          float x3,float y3,float z3,
          float x4,float y4,float z4,
          float zz,
          int t1,int t2, int t3, int t4, int t5, int t6)
{
    BarT(
         x2,y2,z2,
         x3,y3,z3,
         x4,y4,z4,x1,y1,z1,255,255,255,255,t1);
    BarT(
         x2,y2,z2+zz,
         x3,y3,z3+zz,
         x4,y4,z4+zz,x1,y1,z1+zz,255,255,255,255,t2);
    BarT(x1,y1,z1,
         x2,y2,z2,
         x2,y2,z2+zz,
         x1,y1,z1+zz,255,255,255,255,t3);
    BarT(x4,y4,z4,
         x3,y3,z3,
         x3,y3,z3+zz,
         x4,y4,z4+zz,255,255,255,255,t4);
    BarT(x1,y1,z1,
         x4,y4,z4,
         x4,y4,z4+zz,
         x1,y1,z1+zz,255,255,255,255,t5);
    BarT(x2,y2,z2,
         x3,y3,z3,
         x3,y3,z3+zz,
         x2,y2,z2+zz,255,255,255,255,t6);
}


void QUADS8(float x1, float y1, float z1, // bok 1
			float x2, float y2, float z2, // bok 2
			float x3, float y3, float z3, // bok 3
			float x4, float y4, float z4, // bok 4
			float x5, float y5, float z5, // bok 5
			float x6, float y6, float z6, // bok 6
			float x7, float y7, float z7, // bok 7
			float x8, float y8, float z8,  // bok 8
			int r, int g, int b, int a, // kolorki
			int text) //textura
{
	SetTextures(true);
	glColor4ub(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS);
		glTexCoord2f(0.01f,0.66f); glVertex3f(x3,y3,z3);
		glTexCoord2f(0.99f,0.66f); glVertex3f(x8,y8,z8);
		glTexCoord2f(0.69f,0.99f); glVertex3f(x1,y1,z1);
		glTexCoord2f(0.31f,0.99f); glVertex3f(x2,y2,z2);

		glTexCoord2f(0.01f,0.33f); glVertex3f(x4,y4,z4);
		glTexCoord2f(0.99f,0.33f); glVertex3f(x7,y7,z7);
		glTexCoord2f(0.99f,0.66f); glVertex3f(x8,y8,z8);
		glTexCoord2f(0.01f,0.66f); glVertex3f(x3,y3,z3);

		glTexCoord2f(0.31f,0.01f); glVertex3f(x5,y5,z5);
		glTexCoord2f(0.69f,0.01f); glVertex3f(x6,y6,z6);
		glTexCoord2f(0.99f,0.33f); glVertex3f(x7,y7,z7);
		glTexCoord2f(0.01f,0.33f); glVertex3f(x4,y4,z4);
	glEnd();
	SetTextures(false);
}

void QUADS8a(float x1, float y1, float z1, // bok 1
		 	float x2, float y2, float z2, // bok 2
			float x3, float y3, float z3, // bok 3
			float x4, float y4, float z4, // bok 4
			float x5, float y5, float z5, // bok 5
			float x6, float y6, float z6, // bok 6
			float x7, float y7, float z7, // bok 7
			float x8, float y8, float z8,  // bok 8
			int r, int g, int b, int a, // kolorki
			int text) //textura
{
	SetTextures(true);
	glColor4ub(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,0.8f); glVertex3f(x8,y8,z8);
		glTexCoord2f(0,1); glVertex3f(x1,y1,z1);
		glTexCoord2f(0,0); glVertex3f(x7,y7,z7);
		glTexCoord2f(0.5f,1); glVertex3f(x2,y2,z2);

		glTexCoord2f(0.5f,1);   glVertex3f(x2,y2,z2);
		glTexCoord2f(1,1); glVertex3f(x3,y3,z3);
		glTexCoord2f(1,0.8f);   glVertex3f(x4,y4,z4);
		glTexCoord2f(1,0); glVertex3f(x5,y5,z5);
		
		glTexCoord2f(0.5f,1);   glVertex3f(x2,y2,z2);
		glTexCoord2f(0.5f,1);     glVertex3f(x2,y2,z2);
		glTexCoord2f(1,0);   glVertex3f(x5,y5,z5);
		glTexCoord2f(0,0);     glVertex3f(x7,y7,z7);

	glEnd();
	SetTextures(false);
}


void HEAD(float x, float y, float z, float szerokosc, float wysokosc, float grubosc, 
		  int t, int t2, int t3, int t4)
{
	//przód
	QUADS8(x-szerokosc,y+(wysokosc+0.030f),z, //bok1
		   x+szerokosc,y+(wysokosc+0.030f),z, //bok2	
		   x+(szerokosc+0.028f),y+wysokosc,z, //bok3
           x+(szerokosc+0.028f),y-wysokosc,z, //bok4
		   x+szerokosc,y-(wysokosc+0.030f),z, //bok5		   
		   x-szerokosc,y-(wysokosc+0.030f),z, //bok6		   
		   x-(szerokosc+0.028f),y-wysokosc,z, //bok7	
		   x-(szerokosc+0.028f),y+wysokosc,z, //bok8		   
	       255,255,255,255,t);
	//ty³
	QUADS8(x-szerokosc,y+(wysokosc+0.030f),z-grubosc, //bok1
		   x+szerokosc,y+(wysokosc+0.030f),z-grubosc, //bok2	
		   x+(szerokosc+0.028f),y+wysokosc,z-grubosc, //bok3
           x+(szerokosc+0.028f),y-wysokosc,z-grubosc, //bok4
		   x+szerokosc,y-(wysokosc+0.030f),z-grubosc, //bok5		   
		   x-szerokosc,y-(wysokosc+0.030f),z-grubosc, //bok6		   
		   x-(szerokosc+0.028f),y-wysokosc,z-grubosc, //bok7	
		   x-(szerokosc+0.028f),y+wysokosc,z-grubosc, //bok8		   
	       255,255,255,255,t3);
	//lewy bok
	QUADS8(x-szerokosc,y+(wysokosc+0.030f),z, //bok1
		   x-szerokosc,y+(wysokosc+0.030f),z-grubosc, //bok2	
		   x-(szerokosc+0.028f),y+wysokosc,z-grubosc, //bok3
           x-(szerokosc+0.028f),y-wysokosc,z-grubosc, //bok4
		   x-szerokosc,y-(wysokosc+0.030f),z-grubosc, //bok5		   
		   x-szerokosc,y-(wysokosc+0.030f),z, //bok6		   
		   x-(szerokosc+0.028f),y-wysokosc,z, //bok7	
		   x-(szerokosc+0.028f),y+wysokosc,z, //bok8		   
	       255,255,255,255,t2);
	//prawy bok
	QUADS8(x+szerokosc,y+(wysokosc+0.030f),z, //bok1
		   x+szerokosc,y+(wysokosc+0.030f),z-grubosc, //bok2	
		   x+(szerokosc+0.028f),y+wysokosc,z-grubosc, //bok3
           x+(szerokosc+0.028f),y-wysokosc,z-grubosc, //bok4
		   x+szerokosc,y-(wysokosc+0.030f),z-grubosc, //bok5		   
		   x+szerokosc,y-(wysokosc+0.030f),z, //bok6		   
		   x+(szerokosc+0.028f),y-wysokosc,z, //bok7	
		   x+(szerokosc+0.028f),y+wysokosc,z, //bok8		   
	       255,255,255,255,t2);
	//gora
	BarT(x-szerokosc,y+(wysokosc+0.030f),z,
		 x-szerokosc,y+(wysokosc+0.030f),z-grubosc,
		 x+szerokosc,y+(wysokosc+0.030f),z-grubosc,
		 x+szerokosc,y+(wysokosc+0.030f),z,
		 255,255,255,255,t4);

    wys_glowa=(wysokosc*2)+0.030f;
}

float Procent(float x1, float x2)
{
	return x1*(x2/100);
}

void BODY(float x, float y, float z, float szerokosc, float wysokosc, float grubosc, 
          int koszulkaFRONT, int koszulkaBACK, int bary, int bok)
{
	//PRZÓD 
	QUADS8a(x-szerokosc,y,z, //bok1
		   x,y+Procent(wysokosc,10.0f),z, //bok2	
		   x+szerokosc,y,z, //bok3
           x+szerokosc,y-Procent(wysokosc,15.0f),z, //bok4
		   x+(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z, //bok5		   
		   x,y-wysokosc,z, //bok6		   
		   x-(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z, //bok7	
		   x-szerokosc,y-Procent(wysokosc,15.0f),z, //bok8		   
	       255,255,255,255,koszulkaFRONT);
	//TY£
	QUADS8a(x-szerokosc,y,z-grubosc, //bok1
		   x,y+Procent(wysokosc,10.0f),z-grubosc, //bok2	
		   x+szerokosc,y,z-grubosc, //bok3
           x+szerokosc,y-Procent(wysokosc,15.0f),z-grubosc, //bok4
		   x+(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z-grubosc, //bok5		   
		   x,y-wysokosc,z-grubosc, //bok6		   
		   x-(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z-grubosc, //bok7	
		   x-szerokosc,y-Procent(wysokosc,15.0f),z-grubosc, //bok8		   
	       255,255,255,255,koszulkaBACK);
	//LEWA GÓRA
	BarT(x-szerokosc,y,z,
		 x,y+Procent(wysokosc,10.0f),z,
		 x,y+Procent(wysokosc,10.0f),z-grubosc,
		 x-szerokosc,y,z-grubosc,
		 255,255,255,255,bary);
	//PRAWA GÓRA
	BarT(x,y+Procent(wysokosc,10.0f),z,
		 x+szerokosc,y,z,
		 x+szerokosc,y,z-grubosc,
		 x,y+Procent(wysokosc,10.0f),z-grubosc,
		 255,255,255,255,bary);
	//PRAWY BOK
	BarT(x+szerokosc,y-Procent(wysokosc,15.0f),z,
		 x+(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z,
		 x+(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z-grubosc,
		 x+szerokosc,y-Procent(wysokosc,15.0f),z-grubosc, 
		 255,255,255,255,bok);
	//LEWY BOK
	BarT(x-szerokosc,y-Procent(wysokosc,15.0f),z,
		 x-(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z,
		 x-(szerokosc-Procent(szerokosc,25.0f)),y-wysokosc,z-grubosc,
		 x-szerokosc,y-Procent(wysokosc,15.0f),z-grubosc,
		 255,255,255,255,bok);
    //BAR LEWY
    BarT(x-szerokosc,y,z,
         x-szerokosc,y-Procent(wysokosc,15.0f),z,
         x-szerokosc,y-Procent(wysokosc,15.0f),z-grubosc,
         x-szerokosc,y,z-grubosc,
         255,255,255,255,bary);
    // BAR PRAWY
    BarT(x+szerokosc,y,z,
         x+szerokosc,y-Procent(wysokosc,15.0f),z,
         x+szerokosc,y-Procent(wysokosc,15.0f),z-grubosc,
         x+szerokosc,y,z-grubosc,
         255,255,255,255,bary);
    
    //NOGA LEWA
    xpos_L3=x-(szerokosc-Procent(szerokosc,25.0f));
    ypos_L3=y-wysokosc;
    zpos_L3=z;
    szer_3=x+(x-(szerokosc-Procent(szerokosc,25.0f)));
    //NOGA PRAWA
    xpos_L4=x+(szerokosc-Procent(szerokosc,25.0f));
    ypos_L4=y-wysokosc;
    zpos_L4=z;
    

    // REKA LEWA
    xpos_L1=x-szerokosc;
	ypos_L1=y;
	zpos_L1=z;

    //REKA PRAWA
	xpos_L2=x+szerokosc;
	ypos_L2=y;
	zpos_L2=z;

	szer_1=Procent(wysokosc,15.0f);
	szer_2=grubosc;

	wys_tulow=wysokosc;
}



void _RotX(float x,float &y, float &z,float kat)
{
    float yy,zz;
    yy=y*(float)cos(-kat/RAD)+z*(float)sin(-kat/RAD);
    zz=z*(float)cos(-kat/RAD)-y*(float)sin(-kat/RAD);
    y=yy;
    z=zz;
}

void _RotY(float &x,float y, float &z,float kat)
{
    float xx,zz;
    xx=x*(float)cos(-kat/RAD)-z*(float)sin(-kat/RAD);
    zz=z*(float)cos(-kat/RAD)+x*(float)sin(-kat/RAD);
    x=xx;
    z=zz;
}

void _RotZ(float &x,float &y, float z,float kat)
{
    float xx,yy;
    xx=x*(float)cos(-kat/RAD)+y*(float)sin(-kat/RAD);
    yy=y*(float)cos(-kat/RAD)-x*(float)sin(-kat/RAD);
    x=xx;
    y=yy;
}


void Ramie_lewe(int r1, int r2, int r3, int r4, int rekawica)
{   
    xx=xpos_L1,yy=ypos_L1,zz=zpos_L1;
    

    glPushMatrix();
    glTranslatef(xpos_L1,ypos_L1,zpos_L1);
    glRotatef(ludek[frame].rx[BAR1],1,0,0);
    glRotatef(ludek[frame].ry[BAR1],0,1,0);
    glRotatef(ludek[frame].rz[BAR1],0,0,1);
    QUAD(0,0,0,
         0-Procent(szer_1,75),0,0,
         0-Procent(szer_1,75),0-Procent(wys_tulow,65),0,
         0,0-Procent(wys_tulow,65),0,
         -szer_2,
         r4,r4,r3,r4,r4,r3);
    rxx=0;ryy=-Procent(wys_tulow,65);rzz=-szer_2;
	_RotZ(rxx,ryy,rzz,ludek[frame].rz[BAR1]);
	_RotY(rxx,ryy,rzz,ludek[frame].ry[BAR1]);
    _RotX(rxx,ryy,rzz,ludek[frame].rx[BAR1]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(rxx+xpos_L1, ryy+ypos_L1, rzz+zpos_L1);
    glRotatef(ludek[frame].rx[LOKIEC1]+ludek[frame].rx[BAR1],1,0,0);
    glRotatef(ludek[frame].ry[LOKIEC1]+ludek[frame].ry[BAR1],0,1,0);
    glRotatef(ludek[frame].rz[LOKIEC1]+ludek[frame].rz[BAR1],0,0,1);
    QUAD(0,0,0,
         0-Procent(szer_1,75),0,0,
         0-Procent(szer_1,75),0-Procent(wys_tulow,65),0,
         0,0-Procent(wys_tulow,65),0,
         szer_2,
         r2,r2,r2,rekawica,r2,r1);
    glPopMatrix();
}

void Ramie_prawe(int r1, int r2, int r3, int r4, int rekawica)
{   
    xx=xpos_L2,yy=ypos_L2,zz=zpos_L2;
    

    glPushMatrix();
    glTranslatef(xpos_L2,ypos_L2,zpos_L2);
    glRotatef(ludek[frame].rx[BAR2],1,0,0);
    glRotatef(ludek[frame].ry[BAR2],0,1,0);
    glRotatef(ludek[frame].rz[BAR2],0,0,1);
    QUAD(0,0,0,
         0+Procent(szer_1,75),0,0,
         0+Procent(szer_1,75),0-Procent(wys_tulow,65),0,
         0,0-Procent(wys_tulow,65),0,
         -szer_2,
         r4,r4,r3,r4,r4,r3);
    rxx=0;ryy=-Procent(wys_tulow,65);rzz=-szer_2;

    _RotZ(rxx,ryy,rzz,ludek[frame].rz[BAR2]);
	_RotY(rxx,ryy,rzz,ludek[frame].ry[BAR2]);
    _RotX(rxx,ryy,rzz,ludek[frame].rx[BAR2]);

	glPopMatrix();

    glPushMatrix();
    glTranslatef(rxx+xpos_L2, ryy+ypos_L2, rzz+zpos_L2);
    glRotatef(ludek[frame].rx[LOKIEC2]+ludek[frame].rx[BAR2],1,0,0);
    glRotatef(ludek[frame].ry[LOKIEC2]+ludek[frame].ry[BAR2],0,1,0);
    glRotatef(ludek[frame].rz[LOKIEC2]+ludek[frame].rz[BAR2],0,0,1);
    QUAD(0,0,0,
         0+Procent(szer_1,75),0,0,
         0+Procent(szer_1,75),0-Procent(wys_tulow,65),0,
         0,0-Procent(wys_tulow,65),0,
         szer_2,
         r2,r2,r2,rekawica,r2,r1);
    glPopMatrix();
}

void Noga_lewa(int r1, int r2, int r3, int r4, int rekawica)
{   
    xx=xpos_L3,yy=ypos_L3,zz=zpos_L3;

    glPushMatrix();
    glTranslatef(xpos_L3,ypos_L3,zpos_L3);
    glRotatef(ludek[frame].rx[KOLANO1],1,0,0);
    glRotatef(ludek[frame].ry[KOLANO1],0,1,0);
    glRotatef(ludek[frame].rz[KOLANO1],0,0,1);
    QUAD(0,0,0,
         0-Procent(szer_3,100),0,0,
         0-Procent(szer_3,75),0-Procent(wys_tulow,80),0,
         0,0-Procent(wys_tulow,80),0,
         -szer_2,
         r4,r4,r4,r4,r3,r4);
    rxx=0;ryy=-Procent(wys_tulow,80);rzz=-szer_2;
	_RotZ(rxx,ryy,rzz,ludek[frame].rz[KOLANO1]);
	_RotY(rxx,ryy,rzz,ludek[frame].ry[KOLANO1]);
    _RotX(rxx,ryy,rzz,ludek[frame].rx[KOLANO1]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(rxx+xpos_L3, ryy+ypos_L3, rzz+zpos_L3);
    glRotatef(ludek[frame].rx[STOPA1]+ludek[frame].rx[KOLANO1],1,0,0);
    glRotatef(ludek[frame].ry[STOPA1]+ludek[frame].ry[KOLANO1],0,1,0);
    glRotatef(ludek[frame].rz[STOPA1]+ludek[frame].rz[KOLANO1],0,0,1);
    QUAD(0,0,0,
         0-Procent(szer_3,75),0,0,
         0-Procent(szer_3,70),0-Procent(wys_tulow,85),0,
         0,0-Procent(wys_tulow,85),0,
         szer_2,
         r2,r2,r2,rekawica,r1,r2);
    glPopMatrix();
    nxx=0;nyy=-Procent(wys_tulow,85);nzz=szer_2;
	
    _RotZ(nxx,nyy,nzz,ludek[frame].rz[STOPA1]+ludek[frame].rz[KOLANO1]);
    _RotY(nxx,nyy,nzz,ludek[frame].ry[STOPA1]+ludek[frame].ry[KOLANO1]);
    _RotX(nxx,nyy,nzz,ludek[frame].rx[STOPA1]+ludek[frame].rx[KOLANO1]);
    

    
}

void Narta_lewa(int r1)
{
    glPushMatrix();
    glTranslatef(nxx+xpos_L3+rxx, nyy+ypos_L3+ryy, nzz+zpos_L3+rzz);
    glRotatef(ludek[frame].rx[STOPA1]+ludek[frame].rx[KOLANO1]+ludek[frame].rx[NARTA1],1,0,0);
    glRotatef(ludek[frame].ry[STOPA1]+ludek[frame].ry[KOLANO1]+ludek[frame].ry[NARTA1],0,1,0);
    glRotatef(ludek[frame].rz[STOPA1]+ludek[frame].rz[KOLANO1]+ludek[frame].rz[NARTA1],0,0,1);
    QUAD(-Procent(szer_3,75),0,0,
         -Procent(szer_3,75)-szer_2,0,0,
         -Procent(szer_3,75)-szer_2,-0.03f,0,
         -Procent(szer_3,75),-0.03f,0,
         Procent(wys_tulow,280),
         r1,r1,r1,r1,r1,r1);
    QUAD(-Procent(szer_3,75),0,0,
         -Procent(szer_3,75)-szer_2,0,0,
         -Procent(szer_3,75)-szer_2,-0.03f,0,
         -Procent(szer_3,75),-0.03f,0,
         -Procent(wys_tulow,180),
         r1,r1,r1,r1,r1,r1);  
    glPopMatrix();
}

void Noga_prawa(int r1, int r2, int r3, int r4, int rekawica)
{   
    xx=xpos_L4;yy=ypos_L4;zz=zpos_L4;

    glPushMatrix();
    glTranslatef(xpos_L4,ypos_L4,zpos_L4);
    glRotatef(ludek[frame].rx[KOLANO2],1,0,0);
    glRotatef(ludek[frame].ry[KOLANO2],0,1,0);
    glRotatef(ludek[frame].rz[KOLANO2],0,0,1);
    QUAD(0,0,0,
         0+Procent(szer_3,100),0,0,
         0+Procent(szer_3,75),0-Procent(wys_tulow,80),0,
         0,0-Procent(wys_tulow,80),0,
         -szer_2,
         r4,r4,r4,r4,r3,r4);
    rxx=0;ryy=-Procent(wys_tulow,80);rzz=-szer_2;
	_RotZ(rxx,ryy,rzz,ludek[frame].rz[KOLANO2]);
	_RotY(rxx,ryy,rzz,ludek[frame].ry[KOLANO2]);
    _RotX(rxx,ryy,rzz,ludek[frame].rx[KOLANO2]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(rxx+xpos_L4, ryy+ypos_L4, rzz+zpos_L4);
    glRotatef(ludek[frame].rx[STOPA2]+ludek[frame].rx[KOLANO2],1,0,0);
    glRotatef(ludek[frame].ry[STOPA2]+ludek[frame].ry[KOLANO2],0,1,0);
    glRotatef(ludek[frame].rz[STOPA2]+ludek[frame].rz[KOLANO2],0,0,1);
    QUAD(0,0,0,
         0+Procent(szer_3,75),0,0,
         0+Procent(szer_3,70),0-Procent(wys_tulow,85),0,
         0,0-Procent(wys_tulow,85),0,
         szer_2,
         r2,r2,r2,rekawica,r1,r2);
    glPopMatrix();
    nxx=0;nyy=-Procent(wys_tulow,85);nzz=szer_2;
	
    _RotZ(nxx,nyy,nzz,ludek[frame].rz[STOPA2]+ludek[frame].rz[KOLANO2]);
    _RotY(nxx,nyy,nzz,ludek[frame].ry[STOPA2]+ludek[frame].ry[KOLANO2]);
    _RotX(nxx,nyy,nzz,ludek[frame].rx[STOPA2]+ludek[frame].rx[KOLANO2]);
}

void Narta_prawa(int r1)
{
    glPushMatrix();
    glTranslatef(nxx+xpos_L4+rxx, nyy+ypos_L4+ryy, nzz+zpos_L4+rzz);
    glRotatef(ludek[frame].rx[STOPA2]+ludek[frame].rx[KOLANO2]+ludek[frame].rx[NARTA2],1,0,0);
    glRotatef(ludek[frame].ry[STOPA2]+ludek[frame].ry[KOLANO2]+ludek[frame].ry[NARTA2],0,1,0);
    glRotatef(ludek[frame].rz[STOPA2]+ludek[frame].rz[KOLANO2]+ludek[frame].rz[NARTA2],0,0,1);
    QUAD(Procent(szer_3,75),0,0,
         Procent(szer_3,75)+szer_2,0,0,
         Procent(szer_3,75)+szer_2,-0.03f,0,
         Procent(szer_3,75),-0.03f,0,
         Procent(wys_tulow,280),
         r1,r1,r1,r1,r1,r1);
    QUAD(Procent(szer_3,75),0,0,
         Procent(szer_3,75)+szer_2,0,0,
         Procent(szer_3,75)+szer_2,-0.03f,0,
         Procent(szer_3,75),-0.03f,0,
         -Procent(wys_tulow,180),
         r1,r1,r1,r1,r1,r1);
    glPopMatrix();
}
void Ustalanie_kata()
{
    float x1,x2;
    kat=0;
    doing=false;
    if (xpos2<mapa.dl_skoczni+10 && wybicie==false)
    {
        if (xpos2+1>3) {x1=mapa.skocznia[(int)xpos2+1-3];} 
               else {x1=mapa.skocznia[1];}
        if (xpos2<mapa.dl_skoczni-8) x2=mapa.skocznia[(int)xpos2+1+7]; else x2=mapa.skocznia[(int)mapa.dl_skoczni-2];
        kat=-(x1-x2)*35;
        if (xpos2>mapa.dl_skoczni-20) kat=5;
        if (kat<-60) kat=0;
        doing=true;
    }
    if (ladowanie==true || crash==true)
    {
        if (xpos2+5>3) {x1=mapa.teren[(int)xpos2+5-3];} 
               else {x1=mapa.teren[1];}
        if (xpos2<mapa.dl_terenu-12) x2=mapa.teren[(int)xpos2+5+7]; else x2=mapa.teren[(int)mapa.dl_terenu-2];
        if (lad==true) kat=-(x1-x2)*25;
		if (lad==false) kat=-(x1-x2)*25;
        kat=kat+5;
        if (kat<-60) kat=0;
        doing=true;
    }
	
}