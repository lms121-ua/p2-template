// Programación 2 - Práctica 2
// DNI: x8594224k
// Nombre: Letisia Monica Sandu

#include <iostream>
#include <vector>

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
int buscarQuestionById(const vector<Question> &questions, int id){
    int pos, i;
    pos = -1;
    for(i = 0; i < questions.size() && pos == -1; i++){
        if(questions[i].id == id){
            pos = i;
        }
    }
    return pos;
}

int buscarQuestionByIdOnlyFans(const vector<Question> &questions, int id){
    int pos, i;
    pos = -1;
    for(i = 0; i < questions.size() && pos == -1; i++){
        if(questions[i].id == id && questions[i].answer == ""){
            pos = i;
        }
    }
    return pos;
}
void addQuestion(Database &db){
    string s_unit, question;
    unsigned int unit = 0;
    size_t pos = string::npos;
    do{
        cout << "Enter unit: ";
        getline(cin, s_unit);
        if(s_unit == ""){
            error(ERR_EMPTY);
        }
        else{
            unit = stoi(s_unit);
            if(unit < 1 || unit > 5){
                error(ERR_UNIT);
            }
        }
    }while(s_unit != "" && (unit < 1 || unit > 5));
    if(s_unit != ""){
        do{
            cout << "Enter question: ";
            getline(cin, question);
            if(question == ""){
                error(ERR_EMPTY);
            }
            else{
                pos = question.find('|');
                if(pos != string::npos){
                    error(ERR_CHAR);
                }       
            }
        }while(question != "" && pos != string::npos);
        if(question != ""){
            db.questions.push_back({db.nextId, unit, question, ""});
            db.nextId++; 
        }
    }
}

void deleteQuestion(Database &data){
    string s_id;
    int id, pos = -1;
    do{
        cout << "Enter question id: ";
        getline(cin, s_id);
        if(s_id == ""){
            error(ERR_EMPTY);
        }
        else{
            id = stoi(s_id);
            pos = buscarQuestionById(data.questions, id);
            if(pos == -1){
                error(ERR_ID);
            }
            else{
                data.questions.erase(data.questions.begin() + pos); 
            }
        }
    }while(s_id != "" && pos == -1);
}

bool testTeacherName(string name){
    bool ok;
    int i, tam;
    
    ok = true;
    i = 0;
    tam = name.length();
    while(i < tam && ok){
        if(name[i] != ' ' && isalpha(name[i]) == 0){
            ok = false;
        }
        else{
            i++;
        }
    }
    return ok;
}

int buscarTeacherByName(const vector<Teacher> &teachers, string name){
    int pos, i;
    pos = -1;
    for(i = 0; i < teachers.size() && pos == -1; i++){
        if(teachers[i].name == name){
            pos = i;
        }
    }   
    return pos;
}

string trip(string name){
    string tripi = "";
    int pi, pf, tam;
    pi = 0;
    tam = name.length();
    while(pi < tam && name[pi] == ' '){
        pi++;
    }
    pf = tam - 1;
    while(pf >= 0 && name[pf] == ' '){
        pf--;
    }
    tripi = name.substr(pi, pf - pi + 1);
    return tripi;
}

string superEficienteTrip(string name){
    string tripi = "";
    int pi, pf, i, tam;
    tam = name.length();
    i = 0;
    pi = pf = -1;
    while(i < name.length()){
        if(name[i] != ' '){
            if(pi == -1){
                pi = i;
            }
            if(i > pf){
                pf = i;
            }
        }
        else{
            i++;
        }
    }
    tripi = name.substr(pi, pf - pi);   
    return tripi;
}


string askTeacher(const vector<Teacher> &teachers){
    string name;
    int pos = -1;
    bool ok_name = false;
    do{
        cout << "Enter teacher name: ";
        getline(cin, name);
        if(name == ""){
            error(ERR_EMPTY);
        }
        else{
            ok_name = testTeacherName(name);
            if(!ok_name){
                error(ERR_NAME);
            }
            else{
                name = trip(name);
                if(name.length() < 3 || name.length() >= KMAXNAME){
                    error(ERR_NAME);
                    ok_name = false;
                }
                else{
                    pos = buscarTeacherByName(teachers, name);  
                    if(pos != -1){
                        error(ERR_DUPLICATED);
                    }
                }
            }
        }
    }while(name != "" && (!ok_name || pos != -1));
    return name;
}
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
/*
string code(string sp){
    string aux = "";
    char codigos[] = "TRWAGMYFPD";
    int i = 0;
    while(i < sp.length()){
        aux += codigos[sp[i] - '0'];
        i++;
    }
    return aux;
}*/

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
// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    data.nextId=1;
    char option;
    
    do{
        showMenu();
        cin >> option;
        cin.get();
        
        switch(option){
            case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                break;
            case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                break;
            case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
                break;
            case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}


