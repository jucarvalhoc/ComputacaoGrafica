#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"

#define COR_PAREDE 0.98, 0.98, 0.98, 1.0 //cinza claro
#define COR_CHAO_TETO 0.88, 0.88, 0.88, 1.0 //cinza escuro
#define COR_PORTA 0.67, 0.84, 0.9, 0.7 //azul claro
#define COR_LAMPADA 1.0, 0.98, 0.80, 1.0 //amarelo claro
#define COR_QUADRO 0.87, 0.72, 0.53, 1.0 //marrom claro
#define COR_PLACA 0.87, 1.0, 1.0, 1.0 //verde claro
#define COR_TAPETE 0.27, 0.51, 0.70, 1.0 //azul marinho
#define COR_AVISO 1.0, 1.0, 1.0, 1.0 //branco
#define COR_LIXEIRA 0.0, 0.0, 0.0, 1.0 //preto
#define COR_GRADE 1.0, 1.0, 0.0, 1.0 //amarelo
#define COR_EXTINTOR 1.0, 0.0, 0.0, 1.0 //vermelho
#define COR_CADEIRA 0.0, 0.0, 1.0, 1.0 //azul

#define PI 3.14

/* imagens de texturas */
#define TEXTURA_CHAO "teto.jpg"
#define TEXTURA_QUADRO "quadro_avisos.jpg"
#define TEXTURA_EXTINTOR "extintor.jpg"
#define TEXTURA_PAREDE "parede.jpg"
#define TEXTURA_TETO "chao2.jpg"
#define TEXTURA_LIXEIRA "lixeira.jpg"
#define TEXTURA_LAMPADA "lampadas.jpg"
#define TEXTURA_TAPETE "tapete.jpg"
#define TEXTURA_PORTA "porta.jpg"
#define TEXTURA_CADEIRA "cadeira.jpg"
#define TEXTURA_PLACA "placa.jpg"
#define TEXTURA_AVISO "aviso.jpg"

/* vetor de texturas */
GLuint id_textura[15];

static int eixoy = 0;

GLint WIDTH = 800;
GLint HEIGHT = 600;

GLfloat observador[3] = {0.0, 1.0, 0.0}; //y = a que "altura" o observador olha pro objeto
GLfloat referencia[3] = {0.0, 1.0, 0.0}; //y = qual a "altura referencia" que o observador tem do objeto

GLfloat angulo = 0;
GLfloat raio = 100;
GLuint composicao_hall;

/* parede de entrada do hall */
void frente() {
  glColor4f(0.8, 0.8, 0.8, 1.0);
  /* paredes do lado esquerdo/direito da porta de entrada*/
  for(int i = -20; i <= 10; i = i + 30) {
    glPushMatrix();
      glTranslatef(80.0, 0.0, i);
      glScalef(0.5, 10.0, 5.0);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* parede em cima da porta */
  glPushMatrix();
    glTranslatef(80.0, 12.0, -5.0);
    glScalef(0.5, 2.0, 5.0);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

/* parede traseira do hall */
void tras() {
  glColor4f(0.8, 0.8, 0.8, 1.0);
  /* paredes à esquerda/direita da janela */
  for(int i = -23; i <= 18; i = i + 35) {
    glPushMatrix();
      glTranslatef(0.0, 0.0, i);
      glScalef(0.5, 10.0, 3.0);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* paredes acima/abaixo da janela */
  for(int i = -12; i <= 16; i = i + 24) {
    glPushMatrix();
      glTranslatef(0.0, i, -5.0);
      glScalef(0.5, 2.0, 9.0);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* grades da janela */
  glColor4f(COR_GRADE);   
  for (int i = -17; i < 9; i = i + 2) {
    glPushMatrix();
      glTranslatef(0.0, 0.0, i);
      glScalef(0.5, 6.0, 0.1);
      glutSolidCube(3.0);
    glPopMatrix();
 }
}

/* parede do lado esquerdo do hall */
void esquerda() {
  glColor4f(COR_PAREDE);
  for(int i = 17; i <= 63; i = i + 46) {
    glPushMatrix();
      glTranslatef(i, 0.0, 17.0);
      glScalef(11.5, 10.0, 0.5);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }
  
  /* CORREDOR */
  /* paredes do corredor*/
  for(int i = 35; i <= 45; i = i + 10) {
    glPushMatrix();
      glTranslatef(i, 0.0, 35.0);
      glScalef(0.5, 10.0, 12.5);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  } 

  /* "bloqueio" do corredor */
  glPushMatrix();
    glTranslatef(40.0, 0.0, 53.0);
     glScalef(3.0, 10.0, 0.5);
     glutSolidCube(3.0);
     //glutWireCube(3.0);
  glPopMatrix();

  /* chão e teto do corredor */
  glColor4f(COR_CHAO_TETO);
  for (int i = -15; i <= 15; i = i + 30) {
    glPushMatrix();
      glTranslatef(40.0, i, 35.0);
       glScalef(3.5, 0.1, 12.5);
       glutSolidCube(3.0);
       //glutWireCube(3.0);
    glPopMatrix();
  }
}

/* parede do lado direito do hall */
void direita() {
  glColor4f(COR_PAREDE);
  for (int i = 18; i <= 63; i = i + 45) {  
    glPushMatrix();
      glTranslatef(i, 0.0, -28.0);
      glScalef(11.5, 10.0, 0.5);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* CORREDOR */
  /* paredes do corredor*/
  for (int i = 35; i <= 45; i = i + 10) {
    glPushMatrix();
      glTranslatef(i, 0.0, -46.0);
      glScalef(0.5, 10.0, 12.5);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* "bloqueio" do corredor */
  glPushMatrix();
    glTranslatef(40.0, 0.0, -64.0);
     glScalef(3.0, 10.0, 0.5);
     glutSolidCube(3.0);
     //glutWireCube(3.0);
  glPopMatrix();

  /* chão e teto do corredor */
  glColor4f(COR_CHAO_TETO);
  for (int i = -15; i <= 15; i = i + 30) {
    glPushMatrix();
      glTranslatef(40.0, i, -46.0);
       glScalef(3.5, 0.1, 12.5);
       glutSolidCube(3.0);
       //glutWireCube(3.0);
    glPopMatrix();
  }
}

/* chão do hall */
void chao() {
  glColor4f(COR_CHAO_TETO);

  glPushMatrix();
    glTranslatef(40.5, -15.0, -5.0);
    glScalef(27.0, 0.01, 15.0);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

/* teto do hall */
void teto() {
  glColor4f(COR_CHAO_TETO);
  glPushMatrix();
    glTranslatef(40.5, 15.0, -5.0);
    glScalef(27.0, 0.01, 15.0);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

void lixeira() {
  glColor4f(COR_LIXEIRA);   
  /* esquerda e direita */
  for (int i = 31; i <= 33; i = i + 2) {
    glPushMatrix();
      glTranslatef(i, -13.0, 15.0);
      glScalef(0.2, 1.0, 1.0);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* frente e trás */
  for (int i = 14; i <= 16; i = i + 2) {
    glPushMatrix();
      glTranslatef(32.0, -13.0, i);
      glScalef(0.7, 1.0, 0.2);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }

  /* fundo */
  glColor4f(0.9, 0.9, 0.9, 1.0);
  glPushMatrix();
    glTranslatef(32.0, -15.0, 11.0);
    glScalef(0.7, 0.1, 0.2);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

void quadro_avisos() {
  glColor4f(COR_QUADRO);

  glPushMatrix();
    glTranslatef(20.0, 4.0, 16.0);
    glScalef(6.0, 5.0, 0.01);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

void avisos() {
  glColor4f(COR_AVISO);
  for(int i = 15; i <= 25; i = i + 5) {
    glPushMatrix();
      glTranslatef(i, 4.0, 15.5);
      glScalef(1.0, 2.0, 0.01);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }
}

void placas() {
  glColor4f(COR_PLACA);
  for(int i = 55; i <= 70; i = i + 15) {
    glPushMatrix();
      glTranslatef(i, 4.0, -26.0);
      glScalef(4.0, 4.0, 0.01);
      glutSolidCube(3.0);
      //glutWireCube(3.0);
    glPopMatrix();
  }
}

void tapete() {
  glColor4f(COR_TAPETE);
  glPushMatrix();
    glTranslatef(70.0, -14.0, -5.0);
    glScalef(3.0, 0.01, 8.0);
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();
}

void extintor() {
  glColor4f(COR_EXTINTOR);
  glPushMatrix();
    glTranslatef(36.5, 4.0, -30.0);
    glScalef(0.3, 3.5, 0.5);
    glutSolidCube(3.0);
  glPopMatrix();
}

void lampadas() {
  glColor4f(COR_LAMPADA);
  /* lampadas do lado esquerdo */
  for(int i = 10; i <= 90; i = i + 30) {
    /* lampadas replicadas no lado direito */
    for(int j = -20; j <= 10; j = j + 30) {
      glPushMatrix();
        glTranslatef(i, 13.0, j);
        glScalef(3.0, 0.5, 0.3);
        glutSolidCube(3.0);
        //glutWireCube(3.0);
      glPopMatrix();
    }
  }
}

void cadeiras() {
  GLUquadricObj *quadric;

  quadric = gluNewQuadric();

  /* COMPOSIÇÃO DA CADEIRA: encosto, assento, hastes e pés */
   for(int i = 8; i <= 72; i = i + 8) {

    /* "forçando" um espaçamento maior a cada 3 cadeiras, para não ficar na frente do corredor*/
    if(i == 32) {
      i += 24;
    }

    /* replicando os encostos no lado direito do hall */
    glColor4f(COR_CADEIRA);
    for(int j = -26; j <= 16; j = j + 40) {
      glPushMatrix();
        glTranslatef(i, -6.0, j);
        glScalef(3.0, 3.0, 1.0);
        glutSolidSphere(1.0, 10, 10);
        //gluSphere(quadric, 1, 30, 15);
      glPopMatrix();
    }

    /* replicando os assentos no lado direito do hall */
    glColor4f(COR_CADEIRA);
    for(int j = -24; j <= 12; j = j + 36) {
      glPushMatrix();
        glTranslatef(i, -11.0, j);
        glScalef(3.0, 0.5, 3.0);
        glutSolidSphere(1.0, 10, 10);
      glPopMatrix();
    }

    /* replicando as hastes no lado direito do hall */
    glColor4f(0.0, 0.0, 0.0, 1.0); //cor preta
    for(int j = -27; j <= 39; j = j + 42) {
      glPushMatrix();
        glTranslatef(i, -11.0, j);
        glScalef(0.3, 3.0, 0.3);
        glutSolidCube(2.0);
      glPopMatrix();
    }


    /* replicando os pés no lado direito do hall */
    glColor4f(0.0, 0.0, 0.0, 1.0); //cor preta
    for(int j = -24; j <= 13; j = j + 37) {
      glPushMatrix();
        glTranslatef(i, -13.0, j);
        glScalef(0.2, 2.0, 0.2);
        glutSolidCube(2.0);
      glPopMatrix();
    }
  }
}

void hall() {
  /* inicia a composicao do hall */
  composicao_hall = glGenLists(1);
  glNewList(composicao_hall, GL_COMPILE);

  /* ativando textura */
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  /* PARTES DO HALL */
  glBindTexture(GL_TEXTURE_2D, id_textura[3]); //posição 3 do vetor carrega parede.jpg
  frente();  //parte de entrada do hall

  tras(); //traseira do hall

  esquerda(); //parede esquerda do hall

  direita(); //parede direita do hall
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice
  /* FIM PARTES DO HALL */

  glBindTexture(GL_TEXTURE_2D, id_textura[0]); //posição 0 do vetor carrega chao.jpg
  chao();
  glBindTexture(GL_TEXTURE_2D, 0); // zera o índice

  glBindTexture(GL_TEXTURE_2D, id_textura[4]); //posição 4 do vetor carrega teto.jpg
  teto();
  glBindTexture(GL_TEXTURE_2D, 0); // zera o índice

  /* OBJETOS DENTRO DO HALL */
  glBindTexture(GL_TEXTURE_2D, id_textura[5]); //posição 5 do vetor carrega lixeira.jpg
  lixeira();
  glBindTexture(GL_TEXTURE_2D, 0); // zera o índice

  glBindTexture(GL_TEXTURE_2D, id_textura[1]); //posição 1 do vetor carrega quadro_avisos.jpg
  quadro_avisos();
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  //glBindTexture(GL_TEXTURE_2D, id_textura[11]); //posição 11 do vetor carrega aviso.jpg
  avisos();
  //glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  //glBindTexture(GL_TEXTURE_2D, id_textura[10]); //posição 10 do vetor carrega placa.jpg
  placas();
  //glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  glBindTexture(GL_TEXTURE_2D, id_textura[7]); //posição 7 do vetor carrega tapete.jpg
  tapete();
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  glBindTexture(GL_TEXTURE_2D, id_textura[2]); //posição 2 do vetor carrega extintor.jpg
  extintor();
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  cadeiras();

  glBindTexture(GL_TEXTURE_2D, id_textura[6]); //posição 6 do vetor carrega lampada.jpg
  lampadas();
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  /* desativando textura */
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  /* termina a composicao do hall */
  glEndList();
}

void carregar_arquivo_textura(char *arquivo, int indice) {
   int width, height;
   unsigned char* imagem = SOIL_load_image(arquivo, &width, &height, 0, SOIL_LOAD_RGBA);

   glGenTextures(1, &id_textura[indice]); //1º parametro: quantidade de texturas; 2º parametro: vetor com todas as texturas.
   glBindTexture(GL_TEXTURE_2D, id_textura[indice]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL)

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem);
   glBindTexture(GL_TEXTURE_2D, 0); //define a textura corrente
}

void init_textura() {
    carregar_arquivo_textura(TEXTURA_CHAO, 0);
    carregar_arquivo_textura(TEXTURA_QUADRO, 1);
    carregar_arquivo_textura(TEXTURA_EXTINTOR, 2);
    carregar_arquivo_textura(TEXTURA_PAREDE, 3);
    carregar_arquivo_textura(TEXTURA_TETO, 4);
    carregar_arquivo_textura(TEXTURA_LIXEIRA, 5);
    carregar_arquivo_textura(TEXTURA_LAMPADA, 6);
    carregar_arquivo_textura(TEXTURA_TAPETE, 7);
    carregar_arquivo_textura(TEXTURA_PORTA, 8);
    carregar_arquivo_textura(TEXTURA_CADEIRA, 9);
    carregar_arquivo_textura(TEXTURA_PLACA, 10);
    carregar_arquivo_textura(TEXTURA_AVISO, 11);
}

void init_iluminacao() {
  GLfloat ambiente[4] = {1.0, 1.0, 1.0, 1.0}; 
  GLfloat difusa[4] = {0.8, 0.8, 0.8, 1.0}; //cor... sendo 0,0,0 = preto e 1,1,1 = branco
  GLfloat especular[4] = {0.95, 0.95, 0.95, 1.0}; //brilho... sendo 0,0,0 = preto e 1,1,1 = branco
  GLfloat posicao_luz[4] = {10.0, 30.0, 60.0, 1.0}; //necessário quando se trabalha com luz difusa

  GLfloat intensidade_luz = 1;
  GLfloat angulo_luz = 180;

  /* capacidade de brilho do material */
  GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0}; 
  GLint concentracao_brilho = 100;
  
  /* habilita o modelo de colorização de Gouraud */
  glShadeModel(GL_SMOOTH);

  /* define a refletância do material */
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularidade);

  /* define a concentração do brilho */
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, concentracao_brilho); //de 0 a 128. Quanto maior o valor, maior a concentração de brilho

  /* ativa o uso da luz ambiente */
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);

  /* define os parâmetros da luz 0 */
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente); 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
  
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, intensidade_luz); //especifica a intensidade da distribuição de luz. Varia de 0 a 128
  glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, angulo_luz); //especifica o ângulo máximo de propagação de uma fonte de luz. Varia de 0 a 90 e 180 (valor especial)

  glEnable(GL_LIGHT0); //habilitando luz 0

  /* habilita da cor do material */
  glEnable(GL_COLOR_MATERIAL);
  
  /* habilita o uso de iluminação */
  glEnable(GL_LIGHTING);  
    
  /* habilita o depth-buffering */
  glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height) {
  WIDTH = width;
  HEIGHT = height;
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(120.0, width / (float) height, 1, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void display() {
  glEnable(GL_DEPTH_TEST); //teste  
  glDepthMask(GL_TRUE); //teste

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();

  /* calcula a posicao do observador */
  observador[0] = raio * cos(2 * PI * angulo / 360);
  observador[2] = raio * sin(2 * PI * angulo / 360);
  gluLookAt(observador[0], observador[1], observador[2], referencia[0], referencia[1], referencia[2], 0.0, 1.0, 0.0);

  glCallList(composicao_hall);

  /* porta de entrada */
  glColor4f(COR_PORTA);
  /* ativando textura */
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glBindTexture(GL_TEXTURE_2D, id_textura[8]); //posição 8 do vetor carrega porta.jpg

  glPushMatrix();
    /* eixo de rotação */
    glTranslatef(80.0, -3.0, 2.0);
    glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
    glTranslatef(-80.0, 3.0, -2.0);

    glTranslatef(80.0, -3.0, -5.0);

    glScalef(0.5, 8.0, -5.0); //espessura, altura, largura
    glutSolidCube(3.0);
    //glutWireCube(3.0);
  glPopMatrix();

  /*  textura */
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glBindTexture(GL_TEXTURE_2D, 0); //zera o índice

  glPopMatrix();
  glutSwapBuffers();
}

/* setas cima, baixo, esquerda e direita */ 
void special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      observador[1] += 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_DOWN:
      observador[1] -= 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:
      angulo += 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:
      angulo -= 1;
      glutPostRedisplay();
      break;
    }
}

/* interação com teclas do teclado */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'z':
      raio += 1;
      glutPostRedisplay();
      break;

    case 'Z':
      raio -= 1;
      /*if(raio == 0){
        raio = 1;
      }*/
      glutPostRedisplay();
      break;

    case 'a':
      if (eixoy == 90){
        break;
      }
      eixoy += 3;
      glutPostRedisplay();
      break;

    case 'A':
      if (eixoy == 90){
        break;
      }
      eixoy += 3;
      glutPostRedisplay();
      break;

    case 'f':
      if (eixoy == 0){
        break;
      }
      eixoy -= 3;
      glutPostRedisplay();
      break;

    case 'F':
      if (eixoy == 0){
        break;
      }
      eixoy -= 3;
      glutPostRedisplay();
      break;
  }
}

void init() {
 
  glShadeModel(GL_SMOOTH); //Função p/ especificar técnica de coloração desejada. Parâmetro: modelo de Gouraud
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  /* ativando textura */
  glEnable(GL_TEXTURE_2D);
  init_textura();
  init_iluminacao();

   hall();
}

int main(int argc, char **argv) {
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("Hall de Entrada do IC");

  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return(0);
}