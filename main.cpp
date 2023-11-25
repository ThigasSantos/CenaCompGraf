#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <cmath>

GLfloat rSun= 255 ,gSun=255 ,bSun= 0 		//Cor do sol
,rSky= 173, gSky= 216, bSky= 230			//Cor do ceu
,rWindow= 255, gWindow= 255, bWindow= 255;		//Cor da janela
GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco
bool DrawClouds = true; // Desenha as nuvens
bool DrawStars = false; // Desenha as estrelas

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(-10, 10,-10 , 10,-10,10);
    
    glEnable(GL_BLEND);    //Ativar o alpha do glColor
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Ativa pixels aritmeticos

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Background(){
	glBegin(GL_QUADS);
		glColor3ub(rSky,gSky,bSky);			//Plano de fundo
		glVertex2f(-10.0,10.0);
		glVertex2f(-10.0,-10.0);
		glVertex2f(10.0,-10.0);
		glVertex2f(10.0,10.0);
	glEnd();	
}

void Sun(float centerX, float centerY) {
    glColor3ub(rSun, gSun, bSun); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Centro do círculo

    int segments = 100;
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float radius = 1.0f;
        float x = centerX + radius * std::cos(theta);
        float y = centerY + radius * std::sin(theta);
        glVertex2f(x, y);
    }

    glEnd();
}

void Cloud(float x, float y, float radius, int numCircles, float incX, float incY) {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    for (int i = 0; i < numCircles; ++i) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Centro do círculo

        int segments = 100;
        for (int j = 0; j <= segments; ++j) {
            float theta = 2.0f * M_PI * static_cast<float>(j) / static_cast<float>(segments);
            float x_i = x + radius * std::cos(theta);
            float y_i = y + radius * std::sin(theta);
            glVertex2f(x_i, y_i);
        }

        glEnd();

        // Ajusta as coordenadas para o próximo círculo
        x += incX;
        y -= incY;
    }
}

void GrassBg(){
	glBegin(GL_QUADS);
		glColor3ub(0,100,0);			//Plano de fundo
		glVertex2f(-10.0,2.0);
		glVertex2f(-10.0,-10.0);
		glVertex2f(10.0,-10.0);
		glVertex2f(10.0,2.0);
	glEnd();	
}

void Road() {
    // Desenha a faixa de rodagem (um retângulo cinza)
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glBegin(GL_QUADS);
    glVertex2f(-10.0f, -4.0f); // Canto inferior esquerdo
    glVertex2f(10.0f, -4.0f);  // Canto inferior direito
    glVertex2f(10.0f, -10.0f);   // Canto superior direito
    glVertex2f(-10.0f, -10.0f);  // Canto superior esquerdo
    glEnd();

    // Desenha as marcações da estrada (linhas brancas)
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    float lineY = -7.0f;
    for (float x = -10.0f; x <= 10.0f; x += 1.0f) {
        glVertex2f(x, lineY);
        glVertex2f(x + 0.4f, lineY);
    }
    glEnd();
    glLineWidth(1.0f);
}

void Star(float x, float y, float radius) {
    const float pi = 3.14159265358979323846;
    const float angle = pi / 5.0f; // Ângulo entre os raios da estrela

    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro da estrela

    for (int i = 0; i < 10; ++i) {
        float currentAngle = i * 2.0f * angle;
        float xPos = x + radius * std::cos(currentAngle);
        float yPos = y + radius * std::sin(currentAngle);
        glVertex2f(xPos, yPos);

        currentAngle += angle;
        xPos = x + (radius / 2.0f) * std::cos(currentAngle);
        yPos = y + (radius / 2.0f) * std::sin(currentAngle);
        glVertex2f(xPos, yPos);
    }

    glEnd();
}

void House() {
    // Desenha o corpo da casa 
    glColor3f(0.7f, 0.7f, 0.7f); // Cinza
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 1.5f); 
    glVertex2f(4.0f, -1.0f);  
    glVertex2f(6.0f, -1.0f);   
    glVertex2f(6.0f, 1.5f);  
    glEnd();

    // Desenha o telhado 
    glColor3f(0.8f, 0.2f, 0.2f); // Vermelho
    glBegin(GL_TRIANGLES);
    glVertex2f(4.0f, 1.5f);  
    glVertex2f(5.0f, 3.0f);   
    glVertex2f(6.0f, 1.5f);   
    glEnd();

    // Desenha a porta 
    glColor3f(0.4f, 0.2f, 0.0f); // Marrom
    glBegin(GL_QUADS);
    glVertex2f(4.5f, -1.0f); 
    glVertex2f(5.0f, -1.0f);  
    glVertex2f(5.0f, 0.2f);   
    glVertex2f(4.5f, 0.2f);  
    glEnd();

    // Desenha a janela
    glColor3ub(rWindow, gWindow, bWindow); 
    glBegin(GL_QUADS);
    glVertex2f(5.2f, 0.0f);  
    glVertex2f(5.2f, 0.6f);  
    glVertex2f(5.8f, 0.6f);   
    glVertex2f(5.8f, 0.0f);   
    glEnd();

	//Desenha contorno da janela
	glColor3f(0.0f, 0.0f, 0.0f); // Preto
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(5.2f, 0.0f);
	glVertex2f(5.2f, 0.6f);
	glVertex2f(5.8f, 0.6f);
	glVertex2f(5.8f, 0.0f);
	glEnd();

	//Desenha meio da janela
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glVertex2f(5.2f, 0.3f);
	glVertex2f(5.8f, 0.3f);
	glVertex2f(5.5f, 0.0f);
	glVertex2f(5.5f, 0.6f);
	glEnd();

	//Desenha contorno da porta
	glColor3f(0.0f, 0.0f, 0.0f); // Preto
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(4.5f, -1.0f);
	glVertex2f(5.0f, -1.0f);
	glVertex2f(5.0f, 0.2f);
	glVertex2f(4.5f, 0.2f);
	glEnd();
}

void Tree(float x, float y, float trunkHeight, float trunkWidth, float foliageHeight, float foliageWidth) {
    // Desenha o tronco
    glColor3f(0.4f, 0.2f, 0.0f); // Marrom escuro
    glBegin(GL_QUADS);
    glVertex2f(x - trunkWidth / 2, y);               // Canto inferior esquerdo
    glVertex2f(x + trunkWidth / 2, y);               // Canto inferior direito
    glVertex2f(x + trunkWidth / 2, y + trunkHeight); // Canto superior direito
    glVertex2f(x - trunkWidth / 2, y + trunkHeight); // Canto superior esquerdo
    glEnd();

    // Desenha a copa da árvore
    glColor3f(0.0f, 0.5f, 0.0f); // Verde escuro
    glBegin(GL_TRIANGLES);
    glVertex2f(x - foliageWidth / 2, y + trunkHeight);  // Canto inferior esquerdo
    glVertex2f(x, y + trunkHeight + foliageHeight);     // Pico
    glVertex2f(x + foliageWidth / 2, y + trunkHeight);  // Canto inferior direito
    glEnd();
}

void Lake(float x, float y, float widthTop, float widthBottom, float height, int numSegments) {
    // Desenha a água do lago
    glColor3f(0.0f, 0.5f, 1.0f); // Azul claro

    // Desenha bordas arredondadas
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * M_PI * i / numSegments;
        float radius = (widthTop + widthBottom) / 4.0f;
        float px = x + radius * cos(theta);
        float py = y + height / 2 + radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * M_PI * i / numSegments;
        float radius = (widthTop + widthBottom) / 4.0f;
        float px = x + radius * cos(theta);
        float py = y - height / 2 - radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}

void Bush(float x, float y, float radius, int numLeaves) {
    glColor3f(0.0f, 0.8f, 0.0f); // Verde claro para as folhas

    for (int i = 0; i < numLeaves; ++i) {
        float angle = (i / static_cast<float>(numLeaves)) * 2.0f * M_PI;
        float leafX = x + radius * cos(angle);
        float leafY = y + radius * sin(angle);

        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 15) {
            float leafAngle = j * M_PI / 180.0f;
            float leafRadius = 0.3f * radius; // Ajuste o fator para controlar o tamanho das folhas
            glVertex2f(leafX + leafRadius * cos(leafAngle), leafY + leafRadius * sin(leafAngle));
        }
        glEnd();
    }
}

void TrafficLight(float x, float y) {
    // Poste do semáforo
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y);          // Canto inferior esquerdo
    glVertex2f(x + 0.1f, y);          // Canto inferior direito
    glVertex2f(x + 0.1f, y + 2.0f);    // Canto superior direito
    glVertex2f(x - 0.1f, y + 2.0f);    // Canto superior esquerdo
    glEnd();

    // Luz vermelha
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        float px = x + 0.0f + 0.05f * cos(angle);
        float py = y + 1.8f + 0.05f * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();

    // Luz amarela
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        float px = x + 0.0f + 0.05f * cos(angle);
        float py = y + 1.3f + 0.05f * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();

    // Luz verde
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        float px = x + 0.0f + 0.05f * cos(angle);
        float py = y + 0.8f + 0.05f * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();
}

void ToggleSun(){
	if(rSun == 255 && gSun == 255 && bSun == 0)
	{
		rSun = 71; gSun = 74; bSun = 81;
	}else
	{
		rSun = 255; gSun = 255; bSun = 0;
	}
}

void ToggleCloudsStar(){
	DrawClouds = !DrawClouds;
	DrawStars = !DrawStars;
}

void ToggleSky(){
	if(rSky == 173 && gSky == 216 && bSky == 230)
	{
		rSky = 18; gSky = 10; bSky = 143;
	}else
	{
		rSky = 173; gSky = 216; bSky = 230;
	}
}

void ToggleWindow(){
	if(rWindow == 255 && gWindow == 255 && bWindow == 255)
	{
		rWindow = 255; gWindow = 255; bWindow = 0;
	}else
	{
		rWindow = 255; gWindow = 255; bWindow = 255;
	}
}

void ToggleNight(){
	
	ToggleSun();
	ToggleCloudsStar();
	ToggleSky();
	ToggleWindow();
}	

void Draw(){
	Background();
	Sun(7.0f, 7.0f);
	if(DrawClouds)
	{
		Cloud(-2.0f, 7.0f, 0.5f, 4, 0.6f, 0.2f); 
		Cloud(-7.0f, 5.0f, 0.5f, 3, 0.6f, 0.2f); 
		Cloud(2.0f, 5.0f, 0.5f, 4, 0.6f, 0.2f); 
	}
	if(DrawStars)
	{
		Star(-9.0f, 7.0f, 0.3f);
		Star(-7.0f, 6.0f, 0.2f);
		Star(-6.0f, 8.0f, 0.1f);
		Star(-5.0f, 7.0f, 0.1f);
		Star(-4.0f, 9.0f, 0.2f);
		Star(-3.0f, 7.0f, 0.3f);
		Star(-2.0f, 6.0f, 0.1f);
		Star(-1.0f, 7.0f, 0.2f);
		Star(0.0f, 8.0f, 0.1f);
		Star(1.0f, 9.0f, 0.1f);
		Star(2.0f, 8.0f, 0.2f);
		Star(3.0f, 6.0f, 0.3f);
		Star(4.0f, 8.0f, 0.1f);
		Star(5.0f, 9.0f, 0.2f);
		Star(6.0f, 6.0f, 0.1f);
	}
	GrassBg();
	Road();
	House();

    Bush(0.0f, -2.0f, 0.3f, 10);
    Tree(0.0f, -2.0f, 1.5f, 0.3f, 3.0f, 1.5f);
    Bush(-8.0f, 0.0f, 0.2f, 10);
    Tree(-8.0f, 0.0f, 1.0f, 0.1f, 2.0f, 1.0f);
    Bush(7.0f, -1.0f, 0.3f, 10);
    Tree(7.0f, -1.0f, 1.2f, 0.2f, 2.5f, 1.2f);
    Bush(-4.0f, 0.0f, 0.2f, 10);
    Tree(-4.0f, 0.0f, 1.0f, 0.1f, 2.0f, 1.0f);

    glPushMatrix();
    glRotatef(50.0f, -6.0f, 1.0f, 1.0f);
    Lake(-6.0f, 0.0f, 2.0f, 3.0f, 0.7f, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0f, -4.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    TrafficLight(0.0f, 0.0f);
    glPopMatrix();
}

void display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE);
	
	Draw();

	glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		case 27:
			exit ( 0 );
			break;		
		case 'Q':
		case 'q':
			ToggleNight();
			break;							
		default:
			return;
	}
	glutPostRedisplay();	//atualizar informacao da janela
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	else		
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
	else
	return;
		
	glutPostRedisplay();
}

int  main ( int argc, char** argv )
{
    glutInit ( &argc, argv );	//Usada apra iniciar o ambiente Glut
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutCreateWindow ("Projeto Final"); 
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (0, 0);
    init();
    glutDisplayFunc (display);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse);
    glutMainLoop ( );
    return 0;
}
