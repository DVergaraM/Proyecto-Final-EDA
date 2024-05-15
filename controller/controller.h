#include "../model/user.h" // trae los modelos de clases

void crear_tarea(Project *project) // crea tareas, se le pasa el proyecto por parametro
{
    string title, description; // atributos de las tareas
    Date dueDate;
    StatusType status;
    PriorityType priority;
    User *assignee; // apunta al usuario con su id

    cout << "Ingrese el título de la tarea: "; // titulo tarea
    getline(cin, title);
    cout << "Ingrese la descripción de la tarea: "; // descripcion tarea
    getline(cin, description);

    cout << "Ingrese la fecha de vencimiento (DD MM YYYY): "; // fecha vencimiento
    cin >> dueDate.day >> dueDate.month >> dueDate.year;

    cout << "Ingrese el estado de la tarea (0 - Abierto, 1 - En progreso, 2 - Cerrado): ";
    int statusOption; // estado tarea
    cin >> statusOption;
    status = static_cast<StatusType>(statusOption);

    cout << "Ingrese la prioridad de la tarea (0 - Baja, 1 - Media, 2 - Alta): ";
    int priorityOption; // prioridad tarea
    cin >> priorityOption;
    priority = static_cast<PriorityType>(priorityOption);

    cout << "Ingrese el ID del usuario responsable de la tarea: ";
    int assigneeId; // id usuario tarea
    cin >> assigneeId;

    Task newTask(title, description, assignee, dueDate); // crear tarea
    newTask.setStatus(status);
    newTask.setPriority(priority);

    project->getBoard().addTask(newTask); // agrea al proyecto y tablero del proyecto

    cout << "tarea creada" << endl;
}

void asignar_tareas_proyectos(vector<Project *> proyectos)
{
    // Mostrar lista de proyectos disponibles
    cout << "Proyectos disponibles:" << endl;
    for (size_t i = 0; i < proyectos.size(); ++i)
    {
        cout << i + 1 << ". " << proyectos[i]->getTitle() << endl;
    }

    // Solicitar al usuario que seleccione un proyecto
    int proyectoSeleccionado;
    cout << "Seleccione el número del proyecto al que desea asignar la tarea: ";
    cin >> proyectoSeleccionado;

    // Validar la selección del proyecto
    if (proyectoSeleccionado < 1 || proyectoSeleccionado > proyectos.size())
    {
        cout << "Selección de proyecto inválida." << endl;
        return;
    }

    // Obtener el proyecto seleccionado
    Project *proyecto = proyectos[proyectoSeleccionado - 1];

    // Mostrar lista de tareas disponibles
    cout << "Tareas disponibles:" << endl;
    vector<Task> tareas = proyecto->getBoard().getTasks();
    for (size_t i = 0; i < tareas.size(); ++i)
    {
        cout << i + 1 << ". " << tareas[i].getTitle() << endl;
    }

    // Solicitar al usuario que seleccione una tarea
    int tareaSeleccionada;
    cout << "Seleccione el número de la tarea que desea asignar: ";
    cin >> tareaSeleccionada;

    // Validar la selección de la tarea
    if (tareaSeleccionada < 1 || tareaSeleccionada > tareas.size())
    {
        cout << "Selección de tarea inválida." << endl;
        return;
    }

    // Obtener la tarea seleccionada
    Task tarea = tareas[tareaSeleccionada - 1];

    // Asignar la tarea al proyecto
    proyecto->getBoard().addTask(tarea);

    cout << "Tarea asignada al proyecto exitosamente." << endl;
}

void ver_tareas_proyectos(const vector<Project *> &proyectos)
{
    // Mostrar lista de proyectos disponibles
    cout << "Proyectos disponibles:" << endl;
    for (size_t i = 0; i < proyectos.size(); ++i)
    {
        cout << i + 1 << ". " << proyectos[i]->getTitle() << endl;
    }

    // Solicitar al usuario que seleccione un proyecto
    int proyectoSeleccionado;
    cout << "Seleccione el número del proyecto del cual desea ver las tareas: ";
    cin >> proyectoSeleccionado;

    // Validar la selección del proyecto
    if (proyectoSeleccionado < 1 || proyectoSeleccionado > proyectos.size())
    {
        cout << "Selección de proyecto inválida." << endl;
        return;
    }

    // Obtener el proyecto seleccionado
    Project *proyecto = proyectos[proyectoSeleccionado - 1];

    // Obtener las tareas asociadas al proyecto
    vector<Task> tareas = proyecto->getBoard().getTasks();

    // Mostrar las tareas
    cout << "Tareas asociadas al proyecto '" << proyecto->getTitle() << "':" << endl;
    for (const auto &tarea : tareas)
    {
        cout << "Nombre: " << tarea.getTitle() << endl;
        cout << "Estado: " << statusToString(tarea.getStatus()) << endl;
        cout << "Prioridad: " << priorityToString(tarea.getPriority()) << endl;
        cout << "Responsable: ";
        if (tarea.getAssignee() != nullptr)
        {
            cout << tarea.getAssignee()->getUsername() << endl;
        }
        else
        {
            cout << "No asignado" << endl;
        }
        cout << endl;
    }
}
