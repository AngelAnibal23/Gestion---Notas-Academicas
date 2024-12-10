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
            docentes.emplace_back(id, nombre, especialidad);
        } else {
            std::cerr << "Error al leer la linea: " << line << std::endl; // Depuración
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
            estudiantes.emplace_back(id, nombre);
        } else {
            std::cerr << "Error al leer la linea: " << line << std::endl; // Depuración
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

std::vector<Nota> GestorArchivos::cargarNotas(const std::string& archivo) {
    std::vector<Nota> notas;
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string estudianteId, cursoId;
        double nota1, nota2, nota3;
        if (std::getline(iss, estudianteId, ',') && std::getline(iss, cursoId, ',') && iss >> nota1 && iss.ignore() && iss >> nota2 && iss.ignore() && iss >> nota3) {
            notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3);
        } else {
            std::cerr << "Error al leer la linea: " << line << std::endl; // Depuración
        }
    }
    return notas;
}

void GestorArchivos::guardarNotas(const std::string& archivo, const std::vector<Nota>& notas) {
    std::ofstream file(archivo);
    for (const auto& nota : notas) {
        file << nota.getEstudianteId() << "," << nota.getCursoId() << ","
             << nota.getNota1() << "," << nota.getNota2() << "," << nota.getNota3() << std::endl;
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