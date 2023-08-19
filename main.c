#include "estruturas.h"
#include "calcula_intervalo.h"
#include "auxiliares.h"
#include "operacoes.h"

int main(void)
{
  // 2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39 / 0.0

  /* Declara variaveis dos numeros */
  float a, b, c, d, e;

  /* Declara variaveis dos simbolos de operacoes */
  char op1, op2, op3, op4;

  /* Escaneia a expressao aritmetica */
  scanf("%f %c %f %c %f %c %f %c %f", &a, &op1, &b, &op2, &c, &op3, &d, &op4, &e);

  /* Primeira operacao */
  printf("1: \n");
  Interval result = apply_op(interval(a), interval(b), op1);

  /* Segunda operacao*/
  printf("2: \n");
  result = apply_op(result, interval(c), op2);

  /* Terceira operacao*/
  printf("3: \n");
  result = apply_op(result, interval(d), op3);

  /* Quarta operacao */
  printf("4: \n");
  result = apply_op(result, interval(e), op4);

  return 0;
}