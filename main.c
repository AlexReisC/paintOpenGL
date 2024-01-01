#include <windows.h>
#include <GL/glut.h>

#define MAX_POINTS 100
#define MAX_LINES 100
#define MAX_POLYGONS 100
#define height 480
#define width 640

typedef struct{
    float x;
    float y;
}Point;

typedef struct{
    Point start;
    Point end;
}Line;

typedef struct{
    Point vertices[MAX_POINTS];
    int count_edges;
}Poligono;

int count_points = 0;
Point points[MAX_POINTS];

int count_lines = 0;
Line lines[MAX_LINES];

int count_polygons = 0;
Poligono polygons[MAX_POLYGONS];

GLint lineTrue = 0;
GLint clicks = 0;
int count_cord = 0;

void addPoint(float x, float y){

    points[count_points].x = x;
    points[count_points].y = y;

    count_points++;
}

void drawPoints(){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < count_points; i++){
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
}

void addLine(float x1, float y1, float x2, float y2){

    lines[count_lines].start.x = x1;
    lines[count_lines].start.y = y1;

    lines[count_lines].end.x = x2;
    lines[count_lines].end.y = y2;

    count_lines++;
}

void drawLines(){

    glLineWidth(4.0);
    glBegin(GL_LINES);
    for (int i = 0; i < count_lines; i++){
        glVertex2f(lines[i].start.x, lines[i].start.y);
        glVertex2f(lines[i].end.x, lines[i].end.y);
    }
    glEnd();
}

/*
    - desenhar o objeto com base na tecla e na posicao mapeada
    -- passar como parametro para a funcao addPonto()
    -- definir cor do objeto
    - selecionar objeto
    - excluir objeto
    - transformacoes geometricas
    -- arrastar e soltar
    -- rotacionar em relacao ao centro do objeto
    -- escalar em relacao ao centro do objeto

*/

void addPoligono(int n, int vet[]){
    for(int i = 0; i < n; i++){
        polygons[count_polygons].vertices[i].x = vet[i];
        polygons[count_polygons].vertices[i].y = vet[i];
    }

    count_polygons++;
}

void drawTriangle(int vet[]){
   /* glBegin(GL_TRIANGLE);

    glEnd();*/
}

void drawSquare(int vet[]){
    glLineWidth(4.0);
    glBegin(GL_QUADS);
    for(int i = 0; i < 8; i++){
        glVertex2i(vet[i], vet[i+1]);
        i++;
    }

    glEnd();
}

/*
    Transladar: pressionar em cima do objeto e soltar em um local
    -> Algoritmo de selecao de area
    -> GLUT_LEFT_BUTTON, GLUT_DOWN e GLUT_UP
    Rotacionar: seta esquerda e direita, rotaciona 90 graus
    -> Algoritmo de selecao de area
    -> KEY_LEFT e KEY_RIGHT
    Escalar: seta para cima e para baixo, altera tamanho
    -> Algoritmo de selecao de area
    -> KEY_UP e KEY_DOWN
*/

void selectColor(int button, int state, int x, int y){

}

void menu(){

}

void manageKeyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'R':
        case 'r':// muda a cor corrente para vermelho
            glColor3f(1.0,0.0,0.0);
            break;
        case 'G':
        case 'g':// muda a cor corrente para verde
            glColor3f(0.0,1.0,0.0);
            break;
        case 'B':
        case 'b':// muda a cor corrente para azul
            glColor3f(0.0,0.0,1.0);
            break;
        case '1':
            lineTrue = 0;
            break;
        case '2':
            lineTrue = 1;
            break;
    }
    glutPostRedisplay();
}

void manageMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        clicks++;
        addPoint(x, height-y);
        if(lineTrue == 1){
            addLine(points[count_points-2].x, points[count_points-2].y, points[count_points-1].x, points[count_points-1].y);
        }

        // aqui a funcao de selecao do quadrado
        int cord[MAX_POINTS];
        if(count_cord < clicks){
            cord[count_cord] = x;
            cord[count_cord+1] = y;
            count_cord+=2;
        }
        //drawSquare(cord);
    }
    glutPostRedisplay();
}

// para teclas especiais, tais como F1, PgDn e Home
/*void TeclasEspeciais(int key, int x, int y){
    if(key == GLUT_KEY_UP) {

    }
    if(key == GLUT_KEY_DOWN) {

    }
    glutPostRedisplay();
}*/

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawPoints();
    drawLines();
//    drawPoligono();
    /*
    glTranslatef(,,0);
    glScalef(,,1.0);
    glRotatef(,,,1.0);
    */

    glFlush();
}

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,width,0.0,height);

}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200,0);
    glutCreateWindow("Paint OpenGL");

    glutDisplayFunc(display);
    glutKeyboardFunc(manageKeyboard);
    glutMouseFunc(manageMouse);
//    glutSpecialFunc(TeclasEspeciais);

    init();
    glutMainLoop();
    return 0;
}
