#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

class Estudiante {
public:
    Estudiante(const std::string& id, const std::string& nombre);
    std::string getId() const;
    std::string getNombre() const;
    void setNombre(const std::string& nombre);

private:
    std::string id;
    std::string nombre;
};

#endif // ESTUDIANTE_H