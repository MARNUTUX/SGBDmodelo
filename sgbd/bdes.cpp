#include <stdlib.h>

#include "bdes.h"

bdes::bdes() {

}

bdes::~bdes() {

}

int bdes::escritor(string ts, bloqueDato& bd, int& posNx, int& posInicial, int& posFinal, int& posType) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    if (!os.good())
        os.open(ts.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
    os.seekp(posType);
    posInicial = os.tellp();
    serializarBloque(os, bd, posNx);
    posFinal = os.tellp();
    os.close();
}


// para select * from x -> lector(ts, pos = next anterior)
// para cargar todas las tablas lector(ts, bd.posFinal)
int bdes::lector(string ts, int pos, bloqueDato& bd) {
    ifstream is;
    ts.append(".dbf");
    is.open(ts.c_str(), ios::in | ios::out | ios::binary);
    is.seekg(pos);
    bd = *deserializarBloque(is);
    is.close();
}

int bdes::grabador(string ts, bloqueDato *bd, int* pos) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    int posNx;
    serializarBloque(os, bd, posNx);
    os.close();
    
}

int bdes::modificarNext(string ts, int& pos, int valor) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    sb.serialize(os, valor);
    os.close();
}

int bdes::borrador(string ts, int pos) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    sb.serialize(os, 0);
    os.close();
}

int bdes::serializarBloque(ofstream& os, bloqueDato& bd, int& posNx) {
    sb.serialize(os, bd.tabla);
    sb.serialize(os, bd.estado);
    sb.serialize(os, bd.next); //get pos
    int tam = bd.datos.size();
    posNx = os.tellp();
    sb.serialize(os, tam);
    for (std::list<dato>::iterator it = bd.datos.begin(); it != bd.datos.end(); ++it)
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
    for (int i = 0; i < tam; i++)
        bd->datos.push_front(deserializarDato(is));
    return bd;
}

dato bdes::deserializarDato(ifstream& is) {
    dato d;
    d.nombreColumna = sb.deserializeString(is);
    d.tipoDato = sb.deserializeString(is);
    d.valor = sb.deserializeString(is);
    return d;
}



