//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include "glm/glm.h"
#include <time.h>
#include <FreeImage.h>

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
	cwc::glShaderManager SM;
	GLuint ProgramObject;
	clock_t time0, time1;
	float timer010;  // timer counting 0->1->0
	bool bUp;        // flag if counting up or down.
	GLMmodel *astronaut;
	GLMmodel *astronaut2;
	GLMmodel *MarsRover;
	GLMmodel *Satellite;
	GLMmodel *Spaceship;
	GLMmodel *sphere;
	GLMmodel *terreno;
	GLMmodel *sun;

	cwc::glShader* shader;
	cwc::glShader* shader1;
	cwc::glShader* shader2;
	cwc::glShader* shader3;
	cwc::glShader* shader4;
	cwc::glShader* shader5;
	cwc::glShader* shader6;
	cwc::glShader* shader7;


	GLuint texid;
	GLuint texid2;
	GLuint texid3;
	GLuint texid4;
	GLuint texid5;


public:
	myWindow(){}
	void initialize_textures(void)
	{
		//Textura nave espacial
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./models/Spaceship/Spaceship_BaseColor.png", 0),
			"./models/Spaceship/Spaceship_BaseColor.png"
		);  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
		FreeImage_Unload(pImage);

		//Textura Invernadero
		glGenTextures(1, &texid2);
		glBindTexture(GL_TEXTURE_2D, texid2);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		FIBITMAP* bitmap2 = FreeImage_Load(
			FreeImage_GetFileType("./models/Sphere/HDU_01.jpg", 0),
			"./models/Sphere/HDU_01.jpg");


		FIBITMAP* pImage2 = FreeImage_ConvertTo32Bits(bitmap2);
		int nWidth2 = FreeImage_GetWidth(pImage2);
		int nHeight2 = FreeImage_GetHeight(pImage2);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth2, nHeight2,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage2));
		FreeImage_Unload(pImage2);
		///////////////////////

		//Textura astronauta
		glGenTextures(1, &texid3);
		glBindTexture(GL_TEXTURE_2D, texid3);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		FIBITMAP* bitmap3 = FreeImage_Load(
			FreeImage_GetFileType("./models/astronaut/z2_Color_s.jpg", 0),
			"./models/astronaut/z2_Color_s.jpg");


		FIBITMAP* pImage3 = FreeImage_ConvertTo32Bits(bitmap3);
		int nWidth3 = FreeImage_GetWidth(pImage3);
		int nHeight3 = FreeImage_GetHeight(pImage3);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth3, nHeight3,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage3));
		FreeImage_Unload(pImage3);
		//***//

		//Textura Rover//
		glGenTextures(1, &texid4);
		glBindTexture(GL_TEXTURE_2D, texid4);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		FIBITMAP* bitmap4 = FreeImage_Load(
			FreeImage_GetFileType("./models/MarsRover/MMSEV_Color_v2s.png", 0),
			"./models/MarsRover/MMSEV_Color_v2s.png");


		FIBITMAP* pImage4 = FreeImage_ConvertTo32Bits(bitmap4);
		int nWidth4 = FreeImage_GetWidth(pImage4);
		int nHeight4 = FreeImage_GetHeight(pImage4);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth4, nHeight4,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage4));
		FreeImage_Unload(pImage4);



		//Textura Sun
		glGenTextures(1, &texid5);
		glBindTexture(GL_TEXTURE_2D, texid5);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		FIBITMAP* bitmap5 = FreeImage_Load(
			FreeImage_GetFileType("./models/sun/sun.jpg", 0),
			"./models/sun/sun.jpg");


		FIBITMAP* pImage5 = FreeImage_ConvertTo32Bits(bitmap5);
		int nWidth5 = FreeImage_GetWidth(pImage5);
		int nHeight5 = FreeImage_GetHeight(pImage5);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth5, nHeight5,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage5));
		FreeImage_Unload(pImage5);


		glEnable(GL_TEXTURE_2D);
	}


	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//timer010 = 0.09; //for screenshot!
		glPushMatrix();
		if (shader) shader->begin();
			glPushMatrix();
				glTranslatef(0.0, 2.8, 0.0);
				glRotatef(45.0, 1.0, 1.0, 1.0);
				glmDraw(Satellite, GLM_SMOOTH);
			glPopMatrix();
		if (shader) shader->end();

		if (shader1) shader1->begin();
			glPushMatrix();
			glRotatef(30.0, 1.0, 0.0, 0.0);
			glRotatef(45.0, 0.0, 1.0, 0.0);
			glTranslatef(0.0, -1.0, 0.0);
			glScalef(1.25, 1.25, 1.25);
			glBindTexture(GL_TEXTURE_2D, texid);
			glmDraw(Spaceship, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader1) shader1->end();

		if (shader2) shader2->begin();
			glPushMatrix();
			glTranslatef(2.25, 0.75, 0.5);
			glScalef(0.75, 0.75, 0.75);
			glRotatef(30.0, 1.0, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, texid2);
			glmDraw(sphere, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader2) shader2->end();

		if (shader3) shader3->begin();
			glPushMatrix();
			glScalef(0.75, 0.75, 0.75);
			glRotatef(30.0, 1.0, 0.0, 0.0);
			glRotatef(45.0, 0.0, 1.0, 0.0);
			glTranslatef(3.0, 1.25, 1.0);
			glScalef(0.25, 0.25, 0.25);
			glBindTexture(GL_TEXTURE_2D, texid3);
			glmDraw(astronaut, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader3) shader3->end();

		if (shader4) shader4->begin();
			glPushMatrix();
			glScalef(0.25, 0.25, 0.25);
			glTranslatef(-10.0, -4.0, -2.0);
			glBindTexture(GL_TEXTURE_2D, texid4);
			glmDraw(MarsRover, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader4) shader4->end();

		if (shader5) shader5->begin();
			glPushMatrix();
			glRotatef(30.0, 1.0, 0.0, 0.0);
			glRotatef(45.0, 0.0, 1.0, 0.0);
			glTranslatef(1.25, -2.0, 1.0);
			glScalef(0.5, 0.5, 0.5);
			glBindTexture(GL_TEXTURE_2D, texid3);
			glmDraw(astronaut, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader5) shader5->end();

		if (shader6) shader6->begin();
			glPushMatrix();
			glRotatef(30.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0, 0.0, 0.0);
			glScalef(10.0, 10.0, 10.0);
			glmDraw(terreno, GLM_SMOOTH);
			glPopMatrix();
		if (shader6) shader6->end();


		if (shader7) shader7->begin();
			glPushMatrix();
			glScalef(0.25, 0.25, 0.25);
			glTranslatef(4.25, 6.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, texid5);
			glmDraw(sun, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
			glPopMatrix();
		if (shader7) shader7->end();


		glutSwapBuffers();
		glPopMatrix();
		UpdateTimer();
		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!

	virtual void OnInit()
	{
		glClearColor(0.0, 0.0, 0.2, 0.0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		sun = NULL;
		if (!sun)
		{
			sun = glmReadOBJ("./models/sun/SunTEXTURE.obj");
			if (!sun)
				exit(0);
			glmUnitize(sun);
			glmFacetNormals(sun);
			glmVertexNormals(sun, 90.0);
		}

		sphere = NULL;
		if (!sphere)
		{
			sphere = glmReadOBJ("./models/Sphere/Sphere.obj");
			if (!sphere)
				exit(0);
			glmUnitize(sphere);
			glmFacetNormals(sphere);
			glmVertexNormals(sphere, 90.0);
		}


		MarsRover = NULL;
		if (!MarsRover)
		{
			MarsRover = glmReadOBJ("./models/MarsRover/MarsRover.obj");
			if (!MarsRover)
				exit(0);
			glmUnitize(MarsRover);
			glmFacetNormals(MarsRover);
			glmVertexNormals(MarsRover, 90.0);
		}


		Satellite = NULL;
		if (!Satellite)
		{
			Satellite = glmReadOBJ("./models/Satellite/Satellite.obj");
			if (!Satellite)
				exit(0);
			glmUnitize(Satellite);
			glmFacetNormals(Satellite);
			glmVertexNormals(Satellite, 90.0);
		}
		
		Spaceship = NULL;
		if (!Spaceship)
		{
			Spaceship = glmReadOBJ("./models/Spaceship/Spaceship.obj");
			if (!Spaceship)
				exit(0);
			glmUnitize(Spaceship);
			glmFacetNormals(Spaceship);
			glmVertexNormals(Spaceship, 90.0);
		}

		astronaut = NULL;
		if (!astronaut)
		{
			astronaut = glmReadOBJ("./models/astronaut/astronaut.obj");
			if (!astronaut)
				exit(0);
			glmUnitize(astronaut);
			glmFacetNormals(astronaut);
			glmVertexNormals(astronaut, 90.0);
		}


		astronaut2 = NULL;
		if (!astronaut2)
		{
			astronaut2 = glmReadOBJ("./models/astronaut/astronaut.obj");
			if (!astronaut2)
				exit(0);
			glmUnitize(astronaut2);
			glmFacetNormals(astronaut2);
			glmVertexNormals(astronaut2, 90.0);
		}

		terreno = NULL;
		if (!terreno)
		{
			terreno = glmReadOBJ("./models/terreno.obj");
				if (!terreno)
					exit(0);
			glmUnitize(terreno);
			glmFacetNormals(terreno);
			glmVertexNormals(terreno, 90.0);
		}


		shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt"); // load (and compile, link) from file
		if (shader == 0)
			std::cout << "Error Loading, compiling or linking shader satellite \n";
		else
		{
			ProgramObject = shader->GetProgramObject();
		}

		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader spaceship\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

		shader2 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader2 == 0)
			std::cout << "Error Loading, compiling or linking shader sphere\n";
		else
		{
			ProgramObject = shader2->GetProgramObject();
		}

		shader3 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader3 == 0)
			std::cout << "Error Loading, compiling or linking shader astro1\n";
		else
		{
			ProgramObject = shader3->GetProgramObject();
		}

		shader4 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader4 == 0)
			std::cout << "Error Loading, compiling or linking shader rover\n";
		else
		{
			ProgramObject = shader4->GetProgramObject();
		}

		shader5 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader5 == 0)
			std::cout << "Error Loading, compiling or linking shader astro2\n";
		else
		{
			ProgramObject = shader5->GetProgramObject();
		}

		shader6 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader6 == 0)
			std::cout << "Error Loading, compiling or linking shader astro2\n";
		else
		{
			ProgramObject = shader6->GetProgramObject();
		}

		shader7 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader7 == 0)
			std::cout << "Error Loading, compiling or linking shader sun\n";
		else
		{
			ProgramObject = shader7->GetProgramObject();
		}

		time0 = clock();
		timer010 = 0.0f;
		bUp = true;

		initialize_textures();
		DemoLight();

	}

	virtual void OnResize(int w, int h)
	{
		if (h == 0) h = 1;
		float ratio = 1.0f * (float)w / (float)h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glViewport(0, 0, w, h);

		gluPerspective(90, ratio, 1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, 4.0f,
			0.0, 0.0, -1.0,
			0.0f, 1.0f, 0.0f);
	}
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		if (cAscii == 's')      // s: Shader
			shader->enable();
		else if (cAscii == 'f') // f: Fixed Function
			shader->disable();
	}

	void UpdateTimer()
	{
		time1 = clock();
		float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
		delta = delta / 4;
		if (delta > 0.00005f)
		{
			time0 = clock();
			if (bUp)
			{
				timer010 += delta;
				if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
			}
			else
			{
				timer010 -= delta;
				if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
			}
		}
	}

	void DemoLight(void)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		// Light model parameters:
		// -------------------------------------------

		GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

		// -------------------------------------------
		// Spotlight Attenuation

		GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
		GLint spot_exponent = 30;
		GLint spot_cutoff = 180;

		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
		glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

		GLfloat Kc = 1.0;
		GLfloat Kl = 0.0;
		GLfloat Kq = 0.0;

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


		// ------------------------------------------- 
		// Lighting parameters:

		GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
		GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
		GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

		// -------------------------------------------
		// Material parameters:

		GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
		GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
		GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
		GLfloat material_Se = 20.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
	}
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() { std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

