#include "docente.h"

Docente::Docente(const string& id, const string& nombre, const string& especialidad)
    : Usuario(id, nombre), especialidad(especialidad) {}

string Docente::getEspecialidad() const {
    return especialidad;
}

void Docente::setEspecialidad(const string& especialidad) {
    this->especialidad = especialidad;
}