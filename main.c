#include <windows.h>
#include <GL/glut.h>

#define MAX_PONTOS 100
#define MAX_RETAS 100
#define MAX_POLIGONOS 100
#define altura 480
#define largura 640

typedef struct{
    float x;
    float y;
}Ponto;

typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

typedef struct{
    Ponto vertices[MAX_PONTOS];
    int qtd_vertices;
}Poligono;

int qtd_pontos = 0;
Ponto pontos[MAX_PONTOS];

int qtd_retas = 0;
Reta retas[MAX_RETAS];

int qtd_poligonos = 0;
Poligono poligonos[MAX_POLIGONOS];

GLint lineTrue = 0;
GLint clicks = 0;
int qtd_cord = 0;

void addPonto(float x, float y){

    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    qtd_pontos++;
}

void desenharPontos(){

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < qtd_pontos; i++){
        glVertex2f(pontos[i].x, pontos[i].y);
    }
    glEnd();
}

void addReta(float x1, float y1, float x2, float y2){

    retas[qtd_retas].inicio.x = x1;
    retas[qtd_retas].inicio.y = y1;

    retas[qtd_retas].fim.x = x2;
    retas[qtd_retas].fim.y = y2;

    qtd_retas++;
}

void desenharRetas(){

    glLineWidth(4.0);
    glBegin(GL_LINES);
    for (int i = 0; i < qtd_retas; i++){
        glVertex2f(retas[i].inicio.x, retas[i].inicio.y);
        glVertex2f(retas[i].fim.x, retas[i].fim.y);
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
        poligonos[qtd_poligonos].vertices[i].x = vet[i];
        poligonos[qtd_poligonos].vertices[i].y = vet[i];
    }

    qtd_poligonos++;
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
        addPonto(x, altura-y);
        if(lineTrue == 1){
            addLine(pontos[qtd_pontos-2].x, pontos[qtd_pontos-2].y, pontos[qtd_pontos-1].x, pontos[qtd_pontos-1].y);
        }

        // aqui a funcao de selecao do quadrado
        int cord[MAX_PontoS];
        if(qtd_cord < clicks){
            cord[qtd_cord] = x;
            cord[qtd_cord+1] = y;
            qtd_cord+=2;
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

    drawPontos();
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
    gluOrtho2D(0.0,largura,0.0,altura);

}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
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
