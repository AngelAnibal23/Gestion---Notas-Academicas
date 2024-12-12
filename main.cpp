#include <iostream>
#include <vector>
#include "curso.h"
#include "nota.h"
#include "gestorArchivos.h"
#include "menu.h"

using namespace std;

int main() {
     vector<Docente> docentes = GestorArchivos::cargarDocentes("docentes.txt");
    vector<Estudiante> estudiantes = GestorArchivos::cargarEstudiantes("estudiantes.txt");
    vector<Curso> cursos = GestorArchivos::cargarCursos("cursos.txt");
    vector<Nota> notas = GestorArchivos::cargarNotas(); // Cargar notas desde archivos

    // Cargar inscripciones de estudiantes en cursos
    GestorArchivos::cargarInscripciones("inscripciones.txt", cursos, estudiantes);

    Menu menu(docentes, estudiantes, cursos, notas);

    int opcion;
    do {
        cout << "\t\t\t\t\t\t\t__________________ELIGA SU CARGO_________________" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t1.- Docente.\t\t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t2.- Estudiante. \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t0.- Salir.        \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
        cout << "\t\t\t\t\t\t\t|_______________________________________________|" << endl;
        cout << endl << "\t\t\t\t\t\t\t\t \tIngrese la respuesta: ";
        cin >> opcion;
        system("cls"); 

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

    return 0;
}
