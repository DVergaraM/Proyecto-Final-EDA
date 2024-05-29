#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

//Funcion para visualizar los proyectos
void viewProject(const vector<Project*>& projects) {
        for (const auto& project : projects) {
            if (project->getTitle() == title) {
                cout << "Project Title: " << project->getTitle() << endl;
                cout << "Owner: " << project->getOwner()->getUsername() << endl;
                cout << "Board Title: " << project->getBoard().getTitle() << endl;
                cout << "Tasks: " << endl;
                project->getBoard().showTasks();
                cout << "------------------------" << endl;
                return;
            }
        }
        cout << "Project not found" << endl;
    }

//Funcion para añadir las notas (obviamente agregar get y set para las notas)
//tarea
void addNote(User *author, string title, string content)
    {
        Note note;
        note.author = author;
        note.title = title;
        note.content = content;
        notes.push(note);
    }

    void agregarNotaATarea(Task& tarea, User *currentUser) {
    string title, content;

    cout << "Ingrese el título de la nota: ";
    getline(cin, title);

    cout << "Ingrese el contenido de la nota: ";
    getline(cin, content);

    tarea.addNote(currentUser, title, content);
}
//proyecto
void agregarNotaAProyecto(Project& proyecto, User& usuarioActual) {
    string titulo, contenido;

    cout << "Ingrese el título de la nota: ";
    getline(cin, titulo);

    cout << "Ingrese el contenido de la nota: ";
    getline(cin, contenido);

    proyecto.addNote(usuarioActual, titulo, contenido);
}

//cambiar estado de tarea
void setEstadoTarea(Task& tarea, StatusType estado) {
        int eleccion;
        cout<<"Ingrese el estado de la tarea: "<<endl;
        cout<<"0. Abierto"<<endl;
        cout<<"1. En progreso"<<endl;
        cout<<"2. En revisión de código"<<endl;
        cout<<"3. Lista para ser fusionada"<<endl;
        cout<<"4. Cerrado"<<endl;
        cin>>eleccion;

        StatusType estado = static_cast<StatusType>(eleccion);
        tarea.setStatus(estado);
    }
//visualizar notas de tareas

void showNotes()
    {
        if (notes.empty())
        {
            cout << "No hay notas que mostrar" << endl;
            return;
        }
        // Mostrar las notas
        stack<Note> temp = notes;
        while (!temp.empty())
        {
            cout << temp.top().getTitle() << ": " << temp.top().getContent() << endl;
            temp.pop();
        }
    }

//visualizar notas de proyectos

void visualizarNotasDelProyecto(const Project& proyecto) {
    vector<Note> notas = proyecto.getNotes();

    cout << "Notas para el proyecto " << proyecto.getTitle() << ":\n";

    // Mostrar las notas
    for (const Note& nota : notas) {
        cout << "Título: " << nota.getTitle() << "\n";
        cout << "Contenido: " << nota.getContent() << "\n";
        cout << "Autor: " << nota.getAuthor().getUsername() << "\n";
        cout << "------------------------\n";
    }
}

//ordenar tareas por prioridad
void mostrarTareasOrdenadasPorPrioridad(Project& proyecto) {
    // Obtener las tareas del proyecto
    vector<Task> tareas = proyecto.getTasks();

    // Ordenar las tareas por prioridad
    sort(tareas.begin(), tareas.end(), [](const Task& a, const Task& b) {
        return a.getPriority() > b.getPriority();
    });

    // Mostrar las tareas
    for (const Task& tarea : tareas) {
        cout << "Título: " << tarea.getTitle() << "\n";
        cout << "Prioridad: " << tarea.getPriority() << "\n";
        cout << "------------------------\n";
    }
}

//ordenar tareas por estado
void mostrarTareasOrdenadasPorEstado(Project& proyecto) {
    // Obtener las tareas del proyecto
    vector<Task> tareas = proyecto.getTasks();

    // Ordenar las tareas por estado
    sort(tareas.begin(), tareas.end(), [](const Task& a, const Task& b) {
        return a.getState() < b.getState();
    });

    // Mostrar las tareas
    for (const Task& tarea : tareas) {
        cout << "Título: " << tarea.getTitle() << "\n";
        cout << "Estado: " << tarea.getState() << "\n";
        cout << "------------------------\n";
    }
}

