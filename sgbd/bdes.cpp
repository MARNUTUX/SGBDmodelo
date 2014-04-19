#include <stdlib.h>

#include "bdes.h"


bdes::bdes() {
    
}

bdes::~bdes() {
    
}

bloqueDato* getBloque() {
    bloqueDato* bd = new bloqueDato;
    bd->tabla = "tabla0";
    bd->estado = 1;
    bd->next = 0;
    dato d;
    d.nombreColumna = "c0";
    d.tipoDato = "int";
    d.valor = "3";
    bd->datos.push_front(d);
    return bd;
}

int bdes::escritor() {
    ofstream os;
    os.open("prueba.dat", ios::trunc);
    serializarBloque(os, getBloque());
    os.close();
    printf("escrito!!!\n");
           
}

int bdes::lector() {
    ifstream is;
    is.open("prueba.dat", ios::in | ios::out | ios::binary);
    deserializarBloque(is);
    is.close();
}

int bdes::serializarBloque(ofstream& os, bloqueDato* bd) {
    sb.serialize(os, bd->tabla);
    sb.serialize(os, bd->estado);
    sb.serialize(os, bd->next); //get pos
    int tam = bd->datos.size();
    os.tellp();
    sb.serialize(os, tam);
    for(std::list<dato>::iterator it = bd->datos.begin(); it != bd->datos.end(); ++it)
        serializarDato(os, *it);
}

int bdes::serializarDato(ofstream& os, dato d) {
    sb.serialize(os, d.nombreColumna);
    sb.serialize(os, d.tipoDato);
    sb.serialize(os, d.valor);
}

bloqueDato* bdes::deserializarBloque(ifstream& is) {
    bloqueDato* bd = new bloqueDato;
    bd->tabla = sb.deserializeString(is);
    bd->estado = sb.deserializeInt(is);
    bd->next = sb.deserializeInt(is);
    int tam = deserializeInt(is);
    for(int i = 0; i < tam; i++)
        bd->datos.push_front(deserializarDato(is));
    return bd;
}

dato bdes::deserializarDato(ifstream& is) {
    dato d;
    d.nombreColumna = sb.deserializeString(is);
    printf("tabla-->%s\n", d.nombreColumna.c_str());
    d.tipoDato = sb.deserializeString(is);
    d.valor = sb.deserializeString(is);
    return d;
}



