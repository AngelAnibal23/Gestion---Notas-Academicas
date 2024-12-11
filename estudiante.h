#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "usuario.h"

class Estudiante : public Usuario {
public:
    Estudiante(const string& id, const string& nombre);
};

#endif // ESTUDIANTE_H