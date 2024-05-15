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
    set<Project *> *projects;

public:
    User() : id(0), username(""), password(""), role(DEVELOPER), projects(nullptr) {}
    User(string username, string password, RoleType role) : username(username), password(password), role(role), projects(nullptr)
    {
        id = rand() % 1000 + 1;
    }

    int getId() const { return id; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    RoleType getRole() const { return role; }
    set<Project *> *getProjects() const { return projects; }

    void setUsername(string username) { this->username = username; }
    void setPassword(string password) { this->password = password; }
    void setRole(RoleType role) { this->role = role; }
    void setProject(set<Project *> *project) { this->projects = project; }

    void addProject(Project *project)
    {
        if (project->getOwner() == nullptr)
        {
            project->setOwner(this);
        }
        if (projects == nullptr)
        {
            projects = new set<Project *>();
        }

        this->projects->insert(project);
    }

    void removeProject(Project *project)
    {
        if (projects != nullptr)
        {
            this->projects->erase(project);
        }
        else
        {
            cout << "No projects to remove" << endl;
        }
    }

    void showProjects()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }
        for (auto *project : *projects)
        {
            cout << project->getTitle() << endl;
        }
    }

    void showBoards()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }
        for (auto *project : *projects)
        {
            Board temp = project->getBoard();
            cout << temp.getTitle() << endl;
        }
    }

    void showTasks()
    {
        if (projects == nullptr)
        {
            cout << "No projects to show" << endl;
            return;
        }

        for (auto *project : *projects)
        {
            cout << "Project: " << project->getTitle() << endl;
            Board board = project->getBoard();
            for (auto &task : board.getTasks())
            {
                cout << "  - Task: " << task.getTitle() << endl;
            }
        }
    }

    ~User()
    {
        delete projects;
    }

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

    // Método toCSV para convertir un objeto de la clase Usuario a un string en formato CSV
    string toCSV() const
    {
        return id + "," + username + "," + password + "," + role;
    }

    // Método fromCSV para convertir un string en formato CSV a un objeto de la clase Usuario
    static User fromCSV(string linea)
    {
        stringstream ss(linea);
        string nombre, contrasena, correo, telefono;
        getline(ss, nombre, ',');
        getline(ss, contrasena, ',');
        getline(ss, correo, ',');
        getline(ss, telefono, ',');
      //  return User(nombre, contrasena, correo, telefono);
    }
};

#endif // USER_H