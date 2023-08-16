#include <stdio.h> /* printf */
#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <fenv.h>
#include <stdint.h>

typedef union
{
  float f;
  uint32_t u;
} FloatIntUnion;

int convert_float_to_int(float floatValue)
{
  FloatIntUnion unionValue;
  unionValue.f = floatValue;

  uint32_t intValue = unionValue.u;

  return intValue;
}

typedef struct
{
  float lower;
  float upper;
} Interval;

float m(float x)
{
  return nextafterf(x, DBL_MIN);
}

float M(float x)
{
  fesetround(FE_UPWARD);
  return x;
}

Interval interval(float x)
{
  Interval result;

  result.lower = m(x);
  result.upper = M(x);

  return result;
}

Interval interval_sum(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower + b.lower);
  result.upper = M(a.upper + b.upper);

  return result;
}

Interval interval_sub(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower - b.upper);
  result.upper = M(a.upper - b.lower);

  return result;
}

Interval interval_mul(Interval a, Interval b)
{
  Interval result;

  double products[4] = {a.lower * b.lower, a.lower * b.upper, a.upper * b.lower, a.upper * b.upper};

  result.lower = m(fmin(fmin(products[0], products[1]), fmin(products[2], products[3])));
  result.upper = M(fmax(fmax(products[0], products[1]), fmax(products[2], products[3])));

  return result;
}

Interval interval_div(Interval a, Interval b)
{
  Interval inverse;

  if (b.lower == 0 || b.upper == 0)
  {
    inverse.lower = -INFINITY;
    inverse.upper = INFINITY;
    return inverse;
  }

  inverse.lower = 1 / b.upper;
  inverse.upper = 1 / b.lower;

  return interval_mul(a, inverse);
}

void print_errors(Interval a)
{
  float abs_err = a.upper - a.lower;
  float rel_err = abs_err / a.lower;

  int ulps = fabs(convert_float_to_int(a.upper) - convert_float_to_int(a.lower)) - 1;

  printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n\n", abs_err, rel_err, ulps);
}

Interval apply_op(Interval a, Interval b, char op)
{
  printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] = \n", a.lower, a.upper, op, b.lower, b.upper);
  Interval res;
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

int main(void)
{
  // 2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39 / 0.0
  float a, b, c, d, e;
  char op1, op2, op3, op4;

  scanf("%f %c %f %c %f %c %f %c %f", &a, &op1, &b, &op2, &c, &op3, &d, &op4, &e);

  printf("1: \n");
  Interval first = interval(a);
  Interval result = apply_op(first, interval(b), op1);
  printf("2: \n");
  result = apply_op(result, interval(c), op2);
  printf("3: \n");
  result = apply_op(result, interval(d), op3);
  printf("4: \n");
  result = apply_op(result, interval(e), op4);

  return 0;
}