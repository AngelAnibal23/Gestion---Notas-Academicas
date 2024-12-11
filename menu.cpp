#include "menu.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>

using namespace std; 

// Constructor
Menu::Menu(const std::vector<Docente>& docentes, const std::vector<Estudiante>& estudiantes, std::vector<Curso>& cursos, std::vector<Nota>& notas)
    : docentes(docentes), estudiantes(estudiantes), cursos(cursos), notas(notas) {}

// Función de búsqueda binaria manual
template <typename T>
typename std::vector<T>::const_iterator binarySearch(const std::vector<T>& vec, const std::string& id, std::function<std::string(const T&)> getIdFunc) {
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Comparar el ID del elemento en el medio con el ID buscado
        std::string midId = getIdFunc(vec[mid]);
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
void ordenarPorId(std::vector<T>& vec, std::function<std::string(const T&)> getIdFunc) {
    std::sort(vec.begin(), vec.end(), [&getIdFunc](const T& a, const T& b) {
        return getIdFunc(a) < getIdFunc(b);
    });
}

// Función para mostrar los cursos disponibles del docente
void Menu::mostrarCursosDisponibles(const std::string& docenteId) {
    std::cout << "Cursos disponibles para el docente con ID: " << docenteId << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(10) << "ID" << std::setw(40) << "Nombre del Curso" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    for (const auto& curso : cursos) {
        if (curso.getDocenteId() == docenteId) {
            std::cout << std::left << std::setw(10) << curso.getId() << std::setw(40) << curso.getNombre() << std::endl;
        }
    }

    std::cout << "---------------------------------------------------------" << std::endl;
}

void Menu::mostrarMenuDocente() {
   	
    int opcion;
    string docenteId;
    cout << "Ingrese su ID de docente: ";
    cin >> docenteId;
	

    // Ordenar el vector de docentes por ID
    ordenarPorId(docentes, std::function<std::string(const Docente&)>([](const Docente& docente) {
        return docente.getId();
    }));

    // Convertir la lambda a std::function
    std::function<std::string(const Docente&)> getIdFunc = [](const Docente& docente) {
        return docente.getId();
    };

    // Usar búsqueda binaria manual
    auto it = binarySearch(docentes, docenteId, getIdFunc);

    if (it == docentes.end()) {
        std::cout << "Docente no encontrado." << std::endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;

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
    std::string estudianteId;
    std::cout << "Ingrese su ID de estudiante: ";
    std::cin >> estudianteId;

    // Ordenar el vector de estudiantes por ID
    ordenarPorId(estudiantes, std::function<std::string(const Estudiante&)>([](const Estudiante& estudiante) {
        return estudiante.getId();
    }));

    // Convertir la lambda a std::function
    std::function<std::string(const Estudiante&)> getIdFunc = [](const Estudiante& estudiante) {
        return estudiante.getId();
    };

    // Usar búsqueda binaria manual
    auto it = binarySearch(estudiantes, estudianteId, getIdFunc);

    if (it == estudiantes.end()) {
        std::cout << "Estudiante no encontrado." << std::endl;
        system("PAUSE");
        system("cls");
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;

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
                std::cout << "Opcion no valida." << std::endl;
                system("PAUSE");
                system("cls");
        }
    } while (opcion != 0);
}

void Menu::mostrarContenidoArchivoEstudiantes() {
    std::ifstream file("estudiantes.txt");
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo de estudiantes." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void Menu::ingresarNotas(const std::string& docenteId) {
    system("cls");
    
    mostrarCursosDisponibles(docenteId);
    std::string cursoId;
    std::cout << "Ingrese el ID del curso: ";
    std::cin >> cursoId;

    // Ordenar el vector de cursos por ID
    ordenarPorId(cursos, std::function<std::string(const Curso&)>([](const Curso& curso) {
        return curso.getId();
    }));

    // Convertir la lambda a std::function
    std::function<std::string(const Curso&)> getIdFunc = [](const Curso& curso) {
        return curso.getId();
    };

    // Usar búsqueda binaria manual para encontrar el curso
    auto cursoIt = binarySearch(cursos, cursoId, getIdFunc);

    if (cursoIt == cursos.end() || cursoIt->getDocenteId() != docenteId) {
        std::cout << "Curso no encontrado o no asignado a este docente." << std::endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    // Obtener la lista de estudiantes inscritos en el curso
    std::vector<Estudiante> estudiantesInscritos = cursoIt->getEstudiantes();

    // Ordenar los estudiantes inscritos por nombre alfabéticamente
    std::sort(estudiantesInscritos.begin(), estudiantesInscritos.end(), [](const Estudiante& a, const Estudiante& b) {
        return a.getNombre() < b.getNombre();
    });

    // Mostrar la lista de estudiantes inscritos en orden alfabético
    std::cout << "Lista de estudiantes inscritos en el curso " << cursoId << " (orden alfabetico):" << std::endl;
    for (const auto& estudiante : estudiantesInscritos) {
        std::cout << estudiante.getId() << " " << estudiante.getNombre() << std::endl;
    }

    std::string estudianteId;
    double nota1, nota2, nota3;

    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> estudianteId;
    std::cout << "Ingrese la nota 1: ";
    std::cin >> nota1;
    std::cout << "Ingrese la nota 2: ";
    std::cin >> nota2;
    std::cout << "Ingrese la nota 3: ";
    std::cin >> nota3;

    auto it = std::find_if(notas.begin(), notas.end(), [estudianteId, cursoId](const Nota& nota) {
        return nota.getEstudianteId() == estudianteId && nota.getCursoId() == cursoId;
    });

    if (it != notas.end()) {
        it->setNota1(nota1);
        it->setNota2(nota2);
        it->setNota3(nota3);
    } else {
        notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3);
    }

    std::cout << "Notas ingresadas correctamente." << std::endl;
    system("PAUSE");
    system("cls"); 
}

void Menu::mostrarNotas() {
    system("cls");
    for (const auto& nota : notas) {
        std::cout << "Estudiante ID: " << nota.getEstudianteId()
                  << ", Curso ID: " << nota.getCursoId()
                  << ", Nota 1: " << nota.getNota1()
                  << ", Nota 2: " << nota.getNota2()
                  << ", Nota 3: " << nota.getNota3()
                  << ", Promedio: " << nota.calcularPromedio() << std::endl;
    }
}

void Menu::verNotasEstudiante(const std::string& estudianteId) {
    system("cls");
    std::cout << "=========================================================" << std::endl;
    std::cout << "                    NOTAS DEL ESTUDIANTE                 " << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << std::left << std::setw(10) << "Curso"
              << std::setw(10) << "Nota Conocimiento"
              << std::setw(10) << "Nota Producto"
              << std::setw(10) << "Nota Desempeno"
              << std::setw(10) << "Promedio" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    bool encontrado = false;

    for (const auto& nota : notas) {
        if (nota.getEstudianteId() == estudianteId) {
            encontrado = true;
            std::cout << std::left << std::setw(10) << nota.getCursoId()
                      << std::setw(10) << nota.getNota1()
                      << std::setw(10) << nota.getNota2()
                      << std::setw(10) << nota.getNota3()
                      << std::setw(10) << nota.calcularPromedio() << std::endl;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron notas para el estudiante con ID: "
                  << estudianteId << std::endl;
    }

    std::cout << "=========================================================" << std::endl;
}