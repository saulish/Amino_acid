#ifndef BUSQUEDA__AMINO_H
#define BUSQUEDA__AMINO_H
#include <iostream>
#include "lista_d.h"
#include "aminoacido.h"
using namespace std;

int particion__amino(lista_d<Aminoacido> &lista, int left, int right){
    //Elegimos el pivote, es el primer valor de la lista
    Aminoacido piv = lista.peek_ps(left);
    int pivote = int(piv.get_nombre_Amino());

    //Ciclo infinito
    while(1){
        //Mientras cada elemento desde la izquierda esté en orden (sea menor que el pivote) continua avanzando el indice.
        /* objeto obj_left = lista[left];
        objeto obj_right = lista[right]; */

        while(lista.peek_ps(left).recuperar() < pivote){
            left++;
        }
        while(lista.peek_ps(right).recuperar() > pivote){
            right--;
        }

        /*
        Sí la izquierda es menor o igual que la derecha, significa que no necesitamos hacer ningun
        cambio de variables, pues los elementos ya están en orden (al menos en esta iteración)
        */

        if(left >= right){
            /*Indica que "en donde nos quedamos" para poder dividir el arreglo de nuevo
            y ordenar los demás elementos*/
            return right;
        }
        else{
            /*Sí las variables quedaron "lejos" (es decir, la izquierza no superó ni alcanzó
            a la derecha), significa que se detuvieron porque encontraron un valor que no estaba
            en orden, así que lo intercambiamos*/

            swap(lista[left], lista[right]);
            /* lista.change_nodo(left,right); */
            left++;
            right--;
        }
        //El while se repite hasya que izquierda >= derecha
    }
}


void quicksort__amino(lista_d<Aminoacido> &lista, int left, int right){
    if (left < right){
        int indiceParticion = particion__amino(lista, left, right);
        quicksort__amino(lista, left, indiceParticion);
        quicksort__amino(lista, indiceParticion + 1, right);
    }
}

int busqueda_binaria__amino(lista_d<Aminoacido> &lista, int _left, int _right, char _clave){
    /* _clave = int(_clave); */
    int _center = (_left+_right)/2;
    if(_left>_right){
        return -1;
    }
    if(lista[_center].get_nombre_Amino() == _clave){
        return _center;
    }
    else if (lista[_center].get_nombre_Amino() < _clave){
        _left = _center+1;
        busqueda_binaria__amino(lista, _left, _right, _clave);
    }
    else if (lista[_center].get_nombre_Amino()>_clave){
        _right = _center-1;
        busqueda_binaria__amino(lista, _left, _right, _clave);
    }

}

#endif
