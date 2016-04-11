void Get_FPS(int &fPs)
{
	float Fps;
	static float framesPerSecond    = 0.0f;							// This will store our fps
	static float lastTime			= 0.0f;							// This will hold the time from the last frame
	static char strFrameRate[50] = {0};								// We will store the string here for the window title
	float currentTime = GetTickCount() * 0.001f;				
	framesPerSecond+=4;
	if( currentTime - lastTime >= 0.25f )
	{
		lastTime = currentTime;
		Fps=framesPerSecond;
		framesPerSecond = 0;
		fPs=Fps;
	}
}

void Draw_SKY()
{
	glPushMatrix();
	glTranslatef(10,25,0);
	glRotatef(90,1,0,0);
	glRotatef(0,0,1,0);
	glRotatef(sky_rot,0,0,1);
	sky_rot+=0.2f;
	glColor3ub(255,255,255);
	glBindTexture(GL_TEXTURE_2D,texture[10]);	 
	
	glPolygonMode(GL_FRONT,GL_POINT);	
	gluSphere(sky,wielkosc_sky,4,4);
	glPolygonMode(GL_FRONT,GL_FILL);
	glPopMatrix();
}
void BarT2(float x1,float y1,float z1,
		  float x2,float y2,float z2,
		  float x3,float y3,float z3,
		  float x4,float y4,float z4,int r,int g, int b,int a,int text)
{

	glColor4ub(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.99f,0.01f);glVertex3f(x2,y2,z2);
		glTexCoord2f(0.99f,0.99f);glVertex3f(x1,y1,z1);
		glTexCoord2f(0.01f,0.01f);glVertex3f(x3,y3,z3);
		glTexCoord2f(0.01f,0.99f);glVertex3f(x4,y4,z4);
	glEnd();

}

void Rysuj_Skocznie(Tmapa map)
{	
	for (i=-7;i<1;i++)
	{
		ftemp=-x01f[-i];//i*0.1f;
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT2(
			 ftemp+0.1f,map.skocznia[0],-1.0f,
			 ftemp+0.1f,map.skocznia[0]-2,-1.0f,
			 ftemp,map.skocznia[0]-2,-1.0f,
             ftemp,map.skocznia[0],-1.0f,
			 255,255,255,255,texture[1]);		
		BarT2(ftemp,map.skocznia[0],1.0f,
			 ftemp+0.1f,map.skocznia[0],1.0f,
			 ftemp+0.1f,map.skocznia[0],-1.0f,
			 ftemp,map.skocznia[0],-1.0f,
			 255,255,255,255,texture[0]);
		glPolygonMode( GL_FRONT, GL_FILL);
        glPolygonMode( GL_BACK, GL_POINT);
		BarT2(
			 ftemp+0.1f,map.skocznia[0],1,
			 ftemp+0.1f,map.skocznia[0]-2,1,
			 ftemp,map.skocznia[0]-2,1,ftemp,map.skocznia[0],1,
			 255,255,255,255,texture[1]);		
        glPolygonMode( GL_BACK, GL_FILL);		
        glPolygonMode( GL_BACK, GL_POINT);
        BarT2(ftemp,map.skocznia[0]-2,1,
			 ftemp+0.1f,map.skocznia[0]-2,1,
			 ftemp+0.1f,map.skocznia[0]-2,-1,
			 ftemp,map.skocznia[0]-2,-1,
			 255,255,255,255,texture[1]);
		glPolygonMode( GL_BACK, GL_FILL);	
    }
	for (i=1;i<map.dl_skoczni;i++)
	{
		ftemp=x01f[i];//i*0.1f;
		glPolygonMode( GL_BACK, GL_POINT);
		BarT2(
			 ftemp+0.1f,map.skocznia[i],1,
			 ftemp+0.1f,map.skocznia[i]-2,1,
			 ftemp,map.skocznia[i-1]-2,1,ftemp,map.skocznia[i-1],1,
			 255,255,255,255,texture[1]);		
		glPolygonMode( GL_BACK, GL_FILL);
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT2(
			 ftemp+0.1f,map.skocznia[i],-1,
			 ftemp+0.1f,map.skocznia[i]-2,-1,
			 ftemp,map.skocznia[i-1]-2,-1,
             ftemp,map.skocznia[i-1],-1,
			 255,255,255,255,texture[1]);		
		BarT2(ftemp,map.skocznia[i-1],1,
			 ftemp+0.1f,map.skocznia[i],1,
			 ftemp+0.1f,map.skocznia[i],-1,
			 ftemp,map.skocznia[i-1],-1,
			 255,255,255,255,texture[0]);
		glPolygonMode( GL_FRONT, GL_FILL);
        glPolygonMode( GL_BACK, GL_POINT);
        BarT2(ftemp,map.skocznia[i-1]-2,1,
			 ftemp+0.1f,map.skocznia[i]-2,1,
			 ftemp+0.1f,map.skocznia[i]-2,-1,
			 ftemp,map.skocznia[i-1]-2,-1,
			 255,255,255,255,texture[1]);
		glPolygonMode( GL_BACK, GL_FILL);		

	}
	ftemp=x01f[map.dl_skoczni];
	glPolygonMode( GL_BACK, GL_POINT);
	BarT2(ftemp,map.skocznia[map.dl_skoczni-1],-1,
		 ftemp,map.skocznia[map.dl_skoczni-1]-2,-1,
		 ftemp,map.skocznia[map.dl_skoczni-1]-2,1,
		 ftemp,map.skocznia[map.dl_skoczni-1],1,
		 255,255,255,255,texture[3]);
	glPolygonMode( GL_BACK, GL_FILL);	
	
	
	for (i=0;i<11;i++)
	{
		if (map.slupy[i].alive==false) break;
		ftemp=x01f[map.slupy[i].X];
		glPolygonMode( GL_BACK, GL_POINT);
		BarT2(ftemp-0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,0.25f,
			  ftemp-0.5f,map.skocznia[map.slupy[i].X]-1,0.25f,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-1,0.25f,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,0.25f,
			  255,255,255,255,texture[2]);		
		BarT2(ftemp+0.5f,map.skocznia[map.slupy[i].X]-1,0.25f,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-1,-0.25,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,-0.25,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,0.25f,			  
			  255,255,255,255,texture[2]);
		glPolygonMode( GL_BACK, GL_FILL);
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT2(ftemp-0.5f,map.skocznia[map.slupy[i].X]-1,0.25f,
			  ftemp-0.5f,map.skocznia[map.slupy[i].X]-1,-0.25,
			  ftemp-0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,-0.25,
			  ftemp-0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,0.25f,
			  255,255,255,255,texture[2]);
		BarT2(ftemp-0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,-0.25f,
			  ftemp-0.5f,map.skocznia[map.slupy[i].X]-1,-0.25f,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-1,-0.25f,
			  ftemp+0.5f,map.skocznia[map.slupy[i].X]-map.slupy[i].H,-0.25f,
			  255,255,255,255,texture[2]);
		glPolygonMode( GL_FRONT, GL_FILL);
	}
}
void Rysuj_Domek(Tmapa map)
{
	glTranslatef(-0.6f,0,0);
	// s³up
	glPolygonMode( GL_BACK, GL_POINT);
	BarT2(-2.f,map.skocznia[0],1,
		 -0.1f,map.skocznia[0],1,
		 -0.1f,map.skocznia[map.dl_skoczni-1]-2,1,
		 -2.f,map.skocznia[map.dl_skoczni-1]-2,1,
		 255,255,255,255,texture[7]);
	BarT2(-2,map.skocznia[0],-1,
		 -2,map.skocznia[0],1,
		 -2,map.skocznia[map.dl_skoczni-1]-2,1,
		 -2,map.skocznia[map.dl_skoczni-1]-2,-1,
		 255,255,255,255,texture[7]);	
	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_POINT);
	BarT2(-2.f,map.skocznia[0],-1,
		 -0.1f,map.skocznia[0],-1,
		 -0.1f,map.skocznia[map.dl_skoczni-1]-2,-1,
		 -2.f,map.skocznia[map.dl_skoczni-1]-2,-1,
		 255,255,255,255,texture[7]);
	BarT2(-0.1f,map.skocznia[0],-1,
		 -0.1f,map.skocznia[0],1,
		 -0.1f,map.skocznia[map.dl_skoczni-1]-2,1,
		 -0.1f,map.skocznia[map.dl_skoczni-1]-2,-1,
		 255,255,255,255,texture[7]);
	glPolygonMode( GL_FRONT, GL_FILL);
	
	// domek
	glPolygonMode( GL_BACK, GL_POINT);
	BarT2(-2.2f,map.skocznia[0],1.2f,
		 0.1f,map.skocznia[0],1.2f,
		 0.1f,map.skocznia[0],-1.2f,
		 -2.2f,map.skocznia[0],-1.2f,
		 255,255,255,255,texture[4]);
	
	BarT2(-2.2f,map.skocznia[0]+2,-1.2f,
		 -2.2f,map.skocznia[0],-1.2f,
		 0.1f,map.skocznia[0],-1.2f,
		 0.1f,map.skocznia[0]+2,-1.2f,
		 255,255,255,255,texture[4]);
	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_POINT);
	BarT2(-2.2f,map.skocznia[0]+2,1.2f,
		 -2.2f,map.skocznia[0],1.2f,
		 0.1f,map.skocznia[0],1.2f,
		 0.1f,map.skocznia[0]+2,1.2f,
		 255,255,255,255,texture[4]);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_POINT);
	BarT2(-2.2f,map.skocznia[0]+2,1.2f,
		 -2.2f,map.skocznia[0],1.2f,
		 -2.2f,map.skocznia[0],-1.2f,
		 -2.2f,map.skocznia[0]+2,-1.2f,
		 255,255,255,255,texture[4]);
	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_POINT);
	BarT2(0.1f,map.skocznia[0]+2,1.2f,
		 0.1f,map.skocznia[0],1.2f,
		 0.1f,map.skocznia[0],-1.2f,
		 0.1f,map.skocznia[0]+2,-1.2f,
		 255,255,255,255,texture[8]);
	glPolygonMode( GL_FRONT, GL_FILL);

	//okna i drzwi	
	glPolygonMode( GL_FRONT, GL_POINT);
	BarT2(-0.5f,map.skocznia[0]+0.5f,1.21f,
		 -0.5f,map.skocznia[0]+1.5f,1.21f,
		 -1.5f,map.skocznia[0]+1.5f,1.21f,
		 -1.5f,map.skocznia[0]+0.5f,1.21f,
		 255,255,255,255,texture[5]);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_POINT);
	BarT2(-0.5f,map.skocznia[0]+0.5f,-1.21f,
		 -0.5f,map.skocznia[0]+1.5f,-1.21f,
		 -1.5f,map.skocznia[0]+1.5f,-1.21f,
		 -1.5f,map.skocznia[0]+0.5f,-1.21f,
		 255,255,255,255,texture[5]);
	glPolygonMode( GL_BACK, GL_FILL);

    //dach domka
    BarT2(-1.05f,map.skocznia[0]+4,0.0f,
           0.3f,map.skocznia[0]+1.8f,1.4f,
		  -2.4f,map.skocznia[0]+1.8f,1.4f,
          -1.05f,map.skocznia[0]+4,0.0f,
           255,255,255,255,texture[6]);
    BarT2(-1.05f,map.skocznia[0]+4,0,
           0.3f,map.skocznia[0]+1.8f,-1.4f,
		  -2.4f,map.skocznia[0]+1.8f,-1.4f,
          -1.05f,map.skocznia[0]+4,0,
           255,255,255,255,texture[6]);
    BarT2(-1.05f,map.skocznia[0]+4,0,
           0.3f,map.skocznia[0]+1.8f,1.4f,
		   0.3f,map.skocznia[0]+1.8f,-1.4f,
          -1.05f,map.skocznia[0]+4,0,
           255,255,255,255,texture[6]);
    BarT2(-1.05f,map.skocznia[0]+4,0,
          -2.4f,map.skocznia[0]+1.8f,1.4f,
		  -2.4f,map.skocznia[0]+1.8f,-1.4f,
          -1.05f,map.skocznia[0]+4,0,
           255,255,255,255,texture[6]);
    
}

void Rysuj_Teren(Tmapa map)
{
	
    for (i=map.dl_skoczni+6;i<map.dl_terenu-1;i+=2)
    {
    	ftemp=x01f[i+1];
		ftemp2=(i+1)*0.01f-5;
		ftemp3=(i-1)*0.01f-5;
		glPolygonMode( GL_BACK, GL_POINT);
		glPolygonMode( GL_FRONT, GL_FILL);
		BarT2(ftemp-0.1f,map.teren[i-1],-2-ftemp3-1,
			  ftemp+0.1f,map.teren[i+1],-2-ftemp2-1,
			  ftemp+0.1f,map.teren[i+1],2+ftemp2+1,
			  ftemp-0.1f,map.teren[i-1],2+ftemp3+1,              
			  255,255,255,255,texture[9]);
		BarT2(ftemp-0.1f,map.teren[i-1],-2-ftemp3-1.3f,
			  ftemp+0.1f,map.teren[i+1],-2-ftemp2-1.3f,
			  ftemp+0.1f,map.teren[i+1],-2-ftemp2-1,
			  ftemp-0.1f,map.teren[i-1],-2-ftemp3-1,              
			  255,255,255,255,texture[26]);
		glPolygonMode( GL_BACK, GL_FILL);
		glPolygonMode( GL_FRONT, GL_POINT);
		BarT2(ftemp-0.1f,map.teren[i-1],2+ftemp3+1.3f,
			  ftemp+0.1f,map.teren[i+1],2+ftemp2+1.3f,
			  ftemp+0.1f,map.teren[i+1],2+ftemp2+1,
			  ftemp-0.1f,map.teren[i-1],2+ftemp3+1,              
			  255,255,255,255,texture[26]);
    }
	glPolygonMode( GL_BACK, GL_POINT);
	glPolygonMode( GL_FRONT, GL_FILL);
}

void Rysuj_Swiat(Tmapa mapa)
{
	glPushMatrix();
	glEnable(GL_FOG);
	SetTextures(true);
	ftemp=x01f[mapa.dl_terenu];
	ftemp2=(mapa.dl_terenu-1)*0.01f-1.7f;

	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_FILL);
	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.2f,
          ftemp,mapa.teren[mapa.dl_terenu-1],-ftemp2-0.2f,
          ftemp,mapa.teren[mapa.dl_terenu-1],-ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2,
          255,255,255,100,texture[25]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
          ftemp-0.1f,mapa.teren[mapa.dl_terenu-1],-ftemp2-0.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1],-ftemp2-0.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
          255,255,255,100,texture[25]);

	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2-0.2f,
          ftemp,mapa.teren[mapa.dl_terenu-1],ftemp2-0.2f,
          ftemp,mapa.teren[mapa.dl_terenu-1],ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2,
          255,255,255,100,texture[25]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2-0.1f,
          ftemp-0.1f,mapa.teren[mapa.dl_terenu-1],ftemp2-0.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1],ftemp2-0.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2-0.1f,
          255,255,255,100,texture[25]);

	//light
	glBlendFunc(GL_SRC_ALPHA,1);
	glEnable(GL_BLEND); 
	BarT2(ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
          ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+9.0f,-ftemp2+5.1f,
          ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+6.0f,-ftemp2+5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,-ftemp2-0.1f,
          255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+9.0f,-ftemp2+5.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+6.0f,-ftemp2+5.1f,
          ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,-ftemp2-0.1f,
          255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+9.0f,-ftemp2+5.1f,
		  ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+9.0f,-ftemp2+5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,-ftemp2-0.1f,
		  255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,-ftemp2-0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+6.0f,-ftemp2+5.1f,
		  ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+6.0f,-ftemp2+5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,-ftemp2-0.1f,
		  255,255,255,100,texture[29]);

	BarT2(ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2+0.1f,
          ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+9.0f,ftemp2-5.1f,
          ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+6.0f,ftemp2-5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,ftemp2+0.1f,
          255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2+0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+9.0f,ftemp2-5.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+6.0f,ftemp2-5.1f,
          ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,ftemp2+0.1f,
          255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2+0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+9.0f,ftemp2-5.1f,
		  ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+9.0f,ftemp2-5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+8.75f,ftemp2+0.1f,
		  255,255,255,100,texture[29]);
	BarT2(ftemp-0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,ftemp2+0.1f,
          ftemp-1.9f,mapa.teren[mapa.dl_terenu-1]+6.0f,ftemp2-5.1f,
		  ftemp+1.1f,mapa.teren[mapa.dl_terenu-1]+6.0f,ftemp2-5.1f,
          ftemp+0.1f,mapa.teren[mapa.dl_terenu-1]+7.75f,ftemp2+0.1f,
		  255,255,255,100,texture[29]);
	glDisable(GL_BLEND);
	glDisable(GL_FOG);
	glPopMatrix();
}


void Rysuj_Linie(Tmapa map)
{
    i=(int)map.k_point;
    if (i<map.dl_terenu)
    {
    ftemp=map.k_point*0.1f;
	ftemp2=i*0.01f-5;
	ftemp3=(i-1)*0.01f-5;
    BarT2(ftemp,map.teren[i-1]+0.03f,-2-ftemp3-1,
          ftemp+0.1f,map.teren[i]+0.03f,-2-ftemp2-1,
		  ftemp+0.1f,map.teren[i]+0.03f,2+ftemp2+1,
		  ftemp,map.teren[i-1]+0.03f,2+ftemp3+1,              
		  255,255,255,255,texture[13]);
    }
	if (i>=map.dl_terenu) return;
    i=(int)map.r_point;
	ftemp2=i*0.01f-5;
	ftemp3=(i-1)*0.01f-5;
    ftemp=map.r_point*0.1f;
    BarT2(ftemp,map.teren[i-1]+0.03f,-2-ftemp3-1,
          ftemp+0.1f,map.teren[i]+0.03f,-2-ftemp3-1,
		  ftemp+0.1f,map.teren[i]+0.03f,2+ftemp3+1,
		  ftemp,map.teren[i-1]+0.03f,2+ftemp3+1,              
		  255,255,255,255,texture[14]);
}

void DrawSkiJumper(float x2, float y2, float z2)
{
	glEnable(GL_FOG);
    glScalef(1.5f,1,1);
    HEAD(0,y+(wys_glowa+wys_tulow),0.025f,0.018f,0.024f,0.05f,textureL[0],textureL[1],textureL[2],textureL[3]);
    BODY(0,y+(wys_tulow),0.025f,0.1f,0.228f,0.05f,textureL[5],textureL[5],textureL[6],textureL[7]);
    Ramie_lewe(textureL[8],textureL[9],textureL[10],textureL[11],textureL[12]);
    Ramie_prawe(textureL[8],textureL[9],textureL[10],textureL[11],textureL[12]);
    Noga_lewa(textureL[13],textureL[14],textureL[15],textureL[16],textureL[17]);
    Narta_lewa(textureL[18]);
    Noga_prawa(textureL[13],textureL[14],textureL[15],textureL[16],textureL[17]);
    Narta_prawa(textureL[18]);
	glDisable(GL_FOG);
    SetTextures(true);
}

void Rysuj_Wiatr()
{
    glPushMatrix();
    SetTextures(false);
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef(-5.35f,-4,-10);
	glBlendFunc(0,GL_SRC_COLOR);
	glEnable(GL_BLEND); 
    glBegin(GL_QUADS);        
        glColor4ub(155,100,0,255);glVertex3f(0,0,0);
        glColor4ub(155,0,0,255);glVertex3f(0,1,0);
        glColor4ub(155,0,0,255);glVertex3f(1,1,0);
        glColor4ub(155,100,0,255);glVertex3f(1,0,0);
    glEnd();
	glDisable(GL_BLEND); 
    
    glBegin(GL_LINES);
     glColor3ub(255,255,255);
     glVertex3f(0.5f,0.6f,0.01f);
     glVertex3f(0.5f,0.4f,0.01f);
     glColor3ub(0,0,255);
     glVertex3f(0.5f,0.5f,0.01f);
     glVertex3f(0.5f+(wiatr/8),0.5f,0.01f);
     if (wiatr>0)
     {
       glVertex3f(0.5f+(wiatr/8),0.5f,0.01f);
       glVertex3f(0.5f+(wiatr/8)-0.1f,0.4f,0.01f);
       glVertex3f(0.5f+(wiatr/8),0.5f,0.01f);
       glVertex3f(0.5f+(wiatr/8)-0.1f,0.6f,0.01f);
     }
     if (wiatr<0)
     {
       glVertex3f(0.5f+(wiatr/8),0.5f,0.01f);
       glVertex3f(0.5f+(wiatr/8)+0.1f,0.4f,0.01f);
       glVertex3f(0.5f+(wiatr/8),0.5f,0.01f);
       glVertex3f(0.5f+(wiatr/8)+0.1f,0.6f,0.01f);
     }
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    SetTextures(true);
}

void Rysuj_Wysokosc()
{
    glPushMatrix();
    SetTextures(false);
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef(10,-8,-20);

	glBlendFunc(0,GL_SRC_COLOR);
	glEnable(GL_BLEND); 
    glBegin(GL_QUADS);        
        glColor4ub(155,100,0,255);glVertex3f(-0.6f,-0.1f,0);
        glColor4ub(255,255,255,0);glVertex3f(-0.6f,5,0);
        glColor4ub(255,255,255,0);glVertex3f(0.6f,5,0);
        glColor4ub(155,100,0,255);glVertex3f(0.6f,-0.1f,0);
    glEnd();
	glDisable(GL_BLEND); 
	//glScalef(1,2.0f,1);
    glColor3ub(0,255,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,wysokosc,0);
        glColor3ub(0,0,255);
        glVertex3f(-0.5f,0,0);
        glVertex3f(0.5f,0,0);
        glColor3ub(240,0,0);
        glVertex3f(-0.5f,0.4f,0);
        glVertex3f(0.5f,0.4f,0);
        glColor3ub(200,0,0);
        glVertex3f(-0.5f,0.2f,0);
        glVertex3f(0.5f,0.2f,0);
        if (landing>-1)
        {
            glColor3ub(13,240,150);
            glVertex3f(-0.5f,landing,0);
            glVertex3f(0.5f,landing,0);
        }
	//glScalef(1,0.5f,1);
    glEnd();
	glLoadIdentity();
    glTranslatef(0,-7.6f,-20);

	glBlendFunc(0,GL_SRC_COLOR);
	glEnable(GL_BLEND); 
    glBegin(GL_QUADS);        
        glColor4ub(255,255,255,255);  glVertex3f(2,0.4f,0);
        glColor4ub(255,255,255,255);  glVertex3f(2,-0.5f,0);
        glColor4ub(155,100,0,255);    glVertex3f(8.6f,-0.5f,0);
        glColor4ub(155,100,0,255);    glVertex3f(8.6f,0.4f,0);
    glEnd();
	glDisable(GL_BLEND);
	
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	  glVertex3f(8.5f,-0.5f,0);
	  glVertex3f(8.5f,0.4f,0);
	  glColor3ub(0,0,255);
	  glVertex3f(8.5f,-0.05f,0);
	  glVertex3f(8.5f-(prog/100),-0.05f,0);
	glEnd();
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    SetTextures(true);
}


void Rysuj_Stadion()
{
	ftemp=x01f[mapa.dl_terenu]+1;
	glPolygonMode( GL_BACK, GL_POINT);
	SetTextures(true);
	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,6,
          ftemp,mapa.teren[mapa.dl_terenu-1],6,
          ftemp,mapa.teren[mapa.dl_terenu-1],-6,
          ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,-6,
          255,255,255,100,texture[19]);
	BarT2(ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1],6,
		  ftemp,mapa.teren[mapa.dl_terenu-1],6,
          ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,6,
          255,255,255,100,texture[19]);
	BarT2(ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,-6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,6,
		  ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,6,
          ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,-6,
          255,255,255,100,texture[25]);
	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_POINT);
	BarT2(ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,-6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1],-6,
		  ftemp,mapa.teren[mapa.dl_terenu-1],-6,
          ftemp,mapa.teren[mapa.dl_terenu-1]+1.75f,-6,
          255,255,255,100,texture[19]);
	BarT2(ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1],6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1],-6,
          ftemp+12,mapa.teren[mapa.dl_terenu-1]+5.0f,-6,
          255,255,255,100,texture[19]);
	glPolygonMode( GL_FRONT, GL_FILL);
}

void Drzewo(float x, float y, float z, int wielkosc)
{
	BarT2(x,y+3.4f,z,
		 x,y,z,
		 x+2,y,z,
		 x+2,y+3.4f,z,255,255,255,255,textureT[1].texID);
	BarT2(x+1.0f,y+3.4f,z+1.0f,
		 x+1.0f,y,z+1.0f,
		 x+1.0f,y,z-1.0f,
		 x+1.0f,y+3.4f,z-1.0f,255,255,255,255,textureT[1].texID);
}

void PokazDrzewa()
{
	SetTextures(true);
	for (i=0; i<iledrzew; i++)
	{
		Drzewo(tree[i].x,tree[i].y,tree[i].z, tree[i].wys);
	}
}

void Kibic(float x, float y, float z, int nr)
{
	BarT2(x,y+1.2f,z,
		 x,y,z,
		 x,y,z+1.2f,
		 x,y+1.2f,z+1.2f,255,255,255,255,textureT[nr].texID);
}

void RysujKibicow()
{
	SetTextures(true);
	glPushMatrix();
	glTranslatef(x01f[mapa.dl_terenu],mapa.teren[mapa.dl_terenu-1],0);
	for (i=0; i<ilekibicow; i++)
	{
		Kibic(kibic[i].x,kibic[i].y,kibic[i].z,kibic[i].nr);
	}
	glPopMatrix();
}

void Rysuj_gory(int detale,float ftemp4,int itemp)
{
	glBindTexture(GL_TEXTURE_2D,texture[27]);
	glPolygonMode( GL_BACK, GL_FILL);
	glPolygonMode( GL_FRONT, GL_POINT);
	glBegin(GL_QUADS);
	
	for (i=itemp+itemp;i<length-itemp;i+=detale)
	for (j=itemp+itemp;j<1000-itemp;j+=detale)
	{
		ftemp=x01f[i]-42.0f;//x
		ftemp2=x01f[j]-50.0f;//z
		ftemp3=teren[i][j];//y
		
		kolor=1-((ftemp3-low)*0.0075f);
		glColor3f(kolor,kolor,kolor);
		// pierwszy kwadrat
		glTexCoord2f(0.99f,0.99f);glVertex3f(ftemp-ftemp4,teren[i-itemp][j-itemp],ftemp2-ftemp4);
		glTexCoord2f(0.99f,0.01f);glVertex3f(ftemp,teren[i][j-itemp],ftemp2-ftemp4);
		glTexCoord2f(0.01f,0.01f);glVertex3f(ftemp,teren[i][j],ftemp2);
		glTexCoord2f(0.01f,0.99f);glVertex3f(ftemp-ftemp4,teren[i-itemp][j],ftemp2);

		// drugi kwadrat
		glTexCoord2f(0.99f,0.99f);glVertex3f(ftemp,teren[i][j-itemp],ftemp2-ftemp4);
		glTexCoord2f(0.99f,0.01f);glVertex3f(ftemp+ftemp4,teren[i+itemp][j-itemp],ftemp2-ftemp4);
		glTexCoord2f(0.01f,0.01f);glVertex3f(ftemp+ftemp4,teren[i+itemp][j],ftemp2);
		glTexCoord2f(0.01f,0.99f);glVertex3f(ftemp,teren[i][j],ftemp2);

		// trzeci kwadrat
		glTexCoord2f(0.99f,0.99f);glVertex3f(ftemp,teren[i][j],ftemp2);
		glTexCoord2f(0.99f,0.01f);glVertex3f(ftemp+ftemp4,teren[i+itemp][j],ftemp2);
		glTexCoord2f(0.01f,0.01f);glVertex3f(ftemp+ftemp4,teren[i+itemp][j+itemp],ftemp2+ftemp4);
		glTexCoord2f(0.01f,0.99f);glVertex3f(ftemp,teren[i][j+itemp],ftemp2+ftemp4);
		
		// czwarty kwadrat
		glTexCoord2f(0.99f,0.99f);glVertex3f(ftemp-ftemp4,teren[i-itemp][j],ftemp2);
		glTexCoord2f(0.99f,0.01f);glVertex3f(ftemp,teren[i][j],ftemp2);
		glTexCoord2f(0.01f,0.01f);glVertex3f(ftemp,teren[i][j+itemp],ftemp2+ftemp4);
		glTexCoord2f(0.01f,0.99f);glVertex3f(ftemp-ftemp4,teren[i-itemp][j+itemp],ftemp2+ftemp4);
		
	}
	glEnd();
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_FILL);
}

void Rysuj_noty()
{
	glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef(0,0,-10);
	glBlendFunc(0,GL_SRC_COLOR);
	glEnable(GL_BLEND); 
	SetTextures(true);
    BarT2(-0.3f,-2,0,
		 0.3f,-2,0,
		 0.3f,-2.5f,0,
		 -0.3f,-2.5f,0,255,255,255,255,textureT[8].texID);
	BarT2(-0.6f,-2,0,
		 -1.2f,-2,0,
		 -1.2f,-2.5f,0,
		 -0.6f,-2.5f,0,255,255,255,255,textureT[8].texID);
	BarT2(-1.5f,-2,0,
		 -2.1f,-2,0,
		 -2.1f,-2.5f,0,
		 -1.5f,-2.5f,0,255,255,255,255,textureT[8].texID);
	BarT2(0.6f,-2,0,
		 1.2f,-2,0,
		 1.2f,-2.5f,0,
		 0.6f,-2.5f,0,255,255,255,255,textureT[8].texID);
	BarT2(1.5f,-2,0,
		 2.1f,-2,0,
		 2.1f,-2.5f,0,
		 1.5f,-2.5f,0,255,255,255,255,textureT[8].texID);
	BarT2(-2.1f,-2.6f,0,
		 2.1f,-2.6f,0,
		 2.1f,-2.9f,0,
		 -2.1f,-2.9f,0,255,255,255,255,textureT[8].texID);
	glDisable(GL_BLEND); 
	piszTXT(-2.0f,-2.6f,0.15f,0.2f,0.35f,255,150,0, fonttexture.texID,"%s",imie);
	piszTXT(0.4f,-2.6f,0.15f,0.2f,0.35f,255,255,0, fonttexture.texID,"%.1f",odleglosc);
	piszTXT(1.3f,-2.6f,0.15f,0.2f,0.35f,0,255,0, fonttexture.texID,"%.1f",punkty_all);
	
	for (i=1;i<=5;i++) if (punkty[i]>20.0f) punkty[i]=20.0f;
	for (i=1;i<=5;i++) if (punkty[i]<0.0f) punkty[i]=1.0f;
	
	for (i=1;i<=5;i++) if (wsk[i]<1 || wsk[i]>5) wsk[i]=1;

	if (czyshow[1]==true && czyshow[2]==true && czyshow[3]==true && czyshow[4]==true && czyshow[5]==true)
	{
	 if (czyshow[wsk[1]]==true) piszTXT(iksy[wsk[1]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[1]]);
	 if (czyshow[wsk[2]]==true) piszTXT(iksy[wsk[2]],-2.1f,0.1f,0.3f,0.35f,255,0,0, fonttexture.texID,"%.1f",punkty[wsk[2]]);
	 if (czyshow[wsk[3]]==true) piszTXT(iksy[wsk[3]],-2.1f,0.1f,0.3f,0.35f,255,0,0, fonttexture.texID,"%.1f",punkty[wsk[3]]);
	 if (czyshow[wsk[4]]==true) piszTXT(iksy[wsk[4]],-2.1f,0.1f,0.3f,0.35f,255,0,0, fonttexture.texID,"%.1f",punkty[wsk[4]]);
	 if (czyshow[wsk[5]]==true) piszTXT(iksy[wsk[5]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[5]]);
	}
	else
	{
	 if (czyshow[wsk[1]]==true) piszTXT(iksy[wsk[1]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[1]]);
	 if (czyshow[wsk[2]]==true) piszTXT(iksy[wsk[2]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[2]]);
	 if (czyshow[wsk[3]]==true) piszTXT(iksy[wsk[3]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[3]]);
	 if (czyshow[wsk[4]]==true) piszTXT(iksy[wsk[4]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[4]]);
	 if (czyshow[wsk[5]]==true) piszTXT(iksy[wsk[5]],-2.1f,0.1f,0.3f,0.35f,255,255,0, fonttexture.texID,"%.1f",punkty[wsk[5]]);
	}
	
    if (punkty_all==0 && czyshow[1]==true && czyshow[2]==true && czyshow[3]==true && czyshow[4]==true && czyshow[5]==true)
	{
		punkty_all=60.0f;
		punkty_all+=((odleglosc-(float)mapa.K)*mapa.punkt);
		punkty_all+=(punkty[wsk[2]]+punkty[wsk[3]]+punkty[wsk[4]]);
	}

	if (sortok==0)
	{
		zalicz[1]=punkty[1];zalicz[2]=punkty[2];zalicz[3]=punkty[3];zalicz[4]=punkty[4];zalicz[5]=punkty[5];
		for (j=1;j<=5;j++)
		for (i=4;i>0;i--)
		{
			if (zalicz[i]>zalicz[i+1]) 
			{
				ftemp=zalicz[i];
				itemp=wsk[i];
				zalicz[i]=zalicz[i+1];
				wsk[i]=wsk[i+1];
				zalicz[i+1]=ftemp;
				wsk[i+1]=itemp;
			}
		}
		sortok=1;
	}
	if (czyshow[1]==false && Random(0,50)==21) czyshow[1]=true; 
	if (czyshow[2]==false && Random(0,50)==21) czyshow[2]=true;
	if (czyshow[3]==false && Random(0,50)==21) czyshow[3]=true;
	if (czyshow[4]==false && Random(0,50)==21) czyshow[4]=true;
	if (czyshow[5]==false && Random(0,50)==21) czyshow[5]=true;


	glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void Rysuj_dym(float size)
{
	SetTextures(true);
	glBlendFunc(GL_ONE_MINUS_SRC_COLOR,1);
	glEnable(GL_BLEND);
	for (i=1;i<=ile_dymu;i++)
	 if (dym[i].is==true) 
	 {
		glAlphaFunc(GL_GREATER, dym[i].color);
		glPolygonMode( GL_BACK, GL_FILL);
		glPolygonMode( GL_FRONT, GL_FILL);
		BarT2(dym[i].x-size,dym[i].y-size,dym[i].z,
			  dym[i].x+size,dym[i].y-size,dym[i].z,
			  dym[i].x+size,dym[i].y+size,dym[i].z,
			  dym[i].x-size,dym[i].y+size,dym[i].z,
			  255,255,255,255,textureT[9].texID);
		BarT2(dym[i].x,dym[i].y-size,dym[i].z-size,
			  dym[i].x,dym[i].y-size,dym[i].z+size,
			  dym[i].x,dym[i].y+size,dym[i].z+size,
			  dym[i].x,dym[i].y+size,dym[i].z-size,
			  255,255,255,255,textureT[9].texID);
		dym[i].color+=0.01f;
		dym[i].y+=0.005f;
		dym[i].x+=(Random(0,2)-1)*0.01f;
		dym[i].z+=(Random(0,2)-1)*0.01f;
		if (dym[i].color>=0.95f) dym[i].is=false;
	 } 
	glAlphaFunc(GL_GREATER, 0.0f);
	glDisable(GL_BLEND);
}

void Rysuj_reklamy()
{
	SetTextures(true);
	ftemp=x01f[mapa.dl_terenu];
	ftemp2=(mapa.dl_terenu-1)*0.01f-1.7f;
	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+2.75f,ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1],ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1],-ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1]+2.75f,-ftemp2,
          255,255,255,100,textureT[10].texID);
	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+1.25f,-ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1],-ftemp2,
          ftemp-5,mapa.teren[mapa.dl_terenu-1],-ftemp2,
		  ftemp-5,mapa.teren[mapa.dl_terenu-1]+1.25f,-ftemp2,
          255,255,255,100,texture[17]);
	BarT2(ftemp-5,mapa.teren[mapa.dl_terenu-1]+1.25f,-ftemp2,
          ftemp-5,mapa.teren[mapa.dl_terenu-1],-ftemp2,
          ftemp-10,mapa.teren[mapa.dl_terenu-1],-ftemp2,
		  ftemp-10,mapa.teren[mapa.dl_terenu-1]+1.25f,-ftemp2,
          255,255,255,100,texture[18]);
	BarT2(ftemp,mapa.teren[mapa.dl_terenu-1]+2.75f,ftemp2,
          ftemp,mapa.teren[mapa.dl_terenu-1],ftemp2,
          ftemp-5,mapa.teren[mapa.dl_terenu-1],ftemp2,
		  ftemp-5,mapa.teren[mapa.dl_terenu-1]+2.75f,ftemp2,
          255,255,255,100,textureT[11].texID);
	BarT2(ftemp-5,mapa.teren[mapa.dl_terenu-1]+2.75f,ftemp2,
          ftemp-5,mapa.teren[mapa.dl_terenu-1],ftemp2,
          ftemp-10,mapa.teren[mapa.dl_terenu-1],ftemp2,
		  ftemp-10,mapa.teren[mapa.dl_terenu-1]+2.75f,ftemp2,
          255,255,255,100,textureT[11].texID);
	
}

void Rysuj_cien_gracza(Tmapa map)
{

	if (i>=map.dl_terenu) return;
    i=(int)xpos2;
	
	
	ftemp=xpos2*0.1f;

	glEnable(GL_BLEND);
	glBlendFunc(0,GL_SRC_COLOR);
    BarT2(ftemp-0.25f,map.teren[i-5]+0.03f,-0.3f,
          ftemp+0.75f,map.teren[i+5]+0.03f,-0.3f,
		  ftemp+0.75f,map.teren[i+5]+0.03f,0.3f,
		  ftemp-0.25f,map.teren[i-5]+0.03f,0.3f,
		  255,255,255,255,textureT[nrcienia].texID);
	glDisable(GL_BLEND);

}








