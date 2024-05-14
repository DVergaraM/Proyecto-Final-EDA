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
            cout << "Project with this id already exists!" << endl;
            return;
        }
    }

    cout << "Enter project title: ";
    cin >> title;
    cout << "Enter the project description: ";
    cin >> description;

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
    cout << "Project created successfully!" << endl;
}

/**
 * @brief Muestra la información sobre un proyecto, si este es encontrado.
 * @param project Proyecto a buscar.
 * @return void
 */
void getProjectInfo(Project &project)
{
    if (projects.find(project) == projects.end())
    {
        cout << "Project not found!" << endl;
        return;
    }
    cout << "Project title: " << project.getTitle() << endl;
    cout << "Project description: " << project.getDescription() << endl;
    cout << "Project owner: " << project.getOwner()->getUsername() << endl;
    cout << "Project state: " << project.getBoard().getStateString() << endl;
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
    cout << "Assignee added successfully!" << endl;
}

/**
 * @brief Escoge entre los usuarios, quienes serán asignados a la tarea.
 * @param task Tarea a la cual se le asignará usuarios.
 * @return void
 */
void chooseUsersForTask(Task &task)
{
    int choice;
    cout << "Choose assignees for the task: " << endl;
    for (int i = 0; i < users.size(); i++)
    {
        cout << i + 1 << ". " << users[i].getUsername() << endl;
    }
    cout << "0. Exit" << endl;
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0)
            break;
        if (choice < 0 || choice > users.size())
        {
            cout << "Invalid choice!" << endl;
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
        cout << "Project not found!" << endl;
        return;
    }
    Board board = project.getBoard();
    map<PriorityType, queue<Task>> taskQueues = board.getTaskQueues();
    taskQueues.empty() ? cout << "No tasks to show" << endl : cout << "Tasks: " << endl;
    for (auto &taskQueue : taskQueues)
    {
        cout << "Priority: " << taskQueue.first << endl;
        queue<Task> tasks = taskQueue.second;
        while (!tasks.empty())
        {
            Task task = tasks.front();
            cout << "Task: " << task.getTitle() << " State: " << task.getStatus() << endl;
            tasks.pop();
        }
    }
}