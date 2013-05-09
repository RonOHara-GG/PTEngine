#ifndef _GL_BIND_H_
#define _GL_BIND_H_

// Include all the function prototypes
#include "gl.h"

// Define function pointer definitions
#define GL_FUNCTION(funcName, returnType, args)     typedef returnType (__stdcall* pfn##funcName)args;
#include "glCoreFunctions.h"
#include "glExtFunctions.h"
#undef GL_FUNCTION

// create function pointers
#define GL_FUNCTION(funcName, returnType, args)     pfn##funcName funcName = 0;
#include "glCoreFunctions.h"
#include "glExtFunctions.h"
#undef GL_FUNCTION

typedef void* (*FindFunction)(const char* functionName);

// bind funciton pointers
inline void glBind(FindFunction findFunction)
{
#define GL_FUNCTION(funcName, returnType, args)  funcName = (pfn##funcName)findFunction(#funcName);
        
    // Bind all the core functions
    #include "glCoreFunctions.h"
    
    // Bind extensions
    #include "glExtFunctions.h"
        
#undef GL_FUNCTION
}

#endif // _GL_BIND_H_