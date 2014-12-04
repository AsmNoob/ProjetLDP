#ifndef _TableauMulti_H_
#define _TableauMulti_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...
#include <stdexcept> // out_of_range,...


// ----------- Classe Tableau ---------------- //

template < typename T >
class Tableau{

public:

    // Constructeurs

    Tableau() = default;
    Tableau(std::size_t size = 0):size_(size),tab_(new T[size]){}                // constructeur par dimension
    Tableau(std::size_t size, T* tableau):size_(size),tab_(tableau){}                       // constructeur avec une array
    Tableau (const Tableau<int>& tableau):size_(tableau.size_),tab_(new T[tableau.size_]){
        for(std::size_t i = 0; i < tableau.size_ ;i++){
            tab_[i] = tableau.tab_[i];
        }
    }                                   // constructeur de copie
    Tableau (Tableau<int>&& tableau):size_(tableau.size_),tab_(tableau.tab_){
        tableau.size_ = 0;
        tableau.tab_ = nullptr;
    }                            // constructeur de transfert
    
    // Opérateurs 

    Tableau& operator= (const Tableau& );                     // opérateur d'assignation
    Tableau& operator= (Tableau&&);                  // opérateur de transfert
    inline const T operator[] (ptrdiff_t ptr) const;          // opérateur []
    inline T& operator[] (ptrdiff_t ptr);                     // opérateur []
    ~Tableau() = default;
    //~Tableau(){delete[] tab_;}; Problème avec le destructeur

    // Méthodes

    template < typename M >
    friend std::ostream& operator<< (std::ostream&, const Tableau<M>&);

    std::size_t getSize(){
        return size_;
    }

    private:

    // Attributs

    std::size_t size_;
    T* tab_;



};

template <typename T >
Tableau<T>& Tableau<T>::operator= (Tableau&& tableau) {
  if (this != &tableau) {
    size_ = tableau.size_;
    //delete[] tab_;
    tab_ = tableau.tab_; // pointe vers la même adresse
    tableau.size_ = 0; tableau.tab_ = nullptr;
  }
  return *this;
}

template < typename T >
Tableau<T>& Tableau<T>::operator= (const Tableau& tableau){
    if (this != &tableau) {
        //delete[] tab_; ?? Pourquoi le prof l'a ajouté ?
        tab_ = new T[tableau.size_];
        size_ = tableau.size_;
        for(std::size_t i = 0; i < tableau.size_ ;i++){
            tab_[i] = tableau.tab_[i];
        }
    }
    return *this;
}

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

    TableauMulti (){
        tableau_[0] = new Tableau<T>(DIMENSION);
    }                                      // constructeur par défaut
    TableauMulti (T* tableauDimensions){
        std::cout << "\033[0;31m Creation\033[0m" << std::endl;
        for(size_t i = 0; i < DIMENSION; ++i){
            tableau_[i] = new Tableau<T>(tableauDimensions[i]); // new pour éviter la destruction de l'objet créé après le scope du for
            std::cout<< "Valeur de tabl[i]: "<< *tableau_[i] << std::endl;
        }
        std::cout<< "Valeur de tabl[0]: "<< *tableau_[0] << std::endl;
        std::cout << "\033[0;31mFin creation\033[0m" << std::endl;
    };                                 // constructeur par array de tailles des différentes listes
    TableauMulti (const TableauMulti<T,DIMENSION>& tableau)/*:tableau_(new Tableau<T>(DIMENSION))*/{          // constructeur de copie
        for(std::size_t i = 0; i < DIMENSION; i++){

            tableau_[i] = new Tableau<T>(*tableau.tableau_[i]);
        }
    }                
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

template< typename T, size_t DIMENSION >
TableauMulti<T,DIMENSION>& TableauMulti<T,DIMENSION>::operator= (const TableauMulti<T,DIMENSION>& tableau){
    if(this != &tableau){
        std::cout<<tableau;
        for (std::size_t i = 0; i < DIMENSION; ++i){
            std::cout<<" tableau.tableau_[i]: "<<*tableau.tableau_[i]<<std::endl;

            tableau_[i] = new Tableau<T>(tableau.tableau_[i]->getSize());
            std::cout<<" tableau_[i]: "<<*tableau_[i]<<std::endl;
            *tableau_[i] = *tableau.tableau_[i];
            std::cout<<" tableau.tableau_[i]: "<<*tableau.tableau_[i]<<std::endl;
            std::cout<<" tableau_[i]: "<<*tableau_[i]<<std::endl;
            // DEMANDER A ROM1 COMMENT UTILISER Lopérateur d'assignation créé précédemment
            /*for (std::size_t j = 0; j < tableau.tableau_[i]->getSize(); ++j){
                tableau_[i][j] = tableau.tableau_[i][j];
            }*/
        }
    }
    return *this;
}



/*template < typename T >
Tableau<T>& Tableau<T>::operator= (const Tableau& tableau){
    if (this != &tableau) {
        //delete[] tab_; ?? Pourquoi le prof l'a ajouté ?
        tab_ = new T[tableau.size_];
        size_ = tableau.size_;
        for(std::size_t i = 0; i < tableau.size_ ;i++){
            tab_[i] = tableau.tab_[i];
        }
    }
    return *this;
}*/

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
