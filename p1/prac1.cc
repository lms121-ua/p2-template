// Programación 2 - Práctica 1
// DNI: x8594224k
// Nombre: Letisia Monica Sandu

#include <iostream>
#include <vector>

using namespace std;

const int MAXSUBJECT=50;

// Registro para las fechas
struct Date{
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_DUPLICATED: cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING: cout << "ERROR: number out of range" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add academic year" << endl
         << "2- Delete academic year" << endl
         << "3- Add teacher" << endl
         << "4- Delete teacher" << endl
         << "5- Show teacher" << endl
         << "6- Add phrase" << endl
         << "7- Summary" << endl
         << "q- Quit" << endl
         << "Option: ";
}

// Función principal. Tendrás que añadir más código tuyo

void addValor(vector<int> &enteros){
	string valor;
	int pos;
	bool seguir;
	do{
		cout << "Nuevo valor: ";
		getline(cin, valor);
		if(valor.empty()){
			error(ERR_EMPTY);		
			seguir = false;
		}
		else{
			int nuevo_entero = stoi(valor);
			pos = buscarPosicion(enteros, nuevo_entero);
			if(pos != -1){
				seguir = true;
				error(ERR_DUPLICATED);
			}
			else{
				seguir = false;
				enteros.push_back(nuevo_entero);
			}
		}
	}while(seguir);
}

// Pedimos un valor y lo elimino
void deleteValor(vector<int> &enteros){
	string valor;
	int pos;
	bool seguir;
	do{
		cout << "Nuevo valor: ";
		getline(cin, valor);
		if(valor.empty()){
			error(ERR_EMPTY);		
			seguir = false;
		}
		else{
			int nuevo_entero = stoi(valor);
			pos = buscarPosicion(enteros, nuevo_entero);
			if(pos == -1){
				seguir = true;
				error(ERR_NOT_EXIST);
			}
			else{
				seguir = false;
				enteros.erase(enteros.begin() + pos);
			}
		}
	}while(seguir);
	
}

void printValores(const vector<int> &enteros){
	cout << "<";
	for(int i = 0; i < enteros.size(); i++){
		cout << enteros[i];
		if(i != enteros.size() -1 ){
			cout << ", ";
		}
	}
	cout << ">";
	cout << endl;
}
int main(){
    char option;
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
