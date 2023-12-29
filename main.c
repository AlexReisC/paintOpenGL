#include <windows.h>
#include <GL/glut.h>

#define MAX_POINTS 100
#define MAX_LINES 100
#define MAX_POLYGONS 100

typedef struct{
    float x;
    float y;
}Point;

typedef struct{
    Point start;
    Point end;
}Line;

typedef struct{
    Line edges[MAX_LINES];
    int count_edges;
}Poligono;

int count_points = 0;
Point points[MAX_POINTS];

int count_lines = 0;
Line lines[MAX_LINES];

int count_polygons = 0;
Poligono polygons[MAX_POLYGONS];

GLint doubleClick = 0;

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
//    glBegin(GL_LINE_STRIP);
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

void addPoligono(float vertices[], int clicks){
    int i = 0;
    while(i < clicks){
        polygons[count_polygons].edges[i].start.x = vertices[i];
        polygons[count_polygons].edges[i].start.y = vertices[i];

        polygons[count_polygons].edges[i].end.x = vertices[i];
        polygons[count_polygons].edges[i].end.y = vertices[i];

        polygons[count_polygons].count_edges++;
        i++;
    }
    count_polygons++;
}

void drawPoligono(){
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < count_polygons; i++){
        for(int j = 0; j < polygons[i].count_edges; j++){
            glVertex2i(polygons[i].edges[j].start.x, polygons[i].edges[j].start.y);
            glVertex2i(polygons[i].edges[j].end.x, polygons[i].edges[j].end.y);
        }
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
/*
void selectColor(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON){

    }
}
*/
void GerenciaTeclado(unsigned char key, int x, int y){
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
            doubleClick = 0;
            break;
        case '2':
            doubleClick = 1;
            break;
    }
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        addPoint(x, 400-y);
        if(doubleClick == 1){
            addLine(points[count_points-2].x, points[count_points-2].y, points[count_points-1].x, points[count_points-1].y);
        }
    }

    // aplicar funcao de translacao
    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do teclado
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
    gluOrtho2D(0.0,400.0,0.0,400.0);

    float vertices[MAX_POINTS];
    int clicks = 0;
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(200,0);
    glutCreateWindow("Paint OpenGL");

    glutDisplayFunc(display);
    glutKeyboardFunc(GerenciaTeclado);
    glutMouseFunc(GerenciaMouse);
//    glutSpecialFunc(TeclasEspeciais);

    init();
    glutMainLoop();
    return 0;
}
