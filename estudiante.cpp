#include "estudiante.h"

Estudiante::Estudiante(const std::string& id, const std::string& nombre)
    : id(id), nombre(nombre) {}

std::string Estudiante::getId() const {
    return id;
}

std::string Estudiante::getNombre() const {
    return nombre;
}

void Estudiante::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}