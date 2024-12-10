#ifndef CURSO_H
#define CURSO_H

#include <string>
#include <vector>
#include "estudiante.h"

class Curso {
public:
    Curso(const std::string& id, const std::string& nombre, const std::string& docenteId);
    std::string getId() const;
    std::string getNombre() const;
    std::string getDocenteId() const;
    void setNombre(const std::string& nombre);
    void setDocenteId(const std::string& docenteId);
    void agregarEstudiante(const Estudiante& estudiante);
    const std::vector<Estudiante>& getEstudiantes() const;

private:
    std::string id;
    std::string nombre;
    std::string docenteId;
    std::vector<Estudiante> estudiantes;
};

#endif // CURSO_H