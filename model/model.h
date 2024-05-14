#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Usuario {
    string nombre;
    string contrasena;
    string correo;
    string telefono;
};

class Login {
    vector<Usuario> usuarios;

public:

    bool esAlfanumerico(string contrasena) {
        for (char c : contrasena) {
            if (!isalnum(c) || isspace(c)) {
                return false;
            }
        }
        return true;
    }
    
    void registrarUsuario(string nombre, string contrasena1, string contrasena2, string correo, string telefono) {
        if (contrasena1 != contrasena2) {
            cout << "Las contraseñas no coinciden." << endl;
            return;
        }
        if (!esAlfanumerico(contrasena1)) {
            cout << "La contraseña solo puede contener letras y números." << endl;
            return;
        }
        Usuario nuevoUsuario;
        nuevoUsuario.nombre = nombre;
        nuevoUsuario.contrasena = contrasena1;
        nuevoUsuario.correo = correo;
        nuevoUsuario.telefono = telefono;
        usuarios.push_back(nuevoUsuario);
    }

    bool validarUsuario(string nombre, string contrasena, string correo, string telefono) {
        for (Usuario usuario : usuarios) {
            if (usuario.nombre == nombre && usuario.contrasena == contrasena && usuario.correo == correo && usuario.telefono == telefono) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Login login;
    string nombre, contrasena1, contrasena2, correo, telefono;
    int opcion;


    do{
        cout<<"Programa de registro de usuarios"<<endl;
        cout<<"1. Registrar usuario"<<endl;
        cout<<"2. Iniciar sesión"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<"Ingrese una opción: ";
            cin>>opcion;
        
        switch(opcion){
            case 1:
                cout<<"Ingrese el nombre de usuario: ";
                cin>>nombre;
                cout<<"Ingrese la contraseña: ";
                cin>>contrasena1;
                cout<<"Confirme la contraseña: ";
                cin>>contrasena2;
                cout<<"Ingrese el correo: ";
                cin>>correo;
                cout<<"Ingrese el teléfono: ";
                cin>>telefono;
                login.registrarUsuario(nombre, contrasena1, contrasena2, correo, telefono);
                break;
            case 2:
                cout<<"Ingrese el nombre de usuario: ";
                cin>>nombre;
                cout<<"Ingrese la contraseña: ";
                cin>>contrasena1;
                cout<<"Ingrese el correo: ";
                cin>>correo;
                cout<<"Ingrese el teléfono: ";
                cin>>telefono;
                if (login.validarUsuario(nombre, contrasena1, correo, telefono)) {
                    cout << "Inicio de sesión exitoso." << endl;
                } else {
                    cout << "Inicio de sesión fallido." << endl;
                }
                break;
            case 3:
                cout<<"Saliendo del programa..."<<endl;
                break;
            default:
                cout<<"Opción no válida"<<endl;
                break;
        }

    }while(opcion!=3);

    return 0;
}
