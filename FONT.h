#ifndef __FONT_GG_
#define __FONT_GG_

# include <gl\gl.h>
#include <stdio.h>



// **********************************************
class GLFont
{
	public:
		GLFont();
		~GLFont();
		void SetTexture(GLuint Tex, int xCount, int yCount);
		void SetFontProperties(int Width, int Height, int Spacing);
		void SetDisplayMode(int dWidth, int dHeight);
		void SetBase(int Base);
		GLvoid KillFont(GLvoid);
		GLvoid BuildFont();
		GLvoid Print(GLint x, GLint y, int texture,char *string,...);
	
	
	private:
		GLuint fTexture[1];
		GLuint fBase;
		int    fWidth;
		int    fHeight;
		int    fSpacing; 
		int    fStartPos;
		int    fxCount;
		int    fyCount;
		int    fdWidth;
		int    fdHeight;

};

int Resolution_X, Resolution_Y;

// **********************************************
GLFont::GLFont() // Caractéristique de la police
{
	
	fWidth = 15;
	fHeight = 15;
	fSpacing = 10; 
	fxCount = 15;
	fyCount = 15;
	fdWidth = Resolution_X;
	fdHeight = Resolution_Y;
	fStartPos = 0;

}


// **********************************************
GLFont::~GLFont() // Destructeur
{
	
	KillFont();

}


// **********************************************
GLvoid GLFont::KillFont(GLvoid) // On détruit la police
{
	
	glDeleteLists(fBase,fxCount * fyCount);		
	
}


// **********************************************
GLvoid GLFont::Print(GLint x, GLint y, int texture,char *string,...)
{
	char* str;
	va_list args;
    va_start(args,string);
	vsprintf(str,string,args);
    va_end(args);
	// On choisit la texture
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// On désactive le test de profondeur
	glDisable(GL_DEPTH_TEST);
	
	// On choisit la matrice de projection
	glMatrixMode(GL_PROJECTION);
	
	// On stocke la matrice
	glPushMatrix();
	
		// Reset des 3 axes
		glLoadIdentity();
		
		// On définit l'écran
		glOrtho(0,fdWidth,0,fdHeight,-1,1);	
		
		// On choisit la matrcie de visualisation
		glMatrixMode(GL_MODELVIEW);
		
		// On stocke la matrice
		glPushMatrix();
		
			// Reset des 3 axes
			glLoadIdentity();
			
			// Position du texte
			glTranslated(x,fdHeight - y,0);
			
			// On choisit le type de police
			glListBase(fBase - fStartPos);
			
			// On affiche le texte
			glCallLists(strlen(str),GL_BYTE,str);
			
			// On choisit la matrice de projection
			glMatrixMode(GL_PROJECTION);
		
		// On restaure la matrice
		glPopMatrix();	
		
		// On choisit la matrice de visualisation
		glMatrixMode(GL_MODELVIEW);
	
	// On restaure la matrice
	glPopMatrix();
	
	// On active le test de profondeur
	glEnable(GL_DEPTH_TEST);

}


// **********************************************
void GLFont::SetBase(int Base) // Base de la police
{
	
	fStartPos = Base;

}


// **********************************************
void GLFont::SetTexture(GLuint Tex, int xCount, int yCount) // La texture
{
	
	fTexture[0] = Tex;
	fxCount     = xCount;
	fyCount     = yCount;

}


// **********************************************
void GLFont::SetFontProperties(int Width, int Height, int Spacing) // Propriétés
{
	
	fWidth      = Width;
	fHeight     = Height;
	fSpacing    = Spacing;

}


// **********************************************
void GLFont::SetDisplayMode(int dWidth, int dHeight) // Type d'affichage
{

	fdWidth  = dWidth;
	fdHeight = dHeight;

}


// **********************************************
GLvoid GLFont::BuildFont() // Construction de la police d'affichage
{
	// Pour faire une boucle
	int     loop;
	
	// Coord. du caractère sur X
	float	cx;
	
	// Coord. du caractère sur Y
	float	cy;
    
	// Largeur du caractère sur X
	float   cwx;
	
	// Largeur du caractère sur Y
	float   cwy;

	cwx = (1.0f / 256.0f) * fWidth;
	cwy = (1.0f / 256.0f) * fHeight;
	
	// Création d'une liste d'affichage
	fBase = glGenLists(fxCount * fyCount);
	
	// On choisit la texture
	glBindTexture(GL_TEXTURE_2D, fTexture[0]);
	
	// On parcoure toute les listes d'affichage
	for (loop = 0; loop < (fxCount * fyCount); loop ++)
		{
			// Position courante du caractère sur X
			cx = float(loop % fxCount) * cwx;
			
			// Position courante du caractère sur Y
			cy = float(loop / fyCount) * cwy;

			// Début de la construction des listes d'affichage
			glNewList(fBase + loop,GL_COMPILE);
				glBegin(GL_QUADS); // Chaque caractère ...
					glTexCoord2f(cx,1-cy-cwy);
					glVertex2i(0,0);
					glTexCoord2f(cx+cwx,1-cy-cwy);
					glVertex2i(fWidth - 1,0);
					glTexCoord2f(cx+cwx,1-cy);
					glVertex2i(fWidth - 1,fHeight -1);
					glTexCoord2f(cx,1-cy);
					glVertex2i(0,fHeight -1);
				glEnd();
				glTranslated(fSpacing,0,0); // On se place au caractère suivant
			// Les listes d'affichage sont construites
			glEndList();
		}

}

#endif