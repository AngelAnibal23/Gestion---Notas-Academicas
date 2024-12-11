#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

using namespace std;

class Estudiante {
private:
    string id;
    string nombre;
public:
    Estudiante(const string& id, const string& nombre);
    string getId() const;
    string getNombre() const;
    void setNombre(const string& nombre);

};

#endif // ESTUDIANTE_H