// The standard headers included by all files


#ifndef HEADERS_H
#define HEADERS_H

#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#ifdef LINUX
  #include <sys/timeb.h>	// includes ftime (to return current time)
  #include <unistd.h>		// includes usleep (to sleep for some time)
  #include <values.h>           // includes MAXFLOAT
  #define sprintf_s sprintf
  #define _strdup strdup
  #define sscanf_s sscanf
#endif

#ifdef _WIN32

  #include <sys/timeb.h>
  //#include <typeinfo>
  #define M_PI 3.14159
  #define MAXFLOAT FLT_MAX
  //#define rint(x) floor((x)+0.5)
  #pragma warning(disable : 4244 4305 4996 4838)
#endif

#ifdef MACOS
  #include <sys/timeb.h>	// includes ftime (to return current time)
  #define sprintf_s sprintf
  #define _strdup strdup
  #define sscanf_s sscanf
#endif

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#include <cmath>

#include "linalg.h"

#define randIn01() (rand() / (float) RAND_MAX)   // random number in [0,1]

#define signum(x)  (((x) > 0) ? 1 : (((x) < 0) ? -1 : 0))

#endif
