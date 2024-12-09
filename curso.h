#ifndef CURSO_H
#define CURSO_H

#include <string>

class Curso {
public:
    Curso(const std::string& id, const std::string& nombre, const std::string& docenteId);
    std::string getId() const;
    std::string getNombre() const;
    std::string getDocenteId() const;
    void setNombre(const std::string& nombre);
    void setDocenteId(const std::string& docenteId);

private:
    std::string id;
    std::string nombre;
    std::string docenteId;
};

#endif // CURSO_H