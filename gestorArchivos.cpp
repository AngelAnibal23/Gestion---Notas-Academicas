#include "gestorArchivos.h"
#include <fstream>
#include <sstream>
#include <iostream> // Para depuración
#include <algorithm>

std::vector<Docente> GestorArchivos::cargarDocentes(const std::string& archivo) {
    std::vector<Docente> docentes;
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, nombre, especialidad;
        if (std::getline(iss, id, ',') && std::getline(iss, nombre, ',') && std::getline(iss, especialidad)) {
            docentes.emplace_back(id, nombre, especialidad); // Usar el constructor de Docente
        }
    }
    return docentes;
}

std::vector<Estudiante> GestorArchivos::cargarEstudiantes(const std::string& archivo) {
    std::vector<Estudiante> estudiantes;
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, nombre;
        if (std::getline(iss, id, ',') && std::getline(iss, nombre)) {
            estudiantes.emplace_back(id, nombre); // Usar el constructor de Estudiante
        }
    }
    return estudiantes;
}

std::vector<Curso> GestorArchivos::cargarCursos(const std::string& archivo) {
    std::vector<Curso> cursos;
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, nombre, docenteId;
        if (std::getline(iss, id, ',') && std::getline(iss, nombre, ',') && std::getline(iss, docenteId)) {
            cursos.emplace_back(id, nombre, docenteId);
        } else {
            std::cerr << "Error al leer la línea: " << line << std::endl; // Depuración
        }
    }
    return cursos;
}

std::vector<Nota> GestorArchivos::cargarNotas() {
    std::vector<Nota> notasUnidad1 = cargarNotasUnidad("notas_unidad1.txt");
    std::vector<Nota> notasUnidad2 = cargarNotasUnidad("notas_unidad2.txt");

    // Combinar las notas de ambas unidades
    std::vector<Nota> notas;
    notas.insert(notas.end(), notasUnidad1.begin(), notasUnidad1.end());
    notas.insert(notas.end(), notasUnidad2.begin(), notasUnidad2.end());

    return notas;
}

std::vector<Nota> GestorArchivos::cargarNotasUnidad(const std::string& archivo) {
    std::vector<Nota> notas;
    std::ifstream file(archivo);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string estudianteId, cursoId;
        double nota1, nota2, nota3;
        int unidad;

        if (std::getline(iss, estudianteId, ',') && std::getline(iss, cursoId, ',') &&
            iss >> nota1 && iss.ignore() && iss >> nota2 && iss.ignore() && iss >> nota3) {
            // Determinar la unidad basándonos en el archivo
            unidad = (archivo == "notas_unidad1.txt") ? 1 : 2;
            notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3, unidad);
        }
    }

    return notas;
}

void GestorArchivos::guardarNotas(const std::vector<Nota>& notas) {
   std::ofstream fileUnidad1("notas_unidad1.txt"); // Sobrescribir el archivo
    std::ofstream fileUnidad2("notas_unidad2.txt"); // Sobrescribir el archivo

    if (!fileUnidad1.is_open() || !fileUnidad2.is_open()) {
        std::cerr << "Error al abrir los archivos de notas para escritura." << std::endl;
        return;
    }

    for (const auto& nota : notas) {
        if (nota.getUnidad() == 1) {
            fileUnidad1 << nota.getEstudianteId() << "," << nota.getCursoId() << ","
                        << nota.getNota1() << "," << nota.getNota2() << "," << nota.getNota3() << std::endl;
        } else if (nota.getUnidad() == 2) {
            fileUnidad2 << nota.getEstudianteId() << "," << nota.getCursoId() << ","
                        << nota.getNota1() << "," << nota.getNota2() << "," << nota.getNota3() << std::endl;
        }
    }
}

void GestorArchivos::cargarInscripciones(const std::string& archivo, std::vector<Curso>& cursos, const std::vector<Estudiante>& estudiantes) {
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cursoId, estudianteId;
        if (std::getline(iss, cursoId, ',') && std::getline(iss, estudianteId)) {
            auto cursoIt = std::find_if(cursos.begin(), cursos.end(), [cursoId](const Curso& curso) {
                return curso.getId() == cursoId;
            });

            auto estudianteIt = std::find_if(estudiantes.begin(), estudiantes.end(), [estudianteId](const Estudiante& estudiante) {
                return estudiante.getId() == estudianteId;
            });

            if (cursoIt != cursos.end() && estudianteIt != estudiantes.end()) {
                cursoIt->agregarEstudiante(*estudianteIt);
            }
        } else {
            std::cerr << "Error al leer la linea: " << line << std::endl; // Depuración
        }
    }
}