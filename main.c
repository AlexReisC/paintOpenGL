#include <windows.h>
#include <GL/glut.h>
#define MAX_POINTS 1000
#define MAX_LINES 1000

typedef struct{
    float x;
    float y;
}Ponto;

typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

int quantidade_pontos = 0;
Ponto pontos[MAX_POINTS];

int quantidade_retas = 0;
Reta retas[MAX_LINES];

void addPonto(float x, float y){

    pontos[quantidade_pontos].x = x;
    pontos[quantidade_pontos].y = y;

    quantidade_pontos++;
}

void desenhaPontos(){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < quantidade_pontos; i++){
        glColor3f(1, 0, 0);
        glVertex2f(pontos[i].x, pontos[i].y);
    }
    glEnd();
}

void addReta(float x1, float y1, float x2, float y2){

    retas[quantidade_retas].inicio.x = x1;
    retas[quantidade_retas].inicio.y = y1;

    retas[quantidade_retas].fim.x = x2;
    retas[quantidade_retas].fim.y = y2;

    quantidade_retas++;
}

void desenhaRetas(){

    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < quantidade_pontos; i++){
        glColor3f(0, 0, 1);
        glVertex2f(retas[i].inicio.x, retas[i].inicio.y);
        glVertex2f(retas[i].fim.x, retas[i].fim.y);
    }
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    desenhaPontos();
//    desenhaRetas();

    glFlush();
}

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
    /*
    addPonto();
    addPonto();

    addReta();
    */
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,300);
    glutInitWindowPosition(200,0);
    glutCreateWindow("Paint OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
