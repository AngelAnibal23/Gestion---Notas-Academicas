#ifndef MENU_H
#define MENU_H

#include <vector>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"

class Menu {
public:
    Menu(const std::vector<Docente>& docentes, const std::vector<Estudiante>& estudiantes, std::vector<Curso>& cursos, std::vector<Nota>& notas);
    void mostrarMenuDocente();
    void mostrarMenuEstudiante();
    void ingresarNotas(const std::string&);
    void mostrarNotas();
    void verNotasEstudiante(const std::string& estudianteId);

private:
    void mostrarListaEstudiantes();
    void mostrarContenidoArchivoEstudiantes();
	void mostrarCursosDisponibles(const std::string&); 
    std::vector<Docente> docentes;
    std::vector<Estudiante> estudiantes;
    std::vector<Curso>& cursos;
    std::vector<Nota>& notas;
};

#endif // MENU_H