#include "gestorArchivos.h"
#include <fstream>
#include <sstream>
#include <iostream> // Para depuración
#include <algorithm>

using namespace std;

vector<Docente> GestorArchivos::cargarDocentes(const string& archivo) {
    vector<Docente> docentes;
    ifstream file(archivo);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, nombre, especialidad;
        if (getline(iss, id, ',') && getline(iss, nombre, ',') && getline(iss, especialidad)) {
            docentes.emplace_back(id, nombre, especialidad); // Usar el constructor de Docente
        }
    }
    return docentes;
}

vector<Estudiante> GestorArchivos::cargarEstudiantes(const string& archivo) {
    vector<Estudiante> estudiantes;
    ifstream file(archivo);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, nombre;
        if (getline(iss, id, ',') && getline(iss, nombre)) {
            estudiantes.emplace_back(id, nombre); // Usar el constructor de Estudiante
        }
    }
    return estudiantes;
}

vector<Curso> GestorArchivos::cargarCursos(const string& archivo) {
    vector<Curso> cursos;
    ifstream file(archivo);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, nombre, docenteId;
        if (getline(iss, id, ',') && getline(iss, nombre, ',') && getline(iss, docenteId)) {
            cursos.emplace_back(id, nombre, docenteId);
        } else {
            cerr << "Error al leer la línea: " << line << endl; // Depuración
        }
    }
    return cursos;
}

vector<Nota> GestorArchivos::cargarNotas() {
    vector<Nota> notasUnidad1 = cargarNotasUnidad("notas_unidad1.txt");
    vector<Nota> notasUnidad2 = cargarNotasUnidad("notas_unidad2.txt");

    // Combinar las notas de ambas unidades
    vector<Nota> notas;
    notas.insert(notas.end(), notasUnidad1.begin(), notasUnidad1.end());
    notas.insert(notas.end(), notasUnidad2.begin(), notasUnidad2.end());

    return notas;
}

vector<Nota> GestorArchivos::cargarNotasUnidad(const string& archivo) {
    vector<Nota> notas;
    ifstream file(archivo);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string estudianteId, cursoId;
        double nota1, nota2, nota3;
        int unidad;

        if (getline(iss, estudianteId, ',') && getline(iss, cursoId, ',') &&
            iss >> nota1 && iss.ignore() && iss >> nota2 && iss.ignore() && iss >> nota3) {
            // Determinar la unidad basándonos en el archivo
            unidad = (archivo == "notas_unidad1.txt") ? 1 : 2;
            notas.emplace_back(estudianteId, cursoId, nota1, nota2, nota3, unidad);
        }
    }

    return notas;
}

void GestorArchivos::guardarNotas(const vector<Nota>& notas) {
   ofstream fileUnidad1("notas_unidad1.txt"); // Sobrescribir el archivo
	ofstream fileUnidad2("notas_unidad2.txt"); // Sobrescribir el archivo

    if (!fileUnidad1.is_open() || !fileUnidad2.is_open()) {
        cerr << "Error al abrir los archivos de notas para escritura." << endl;
        return;
    }

    for (const auto& nota : notas) {
        if (nota.getUnidad() == 1) {
            fileUnidad1 << nota.getEstudianteId() << "," << nota.getCursoId() << ","
                        << nota.getNota1() << "," << nota.getNota2() << "," << nota.getNota3() << endl;
        } else if (nota.getUnidad() == 2) {
            fileUnidad2 << nota.getEstudianteId() << "," << nota.getCursoId() << ","
                        << nota.getNota1() << "," << nota.getNota2() << "," << nota.getNota3() << endl;
        }
    }
}

void GestorArchivos::cargarInscripciones(const string& archivo, vector<Curso>& cursos, const vector<Estudiante>& estudiantes) {
    ifstream file(archivo);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string cursoId, estudianteId;
        if (getline(iss, cursoId, ',') && getline(iss, estudianteId)) {
            auto cursoIt = find_if(cursos.begin(), cursos.end(), [cursoId](const Curso& curso) {
                return curso.getId() == cursoId;
            });

            auto estudianteIt = find_if(estudiantes.begin(), estudiantes.end(), [estudianteId](const Estudiante& estudiante) {
                return estudiante.getId() == estudianteId;
            });

            if (cursoIt != cursos.end() && estudianteIt != estudiantes.end()) {
                cursoIt->agregarEstudiante(*estudianteIt);
            }
        } else {
            cerr << "Error al leer la linea: " << line << endl; // Depuración
        }
    }
}