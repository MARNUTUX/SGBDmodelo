
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
//    es.escritor(ts, *getBloque(), pos, posInicial, posFinal, posFinal);
//    es.escritor(ts, *getBloque(), pos, posInicial, posFinal, posFinal);
    /*printf("pos--> %d \n", pos);
    printf("posInicial--> %d \n", posInicial);
    printf("posFinal--> %d \n", posFinal);*/
    bloqueDato bd;
    //es.lector(ts, 50, bd);
    //printf("nombre tabla --> %s\n", bd.datos.front().nombreColumna.c_str());
    /* bd.tabla = "t1";
     es.grabador(ts, bd, 0);
     es.lector(ts, 0, bd);
     printf("nombre tabla --> %s\n", bd.tabla.c_str());*/
    //    delete es;
//    //es.borrador(ts, 0);
//    es.lector(ts, 0, bd);
//    printf("nombre tabla --> %d\n", bd.estado);  
    
    //es.lector(ts, )
    es.compresor(ts);
}

int main() {
    pruebaBdes();

}