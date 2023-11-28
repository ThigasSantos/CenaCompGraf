#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <cmath>

GLfloat x = 0.0
,rTLR = 211 ,gTLR = 211,bTLR = 211
,rTLG = 0 ,gTLG = 255 ,bTLG = 0   //Cores do sinal
,rSun= 255 ,gSun=255 ,bSun= 0 		//Cor do sol
,rSky= 173, gSky= 216, bSky= 230			//Cor do ceu
,rWindow= 255, gWindow= 255, bWindow= 255;		//Cor da janela
bool DrawClouds = true; // Desenha as nuvens
bool DrawStars = false; // Desenha as estrelas
bool noRed = true;  //Sinal Vermelho

void init(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(-10, 10,-10 , 10,-10,10);
    
    glEnable(GL_BLEND);    //Ativar o alpha do glColor
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Ativa pixels aritmeticos

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Quads(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y); // Canto inferior esquerdo
    glVertex2f(x + width, y); // Canto inferior direito
    glVertex2f(x + width, y + height); // Canto superior direito
    glVertex2f(x, y + height); // Canto superior esquerdo
    glEnd();
}

void Circle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro do círculo
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float dx = radius * std::cos(theta);
        float dy = radius * std::sin(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void Background(){		    
    glColor3ub(rSky,gSky,bSky);			//Plano de fundo
    Quads(-10.0f, -10.0f, 20.0f, 20.0f);	//Desenha o plano de fundo
}

void Cloud(float x, float y, float radius, int numCircles, float incX, float incY) {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    for (int i = 0; i < numCircles; ++i) {
        Circle(x, y, radius, 100);
        // Ajusta as coordenadas para o próximo círculo
        x += incX;
        y -= incY;
    }
}

void GrassBg(){
    glColor3ub(0,100,0);
	Quads(-10.0f, -4.0f, 20.0f, 6.0f);
}

void Road() {
    // Desenha a faixa de rodagem (um retângulo cinza)
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    Quads(-10.0f, -10.0f, 20.0f, 6.0f);

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
    Quads(4.0f, -1.0f, 2.0f, 2.5f);

    // Desenha o telhado 
    glColor3f(0.8f, 0.2f, 0.2f); // Vermelho
    glBegin(GL_TRIANGLES);
    glVertex2f(4.0f, 1.5f);  
    glVertex2f(5.0f, 3.0f);   
    glVertex2f(6.0f, 1.5f);   
    glEnd();

    // Desenha a porta 
    glColor3f(0.4f, 0.2f, 0.0f); // Marrom
    Quads(4.5f, -1.0f, 0.5f, 1.2f);

    // Desenha a janela
    glColor3ub(rWindow, gWindow, bWindow); 
    Quads(5.2f, 0.0f, 0.6f, 0.6f);

	//Desenha contorno da janela
	glColor3f(0.0f, 0.0f, 0.0f); // Preto
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(5.2f, 0.0f);
	glVertex2f(5.2f, 0.6f);
	glVertex2f(5.8f, 0.6f);
	glVertex2f(5.8f, 0.0f);
	glEnd();
	
	//Ilumina��o noturna
	if(DrawStars){
		glColor4f(1.0,1.0,0,0.3);
		glBegin(GL_POLYGON);
		glVertex2f(5.2,0.6f);
		glVertex2f(5.8f, 0.6f);
		glVertex2f(6.2,-1.2);
		glVertex2f(4.8,-1.2);
		glEnd();
	}
	
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
    Quads(x - trunkWidth / 2, y, trunkWidth, trunkHeight);
    
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
    Circle(x, y, widthTop / 2.0f, numSegments);
    Circle(x, y - height, widthBottom / 2.0f, numSegments);
}

void Bush(float x, float y, float radius, int numLeaves) {
    glColor3f(0.0f, 0.8f, 0.0f); // Verde claro para as folhas

    for (int i = 0; i < numLeaves; ++i) {
        float angle = (i / static_cast<float>(numLeaves)) * 2.0f * M_PI;
        float leafX = x + radius * cos(angle);
        float leafY = y + radius * sin(angle);

        Circle(leafX, leafY, radius, 100);
    }
}

void Sun(float centerX, float centerY){
    glColor3ub(rSun, gSun, bSun); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Centro do círculo

    Circle(centerX, centerY, 1.0f, 100);

    glEnd();
}

void TrafficLight(float x, float y){
    // Poste do semáforo
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    Quads(x, y, 0.5f, 3.0f);

    // Luz vermelha
    glColor3ub(rTLR,gTLR,bTLR);
    Circle(x + 0.25f, y + 2.7f, 0.15f, 100);

    // Luz verde
    glColor3f(rTLG,gTLG,bTLG);
    Circle(x+ 0.25f, y + 2.3f, 0.15f, 100);
}

void Car(float x, float y){
    // Desenha o corpo do carro
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glBegin(GL_POLYGON);
    glVertex2f(x, y);          // Canto inferior esquerdo
    glVertex2f(x + 2.0f, y);          // Canto inferior direito
    glVertex2f(x + 2.0f, y + 1.0f);    // Canto medio direito
    glVertex2f(x + 1.5f, y + 1.0f);    // Canto superior medio direito
    glVertex2f(x + 1.5f, y + 1.5f);     // Canto superior direito 
    glVertex2f(x + 0.5f, y + 1.5f);     // Canto superior esquerdo
    glVertex2f(x, y + 1.0f);    // Canto medio esquerdo
    glEnd();

    //Contorno do carro
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);          // Canto inferior esquerdo
    glVertex2f(x + 2.0f, y);          // Canto inferior direito
    glVertex2f(x + 2.0f, y + 1.0f);    // Canto medio direito
    glVertex2f(x + 1.5f, y + 1.0f);    // Canto superior medio direito
    glVertex2f(x + 1.5f, y + 1.5f);     // Canto superior direito
    glVertex2f(x + 0.5f, y + 1.5f);     // Canto superior esquerdo
    glVertex2f(x, y + 1.0f);    // Canto medio esquerdo
    glEnd();

    // Desenha as rodas
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    Circle(x + 0.5f, y, 0.25f, 100);        // Roda esquerda
    Circle(x + 1.5f, y, 0.25f, 100);        // Roda direita

    //Aro da roda
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    Circle(x + 0.5f, y, 0.1f, 100);        // Roda esquerda
    Circle(x + 1.5f, y, 0.1f, 100);        // Roda direita

    // Desenha o vidro
    glColor3f(0.0f, 1.0f, 1.0f); // Azul claro
    Quads(x + 1.0f, y + 1.0f, 0.5f, 0.45f);

    // Desenha o farol
    glColor3f(rWindow, gWindow, bWindow);
    Circle(x + 1.9f, y + 0.8f, 0.1f, 100);
    
    //Ilumina��o Noturna
    if(DrawStars){
    	glColor4f(1.0,1.0,0.0,0.2);
    	glBegin(GL_TRIANGLES);
    	glVertex2f(x+1.9,y+0.8);
    	glVertex2f(x+2.8,y+1.4);
    	glVertex2f(x+2.8,y-0.4);
		glEnd();
	}
    
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

void StopRunning(){
	noRed = !noRed;
	if(noRed){
		rTLR = 211 ,gTLR = 211,bTLR = 211
		,rTLG = 0 ,gTLG = 255 ,bTLG = 0;
	}
	if(!noRed){
		rTLR = 255 ,gTLR = 0,bTLR = 0
		,rTLG = 211 ,gTLG = 211 ,bTLG = 211;
	}
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

    TrafficLight(8.0f, -4.0f);
    
    glPushMatrix();
    glTranslatef(-5.0 + x,0,0);
    Car(-12.0f, -5.7f);
    Car(-8.0f, -8.7f);
    Car(0.0f, -8.7f);
    Car(5.0f, -5.7f);
    	if(noRed)
    	x+=0.05;
    glPopMatrix();
    
    if(x>12)
    x = 0.0;

}

void MenuTrafficLigth(int value){
	
}

void Menu2(int value){
	switch ( value )
	{
		case 0:
			ToggleNight();
			break;
		case 1:
			exit(0);
			break;
		case 2:
			StopRunning();
			break;
	}
}

void Menu(){
	int menu;
	    
    menu = glutCreateMenu(Menu2);
    glutAddMenuEntry("Dia/Noite",0);
    glutAddMenuEntry("Alternar Semaforo",2);
    glutAddMenuEntry("Sair",1);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display( void ){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE);
	
	Draw();

	glutPostRedisplay();
	glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y ){
	switch ( key )
	{
		case 27:
			exit ( 0 );
			break;		
		case 'Q':
		case 'q':
			ToggleNight();
			break;
		case 'W':
		case 'w':
			StopRunning();
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
	{	Menu();
	}
	else
	return;
		
	glutPostRedisplay();
}

int  main ( int argc, char** argv ){
    glutInit ( &argc, argv );	//Usada apra iniciar o ambiente Glut
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutCreateWindow ("Projeto Final"); 
    glutFullScreen();
    init();
    glutDisplayFunc (display);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse);
    glutMainLoop ( );
    return 0;
}
