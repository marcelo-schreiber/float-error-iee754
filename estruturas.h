#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <fenv.h>
#include <math.h>

typedef union
{
  float f;
  uint32_t u;
} FloatIntUnion;

typedef struct
{
  float lower;
  float upper;
} Interval;