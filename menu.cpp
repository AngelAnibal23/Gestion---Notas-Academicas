#include "menu.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include "usuario.h" 
#include "docente.h"
#include "estudiante.h"
#include <map>
#include "gestorArchivos.h"

using namespace std; 

vector<Nota> notas = GestorArchivos::cargarNotas();

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
    cout << "\t\t\t\tCursos que dicta el docente con ID: " << docenteId <<  endl;
    cout << "\t\t\t\t---------------------------------------------------------" <<  endl;
    cout << left << setw(10) << "\t\t\t\tID" << setw(40) << "   Nombre del Curso" << endl;
    cout << "\t\t\t\t---------------------------------------------------------" << endl;

    for (const auto& curso : cursos) {
        if (curso.getDocenteId() == docenteId) {
            cout << std::left << "\t\t\t\t" << setw(10) << curso.getId() << setw(40) << curso.getNombre() << endl;
        }
    }

    cout << "\t\t\t\t---------------------------------------------------------" << endl;
    cout << endl; 
}

void Menu::mostrarMenuDocente() {
   	
    int opcion;
    string docenteId;
    
    cout << "\t\t\t\t\t\t\t\tIngrese su ID de docente: ";
    cin >> docenteId;
	system("cls");

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
        cout << "\t\t\t\tDocente no encontrado." << endl;
        system("PAUSE");
        system("cls"); 
        return;
    }

    //cout << "Bienvenido, " << it->getNombre() << endl;

    do {
        //system("cls");       
        cout << "\t\t\t\t\t\t\t==================MENU DOCENTE==================" << endl;
        cout << "\t\t\t\t\t\t\t|Bienvenido, " << it->getNombre() << "\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t1.- Ingresar Notas.       \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t2.- Mostrar Registro de Notas Ingresadas. \t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t0.- Salir.                \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|_______________________________________________|" << endl;
		cout << endl << "\t\t\t\t\t\t\t\t \tIngrese la respuesta: ";
		cin >> opcion;
		system("cls");
    	
        switch (opcion) {
            case 1:
                // Mostrar los cursos disponibles del docente
                
                ingresarNotas(docenteId);
                break;
            case 2:
                mostrarNotas(docenteId);
                system("PAUSE");
                system("cls"); 
                break;
            case 0:
            	system("cls"); 
                break;
            default:
                std::cout << "\t\t\t\tOpcion no valida." << endl;
                system("PAUSE");
                system("cls"); 
        }
    } while (opcion != 0);

}

void Menu::mostrarMenuEstudiante() {
    int opcion;
	string estudianteId;
    cout << "\t\t\t\tIngrese su ID de estudiante: ";
    cin >> estudianteId;
	system("cls");
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
         cout << "\t\t\t\t\t\t\t\tIngrese su ID de estudiante: ";
        system("PAUSE");
        system("cls");
        return;
    }

    do {
        //system("cls");
        cout << "\t\t\t\t\t\t\t==================MENU ESTUDIANTE==============" << endl;
		 cout << "\t\t\t\t\t\t\t|Bienvenido, " << it->getNombre() << "\t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t1.- Mostrar notas.        \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t0.- Salir.                \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|\t\t                          \t\t|" << endl;
		cout << "\t\t\t\t\t\t\t|_______________________________________________|" << endl;
		cout << endl << "\t\t\t\t\t\t\t\t \tIngrese la respuesta: ";
		cin >> opcion;
		system("cls");

        switch (opcion) {
            case 1:
               //verNotasEstudiante(estudianteId);
                verNotasEstudiante(estudianteId); 
                system("PAUSE");
                system("cls");
                break;
            case 0:
            	system("cls"); 
                break;
            default:
                cout << "\t\t\t\tOpcion no valida." << endl;
                system("PAUSE");
                system("cls");
        }
    } while (opcion != 0);
}

void Menu::mostrarContenidoArchivoEstudiantes() {
    ifstream file("estudiantes.txt");
    if (!file.is_open()) {
        cout << "\t\t\t\tNo se pudo abrir el archivo de estudiantes." << endl;
        return;
    }

    string line;
    while ( getline(file, line)) {
        cout << "\t\t\t\t " <<line << endl;
    }
    file.close();
}

void Menu::mostrarNotas(const string& idDocente) {
    system("cls");

    // Ordenar las notas usando ShellSort
    shellSort(notas);

    cout << "\t\t\t\t====================================================================================" << endl;
    cout << "\t\t\t\t                    REGISTRO DE NOTAS INGRESADAS POR EL DOCENTES" << endl;
    cout << "\t\t\t\t====================================================================================" << endl;

    // Crear un mapa para agrupar las notas por estudiante y curso, pero solo para el docente actual
    map<pair<string, string>, vector<Nota>> notasPorEstudianteCurso;

    for (const auto& nota : notas) {
        // Filtrar las notas por el idDocente
        for (const auto& curso : cursos) {
            if (curso.getId() == nota.getCursoId() && curso.getDocenteId() == idDocente) {
                notasPorEstudianteCurso[{nota.getEstudianteId(), nota.getCursoId()}].push_back(nota);
                break; // Salir del bucle una vez que se encuentra el curso
            }
        }
    }

    // Mostrar las notas de ambas unidades en secciones separadas
    for (const auto& par : notasPorEstudianteCurso) {
        const string& estudianteId = par.first.first;
        const string& cursoId = par.first.second;
        const vector<Nota>& notasDelEstudiante = par.second;

        // Variables para almacenar las notas de ambas unidades
        double nota1Unidad1 = 0, nota2Unidad1 = 0, nota3Unidad1 = 0;
        double nota1Unidad2 = 0, nota2Unidad2 = 0, nota3Unidad2 = 0;

        for (const auto& nota : notasDelEstudiante) {
            if (nota.getUnidad() == 1) {
                nota1Unidad1 = nota.getNota1();
                nota2Unidad1 = nota.getNota2();
                nota3Unidad1 = nota.getNota3();
            } else if (nota.getUnidad() == 2) {
                nota1Unidad2 = nota.getNota1();
                nota2Unidad2 = nota.getNota2();
                nota3Unidad2 = nota.getNota3();
            }
        }

        // Calcular el promedio final de ambas unidades
        double promedioFinal = (nota1Unidad1 + nota2Unidad1 + nota3Unidad1 + nota1Unidad2 + nota2Unidad2 + nota3Unidad2) / 6.0;

        // Mostrar las notas de ambas unidades en secciones separadas
        cout << left << setw(15) <<"\t\t\t\ "<< estudianteId
                  << setw(20) << "    "<<cursoId << endl;
        cout << "\t\t\t\tUnidad 1:" << endl;
        cout << setw(15) << ""
                  << setw(15) << "\t\t\t\Nota EC"
                  << setw(15) << "\t\t\t\Nota EP"
                  << setw(15) << "\t\t\t\Nota ED" << endl;
        cout << setw(15) << ""
                  << setw(15) <<"\t\t\t\ " << nota1Unidad1
                  << setw(15) <<"\t\t\t\ " << nota2Unidad1
                  << setw(15) <<"\t\t\t\ " << nota3Unidad1 << endl;
        cout << "\t\t\t\tUnidad 2:" << endl;
        cout << setw(15) << ""
                  << setw(15) << "\t\t\t\Nota EC"
                  << setw(15) << "\t\t\t\Nota EP"
                  << setw(15) << "\t\t\t\Nota ED" << endl;
        cout << setw(15) << ""
                  << setw(15) <<"\t\t\t\ " << nota1Unidad2
                  << setw(15) <<"\t\t\t\ " << nota2Unidad2
                  << setw(15) <<"\t\t\t\ " << nota3Unidad2 << endl;
        cout << "\t\t\t\t---------------------------------------------------------" << endl;
        cout << "\t\t\t\tPromedio Final: " << promedioFinal << endl;
        cout << "\t\t\t\t---------------------------------------------------------" << endl;
    }

    cout << "\t\t\t\t=========================================================" << endl;
}

void Menu::verNotasEstudiante(const string& estudianteId) {
     system("cls");
    shellSort(notas);
    cout << "\t\t\t\t=========================================================" << endl;
    cout << "\t\t\t\t                    NOTAS DEL ESTUDIANTE                 " << endl;
    cout << "\t\t\t\t=========================================================" << endl;

    bool encontrado = false;

    // Crear un mapa para agrupar las notas por curso
    map<string, vector<Nota>> notasPorCurso;

    for (const auto& nota : notas) {
        if (nota.getEstudianteId() == estudianteId) {
            notasPorCurso[nota.getCursoId()].push_back(nota);
        }
    }

    // Mostrar las notas de ambas unidades en secciones separadas
    for (const auto& par : notasPorCurso) {
        const string& cursoId = par.first;
        const vector<Nota>& notasDelCurso = par.second;

        // Variables para almacenar las notas de ambas unidades
        double nota1Unidad1 = 0, nota2Unidad1 = 0, nota3Unidad1 = 0;
        double nota1Unidad2 = 0, nota2Unidad2 = 0, nota3Unidad2 = 0;

        for (const auto& nota : notasDelCurso) {
            if (nota.getUnidad() == 1) {
                nota1Unidad1 = nota.getNota1();
                nota2Unidad1 = nota.getNota2();
                nota3Unidad1 = nota.getNota3();
            } else if (nota.getUnidad() == 2) {
                nota1Unidad2 = nota.getNota1();
                nota2Unidad2 = nota.getNota2();
                nota3Unidad2 = nota.getNota3();
            }
        }

        // Calcular el promedio final de ambas unidades
        double promedioFinal = (nota1Unidad1 + nota2Unidad1 + nota3Unidad1 + nota1Unidad2 + nota2Unidad2 + nota3Unidad2) / 6.0;

        // Mostrar las notas de ambas unidades en secciones separadas
        cout << left << setw(20) << "\t\t\t\ " << cursoId << endl;
        cout << "\t\t\t\tUnidad 1:" << endl;
        cout << setw(15) << ""
                  << setw(15) << "\t\t\t\Nota EC"
                  << setw(15) << "\t\t\t\Nota EP"
                  << setw(15) << "\t\t\t\Nota ED" << endl;
        cout << setw(15) << ""
                  << setw(15) <<"\t\t\t\ " << nota1Unidad1
                  << setw(15) <<"\t\t\t\ " << nota2Unidad1
                  << setw(15) <<"\t\t\t\ " << nota3Unidad1 << endl;
        cout << "\t\t\t\tUnidad 2:" << endl;
        cout << setw(15) << ""
                  << setw(15) << "\t\t\t\Nota EC"
                  << setw(15) << "\t\t\t\Nota EP"
                  << setw(15) << "\t\t\t\Nota ED" << endl;
        cout << setw(15) << ""
                  << setw(15) <<"\t\t\t\ " << nota1Unidad2
                  << setw(15) <<"\t\t\t\ " << nota2Unidad2
                  << setw(15) <<"\t\t\t\ " << nota3Unidad2 << endl;
        cout << "\t\t\t\t---------------------------------------------------------" << endl;
        cout << "\t\t\t\tPromedio Final: " << promedioFinal << endl;
        cout << "\t\t\t\t---------------------------------------------------------" << endl;
    }

    if (!encontrado) {
        cout << "\t\t\t\tNo hay mas notas registradas por el momento " << endl;
    }

    cout << "\t\t\t\t=========================================================" << endl;
}
