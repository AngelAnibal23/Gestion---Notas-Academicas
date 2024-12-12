#include "nota.h"

// Constructor que acepta 6 argumentos
Nota::Nota(const string& estudianteId, const string& cursoId, double nota1, double nota2, double nota3, int unidad)
    : estudianteId(estudianteId), cursoId(cursoId), nota1(nota1), nota2(nota2), nota3(nota3), unidad(unidad) {}

string Nota::getEstudianteId() const {
    return estudianteId;
}

string Nota::getCursoId() const {
    return cursoId;
}

double Nota::getNota1() const {
    return nota1;
}

double Nota::getNota2() const {
    return nota2;
}

double Nota::getNota3() const {
    return nota3;
}

int Nota::getUnidad() const { // Implementación del método getUnidad
    return unidad;
}

void Nota::setNota1(double nota1) {
    this->nota1 = nota1;
}

void Nota::setNota2(double nota2) {
    this->nota2 = nota2;
}

void Nota::setNota3(double nota3) {
    this->nota3 = nota3;
}

double Nota::calcularPromedio() const {
    return (nota1 + nota2 + nota3) / 3.0;
}