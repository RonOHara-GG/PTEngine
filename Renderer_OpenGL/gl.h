#ifndef __gl_h_
#ifndef __GL_H__

#define __gl_h_
#define __GL_H__

#include "glDefines.h"


#define GL_FUNCTION(funcName, returnType, args)     extern returnType (__stdcall *funcName) args;
#include "glCoreFunctions.h"
#include "glExtFunctions.h"
#undef GL_FUNCTION


#endif // __GL_H__
#endif // __gl_h_