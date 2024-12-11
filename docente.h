#ifndef DOCENTE_H
#define DOCENTE_H

#include <string>

using namespace std;

class Docente {

private:
    string id;
    string nombre;
    string especialidad;
	
public:
    Docente(const string& id, const string& nombre, const string& especialidad);
    string getId() const;
    string getNombre() const;
    string getEspecialidad() const;
    void setNombre(const string& nombre);
    void setEspecialidad(const string& especialidad);

};

#endif // DOCENTE_H