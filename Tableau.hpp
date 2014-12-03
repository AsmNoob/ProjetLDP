#ifndef _TableauMulti_H_
#define _TableauMulti_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...
#include <stdexcept> // out_of_range,...


// ----------- Classe Tableau ---------------- //

template < typename T >
class Tableau{

private:

    // Attributs

    T* tab_;
    std::size_t size_;

public:

    // Constructeurs

    Tableau() = default;
    Tableau(std::size_t size = 0):tab_(new T[size]),size_(size){
        std::cout<<"Constructeur par taille, taille: "<< size_ <<std::endl;
    }                // constructeur par dimension
    Tableau(std::size_t size, T* tableau):tab_(tableau),size_(size) {
        std::cout<<"Constructeur par tableau, taille: "<< size_ <<std::endl;
    }                       // constructeur avec une array
    Tableau (const Tableau&) = default;                       // constructeur de copie
    Tableau (Tableau&&) = default;                            // constructeur de transfert
    Tableau& operator= (const Tableau&) = default;            // opérateur d'assignation
    Tableau& operator= (Tableau&&)= default;                  // opérateur de transfert
    inline const T operator[] (ptrdiff_t ptr) const;          // opérateur []
    inline T& operator[] (ptrdiff_t ptr);                     // opérateur []
    ~Tableau() = default;
    //~Tableau(){delete[] tab_;}; Problème avec le destructeur

    // Méthodes

    template < typename M >
    friend std::ostream& operator<< (std::ostream&, const Tableau<M>&);

    size_t getSize(){
        return size_;
    }


};

template <typename T>
const T Tableau<T>::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= size_)
    throw std::out_of_range("Tableau : Index out of range");
  return tab_[i];
}

template <typename T>
T& Tableau<T>::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= size_)
    throw std::out_of_range("Tableau : Index out of range");
  return tab_[i];
}


template < typename T >
std::ostream& operator<< (std::ostream& out, const Tableau<T>& tab){
    T *p = tab.tab_; // pointeur vers le début de l'array
    //std::cout<<sizeof(tab);
    out << "[ ";
    for (size_t i = 0; i < tab.size_; ++i){
        out <<(*p++);
        if(i < tab.size_-1)
            out<<", ";
    }
    out<<" ]";
    return out;
}

// ----------- Classe TableauMulti --------------- //

template < typename T, size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
class TableauMulti{
private:

    // Attributs

    Tableau<T>* tableau_[DIMENSION]; // tableau qui va contenir tous les autres tableaux

public:

    // Constructeurs

    TableauMulti () = default;                                        // constructeur par défaut
    TableauMulti (T* tableauDimensions){
        std::cout << "\033[0;31m Creation\033[0m" << std::endl;
        for(size_t i = 0; i < DIMENSION; ++i){
            tableau_[i] = new Tableau<T>(tableauDimensions[i]); // new pour éviter la destruction de l'objet créé après le scope du for
            std::cout<< "Valeur de tabl[i]: "<< *tableau_[i] << std::endl;
        }
        std::cout<< "Valeur de tabl[0]: "<< *tableau_[0] << std::endl;
        std::cout << "\033[0;31mFin creation\033[0m" << std::endl;
    };                                 // constructeur par array de tailles des différentes listes
    TableauMulti (const TableauMulti<T,DIMENSION> & );                // constructeur de copie
    TableauMulti (TableauMulti<T,DIMENSION> &&);                      // constructeur de transfert


    // Destructeur

    ~TableauMulti (){

        /*for(std::size_t i = 0; i < DIMENSION;++i){
            delete tableau_[i];
        }
        delete[] tableau_;*/
    }

    // Surcharge d'opérateurs

    TableauMulti& operator= (const TableauMulti<T,DIMENSION>& );        // opérateur d'assignation
    TableauMulti& operator= (TableauMulti<T,DIMENSION>&&);             // opérateur de transfert
    inline const Tableau<T> operator[] (ptrdiff_t ptr) const;          // opérateur []
    inline Tableau<T>& operator[] (ptrdiff_t ptr);                // opérateur []

    // Méthodes
    template < typename M, size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauMulti<M,Dim>&);

    std::size_t getSize(){
        return DIMENSION;
    }

    std::size_t getSizeAll(){
        std::size_t completeSize = 0;
        for(std::size_t i = 0; i < DIMENSION;++i){
            std::cout<<"Dimension tableau"<< i << ": " << tableau_[i]->getSize() << std::endl;
            completeSize+=tableau_[i]->getSize();
        }
        return completeSize;
    }

};

template <typename T, size_t DIMENSION>
const Tableau<T> TableauMulti<T,DIMENSION>::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= DIMENSION)
    throw std::out_of_range ("TableauMulti : Index out of range"); // ne fonctionne pas avec std:: uniquement il a fallu #include <stdexcept>
  return *tableau_[i];
}

template <typename T, size_t DIMENSION>
Tableau<T>& TableauMulti<T,DIMENSION>::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= DIMENSION)
    throw std::out_of_range("TableauMulti : Index out of range");
  return *tableau_[i];
}


template < typename T, size_t Dim >
std::ostream& operator<< (std::ostream& out, const TableauMulti<T,Dim>& tableau){
    out << "[ ";
    for(std::size_t i = 0; i < Dim; ++i){
        out << *tableau.tableau_[i];
        if(i < Dim-1)
            out<<", ";
    }
    out<<" ]"<<std::endl;
    return out;
}




#endif
