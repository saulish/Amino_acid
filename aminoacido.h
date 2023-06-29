#ifndef AMINOACIDO_H
#define AMINOACIDO_H
#include <iostream>
using namespace std;

class Aminoacido {
    public:
        //Constructores
        Aminoacido(const Aminoacido& otro) : nombre(otro.nombre){}
        Aminoacido() : nombre('-') {};
        Aminoacido(char t_nombre) : nombre(t_nombre) {};

        //Getters y Setters
        void set_nombre_Amino(char t_nombre){
            nombre = t_nombre;
        }
        char get_nombre_Amino(){
            return nombre;
        }

        //Sobrecarga de operadores
        friend ostream& operator<<(ostream& os, const Aminoacido& rhs) {
            /* os<<"Aminoacido: "<<rhs.nombre<<endl; */
            os<<rhs.nombre;
            return os;
        }
        Aminoacido& operator=(const Aminoacido& otro) {
            if (this != &otro){
                nombre = otro.nombre;
            }
            return *this;
        }
        Aminoacido & operator=(Aminoacido &&rhs){
            swap(nombre,rhs.nombre);
            return *this;
        }
        const char& recuperar() const {
            return nombre;
        }
/*         Aminoacido& operator=(Aminoacido&& otro) {
            if (this != &otro) {
                nombre = std::move(otro.nombre);    }
            return *this;
        } */
    private:
        char nombre;

   /*  friend class Proteinas; */
};





#endif

