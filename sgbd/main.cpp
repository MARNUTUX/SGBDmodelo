
#include "bdes.h"
using namespace std;

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

int pruebaBdes() {
    bdes es; // = new bdes("pruebaDbf.dbf");
    string ts = "ts0";
    int pos = -1;
    int posInicial = -1;
    int posFinal = 0;
    //es.escritor(ts, *getBloque(), pos, posInicial, posFinal, posFinal);
    //es.escritor(ts, *getBloque(), pos, posInicial, posFinal, posFinal);
    printf("pos--> %d \n", pos);
    printf("posInicial--> %d \n", posInicial);
    printf("posFinal--> %d \n", posFinal);
    bloqueDato bd;
    es.lector(ts, 50, bd);
    printf("nombre tabla --> %s\n", bd.tabla.c_str());
    //    delete es;
}

int main() {
    pruebaBdes();

}