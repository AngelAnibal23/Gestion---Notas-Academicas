#include "curso.h"

Curso::Curso(const std::string& id, const std::string& nombre, const std::string& docenteId)
    : id(id), nombre(nombre), docenteId(docenteId) {}

std::string Curso::getId() const {
    return id;
}

std::string Curso::getNombre() const {
    return nombre;
}

std::string Curso::getDocenteId() const {
    return docenteId;
}

void Curso::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Curso::setDocenteId(const std::string& docenteId) {
    this->docenteId = docenteId;
}

void Curso::agregarEstudiante(const Estudiante& estudiante) {
    estudiantes.push_back(estudiante);
}

const std::vector<Estudiante>& Curso::getEstudiantes() const {
    return estudiantes;
}