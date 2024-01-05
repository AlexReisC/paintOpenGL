#define MAX_PONTOS 100
#define MAX_RETAS 100
#define MAX_POLIGONOS 100
#define MAX_VERTICES 20
#define altura 480
#define largura 640

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

GLint modo = 1;
GLint clicks = 0;
GLfloat corAtual[3];
GLint cordenadas[MAX_VERTICES];
GLint cont_cord = 0;
GLint xReta[4];
GLint yReta[4];
GLint cont_XY = 0;
