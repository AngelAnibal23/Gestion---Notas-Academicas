#ifndef DOCENTE_H
#define DOCENTE_H

#include "usuario.h"

class Docente : public Usuario {
private:
    string especialidad;

public:
    Docente(const string& id, const string& nombre, const string& especialidad);
    string getEspecialidad() const;
    void setEspecialidad(const string& especialidad);
};

#endif // DOCENTE_H