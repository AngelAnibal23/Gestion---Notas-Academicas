#include "docente.h"

using namespace std;

Docente::Docente(const string& id, const string& nombre, const string& especialidad)
    : id(id), nombre(nombre), especialidad(especialidad) {}

string Docente::getId() const {
    return id;
}

string Docente::getNombre() const {
    return nombre;
}

string Docente::getEspecialidad() const {
    return especialidad;
}

void Docente::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Docente::setEspecialidad(const string& especialidad) {
    this->especialidad = especialidad;
}