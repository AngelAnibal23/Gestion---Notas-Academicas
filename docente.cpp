#include "docente.h"

Docente::Docente(const std::string& id, const std::string& nombre, const std::string& especialidad)
    : id(id), nombre(nombre), especialidad(especialidad) {}

std::string Docente::getId() const {
    return id;
}

std::string Docente::getNombre() const {
    return nombre;
}

std::string Docente::getEspecialidad() const {
    return especialidad;
}

void Docente::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Docente::setEspecialidad(const std::string& especialidad) {
    this->especialidad = especialidad;
}