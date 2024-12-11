#ifndef CURSO_H
#define CURSO_H

#include <string>
#include <vector>
#include "estudiante.h"

using namespace std;

class Curso {
private:
    string id;
    string nombre;
    string docenteId;
    vector<Estudiante> estudiantes;
    
public:
    Curso(const string& id, const string& nombre, const string& docenteId);
    string getId() const;
    string getNombre() const;
    string getDocenteId() const;
    void setNombre(const string& nombre);
    void setDocenteId(const string& docenteId);
    void agregarEstudiante(const Estudiante& estudiante);
    const vector<Estudiante>& getEstudiantes() const;

};

#endif // CURSO_H