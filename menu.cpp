#include "menu.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

Menu::Menu(const std::vector<Docente>& docentes, const std::vector<Estudiante>& estudiantes, std::vector<Curso>& cursos, std::vector<Nota>& notas)
    : docentes(docentes), estudiantes(estudiantes), cursos(cursos), notas(notas) {}

void Menu::mostrarMenuDocente() {
    int opcion;
    std::string docenteId;
    std::cout << "Ingrese su ID de docente: ";
    std::cin >> docenteId;

    // Buscar el docente por ID
    auto it = std::find_if(docentes.begin(), docentes.end(), [docenteId](const Docente& docente) {
        return docente.getId() == docenteId;
    });

    if (it == docentes.end()) {
        std::cout << "Docente no encontrado." << std::endl;
        system("PAUSE");
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;

    do {
        system("cls");
        std::cout << "===== MENU DOCENTE =====" << std::endl;
        std::cout << "1. Ingresar notas" << std::endl;
        std::cout << "2. Ver notas" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ingresarNotas(docenteId);
                break;
            case 2:
                mostrarNotas();
                system("PAUSE");
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
                system("PAUSE");
        }
    } while (opcion != 0);
}

void Menu::mostrarMenuEstudiante() {
    int opcion;
    std::string estudianteId;
    std::cout << "Ingrese su ID de estudiante: ";
    std::cin >> estudianteId;

    // Buscar el estudiante por ID
    auto it = std::find_if(estudiantes.begin(), estudiantes.end(), [estudianteId](const Estudiante& estudiante) {
        return estudiante.getId() == estudianteId;
    });

    if (it == estudiantes.end()) {
        std::cout << "Estudiante no encontrado." << std::endl;
        system("PAUSE");
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;

    do {
        system("cls");
        std::cout << "===== MENU ESTUDIANTE =====" << std::endl;
        std::cout << "1. Ver notas" << std::endl;
        std::cout << "0. Volver" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                verNotasEstudiante(estudianteId);
                system("PAUSE");
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
                system("PAUSE");
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
    std::string cursoId;
    std::cout << "Ingrese el ID del curso: ";
    std::cin >> cursoId;

    // Buscar el curso por ID
    auto cursoIt = std::find_if(cursos.begin(), cursos.end(), [cursoId](const Curso& curso) {
        return curso.getId() == cursoId;
    });

    if (cursoIt == cursos.end() || cursoIt->getDocenteId() != docenteId) {
        std::cout << "Curso no encontrado o no asignado a este docente." << std::endl;
        system("PAUSE");
        return;
    }

    std::cout << "Lista de estudiantes inscritos en el curso " << cursoId << ":" << std::endl;
    for (const auto& estudiante : cursoIt->getEstudiantes()) {
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
              << std::setw(10) << "Nota 1"
              << std::setw(10) << "Nota 2"
              << std::setw(10) << "Nota 3"
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