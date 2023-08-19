#include "estruturas.h"

Interval interval(float x)
{
  Interval result;

  result.lower = m(x);
  result.upper = M(x);

  return result;
}

float m(float x)
{
  return nextafterf(x, DBL_MIN);
}

float M(float x)
{
  fesetround(FE_UPWARD);
  return x;
}