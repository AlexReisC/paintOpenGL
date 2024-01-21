#define MAX_PONTOS 1000
#define MAX_RETAS 500
#define MAX_POLIGONOS 500
#define MAX_VERTICES 20
#define ALTURA 480
#define LARGURA 640
#define TOLERANCIA 7
#define TOLERANCIA_LINHA 10
#define FORA 0
#define ESQUERDA 1
#define DIREITA 2
#define ABAIXO 4
#define ACIMA 8

typedef struct{
    GLint x;
    GLint y;
    GLfloat cor[3];
}Ponto;

typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

typedef struct{
    Ponto vertices[MAX_VERTICES];
    GLint qtd_vertices;
}Poligono;

GLint qtd_pontos = 0;
Ponto pontos[MAX_PONTOS];

GLint qtd_retas = 0;
Reta retas[MAX_RETAS];

GLint qtd_poligonos = 0;
Poligono poligonos[MAX_POLIGONOS];

int modo = 1;
int clicks = 0;
GLfloat corAtual[3];
GLint cordenadas[MAX_VERTICES];
int cont_cord = 0;
int inicioX, inicioY, fimX, fimY;
int pontoSelecionado = 0, linhaSelecionada = 0, poligonoSelecionado = 0;
char pickObjeto[3];
GLint pontoFimX, pontoFimY;
int transladarAtivacao = 0, rotacaoAtivacao = 0, escalaAtivacao = 0;
Poligono poligonoAuxiliar;
Ponto pontoAuxiliar;
Reta retaAuxiliar;
float angulo = 45.0;
Ponto pontoMedio, centroide;
float escalaX = 1.0, escalaY = 1.0, larguraDalinha = 6.0;
