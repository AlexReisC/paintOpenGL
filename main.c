#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include "estruturas.h"
#include "funcoesDesenho.h"

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

void addPonto(int x, int y){

    pontos[qtd_pontos].x = x;
    pontos[qtd_pontos].y = y;

    pontos[qtd_pontos].cor[0] = corAtual[0];
    pontos[qtd_pontos].cor[1] = corAtual[1];
    pontos[qtd_pontos].cor[2] = corAtual[2];

    qtd_pontos++;
}

void desenharPontos(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < qtd_pontos; i++){
        glColor3f(pontos[i].cor[0], pontos[i].cor[1], pontos[i].cor[2]);
        glVertex2i(pontos[i].x, pontos[i].y);
    }
    glEnd();
}

void addReta(int x1, int y1, int x2, int y2){

    retas[qtd_retas].inicio.x = x1;
    retas[qtd_retas].inicio.y = y1;
    retas[qtd_retas].inicio.cor[0] = corAtual[0];
    retas[qtd_retas].inicio.cor[1] = corAtual[1];
    retas[qtd_retas].inicio.cor[2] = corAtual[2];

    retas[qtd_retas].fim.x = x2;
    retas[qtd_retas].fim.y = y2;
    retas[qtd_retas].fim.cor[0] = corAtual[0];
    retas[qtd_retas].fim.cor[1] = corAtual[1];
    retas[qtd_retas].fim.cor[2] = corAtual[2];

    qtd_retas++;
}

void desenharRetas(){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    for (int i = 0; i < qtd_retas; i++){
        glColor3f(retas[i].inicio.cor[0], retas[i].inicio.cor[1], retas[i].inicio.cor[2]);
        glVertex2i(retas[i].inicio.x, retas[i].inicio.y);
        glColor3f(retas[i].fim.cor[0], retas[i].fim.cor[1], retas[i].fim.cor[2]);
        glVertex2i(retas[i].fim.x, retas[i].fim.y);
    }
    glEnd();
}

void addPoligono(int n, int vet[]){
    poligonos[qtd_poligonos].qtd_vertices = n;
    int j = 0;
    for(int i = 0; i < n; i++){
        poligonos[qtd_poligonos].vertices[i].x = vet[j];
        poligonos[qtd_poligonos].vertices[i].y = vet[j+1];
        j = j + 2;
    }
    qtd_poligonos = qtd_poligonos + 1;
}

void desenharPoligono(){
    for(int i = 0; i < qtd_poligonos; i++){

    }
}

void desenharPaletaDeCores(int button, int state, int x, int y){

}

void desenharMenu(){
    //desenha quadrados

    glLineWidth(3.0);
    glBegin(GL_QUADS);
        glColor3f(0.0,0.0,0.0);
        glVertex2i(50,100);
        glVertex2i(50,50);
        glVertex2i(100,50);
        glVertex2i(100,100);
    glEnd();
}


void gerenciaTeclado(unsigned char key, int x, int y){
    switch (key) {
        case 'R':
        case 'r':// vermelho
            corAtual[0] = 1.0;
            corAtual[1] = 0.0;
            corAtual[2] = 0.0;
            break;
        case 'G':
        case 'g':// verde
            corAtual[0] = 0.0;
            corAtual[1] = 1.0;
            corAtual[2] = 0.0;
            break;
        case 'B':
        case 'b':// azul
            corAtual[0] = 0.0;
            corAtual[1] = 0.0;
            corAtual[2] = 1.0;
            break;
        case 'Y':
        case 'y':// amarelo
            corAtual[0] = 1.0;
            corAtual[1] = 1.0;
            corAtual[2] = 0.0;
            break;
        case 'P':
        case 'p':// roxo
            corAtual[0] = 1.0;
            corAtual[1] = 0.0;
            corAtual[2] = 1.0;
            break;
        case 'C':
        case 'c':// ciano
            corAtual[0] = 0.0;
            corAtual[1] = 1.0;
            corAtual[2] = 1.0;
            break;
        case '1':
            modo = 0;
            break;
        case '2':
            modo = 1;
            break;
        case '3':
            modo = 2;
            break;
    }
    glutPostRedisplay();
}

void gerenciaMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        addPonto(x, altura-y);
        if(modo == 1){
            addReta(pontos[qtd_pontos-2].x, pontos[qtd_pontos-2].y, pontos[qtd_pontos-1].x, pontos[qtd_pontos-1].y);
        }
    }

    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        clicks++;
        cord[cont_cord] = x;
        cord[cont_cord+1] = altura-y;
        cont_cord = cont_cord + 2;
    }

    if(modo == 2){
        modo = 0;
        addPoligono(clicks, cord);
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

    desenharPontos();
    desenharRetas();
    desenharPoligono();
    glLoadIdentity();
//    desenharMenu();
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
    glutKeyboardFunc(gerenciaTeclado);
    glutMouseFunc(gerenciaMouse);
//    glutSpecialFunc(TeclasEspeciais);

    init();
    glutMainLoop();
    return 0;
}
