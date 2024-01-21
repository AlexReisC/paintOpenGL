# Paint OpenGL
## Descrição
Projeto feito para a disciplina de Computação Gráfica. Um paint feito em C com OpenGL, nele é possivel desenhar pontos, retas e poligonos através do mouse.
## Funcionalidades
- Desenhar pontos, retas e poligonos
- Escolher a cor do desenho
- Selecionar pontos, retas e poligonos
- Mover, aumentar tamanho e rotacinar os objetos desenhados
- Excluir objetos
- Salvar e carregar objetos desenhados em arquivo
## Como usar
O programa tem 4 modos, o modo de desenho de pontos, o de retas, o de poligonos e o modo de seleção. Por padrão, inicia no modo 1 de desenho de pontos, utilizando as teclas '1', '2', '3' e '4', respectivamente, do teclado pode se alternar entre os modos.
(O teclado será bastante utilizado, ao final listarei todas as teclas e funcionalidades).
Para desenhar pontos basta clicar com o botão esquerdo mouse, para retas é arrastando e soltando e para desenhar poligonos deve-se clicar com o botão esquerdo onde seram os vertices e ao fim clicar com o botão direito do mouse para desenhar o poligono desejado. É possivel escolher a cor do desenho através do teclado, pressionando a tecla que correpondente ao nome da cor em inglês.
O modo de seleção é usada para selecionar individualmente ponto, reta ou poligono para aplicar as transformações geometricas de translação, rotação e escala. A translação ocorre pressionando e arrastando o objeto ao local desejado, a rotação ocorre ao clicar no objeto e então ele será rotacionado em quantos graus for desejado (feito através das setas do teclado) e na escala o objeto aumenta de tamanho ao clique do mouse (também determina o fator de escala pelas setas do teclado).
A última funcionalidade é a de salvar os objetos em arquivos e carrega-los do arquivo para a tela quando quiser, não há requisito para tal e pode ser feito pressionanando 'F1' para salvar e 'F2' para carregar os objetos salvos nos arquivos.

### Lista de teclas e funcionalidades
- R: cor vermelha / no modo de seleção ativa a rotação
- G: verde
- B: azul
- Y: amarelo
- O: laranja
- P: roxo / no modo de seleção ativa a seleção de poligonos
- C: ciano
- D: preto / no modo de seleção ativa a seleção de pontos
- L: ativa a seleção de retas
- E: ativa a função de escalar objetos
- T: ativa a translação
- Q: fecha o programa
- 1: muda para o modo de desenhar pontos
- 2: modo de desenhar retas
- 3: modo de desenhar poligonos
- 4: modo de seleção de objetos
- End: excluir objetos selecionados
- F1: salvar objetos no arquivo
- F2: carregar o objeto salvo
- Seta para cima: aumenta o fator de escala em Y em 0.5
- Seta para baixo: diminui o fato de escala em Y em 0.5
- Seta para direita: quando escala ativada aumenta o fator de escala em X em 0.5 / quando rotação ativada aumenta o angulo de rotação em 5 graus
- Seta para a esquerda: quando escala ativada diminui o fator de escala em X em 0.5 / quando rotação ativada diminui o angulo de rotação em 5 graus
