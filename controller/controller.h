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

void responsables_por_nombre(const vector<Task> &tareas)
{

    vector<const User *> responsables;
    for (const Task &tarea : tareas)
    {
        const User *responsable = tarea.getAssignee();
        if (responsable != nullptr)
        {
            responsables.push_back(responsable);
        }
    }

    sort(responsables.begin(), responsables.end(), [](const User *a, const User *b)
         { return a->getUsername() < b->getUsername(); });

    // Mostramos la lista ordenada de responsables por nombre
    cout << "Responsables de tareas ordenados por nombre:" << endl;
    for (const User *responsable : responsables)
    {
        cout << "- " << responsable->getUsername() << endl;
    }
}

// Enumeración para la frecuencia de repetición
enum class RecurrenceFrequency
{
    DIARIA,
    SEMANAL,
    MENSUAL
};

// Clase para representar una actividad recurrente
class RecurringActivity
{
private:
    string title;
    string description;
    RecurrenceFrequency frequency;

public:
    // Constructor
    RecurringActivity(const string &title, const string &description, RecurrenceFrequency frequency)
        : title(title), description(description), frequency(frequency) {}

    // Método para obtener la frecuencia de repetición como cadena de caracteres
    string getFrequencyAsString() const
    {
        switch (frequency)
        {
        case RecurrenceFrequency::DIARIA:
            return "Diaria";
        case RecurrenceFrequency::SEMANAL:
            return "Semanal";
        case RecurrenceFrequency::MENSUAL:
            return "Mensual";
        default:
            return "Desconocida";
        }
    }

    // Método para imprimir los detalles de la actividad recurrente
    void printDetails() const
    {
        cout << "Título: " << title << endl;
        cout << "Descripción: " << description << endl;
        cout << "Frecuencia de repetición: " << getFrequencyAsString() << endl;
    }
};

// Función para crear actividades recurrentes
void actividades_recurrentes()
{
    // Solicitar al usuario los detalles de la actividad recurrente
    string titulo, descripcion;
    int opcion_frecuencia;

    cout << "Ingrese el título de la actividad: ";
    getline(cin >> ws, titulo);

    cout << "Ingrese la descripción de la actividad: ";
    getline(cin >> ws, descripcion);

    cout << "Seleccione la frecuencia de repetición:" << std::endl;
    cout << "1. Diaria" << endl;
    cout << "2. Semanal" << endl;
    cout << "3. Mensual" << endl;
    cout << "Opción: ";
    cin >> opcion_frecuencia;

    // Validar la opción de frecuencia
    RecurrenceFrequency frecuencia;
    switch (opcion_frecuencia)
    {
    case 1:
        frecuencia = RecurrenceFrequency::DIARIA;
        break;
    case 2:
        frecuencia = RecurrenceFrequency::SEMANAL;
        break;
    case 3:
        frecuencia = RecurrenceFrequency::MENSUAL;
        break;
    default:
        cout << "Opción de frecuencia inválida. La actividad no se programó." << endl;
        return;
    }

    // Crear la actividad recurrente
    RecurringActivity actividad_recurrente(titulo, descripcion, frecuencia);

    // Imprimir los detalles de la actividad recurrente
    cout << endl
         << "Actividad recurrente creada exitosamente:" << endl;
    actividad_recurrente.printDetails();
}
