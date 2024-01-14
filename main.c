#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

/*
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
    glPointSize(7.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < qtd_pontos; i++){
        glColor3f(pontos[i].cor[0], pontos[i].cor[1], pontos[i].cor[2]);
        glVertex2i(pontos[i].x, pontos[i].y);
    }
    glEnd();
}

void desenharPonto(){
    glPointSize(7.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < qtd_pontos; i++){
        if(pontoInicioX == pontos[i].x && pontoInicioY == pontos[i].y){
            glColor3f(pontos[i].cor[0], pontos[i].cor[1], pontos[i].cor[2]);
        }
    }
        glVertex2i(pontoInicioX, pontoInicioY);
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

void desenharReta(){
    glLineWidth(5.0);
    glBegin(GL_LINES);
    for (int i = 0; i < qtd_retas; i++){
        if(retas[i].inicio.x == pontoInicioX && retas[i].inicio.y == pontoInicioY){
            glColor3f(retas[i].inicio.cor[0], retas[i].inicio.cor[1], retas[i].inicio.cor[2]);
        }
    }
        glVertex2i(pontoInicioX, pontoInicioY);
        glVertex2i(pontoFimX, pontoFimY);
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

    qtd_poligonos++;
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
                pontoInicioX = pontos[i].x;
                pontoInicioY = pontos[i].y;
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

    while(terminou != 1){
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
                px1 = x0;
                py1 = y0;
            } else {
                px2 = x0;
                py2 = y0;
            }
        }
    }
    return dentro;
}

int selecionarPoligono(int mx, int my, Poligono p){
    int i, j, num_intersecoes = 0;
    for (int i = 0, j = p.qtd_vertices-1; i < p.qtd_vertices; j = i++){
        if((p.vertices[i].y > my) != (p.vertices[j].y > my) && (mx < p.vertices[i].x + (my - p.vertices[i].y) * (p.vertices[j].x - p.vertices[i].x) / (p.vertices[j].y - p.vertices[i].y))){
            if(p.vertices[i].y != p.vertices[j].y){
                num_intersecoes++;
            }
        }
        else if(p.vertices[i].y == my && p.vertices[j].y > my && p.vertices[i].x < mx){
            num_intersecoes++;
        }
    }
    return (num_intersecoes % 2 != 0);
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
          addPonto(x, ALTURA-y);
        }
        else if(modo == 2){
            inicioX = x;
            inicioY = ALTURA-y;
        }
        else if(modo == 3){
            cordenadas[cont_cord] = x;
            cordenadas[cont_cord+1] = ALTURA-y;
            clicks++;
            cont_cord = cont_cord + 2;
        }
        else{
            if(strcmp(pickObjeto,"pt") == 0){
                pontoSelecionado = selecionarPonto(x, ALTURA-y, TOLERANCIA);
            }
            else if(strcmp(pickObjeto,"rt") == 0){
                for (int i = 0; i < qtd_retas; i++){
                    linhaSelecionada = selecionarLinha(x, ALTURA-y, retas[i].inicio.x, retas[i].inicio.y, retas[i].fim.x, retas[i].fim.y);
                    if(linhaSelecionada == 1){
                        pontoInicioX = retas[i].inicio.x;
                        pontoInicioY = retas[i].inicio.y;
                        pontoFimX = retas[i].fim.x;
                        pontoFimY = retas[i].fim.y;
                    }
                }
            }
            else if(strcmp(pickObjeto,"pl") == 0){
                int paridade = 0;
                for (int i = 0; i < qtd_poligonos; i++){
                    paridade = selecionarPoligono(x, ALTURA-y, poligonos[i]);
                    if(paridade != 0){
                        break;
                    } else{
                        continue;
                    }
                }

            }
        }
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(modo == 2){
            fimX = x;
            fimY = ALTURA - y;
            addReta(inicioX, inicioY, fimX, fimY);
        } else if(modo == 4){
            if(pontoSelecionado == 1){
                pontoFimX = x;
                pontoFimY = ALTURA - y;
                transladarPonto = 1;
                for (int i = 0; i < qtd_pontos; i++){
                    if(pontos[i].x == pontoInicioX && pontos[i].y == pontoInicioY){
                        pontos[i].x = pontoFimX;
                        pontos[i].y = pontoFimY;
                    }
                }
            }
            else if(linhaSelecionada == 1){
                aux1 = x;
                aux2 = ALTURA - y;
                transladarLinha = 1;
                float transX = aux1 - pontoInicioX;
                float transY = aux2 - pontoInicioY;
                for (int i = 0; i < qtd_retas; i++){
                    if((retas[i].inicio.x == pontoInicioX) && (retas[i].inicio.y == pontoInicioY) && (retas[i].fim.x == pontoFimX) && (retas[i].fim.y == pontoFimY)){
                        // Transladar a reta
                        retas[i].inicio.x += transX;
                        retas[i].inicio.y += transY;
                        retas[i].fim.x += transX;
                        retas[i].fim.y += transY;
                    }
                }
            }
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

    if(transladarPonto == 1){
        glPushMatrix();
        glTranslatef((float)pontoFimX, (float)pontoFimY, 0.0);
        desenharPonto();
        glPopMatrix();
    }

    transladarPonto = 0;

    glLoadIdentity();
    desenharRetas();

    if(transladarLinha == 1){
        float a, b;
        a = aux1 - pontoInicioX;
        b = aux2 - pontoInicioY;
        glPushMatrix();
        glTranslatef(a, b, 0.0);
        desenharReta();
        glPopMatrix();
    }
    transladarLinha = 0;
    glLoadIdentity();
    desenharPoligono();

    /*
    glScalef(,,1.0);
    glRotatef(,,,1.0);
    */

    glFlush();
    glutSwapBuffers();
}

int init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,LARGURA,0.0,ALTURA);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA, ALTURA);
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
