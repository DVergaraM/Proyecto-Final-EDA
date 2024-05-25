#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <stdlib.h>

#include "./enums.h"

using namespace std;

class User; // Forward declaration

/**
 * @brief Estructura interna de un comentario
 */
struct Comment
{
    User *author;
    string content;

    Comment() : author(nullptr), content(""){};
    Comment(User *author, string content) : author(author), content(content){};
};

/**
 * @brief Clase que representa una nota para una tarea
 * @details Contiene un autor, un título, un contenido y una pila de comentarios
 */
class Note
{
private:
    User *author;
    string title;
    string content;
    stack<Comment> comments;
    map<ReactionType, int> reactions;

public:
    /**
     * @brief Constructor vacío de la clase Note
     */
    Note() : author(nullptr), title(""), content("")
    {
        reactions[LIKE] = 0;
        reactions[LAUGH] = 0;
        reactions[WOW] = 0;
        reactions[SAD] = 0;
        reactions[ANGRY] = 0;
        reactions[NONE] = 0;
    }
    /**
     * @brief Constructor de la clase Note
     */
    Note(User *author, string title, string content) : author(author), title(title), content(content)
    {
        reactions[LIKE] = 0;
        reactions[LAUGH] = 0;
        reactions[WOW] = 0;
        reactions[SAD] = 0;
        reactions[ANGRY] = 0;
        reactions[NONE] = 0;
    };

    // Getters
    User *getAuthor() const { return author; };
    string getTitle() const { return title; };
    string getContent() const { return content; };
    stack<Comment> getComments() const { return comments; };
    map<ReactionType, int> getReactions() const { return reactions; }
    std::set<ReactionType> getReactionsKeys() const
    {
        std::set<ReactionType> reactionSet;
        for (auto reaction : reactions)
        {
            reactionSet.insert(reaction.first);
        }
        return reactionSet;
    }

    std::set<int> getReactionsValues() const
    {
        std::set<int> reactionValues;
        for (auto reaction : reactions)
        {
            reactionValues.insert(reaction.second);
        }
        return reactionValues;
    }

    // Setters
    void setAuthor(User *author) { this->author = author; };
    void setTitle(string title) { this->title = title; };
    void setContent(string content) { this->content = content; };
    void setComments(stack<Comment> comments) { this->comments = comments; };
    void updateReaction(ReactionType oldReaction, ReactionType newReaction)
    {
        reactions[newReaction] = reactions[oldReaction];
        reactions.erase(oldReaction);
    }

    // Métodos

    /**
     * @brief Método para agregar una reacción a latarea.
     * @return void
     */
    void addReaction(ReactionType reaction)
    {
        reactions[reaction]++;
    }

    /**
     * @brief Método para eliminar la última reacción de la tarea.
     * @return void
     * @pre No hay reacciones del tipo en la tarea.
     */
    bool removeReaction(ReactionType reaction)
    {
        if (reactions[reaction] == 0)
        {
            return false;
        }
        reactions[reaction]--;
        return true;
    }

    /**
     * @brief Añade un comentario a la pila de comentarios
     * @param author Usuario que realiza el comentario
     * @param content Contenido del comentario
     * @return void
     */
    void addComment(User *author, string content)
    {
        comments.push(Comment(author, content));
    };
    /**
     * @brief Elimina el último comentario de la pila
     * @return void
     */
    void removeComment()
    {
        if (!comments.empty())
        {
            comments.pop();
            return;
        }
        cout << "No hay comentarios que eliminar" << endl;
    }

    void updateComment(Comment oldComment, Comment newComment)
    {
        stack<Comment> temp;
        while (!comments.empty())
        {
            if (comments.top().author == oldComment.author && comments.top().content == oldComment.content)
            {
                temp.push(newComment);
            }
            else
            {
                temp.push(comments.top());
            }
            comments.pop();
        }
        comments = temp;
    }

    /**
     * @brief Elimina un comentario específico de la pila
     * @param author Usuario que realizó el comentario
     * @return void
     */
    void removeComment(User *author)
    {
        stack<Comment> temp;
        while (!comments.empty())
        {
            if (comments.top().author != author)
            {
                temp.push(comments.top());
            }
            comments.pop();
        }
        comments = temp;
    }

    /**
     * @brief Muestra los comentarios de la pila
     * @return void
     */
    void showComments()
    {
        stack<Comment> temp = comments;
        while (!temp.empty())
        {
            cout << temp.top().author << ": " << temp.top().content << endl;
            temp.pop();
        }
    }

    // Destructor
    ~Note()
    {
        while (!comments.empty())
        {
            comments.pop();
        }
    }

    // Sobrecarga de operadores

    /**
     * @brief Sobrecarga del operador de inserción
     * @param os Stream de salida
     * @param note Nota a imprimir
     * @return ostream&
     */
    friend ostream &operator<<(ostream &os, const Note &note)
    {
        os << "Author: " << note.author << endl;
        os << "Title: " << note.title << endl;
        os << "Content: " << note.content << endl;
        os << "Comments: ";
        stack<Comment> temp = note.comments;
        while (!temp.empty())
        {
            os << temp.top().author << ": " << temp.top().content << endl;
            temp.pop();
        }
        os << "Reactions: ";
        for (auto reaction : note.getReactions())
        {
            os << reaction.first << ": " << reaction.second << " ";
        }
        return os;
    }

    /**
     * @brief Sobrecarga del operador de comparación menor que
     * @param note Nota a comparar
     * @return bool
     */
    bool operator<(const Note &note) const
    {
        return title < note.title;
    }

    /**
     * @brief Sobrecarga del operador de comparación igual que
     * @param note Nota a comparar
     * @return bool
     */
    bool operator==(const Note &note) const
    {
        return title == note.title;
    }
};

#endif // NOTE_H
