#ifndef NOTA_H
#define NOTA_H

#include <string>

using namespace std;

class Nota {
private:
    string estudianteId;
    string cursoId;
    double nota1;
    double nota2;
    double nota3;
    int unidad; // Unidad para la cual se ingresan las notas

public:
    // Constructor que acepta 6 argumentos
    Nota(const string& estudianteId, const string& cursoId, double nota1, double nota2, double nota3, int unidad);
    string getEstudianteId() const;
    string getCursoId() const;
    double getNota1() const;
    double getNota2() const;
    double getNota3() const;
    int getUnidad() const; // Método para obtener la unidad
    void setNota1(double nota1);
    void setNota2(double nota2);
    void setNota3(double nota3);
    double calcularPromedio() const;
};

#endif // NOTA_H