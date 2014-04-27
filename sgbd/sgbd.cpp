#include "sgbd.h"

sgbd::sgbd() {
    this->parser = Parser();
}

int sgbd::creador(tabla t, string nombretablespace) {
    dd.agregarTabla(t, nombretablespace);
}

int sgbd::validaInsertor(string cadena) {
    if (parser.insertando(cadena)) {
        cout << cadena << endl;
        splitstring s(cadena);
        vector<string> ss = s.split(' ');
        //        for (int k = 0; k < ss.size(); k++)
        //            cout << k << " => " << ss[k] << endl;
        return 1;
    } else
        return 0;
}

int sgbd::validaSeleccionador(string cadena) {
    if (parser.selecteando(cadena)) {
        cout << cadena << endl;
        splitstring s(cadena);
        vector<string> ss = s.split(' ');
        //for (int k = 0; k < ss.size(); k++)
        //    cout << k << " => " << ss[k] << endl;
        return 1;
    } else
        return 0;
}

int sgbd::validaActualizador(string cadena) {
    if (parser.actualizando(cadena)) {
        cout << cadena << endl;
        splitstring s(cadena);
        vector<string> ss = s.split(' ');
        for (int k = 0; k < ss.size(); k++)
            cout << k << " => " << ss[k] << endl;
        return 1;
    } else
        return 0;
}

int sgbd::validaBorrador(string cadena) {
    if (parser.borrando(cadena)) {
        cout << cadena << endl;
        splitstring s(cadena);
        vector<string> ss = s.split(' ');
        for (int k = 0; k < ss.size(); k++)
            cout << k << " => " << ss[k] << endl;
        return 1;
    } else
        return 0;
}

int sgbd::creador(string cadena) {
    if (parser.creando(cadena)) {
        cout << cadena << endl;
        splitstring s(cadena);
        vector<string> ss = s.split(' ');
        for (int k = 0; k < ss.size(); k++)
            cout << k << " => " << ss[k] << endl;
        return 1;
    } else
        return 0;
}

bool sgbd::reconocedor(string cadena) {
    vector<string> ss = separador(cadena, ' ');
    vector<string> ss0;
    vector<string> ss1;
    if (ss[0] == "insert") {
        if (validaInsertor(cadena)) {
            if (insertor(ss))
                cout << "insertado bien" << endl;
            else
                cout << "error al insertar" << endl;
        } else return false;
    } else if (ss[0] == "select") {
        if (this->validaSeleccionador(cadena)) {
            if (seleccionador(ss)) {
                cout << "seleccionado" << endl;
            } else {
                cerr << "error" << endl;
            }
        } else return false;
    } else if (ss[0] == "delete") {
        if (validaBorrador(cadena)) {

        } else return false;
    } else if (ss[0] == "update") {
        //ss[1] tiene el nombre de la tabla a actualizar
        if (validaActualizador(cadena)) {

        } else return false;
    } else if (ss[0] == "create") {
        if (creador(cadena)) {
            //ss[2] posee el nombre de la tabla a crear
            //ss0 = separador(ss[3], ','); 
            ss1 = separador(cadena, '(');
            vector<string> ss2 = separador(ss1[1], ')');
            vector<string> ss3 = separador(ss2[0], ',');
            //for (int i = 0; i < ss3.size(); i++)
            //cout << ss3[i] + "\n";
            list<columna> colist;
            vector<string> values;
            for (int i = 0; i < ss3.size(); i++) {
                if (!values.empty())values.clear();
                values = separador(ss3[i], ' ');
                colist.push_front(creaCol(values[0], values[1]));

            }
            creaTabla(ss[2], colist);
            cout << "lo hizo\n";
            return true;
        } else return false;
    }
}

vector<string> sgbd::separador(string cadena, char val) {
    splitstring s(cadena);
    return s.split(val);
}

int sgbd::creaTabla(string nombre, list<columna> colist) {
    tabla tab;
    tab.nombre = nombre;
    tab.bloqueFinal = -1;
    tab.bloqueInicial = -1;
    tab.columnas = colist;
    if (dd.agregarTabla(tab, DEFAULT))
        return 1;
    else
        return 0;
}

columna sgbd::creaCol(string nombre, string tipo) {
    columna col;
    col.nombre = nombre;
    col.tipo = tipo;
    return col;
}

bool sgbd::validaNumeros(string cadena) {
    if (cadena == "0")return true;
    if (atoi(cadena.c_str()) == 0)return false;
    else return true;
}


// operaciones basicas

int sgbd::insertor(vector<string> ss) {
    vector<string> values;
    values = separador(ss[4], ',');
    string nombre = ss[2];
    bloqueDato bd;
    tabla t;
    int cont = 0;
    if (dd.existeTabla(nombre, t)) {
        columna c0;
        int tam0 = t.columnas.size();
        int tam1 = values.size();
        if (tam0 == tam1) {
            for (std::list<columna>::iterator it = t.columnas.begin(); it != t.columnas.end(); ++it) {
                c0 = *it;
                //cout << "c0" << c0.nombre << endl;
                if (c0.tipo == "int" || c0.tipo == "integer") {
                    if (!validaNumeros(values[cont]))
                        return 0;
                    //cout << "integer" << endl;
                }
                bd.datos.push_front(values[cont]);
                cont++;
            }
            bd.tabla = nombre;
            bd.estado = 1;
            bd.next = -1;
            bd.posFinal = -1;
            bd.posInicial = -1;
            int next;
            int posInicial;
            int posFinal;
            int posEscribe = dd.miPivote;
            bdess.escritor(DEFAULT, bd, next, posInicial, posFinal, posEscribe);
            dd.miPivote = posFinal;
            pivote *p0;
            dd.actualizaBloquesTabla(t.nombre, posInicial, posInicial);
            p0 = dd.getPivote(nombre);

            if (p0 != 0) {
                cout << "posPivote................>> " << p0->pivote << endl;
                int posAnterior = p0->pivote;
                p0->pivote = posInicial;
                cout << "posPivote................>> " << p0->pivote << endl;
                bdess.modificarNext(DEFAULT, posAnterior, p0->pivote);
            } else {
                p0 = new pivote;
                p0->pivote = next;
                cout << "posPivote................>> " << p0->pivote << endl;
                p0->tabla = nombre;
                dd.pivotes.push_front(*p0);
            }

        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}

int sgbd::seleccionador(vector<string> ss) {
    vector<string> ss0;
    vector<string> ss1;
    vector<string> whereValues;
    string nombre = ss[3];
    ss0 = separador(ss[1], ',');
    // cout << "nombre --> " << nombre << endl;
    tabla t;
    list<bloqueDato> bloquesSelec; //lista devuelve lista bloques
    if (dd.existeTabla(nombre, t)) {
        if (ss[1].compare("*") == 0) {
            bloqueDato bd;
            int next = t.bloqueInicial;
            do {
                cout << "bd.next" << bd.next << endl;
                bdess.lector(DEFAULT, next, bd);
                cout << "bd.nombre" << bd.tabla << endl;
                for (std::list<string>::iterator it = bd.datos.begin(); it != bd.datos.end(); ++it) {
                    cout<<(*it)<<endl;
                }
                cout << "bd.c0" << bd.datos.front() << endl;
                bloquesSelec.push_front(bd);

                next = bd.next;
            } while (bd.next != -1);
            lstBloques = bloquesSelec;
        } else {
            cout << "no *" << ss[1] << endl;
        }
    } else {
        return 0;
    }

    //ss0 tiene los valores que se desean seleccionar, puede que solo sea "*" - todos los valores de la tabla-
    //for (int i = 0; i < ss0.size(); i++)
    //    cout << ss0[i] + "\n";
    /*vector<string> vstr;
    if (ss.size() > 4) {
        //en dado caso que tuviera where la sentencia
        for (int i = 5; i < ss.size(); i += 2) {
            ss1.push_back(ss[i]);
            cout << "ss[i] --> " << ss[i] << endl;
            vstr = separador(ss[i], '=');
            for (int j = 0; vstr.size(); j++) {
                whereValues.push_back(vstr[j]);
                cout << "wv[i] --> " << vstr[j] << endl;
            }
        }
        cout << "size --->" << ss1.size() << endl;
        //ss1 tiene los valores del where (sin ands y ors)
    }*/
    return 1;

}

int sgbd::borrador(vector<string> ss) {
    seleccionador(ss);
    for (std::list<bloqueDato>::iterator it = lstBloques.begin(); it != lstBloques.end(); ++it) {
        bdess.borrador((*it).tabla, (*it).posInicial);
    }
}

int sgbd::actualizador(vector<string> ss) {

}

int sgbd::comprimir() {
    bdess.compresor(DEFAULT, dd);
}

// utiles

