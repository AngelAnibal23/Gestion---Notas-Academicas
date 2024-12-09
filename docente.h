#ifndef DOCENTE_H
#define DOCENTE_H

#include <string>

class Docente {
public:
    Docente(const std::string& id, const std::string& nombre, const std::string& especialidad);
    std::string getId() const;
    std::string getNombre() const;
    std::string getEspecialidad() const;
    void setNombre(const std::string& nombre);
    void setEspecialidad(const std::string& especialidad);

private:
    std::string id;
    std::string nombre;
    std::string especialidad;
};

#endif // DOCENTE_H