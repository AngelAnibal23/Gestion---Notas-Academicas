#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <vector>
#include <string>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"

class GestorArchivos {
public:
    static std::vector<Docente> cargarDocentes(const std::string& archivo);
    static std::vector<Estudiante> cargarEstudiantes(const std::string& archivo);
    static std::vector<Curso> cargarCursos(const std::string& archivo);
    static std::vector<Nota> cargarNotas(const std::string& archivo);
    static void guardarNotas(const std::string& archivo, const std::vector<Nota>& notas);
    static void cargarInscripciones(const std::string& archivo, std::vector<Curso>& cursos, const std::vector<Estudiante>& estudiantes);
};

#endif // GESTORARCHIVOS_H