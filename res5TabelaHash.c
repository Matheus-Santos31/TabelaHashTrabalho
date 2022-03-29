#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 19

typedef struct {
  int ocupado;
  char chave[4];
  char url[50];
} Url;

Url tabelaHash[M];

void inicializarTabela() {
  int i;
  
  for (i = 0; i < M; i++)
    tabelaHash[i].ocupado = -1;
}

int retornaValor(char *chave) {
  int soma = 0, i;
  
  for (i = 0; i < strlen(chave); i++)
    soma += chave[i];
  
  return soma;
}

int gerarCodigoHash(int chave) {
  return chave % M;
}

Url lerUrl() {
  Url u;
  printf("Digite a URL: ");
  fflush(stdin);
  scanf("%s", u.url);
  printf("Digite a URL curta (até 4 letras): ");
  fflush(stdin);
  scanf("%s", u.chave);
  u.ocupado = 1;
  return u;
}

void inserir() {
  Url u = lerUrl();
  int x = retornaValor(u.chave);
  int i = gerarCodigoHash(x);
  
  while (tabelaHash[i].ocupado != -1) {
    i = gerarCodigoHash(i + 1);
  }  
  tabelaHash[i] = u;
}

Url *buscar(char *chave) {
  int i = gerarCodigoHash(retornaValor(chave));
  if (strcmp(tabelaHash[i].chave, chave) == 0) {
    return &tabelaHash[i];
  }
  else {
    return NULL;
  }
}

void remover(char *chave) {
  Url *u = buscar(chave);
  if (u) {
    u->ocupado = -1;
  }
  else {
    printf("URL não encontrada\n");
  }
}

void imprimir() {
  int i;
  printf("\n---TABELA---\n");
  for (i = 0; i < M; i++) {
    if (tabelaHash[i].ocupado != -1)
      printf("%d %d %s %s\n", i, tabelaHash[i].ocupado,
      tabelaHash[i].chave, tabelaHash[i].url);
    else
      printf("%2d =\n", i);
  }
  printf("\n----------\n");
}

int main() {
  int op;
  Url *u = NULL;
  char chave[4];
  inicializarTabela();
  
  do {
    printf("1 Para inserir\n2 Para buscar\n3 Para excluir\n4 Para
    listar\n0 Para sair\nDigite a opção: ");
    scanf("%d", &op);
    switch (op) {
      case 1:
        inserir();
        break;
      case 2:
        printf("Digite a URL encurtada: ");
        scanf("%s", chave);
        u = buscar(chave);
        if (u)
          printf("URL: %s\n", u->url);
        else
          printf("URL não encontrada\n");
          break;
      case 3:
        printf("Digite a URL encurtada: ");
        scanf("%s", chave);
        remover(chave);
        break;
      case 4:
        imprimir();
        break;
      default:
        break;
    }
  } while (op != 0);
  return 0;
}