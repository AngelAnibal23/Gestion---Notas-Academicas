#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {
protected:
    string id;
    string nombre;

public:
    Usuario(const string& id, const string& nombre);
    string getId() const;
    string getNombre() const;
    void setNombre(const string& nombre);
};

#endif // USUARIO_H