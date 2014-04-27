#include "diccionarioDatos.h"
#include <iostream>
#include <vector>

diccionarioDatos::diccionarioDatos() {
    abrir();

}

diccionarioDatos::~diccionarioDatos() {
    guardar();
    cout << "ya guarde :)))))))" << endl;
}

/*tablespace diccionarioDatos::createTablespace(string nombre) {
    tablespace tsdf;
    tsdf.nombre = nombre;
    tsdf.ruta = nombre.append(".dbf");
    tablespaces.push_front(tsdf);
    return tsdf;
}*/

int diccionarioDatos::abrir() {
    cout << "Abriendo el archivos" << endl;
    ifstream is;
    is.open("system.dbf");
    if (is.good()) {
        int tam = sb.deserializeInt(is);
        cout << tam << "<-Tam" << endl;
        for (int i = 0; i < tam; i++) {
            tablespaces.push_front(abrirTablespace(is));
        }
        pivotes = abrirPrivotes(is);
        miPivote = sb.deserializeInt(is);

    } else {
        tablespace ts;
        ts.nombre = DEFAULT;
        ts.ruta.append(".dbf");
        tablespaces.push_front(ts);
        miPivote = 0;
    }
    is.close();
}

int diccionarioDatos::guardar() {
    ofstream os;
    os.open("system.dbf");
    int tam = tablespaces.size();
    sb.serialize(os, tam);
    //cout << "estoy guardeando" << endl;
    //cout << "\n\n\n\n\ntam ----------->  " << tam;
    for (std::list<tablespace>::iterator it = tablespaces.begin(); it != tablespaces.end(); ++it) {
        guardarTablespace(os, *it);
        //cout << "estoy guardeando" << endl;
    }
    guardarPivotes(os);
    sb.serialize(os, miPivote);
    os.close();
}

tablespace diccionarioDatos::abrirTablespace(ifstream &is) {
    tablespace ts;
    ts.nombre = sb.deserializeString(is);
    ts.ruta = sb.deserializeString(is);
    int tam = sb.deserializeInt(is);
    for (int i = 0; i < tam; i++) {
        ts.tablas.push_front(abrirTabla(is));
    }
    return ts;
}

tabla diccionarioDatos::abrirTabla(ifstream &is) {
    tabla t;
    t.nombre = sb.deserializeString(is);
    //cout << "Tablas levantadas-------------------------------- ->" << t.nombre << endl;
    t.bloqueInicial = sb.deserializeInt(is);
    t.bloqueFinal = sb.deserializeInt(is);
    int tam = sb.deserializeInt(is);
    for (int i = 0; i < tam; i++) {
        t.columnas.push_front(abrirColumna(is));
    }
    return t;
}

columna diccionarioDatos::abrirColumna(ifstream &is) {
    columna c;
    c.nombre = sb.deserializeString(is);
    c.tipo = sb.deserializeString(is);
    return c;
}

list<pivote> diccionarioDatos::abrirPrivotes(ifstream& is) {
    list<pivote> lst;
    int tam = sb.deserializeInt(is);
    for (int i = 0; i < tam; i++) {
        lst.push_front(abrirPivote(is));
    }
    return lst;
}

pivote diccionarioDatos::abrirPivote(ifstream& is) {
    pivote p0;
    p0.tabla = sb.deserializeString(is);
    p0.pivote = sb.deserializeInt(is);
    return p0;
}

int diccionarioDatos::guardarTablespace(ofstream &os, tablespace ts) {
    sb.serialize(os, ts.nombre);
    sb.serialize(os, ts.ruta);
    int tam = ts.tablas.size();
    sb.serialize(os, tam);
    //cout << "\n\n\nTAMtam...--->" << tam << endl;
    for (std::list<tabla>::iterator it = ts.tablas.begin(); it != ts.tablas.end(); ++it) {
        guardarTabla(os, *it);
        //cout << "estoy guardeando" << endl;
    }
    return 1;
}

int diccionarioDatos::guardarTabla(ofstream &os, tabla t) {
    sb.serialize(os, t.nombre);
    sb.serialize(os, t.bloqueInicial);
    sb.serialize(os, t.bloqueFinal);
    int tam = t.columnas.size();
    sb.serialize(os, tam);
    //cout << "guardandoTabla" << endl;
    for (std::list<columna>::iterator it = t.columnas.begin(); it != t.columnas.end(); ++it) {
        guardarColumna(os, *it);
    }
    return 1;
}

int diccionarioDatos::guardarColumna(ofstream &os, columna c) {
    sb.serialize(os, c.nombre);
    sb.serialize(os, c.tipo);
    //cout << "estoy guardeando------------------------->" << c.nombre << endl;
    return 1;
}

int diccionarioDatos::guardarPivotes(ofstream& os) {
    int tam = pivotes.size();
    sb.serialize(os, tam);
    for (std::list<pivote>::iterator it = pivotes.begin(); it != pivotes.end(); ++it) {
        guardarPivote(os, *it);
    }
}

int diccionarioDatos::guardarPivote(ofstream& os, pivote p) {
    sb.serialize(os, p.tabla);
    sb.serialize(os, p.pivote);
}

int diccionarioDatos::agregarTabla(tabla t, string nombre = DEFAULT) {
    if (existeTabla(t.nombre, t) == 0) {
        tablespaces.front().tablas.push_front(t);
        //cout<<"------------->"<<t.nombre<<endl;
        //guardar();
        return 1;
    } else {
        return 0;
    }

}

tablespace* diccionarioDatos::existeTablespace(string tsP) { //***¡!***
    tablespace* ts = 0;
    tablespace tsV;
    //cout << "existeTablespace" << endl;
    for (std::list<tablespace>::iterator it = tablespaces.begin(); it != tablespaces.end(); ++it) {
        tsV = *it;
        if (tsV.nombre.compare(tsP) == 0) {
            //cout << "lllegggoooo" << endl;
            ts = &tsV;
        }
    }
    return ts;
}

string diccionarioDatos::toString() {
    stringstream ss;
    ss << "nombre" << tablespaces.front().tablas.front().columnas.front().tipo;
    return ss.str();
}

int diccionarioDatos::existeTabla(string s, tabla& tP) {
    int existe = 0;
    tablespace ts;
    tabla t0;
    for (std::list<tablespace>::iterator it0 = tablespaces.begin(); it0 != tablespaces.end(); ++it0) {
        ts = *it0;
        for (std::list<tabla>::iterator it = ts.tablas.begin(); it != ts.tablas.end(); ++it) {
            t0 = *it;
            //cout<<"Tp.nombre--->"<<s<<endl;
            if (t0.nombre.compare(s) == 0) {
                existe = 1;
                tP = t0;
                //cout << "encontro ihgjhg" << endl;
            }
        }
    }
    return existe;
}

int diccionarioDatos::actualizaBloquesTabla(string s, int inicio, int final) {
    int existe = 0;
    tablespace ts;
    tabla t0;
    for (std::list<tablespace>::iterator it0 = tablespaces.begin(); it0 != tablespaces.end(); ++it0) {
        for (std::list<tabla>::iterator it = (*it0).tablas.begin(); it != (*it0).tablas.end(); ++it) {
            t0 = *it;
            if (t0.nombre.compare(s) == 0) {
                //cout << "HALLADO111!!!!!!!!!!!!!!!!!!!" << endl;
                if ((*it).bloqueInicial == -1) {
                    (*it).bloqueInicial = inicio;
                }
                (*it).bloqueFinal = final;
                existe = 1;
            }
        }
    }
    return existe;
}

pivote* diccionarioDatos::getPivote(string nomTabla) {
    pivote* p0 = 0;
    for(std::list<pivote>::iterator it = pivotes.begin(); it != pivotes.end(); ++it) {
        if((*it).tabla.compare(nomTabla) == 0) {
            p0 = &(*it);
        }
    }
    return p0;
}
