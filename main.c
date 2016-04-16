 /**
 *  Copyright 2015 Gabriel Nicolás González Ferreira <gabrielinuz@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **/

#ifdef __unix__
    #include "dlfcn.h"
    #define GET_FUNCTION dlsym
    #define OPEN_LIBRARY(X) dlopen(X, RTLD_NOW)
    #define LIBRARY_POINTER_TYPE void*
    #define CLOSE_LIBRARY dlclose

#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #define GET_FUNCTION GetProcAddress
    #define OPEN_LIBRARY(X) LoadLibrary((LPCSTR)X)
    #define LIBRARY_POINTER_TYPE HMODULE
    #define CLOSE_LIBRARY FreeLibrary
#endif // defined

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
        printf("Cannot open library:");
        return 1;
    }

    //"Loading symbol..."
    typedef void (*function_type)();

    function_type greet = (function_type) GET_FUNCTION(handle, "greet");

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
