#include <stdlib.h>
#include "estruturas.h"
#include "operacoes.h"
#include "auxiliares.h"
#include "calcula_intervalo.h"

int convert_float_to_int(float floatValue)
{
  FloatIntUnion unionValue;
  unionValue.f = floatValue;

  return ((int)unionValue.u);
}

void print_errors(Interval a)
{
  float abs_err = a.upper - a.lower;
  float rel_err = abs_err / a.lower;

  int ulps = abs(convert_float_to_int(a.upper) - convert_float_to_int(a.lower)) - 1;

  printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n\n", abs_err, rel_err, ulps);
}

Interval apply_op(Interval a, Interval b, char op)
{
  Interval res;

 printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] = \n", a.lower, a.upper, op, b.lower, b.upper);

  switch (op)
  {
  case '+':
    res = interval_sum(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    print_errors(res);

    return res;
  case '-':
    res = interval_sub(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    print_errors(res);

    return res;
  case '*':
    res = interval_mul(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    print_errors(res);

    return res;
  case '/':
    res = interval_div(a, b);
    printf("[%1.8e,%1.8e]\n", res.lower, res.upper);
    print_errors(res);

    return res;
  default:
    printf("Operação inválida\n");
    return interval(0);
  }
}