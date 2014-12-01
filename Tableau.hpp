#ifndef _TableauMulti_H_
#define _TableauMulti_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...


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
    ~Tableau() = default;
    //~Tableau(){delete[] tab_;}; Problème avec le destructeur

    // Méthodes

    template < typename M >
    friend std::ostream& operator<< (std::ostream&, const Tableau<M>&);

    

};

template < typename T >
std::ostream& operator<< (std::ostream& out, const Tableau<T>& tab){
    T *p = tab.tab_; // pointeur vers le début de l'array
    //std::cout<<sizeof(tab);
    out << "[ ";
    for (size_t i = 0; i < tab.size_; ++i){
        out <<*p++;
        if(i < tab.size_-1)
            out<<", ";
    }
    out<<" ]";
    out<< std::endl;
    return out;
}

// ----------- Classe TableauMulti --------------- //

template < typename T, size_t Dimension = 1>  // 2 paramètres de template: type et nombre de tableaux 
class TableauMulti{
private:

    // Attributs

    Tableau<T>* tableau_; // tableau qui va contenir tous les autres tableaux

public:

    // Constructeurs

    TableauMulti () = default;                                        // constructeur par défaut
    TableauMulti (T* tableauDimensions):tableau_(new Tableau<T>(Dimension)){
        for(size_t i = 0; i < Dimension; ++i){
            tableau_[i] = Tableau<T>(tableauDimensions[i]);
        }
    };                                 // constructeur par array de tailles des différentes listes
    TableauMulti (const TableauMulti<T,Dimension> & );                // constructeur de copie
    TableauMulti (TableauMulti<T,Dimension> &&);                      // constructeur de transfert
    

    // Destructeur

    ~TableauMulti (){
        
        /*for(std::size_t i = 0; i < Dimension;++i){
            delete tableau_[i];
        }
        delete[] tableau_;*/
    }             

    // Surcharge d'opérateurs

    TableauMulti& operator= (const TableauMulti<T,Dimension>& );        // opérateur d'assignation
    TableauMulti& operator= (TableauMulti<T,Dimension>&&);             // opérateur de transfert
    inline T operator[] (ptrdiff_t ptr) const;          // opérateur []
    inline T& operator[] (ptrdiff_t ptr);                // opérateur []

    // Méthodes
    template < typename M, size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauMulti<M,Dim>&);

};


template < typename T, size_t Dim >
std::ostream& operator<< (std::ostream& out, const TableauMulti<T,Dim>& tableau){
    out << "[ "<< std::endl;
    for(std::size_t i = 0; i < Dim; ++i){
        out << tableau.tableau_[i];
        if(i < Dim-1)
            out<<", ";
    }
    out<<" ]"<<std::endl;
    return out;
}




#endif