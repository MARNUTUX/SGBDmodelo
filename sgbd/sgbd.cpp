#include "sgbd.h"


int sgbd::creador(tabla t, string nombretablespace) {
    dd.agregarTabla(t, nombretablespace);
}
/*
int sgbd::insertor(tabla t, list<dato> lst, int estado, int next = -1) {
    bloqueDato bd;
    bd.tabla = t;
    bd.datos = lst;
    bd.estado = estado;
    bd.next = next;
}*/

