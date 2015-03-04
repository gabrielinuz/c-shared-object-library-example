#ifdef __unix__
    #include "dlfcn.h"
    #define GET_METHOD dlsym
    #define OPEN_LIBRARY(X) dlopen(X, RTLD_NOW)
    #define LIBRARY_POINTER_TYPE void*
    #define CLOSE_LIBRARY dlclose

#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #define GET_METHOD GetProcAddress
    #define OPEN_LIBRARY(X) LoadLibrary((LPCSTR)X)
    #define LIBRARY_POINTER_TYPE HMODULE
    #define CLOSE_LIBRARY FreeLibrary
#endif // defined

/*
    File        : main.cpp

    Project     : c shared object library and dynamic link library example

    Author      : Gabriel Nicolás González Ferreira

    License     : http://www.gnu.org/licenses/gpl.txt GNU GPL 3.0

    IDE         : Codeblocks
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    #ifdef __unix__
        LIBRARY_POINTER_TYPE handle = OPEN_LIBRARY("./lib.so");
    #elif defined(_WIN32) || defined(WIN32)
        LIBRARY_POINTER_TYPE handle = OPEN_LIBRARY("./lib.dll");
    #endif // defined

    if(!handle)
    {
        printf("Cannot open library: /n");
        return 1;
    }

    //"Loading symbol..."
    typedef void (*function_type)();

    function_type greet = (function_type) GET_METHOD(handle, "greet");

    if (!greet)
    {
        printf("Cannot load method /n");
        CLOSE_LIBRARY(handle);
        return 1;
    }

    printf("Calling function...\n");
    greet();

    // close the library
    printf("Closing library...\n");
    CLOSE_LIBRARY(handle);

    return 0;
}
