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


