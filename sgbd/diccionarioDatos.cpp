#include "diccionarioDatos.h"
#include <iostream>

diccionarioDatos::diccionarioDatos() {
    abrir();
    
}

int diccionarioDatos::createTablespace(tabla t, string nombre) {
    tablespace tsdf;
    tsdf.nombre = nombre;
    tsdf.ruta = nombre.append(".dbf");
    tsdf.tablas.push_front(t);
    tablespaces.push_front(tsdf);
}

int diccionarioDatos::abrir() {
    ifstream is;
    is.open("system.dbf");
    int tam = sb.deserializeInt(is);
    cout<<tam<<"<-Tam"<<endl;
    for(int i = 0; i < tam; i++) {
        tablespaces.push_front(abrirTablespace(is));
    }
    is.close();
}

tablespace diccionarioDatos::abrirTablespace(ifstream &is) {
    tablespace ts;
    ts.nombre = sb.deserializeString(is);
    ts.ruta = sb.deserializeString(is);
    int tam = sb.deserializeInt(is);
    for(int i = 0; i < tam; i++) {
        ts.tablas.push_front(abrirTabla(is));
    }
    return ts;
}

tabla diccionarioDatos::abrirTabla(ifstream &is) {
    tabla t;
    t.nombre = sb.deserializeString(is);
    t.bloqueInicial = sb.deserializeString(is);
    t.bloqueFinal = sb.deserializeString(is);
    int tam = sb.deserializeInt(is);
    for(int i = 0; i < tam; i++) {
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

int diccionarioDatos::guardar() {
    ofstream os;
    os.open("system.dbf");
    int tam = tablespaces.size();
    sb.serialize(os, tam);
    for (std::list<tablespace>::iterator it = tablespaces.begin(); it != tablespaces.end(); ++it) {
        guardarTablespace(os, *it);
    }
    os.close();
 }

int diccionarioDatos::guardarTablespace(ofstream &os, tablespace ts) {
    sb.serialize(os, ts.nombre);
    sb.serialize(os, ts.ruta);
    int tam = ts.tablas.size();
    sb.serialize(os, tam);
    for (std::list<tabla>::iterator it = ts.tablas.begin(); it != ts.tablas.end(); ++it){
        guardarTabla(os, *it);
    }
    return 1;
}

int diccionarioDatos::guardarTabla(ofstream &os, tabla t) {
    sb.serialize(os, t.nombre);
    sb.serialize(os, t.bloqueInicial);
    sb.serialize(os, t.bloqueFinal);
    int tam = t.columnas.size();
    sb.serialize(os, tam);
    for (std::list<columna>::iterator it = t.columnas.begin(); it != t.columnas.end(); ++it) {
        guardarColumna(os, *it);
    }
    return 1;
}

int diccionarioDatos::guardarColumna(ofstream &os, columna c) {
    sb.serialize(os, c.nombre);
    sb.serialize(os, c.tipo);
    return 1;
}


int diccionarioDatos::prueba() {
    tablespace ts;
    ts.nombre = "ts1";
    ts.ruta = "/file/...";
    tabla t;
    t.nombre = "nom";
    t.bloqueInicial = "213";
    t.bloqueFinal = "355";
    columna c;
    c.nombre = "nomCol";
    c.tipo = "varchar";
    t.columnas.push_front(c); 
    ts.tablas.push_front(t);
    tablespaces.push_front(ts);
    cout<<"prueba"<<endl;
}

int diccionarioDatos::agregarTabla(tabla t, string nombre = DEFAULT) {
    tablespace ts;
    for(std::list<tablespace>::iterator it = tablespaces.begin(); it != tablespaces.end(); ++it) {
        ts = *it;
        if(ts.nombre.compare(nombre)){
            ts.tablas.push_front(t);
        } else {
           createTablespace(t, nombre);           
        }
    }
}


string diccionarioDatos::toString() {
    stringstream ss;
    ss<< "nombre" <<tablespaces.front().tablas.front().columnas.front().tipo;
    return ss.str();
}