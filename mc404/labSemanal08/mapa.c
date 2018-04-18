#include "dfs.h"

#define XMAXSIZE 10
#define YMAXSIZE 10

char mapa[XMAXSIZE][YMAXSIZE] = 
{
{'X','X','X','X','X','X','X','X','X','X'},
{'X','_','_','_','X','X','_','X','_','X'},
{'X','_','X','_','X','X','_','_','_','X'},
{'X','_','X','X','_','_','_','X','_','X'},
{'X','_','X','_','_','X','_','_','_','X'},
{'X','_','_','_','X','X','_','X','_','X'},
{'X','_','X','_','_','X','_','X','_','X'},
{'X','_','_','X','_','_','_','X','_','X'},
{'X','_','_','_','_','X','_','_','_','X'},
{'X','X','X','X','X','X','X','X','X','X'}
};

int visitados[XMAXSIZE][YMAXSIZE];

int xRob, yRob, xLoc, yLoc;

int daParaPassar(int x, int y);

int posicaoXRobinson();

int posicaoYRobinson();

int posicaoXLocal();

int posicaoYLocal();

void inicializaVisitados();

int foiVisitado(int x, int y);

void visitaCelula(int x, int y);

int _start(int argv, char** argc) {

    xRob = 3;
    yRob = 1;
    xLoc = 8;
    yLoc = 3;

    ajudaORobinson();

    return 0;
}

int daParaPassar(int x, int y) {
 if ((x < 0 || x >= XMAXSIZE) || (y < 0 || y >= YMAXSIZE))
  return 0;
 else
  return mapa[x][y] != 'X';
}

int posicaoXRobinson() {
  return xRob;
}

int posicaoYRobinson() {
  return yRob;
}

int posicaoXLocal() {
  return xLoc;
}

int posicaoYLocal() {
  return yLoc;
}

void inicializaVisitados() {
  int i, j;
  for (i = 0; i < XMAXSIZE; i++) {
    for (j = 0; j < YMAXSIZE; j++) {
      visitados[i][j] = 0;
    }
  }
}

int foiVisitado(int x, int y) {
  return visitados[x][y] == 1;
}

void visitaCelula(int x, int y) {
  visitados[x][y] = 1;
}
