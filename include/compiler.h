#ifndef CLOX_COMPILER_H_
#define CLOX_COMPILER_H_

#include "chunk.h"
#include "object.h"

ObjFunction* compile(const char* source);
void markCompilerRoots();

#endif  // CLOX_COMPILER_H_
