#include "../model/user.h"
#include <deque>

deque<User> users;
set<Project> projects;
set<string> projectsTitles;
set<User *> projectsOwners;
set<StatusType> projectStates;
set<string> projectsDescriptions;

/**
 * @brief Verifica si la fecha es válida.
 * @param date Fecha a validar.
 * @return bool
 */
bool isDateValid(const string &date)
{
    if (date.size() != 10)
        return false;
    if (date[2] != ' ' || date[5] != ' ')
        return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (year < 1900 || year > 2053)
        return false;

    return true;
}

/**
 * @brief Crea un proyecto nuevo para el usuario dado.
 * @param user El usuario quien creará el proyecto.
 * @return void
 */
void createProject(User &user)
{
    Project newProject;
    int id;
    string title;
    string description;

    do
    {
        id = rand() % 1000 + 1;
    } while (find_if(projects.begin(), projects.end(), [id](const Project &project)
                     { return project.getId() == id; }) != projects.end());

    cout << "Ingresa el título del proyecto: ";
    getline(cin >> ws, title);
    cout << "Ingresa la descripción del proyecto: ";
    getline(cin >> ws, description);

    newProject.setId(id);
    newProject.setOwner(&user);
    newProject.setTitle(title);
    newProject.setDescription(description);
    newProject.addMember(&user);
    user.addProject(&newProject);
    projects.insert(newProject);
    projectsTitles.insert(title);
    projectsOwners.insert(&user);
    projectsDescriptions.insert(description);
    projectStates.insert(newProject.getBoard().getState());
    cout << "¡Proyecto creado exitosamente!" << endl;
}

/**
 * @brief Actualiza un proyecto existente.
 * @param project Proyecto a actualizar.
 * @return void
 */
void updateProject(Project &project)
{
    int choice;
    string newTitle;
    string newDescription;

    cout << "¿Qué quieres editar?: " << endl;
    cout << "1. Título" << endl;
    cout << "2. Descripción" << endl;
    cout << "Ingresa tu opción: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Ingresa el nuevo título: ";
        getline(cin >> ws, newTitle);
        project.setTitle(newTitle);
        cout << "Título actualizado correctamente" << endl;
        break;
    case 2:
        cout << "Ingresa la nueva descripción: ";
        getline(cin >> ws, newDescription);
        project.setDescription(newDescription);
        cout << "Descripción actualizada correctamente" << endl;
        break;
    default:
        cout << "¡Opción inválida!" << endl;
        break;
    }
}

/**
 * @brief Muestra la información sobre un proyecto, si este es encontrado.
 * @param project Proyecto a buscar.
 * @return void
 */
void getProjectInfo(const Project &project)
{
    auto it = projects.find(project);
    if (it == projects.end())
    {
        cout << "¡Proyecto no encontrado!" << endl;
        return;
    }

    cout << "Título del proyecto: " << project.getTitle() << endl;
    cout << "Descripción del proyecto: " << project.getDescription() << endl;
    cout << "Dueño del proyecto: " << project.getOwner()->getUsername() << endl;
    cout << "Estado del proyecto: " << project.getBoard().getStateString() << endl;
    cout << endl;
}

/**
 * @brief Agrega un usuario a una tarea.
 * @param task Tarea a la cual asignar un usuario.
 * @param user Usuario que será agregado a la tarea.
 * @return void
 */
void addAssigneeToTask(Task &task, User &user)
{
    task.addAssignee(&user);
    cout << "¡Asignado agregado exitosamente!" << endl;
}

/**
 * @brief Escoge entre los usuarios, quienes serán asignados a la tarea.
 * @param task Tarea a la cual se le asignará usuarios.
 * @return void
 */
void chooseUsersForTask(Task &task)
{
    int choice;
    cout << "Escoge asignados para la tarea: " << endl;
    for (size_t i = 0; i < users.size(); i++)
    {
        cout << i + 1 << ". " << users[i].getUsername() << endl;
    }
    cout << "0. Salir" << endl;
    while (true)
    {
        cout << "Ingresa tu opción: ";
        cin >> choice;
        if (choice == 0)
            break;
        if (choice < 1 || choice > users.size())
        {
            cout << "¡Opción inválida!" << endl;
            continue;
        }
        addAssigneeToTask(task, users[choice - 1]);
    }
}

/**
 * @brief Muestra los estados de las tareas en un proyecto.
 * @param project Proyecto al cual se le mostrarán los estados de tarea.
 * @return void
 */
void showStatesForTasks(Project &project)
{
    if (projects.find(project) == projects.end())
    {
        cout << "¡Proyecto no encontrado!" << endl;
        return;
    }
    Board board = project.getBoard();
    map<PriorityType, queue<Task>> taskQueues = board.getTaskQueues();
    if (taskQueues.empty())
    {
        cout << "No hay tareas para mostrar" << endl;
    }
    else
    {
        cout << "Tareas: " << endl;
        for (auto &taskQueue : taskQueues)
        {
            cout << "Prioridad: " << taskQueue.first << endl;
            queue<Task> tasks = taskQueue.second;
            while (!tasks.empty())
            {
                Task task = tasks.front();
                cout << "Tarea: " << task.getTitle() << " Estado: " << task.getStatus() << endl;
                tasks.pop();
            }
        }
    }
}

/**
 * @brief Muestra los proyectos de un usuario, organizados por su fecha de creación
 * @param user Usuario al que se le mostrarán sus proyectos
 * @return void
 */
void showProjectsByCreationDate(User &user)
{
    vector<Project *> userProjects(user.getProjects()->begin(), user.getProjects()->end());
    sort(userProjects.begin(), userProjects.end(), [](Project *a, Project *b)
         { return a->getCreationDate() < b->getCreationDate(); });
    for (auto project : userProjects)
    {
        cout << "Título del proyecto: " << project->getTitle() << endl;
        cout << "Fecha de creación del proyecto: " << project->getCreationDate() << endl;
        cout << endl;
    }
}

/**
 * @brief Muestra los proyectos de un usuario, organizados por su fecha de vencimiento
 * @param user Usuario al que se le mostrarán sus proyectos
 * @return void
 */
void showProjectsByDueDate(User &user)
{
    vector<Project *> userProjects(user.getProjects()->begin(), user.getProjects()->end());
    sort(userProjects.begin(), userProjects.end(), [](Project *a, Project *b)
         { return a->getDueDate() < b->getDueDate(); });
    for (auto project : userProjects)
    {
        cout << "Título del proyecto: " << project->getTitle() << endl;
        cout << "Fecha de vencimiento del proyecto: " << project->getDueDate() << endl;
        cout << endl;
    }
}

/**
 * @brief Permite al usuario ver sus proyectos organizados por fecha.
 * @param user Usuario al que se le mostrarán sus proyectos
 * @return void
 */
void showProjectsSorted(User &user)
{
    int choice;
    cout << "Ordenar proyectos por: " << endl;
    cout << "1. Fecha de creación" << endl;
    cout << "2. Fecha de vencimiento" << endl;
    cout << "Ingresa tu opción: ";
    cin >> choice;

    if (choice == 1)
    {
        showProjectsByCreationDate(user);
    }
    else if (choice == 2)
    {
        showProjectsByDueDate(user);
    }
    else
    {
        cout << "¡Opción inválida!" << endl;
    }
}

/**
 * @brief Busca por el nombre de un proyecto con respecto al usuario.
 * @param user Usuario al que se le buscará el nombre del proyecto
 * @param projectName Nombre del proyecto
 * @return void
 */
void searchProject(const User &user, const string &projectName)
{
    const auto &userProjects = *user.getProjects();
    if (userProjects.empty())
    {
        cout << "No hay proyectos para mostrar" << endl;
        return;
    }

    for (const auto &project : userProjects)
    {
        if (project->getTitle() == projectName)
        {
            getProjectInfo(*project);
            return;
        }
    }
    cout << "¡Proyecto no encontrado!" << endl;
}

/**
 * @brief Muestra las tareas que están relacionadas al proyecto
 * @param project Proyecto al que se le mirarán las tareas
 * @return void
 */
void showTasksRelatedWithProject(Project &project)
{
    if (projects.find(project) == projects.end())
    {
        cout << "¡Proyecto no encontrado!" << endl;
        return;
    }
    Board board = project.getBoard();
    map<PriorityType, queue<Task>> taskQueues = board.getTaskQueues();
    if (taskQueues.empty())
    {
        cout << "No hay tareas para mostrar" << endl;
    }
    else
    {
        cout << "Tareas: " << endl;
        for (auto &taskQueue : taskQueues)
        {
            cout << "Prioridad: " << taskQueue.first << endl;
            queue<Task> tasks = taskQueue.second;
            while (!tasks.empty())
            {
                Task task = tasks.front();
                cout << "Tarea: " << task.getTitle() << " Estado: " << task.getStatus() << endl;
                tasks.pop();
            }
        }
    }
}

/**
 * @brief Permite agregar una reacción a la nota escogida.
 * @param note Nota a la que se le agregará la reacción
 * @param reaction Reacción a agregar a la nota
 * @return void
 */
void addReactionToNote(Note &note, const ReactionType &reaction)
{
    note.addReaction(reaction);
    cout << "¡Reacción " << reactionToString(reaction) << " agregada exitosamente!" << endl;
}

/**
 * @brief Permite eliminar un tipo de reacción de una nota
 * @param note Nota a la que se le eliminará 1 de la reacción escogida
 * @param reaction Reacción a la cual se le eliminará 1
 * @return void
 */
void removeReactionFromNote(Note &note, const ReactionType &reaction)
{
    if (note.removeReaction(reaction))
    {
        cout << "¡Reacción " << reactionToString(reaction) << " eliminada exitosamente!" << endl;
    }
    else
    {
        cout << "No hay reacciones que eliminar" << endl;
    }
}

/**
 * @brief Permite escoger la reacción que se le asignará a la nota escogida.
 * @param note Nota a la que se le agregará la reacción
 * @return void
 */
void chooseReaction(Note &note)
{
    cout << "Escoge una reacción: " << endl;
    cout << "1. Me gusta" << endl;
    cout << "2. Corazón" << endl;
    cout << "3. Risa" << endl;
    cout << "4. Sorpresa" << endl;
    cout << "5. Triste" << endl;
    cout << "6. Enojado" << endl;
    cout << "7. Ninguno" << endl;

    int choice;
    while (true)
    {
        cout << "Ingresa tu opción: ";
        cin >> choice;
        if (choice == 7)
            break;
        if (choice < 1 || choice > 7)
        {
            cout << "¡Opción inválida!" << endl;
            continue;
        }
        ReactionType reaction = static_cast<ReactionType>(choice - 1);
        addReactionToNote(note, reaction);
        break;
    }
}

/**
 * @brief Permite mostrar la cantidad de reacciones por tipo, de una nota
 * @param note Nota a la que se le visualizarán las reacciones
 * @return void
 */
void displayReactionsFromNote(Note &note)
{
    map<ReactionType, int> reactions = note.getReactions();

    cout << "Reacciones: " << endl;

    for (auto &reaction : reactions)
    {
        cout << reactionToString(reaction.first) << ": " << reaction.second << endl;
    }
}

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
        cout << "Responsables: ";
        if (!tarea.getAssignees().empty())
        {
            for (const auto &responsable : tarea.getAssignees())
            {
                cout << "- " << responsable->getUsername() << endl;
            }
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

    vector<vector<const User *>> responsables;
    for (const Task &tarea : tareas)
    {
        const set<User *> tareaResponsables = tarea.getAssignees();

        for (const User *responsable : tareaResponsables)
        {
            responsables.emplace_back(responsable);
        }
    }

    sort(responsables.begin(), responsables.end(), [](const User *a, const User *b)
         { return a->getUsername() < b->getUsername(); });

    // Mostramos la lista ordenada de responsables por nombre
    int i = 1;
    int j = 1;
    cout << "Responsables de tareas ordenados por nombre:" << endl;
    for (vector<const User *> responsable : responsables)
    {
        for (const User *r : responsable)
        {
            cout << i << "." << j << " " << r->getUsername() << endl;
            j++;
        }
        i++;
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