#include "curso.h"

using namespace std;
Curso::Curso(const string& id, const string& nombre, const string& docenteId)
    : id(id), nombre(nombre), docenteId(docenteId) {}

string Curso::getId() const {
    return id;
}

string Curso::getNombre() const {
    return nombre;
}

string Curso::getDocenteId() const {
    return docenteId;
}

void Curso::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Curso::setDocenteId(const string& docenteId) {
    this->docenteId = docenteId;
}

void Curso::agregarEstudiante(const Estudiante& estudiante) {
    estudiantes.push_back(estudiante);
}

const vector<Estudiante>& Curso::getEstudiantes() const {
    return estudiantes;
}