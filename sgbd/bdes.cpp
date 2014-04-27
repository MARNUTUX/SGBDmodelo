#include <stdlib.h>
#include <iostream>
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
    bd.posInicial = pos;
    bd = *deserializarBloque(is);
    bd.posFinal = is.tellg();
    is.close();
}

int bdes::grabador(string ts, bloqueDato bd, int pos) { //bug con tamaño diferente
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    int posNx;
    serializarBloque(os, bd, posNx);
    os.close();

}

int bdes::validador(string ts, int pos) {
    ts.append(".dbf");
    int valido;
    ifstream is;
    is.seekg(getPosEstado(ts, pos));
    valido = sb.deserializeInt(is);
    is.close();
    return valido;
}

int bdes::compresor(string ts) {
    ofstream os;
    ifstream is;
    bloqueDato bd;
    string str = ts;
    str.append(".bak");
    os.open(str.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
    ts.append(".dbf");
    is.open(ts.c_str(), ios::in | ios::out | ios::binary);
    int pivote = 0;
    int posNx = 0;
    int gcount = 0;
    do {
        size_t n = 0;
        is.read((char*) &n, sizeof (size_t));
        gcount = is.gcount();
        pivote = is.tellg();
        printf("pivote-->%d\n", pivote);
        if (gcount) {
            is.seekg(pivote-sizeof(size_t));
            bd = *deserializarBloque(is);
 //           printf("ser--->%s\n", bd.datos.front());
            if(bd.estado){
                serializarBloque(os, bd, posNx);
            }
        }
    } while (gcount);
    is.close();
    os.close();
    remove(ts.c_str());
    rename(str.c_str(), ts.c_str());
}

int bdes::modificarNext(string ts, int& pos, int valor) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    std::cout<<"modificarNext ---> "<<valor<<std::endl;
    os.write(reinterpret_cast<char*>(&valor), sizeof(int));
    os.close();
}

int bdes::borrador(string ts, int pos) {
    ts.append(".dbf");
    pos = getPosEstado(ts, pos);
    ofstream os;
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    sb.serialize(os, 0);
    os.close();
    // cambiar el next anterior
}

int bdes::serializarBloque(ofstream& os, bloqueDato& bd, int& posNx) {
    sb.serialize(os, bd.tabla);
    sb.serialize(os, bd.estado);
    posNx = os.tellp();
    os.write(reinterpret_cast<char*>(&bd.next), sizeof(int));
    int tam = bd.datos.size();
    sb.serialize(os, tam);
    for (std::list<string>::iterator it = bd.datos.begin(); it != bd.datos.end(); ++it)
        serialize(os, *it);
}



bloqueDato* bdes::deserializarBloque(ifstream& is) {
    bloqueDato* bd = new bloqueDato;
    bd->tabla = sb.deserializeString(is);
    bd->estado = sb.deserializeInt(is);
    int nx = -2;
    is.read(reinterpret_cast<char*>(&nx), sizeof(int));
    bd->next = nx;
    //bd->next = sb.deserializeInt(is);
    int tam = deserializeInt(is);
    for (int i = 0; i < tam; i++)
        bd->datos.push_front(deserializeString(is));
    return bd;
}


int bdes::getPosEstado(string nom, int pos) {
    ifstream is;
    is.open(nom.c_str(), ios::in | ios::out | ios::binary);
    size_t n = 0;
    is.seekg(pos);
    is.read((char*) &n, sizeof (size_t));
    int tam = n;
    pos = tam + sizeof (size_t);
    is.close();
    return pos;
}





