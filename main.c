#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
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
    glPointSize(6.0);
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
    glLineWidth(5.0);
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
        poligonos[qtd_poligonos].vertices[i].cor[0] = corAtual[0];
        poligonos[qtd_poligonos].vertices[i].cor[1] = corAtual[1];
        poligonos[qtd_poligonos].vertices[i].cor[2] = corAtual[2];
        j = j + 2;
    }

    qtd_poligonos = qtd_poligonos + 1;
}

void desenharPoligono(){
    for(int i = 0; i < qtd_poligonos; i++){
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < poligonos[i].qtd_vertices; j++){
            glColor3f(poligonos[i].vertices[j].cor[0], poligonos[i].vertices[j].cor[1], poligonos[i].vertices[j].cor[2]);
            glVertex2i(poligonos[i].vertices[j].x, poligonos[i].vertices[j].y);
        }
        glEnd();
    }
}

int selecionarPonto(int mx, int my, int t){
    for(int i = 0; i < qtd_pontos; i++){
        if(mx <= pontos[i].x + t && mx >= pontos[i].x - t){
            if(my <= pontos[i].y + t && my >= pontos[i].y - t){
                return 1;
            }
        }
    }
    return 0;
}

int calcularCodigo(int mx, int my, int px, int py){
    int codigo = FORA;
    if(px < mx - TOLERANCIA_LINHA){
        codigo |= ESQUERDA;
    }
    else if(px > mx + TOLERANCIA_LINHA){
        codigo |= DIREITA;
    }
    else if(py < my - TOLERANCIA_LINHA){
        codigo |= ABAIXO;
    }
    else if(py > my + TOLERANCIA_LINHA){
        codigo |= ACIMA;
    }
    return codigo;
}

int selecionarLinha(int mx, int my, int px1, int py1, int px2, int py2){
    int codigo, codigo1, codigo2;
    int dentro = 0, terminou = 0;
    int xmin = mx - TOLERANCIA_LINHA;
    int xmax = mx + TOLERANCIA_LINHA;
    int ymin = my - TOLERANCIA_LINHA;
    int ymax = my + TOLERANCIA_LINHA;

    while(!terminou){
        codigo1 = calcularCodigo(mx, my, px1, py1);
        codigo2 = calcularCodigo(mx, my, px2, py2);

        if(codigo1 == 0 || codigo2 == 0){
            dentro = 1;
            terminou = 1;
        }
        else if(codigo1 & codigo2){
            terminou = 1;
        }
        else {
            int x0, y0;
            codigo = codigo1 ? codigo1 : codigo2;
            if(codigo & ESQUERDA){
                x0 = xmin;
                y0 = py1 + (xmin-px1)*(py2-py1) / (px2-px1);
            } else if(codigo & DIREITA){
                x0 = xmax;
                y0 = py1 + (xmax-px1)*(py2-py1) / (px2-px1);
            } else if(codigo & ABAIXO){
                y0 = ymin;
                x0 = px1 + (ymin-py1)*(px2-px1) / (py2-py1);
            } else if(codigo & ACIMA){
                y0 = ymax;
                x0 = px1 + (ymax-py1)*(px2-px1) / (py2-py1);
            }
            if(codigo == codigo1){
                px1 = x;
                py1 = y;
            } else {
                px2 = x;
                py2 = y;
            }
        }
    }
    return dentro;
}

void desenharPaletaDeCores(int x, int y){

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
            if(modo == 4){
                char str[] = "rt";
                strcpy(pickObjeto,str);
                break;
            }
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
            if(modo == 4){
                char str[] = "pl";
                strcpy(pickObjeto,str);
                break;
            }
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
        case 'O':
        case 'o': //laranja
            corAtual[0] = 1.0;
            corAtual[1] = 0.5;
            corAtual[2] = 0.0;
            break;
        case 'D':
        case 'd': // default: preto
            if(modo == 4){
                char str[] = "pt";
                strcpy(pickObjeto,str);
                break;
            }
            corAtual[0] = 0.0;
            corAtual[1] = 0.0;
            corAtual[2] = 0.0;
            break;
        case '1':
            modo = 1;
            break;
        case '2':
            modo = 2;
            break;
        case '3':
            modo = 3;
            break;
        case '4':
            modo = 4;
            break;
    }
    glutPostRedisplay();
}

void gerenciaMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(modo == 1){
          addPonto(x, altura-y);
        }
        else if(modo == 2){
            inicioX = x;
            inicioY = altura - y;
        }
        else if(modo == 3){
            cordenadas[cont_cord] = x;
            cordenadas[cont_cord+1] = altura-y;
            clicks++;
            cont_cord = cont_cord + 2;
        }
        else{
            if(strcmp(pickObjeto,"pt") == 0){
                int resp = selecionarPonto(x, altura-y, TOLERANCIA);

            }
            else if(strcmp(pickObjeto,"rt") == 0){
                /*for(int i = 0; i < qtd_retas; i++){
                    linhaSelecionada = selecionarLinha(x, y, retas[i].inicio.x, retas[i].inicio.y, retas[i].fim.x, retas[i].fim.y);
                    if(!linhaSelecionada){
                        break;
                    }
                }*/
            }

            // funcao de transladar e escalar:
        }
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(modo == 2){
            fimX = x;
            fimY = altura - y;
            addReta(inicioX, inicioY, fimX, fimY);
        }
    }

    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if(modo == 3){
            addPoligono(clicks, cordenadas);
            clicks = 0;
            cont_cord = 0;
        }
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
