#include "usuario.h"

Usuario::Usuario(const string& id, const string& nombre) : id(id), nombre(nombre) {}

string Usuario::getId() const {
    return id;
}

string Usuario::getNombre() const {
    return nombre;
}

void Usuario::setNombre(const string& nombre) {
    this->nombre = nombre;
}