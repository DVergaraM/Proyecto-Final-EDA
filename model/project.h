#ifndef PROJECT_H
#define PROJECT_H

#include "./board.h"

class Project
{
private:
    int id;
    User *owner;
    string title;
    string description;
    Board board;
    std::set<User *> members;

public:
    /**
     * @brief Constructor vacío de un proyecto
    */
    Project() : owner(nullptr), title("") {
        id = rand() % 1000 + 1;
    }
    /**
     * @brief Constructor de un proyecto solo con título.
    */
    Project(string title) : owner(nullptr), title(title) {
        id = rand() % 1000 + 1;
    }
    /**
     * @brief Constructor de un proyecto con dueño y título
    */
    Project(User *owner, string title) : owner(owner), title(title) {
        id = rand() % 1000 + 1;
    }

    // Getters
    int getId() const { return id; }
    User *getOwner() const { return owner; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    Board getBoard() const { return board; }
    std::set<User *> getMembers() const { return members; }

    // Setters
    void setId(int id) { this->id = id; }
    void setOwner(User *owner) { this->owner = owner; }
    void setTitle(string title) { this->title = title; }
    void setDescription(string description) { this->description = description; }
    void setBoard(Board board) { this->board = board; }
    void setMembers(std::set<User *> members) { this->members = members; }
    void addMember(User *member) { members.insert(member); }

    /**
     * @brief Destructor de un proyecto.
    */
    ~Project() {}

    // Sobrecarga de operadores

    /**
     * @brief Sobrecarga del operador de inserción.
     * @param os Stream de salida.
     * @param project Proyecto a imprimir.
     * @return ostream&
    */
    friend ostream &operator<<(ostream &os, const Project &project)
    {
        os << project.title;
        return os;
    }

    /**
     * @brief Sobrecarga del operador de menor que.
     * @param project Proyecto a comparar.
     * @return bool
    */
    bool operator<(const Project &project) const
    {
        return id < project.getId();
    }

    /**
     * @brief Sobrecarga del operador de igual que.
     * @param project Proyecto a comparar.
     * @return bool
    */
    bool operator==(const Project &project) const
    {
        return id == project.getId();
    }
};

#endif // PROJECT_H