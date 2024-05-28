#include "../model/user.h"
#include <deque>

deque<User>
    users;
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
bool isDateValid(string date)
{
    if (date.size() != 10)
        return false;
    if (date[2] != ' ' || date[5] != ' ')
        return false;
    if (stoi(date.substr(0, 2)) > 31 || stoi(date.substr(0, 2)) < 1)
        return false;
    if (stoi(date.substr(3, 2)) > 12 || stoi(date.substr(3, 2)) < 1)
        return false;
    if (stoi(date.substr(6, 4)) < 1900 || stoi(date.substr(6, 4)) > 2053)
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
    int id = rand() % 1000 + 1;
    string title;
    string description;

    for (auto &project : projects)
    {
        if (project.getId() == id)
        {
            cout << "¡Proyecto con este ID ya existe!" << endl;
            return;
        }
    }

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
    if (projects.find(project) == projects.end())
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
    for (int i = 0; i < users.size(); i++)
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
        if (choice < 0 || choice > users.size())
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
    taskQueues.empty() ? cout << "No hay tareas para mostrar" << endl : cout << "Tareas: " << endl;
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

/**
 * @brief Muestra los proyectos de un usuario, organizados por su fecha de creación
 * @param user Usuario al que se le mostrarán sus proyectos
 * @return void
 */
void showProjectsByCreationDate(User &user)
{
    set<Project *> userProjects = *user.getProjects();
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
    set<Project *> userProjects = *user.getProjects();
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
void searchProject(const User &user, string projectName)
{
    set<Project *> userProjects = *user.getProjects();
    userProjects.empty() ? cout << "No hay proyectos para mostrar" << endl : cout << "Proyectos: " << endl;
    for (auto &project : userProjects)
    {
        if (project->getTitle() == projectName)
        {
            getProjectInfo(*project);
            return;
        }
    }
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
    taskQueues.empty() ? cout << "No hay tareas para mostrar" << endl : cout << "Tareas: " << endl;
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
};

/**
 * @brief Permite agregar una reacción a la nota escogida.
 * @param note Nota a la que se le agregará la reacción
 * @param reaction Reacción a agregar a la nota
 * @return void
 */
void addReactionToNote(Note &note, ReactionType &reaction)
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
void removeReactionFromNote(Note &note, ReactionType &reaction)
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

    ReactionType reaction;

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
        reaction = (ReactionType)(choice - 1);
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

    for (auto reaction : reactions)
    {
        cout << reactionToString(reaction.first) << ": " << reaction.second << endl;
    }
}
