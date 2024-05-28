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
    Date creationDate;
    Date dueDate;
    std::set<User *> members;

public:
    /**
     * @brief Constructor vacío de un proyecto
     */
    Project() : owner(nullptr), title(""), creationDate(), dueDate()
    {
        id = rand() % 1000 + 1;
    }
    /**
     * @brief Constructor de un proyecto solo con título.
     */
    Project(string title) : owner(nullptr), title(title)
    {
        id = rand() % 1000 + 1;
    }
    /**
     * @brief Constructor de un proyecto con dueño y título
     */
    Project(User *owner, string title, Date creationDate, Date dueDate) : owner(owner), title(title), creationDate(creationDate), dueDate(dueDate)
    {
        id = rand() % 1000 + 1;
    }

    // Getters
    int getId() const { return id; }
    User *getOwner() const { return owner; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }
    Board getBoard() const { return board; }
    Date getCreationDate() const { return creationDate; }
    Date getDueDate() const { return dueDate; }
    std::set<User *> getMembers() const { return members; }

    // Setters
    void setId(int id) { this->id = id; }
    void setOwner(User *owner) { this->owner = owner; }
    void setTitle(string title) { this->title = title; }
    void setDescription(string description) { this->description = description; }
    void setDueDate(Date dueDate) { this->dueDate = dueDate; }
    void setBoard(Board board) { this->board = board; }
    void setMembers(std::set<User *> members) { this->members = members; }
    void addMember(User *member) { members.insert(member); }
    void removeMember(User *member)
    {
        members.erase(remove(members.begin(), members.end(), member), members.end());
    }

    // Métodos de clase
    void updateMember(User *oldMember, User *newMember)
    {
        removeMember(oldMember);
        addMember(newMember);
    }

    /**
     * @brief Destructor de un proyecto.
     */
    ~Project()
    {
        for (auto &member : members)
        {
            member->getProjects()->erase(this);
        }
    }

    // Sobrecarga de operadores

    /**
     * @brief Sobrecarga del operador de inserción.
     * @param os Stream de salida.
     * @param project Proyecto a imprimir.
     * @return ostream&
     */
    friend ostream &operator<<(ostream &os, const Project &project)
    {
        os << "ID: " << project.id << endl;
        os << "Owner: " << project.owner->getUsername() << endl;
        os << "Title: " << project.title << endl;
        os << "Description: " << project.description << endl;
        os << "Board: " << project.board.getTitle() << endl;
        os << "Members: ";
        for (auto &member : project.members)
        {
            os << "- " << member->getUsername() << endl;
        }

        return os;
    }

    /**
     * @brief Sobrecarga del operador de menor que.
     * @param project Proyecto a comparar.
     * @return bool
     */
    bool operator<(const Project &project) const
    {
        return this->getDueDate() < project.getDueDate();
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