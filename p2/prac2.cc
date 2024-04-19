// Programación 2 - Práctica 2
// DNI: x8594224k
// Nombre: Letisia Monica Sandu

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

// Registro para las preguntas
struct Question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch (e){
        case ERR_OPTION:
            cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY:
            cout << "ERROR: empty string" << endl;
            break;
        case ERR_UNIT:
            cout << "ERROR: wrong unit" << endl;
            break;
        case ERR_CHAR:
            cout << "ERROR: wrong char" << endl;
            break;
        case ERR_FILE:
            cout << "ERROR: cannot open file" << endl;
            break;
        case ERR_NAME:
            cout << "ERROR: wrong teacher name" << endl;
            break;
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated name" << endl;
            break;
        case ERR_PASSWORD:
            cout << "ERROR: wrong password" << endl;
            break;      
        case ERR_NO_QUESTIONS:
            cout << "ERROR: no pending questions" << endl;
            break;
        case ERR_ID:
            cout << "ERROR: wrong id" << endl;
            break;
        case ERR_ARGS:
            cout << "ERROR: wrong arguments" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
         << "2- Batch add questions" << endl
         << "3- Delete question" << endl
         << "4- Add teacher" << endl
         << "5- Add answers" << endl
         << "6- View answers" << endl
         << "7- View statistics" << endl
         << "8- Export questions" << endl
         << "q- Quit" << endl
         << "Option: ";
}

//funcion que se encarga de pedirle al usuario una neuva pregunta y la anyade a la base de datos
void addQuestion(Database &db){
	string nueva_unit, question;
	unsigned int unit;
	size_t pos = string::npos; //variable que almacena la posicion de '|' en la pregunta

	unit = 0;

	do{
		cout << "Enter unit: ";
		getline(cin, nueva_unit);
		
		if(nueva_unit.empty()){ //condicion que veriffica si la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{
			unit = stoi(nueva_unit); //si la entrada no esta vacia se tranforma a entero
			
			if(unit > 5 || unit < 1){ //condicion que verifica si unit esta dentro del rango permitido
				error(ERR_UNIT);
			}
		}
	}while(!nueva_unit.empty() && (unit < 1 || unit > 5)); //se repite le bucle mientras que la entrada no este vacia y unit este dentro del rango permitido
	
	if(!nueva_unit.empty()){ //condicion que verifica si unit no esta vacio
		do{
			cout << "Enter question: ";
			getline(cin, question);

			if(question.empty()){ //condicion que verifica si la pregunta introducida esta vacia
				error(ERR_EMPTY);
			
			}else{
				pos = question.find('|'); //se busca la posicion de '|' en la pregutna
				
				if(pos != string::npos){ //condicion que verifica si se encuntra el caracter
					error(ERR_CHAR);
				}		
			}
		}while(!question.empty() && pos != string::npos); //bucle que se repite mientras la pregunta no este vacia y no se encuentre '|'
		
		if(!question.empty()){ //condicion que verifica que la pregunta introducida no este vacia
			db.questions.push_back({db.nextId, unit, question, ""}); //entonces se anyade dicha pregunta a la base de datos
			db.nextId++; //y se incrementa el id para la proxima pregunta
		}
	}
}

//funcion que se encarga de buscar, en un vector de preguntas, una preguntas por su id
int searchIdQuestion(const vector<Question> &questions, int id) {
    int pos, i;

	pos = -1;
	i = 0;

    while (i < questions.size() && pos == -1) { //condicion que busca la posicion de la pregunta por su id
        if (questions[i].id == id) { //condicion que comprueba que el id que estamos buscando es igual al id de la posicion actual
            pos = i; //y si lo es se actualiza la posicion
        }
        i++;
    }
    return pos; //devuelve la posicion de la preguntada encontrada o -1 si no se ecuentra
}

//funcion parecida a la anterior, solo que busca el id una pregunta sin respuesta
//(procedimeinto parecido)
int searchPosQuestionNoAnswer(const vector<Question> &questions, int id) {
    int pos, i;

	pos = -1;
	i = 0;

    while (i < questions.size() && pos == -1) {
        if (questions[i].id == id && questions[i].answer == "") { //se comprueba ademas de si el id buscado es igual al id de la posicion actual,
																	// tambien si la respuesta de la pregunta en dicha psicion esta vacia
            pos = i; //si es asi se actualiza la posicion
        }
        i++;
    }
    return pos; //devuelve la posicion de la pregunta sin respuesta o -1 si no se ha encontrado
}

//funcion que se encarga de borrar una pregunta de la base de datos mendiante el id de dicha pregunta
void deleteQuestion(Database &data){
	int id, pos;
	string nueva_id;
	
	pos = -1;

	do{
		cout << "Enter question id: ";
		getline(cin, nueva_id);
		
		if(nueva_id .empty()){ //condicion que verifica si la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{
			id = stoi(nueva_id); //sino se tranforma la entrada a entero
			pos = searchIdQuestion(data.questions, id); //se busca el id de la pregunta en la base de datos
			
			if(pos == -1){ //condicion que verifica si no se ha encontrado la pregutna
				error(ERR_ID);
			
			}else{
				data.questions.erase(data.questions.begin() + pos);	//y si se encuentra, se borra del vector de preguntas
			}
		}
	}while(pos == -1 && !nueva_id.empty()); //se repite el bucle mientras NO se encuentre la pegunta en la base de datos y la entrada NO este vacia
}

//funcion que se encarga de eliminar los espacios en blanco, tanto del principio como del final, de una cadena de texto (nombre)
string deleteSpaces(string name){
	string espacio;
	int inicio, fin, tam;
	
	espacio = ""; //inicializo la cadena sin espacios
	inicio = 0;
	tam = name.length(); //obtenemos la longitud de la cadena
	
	while(inicio < tam && name[inicio] == ' '){ //bucle que busca el inicio de la cadena de texto sin espacios
		inicio++; //asi que mientras se encuentren espacios en blanco se incrementa el indice de inicio
	}
	
	fin = tam - 1; //lo inizializo como el ultimo indice de la cadena
	
	while(fin >= 0 && name[fin] == ' '){ //bucle que busca el final de la cadena de texto sin espacios
		fin--; //asi que mientras se encuentren espacios en blanco se decrementa el indice de inicio
	}
	
	espacio = name.substr(inicio, fin - inicio + 1); //extrae la parte de la cadena detexto que no tiene espacios en blanco, desde el inicio hasta el final
	return espacio; //por tanto, de devuelve la cadena de texto sin espacios en blanco
}

//funcion que se encarga de comprobar si el nombre del profesor es valido
bool comprobateTeacherName(string name){
	bool correcto;
	int i, tam;
	
	correcto = true;
	i = 0;
	tam = name.length();
	
	while(i < tam && correcto){ //condicion que verifica si cada iteracion de la cadena son letras o espacios en blanco
		if(name[i] != ' ' && !isalpha(name[i])){ //condicion que verifica si el caracter de la posicion actual NO es un
												  // espacio en blanco y NO es una letra
			correcto = false;
		
		}else{
			i++; //y si es valido pasa al siguiente caracter
		}
	}

	return correcto; //devuelve correcto que valida el nombre o no
}

//funcion que se encargar de buscar, en un vector de profesor, a un profe por su nombre
int buscarTeacherName(const vector<Teacher> &teachers, string name){
	int pos, i;
	
	pos = -1;
	i = 0;

	while(i < teachers.size() && pos == -1){ //bucle que se repite mientras haya mas profes por revisar y no se haya encontrado al profe
		if(teachers[i].name == name){ //condicion que verifica si el nombre del profe buscado es igual al nombre del profe de la posicion actual
			pos = i; //y si coincide, se actualiza la posicion
		}
		i++; //y pasa al siguiente profesor
	}
	
	return pos; //devuelve la posicion del profe encontrado o -1 si no se ha encontrado
}

//funcion que se encarga de pedir al usuario el nombre de un profesor y luego lo valida
string askTeacher(const vector<Teacher> &teachers){
	string nombre;
	int pos;
	bool nombre_correcto;

	pos = -1;
	nombre_correcto = false;

	do{
		cout << "Enter teacher name: ";
		getline(cin, nombre);
		
		if(nombre == ""){ //condicion que verifica si la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{
			nombre_correcto = comprobateTeacherName(nombre); //y luego se verifica si el nombre es valido con otra funcion
			
			if(!nombre_correcto){
				error(ERR_NAME);
			
			}else{
				nombre = deleteSpaces(nombre); //si el nombre es valido se borran los espacios en blanco
				
				if(nombre.length() < 3 || nombre.length() >= KMAXNAME){ //condicion que verifica si el nombre tiene la longitud correcta
					error(ERR_NAME);
					nombre_correcto = false;
				
				}else{
					pos = buscarTeacherName(teachers, nombre);// y si la tiene se busca al profe en el vector de profesores
					
					if(pos != -1){ //condicion que verifica si el profesor ya existe en el vector
						error(ERR_DUPLICATED); //y si existe muestra mensaje de error
					}
				}
			}
		}
	}while(nombre != "" && (!nombre_correcto || pos != -1)); //bucle que se repite mientras el nombre NO este vacio y NO sea valido
	
	return nombre;
}

//funcion que se encarga de validar una contrasenya
//condiciones: que tenga solo 4 caracteres y sean solo digitos
bool testPassword(string password){
	bool correcto;
	int i, tam;

	tam = password.length();
	if(tam == 4){  //condicion que verifica si el tamanyo de la contrasenya es de 4 caracteres
		correcto = true;
		
		for(int i = 0; i < tam && correcto; i++){ //bucle que recorre la contrasenya comprobando si los caracteres son digitos
			if(!isdigit(password[i])){ //condicion que verifica si el caracter actual NO es un digito
				correcto = false;
			}
		}
	}else{
		correcto = false; 
	}	
	return correcto; //devuelve correcto, que indica que la contrasenya es valida
}

//funcion que se encarga de pedir y validar una contrasenya
string askPassword(){
	string password;
	bool correcta;
	
	do{
		cout << "Enter password: ";
		getline(cin, password);
		
		if(password.empty()){ //condicion que comprueba si la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{
			correcta = testPassword(password); //sino se verifica si la contrasenya es valida
			
			if(!correcta){ //y si no es valida muestra mensaje de error
				error(ERR_PASSWORD);
			}
		}
	}while(!correcta && !password.empty()); //bucle que se repite mientras la contrasenya NO es valida y NO esta vacia
	
	return password;
}

//funcion que se encarga de generar un codigo a partir de una cadena de digitos
string code(string cadena){
	string aux;
	char codigos[] = "TRWAGMYFPD"; //codigos correspondientes a cada numero
	int i;
	
	i = 0;
	aux = ""; //la inicializamos vacia

	for(i = 0; i < cadena.length(); i++){ //bucle que recorre la cadena de numeros 
		aux = aux + codigos[cadena[i] - '0'];
	}

	return aux; //devuelve codigo generado
}

//funcion que se encarga de anyadir un nuevo profe
void addTeacher(Database &data){
	Teacher profe;
	string nombre, contrasenya, c_correcta;
	
	nombre = askTeacher(data.teachers); //se pide el nombre de un nuevo profe y se valida
	
	if(nombre != ""){ //condicion que verifica que el nombre no este vacio
		contrasenya = askPassword(); //continua pidiendo la contrasenya y la valida
		
		if(contrasenya != ""){ //condicion que verifica que la contrasenya no este vacia
			c_correcta = code(contrasenya); //se genera el codigo para la contrasenya

			//se copia el nombre y la contrasenya al objeto Teacher
			strcpy(profe.name, nombre.c_str());
			strcpy(profe.password, c_correcta.c_str());
			profe.answered = 0;
			data.teachers.push_back(profe); //se anyade el nuevo profe a la base de datos
		}
	}	
}

//funcion que se encarga de mostrar las preguntas que no tengan respuestas
void showQuestions(const vector<Question> &questions){
	for(int i = 0; i < questions.size(); i++){ //bucle que recorre cada pregunta
		if(questions[i].answer == ""){ //condicion que verifica si la pregunta actual tiene respuesta
			cout << questions[i].id << ". (" << questions[i].unit << ") " << questions[i].question;
			cout << endl;
		}
	}
}

//funcion que devuelve la cantidad de preguntas sin responder
int contarSinResponder(const vector<Question> &questions){
	int no = 0;
	for(int i = 0; i < questions.size(); i++){ //bucle que recorre cada pregunta dle vector de pregutnas
		if(questions[i].answer == ""){ //condicion que verifica si la pregunta actual esta sin responder
			no++;
		}
	}
	return no; //devuelve cantidad de preguntas sin responder
}

//funcion que se encarga de anyadir repsuestas a las preguntas que aun no estan contestadas
void addAnswer(Database &data){
	bool pedir, contestar;
	string nombre, contrasenya, q_id, respuesta, cod;
	int id, sinResponder, posTeacher, posQuestion;

	sinResponder = 0;
	
	do{ //bucle que pide el nombre del profesor
		pedir = false;
		cout << "Enter teacher name: ";
		getline(cin, nombre);
		
		if(nombre.empty()){ //condidion que verifica que la entrada esta vacia
			error(ERR_EMPTY);
		
		}else{
			posTeacher = buscarTeacherName(data.teachers, nombre);	//si no esta vacia, busca el nombre en la base de datos
			
			if(posTeacher == -1){ //condicion que verifica que el nombre del profe NO lo encuentra
				error(ERR_NAME);
				pedir = true; //lo ponemos true para que vuelva a solicitar otra vez el nombre del profesor
			}
		}
	}while(pedir); //se repite mientras pedir sea true
	
	if(nombre != ""){ //si el nombre no esta vacio...
		do{ //bucle que pide la contrasenya
			pedir = false;
			cout << "Enter password: ";
			getline(cin, contrasenya);
			
			if(contrasenya == ""){ //condicion que verifica si la contrasenya esta vacia
				error(ERR_EMPTY);
			
			}else{
				cod = code(contrasenya); //y si no esta vacia pasa a codificarla
				
				if(cod != data.teachers[posTeacher].password){ //condicion que verifica si la constrasenya es correcta
					error(ERR_PASSWORD);
					pedir = true; //y si no es correcta, vuelve a pedirla
				}
			}	
		}while(pedir); //se repite mientras pedir sea true
		
		if(contrasenya != ""){ //condicion que verifica si la contrasenya esta vacia
			sinResponder = contarSinResponder(data.questions); //devuelve la cantidad de preguntas sin contestar
			
			if(sinResponder == 0){ //condicion que compara si hay o no preguntas sin responder
				error(ERR_NO_QUESTIONS);
			
			}else{
				do{ //bucle para anyadir respuestas a las preguntas sin responder
					showQuestions(data.questions);
					do{
						cout << "Enter question id: ";
						getline(cin, q_id);
						
						if(q_id.empty()){ //condicion que verifica si id esta vacio
							error(ERR_EMPTY);
							pedir = false;
							contestar = false;
						
						}else if(q_id == "b"){
								pedir = false;
								contestar = false;
							
							}else{
								posQuestion = searchPosQuestionNoAnswer(data.questions, stoi(q_id)); //busca la posicion de la pregunta
								if(posQuestion == -1){
									error(ERR_ID);	
									pedir = true;
								
								}else{
									pedir = false;
								}
							}
					}while(pedir); //se repite el bucle mientras pedir sea true
					
					respuesta = "";
					
					if(q_id != "" && q_id != "b"){ //condicion que comprueba si se dee anyadir una respuesta a la pregunta
						contestar = true;
						
						do{	//bucle que pide la respuesta	
							cout << "Enter answer: ";
							getline(cin, respuesta);
							pedir = true;
							
							if(respuesta == ""){ //condicion que verifica si respuesta esta vacia
								error(ERR_EMPTY);
								pedir = false;
								contestar = false;
							
							}else if(respuesta.find('|') != string::npos){ //condicion que verifica si la respuesta tiene '|'
								error(ERR_CHAR);
								
								}else{
									pedir = false;
								}
							
						}while(pedir); //se repite mientras pedir sea true
						
						if(respuesta != ""){ //condicion que verifica que la respuesta NO este vacia
							data.questions[posQuestion].answer = respuesta; //y la anyade a la pregunta correspondiente
							data.teachers[posTeacher].answered++; //incrementamos el contador de pregutnas respondidas
							sinResponder--; //y decrementa las preguntas sin responder
							
							if(sinResponder == 0){ //condicion que verifica que NO hay mas preguntas sin responder
								error(ERR_NO_QUESTIONS);
							}
						}
					}
					else{
						contestar = false;
					}
				}while(q_id != "b"  && q_id != "" && respuesta != ""); //se repite el bucle mientras se introduzca 'b', se deje en blanco el id o la pregunta
			}
		}
	}	
}

//funcion que se encarga de verificar si la respuesta de cada repgunta NO esta vacia
void viewAnswers(const Database &data){
	
	for(size_t i = 0; i < data.questions.size(); ++i) {
    	if(data.questions[i].answer != "") {
			//y si la respuesta no esta vacia imprimimos el id, la unidad, la pregunta y la respuesta
        	cout << data.questions[i].id << ". (" << data.questions[i].unit << ") " << data.questions[i].question << ": " << data.questions[i].answer << endl;
    	}
	}
}

//funcion que se encarga de imprimir el nombre y el numero de preguntas respondidas por cada profesor
void viewStatistics(const Database &data){
	cout << "Total number of questions: " << data.questions.size() << endl;
	cout << "Number of questions answered: " << data.questions.size() - contarSinResponder(data.questions) << endl;
	
	for(size_t i = 0; i < data.teachers.size(); ++i) {
    	cout << data.teachers[i].name << ": " << data.teachers[i].answered << endl;
	}
}

//funcion que se encarga de llevar las preguntas y respuestas a un archivo de texto
void exportQuestions(const Database &data){
	bool continuar;
	string filename;
	ofstream fichero;
	
	do{ //bucle que pide nombre del archivo
		cout << "Enter filename: ";
		getline(cin, filename);
		
		if(filename == ""){ //condicion que verifica si el nombre del archivo esta vacio
			error(ERR_EMPTY);
			continuar = false;
		
		}else{
			fichero.open(filename.c_str()); //si no esta vacio abre el archivo con dicho nombre
			
			if(fichero.is_open() == false){  //condicion que verifica si se ha abierto correctamente
				error(ERR_FILE);
				continuar = true;
			
			}else{
				continuar = false;
				
				//bucle que recorre todas las preguntas y escribe sus datos en el archivo
				for(size_t i = 0; i < data.questions.size(); ++i) {
    				fichero << data.questions[i].unit << "|" << data.questions[i].question;
    				
					//y si la pregunta tiene una respuesta, esta se escribe en el archivo
					if(data.questions[i].answer != "") {
        				fichero << "|" << data.questions[i].answer;
    				}
    				fichero << endl;
				}
				fichero.close(); //se cierra el archivo
			}
		}
	}while(continuar); //se repite mientras que continuar sea true
}

//funcion que se encarga de cargar desde un fichero binario datos de profesores y los anyade al vector de profesores
void loadTeachers(vector<Teacher> &teachers){
	Teacher nuevo;

	ifstream fich("teachers.bin", ios::binary); //abre el archivo binario en modo lectura
	if(fich.is_open()){ //condicion que verifica si el archivo esta abierto correctamente
		while(fich.read((char *) &nuevo, sizeof(nuevo))){ //condicion que lee datos del archivo
			teachers.push_back(nuevo); //y los anyade al vector de profesores
		}
		fich.close(); //finalmente cierra el archivo despues de leer todos los datos
	}
}

//funcion que se encarga de guardar los datos de profesores en un archivo binario
void saveTeachers(const vector<Teacher> &teachers){
	ofstream fich("teachers.bin", ios::binary); //abre el archivo binario en modo escritura
	
	if(fich.is_open()){ //condicion que verifica si se ha abierto correctamente
		//bucle que escribe los datos del profesor en el archivo
		for(size_t i = 0; i < teachers.size(); ++i) {
    		fich.write((const char *) &teachers[i], sizeof(teachers[i]));
		}
		fich.close(); //cierra el archivo despues de escribir todos los datos 
	}
	else{
		error(ERR_FILE); //muestra error si no se pudo abrir
	}
}

//funcion que se encarga de procesar los argumentos de la linea de comando pasados al programa
bool processArguments(int argc, char *argv[], string &nombre, bool &s){
	bool correcto;
	
	nombre = "";
	s = false;
	correcto = true;
	
	for(int i = 1; i < argc && correcto; i++){ //bucle que recorre los argumentos de la linea de comandos
		if(strcmp(argv[i], "-f") == 0){ //condicion que verifica si el argument actual es '-f'
			if(nombre != ""){ //condicion que verifica si ya se dio un nombre de archivo
				correcto = false; //porque ya tenia nombre de fichero.
			
			}else{
				if(i + 1 < argc){ //condicion que verifica si hay un nombre de archivo despues de '-f'
					nombre = argv[i + 1]; //si hay, entonces lo almacena en nombre
					i++; //salta al siguiente argumento
				
				}else{
					correcto = false;
				}
			}
		
		}else{
			if(strcmp(argv[i], "-s") == 0){ //condicion que verifica si el argumento actual es '-s'
				if(s == true){ //entonces activa s
					correcto = false;
				}
				else{
					s = true;
				}
			}
			else{
				correcto = false;
			}
		}
		if(!correcto){ //condicion que comprueba si hay algun prolema con los argumentos
			error(ERR_ARGS);
		}
	}
	return correcto;
}

//funcion que se encarga de verificar el formato de la linea si es correcto:
//(id | pregunta) o (id | pregunta | respuesta)
void procesarLinea(Database &data, string linea, int barra, int &agregadas){
	int pos1, pos2, pos3;
	string part1, part2, part3;
	Question nueva;
	
	//busca la primera barra '|' en la linea
	pos1 = linea.find('|');
	if(pos1 == string::npos){
		cout << "Error line " << barra; //no hay barras
		cout << endl;
	
	}else{
		//busca la segund barra en la linea
		pos2 = linea.find('|', pos1 + 1);
		
		if(pos2 == string::npos){ //condicion que verifica si solo hay una barra
				part1 = linea.substr(0, pos1); //entonces extrae la primera parte antes de la barra
				part2 = linea.substr(pos1 + 1); //y hace lo mismo con l segunda parte despues de la linea
				
				if(part1 == "" || part2 == ""){ //condicion que verifica si alguna parte, de las extraidas, esta vacia
					cout << "Error line " << barra;
					cout << endl;
				
				}else{
					nueva.unit = stoi(part1); //convierte la primera parte en un entero
					
					if(nueva.unit < 1 || nueva.unit > 5){ //condicion que verifica si el entero esta dentro del rango proporcionado
						cout << "Error line " << barra;
						cout << endl;
					
					}else{
						nueva.question = part2; //entonces establece la segunda parte como pregunta
						nueva.answer = "";
						nueva.id = data.nextId++; //le da un neuvo id a la pregunta
						data.questions.push_back(nueva); //y anyade la nueva pregunta a la base de datos
						agregadas++;
					}
				}
		
		}else{
			//busca la tercera barra en la linea
			pos3 = linea.find("|", pos2 + 1);
			
			if(pos3 != string::npos){ //condicion que verifica si hay mas de dos barras en la linea
				cout << "Error line " << barra;
				cout << endl;
			
			}else{
				part1 = linea.substr(0, pos1); //extrae la primera parte antes de la primera barra
				part2 = linea.substr(pos1 + 1, pos2 - pos1 - 1); //extrae la segunda parte entre las dos barras
				part3 = linea.substr(pos2 + 1); //extrae la tercera parte despues de la ultima barra
				
				if(part1 == "" || part2 == "" || part3 == ""){ //condicion que verifica si alguna parte esta vacia
					cout << "Error line " << barra;
					cout << endl;
				
				}else{
					nueva.unit = stoi(part1); //convierte la primera parte en entero (id)
				
					if(nueva.unit < 1 || nueva.unit > 5){ //condicion que verifica si el entero esta dentro del rango permitido
						cout << "Error line " << barra;
						cout << endl;
				
					}else{
						nueva.question = part2; //establece la segunda parte como pregutna
						nueva.answer = part3; //establece la tercera parte como respuesta
						nueva.id = data.nextId++; //le da un nuevo id a la pregunta
						data.questions.push_back(nueva); //y anyade la nueva pregunta a la base de datos
						agregadas++;
					}			
				}
			}
		}
	}
}

//funcion que deja anyadir preguntas desde un archivo de texto a la base de datos
void batchAddQuestions(Database &data, string filename){
	bool abierto;
	int num_l, agregadas, noVacias;
	string linea;
	ifstream fichero;
	
	if(filename == ""){ //condicio que verifica si nombre de archivo esta vacio
		do{
			abierto = false;
			cout << "Enter filename: ";
			getline(cin, filename);
			
			if(filename == ""){ //condicion que verifica si se introdujo un nombre de archivo
				error(ERR_EMPTY);
			
			}else{
				fichero.open(filename.c_str()); //abrimos el archivo
				
				if(!fichero.is_open()){ //y se comprueba si se h abierto acorrectamente
					error(ERR_FILE);
				
				}else{
					abierto = true;
				}
			}
		}while(filename != "" && !abierto); //se repite meintras el nombre del archivo este vacio y no cerrado
	
	}else{
		fichero.open(filename.c_str()); //abrimos el archivo
		
		if(!fichero.is_open()){ //y se comprueba si se ha abierto correctamente
			error(ERR_FILE);
			abierto = false;
		
		}else{
			abierto = true;
		}
	}
	if(abierto == true){ //si se ha leido correctamente ahora procesamos las lineas
		agregadas = 0;
		num_l = 1;
		noVacias = 0;
		
		while(getline(fichero, linea)){ //condicion que lee cada linea del archivo
			if(linea != ""){ //condicion que verifica si la linea NO esta vacia
				procesarLinea(data, linea, num_l, agregadas);
				noVacias++; //
			}
			num_l++;
		}
		//imprimimos un summary de las preguntas introducidas
		cout << "Summary: " << agregadas << "/"  << noVacias << " questions added";
		cout << endl;

		fichero.close(); //se cierra el archivo
	}
}

// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    data.nextId=1;
    char option;
    bool ok, s;
    string filename;
    
    ok = processArguments(argc, argv, filename, s);
    if(ok){
    	if(filename != ""){
    		batchAddQuestions(data, filename);
    	}
    	if(s){
    		viewStatistics(data);
    		return 666;
    	}
		loadTeachers(data.teachers);
		do{
		    showMenu();
		    cin >> option;
		    cin.get();
		    
		    switch(option){
		        case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
		        	addQuestion(data);
		            break;
		        case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
		            batchAddQuestions(data, "");
		            break;
		        case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
		        	deleteQuestion(data);
		            break;
		        case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
		        	addTeacher(data);
		            break;
		        case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
		        	addAnswer(data);
		            break;
		        case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
		            viewAnswers(data);
		            break;
		        case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
		            viewStatistics(data);
		            break;
		        case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
		            exportQuestions(data);
		            break;
		        case 'q': // Salir del programa guardando los profesores en fichero
	 				saveTeachers(data.teachers);
		            break;
		        default: error(ERR_OPTION);
		    }
		}while(option!='q');
 	}
 return 0;
}

