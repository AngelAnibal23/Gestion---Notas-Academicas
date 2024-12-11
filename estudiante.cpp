#include "estudiante.h"

using namespace std;

Estudiante::Estudiante(const string& id, const string& nombre)
    : id(id), nombre(nombre) {}

string Estudiante::getId() const {
    return id;
}

string Estudiante::getNombre() const {
    return nombre;
}

void Estudiante::setNombre(const string& nombre) {
    this->nombre = nombre;
}