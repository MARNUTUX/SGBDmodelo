#include "sgbd.h"

int sgbd::creador(tabla t, string nombretablespace) {
    dd.agregarTabla(t, nombretablespace);
}

