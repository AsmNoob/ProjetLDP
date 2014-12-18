#ifndef _TableauCompact_H_
#define _TableauCompact_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t (pas sur si inclure si on utilise std::size_t)
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...
#include <stdexcept> // out_of_range,...





// template < typename T, std::size_t DIMENSION = 1 >
// class TableauCompact{};

// -----------------------------------------------------------------------------------------------//

// Pour DIM = 1 créer une spécialisation pour [];


// template < typename T, std::size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
// class TableauCompact{}; // Pas instanciable car on tombe d'office dans une spécialisation




//--------------------------------------------------------------------------------------------//

template < typename T, std::size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
class TableauCompact{
private:

    // Attributs

    T* tableau_; // array compacte qui contient toutes les valeurs 
    std::size_t tailleTableau_; // taille complete de ce tableau en compacté
    int tailles_[DIMENSION]; // array qui contient les tailles de chaque dimension
    int sous_tailles_[DIMENSION]; // contient les tailles des sous-dimensions


public:

    // Constructeurs
    TableauCompact ();
    TableauCompact (std::size_t);                                        // constructeur par défaut
    TableauCompact (int*);                                               // constructeur par array de tailles des différentes listes
    TableauCompact (const TableauCompact<T,DIMENSION>& );                // constructeur de copie
    TableauCompact (TableauCompact<T,DIMENSION> &&);                     // constructeur de transfert
                                                  
    // Destructeur

    ~TableauCompact ();

    // Surcharge d'opérateurs

    TableauCompact& operator= (const TableauCompact<T,DIMENSION>& );         // opérateur d'assignation
    TableauCompact& operator= (TableauCompact<T,DIMENSION>&&);               // opérateur de transfert
    //inline const TableauSlice operator[] (ptrdiff_t ptr) const;             // opérateur []
    // inline Tableau<T>& operator[] (ptrdiff_t ptr);                        // opérateur []

    // Méthodes
    template < typename M, std::size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauCompact<M,Dim>&);

};

template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::TableauCompact():tableau_(nullptr),tailleTableau_(0){}


// Constructeur avec la dimension par défaut 1 et de taille donnée
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::TableauCompact(std::size_t taille):tableau_(new T[taille]){}

// Destructeur
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::~TableauCompact(){
    delete tableau_;
}
// Constructeur avec array contenant les tailles des dimensions
// ATTENTION Vérifier la valeur de DIMENSION .... quoique on va pas rentrer dans la boucle donc rien ne va être créé
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::TableauCompact(int* array)/*:tableau_(new T[])*/{ // on ne peut pas initialiser tableau_ ici car on a besoin de parcourir l'array
    for(std::size_t i = 0; i < DIMENSION; i++){
        tailleTableau_*=array[i];
    }
    tableau_ = new T[tailleTableau_];
}

//------------------//
/*template <typename T, std::size_t DIMENSION>
const TableauSlice TableauCompact<T,DIMENSION>::operator[] (std::ptrdiff_t i) const {
    if(i < 0 or i >= tailles_[0]){
        throw std::out_of_range("TableauCompact: Index out of range");
    }else{
        TableauSlice<T,DIMENSION-1> tableau =  TableauSlice<T,DIMENSION-1>();
        return tableau;
    }
}*/
//-------------------//

//---------------------------------------------------------------------------------------------//


template < typename T >
class TableauCompact <T,1>{
private:
    //Attributs
    std::size_t size_;
    T* tableau_;

public:
    //Constructeurs
    TableauCompact();
    TableauCompact(std::size_t );
    TableauCompact(T*, std::size_t);
    TableauCompact(const TableauCompact<T,1>& );                // constructeur de copie
    TableauCompact(TableauCompact<T,1>&& );                     // constructeur de transfert

    // Opérateurs
    TableauCompact<T,1>& operator= (const TableauCompact<T,1>& );                     // opérateur d'assignation
    TableauCompact<T,1>& operator= (TableauCompact<T,1>&&);                  // opérateur de transfert
    inline const T operator[] (ptrdiff_t ptr) const;          // opérateur []
    inline T& operator[] (ptrdiff_t ptr);                     // opérateur []

    template < typename M >
    friend std::ostream& operator<< (std::ostream&, const TableauCompact<M,1>&);

    // Destructeur
    ~TableauCompact() = default;
};


template < typename T>
TableauCompact<T,1>::TableauCompact(std::size_t size):size_(size),tableau_(new T[size]){}

template < typename T>
TableauCompact<T,1>::TableauCompact(T* tableau,std::size_t size):size_(size),tableau_(new T[size]){
    for(std::size_t i = 0; i < size;i++){
        tableau_[i] = tableau[i];
    }
}

template < typename T >
TableauCompact<T,1>::TableauCompact (const TableauCompact<T,1>& tableau):size_(tableau.size_),tableau_(new T[tableau.size_]){
    for(std::size_t i = 0; i < tableau.size_ ;i++){
        tableau_[i] = tableau.tableau_[i];
    }
}
   
template < typename T >                         // constructeur de copie
TableauCompact<T,1>::TableauCompact (TableauCompact<T,1>&& tableau):size_(tableau.size_),tableau_(tableau.tableau_){
    tableau.size_ = 0;
    tableau.tableau_ = nullptr;
}        


template < typename T >
TableauCompact<T,1>& TableauCompact<T,1>::operator= (const TableauCompact& tableau){
    if (this != &tableau) {
        //delete[] tab_; ?? Pourquoi le prof l'a ajouté ?
        tableau_ = new T[tableau.size_];
        size_ = tableau.size_;
        for(std::size_t i = 0; i < tableau.size_ ;i++){
            tableau_[i] = tableau.tableau_[i];
        }
    }
    return *this;
}


template <typename T >
TableauCompact<T,1>& TableauCompact<T,1>::operator= (TableauCompact&& tableau) {
  if (this != &tableau) {
    size_ = tableau.size_;
    //delete[] tab_;
    tableau_ = tableau.tableau_; // pointe vers la même adresse
    tableau.size_ = 0; tableau.tableau_ = nullptr;
  }
  return *this;
}

template <typename T>
const T TableauCompact<T,1>::operator[] (std::ptrdiff_t i) const {
  if (std::size_t(i) >= size_)
    throw std::out_of_range("Tableau : Index out of range");
  return tableau_[i];
}

template <typename T>
T& TableauCompact<T,1>::operator[] (std::ptrdiff_t i) {
  if (std::size_t(i) >= size_)
    throw std::out_of_range("Tableau : Index out of range");
  return tableau_[i];
}

template < typename T >
std::ostream& operator<< (std::ostream& out, const TableauCompact<T,1>& tableau){
    T *p = tableau.tableau_; // pointeur vers le début de l'array
    //std::cout<<sizeof(tab);
    out << "[ ";
    for (size_t i = 0; i < tableau.size_; ++i){
        out <<(*p++);
        if(i < tableau.size_-1)
            out<<", ";
    }
    out<<" ]";
    return out;
}

// J'AVOUE NE PAS COMPRENDRE EXACTEMENT COMMENT FONCTIONNE LA SIGNATURE D'HERITAGE en regardant les exemples

template < typename T,std::size_t DIMENSION>
class TableauSlice/*<T,DIMENSION>*/ : public TableauCompact<T,DIMENSION>{
public:
    TableauSlice();
    // TableauSlice(TableauSlice&)
    // TableauSlice(TableauSlice&&)



    ~TableauSlice();
};

template < typename T>
class TableauSlice < T, 1 > : public TableauCompact<T>{
public:
    TableauSlice();
    ~TableauSlice();
    
};









#endif