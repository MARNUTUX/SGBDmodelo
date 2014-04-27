#include <stdlib.h>
#include <iostream>
#include "bdes.h"
#include "diccionarioDatos.h"

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

int bdes::compresor(string ts, diccionarioDatos& dd) {
    ofstream os;
    ifstream is;
    bloqueDato bd;
    string str = ts;
    str.append(".bak");
    os.open(str.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
    ts.append(".dbf");
    is.open(ts.c_str(), ios::in | ios::out | ios::binary);
    int pivoteV = 0;
    int posNx = 0;
    int gcount = 0;
    int inicio = -1;
    int fin = -1;
    list<pivote> lstPiv;
    do {
        size_t n = 0;
        is.read((char*) &n, sizeof (size_t));
        gcount = is.gcount();
        pivoteV = is.tellg();
        printf("pivote-->%d\n", pivoteV);
        if (gcount) {
            is.seekg(pivoteV - sizeof (size_t));
            bd = *deserializarBloque(is);
            if (bd.estado) {
                inicio = os.tellp();
                serializarBloque(os, bd, posNx);
                fin = os.tellp();
                pivote* p0 = 0;
                
                for (std::list<pivote>::iterator it = lstPiv.begin(); it != lstPiv.end(); ++it) {
                    if ((*it).tabla.compare(bd.tabla)) {
                        p0 = &(*it);
                    }
                }
                if (p0 != 0) {
                    int posAnterior = p0->pivote;
                    p0->pivote = bd.next;
                    modificarNext(DEFAULT, posAnterior, inicio);
                    dd.actualizaBloquesTabla(bd.tabla, inicio, inicio, 0);
                } else {
                    p0 = new pivote;
                    p0->pivote = bd.next;
                    p0->tabla = bd.tabla;
                    lstPiv.push_front(*p0);
                    dd.actualizaBloquesTabla(bd.tabla, inicio, inicio, 1);
                }

            }
        }
    } while (gcount);
    is.close();
    dd.miPivote = os.tellp();
    os.close();
    remove(ts.c_str());
    rename(str.c_str(), ts.c_str());
    dd.pivotes = lstPiv;
    cout << "\n\n\n---->pivotes--> " << dd.pivotes.front().pivote << endl;
}

int bdes::modificarNext(string ts, int& pos, int valor) {
    ofstream os;
    ts.append(".dbf");
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    os.seekp(pos);
    std::cout << "modificarNext ---> " << valor << std::endl;
    os.write(reinterpret_cast<char*> (&valor), sizeof (int));
    os.close();
}

int bdes::borrador(string ts, int pos) {
    ts.append(".dbf");
    cout << "POOSS --->     " << pos << endl;
    pos += getPosEstado(ts, pos);
    ofstream os;
    os.open(ts.c_str(), ios::in | ios::out | ios::binary);
    cout << "POOSS --->     " << pos << endl;
    os.seekp(pos);
    sb.serialize(os, 0);
    os.close();
    // cambiar el next anterior
}

int bdes::serializarBloque(ofstream& os, bloqueDato& bd, int& posNx) {
    sb.serialize(os, bd.tabla);
    sb.serialize(os, bd.estado);
    posNx = os.tellp();
    os.write(reinterpret_cast<char*> (&bd.next), sizeof (int));
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
    is.read(reinterpret_cast<char*> (&nx), sizeof (int));
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
    cout << "getPosEstado" << pos << endl;
    return pos;
}





