#include "estruturas.h"
#include "calcula_intervalo.h"
#include <float.h>
#include <math.h>  /* nextafter e INFINITY */
#include <fenv.h>

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