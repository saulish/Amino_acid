#ifndef LISTA_D_H
#define LISTA_D_H
#include <iostream>
using namespace std;

template <typename objeto>
class lista_d
{
public:
    lista_d(const lista_d <objeto>& rhs);
    ~lista_d();
    lista_d(lista_d <objeto>&& rhs);
    lista_d();
    lista_d <objeto>& operator=(const lista_d <objeto>& rhs);
    const objeto& operator[](int x)const{
        if(x<0 || x>=tamanio){
            throw std::out_of_range("Índice fuera de rango");
        }
        nodo* act = head;
        for (int i = 0; i < x; i++) {
            act = act->next;
        }
        return act->dato;
    }
    objeto& operator[](int x){

        if(x<0 || x>=tamanio){
            throw std::out_of_range("Índice fuera de rango");
        }
        nodo* act = head;
        for (int i = 0; i < x; i++) {
            act = act->next;
        }
        return act->dato;
    }
    void iniciar();

    bool llena();

    void push_b(const objeto& x);
    void push_b(objeto&& x);
    bool vacia();
    void push_f(const objeto& x);
    void push_f(objeto&& x);
    void push_f(const objeto* p);
    void push_ps(int ps, const objeto& x);
    void push_ps(int ps, objeto&& x);

    void delete_f();
    void delete_b();
    void delete_ps(int x);

    const int r_tamanio()const;
    const objeto peek_f()const;
    const objeto peek_b()const;
    const objeto peek_td(int x)const;
    const objeto peek_ps(int x)const;
    const objeto peek_td_reves(int x)const;
    bool validacion(int x);
    template <typename T>
    friend ostream& operator<<(ostream& salida, const lista_d<T>& lista);

    void change_nodo(int _left, int _right){
        /* nodo* temp; */
        nodo* nodo1 = head;
        nodo* nodo2 = head;
        for (int i = 0; i < _left - 1; i++) {
            nodo1 = nodo1->next;
        }
        for (int i = 0; i < _right - 1; i++) {
            nodo2 = nodo2->next;
        }

        /* temp = nodo1;
        nodo1 = nodo2;
        nodo2=temp;
        delete temp; */
        swap(nodo1->dato,nodo2->dato);
    }

    int getCapacidad(){
        return capacidad;
    }

    int getTamanio(){
        return tamanio;
    }



protected:
    struct nodo
    {
        objeto dato;
        nodo* next;
        nodo* prev;
        nodo(const objeto& d = objeto{}, nodo* n = nullptr) :dato{ d }, next{ n }, prev{ n }
        {}
        nodo(objeto&& d = objeto{}, nodo* n = nullptr) :dato{ move(d) }, next{ move(n) }, prev{ move(n) }
        {}
    };
    nodo* head;
    nodo* tail;
    int tamanio;
    int capacidad;
    class iterador_const
    {
    public:
            iterador_const begin() {
        return iterador{head};  // El iterador comienza en el primer nodo (head)
    }

    iterador_const end() {
        return iterador{nullptr};  // El iterador de fin apunta a nullptr
    }
        iterador_const() :actual{ nullptr }
        {}
        const objeto& operator*()const
        {
            return recuperar();
        }
        iterador_const& operator++()
        {
            actual = actual->next;
            return *this;
        }
        iterador_const& operator++(int)
        {
            iterador_const viejo = *this;
            ++(*this);
            return viejo;
        }
        bool operator== (const iterador_const& rhs)const
        {
            return actual == rhs.actual;
        }
        bool operator!=(const iterador_const& rhs)const
        {
            return !(*this == rhs);
        }


    protected:
        nodo* actual;
        objeto& recuperar() const
        {
            return actual->dato;
        }
        iterador_const(nodo* p) :actual{ p }
        {
        }
        friend class lista_d <objeto>;
    };
    class iterador :public iterador_const
    {
    public:
            iterador begin() {
        return iterador{head};
    }

    iterador end() {
        return iterador{nullptr};
    }

        iterador()
        {
        }
        objeto& operator*()
        {
            return iterador_const::recuperar();
        }
        const objeto& operator*()const
        {
            return iterador_const::operator*();
        }
        iterador& operator++()
        {
            this->actual = this->actual->next;
            return *this;
        }
        iterador operator++(int)
        {
            iterador viejo = *this;
            ++(*this);
            return viejo;
        }
    protected:
        /* friend class lista_d <objeto>; */
    };

};

template <typename objeto>
lista_d <objeto>::lista_d(const lista_d <objeto>& rhs)
{
    iniciar();
    nodo* current = rhs.head;
    while (current != nullptr) {
        push_b(current->dato);
        current = current->next;
    }
    // copy ctor
}
template <typename objeto>
lista_d <objeto>::lista_d(lista_d <objeto>&& rhs) :head{ rhs.head }, tail{ rhs.tail }, tamanio{ rhs.tamanio }, capacidad{ rhs.capacidad }
{
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.tamanio = 0;
    rhs.capacidad = 10000;
}
template <typename objeto>
lista_d <objeto>::~lista_d()
{
    nodo* t;
    while (head != nullptr) {
        t = head;
        head = head->next;
        delete t;
    }
    tail = nullptr;
    delete head;
    delete tail;
    //dtor
}
template <typename objeto>
lista_d <objeto>::lista_d()
{
    iniciar();
}


template <typename objeto>
lista_d<objeto>& lista_d<objeto>::operator=(const lista_d<objeto>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    nodo* nodo_actual = head;
    while (nodo_actual) {
        nodo* siguiente = nodo_actual->next;
        delete nodo_actual;
        nodo_actual = siguiente;
    }
    head = nullptr;
    tail = nullptr;


    nodo* nodo_rhs = rhs.head;
    while (nodo_rhs) {
        push_b(nodo_rhs->dato);
        nodo_rhs = nodo_rhs->next;
    }

    return *this;
}

template <typename objeto>
void lista_d <objeto>::iniciar()
{
    head = nullptr;
    tail = nullptr;
    tamanio = 0;
    capacidad = 10000;
}

template <typename objeto>
bool lista_d <objeto>::llena()
{
    if (tamanio == capacidad)
        return true;
    else
        return false;
}
template <typename objeto>
bool lista_d <objeto>::vacia()
{
    if (head == nullptr)
        return true;
    else
        return false;
}
template <typename objeto>
void lista_d <objeto>::push_b(const objeto& x)
{
    nodo* p = new nodo{ x,nullptr };
    if (vacia()) {
        p->next = head;
        p->prev = nullptr;
        if (head != nullptr) {
            head->prev = p;
        }
        else {
            tail = p;
        }
        head = p;
        tamanio++;
    }
    else {
        tail->next = p;
        p->prev = tail;
        tail = p;
        tamanio++;
    }
}
template <typename objeto>
void lista_d <objeto>::push_b(objeto&& x)
{
    nodo* p = new nodo{ move(x),nullptr };
    if (vacia())
    {
        p->next = head;
        head = p;
        tail = head;
        tamanio++;
    }
    else {
        tail->next = p;
        p->prev = tail;
        tail = p;
        tamanio++;
    }
}









template <typename objeto>
void lista_d <objeto>::push_f(const objeto& x)
{
    nodo* p = new nodo{ x,nullptr };
    if (vacia()) {
        p->next = head;
        p->prev = nullptr; // Asegurar que el puntero prev del nuevo nodo sea nullptr
        if (head != nullptr) {
            head->prev = p; // Actualizar el puntero prev del nodo anterior head
        }
        else {
            tail = p; // Si la lista estaba vacía, también debemos actualizar tail
        }
        head = p; // Asignar p como el nuevo head
        tamanio++;
    }
    else {
        p->next = head;
        head->prev = nullptr;
        head = p;
        tamanio++;
    }
}
template <typename objeto>
void lista_d <objeto>::push_f(objeto&& x)
{
    nodo* p = new nodo{ move(x),nullptr };
    if (vacia()) {
        p->next = head;
        p->prev = nullptr; // Asegurar que el puntero prev del nuevo nodo sea nullptr
        if (head != nullptr) {
            head->prev = p; // Actualizar el puntero prev del nodo anterior head
        }
        else {
            tail = p; // Si la lista estaba vacía, también debemos actualizar tail
        }
        head = p; // Asignar p como el nuevo head
        tamanio++;
    }
    else {
        p->next = head;
        head->prev = nullptr;
        head = p;
        tamanio++;
    }

}
template <typename objeto>
const objeto lista_d <objeto>::peek_f()const
{

    return head->dato;

}
template <typename objeto>
const objeto lista_d <objeto>::peek_b()const
{
    return tail->dato;

}
template <typename objeto>
const objeto lista_d <objeto>::peek_td(int x)const
{
    nodo* p = head;
    for (int i = 0; i < x; i++)
    {
        p = p->next;
    }

    return p->dato;
}
template <typename objeto>
const objeto lista_d <objeto>::peek_td_reves(int x)const
{
    nodo* p = tail;
    for (int i = 0; i < x; i++)
    {
        p = p->prev;
    }

    return p->dato;
}
template <typename objeto>
const objeto lista_d <objeto>::peek_ps(int x)const
{
    nodo* p = head;
    for (int i = 0; i < x; i++)
    {
        p = p->next;
    }

    return p->dato;
}
template <typename objeto>
const int lista_d<objeto>::r_tamanio()const {
    return tamanio;
}
template <typename objeto>
void lista_d <objeto>::push_ps(int ps, const objeto& x)
{
    if (vacia())
    {
        push_f(x);
        return;
    }
    else if (ps == 0) {
        push_f(x);
        return;
    }
    else if (ps == tamanio) {
        push_b(x);
        return;
    }
    else if (validacion(ps)) {
        nodo* pre = head;
        nodo* aft;
        for (int i = 0; i < ps - 1; i++) {
            pre = pre->next;
        }
        aft = pre->next;
        nodo* n = new nodo{ x,nullptr };
        n->next = aft;
        aft->prev = n;
        pre->next = n;
        n->prev = pre;
        tamanio++;
    }
    else {

    }
}
template <typename objeto>
void lista_d <objeto>::push_ps(int ps, objeto&& x)
{
    if (vacia())
    {
        push_f(x);
    }
    else if (ps == 0) {
        push_f(x);
        return;
    }
    else if (ps == tamanio) {
        push_b(x);
        return;
    }
    else if (validacion(ps)) {
        nodo* pre = head;
        nodo* aft;
        for (int i = 0; i < ps - 1; i++) {
            pre = pre->next;
        }
        aft = pre->next;
        nodo* n = new nodo{ move(x),nullptr };
        n->next = aft;
        aft->prev = n;
        pre->next = n;
        n->prev = pre;
        tamanio++;
    }
    else {

    }
}
template <typename objeto>
bool lista_d<objeto>::validacion(int x)
{
    if (x >= 0 && x <= tamanio) {
        return true;
    }
    else {
        return false;
    }
}

template <typename objeto>
void lista_d<objeto>::delete_f()
{
    if (vacia()) {
        return;
    }
    else {
        nodo* tmp = head;
        head = head->next;
        delete tmp;
        tamanio--;

        if (head == nullptr) {
            tail = nullptr;
        }
        else {
            head->prev = nullptr;
        }
    }

}
template <typename objeto>
void lista_d<objeto>::delete_b()
{
    if (vacia()) {
        return;
    }
    else if (head == tail) {
        delete_f();
        return;
    }
    else {
        nodo* pre = nullptr;
        nodo* tmp = head;

        while (tmp->next != nullptr) {
            pre = tmp;
            tmp = tmp->next;
        }

        pre->next = nullptr;
        delete tmp;
        tail = pre;
        tamanio--;

    }
}
template <typename objeto>
void lista_d<objeto>::delete_ps(int ps)
{
    if (vacia()) {
        return;
    }
    else if (ps == 0) {
        delete_f();
        return;
    }
    else if (ps == tamanio-1) {
        delete_b();
        return;
    }
    else if (validacion(ps)) {
        nodo* pre = head;
        for (int i = 0; i < ps - 1; i++) {
            pre = pre->next;
        }
        nodo* dlt = pre->next;
        nodo* aft=dlt->next;
        pre->next = aft;
        //aft->prev = pre;
        aft->prev = dlt->prev;
        delete dlt;
        tamanio--;
    }
    else {

    }



}
template <typename Aminoacido>
ostream& operator<<(ostream& salida, const lista_d<Aminoacido>& lista) {
    if(lista.r_tamanio()==0){
        salida <<"Vacia"<<endl;
    }
    else{
         for(int i=0;i<lista.r_tamanio();i++){
            salida<<lista.peek_ps(i)<<endl;
         }

    }
    return salida;
}


#endif

