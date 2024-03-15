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

int searchPosYear(int year, const vector<AcademicYear> &years){
    int pos;
    pos = -1;

    for(int i = 0; i < years.size() && pos == -1; i++){
        if(years[i].id == year){
            pos = i;
        }
    }
    return pos;
}

bool yearAsk(int &yearO, const vector<AcademicYear> &years){
    int pos;
    string year;
    bool vacio;

    do{
        cout << "Enter academic year: ";
        getline(cin, year);

        if(year.length() == 0){
            error(ERR_EMPTY);
            vacio = true;
        }else{
            vacio = false;
            pos = searchPosYear(stoi(year), years);
            if(pos == -1){
                yearO = stoi(year);
            }else{
                error(ERR_DUPLICATED);
            }
        }
    }while(pos != -1 && !vacio);

    return vacio;
}

void addAcademicYear(vector<AcademicYear> &years){
    int year;
    AcademicYear nuevo;
    bool vacio;

    vacio = yearAsk(nuevo.id, years);

    if(!vacio){
        years.push_back(nuevo);
    }
}

int yearAsk(const vector<AcademicYear> &years){
    string year;
    bool b;
    int pos;
    pos = -1;

    do{
        cout << "Enter academic year: ";
        getline(cin, year);

        if(year.length() == 0){
            error(ERR_EMPTY);
            b = false;
        }else{
            pos = searchPosYear(stoi(year), years);

            if(pos == -1){
                error(ERR_NOT_EXIST);
                b = true;
            }else{
                b = false;
            }
        }
    }while(b);

    return pos;
}

void deleteAcademicYear(vector<AcademicYear> &years){
    int pos;

    pos = yearAsk(years);

    if(pos != -1){
        years.erase(years.begin() + pos);
    }
}
void searchTeacher(string nameTeacher, int &posTeacher, int &posYear, const vector<AcademicYear> &years){
    int i, j;
    posYear = -1;
    posTeacher = -1;

    for(i = 0; i < years.size() && posYear == -1; i++){
        for(j = 0; j < years[i].listTeachers.size() && posYear == -1; j++){
            if(years[i].listTeachers[j].name == nameTeacher){
                posYear = i;
                posTeacher = j;
            } 
        }
    }
}

void askSimba(int &rating, int ini, int fin){
	string aux;
	bool seguir;
	seguir = true;	
	do{
		cout << "Enter rating: ";
		getline(cin, aux);
		if(aux == ""){
			rating = 0;
			seguir = false;
		}
		else{
			rating = stoi(aux);
			if(rating < ini || rating > fin){
				error(ERR_RATING);
				seguir = true;
			}
			else{
				seguir = false;
			}
		}
	}while(seguir);
}

bool askDataTeacher(const vector<AcademicYear> &years, Teacher &nuevo){
	bool e;
	string aux;
	
	cout << "Enter nickname: ";
	getline(cin, nuevo.nickname);
	cout << "Enter subject: ";
	getline(cin, aux);
	if(aux == ""){
		e = true;
		error(ERR_EMPTY);
	}
	else{
		strncpy(nuevo.subject, aux.c_str(), MAXSUBJECT);
		nuevo.subject[MAXSUBJECT - 1] = '\0';
		askSimba(nuevo.rating, 1, 5);
		e = false;
	}
	return e;
}


void askTeacher(const vector<AcademicYear> &years, string &name){
	int posYear, posTeacher;
	do{
		cout << "Enter teacher name: ";
		getline(cin, name);
		if(name == ""){
			error(ERR_EMPTY);
		}
		else{
			searchTeacher(name, posYear, posTeacher, years);
			if(posYear != -1){
				error(ERR_DUPLICATED);
			}
		}
	}while(name != "" && posYear != -1);
}

void addTeacher(vector<AcademicYear> &years){
	Teacher nuevo;
	int pos;	
	bool error;
	
	pos = yearAsk(years); 
	if(pos != -1){
		askTeacher(years, nuevo.name);
		if(nuevo.name != ""){		
			error = askDataTeacher(years, nuevo);
			if(!error){
				years[pos].listTeachers.push_back(nuevo);
			}
		}
	}	
}

void askTeacher(const vector<AcademicYear> &years, int &posYear, int &posTeacher){
	string name;
	bool b;
	posYear = posTeacher = -1;
	do{
		cout << "Enter teacher name: ";
		getline(cin, name);
		if(name == ""){
			error(ERR_EMPTY);
			b = false; // no seguimos con el teacher
		}
		else{
			searchTeacher(name, posYear, posTeacher, years);
			if(posYear == -1){
				error(ERR_NOT_EXIST);
				b = true;
			}
			else{
				b = false; // seguimos con el teacher
			}
		}
	}while(b);
}

// detele teacher
void deleteTeacher(vector<AcademicYear> &years){
	int posTeacher, posYear;
	askTeacher(years, posYear, posTeacher);
	if(posYear != -1){
		years[posYear].listTeachers.erase(years[posYear].listTeachers.begin() + posTeacher);
	}
}

void printRating(int rating){
	cout << "Rating: ";
	for(int i = 1; i <= rating; i++){
		cout << "*";
	}
	cout << endl;
}

void printRating(int rating){
	cout << "Rating: ";
	for(int i = 1; i <= rating; i++){
		cout << "*";
	}
	cout << endl;
}

/*
Phrase 1 (2021-2-10) [8]: Imaginemos una vaca esferica
Phrase 2 [7]: El mejor ejemplo de nihilistas lo podemos encontrar en un gimnasio
Phrase 3 (2021-2-14): Tolkien es como Rambo, pero en profesor de Oxford
Phrase 4: Hasta yo tengo mi parte malvada. Voy a Ikea y me llevo el lapiz
*/
void print(const Date &date){
	cout << " (" << date.year << "-" << date.month << "-" << date.day << ")";
}

void print(const Phrase &p){
	if(p.date.day != 0){
		print(p.date);
	}
	if(p.rating != 0){
		cout << " [" << p.rating << "]";
	}
	cout << ": " << p.text << endl;
}


void print(const vector<Phrase> &phrases){
	for(int i = 0; i < phrases.size(); i++){
		cout << "Phrase " << i + 1;
		print(phrases[i]);
	}
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
