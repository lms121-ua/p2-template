// Programación 2 - Práctica 1
// DNI: x8594224k
// Nombre: Letisia Monica Sandu

#include <iostream>
#include <vector>
#include <cstring>

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

//Funcion que se encarga de mostrar toda la informacion de los años academicos, y tambien
//los identificadores, nombre, apodos, notas(rating) de los profesores, y las frases asociadas a cada profesor 
void showGirls(const vector<AcademicYear> &years){
	// mostrar los identificadores
	cout << "los identificadores" << endl;
	cout << "===================" << endl;
	for(int i = 0; i< years.size(); i++){ //bucle que recorre el vector de años academicos
		cout << years[i].id << endl;
		
		for(int j = 0; j < years[i].listTeachers.size(); j++){ //bucle que recorre cada profesor de la posicion actual de año academico
			cout << "\t" << years[i].listTeachers[j].name << ", " 
			<< years[i].listTeachers[j].nickname<< ", " << years[i].listTeachers[j].rating << endl;			
			
			for(int k = 0; k < years[i].listTeachers[j].listPhrases.size(); k++){ //bucle que recorre cada frase asociada a la posicion actual de cada profesor
				cout << "\t\t" << years[i].listTeachers[j].listPhrases[k].text << endl;
			}
		}
	}
}


// Funcion que se encarga de bsucar la posición de un año que le hayamos introducido recorriendo el vector
// AcademicYear, y si no está devueolve -1.
int buscarYear(int year, const vector<AcademicYear> &years){
	int pos = -1;
	for(int i = 0; i < years.size()&& pos == -1; i++){
		if(years[i].id == year){
			pos = i;
		}
	}
	return pos;
}

//Funcion que se encarga de buscar un profe especifico -teacherName- dentro del vector de años academicos -vector<AcademicYears>-
//y sus respectvas listas de profes
void buscarTeacher(int &posYear, int &posTeacher, string teacherName, const vector<AcademicYear> &years){
	int i, j;
	posTeacher = -1;
	posYear = -1;
	
	for(i = 0; i < years.size() && posYear == -1; i++){ //bucle sobre los años academicos en busca del profe
		for(j = 0; j <  posYear == -1 && years[i].listTeachers.size(); j++){  //bucle sobre la lista de profes del año academico actual
			if(years[i].listTeachers[j].name == teacherName){ //condicion que comprueba si el nombre del profe coincide con el nombre buscado
				posYear = i;
				posTeacher = j;
			}
		}
	}
}

// Función que se utilizará en la función -addAcademicYear-, en la que se encargue pedir al usuario
// un año academico y devuelve su posición en el vector gracias al módulo -buscarYear-
bool askNotExistYear(int &noEncontrado, const vector<AcademicYear> &years){
	string anyo;
	bool vacio;
	int pos;
	pos = -1;

	do{
		cout << "Enter academic year: ";
		getline(cin, anyo);
		
		if(anyo.length() == 0){ //condicion que verifica si la entrada del usuario está vacia
			error(ERR_EMPTY); //si está vacia, muestra error
			vacio = true;
		}
		else{
			vacio = false;
			pos = buscarYear(stoi(anyo), years); //busca si el año que ingresó el usuario ya existe en el vector
			
			if(pos == -1){ //condicion que se encarga de asignarle el año ingresado a noEcontrado, si el año no estñá en el vector 
				noEncontrado = stoi(anyo); 
			}else{
				error(ERR_DUPLICATED); //si el año ingresado existe en el vector, se muestra el mensaje de error
			}
		}
	}while(pos != -1 && !vacio); //continua el bucle si la entrada no está vacia y el año ingresado no existe en el vector
	
	return vacio;
}

// Función que se utilizará en la función -deleteAcademicYear-, en la que se encargue pedir al usuario
// un año academico y vuelve a pedirlo si no esta en le vector mediante el modulo -buscarYear-
int askExistYear(const vector<AcademicYear> &years){
	string anyo;
	bool encontrado;
	int pos;
	pos = -1;

	do{
		cout << "Enter academic year: ";
		getline(cin, anyo);
		
		if(anyo.length() == 0){ //condicion que comprueba si la entrada esta vacia
			error(ERR_EMPTY);
			encontrado = false;
		
		}else{
			pos = buscarYear(stoi(anyo), years); //busca si el año ingresado está en el vector
			
			if(pos == -1){ //condicion que se cumple si dicho año no está en el vector
				error(ERR_NOT_EXIST);
				encontrado = true;
			
			}else{
				encontrado = false;
			}
		}
	}while(encontrado);

	return pos;
}

//Funcion que se encarga de añadir años academicos ingresados por el usuario, utilizando el 
//modulo -askExistYear-
void addAcademicYear(vector<AcademicYear> &years){
	
	bool vacio;
	AcademicYear nuevo;

	vacio = askNotExistYear(nuevo.id, years); //comprueba si el año ingresado ya existe en el vector
	
	if(!vacio){
		years.push_back(nuevo); //se añade el nuevo año si no existe en el vector (con la instruccion de push_back) 
	}
}	

//Funcion que se encarga de eliminar años academicos ingresados por el usuario, utilizando el 
//modulo -askNotExistYear-
void deleteAcademicYear(vector<AcademicYear> &years){
	
	int pos;
	pos = askExistYear(years); //se busca el año en el vector
	
	if(pos != -1){
		years.erase(years.begin() + pos); //se elimina dicho año en la posicion 'pos' del vector,
											//en caso de que el año exista en el vector
	}	
}

//Funcion que se encarga de pedir al usuario una nota y se comprueba si se encuentra
//dentro del rango correspondiente
void askRating(int &rating, int inicio, int fin){
	string aux; //variable auxiliar para almacenar la entrada del usuario
	bool continuar;
	continuar = true;

	do{
		cout << "Enter rating: ";
		getline(cin, aux);
		
		if(aux.length() == 0){ //condicion que comprueba si la entrada está vacia
			rating = 0; //si la entrada esta vacia se le asigna 0
			continuar = false; //y se sale del bucle

		}else{
			rating = stoi(aux); //si la entrada no esta vacia se convierte a entero (stoi)
			
			if(rating < inicio || rating > fin){ //condicion que comprueba si el rating esta fuera del rango permitido
				error(ERR_RATING); //si se encuentra fuera del rango muestra mensaje de error
				continuar = true;

			}else{
				continuar = false;
			}
		}
	}while(continuar = true); //bucle que se repite mientras "continuar" sea verdadero 
}

//Funcion que se encarga de imprimir por pantalla un dibujo de * segun rating que se le haya proporcionado como argumento
void printRating(int rating){
	int i;
	cout << "Rating: ";
	
	for(i = 1; i <= rating; i++){ //bucle que imprime tantas veces el valor del rating
		cout << "*";
	}
	cout << endl;
}

//Funcion que se encarga de pedir al usuario datos de un profesor (apodo y nota), que pasan
//por diferentes condiciones para validar esos datos
bool askDatosTeacher( Teacher &nuevo, const vector<AcademicYear> &years){
	bool datos;
	string aux;
	
	cout << "Enter nickname: "; //se pide al usuario el apodo del profe
	getline(cin, nuevo.nickname);
	
	cout << "Enter subject: "; //se pide la asignatura del profe
	getline(cin, aux);
	
	if(aux.length() == 0){ //condicion que comprueba si la segunda entrada esta vacia
		datos = true;
		error(ERR_EMPTY);
	
	}else{ //en el caso de que la entrada NO este vacia
		strncpy(nuevo.subject, aux.c_str(), MAXSUBJECT); //se copia la cadena a "nuevo.subject"
		nuevo.subject[MAXSUBJECT - 1] = '\0'; //damos la ultima posicion a '\0', para que no haya desbordamiento de buffer
		askRating(nuevo.rating, 1, 5); //llamamos al modulo -askRating- le pedimos al usuario al nota dentro del rango 1-5
		datos = false;
	}

	return datos; //de devuelve el valor de "datos", que significa si han introducido datos correctos o no
}

//Funcion que se encarga de pedir al usuario que introduzca el nombre de un profesor que no existe en el sistema
void askNotExistTeacher(const vector<AcademicYear> &years, string &name){
	int posAnyo; //posicion año academico
	int posTeacher; //posicion profe

	do{
		cout << "Enter teacher name: "; //se pide el nombre del profe
		getline(cin, name);
		
		if(name.length() == 0){ //condicion que comprueba si la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{ //si la entrada no esta vacia
			buscarTeacher( posAnyo, posTeacher, name, years); //se busca al profe en los años academicos
			
			if(posAnyo != -1){ //condicion que encuentra al profe
				error(ERR_DUPLICATED); //y se muestra un mensaje de error (osea ese profe ya existe)
			}
		}
	}while( posAnyo != -1 && name != ""); //bucle que se repite mientras no se encuentre el profe y el nombre NO este vacio
}

//Funcion que se encarga de pedir al usuario que introduzca el nombre de un profesor que ya existe en el sistema
void askExistTeacher(const vector<AcademicYear> &years, int &posAnyo, int &posTeacher){
	string name;
	bool a;
	posAnyo = posTeacher = -1;

	do{
		cout << "Enter teacher name: "; //se pide nombre del profe
		getline(cin, name);
		
		if(name.length() == 0){ //condicion que comprueba si la entrada esta vacia
			error(ERR_EMPTY);
			a = false; 
		
		}else{ //si la entrada no esta vacia
			buscarTeacher( posAnyo, posTeacher, name, years); //se busca al profe en los años academicos
			
			if(posAnyo == -1){ //y si no esta en ningun año
				error(ERR_NOT_EXIST); //se muestra mensaje de error
				a = true;
			
			}else{
				a = false; 
			}
		}
	}while(a); //bucle que continua mientras "a" sea verdadero 
}

//Funcion que se encarga de añadir un nuevo profesor al sistema
void addTeacher(vector<AcademicYear> &years){
	Teacher nuevo;
	int pos;	
	bool error;
	
	pos = askExistYear(years); //el usuario debe seleccinar un año academico que exista
	if(pos != -1){ //condicion que comprueba si dicho año es existente
		askNotExistTeacher(years, nuevo.name); 
		
		if(nuevo.name != ""){ //condicion que comprueba si se ingresa un nombre de profe NO vacio
			error = askDatosTeacher(nuevo, years); //y se piden otros datos sobre el profe
			
			if(!error){ //si no hay errores en los datos
				years[pos].listTeachers.push_back(nuevo); //se agrega el nuevo profe a la lista de profesores -listTTeachers- (push_back)
			}
		}
	}	
}

//Funcion que se encarga de eliminar a un profesor del sistema
void deleteTeacher(vector<AcademicYear> &years){
	int posTeacher;
	int posAnyo;
	
	askExistTeacher(years, posAnyo, posTeacher); //se pide al usuario que escoja a un profe existente 
	if(posAnyo != -1){ //condicion que comprueba si el profe es valido
		years[posAnyo].listTeachers.erase(years[posAnyo].listTeachers.begin() + posTeacher); //se elimina al profe de la lista de profesores del año academico seleccionado
	}
}

//Funcion que se encarga de imprimir por pantalla una fecha
void print(const Date &date){
	cout << " (" << date.year << "-" << date.month << "-" << date.day << ")";
}

//Funcion que se encarga de imprimir una frase con texto, fecha y un rating
void print(const Phrase &p){
	if(p.date.day != 0){ //condicion que comprueba si la fecha de la frase esta definida
		print(p.date);
	}
	
	if(p.rating != 0){ //condicion que comprueba si el rating de la frase esta definido
		cout << " [" << p.rating << "]";
	}
	
	cout << ": " << p.text;
	cout << endl;
}

//Funcion que se encarga de imprimir todas las frases de un vector de frases -vector<Phrases>-
void print(const vector<Phrase> &phrases){
	int i;

	for(i = 0; i < phrases.size(); i++){ //bucle que recorre cada elemento del vector<Phrases>
		cout << "Phrase " << i + 1;
		print(phrases[i]);
	}
}

//Funcion que se encarga de mostrar los datos relacionados con el profesor
void showDatosTeacher(const Teacher &teacher){
	cout << "Name: " << teacher.name << endl;
	
	if(teacher.nickname != ""){ //condicion que comprueba si el apodo NO esta vacio
		cout << "Nickname: " << teacher.nickname << endl;
	}
	
	cout << "Subject: " << teacher.subject << endl;
	
	if(teacher.rating != 0){ //condicion que comprueba si la nota del profe NO es 0
		printRating(teacher.rating); //imprime la nota(rating)
	}
	
	print(teacher.listPhrases);	//imprime las frases asociadas al profesor
}

//Funcion que se encarga de extraer los elementos de una fecha de una cadena (año-mes-dia)
//y los añade a una estructura 'Date'
void extractDate(string cad, Date &date){
	int i;
	string aux;
	
	if(cad.length() == 0){ //condicion quue comprueba si la cadena esta vacia
		date.day = date.month = date.year = 0;
	
	}else{
		aux = "";
		i = 0;
		
		while(cad[i] != '-'){ //bucle que extrae el año de la cadena hasta encontrar el primer guion '-'
			aux += cad[i]; 
			i++;
		}
		i++;
		date.year = stoi(aux); //convertimos la cadena a entero y asigno el año
		aux = ""; //reinciamos la cadena aux
		
		while(cad[i] != '-'){ //bucle que extrae el mes de la cadena hasta encontrar el segundo guion '-'
			aux += cad[i];
			i++;
		}
		i++;
		date.month = stoi(aux); //convertimos la cadena a entero y asigno el mes
		aux = ""; //reiniciamos la cadena aux
		
		while(i < cad.length()){ //bucle que extrae el dia de la cadena desde la posicion actual hasta el final de la cadena
			aux += cad[i];
			i++;
		}
		date.day = stoi(aux); //convertimos la cadena a entero y asigno el dia
	}
}

//Funcion que se encarga de mostrar la informacion de un profesor seleccionado, junto con su
//año academico correspondiente
void showTeacher(vector<AcademicYear> &years){
	int posTeacher, posYear;
	
	askExistTeacher(years, posYear, posTeacher); //se pide al usuario que elija a un porfe que exista
	
	if(posYear != -1){ //condicion que comprueba si dicho profe es valido
		cout << "Academic year: " << years[posYear].id << endl; //se imprime por pantalla el año academico correspondiente del profe
		showDatosTeacher(years[posYear].listTeachers[posTeacher]); //y su informacion
	}
}

//Funcion que se encarga de encontrar si algun profesor, en el vector de profesores, tiene frases en su lista de frases
bool tienenFrases(const vector<Teacher> &teachers){
	int i;
	bool tienen;
	tienen = false;

	for(i = 0; i <  !tienen && teachers.size(); i++){ //bule que recorre vector de profesores
		if(teachers[i].listPhrases.size() != 0){ //condicion que comprueba si el profe de la posicion actual tienen frases en su lista de frases
			tienen = true;
		}
	}
	return tienen; //se devuelve el valor de tienen que indica si algun profe tiene frases
}

//Funcion que se encarga de que el usuario pueda añadir una frase nueva a la lista de frases de un profesor 
//en un año academico concreto
void addPhrase(vector<AcademicYear> &years){
	int posTeacher, posAnyo;
	string aux;
	Phrase nueva;
	
	askExistTeacher(years, posAnyo, posTeacher); //se pdie al usuario que elija a un profe que ya exista
	if(posAnyo != -1){ //condicion que comprueba el dicho año es valido
			cout << "Enter phrase: ";
			getline(cin,  nueva.text);
			
			if(nueva.text == ""){ //condicion que comprueba si la frase esta vacia
				error(ERR_EMPTY);
			
			}else{ //si la frase NO esta vacia pedir al usuario que introduzca una fecha en ese formato
				cout << "Enter date (year-month-day): ";
				getline(cin, aux),
				
				extractDate(aux, nueva.date); //extraer la fecha de la cadena que se ha introducido y asignarla a nueva.date
				askRating(nueva.rating, 1, 10);	//pedir al usuario la nota (rating) para la frase
				years[posAnyo].listTeachers[posTeacher].listPhrases.push_back(nueva); //agregar la nueva frase al vector de frases del profesor escogido
			}
	}	
}

//Funcion que se encarga de generar un resumen de los años academicos, imprimiendo los profes que tienen frases, 
//por orden descendiente segun su identificador
void summary(const vector<AcademicYear> &years){
	vector<AcademicYear> aux = years;
	string nombre;
	
	for (int i = 0; i < aux.size() - 1; ++i) { //se ordena el vector de años academicos en orden descendiente
		for (int j = 0; j < aux.size() - i - 1; ++j) {
		    if (aux[j].id < aux[j + 1].id) {
				AcademicYear temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
		    }
		}
	}
	
	for(int i = 0; i < aux.size(); i++){
		if(aux[i].listTeachers.size() != 0){ //condicion que comprueba si el año academico tiene profesores
			if(tienenFrases(aux[i].listTeachers)){ //condicion que comprueba si algun porfesor tiene frases
				cout << "Academic year: " << aux[i].id << endl;
				
				for(int j = 0; j < aux[i].listTeachers.size(); j++){ //bucle que recorre los profes del año academico
					if(aux[i].listTeachers[j].listPhrases.size() != 0){ //ondicion que comprueba si algun porfesor tiene frases
						nombre = aux[i].listTeachers[j].name; //almacena el nombre del profe
						
						for(int k = 0; k < aux[i].listTeachers[j].listPhrases.size(); k++){ //bucle que recorre las frases del profe
							cout << nombre;
							
							if(aux[i].listTeachers[j].listPhrases[k].rating != 0){ //condicion que comprueba si hay alguna nota (rating) asociada a la frase
								cout << " - "
								<< aux[i].listTeachers[j].listPhrases[k].rating; //imprime nota
							}
							cout << " - "
							<< aux[i].listTeachers[j].listPhrases[k].text; //imprime frase
							cout << endl;
						}
					}
				}
			}
		}
	}
}

int main(){
	vector<AcademicYear> years;
    char option;
    
    do{
    	//showGirls(years);
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
				addAcademicYear(years);            	
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                deleteAcademicYear(years);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
            	addTeacher(years);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                deleteTeacher(years);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                showTeacher(years);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                addPhrase(years);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
            	summary(years);
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
