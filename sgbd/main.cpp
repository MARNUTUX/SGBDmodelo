
#include "sgbd.h"
#include "bdes.h"

using namespace std;

int ayuda() {
    cout << "Las operaciones basicas son create, insert, delete, select, update, compress" << endl;
    cout << "Algunos Ejemplos" << endl;
    cout << "create table t3 ( x int,y varchar[5],z int );" << endl;
    cout << "insert into t3 values( 0,dfggf,33 );" << endl;
    cout << "delete from t1 where a=x or y=1;" << endl;
    cout << "select * from t3 where a=1 and x=qwerty or h5=h1;" << endl;
    cout << "update t1 set a=b,c=1 where a=z and h=1;" << endl;
    cout << "¡Se debe de tener cuidado con espacios!" << endl;
    cin.get();
}

int menu() {
    sgbd sg = sgbd();
    cout << "Bienvenido al sdbd. Digite la sentencias que desea." << endl;
    cout << "Digite help o h para ayuda" << endl;
    while (1) {
        string entrada;
        cout << "> ";
        cin >> entrada;
        if (entrada.compare("exit") == 0 || entrada.compare("quit") == 0 ||
                entrada.compare("q") == 0) {
            return 1;
        } else if (entrada.compare("help") == 0 || entrada.compare("h") == 0) {
            ayuda();
        } else if (entrada.compare("compress") == 0) {
            sg.comprimir();
        }
        if (sg.reconocedor(entrada)) {
            cout << ">";
        } else {
            cout << "sentencia desconocida" << endl;
        }
    }
}

int prueba() {
    //    remove("default.dbf");
    //    remove("system.dbf");
    sgbd sg = sgbd();
//    sg.reconocedor("create table t3 ( x int,y varchar[5],z int );");
    //    sg.reconocedor("create table t2 ( x int,z int );");
    //sg.reconocedor("insert into t3 values( 0,dfggf,33 );");
    //    sg.reconocedor("insert into t2 values( 0,33 );");
    //sg.reconocedor("insert into t3 values( 1,a,2 );");
    //sg.reconocedor("insert into t3 values( 2,C,3 );");
    //sg.reconocedor("insert into t3 values( 3,D,4 );");
    //////////////    ////            sg.reconocedor("delete from t3 where a=x or y=1;");
    //////////////    //    //sg.reconocedor("select * from t3 where a=1 and x=qwerty or h5=h1;");
    //////////////    
    //    sg.reconocedor("delete from t2 where a=x or y=1;");
    //    sg.comprimir();

    //sg.reconocedor("select * from t3 where a=1 and x=qwerty or h5=h1;");
    sg.reconocedor("update t3 set a=b,c=1 where a=z and h=1;");
    //sg.reconocedor("select * from t3 where a=1 and x=qwerty or h5=h1;");
}

int main() {
    //  menu();
    prueba();
    //cout<<"holamundo"<<endl;
    return 1;
}