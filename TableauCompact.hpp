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
    std::size_t taille_tableau_ = 1; // taille complete de ce tableau en compacté
    int tailles_[DIMENSION]; // array qui contient les tailles de chaque dimension
    int sous_tailles_[DIMENSION]; // contient les tailles des sous-dimensions


public:

    // Constructeurs
    TableauCompact ();
    TableauCompact (int*);                                               // constructeur par array de tailles des différentes listes
    // TableauCompact (const TableauCompact<T,DIMENSION>& );                // constructeur de copie
    // TableauCompact (TableauCompact<T,DIMENSION> &&);                     // constructeur de transfert
                                                  
    // Destructeur

    ~TableauCompact ();

    // Surcharge d'opérateurs

    // TableauCompact& operator= (const TableauCompact<T,DIMENSION>& );         // opérateur d'assignation
    // TableauCompact& operator= (TableauCompact<T,DIMENSION>&&);               // opérateur de transfert
    inline const TableauCompact<T,DIMENSION-1> operator[] (ptrdiff_t ptr) const;             // opérateur []
    // inline Tableau<T>& operator[] (ptrdiff_t ptr);                        // opérateur []

    // Méthodes
    template < typename M, std::size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauCompact<M,Dim>&);

    T* get_tableau(){
        return tableau_;
    }

    void set_tableau(T* tableau){
        tableau_ = tableau;
    }

    int* get_tailles(){
        return tailles_;
    }

    void set_tailles(int* tailles){
        for(std::size_t i = 0; i < DIMENSION; i++){
            tailles_[i] = tailles[i];
        }
    }

    int* get_sousTailles(){
        return sous_tailles_;
    }

    void set_sousTailles(int* sous_tailles){
        for(std::size_t i = 0; i < DIMENSION; i++){
            sous_tailles_[i] = sous_tailles[i];
        }
    }

};
// Constructeurs
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::TableauCompact():tableau_(nullptr),taille_tableau_(0){}

// Constructeur avec array contenant les tailles des dimensions
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::TableauCompact(int* array){ // on ne peut pas initialiser tableau_ ici car on a besoin de parcourir l'array
    std::cout << "\033[0;31mCreation\033[0m" << std::endl;
    for(std::size_t i = 0; i < DIMENSION; i++){
        std::cout << " array["<<i<<"]: "<<array[i]; 
        taille_tableau_*=array[i]; // ensemble d'elements
        std::cout<< "taille_tableau_ :"<< taille_tableau_ <<std::endl;
        tailles_[i] = array[i]; // enregistre les différentes tailes de chaque dimension
    }


    std::cout<<std::endl << "\033[0;31mTest tailles_\033[0m" << std::endl;
    for(std::size_t i = 0; i < DIMENSION;i++){
        std::cout << " tailles_["<<i<<"]: "<<tailles_[i];
    }
    tableau_ = new T[taille_tableau_];
    std::cout<<std::endl << "\033[0;31mTest tableau_\033[0m" << std::endl;
    for(std::size_t i = 0; i < taille_tableau_;i++){
        std::cout << " tableau_["<<i<<"]: "<<tableau_[i];
    }
    int valeur_sousTaille = 1;
    std::cout << "MIDDLE"<<std::endl;
    for(std::size_t i = DIMENSION; i  > 0; i--){
        std::cout<<"i: "<<i;
        valeur_sousTaille*= tailles_[i-1];
        sous_tailles_[i-1] = valeur_sousTaille;
    }
    std::cout<<std::endl << "\033[0;31mTest sous_tailles_\033[0m" << std::endl;
    for(std::size_t i = 0; i < DIMENSION;i++){
        std::cout << " sous_tailles_["<<i<<"]: "<<sous_tailles_[i];
    }
    
    std::cout<<std::endl << "\033[0;31mFin creation\033[0m" << std::endl;
}

// Destructeur
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::~TableauCompact(){
    delete tableau_;
    delete tailles_;
    delete sous_tailles_;
}


//------------------//
template <typename T, std::size_t DIMENSION>
const TableauCompact<T,DIMENSION-1> TableauCompact<T,DIMENSION>::operator[] (std::ptrdiff_t i) const {
    if(i < 0 or i >= tailles_[0]){
        throw std::out_of_range("TableauCompact: Index out of range");
    }else{
        int nouvelle_tailles[DIMENSION-1];
        int nouvelle_sousTailles[DIMENSION-1];
        std::cout << "test nouvelles array tailles"<< std::endl;
        for(std::size_t i = 0; i < (DIMENSION-1);i++){
            nouvelle_tailles[i] = tailles_[i+1];
            std::cout << "nouvelles_tailles["<<i<<"]: " << nouvelle_tailles[i] << std::endl;
            nouvelle_sousTailles[i] = sous_tailles_[i+1];
            std::cout << "nouvelles_sous_tailles["<<i<<"]: " << nouvelle_sousTailles[i] << std::endl;
        }

        TableauCompact<T,DIMENSION-1> tableau =  TableauCompact<T,DIMENSION-1>();
        tableau.set_tableau(tableau_+i*sous_tailles_[0]);
        tableau.set_tailles(nouvelle_tailles);
        tableau.set_sousTailles(nouvelle_sousTailles);

        return tableau;
    }
}
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

    T* get_tableau(){
        return tableau_;
    }

    void set_tableau(T* tableau){
        tableau_ = tableau;
    }

    void set_tailles(int* tailles){
        size_ = tailles[0];
    }

    void set_sousTailles(int* sous_tailles){
        size_ = sous_tailles[0];
    }

    // Destructeur
    ~TableauCompact(){
        delete tableau_;
    }
};

template < typename T >
TableauCompact<T,1>::TableauCompact():size_(0),tableau_(nullptr){}


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
class TableauSlice/*<T,DIMENSION>*/ /*: public TableauCompact<T,DIMENSION>*/{
public:
    TableauSlice();
    // TableauSlice(TableauSlice&)
    // TableauSlice(TableauSlice&&)



    ~TableauSlice();
};

template < typename T>
class TableauSlice < T, 1 >/* : public TableauCompact<T>*/{
public:
    TableauSlice();
    ~TableauSlice();
    
};









#endif