#include "menu.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>

using namespace std; 

// Constructor
Menu::Menu(const vector<Docente>& docentes, const vector<Estudiante>& estudiantes, vector<Curso>& cursos, vector<Nota>& notas)
    : docentes(docentes), estudiantes(estudiantes), cursos(cursos), notas(notas) {}

// Función de búsqueda binaria manual
template <typename T>
typename vector<T>::const_iterator binarySearch(const  vector<T>& vec, const  string& id,  function< string(const T&)> getIdFunc) {
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Comparar el ID del elemento en el medio con el ID buscado
        string midId = getIdFunc(vec[mid]);
        if (midId == id) {
            return vec.begin() + mid; // Elemento encontrado
        } else if (midId < id) {
            left = mid + 1; // Buscar en la mitad derecha
        } else {
            right = mid - 1; // Buscar en la mitad izquierda
        }
    }

    return vec.end(); // Elemento no encontrado
}

// Función para ordenar un vector por el campo ID
template <typename T>
void ordenarPorId( vector<T>& vec, function< string(const T&)> getIdFunc) {
    sort(vec.begin(), vec.end(), [&getIdFunc](const T& a, const T& b) {
        return getIdFunc(a) < getIdFunc(b);
    });
}


void shellSort( vector<Nota>& notas) {
    int n = notas.size();

    // Inicio con un gap grande y luego lo reduzco
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Realizo un ordenamiento por inserción para el gap actual
        for (int i = gap; i < n; i++) {
            Nota temp = notas[i];
            int j;
            for (j = i; j >= gap && notas[j - gap].calcularPromedio() < temp.calcularPromedio(); j -= gap) {
                notas[j] = notas[j - gap];
            }
            notas[j] = temp;
        }
    }
}

// Función para mostrar los cursos disponibles del docente
void Menu::mostrarCursosDisponibles(const string& docenteId) {
    cout << "Cursos disponibles para el docente con ID: " << docenteId <<  endl;
    cout << "---------------------------------------------------------" <<  endl;
    cout << left << setw(10) << "ID" << setw(40) << "Nombre del Curso" << endl;
    cout << "---------------------------------------------------------" << endl;

    for (const auto& curso : cursos) {
        if (curso.getDocenteId() == docenteId) {
            std::cout << std::left << std::setw(10) << curso.getId() << std::setw(40) << curso.getNombre() << std::endl;
        }
    }

    cout << "---------------------------------------------------------" << endl;
}

void Menu::mostrarMenuDocente() {
   	
    int opcion;
    string docenteId;
    cout << "Ingrese su ID de docente: ";
    cin >> docenteId;
	

    // Ordenar el vector de docentes por ID
    ordenarPorId(docentes, function< string(const Docente&)>([](const Docente& docente) {
        return docente.getId();
    }));

    // Convertir la lambda a std::function
    function< string(const Docente&)> getIdFunc = [](const Docente& docente) {
        return docente.getId();
    };

    // Usar búsqueda binaria manual
    auto it = binarySearch(docentes, docenteId, getIdFunc);

    if (it == docentes.end()) {
        cout << "Docente no encontrado." << endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    cout << "Bienvenido, " << it->getNombre() << endl;

    do {
        //system("cls");
        cout << "\t\t\t\t\t\t\t============ MENU DOCENTE ============" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t                        \t\t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t1.- Ingresar Notas.       \t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t                        \t\t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t2.- Ver notas ingresadas. \t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t                        \t\t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t0.- Volver.               \t|" << endl;
	    cout << "\t\t\t\t\t\t\t|\t\t                        \t\t|" << endl;
	    cout << "\t\t\t\t\t\t\t|_____________________________________|" << endl;
	    cout << endl << "\t\t\t\t\t\t\t\tIngrese la opcion deseada: ";
	    cin >> opcion;

        switch (opcion) {
            case 1:
                // Mostrar los cursos disponibles del docente
                
                ingresarNotas(docenteId);
                break;
            case 2:
                mostrarNotas();
                system("PAUSE");
                system("cls"); 
                break;
            case 0:
            	system("cls"); 
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
                system("PAUSE");
                system("cls"); 
        }
    } while (opcion != 0);

}

void Menu::mostrarMenuEstudiante() {
    int opcion;
	string estudianteId;
    cout << "Ingrese su ID de estudiante: ";
    cin >> estudianteId;

    // Ordenar el vector de estudiantes por ID
    ordenarPorId(estudiantes, function<string(const Estudiante&)>([](const Estudiante& estudiante) {
        return estudiante.getId();
    }));

    // Convertir la lambda a std::function
    function<string(const Estudiante&)> getIdFunc = [](const Estudiante& estudiante) {
        return estudiante.getId();
    };

    // Usar búsqueda binaria manual
    auto it = binarySearch(estudiantes, estudianteId, getIdFunc);

    if (it == estudiantes.end()) {
        cout << "Estudiante no encontrado." << endl;
        system("PAUSE");
        system("cls");
        return;
    }

    cout << "Bienvenido, " << it->getNombre() << endl;

    do {
        //system("cls");
        cout << "\t\t\t\t\t\t\t============ MENU ESTUDIANTE ============" << endl;
    	cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
    	cout << "\t\t\t\t\t\t\t|\t\t1.- Ver Notas.       \t\t|" << endl;
   		cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
    	cout << "\t\t\t\t\t\t\t|\t\t0.- Volver.          \t\t|" << endl;
    	cout << "\t\t\t\t\t\t\t|\t\t                  \t\t|" << endl;
    	cout << "\t\t\t\t\t\t\t|_______________________________________|" << endl;
    	cout << endl << "\t\t\t\t\t\t\t\tIngrese la opcion deseada: ";
    	cin >> opcion;

        switch (opcion) {
            case 1:
                verNotasEstudiante(estudianteId);
                system("PAUSE");
                system("cls");
                break;
            case 0:
            	system("cls"); 
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("PAUSE");
                system("cls");
        }
    } while (opcion != 0);
}

void Menu::mostrarContenidoArchivoEstudiantes() {
    ifstream file("estudiantes.txt");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo de estudiantes." << endl;
        return;
    }

    string line;
    while ( getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void Menu::ingresarNotas(const string& docenteId) {
    system("cls");
    
    mostrarCursosDisponibles(docenteId);
    string cursoId;
    cout << "Ingrese el ID del curso: ";
    cin >> cursoId;

    // Ordenar el vector de cursos por ID
    ordenarPorId(cursos, function<string(const Curso&)>([](const Curso& curso) {
        return curso.getId();
    }));

    // Convertir la lambda a std::function
    function<string(const Curso&)> getIdFunc = [](const Curso& curso) {
        return curso.getId();
    };

    // Usar búsqueda binaria manual para encontrar el curso
    auto cursoIt = binarySearch(cursos, cursoId, getIdFunc);

    if (cursoIt == cursos.end() || cursoIt->getDocenteId() != docenteId) {
        cout << "Curso no encontrado o no asignado a este docente." << endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    // Obtener la lista de estudiantes inscritos en el curso
	vector<Estudiante> estudiantesInscritos = cursoIt->getEstudiantes();

    // Ordenar los estudiantes inscritos por nombre alfabéticamente
    sort(estudiantesInscritos.begin(), estudiantesInscritos.end(), [](const Estudiante& a, const Estudiante& b) {
        return a.getNombre() < b.getNombre();
    });

    // Mostrar la lista de estudiantes inscritos en orden alfabético
    cout << "Lista de estudiantes inscritos en el curso " << cursoId << " (orden alfabetico):" << endl;
    for (const auto& estudiante : estudiantesInscritos) {
        cout << estudiante.getId() << " " << estudiante.getNombre() << endl;
    }

    string estudianteId;
    double nota1, nota2, nota3;

    cout << "Ingrese el ID del estudiante: ";
    cin >> estudianteId;

    // Validar que el estudiante existe y está inscrito en el curso
    auto estudianteIt = find_if(estudiantesInscritos.begin(), estudiantesInscritos.end(), [estudianteId](const Estudiante& estudiante) {
        return estudiante.getId() == estudianteId;
    });

    if (estudianteIt == estudiantesInscritos.end()) {
        cout << "Estudiante no encontrado o no inscrito en este curso." << endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    cout << "Ingrese la nota de desempeno: ";
    cin >> nota1;
    cout << "Ingrese la nota conocimiento: ";
	cin >> nota2;
    cout << "Ingrese la nota producto: ";
    cin >> nota3;

    auto it =  find_if(notas.begin(), notas.end(), [estudianteId, cursoId](const Nota& nota) {
        return nota.getEstudianteId() == estudianteId && nota.getCursoId() == cursoId;
    });

    if (it != notas.end()) {
        it->setNota1(nota1);
        it->setNota2(nota2);
        it->setNota3(nota3);
    } else {
        notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3);
    }

    cout << "Notas ingresadas correctamente." << endl;
    system("PAUSE");
    system("cls"); 
}

void Menu::mostrarNotas() {
    system("cls");

    // Ordenar las notas usando ShellSort
    shellSort(notas);

    cout << "=========================================================" << endl;
    cout << "                    NOTAS ORDENADAS                      " << endl;
    cout << "=========================================================" << endl;
    cout << left << setw(15) << "Estudiante ID"
              << setw(15) << "Curso ID"
              << setw(15) << "Nota 1"
              << setw(15) << "Nota 2"
              << setw(15) << "Nota 3"
              << setw(15) << "Promedio" << endl;
    cout << "---------------------------------------------------------" << endl;

    for (const auto& nota : notas) {
        cout << left << setw(15) << nota.getEstudianteId()
                  << setw(15) << nota.getCursoId()
                  << setw(15) << nota.getNota1()
                  << setw(15) << nota.getNota2()
                  << setw(15) << nota.getNota3()
                  << setw(15) << nota.calcularPromedio() << endl;
    }

    cout << "=========================================================" << endl;
}

void Menu::verNotasEstudiante(const std::string& estudianteId) {
    system("cls");
    shellSort(notas);
    cout << "=========================================================" << endl;
    cout << "                    NOTAS DEL ESTUDIANTE                 " << endl;
    cout << "=========================================================" << endl;
    cout << left << std::setw(10) << "Curso"
              << setw(10) << "Nota CN"
              << setw(10) << "Nota PR"
              << setw(10) << "Nota DP"
              << setw(10) << "Promedio" << endl;
    cout << "---------------------------------------------------------" << endl;

    bool encontrado = false;

    for (const auto& nota : notas) {
        if (nota.getEstudianteId() == estudianteId) {
            encontrado = true;
            cout << left << setw(10) << nota.getCursoId()
                      << setw(10) << nota.getNota1()
                      << setw(10) << nota.getNota2()
                      << setw(10) << nota.getNota3()
                      << setw(10) << nota.calcularPromedio() << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron notas para el estudiante con ID: "
                  << estudianteId << endl;
    }

    cout << "=========================================================" << endl;
}