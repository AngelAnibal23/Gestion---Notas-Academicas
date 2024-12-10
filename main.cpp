#include <iostream>
#include <vector>
#include "docente.h"
#include "estudiante.h"
#include "curso.h"
#include "nota.h"
#include "gestorArchivos.h"
#include "menu.h"

int main() {
    std::vector<Docente> docentes = GestorArchivos::cargarDocentes("docentes.txt");
    std::vector<Estudiante> estudiantes = GestorArchivos::cargarEstudiantes("estudiantes.txt");
    std::vector<Curso> cursos = GestorArchivos::cargarCursos("cursos.txt");
    std::vector<Nota> notas = GestorArchivos::cargarNotas("notas.txt");

    // Cargar inscripciones de estudiantes en cursos
    GestorArchivos::cargarInscripciones("inscripciones.txt", cursos, estudiantes);

    Menu menu(docentes, estudiantes, cursos, notas);

    int opcion;
    do {
        std::cout << "Seleccione un usuario:" << std::endl;
        std::cout << "1. Docente" << std::endl;
        std::cout << "2. Estudiante" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                menu.mostrarMenuDocente();
                break;
            case 2:
                menu.mostrarMenuEstudiante();
                break;
            case 0:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcion != 0);

    GestorArchivos::guardarNotas("notas.txt", notas);

    return 0;
}