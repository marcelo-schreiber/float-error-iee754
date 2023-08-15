#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <stdio.h> /* printf */
#include <fenv.h>

typedef struct {
  float a;
  float b;
} Interval_t;

Interval_t interval(float x) {
  Interval_t r;
  r.a = nextafterf(x, DBL_MIN);
  r.b = x;
  return r;
}


int main(void) {
  fesetround(FE_UPWARD);
  float x = 0.001;
  // float y = nextafterf(x, DBL_MIN);

  Interval_t r = interval(x);  
  // round x to nearest float bigger with fesetround(FE_UPWARD)

  printf("[%1.8e,%1.8e]\n", r.a, r.b);
  printf("[2.34699276e-40,2.34700678e-40] (expected)\n");
}