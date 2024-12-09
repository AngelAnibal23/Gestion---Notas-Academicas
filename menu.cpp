#include "Menu.h"
#include <iostream>
#include <algorithm>

Menu::Menu(const std::vector<Docente>& docentes, const std::vector<Estudiante>& estudiantes, const std::vector<Curso>& cursos, std::vector<Nota>& notas)
    : docentes(docentes), estudiantes(estudiantes), cursos(cursos), notas(notas) {}

void Menu::mostrarMenuDocente() {
    std::string docenteId;
    std::cout << "Ingrese su ID de docente: ";
    std::cin >> docenteId;

    // Buscar el docente por ID
    auto it = std::find_if(docentes.begin(), docentes.end(), [docenteId](const Docente& docente) {
        return docente.getId() == docenteId;
    });

    if (it == docentes.end()) {
        std::cout << "Docente no encontrado." << std::endl;
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;
    std::cout << "1. Ingresar notas" << std::endl;
    std::cout << "2. Ver notas" << std::endl;
    std::cout << "0. Volver" << std::endl;

    int opcion;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            ingresarNotas();
            break;
        case 2:
            mostrarNotas();
            break;
        case 0:
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
}

void Menu::mostrarMenuEstudiante() {
    std::string estudianteId;
    std::cout << "Ingrese su ID de estudiante: ";
    std::cin >> estudianteId;

    // Buscar el estudiante por ID
    auto it = std::find_if(estudiantes.begin(), estudiantes.end(), [estudianteId](const Estudiante& estudiante) {
        return estudiante.getId() == estudianteId;
    });

    if (it == estudiantes.end()) {
        std::cout << "Estudiante no encontrado." << std::endl;
        return;
    }

    std::cout << "Bienvenido, " << it->getNombre() << std::endl;
    std::cout << "1. Ver notas" << std::endl;
    std::cout << "0. Volver" << std::endl;

    int opcion;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            verNotasEstudiante(estudianteId);
            break;
        case 0:
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
    }
}

void Menu::ingresarNotas() {
    std::string estudianteId, cursoId;
    double nota1, nota2, nota3;

    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> estudianteId;
    std::cout << "Ingrese el ID del curso: ";
    std::cin >> cursoId;
    std::cout << "Ingrese la nota 1: ";
    std::cin >> nota1;
    std::cout << "Ingrese la nota 2: ";
    std::cin >> nota2;
    std::cout << "Ingrese la nota 3: ";
    std::cin >> nota3;

    // Buscar la nota existente o crear una nueva
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
}

void Menu::mostrarNotas() {
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
    for (const auto& nota : notas) {
        if (nota.getEstudianteId() == estudianteId) {
            std::cout << "Curso ID: " << nota.getCursoId()
                      << ", Nota 1: " << nota.getNota1()
                      << ", Nota 2: " << nota.getNota2()
                      << ", Nota 3: " << nota.getNota3()
                      << ", Promedio: " << nota.calcularPromedio() << std::endl;
        }
    }
}