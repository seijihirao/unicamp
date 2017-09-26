#ifndef TOKEN_H
#define TOKEN_H

typedef enum TipoDoToken {Instrucao, Diretiva, DefRotulo, Hexadecimal, Decimal, Nome} TipoDoToken;

typedef struct Token {
  TipoDoToken tipo;
  char* palavra;
  unsigned linha;
} Token;

unsigned adicionarToken(Token novoToken);
void removerToken(unsigned pos);
Token recuperaToken(unsigned pos);
void imprimeListaTokens();
unsigned getNumberOfTokens();

#endif
