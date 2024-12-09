#include "gestorArchivos.h"
#include <fstream>
#include <sstream>

std::vector<Docente> GestorArchivos::cargarDocentes(const std::string& archivo) {
    std::vector<Docente> docentes;
    std::ifstream file(archivo);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, nombre, especialidad;
        iss >> id >> nombre >> especialidad;
        docentes.emplace_back(id, nombre, especialidad);
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
        iss >> id >> nombre;
        estudiantes.emplace_back(id, nombre);
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
        iss >> id >> nombre >> docenteId;
        cursos.emplace_back(id, nombre, docenteId);
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
        iss >> estudianteId >> cursoId >> nota1 >> nota2 >> nota3;
        notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3);
    }
    return notas;
}

void GestorArchivos::guardarNotas(const std::string& archivo, const std::vector<Nota>& notas) {
    std::ofstream file(archivo);
    for (const auto& nota : notas) {
        file << nota.getEstudianteId() << " " << nota.getCursoId() << " "
             << nota.getNota1() << " " << nota.getNota2() << " " << nota.getNota3() << std::endl;
    }
}