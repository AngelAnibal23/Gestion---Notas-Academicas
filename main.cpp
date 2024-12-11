#include <iostream>
#include <vector>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"
#include "gestorArchivos.h"
#include "menu.h"

using namespace std;

int main() {
    vector<Docente> docentes = GestorArchivos::cargarDocentes("docentes.txt");
    vector<Estudiante> estudiantes = GestorArchivos::cargarEstudiantes("estudiantes.txt");
    vector<Curso> cursos = GestorArchivos::cargarCursos("cursos.txt");
    vector<Nota> notas = GestorArchivos::cargarNotas("notas.txt");

    // Cargar inscripciones de estudiantes en cursos
    GestorArchivos::cargarInscripciones("inscripciones.txt", cursos, estudiantes);

    Menu menu(docentes, estudiantes, cursos, notas);

    int opcion;
    do {
        cout << "Seleccione un usuario:" << endl;
        cout << "1. Docente" << endl;
        cout << "2. Estudiante" << endl;
        cout << "0. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                menu.mostrarMenuDocente();
                break;
            case 2:
                menu.mostrarMenuEstudiante();
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);

    GestorArchivos::guardarNotas("notas.txt", notas);

    return 0;
}