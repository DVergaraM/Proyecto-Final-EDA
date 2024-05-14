#ifndef BOARD_H
#define BOARD_H

#include "./task.h"

class Board
{
private:
    int id;
    string title;
    vector<Task> tasks;
    StatusType state;
    map<PriorityType, queue<Task>> taskQueues;

public:
    /**
     * @brief Constructor vacío de un tablero
    */
    Board() : title(""), state(OPEN)
    {
        id = rand() % 1000 + 1;
    }

    /**
     * @brief Constructor de un tablero
    */
    Board(string title) : title(title), state(OPEN)
    {
        id = rand() % 1000 + 1;
    }

    // Getters
    int getId() const { return id; }
    string getTitle() const { return title; }
    vector<Task> getTasks() const { return tasks; }
    StatusType getState() const { return state; }
    string getStateString() const { return statusToString(state); }
    map<PriorityType, queue<Task>> getTaskQueues() const { return taskQueues; }
    set<PriorityType> getPriorities() const
    {
        set<PriorityType> priorities;
        for (auto &task : tasks)
        {
            priorities.insert(task.getPriority());
        }
        return priorities;
    }
    set<queue<Task>> getTasksQueue() const
    {
        set<queue<Task>> queues;
        for (auto &taskQueue : taskQueues)
        {
            queues.insert(taskQueue.second);
        }
        return queues;
    }

    // Setters

    void setTitle(string title) { this->title = title; }
    void setTasks(vector<Task> tasks) { this->tasks = tasks; }
    void setState(StatusType state) { this->state = state; }
    void setTaskQueues(map<PriorityType, queue<Task>> taskQueues) { this->taskQueues = taskQueues; }

    // Métodos de clase
    /**
     * @brief Agrega una tarea al tablero.
     * @param task Tarea a agregar.
     * @return void
    */
    void addTask(Task task)
    {
        tasks.push_back(task);
        taskQueues[task.getPriority()].push(task);
    }

    /**
     * @brief Elimina una tarea del tablero.
     * @param task Tarea a eliminar.
     * @return void
    */
    void removeTask(Task task)
    {
        tasks.erase(remove(tasks.begin(), tasks.end(), task), tasks.end());
        taskQueues[task.getPriority()].pop();
    }

    /**
     * @brief Muestra las tareas por medio de su título.
     * @return void
    */
    void showTasks()
    {
        tasks.empty() ? cout << "No tasks to show" << endl : cout << "Tasks: " << endl;
        for (auto &task : tasks)
        {
            cout << task.getTitle() << endl;
        }
    }

    /**
     * @brief Muestra las tareas por su prioridad.
     * @return void
    */
    void showTaskQueues()
    {
        taskQueues.empty() ? cout << "No tasks to show" << endl : cout << "Tasks: " << endl;
        for (auto &taskQueue : taskQueues)
        {
            cout << "Priority: " << priorityToString(taskQueue.first) << endl;
            queue<Task> temp = taskQueue.second;
            while (!temp.empty())
            {
                cout << temp.front().getTitle() << endl;
                temp.pop();
            }
        }
    }

    /**
     * Destructor de tablero, por medio de la eliminación de tareas y sus prioridades.
    */
    ~Board()
    {
        tasks.clear();
        taskQueues.clear();
    }

    // Sobrecarga de operadores

    /**
     * @brief Sobrecarga del operador de inserción.
     * @param os Stream de salida.
     * @param board Tablero a imprimir.
     * @return ostream&
    */
    friend ostream &operator<<(ostream &os, const Board &board)
    {
        os << "ID: " << board.id << endl;
        os << "Title: " << board.title << endl;
        os << "Tasks: " << endl;
        for (auto &task : board.tasks)
        {
            os << task << endl;
        }
        os << "Task Queues: " << endl;
        for (auto &taskQueue : board.taskQueues)
        {
            os << "Priority: " << priorityToString(taskQueue.first) << endl;
            queue<Task> temp = taskQueue.second;
            while (!temp.empty())
            {
                os << temp.front() << endl;
                temp.pop();
            }
        }
        return os;
    }

    /**
     * @brief Sobrecarga del operador de menor que.
     * @param board Tablero a comprar.
     * @return bool
    */
    bool operator<(const Board &board) const
    {
        return id < board.getId();
    }

    /**
     * @brief Sobrecarga del operador de igual que
     * @param board Tablero a comparar.
     * @return bool
    */
    bool operator==(const Board &board) const
    {
        return id == board.getId();
    }
};

#endif // BOARD_H