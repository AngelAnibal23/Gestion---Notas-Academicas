#ifndef NOTA_H
#define NOTA_H

#include <string>

class Nota {
public:
    Nota(std::string estudianteId, std::string cursoId, double nota1, double nota2, double nota3);
    std::string getEstudianteId() const;
    std::string getCursoId() const;
    double getNota1() const;
    double getNota2() const;
    double getNota3() const;
    void setNota1(double nota);
    void setNota2(double nota);
    void setNota3(double nota);
    double calcularPromedio() const;

private:
    std::string estudianteId;
    std::string cursoId;
    double nota1;
    double nota2;
    double nota3;
};

#endif // NOTA_H