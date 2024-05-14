#ifndef USER_H
#define USER_H

#include "./project.h"

class User
{
private:
    int id;
    string username;
    string password;
    RoleType role;
    std::set<Project *> *projects;

public:
    /**
     * @brief Constructor vacío para un usuario
     */
    User() : id(0), username(""), password(""), role(DEVELOPER), projects(nullptr) {}

    /**
     * @brief Constructor para un usuario.
     */
    User(string username, string password, RoleType role) : username(username), password(password), role(role), projects(nullptr)
    {
        id = rand() % 1000 + 1;
    }

    // Getters
    int getId() const { return id; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    RoleType getRole() const { return role; }
    std::set<Project *> *getProjects() const { return projects; }

    // Setters
    void setUsername(string username) { this->username = username; }
    void setPassword(string password) { this->password = password; }
    void setRole(RoleType role) { this->role = role; }
    void setProject(std::set<Project *> *project) { this->projects = project; }

    // Métodos de clase
    /**
     * @brief Agrega un proyecto al usuario.
     * @param project Proyecto a agregarle al usuario.
     * @return void
     */
    void addProject(Project *project)
    {
        if (project->getOwner() == nullptr)
        {
            project->setOwner(this);
        }
        if (projects == nullptr)
        {
            projects = new std::set<Project *>();
        }

        if (projects->find(project) != projects->end())
        {
            cout << "Project already exists" << endl;
            return;
        }

        this->projects->insert(project);
    }

    /**
     * @brief Elimina un proyecto del usuario.
     */
    void removeProject(Project *project)
    {
        if (projects != nullptr)
        {
            this->projects->erase(remove(projects->begin(), projects->end(), project), projects->end());
        }
        else
        {
            cout << "No projects to remove" << endl;
        }
    }

    /**
     * @brief Muestra los títulos de los proyectos a los que pertenece el usuario.
     * @return void
     */
    void showProjects()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }
        projects->empty() ? cout << "No projects to show" << endl : cout << "Projects: " << endl;
        for (auto *project : *projects)
        {
            cout << project->getTitle() << endl;
        }
    }


    /**
     * @brief Muestra el título del tablero principal de cada proyecto al que pertenece el usuario.
     * @return void
    */
    void showBoards()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }
        projects->empty() ? cout << "No projects to show" << endl : cout << "Projects: " << endl;
        for (auto *project : *projects)
        {
            cout << project->getBoard().getTitle() << endl;
        }
    }

    /**
     * @brief Muestra las tareas de cada proyecto al que pertenece el usuario.
     * @return void
    */
    void showTasks()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }
        projects->empty() ? cout << "No projects to show" << endl : cout << "Projects: " << endl;
        for (auto *project : *projects)
        {
            cout << "- " << project->getTitle() << endl;
            Board board = project->getBoard();
            for (auto &task : board.getTasks())
            {
                cout << "  - Task: " << task.getTitle() << endl;
            }
        }
    }

    /**
     * @brief Destructor de usuario.
    */
    ~User()
    {
        delete projects;
    }

    // Sobrecarga de operadores
    /**
     * @brief Sobrecarga del operador de inserción
     * @param os Stream de salida.
     * @param user Usuario a imprimir.
     * @return ostream&
    */
    friend ostream &operator<<(ostream &os, const User &user)
    {
        os << "ID: " << user.getId() << endl;
        os << "Username: " << user.getUsername() << endl;
        os << "Role: " << roleToString(user.getRole()) << endl;
        os << "Projects: " << endl;
        if (user.getProjects() == nullptr)
        {
            os << "No projects" << endl;
            return os;
        }
        for (auto &project : *user.getProjects())
        {
            os << "- " << project->getTitle() << endl;
        }
        return os;
    }
};

#endif // USER_H