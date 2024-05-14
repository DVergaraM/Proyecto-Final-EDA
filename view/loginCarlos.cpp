#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

    // Clase Usuario con atributos nombre, contrasena, correo y telefono
    class Usuario{
        
        private:
            string nombre;
            string contrasena;
            string correo;
            string telefono;

        public:

            // Constructor de la clase Usuario
            Usuario(string nombre, string contrasena, string correo, string telefono){
                this->nombre = nombre;
                this->contrasena = contrasena;
                this->correo = correo;
                this->telefono = telefono;
            }

            // Métodos get y set para los atributos de la clase Usuario
            string getNombre() const{
                return nombre;
            }

            string getContrasena() const{
                return contrasena;
            }

            string getCorreo() const{
                return correo;
            }

            string getTelefono() const{
                return telefono;
            }

            void setNombre(string nombre){
                this->nombre = nombre;
            }

            void setContrasena(string contrasena){
                this->contrasena = contrasena;
            }

            void setCorreo(string correo){
                this->correo = correo;
            }

            void setTelefono(string telefono){
                this->telefono = telefono;
            }

            // Método toCSV para convertir un objeto de la clase Usuario a un string en formato CSV
            string toCSV() const{
                return nombre + "," + contrasena + "," + correo + "," + telefono;
            }

            // Método fromCSV para convertir un string en formato CSV a un objeto de la clase Usuario
            static Usuario fromCSV(string linea){
                stringstream ss(linea);
                string nombre, contrasena, correo, telefono;
                getline(ss, nombre, ',');
                getline(ss, contrasena, ',');
                getline(ss, correo, ',');
                getline(ss, telefono, ',');
                return Usuario(nombre, contrasena, correo, telefono);
            }
    };

    // Sobrecarga del operador << para imprimir un objeto de la clase Usuario y sus atributos en consola 
    ostream& operator<<(ostream& os, const Usuario& usuario){
        os<<"Nombre: "<<usuario.getNombre()<<", Correo: "<<usuario.getCorreo()<<", Teléfono: "<<usuario.getTelefono();
        return os;
    }

    // Clase Login con atributo usuarios de tipo vector de Usuario
    class Login{

        private:
            vector<Usuario> usuarios;

        public:

            //Método get para el atributo usuarios
            vector<Usuario> getUsuarios() const{
                return usuarios;
            }

            //Método para validar si una cadena es alfanumérica
            bool esAlfanumerico(string contrasena){
                for(char c : contrasena){
                    if(!isalnum(c) || isspace(c)){
                        return false;
                    }
                }
                return true;
            }

            //Método para validar si un número de teléfono es válido
            bool esTelefonoValido(string telefono){
                if(telefono.length() != 10){
                    return false;
                }
                for(char c : telefono){
                    if (!isdigit(c)) {
                        return false;
                    }
                }
                return true;
            }

            //Método para validar si un correo es válido
            bool esCorreoValido(string correo){
                size_t atPos = correo.find('@');
                size_t dotPos = correo.rfind('.');
                if(atPos == string::npos || dotPos == string::npos){
                    return false;
                }
                if(atPos == 0 || atPos == correo.length() - 1 || dotPos == 0 || dotPos == correo.length() - 1){
                    return false;
                }
                return true;
            }

            //Método para validar si un usuario con nombre dado como parámetro ya está registrado
            bool esUsuarioRegistrado(const string& nombre) const{
                for(const Usuario& usuario : getUsuarios()){
                    if(usuario.getNombre() == nombre){
                        return true;
                    }
                }
                return false;
            }

            //Método para registrar un usuario con nombre, contrasena, correo y telefono dados como parámetros 
            void registrarUsuario(string nombre, string contrasena1, string contrasena2, string correo, string telefono){

                //Valdaciones de los datos ingresados por el usuario
                if(contrasena1 != contrasena2){
                    cout<<"Las contraseñas no coinciden."<<endl;
                    return;
                }
                if(!esAlfanumerico(contrasena1)){
                    cout<<"La contraseña solo puede contener letras y números."<<endl;
                    return;
                }
                if(!esTelefonoValido(telefono)){
                    cout << "El número de teléfono debe contener exactamente 10 dígitos."<<endl;
                    return;
                }
                if(!esCorreoValido(correo)){
                    cout<<"El correo debe contener un @ y un punto."<<endl;
                    return;
                }
                if(!esUsuarioRegistrado(nombre)){
                    cout<<"Ese nombre de usuario ya está registrado. Por favor, elija un nombre de usuario diferente."<<endl;
                    return;
                }

                //Creación de un nuevo objeto de la clase Usuario y agregación al vector de usuarios
                Usuario nuevoUsuario(nombre, contrasena1, correo, telefono);
                nuevoUsuario.setNombre(nombre);
                nuevoUsuario.setContrasena(contrasena1);
                nuevoUsuario.setCorreo(correo);
                nuevoUsuario.setTelefono(telefono);
                usuarios.push_back(nuevoUsuario);
            }

            //Método para validar si un usuario con nombre y contraseña dados como parámetros existe en el vector de usuarios
            bool validarUsuario(string nombre, string contrasena){
                for(Usuario usuario : usuarios){
                    if(usuario.getNombre() == nombre && usuario.getContrasena() == contrasena){
                        return true;
                    }
                }
                return false;
            }

            //Método para importar usuarios desde un archivo de texto y agregarlos al vector de usuarios usando el método fromCSV 
            void importarUsuarios(){
                ifstream archivo;
                archivo.open("usuarios.txt");
                if(archivo.is_open()){
                    string linea;
                    while(getline(archivo, linea)){
                        Usuario usuario = Usuario::fromCSV(linea);
                        usuarios.push_back(usuario);
                    }
                    archivo.close();
                }else{
                    cout<<"No se pudo abrir el archivo usuarios.txt jaja :(."<<endl;
                }
            }

            //Método para exportar usuarios al archivo de texto usuarios.txt usando el método toCSV 
            void exportarUsuarios(){
                ofstream archivo;
                archivo.open("usuarios.txt");
                if(archivo.is_open()){
                    for(Usuario usuario : usuarios){
                        archivo<<usuario.toCSV()<<endl;
                        if(archivo.fail()){
                            cout<<"Error al escribir en el archivo."<<endl;
                            break;
                        }
                    }
                    archivo.close();
                    if (archivo.fail()){
                        cout<<"Error al cerrar el archivo."<<endl;
                    }
                }else{
                    cout<<"No se pudo abrir el archivo usuarios.txt jaja :(."<<endl;
                }
            }

            //Método para imprimir los usuarios registrados en consola
            void imprimirUsuarios() const{
                vector<Usuario> usuarios = getUsuarios();
                for(Usuario usuario : usuarios){
                    cout<<usuario<<endl;
                }
            }
    };

    //Método de ejecución principal del programa
    int main(){
        //Creación de objeto de la clase Login y variables para los datos de usuario
        Login login;
        string nombre, contrasena1, contrasena2, correo, telefono;
        int opcion;

        //Ciclo principal del programa con menú de opciones
        do{
            cout<<"Programa de registro de usuarios"<<endl;
            cout<<"1. Registrar usuario"<<endl;
            cout<<"2. Iniciar sesión"<<endl;
            cout<<"3. Exportar usuarios"<<endl;
            cout<<"4. Importar usuarios"<<endl;
            cout<<"5. Mostrar usuarios"<<endl;
            cout<<"6. Salir"<<endl;
            cout<<"Ingrese una opción: ";
                cin>>opcion;

            //Validación de la entrada del usuario para que sea un número entero
            while(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Entrada inválida. Por favor, ingrese un número: ";
                    cin>>opcion;
            }
            
            //Switch case para ejecutar la opción seleccionada por el usuario y llama a los métodos correspondientes
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
                    if(login.validarUsuario(nombre, contrasena1)){
                        cout<<"Inicio de sesión exitoso."<<endl;
                    }else{
                        cout<<"Inicio de sesión fallido."<<endl;
                    }
                    break;
                case 3:
                    login.exportarUsuarios();
                    break;
                case 4:
                    login.importarUsuarios();
                    break;
                case 5:
                    login.imprimirUsuarios();
                    break;
                case 6:
                    cout<<"Saliendo del programa"<<endl;
                    break;
                default:
                    cout<<"Opción no válida"<<endl;
                    break;
            }

        }while(opcion!=6);

        return 0;
    }
