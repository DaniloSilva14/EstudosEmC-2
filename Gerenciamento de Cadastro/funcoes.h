#ifndef FUNCOES
#define FUNCOES

struct user{
  char *primeiroNome, *ultimoNome;
  char *cpf, *tell;
};

typedef struct user USER;

//FUNCOES
void cadastra(USER *,int );
void buscarCPF(USER *,int ,char *);
void dump(USER *,int );
int removeUSER(USER *,int ,char *);
void libera(USER *,int );

#endif
