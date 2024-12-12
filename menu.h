#ifndef MENU_H
#define MENU_H

#include <vector>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"

using namespace std;

class Menu {
public:
    Menu(const vector<Docente>& docentes, const vector<Estudiante>& estudiantes, vector<Curso>& cursos, vector<Nota>& notas);
    void mostrarMenuDocente();
    void mostrarMenuEstudiante();
    void ingresarNotas(const string&);
    void mostrarNotas(const string&);
    void verNotasEstudiante(const string& estudianteId);

private:
    void mostrarListaEstudiantes();
    void mostrarContenidoArchivoEstudiantes();
	void mostrarCursosDisponibles(const string&); 
    vector<Docente> docentes;
    vector<Estudiante> estudiantes;
    vector<Curso>& cursos;
    vector<Nota>& notas;
};

#endif // MENU_H


