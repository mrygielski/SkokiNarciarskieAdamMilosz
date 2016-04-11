

void INITALL()
{
	for (i=0;i<=ile_dymu;i++) dym[i].is=false;
	
	sky=gluNewQuadric();
	gluQuadricNormals(sky,GLU_NONE);
	gluQuadricTexture(sky,GL_TRUE); 	
    plik=Assign("data/skoczek.ani");
    read(plik,&ludek,sizeof(ludek));
    close(plik);
	

	SetTextures(true);

	myszY=windowY2;
/*
	randomize();
	for (i=0; i<(iledrzew*4)/5; i++)
	{
		tree[i].x=(float)Random(-20,(mapa.dl_skoczni-10)*0.1f);
		tree[i].y=mapa.skocznia[mapa.dl_skoczni-1]-2;
		
		while ((tree[i].z>-2) && (tree[i].z<2))
		{
		tree[i].z=-49.0f+(float)Random(0,98);
		}
		tree[i].wys=Random(0,1);
	}
	for (i=(iledrzew*4)/5; i<iledrzew; i++)
	{
		tree[i].x=Random((mapa.dl_terenu+10)*0.1f,((mapa.dl_terenu+10)*0.1f)+13);
		tree[i].y=mapa.teren[mapa.dl_terenu-1];
		
		while ((tree[i].z>-7) && (tree[i].z<7))
		{
		tree[i].z=-49.0f+(float)Random(0,98);
		}
		tree[i].wys=Random(0,1);
	}*/


	for (i=0; i<6; i++)
	{
		kibic[i].x=((mapa.dl_terenu+25)*0.1f);
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+2.25f;
		kibic[i].z=-4.5f+(i*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=6; i<12; i++)
	{
		kibic[i].x=(mapa.dl_terenu+35)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+2.5f;
		kibic[i].z=-4.5f+((i-6)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=12; i<18; i++)
	{
		kibic[i].x=(mapa.dl_terenu+45)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+2.75f;
		kibic[i].z=-4.5f+((i-12)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=18; i<24; i++)
	{
		kibic[i].x=(mapa.dl_terenu+55)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+3.0f;
		kibic[i].z=-4.5f+((i-18)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=24; i<30; i++)
	{
		kibic[i].x=(mapa.dl_terenu+65)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+3.25f;
		kibic[i].z=-4.5f+((i-24)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=30; i<36; i++)
	{
		kibic[i].x=(mapa.dl_terenu+75)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+3.5f;
		kibic[i].z=-4.5f+((i-30)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=36; i<42; i++)
	{
		kibic[i].x=(mapa.dl_terenu+85)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+3.75f;
		kibic[i].z=-4.5f+((i-36)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=42; i<48; i++)
	{
		kibic[i].x=(mapa.dl_terenu+95)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+4.0f;
		kibic[i].z=-4.5f+((i-42)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=48; i<54; i++)
	{
		kibic[i].x=(mapa.dl_terenu+105)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+4.25f;
		kibic[i].z=-4.5f+((i-48)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
	for (i=54; i<60; i++)
	{
		kibic[i].x=(mapa.dl_terenu+115)*0.1f;
		kibic[i].y=mapa.teren[mapa.dl_terenu-1]+4.5f;
		kibic[i].z=-4.5f+((i-54)*(1.75f+((Random(0,3)-1.5f)/10)))-0.5f;
		kibic[i].nr=4+Random(0,3);
	}
}


void Make_World(int k)
{
	if (k<=60) mapa.punkt=4.8f;
	if (k<100 && k>60) mapa.punkt=2.0f;
	if (k>=100 && k<150) mapa.punkt=1.8f;
	if (k>=150 && k>250) mapa.punkt=1.2f;
	wielkosc_sky=k+200;
	//
    // TWORZENIE SKOCZNI
    // 
    int temp;
	mapa.K=k;
    mapa.K35=mapa.K/140000;
    mapa.K53=(0.000175f-(((mapa.K-25)/1000000)));
    mapa.K2=mapa.K/2;
    mapa.K3=mapa.K/3;
    mapa.K4=mapa.K/4;
    mapa.K5=mapa.K/5;
    mapa.K6=mapa.K/6;
    mapa.dl_skoczni=mapa.K*3.3333f;// np.300=K*3.3333 czyli 300=90*3.3333
    mapa.dl_terenu=mapa.dl_skoczni*3;
	temp=mapa.dl_skoczni*2.6f;
	speed_min=temp;
    mapa.k_point=(/**/mapa.K/**/*4.0f)+mapa.dl_skoczni;
    mapa.r_point=(/**/(mapa.K-50)/**/*4.0f)+mapa.dl_skoczni;
	for (i=0;i<mapa.dl_skoczni;i++)
	{
		mapa.skocznia[i]=(float)sin((i/(mapa.dl_skoczni/3.0f))+1.8f)*((mapa.dl_skoczni/3.0f)/10.0f);
	}
    for (i=mapa.dl_skoczni;i<mapa.dl_terenu;i++)
    {
        mapa.teren[i]=mapa.skocznia[mapa.dl_skoczni-1]-(
        sin((i/(mapa.dl_skoczni/2.0f))+2.7f)*((mapa.dl_skoczni/2.0f)/10.0f));
        mapa.teren[i]-=((mapa.dl_skoczni/2.0f)/10.0f)+2;
    }
	for (i=temp;i<mapa.dl_terenu;i++)
    {
        mapa.teren[i]=mapa.teren[temp-1];
    }
	mapa.start=(int)Procent(mapa.dl_skoczni,85);
	length=mapa.dl_skoczni+mapa.dl_terenu+1000;
}

void Make_Teren()
{
	for (i=0;i<3500;i++) for (j=0;j<1000;j++) {teren[i][j]=Random(0,10)/10.0f;}
	//////////
	//// STANDARTOWA SKOCZNIA BEZ GÓREK
	for (i=0;i<mapa.dl_skoczni+420;i++) for (j=0;j<1000;j++) teren[i][j]=mapa.skocznia[mapa.dl_skoczni-1]-2.1f;
	for (i=mapa.dl_skoczni+420;i<mapa.dl_skoczni+mapa.dl_terenu+420;i++) for (j=0;j<1000;j++) teren[i][j]=mapa.teren[(i-(420))+1]-1.5f;
	if (length>6000) length=6000;
	for (i=mapa.dl_terenu+420;i<length;i++) for (j=0;j<1000;j++) teren[i][j]=mapa.teren[mapa.dl_terenu-1]-1.5f;
	///////////////////////////////////////////////////
	////////////
	////// BAJERY NA GORACH

	///////////////////////////////////////////////////
	for (i=1;i<length;i++) for (j=1;j<999;j++) 
	{
		ftemp=teren[i][j];//(((Random(0,8)-4)*0.9f))+teren[i][j];
		teren[i][j]=ftemp;
	}
	for (i=1;i<350;i++) for (j=1;j<999;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)+((350-i)/20.0f)+10.0f)+teren[i][j]+10;
		teren[i][j]=ftemp;
	}
	for (i=350;i<mapa.dl_skoczni+350;i++) for (j=700;j<999;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)+((350-i)/20.0f)+10.0f)+teren[i][j]+10;
		teren[i][j]=ftemp;
	}
	for (i=350;i<mapa.dl_skoczni+350;i++) for (j=1;j<300;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)+((350-i)/20.0f)+10.0f)+teren[i][j]+10;
		teren[i][j]=ftemp;
	}
	for (i=mapa.dl_skoczni+350;i<length;i++) for (j=1;j<100;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)-((350-i)/100.0f)+10.0f)+teren[i][j]+10;
		teren[i][j]=ftemp;
		teren[i][j+900]=ftemp;
	}
	for (i=mapa.dl_skoczni+350;i<length;i++) for (j=100;j<300;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)-((350-i)/100.0f)+10.0f)+teren[i][j]-((j-100)*0.1f);
		teren[i][j]=ftemp;
		teren[i][(300-j)+700]=ftemp;
	}
	for (i=330;i<mapa.dl_skoczni+350;i++) for (j=1;j<100;j++) 
	{
		ftemp=teren[mapa.dl_skoczni+351][j];
		teren[i][j]=ftemp;
		teren[i][j+900]=ftemp;
	}

	for (i=length-350;i<length;i++) for (j=100;j<900;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)-((350-i)/100.0f)+10.0f)+teren[i][j]-20+((i-(length-350))*0.08f);
		teren[i][j]=ftemp;
		
	}
	for (i=length-350;i<length;i++) for (j=300;j<700;j++) 
	{
		ftemp=(((Random(0,8)-4)*0.9f)-((350-i)/100.0f)+1.0f)+teren[i][j]-20+((i-(length-350))*0.06f)-10;
		teren[i][j]=ftemp;
		
	}
	///////////////////////////////////////////////////
	
	itemp=0;
	do
	{
	itemp2=Random(35,length-35);
	itemp3=Random(35,1000-35);
	ftemp=(Random(0,10)/3.2f);
	for (i=itemp2-35;i<itemp2+35;i++) for (j=itemp3-35;j<itemp3+35;j++) teren[i][j]=teren[i][j]+ftemp;
	itemp++;
	}
	while (itemp<1500);
	itemp=0;
	
	do
	{
	for (i=0;i<length-1;i+=1) 
	for (j=0;j<1000-1;j+=1) 
		teren[i][j]=(teren[i-1][j]+teren[i+1][j]+teren[i][j-1]+teren[i][j+1])/4;
	itemp++;
	}
	while (itemp<5);

	for (i=350;i<mapa.dl_skoczni+420;i++) for (j=400;j<600;j++) teren[i][j]=mapa.skocznia[mapa.dl_skoczni-1]-2.1f;
	for (i=mapa.dl_skoczni+420;i<mapa.dl_terenu+420;i++) for (j=340;j<660;j++) teren[i][j]=mapa.teren[(i-(420))+1]-0.5f;
	for (i=mapa.dl_terenu+420;i<length-((int)Procent(length-mapa.dl_terenu,25));i++) for (j=370;j<630;j++) teren[i][j]=mapa.teren[mapa.dl_terenu-1]-0.5f;
	for (i=0;i<length;i++) for (j=0;j<1000;j++) teren[i][j]-=0.0f;
	low=1000000.0f;
	for (i=0;i<length;i++) for (j=0;j<1000;j++) {if (teren[i][j]<low) low=teren[i][j];}
}


void Load_Textures()
{
    // textury dla skoczni
	texture[0]=LoadTexture("textures/snow.bmp",2,false);
	texture[1]=LoadTexture("textures/gray.bmp",2,true);
	texture[2]=LoadTexture("textures/yellow.bmp",2,true);
	texture[3]=LoadTexture("textures/reklama.bmp",2,true);
    texture[9]=LoadTexture("textures/snow2.bmp",2,true);
    texture[10]=LoadTexture("textures/clouds.bmp",2,true);
    texture[11]=LoadTexture("textures/terr1.bmp",2,true);
    texture[12]=LoadTexture("textures/snow3.bmp",2,true);
    texture[13]=LoadTexture("textures/kpoint.bmp",2,false);
    texture[14]=LoadTexture("textures/rpoint.bmp",2,false);
	texture[26]=LoadTexture("textures/linie.bmp",2,true);
//	texture[28]=LoadTexture("textures/ludek/cien.bmp",2,true);
	LoadTGAFile(&textureT[12],"textures/ludek/cien.tga",false,2);
	LoadTGAFile(&textureT[13],"textures/ludek/cien2.tga",false,2);
	LoadTGAFile(&textureT[14],"textures/snow1.tga",false,2);
    LoadTGAFile(&textureT[0],"textures/plotek.tga",false,2);
	//reklamy
	//texture[16]=LoadTexture("textures/reklamy/reklama1.bmp",2,false);
	texture[17]=LoadTexture("textures/reklamy/reklama2.bmp",2,false);
	texture[18]=LoadTexture("textures/reklamy/reklama3.bmp",2,false);
	texture[24]=LoadTexture("textures/reklamy/reklama4.bmp",2,false);
	texture[20]=LoadTexture("textures/reklamy/reklama5.bmp",2,false);
	texture[19]=LoadTexture("textures/reklamy/back.bmp",2,false);
	texture[25]=LoadTexture("textures/stadion/stadion.bmp",2,false);
	texture[27]=LoadTexture("textures/teren.bmp",1,true);
	texture[29]=LoadTexture("textures/reklamy/light.bmp",2,false);
	
	//textury dla domku
	texture[4]=LoadTexture("textures/buda/deska.bmp",2,true);
	texture[5]=LoadTexture("textures/buda/window.bmp",2,true);
	texture[6]=LoadTexture("textures/buda/roof.bmp",2,true);
	texture[7]=LoadTexture("textures/buda/slup.bmp",2,true);
	texture[8]=LoadTexture("textures/buda/deska2.bmp",2,true);
	//drzewa
	LoadTGAFile(&textureT[1],"textures/tree2.tga",false,2);
	//kibice
	LoadTGAFile(&textureT[4],"textures/kibice/kibice1.tga",false,2);
	LoadTGAFile(&textureT[5],"textures/kibice/kibice2.tga",false,2);
	LoadTGAFile(&textureT[6],"textures/kibice/kibice3.tga",false,2);
	LoadTGAFile(&textureT[7],"textures/kibice/kibice4.tga",false,2);
	LoadTGAFile(&textureT[8],"textures/noty.tga",false,2);
	LoadTGAFile(&textureT[9],"textures/dym.tga",false,2);
	LoadTGAFile(&textureT[10],"textures/reklamy/reklama1.tga",false,2);
	LoadTGAFile(&textureT[11],"textures/reklamy/reklama2.tga",false,2);
    //textury ludka
    textureL[0]=LoadTexture("textures/ludek/ryj.bmp",2,false);
	textureL[1]=LoadTexture("textures/ludek/bokglowy.bmp",2,false);
	textureL[2]=LoadTexture("textures/ludek/tylglowy.bmp",2,false);
	textureL[3]=LoadTexture("textures/ludek/goraglow.bmp",2,false);
	//textureL[4]=LoadTexture("texture5.bmp",2,false);
    textureL[5]=LoadTexture("textures/ludek/koszulka.bmp",2,false);
    textureL[6]=LoadTexture("textures/ludek/bar.bmp",2,false);
    textureL[7]=LoadTexture("textures/ludek/bok.bmp",2,false);
    textureL[8]=LoadTexture("textures/ludek/rekaw1.bmp",2,false);
    textureL[9]=LoadTexture("textures/ludek/rekaw2.bmp",2,false);
    textureL[10]=LoadTexture("textures/ludek/rekaw3.bmp",2,false);
    textureL[11]=LoadTexture("textures/ludek/rekaw4.bmp",2,false);
    textureL[12]=LoadTexture("textures/ludek/rekawica.bmp",2,false);
    textureL[13]=LoadTexture("textures/ludek/noga1.bmp",2,false);
    textureL[14]=LoadTexture("textures/ludek/noga2.bmp",2,false);
    textureL[15]=LoadTexture("textures/ludek/noga3.bmp",2,false);
    textureL[16]=LoadTexture("textures/ludek/noga4.bmp",2,false);
    textureL[17]=LoadTexture("textures/ludek/but.bmp",2,false);
    textureL[18]=LoadTexture("textures/ludek/narta.bmp",2,false);
}