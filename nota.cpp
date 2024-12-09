#include "nota.h"

Nota::Nota(std::string estudianteId, std::string cursoId, double nota1, double nota2, double nota3)
    : estudianteId(estudianteId), cursoId(cursoId), nota1(nota1), nota2(nota2), nota3(nota3) {}

std::string Nota::getEstudianteId() const {
    return estudianteId;
}

std::string Nota::getCursoId() const {
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

void Nota::setNota1(double nota) {
    nota1 = nota;
}

void Nota::setNota2(double nota) {
    nota2 = nota;
}

void Nota::setNota3(double nota) {
    nota3 = nota;
}

double Nota::calcularPromedio() const {
    return (nota1 + nota2 + nota3) / 3.0;
}