#include <iostream>
#include "lista_d.h"
#include "aminoacido.h"
#include "proteina.h"
#include "busqueda__amino.h"
#include <limits>
#include <clocale>
using namespace std;




void imprimir_lista(lista_d<Proteina> &lista){
   cout<<lista;
}

void nuevo_nombre_p(lista_d<Proteina> &lista, Proteina p, int ps){
    string t_nombre;
    cout<<"Ahora ingresa el nuevo nombre: "<<endl;
    cin>>t_nombre;
    p.set_nombre_proteina(t_nombre);
    cout<<p;
    cout<<"ps: "<<ps<<endl;
    cout<<"tamanio: "<<lista.r_tamanio()<<endl;
    lista.delete_ps(ps);
    lista.push_ps(ps, p);


}
void menu_push(lista_d<Proteina> &lista, Proteina p) {
    int opc;
    cout<<"Tu proteina es: "<<endl<<p;
    if(lista.vacia()){
        cout<<"La lista esta vacia, por lo tanto no importa la posicion"<<endl;
        lista.push_f(p);
        return;
    }
    cout<<"En que parte de la lista deseas ingresar tu proteina?"<<endl;
    cout<<"[1]En el frente"<<endl;
    cout<<"[2]En el final"<<endl;
    cout<<"[3]En posicion"<<endl;
    fflush;
    do{
        cout<<"ingresa una opcion valida"<<endl;
        cin>>opc;
    }while(opc<0||opc>3);
    switch(opc){
    case 1:
        lista.push_f(p);
        break;
    case 2:
        lista.push_b(p);
        break;
    case 3:
        int ps;

        do{
            cout<<"Ingresa una posicion valida"<<endl;
            cin>>ps;

        }while(ps<0||ps>(lista.r_tamanio()-1));
        lista.push_ps(ps,p);
        break;
    }

}
void limpiar_pantalla()
    {
    #ifdef _WIN32
    #define CLEAR "cls"
    #elif defined(unix)  defined(unix)  defined(APPLE) || defined(MACH)
    #define CLEAR "clear"
    #else
    #error "SO no soportado para limpiar pantalla easter egg el rivas es el Macho alfa"
    #endif
        system(CLEAR);
    }



int particion__prote(lista_d<Proteina> &lista, int left, int right){
    //Elegimos el pivote, es el primer valor de la lista
    Proteina piv = lista[left];
    int pivote = piv.secuencia_tamanio();


    //Ciclo infinito
    while(1){
        //Mientras cada elemento desde la izquierda esté en orden (sea menor que el pivote) continua avanzando el indice.
        /* objeto obj_left = lista[left];
        objeto obj_right = lista[right]; */

        while(lista[left].secuencia_tamanio() < pivote){
            left++;
        }
        while(lista[right].secuencia_tamanio() > pivote){
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
        //El while se repite hasta que izquierda >= derecha
    }
}

void quicksort__prote(lista_d<Proteina> &lista, int left, int right){/////////////
    if (left < right){
        int indiceParticion = particion__prote(lista, left, right);
        quicksort__prote(lista, left, indiceParticion);
        quicksort__prote(lista, indiceParticion + 1, right);
    }
}

int busqueda_binaria(int _array[], int _left, int _right, int _clave){

    int _center = (_left+_right)/2;
    if(_left>_right){
        return -1;
    }
    if(_array[_center] == _clave){
        return _center;
    }
    else if (_array[_center] < _clave){
        _left = _center+1;
        busqueda_binaria(_array, _left, _right, _clave);
    }
    else if (_array[_center]>_clave){
        _right = _center-1;
        busqueda_binaria(_array, _left, _right, _clave);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
void buscarAmino(Proteina p){
    char valor;
    cout<<"Cual Aminoacido desea buscar?: ";
    cin>>valor;

    lista_d<Aminoacido> aminoT = p.getSecuencia();
    quicksort__amino(aminoT,0,aminoT.getTamanio()-1);

    int valor_returned = busqueda_binaria__amino(aminoT, 0, aminoT.getTamanio()-1, valor);
    if(valor_returned == -1){
        cout<<"El valor no se encuentra en la lista"<<endl;
    }
    else{
        cout<<"Si se encontro el valor de la lista: "<<aminoT[valor_returned].recuperar()<<endl;
    }
    aminoT.~lista_d();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int buscar(Proteina p){//Busqueda que se encarga de pedir un nombre de aminoacido y regresar su posicion al iterar

    char t_name;
    int menu = 0;
    Aminoacido t_a;
    cout << p;

    do {
        cout << "Ingresa el aminoacido que desees: ";
        cin >> t_name;

        for (int i = 0; i < p.secuencia_tamanio(); i++) {
            t_a = p.peek_ps_amino(i);
            if (t_a.get_nombre_Amino() == t_name) {
                menu = 1;
                return i;
            }
        }
        if (menu == 0) {
            cout << "No se encontro un aminoacido con ese nombre" << endl;
        }
    } while (menu == 0);


}

void ordenar_lista(lista_d<Proteina> &lista){
    quicksort__prote(lista, 0, (lista.r_tamanio()-1));
    cout<<lista;

}


int busqueda_binaria__prote(lista_d<Proteina> &lista, int _left, int _right, int _clave){

    int _center = (_left + _right) / 2;
    if(_left>_right){
        return -1;
    }
    if(lista[_center].secuencia_tamanio() == _clave){
        return (_center);
    }
    else if(lista[_left].secuencia_tamanio() == _clave){
        return (_left);
    }
    else if(lista[_right].secuencia_tamanio() == _clave){
        return (_right);
    }
    else if (lista[_center].secuencia_tamanio() > _clave){
        _left = _center+1;
        return busqueda_binaria__prote(lista, _left, _right, _clave);
    }
    else if (lista[_center].secuencia_tamanio()<_clave){

        _right = _center-1;
        return busqueda_binaria__prote(lista, _left, _right, _clave);
    }
}

int buscar(lista_d<Proteina>& lista){//Busqueda que se encarga de pedir un nombre de proteina y regresar su posicion al iterar
    int aminos,ps;
    lista_d<Proteina> lista_copia;
    lista_copia=lista;
    quicksort__prote(lista_copia, 0,(lista_copia.r_tamanio()-1));
    do {
        cout << "Ingresa la cantidad de aminoácidos de la proteína que buscas: " << endl;
        cin >> aminos;
        ps = busqueda_binaria__prote(lista_copia, 0, (lista_copia.r_tamanio()-1), aminos);

        if (ps == -1) {
            cout << "Proteína no encontrada. Intentalo de nuevo." << endl;
        }
    } while (ps == -1);

    return ps;

}
Proteina menu_agregar(lista_d<Proteina> &lista, Proteina p){//AGREGACION DE AMINOACIDOS ASI COMO PUSH A LA LISTA
    char t_nombre;
    int opc;
    int agregar_opc;
    cout << "Ahora estas en el menu de agregacion de aminoacidos" << endl;
    cout << "Estas dentro de la proteina: " << p.get_nombre_proteina() << endl;

    do{
        cout << "Ingresa el aminoacido: " << endl;
        cin >> t_nombre;
        Aminoacido  a =Aminoacido{t_nombre };
        if(p.secuencia_vacia()){
            cout<<"No existen aminoacidos, asi que sera agregado"<<endl;
            p.push_lista_f(a);
        }
        else{
            do{
            cout<<"En que posicion deseas ingresarlo?"<<endl;
            cout<<"[1]En el frente"<<endl;
            cout<<"[2]En el final"<<endl;
            cout<<"[3]Ingresar posicion"<<endl;
            cin>>agregar_opc;
            }while(agregar_opc<0||agregar_opc>3);
            switch(agregar_opc){
                case 1:
                    p.push_lista_f(a);
                    break;
                case 2:
                    p.push_lista_b(a);
                    break;
                case 3:
                    int push_ps;
                    do{
                        cout<<"Ingresa una posicion valida"<<endl;
                        cin>>push_ps;
                    }while(push_ps<=-1||push_ps>(p.secuencia_tamanio()-1));
                    p.push_lista_ps(a, push_ps);
                    break;
            }

        }
        cout<<"Deseas aniadir otro aminoacido? "<<endl;
        cout<<"[0]NO"<<endl;
        cout<<"[1]SI"<<endl;
        cin>>opc;


    }while(opc);
    return p;

    }
Proteina menu_eliminar_aminos(Proteina p){
    int opc;
    cout<<"Estas en el menu de eliminar aminoacidos, tu proteina es: "<<endl<<p;
    cout<<"Cual deseas eliminar?"<<endl;
    cout<<"[1]El primero"<<endl;
    cout<<"[2]El ultimo"<<endl;
    cout<<"[3]Ingresa una posicion"<<endl;
    do{
        cout<<"Ingresa una posicion valida"<<endl;
        cin>>opc;
    }while(opc<0||opc>3);
    switch(opc){
    case 1:
        p.delete_f_a();
        break;
    case 2:
        p.delete_b_a();
        break;
    case 3:
        int opc_del;
        do{
            cout<<"Ingresa una posicion valida"<<endl;
            cin>>opc_del;
        }while(opc_del<=-1||opc_del>(p.secuencia_tamanio()-1));
        p.delete_ps_a(opc_del);
        break;

    }


    return p;
}
Proteina menu_editar_secuencia(Proteina p){
    int amino_ps;
    char t_amino;
    amino_ps=buscar(p);
    cout<<"Ingresa el nuevo aminoacido"<<endl;
    cin>>t_amino;
    Aminoacido a;
    a.set_nombre_Amino(t_amino);
    p.delete_ps_a(amino_ps);
    p.push_lista_ps(a,amino_ps);
    return p;
}


void buscar_imprimir(lista_d<Proteina> lista){
    if(lista.vacia()){
        cout<<"Lista vacia"<<endl;
        return;
    }
    int ps_pro=buscar(lista);
    int opc;
    Proteina t_p=lista.peek_ps(ps_pro);
    cout<<"El nombre de la proteina es: "<<t_p.get_nombre_proteina()<<endl;
    cout<<"Deseas buscar un aminoacido dentro de la misma?"<<endl;
    cout<<"[1]SI"<<endl;
    cout<<"[2]NO"<<endl;
    do{
        cout<<"Ingresa una opcion valida"<<endl;
        cin>>opc;

    }while(opc<0||opc>2);
    if(opc==1){
        cout<<"Vamos a buscar si el aminoacido existe"<<endl;
        buscarAmino(t_p);

    }


}


void menu_eliminar(lista_d<Proteina>& lista) {//ELIMINACION DE PROTEINAS
    if(lista.vacia()){
            cout<<"LISTA VACIA"<<endl;
        return;
    }
    else{
    int opc=buscar(lista);
    lista.delete_ps(opc);
    }


}
void edit_aminos(lista_d<Proteina> &lista, Proteina p, int ps){
    int amino_opc;
    cout<<p;
    cout<<"Que deseas hacer?"<<endl;
    cout<<"[1]Ingresar aminoacidos "<<endl;
    cout<<"[2]Eliminar aminoacidos"<<endl;
    cout<<"[3]Editar aminoacidos"<<endl;
    do{
        cout<<"Ingresa una opcion valida"<<endl;
        cin>>amino_opc;
    }while(amino_opc<0||amino_opc>3);

    switch(amino_opc){
    case 1:
        p=menu_agregar(lista,p);
        lista.delete_ps(ps);
        lista.push_ps(ps,p);
        break;
    case 2:
        if(p.secuencia_vacia()){
            cout<<"La lista esta vacia"<<endl;
            break;
        }
        p=menu_eliminar_aminos(p);
        lista.delete_ps(ps);
        lista.push_ps(ps,p);
        break;
    case 3:
        if(p.secuencia_vacia()){
            cout<<"La lista esta vacia"<<endl;
            break;
        }
        p=menu_editar_secuencia(p);
        lista.delete_ps(ps);
        lista.push_ps(ps,p);
        break;

    }

}
void menu_editar(lista_d<Proteina>& lista){//BUSQUEDA Y EDICION DEL NOMBRE
    int ps;
    int opc;
    if(lista.vacia()){
        cout<<"Lista vacia"<<endl;
        return;
    }
    cout<<"Ahora estas dentro de la edicion: "<<endl;
    ps =buscar(lista);
    cout<<"Tu proteina es: "<<endl;
    Proteina p;
    p=lista.peek_ps(ps);
    cout<<p;
    cout<<"Que deseas editar?"<<endl;
    cout<<"[1]Nombre de proteina"<<endl;
    cout<<"[2]Aminoacidos"<<endl;
    do{
        cout<<"Ingresa una opcion valida"<<endl;
        cin>>opc;

    }while(opc<0 || opc>2);
    switch(opc){
    case 1:
        nuevo_nombre_p(lista,p,ps);
        cout<<"listo: "<<endl;
        cout<<lista.peek_ps(ps);
        break;
    case 2:
        edit_aminos(lista, p, ps);
        cout<<"listo"<<endl;
        break;


    }




}

void menu_crear(lista_d<Proteina>& lista) {//CRECION DE PROTEINA
    string t_name;
    cout << "Vamos a agregar una nueva proteina" << endl;
    cout << "Ingresa el nombre: " << endl;
    cin >> t_name;
    limpiar_pantalla();
    Proteina p ;
    p.set_nombre_proteina(t_name);
    p=menu_agregar(lista, p);
    menu_push(lista, p);

}

void menu(lista_d <Proteina>&lista){
    unsigned int opcion;

    do{
        cout<<"Bienvenido al sistema de administracion de proteinas"<<endl;
        cout<<"Que desea hacer?"<<endl;
        cout<<"[1]Crear proteina"<<endl;
        cout<<"[2]Eliminar proteina"<<endl;
        cout<<"[3]Editar"<<endl;
        cout<<"[4]Ordenar lista de proteinas" << endl;
        cout<<"[5]Mostrar proteinas" << endl;
        cout<<"[6]Buscar"<<endl;
        cout<<"[0]Salir"<<endl;
        cin >>opcion;
        limpiar_pantalla();
        switch(opcion){
        case 1:
            menu_crear(lista);
            break;
        case 2:
            menu_eliminar(lista);
            break;
        case 3:
            menu_editar(lista);
            break;
        case 4:
            ordenar_lista(lista);
            break;
        case 5:
            imprimir_lista(lista);
            break;
        case 6:
            buscar_imprimir(lista);
            //buscarAmino(lista.peek_ps(0)); ACTUALMENTE ES POSIBLE BUSCAR Y ENCONTRAR UN AMINOACIDO USANDO LA PRIMERA PROTEINA DE LA LISTA
            break;
        case 0:
            cout<<"Nos vemos"<<endl;
            break;
        }
    }while(opcion!=0);
}


int main()/////////////////////////////////////////////////////////////////////////////////
{
    lista_d<Proteina>lista;
    menu(lista);
    lista.~lista_d();
    return 0;
}
