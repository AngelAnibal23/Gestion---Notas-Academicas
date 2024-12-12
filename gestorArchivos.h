#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <vector>
#include <string>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"

using namespace std;
class GestorArchivos {
public:
    static vector<Docente> cargarDocentes(const string& archivo);
    static vector<Estudiante> cargarEstudiantes(const string& archivo);
    static vector<Curso> cargarCursos(const string& archivo);
    static vector<Nota> cargarNotas();
    static void guardarNotas(const vector<Nota>& notas);
    static void cargarInscripciones(const string& archivo, vector<Curso>& cursos, const vector<Estudiante>& estudiantes);

    // Nuevo método para cargar notas de una unidad específica
    static vector<Nota> cargarNotasUnidad(const string& archivo);
};

#endif // GESTORARCHIVOS_H