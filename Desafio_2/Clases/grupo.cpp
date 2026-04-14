#include "grupo.h"

Grupo::Grupo() {}

Grupo::~Grupo(){
    if (this->equipos != nullptr) delete[] this->equipos;
}
