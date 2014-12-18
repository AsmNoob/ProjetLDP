#ifndef _TableauCompact_H_
#define _TableauCompact_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t (pas sur si inclure si on utilise std::size_t)
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...
#include <stdexcept> // out_of_range,...
#include "TableauIndice.hpp"


// template < typename T, std::size_t DIMENSION = 1 >
// class TableauCompact{};

// -----------------------------------------------------------------------------------------------//

// Pour DIM = 1 créer une spécialisation pour [];


// template < typename T, std::size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
// class TableauCompact{}; // Pas instanciable car on tombe d'office dans une spécialisation




//--------------------------------------------------------------------------------------------//

template < typename T, std::size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
class TableauCompact{
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
    inline const TableauIndice<T,DIMENSION-1,DIMENSION> operator[] (ptrdiff_t) const;             // opérateur []
    inline TableauIndice<T,DIMENSION-1,DIMENSION> operator[] (ptrdiff_t);                        // opérateur []

    // Méthodes
    template < typename M, std::size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauCompact<M,Dim>&);

    void set_offset(int decalage,T valeur){
        tableau_[decalage] = valeur;
    }

    T get_offset(int decalage){
        return tableau_[decalage];
    }

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

    void set_tailleTableau(int taille){
        taille_tableau_ = taille;
    }
private:

    // Attributs

    T* tableau_; // array compacte qui contient toutes les valeurs 
    std::size_t taille_tableau_ = 1; // taille complete de ce tableau en compacté
    int tailles_[DIMENSION]; // array qui contient les tailles de chaque dimension
    int sous_tailles_[DIMENSION]; // contient les tailles des sous-dimensions



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
        tableau_[i] = 0;
        std::cout << " tableau_["<<i<<"]: "<<tableau_[i];
    }
    int valeur_sousTaille = 1;
    std::cout << "MIDDLE"<<std::endl;
    for(std::size_t i = DIMENSION-1; i  > 0; i--){
        std::cout<<"i: "<<i;
        valeur_sousTaille*= tailles_[i];
        sous_tailles_[i-1] = valeur_sousTaille;
    }
    sous_tailles_[DIMENSION-1] = 1;
    std::cout<<std::endl << "\033[0;31mTest sous_tailles_\033[0m" << std::endl;
    for(std::size_t i = 0; i < DIMENSION;i++){
        std::cout << " sous_tailles_["<<i<<"]: "<<sous_tailles_[i];
    }
    
    std::cout<<std::endl << "\033[0;31mFin creation\033[0m" << std::endl;
}

// Destructeur
template <typename T, std::size_t DIMENSION>
TableauCompact<T,DIMENSION>::~TableauCompact(){
    delete[] tableau_;
}


template <typename T, std::size_t DIMENSION>
const TableauIndice<T,DIMENSION-1,DIMENSION> TableauCompact<T,DIMENSION>::operator[] (std::ptrdiff_t ptr) const{
    int decalage = ptr * sous_tailles_[0];
    int tailles[DIMENSION-1];
    int sous_tailles[DIMENSION-1];
    for(std::size_t i = 1; i < DIMENSION; i++){
        tailles[i-1] = tailles_[i];
        sous_tailles[i-1] = sous_tailles_[i];
    }

    return TableauIndice<T,DIMENSION-1, DIMENSION>(this,decalage,tailles,sous_tailles);
}

template < typename T, std::size_t DIMENSION>
TableauIndice<T,DIMENSION-1, DIMENSION> TableauCompact<T,DIMENSION>::operator[] (ptrdiff_t ptr){
    int decalage = ptr * sous_tailles_[0];
    int tailles[DIMENSION-1];
    int sous_tailles[DIMENSION-1];
    for(std::size_t i = 1; i < DIMENSION; i++){
        tailles[i-1] = tailles_[i];
        sous_tailles[i-1] = sous_tailles_[i];
    }

    return TableauIndice<T,DIMENSION-1,DIMENSION>(this,decalage,tailles,sous_tailles);
} 

template < typename M, std::size_t Dim>
std::ostream& operator<< (std::ostream& out, const TableauCompact<M,Dim>& tableau){
    for(std::size_t i = 0; i < tableau.taille_tableau_;i++){
        for(std::size_t j = 0; j < Dim-1;j++){
            if(i % tableau.sous_tailles_[j] == 0){
                out << std::string(Dim - j,'\n');
            }
        }
        out << tableau.get_offset(i);
    }
}

//------------------//
/*template <typename T, std::size_t DIMENSION>
const *TableauCompact<T,DIMENSION-1> TableauCompact<T,DIMENSION>::operator[] (std::ptrdiff_t i) const {
    if(i < 0 or i >= tailles_[0]){
        throw std::out_of_range("TableauCompact: Index out of range");
    }else{
        int nouvelle_tailles[DIMENSION-1];
        int nouvelle_sousTailles[DIMENSION-1];
        std::cout << "test nouvelles array tailles"<< std::endl;
        for(std::size_t j = 0; j < (DIMENSION-1);j++){
            nouvelle_tailles[j] = tailles_[j+1];
            std::cout << "nouvelles_tailles["<<j<<"]: " << nouvelle_tailles[j] << std::endl;
            nouvelle_sousTailles[j] = sous_tailles_[j+1];
            std::cout << "nouvelles_sous_tailles["<<j<<"]: " << nouvelle_sousTailles[j] << std::endl;
        }  
        std::size_t nouvelle_tailleTableau = 1;
        for(std::size_t j = 0; j < DIMENSION-1;j++){
            nouvelle_tailleTableau*= nouvelle_tailles[j];
        }

        TableauCompact<T,DIMENSION-1> *tableau =  new TableauCompact<T,DIMENSION-1>();
        T* copieTableau = new T[nouvelle_tailleTableau];
        for(std::size_t j = i*sous_tailles_[0]; j < i*sous_tailles_[0]+nouvelle_tailleTableau;j++){
            copieTableau[j] = tableau_[j];
        }
        tableau.set_tableau(copieTableau);
        tableau.set_tailles(nouvelle_tailles);
        tableau.set_sousTailles(nouvelle_sousTailles);
        tableau.set_tailleTableau(nouvelle_tailleTableau);

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
    inline const T operator[] (ptrdiff_t) const;          // opérateur []
    inline T& operator[] (ptrdiff_t);                     // opérateur []

    void set_offset(int decalage,T valeur){
        tableau_[decalage] = valeur;
    }

    T get_offset(int decalage){
        return tableau_[decalage];
    }

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

    void set_tailleTableau(int taille){
        size_ = taille;
    }

    // Destructeur
    ~TableauCompact(){
        delete[] tableau_;
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
    for (std::size_t i = 0; i < tableau.size_; ++i){
        out <<(*p++);
        if(i < tableau.size_-1)
            out<<", ";
    }
    out<<" ]";
    return out;
}

// J'AVOUE NE PAS COMPRENDRE EXACTEMENT COMMENT FONCTIONNE LA SIGNATURE D'HERITAGE en regardant les exemples

/*template < typename T,std::size_t DIMENSION, std::size_t DIM>
class TableauIndice{
public:
    TableauIndice(TableauCompact<T,DIM>*,std::size_t,int*,int*);
    // TableauIndice(TableauIndice&)
    // TableauIndice(TableauIndice&&)
    inline const TableauIndice<T,DIMENSION-1,DIM> operator[] (ptrdiff_t) const;          // opérateur []
    inline TableauIndice<T,DIMENSION-1,DIM>& operator[] (ptrdiff_t);                     // opérateur []

    //~TableauIndice();

private:
    TableauCompact<T,DIM>* tableau_;
    std::size_t decalage_;
    int tailles_[DIMENSION];
    int sous_tailles_[DIMENSION];
};

template < typename T, std::size_t DIMENSION,std::size_t DIM>
TableauIndice<T,DIMENSION,DIM>::TableauIndice(TableauCompact<T,DIM>* tableau,std::size_t decalage,int tailles[DIMENSION],int sous_tailles[DIMENSION]):decalage_(decalage){
    tableau_ = tableau;
    for(std::size_t i = 0; i < DIMENSION; i++){
        tailles_[i] = tailles[i];
        sous_tailles_[i] = sous_tailles[i];
    }

}

template < typename T, std::size_t DIMENSION,std::size_t DIM>
const TableauIndice<T,DIMENSION-1, DIM> TableauIndice<T,DIMENSION,DIM>::operator[] (ptrdiff_t ptr) const{
    int decalage = decalage_;
    decalage += ptr * sous_tailles_[0];
    int tailles[DIMENSION-1];
    int sous_tailles[DIMENSION-1];
    for(std::size_t i = 1; i < DIMENSION; i++){
        tailles[i-1] = tailles_[i];
        sous_tailles[i-1] = sous_tailles_[i];
    }

    return TableauIndice<T,DIMENSION-1, DIM>(tableau_,decalage,tailles,sous_tailles);
}          // opérateur []

template < typename T, std::size_t DIMENSION,std::size_t DIM>
TableauIndice<T,DIMENSION-1, DIM>& TableauIndice<T,DIMENSION,DIM>::operator[] (ptrdiff_t ptr){
    int decalage = decalage_;
    decalage += ptr * sous_tailles_[0];
    int tailles[DIMENSION-1];
    int sous_tailles[DIMENSION-1];
    for(std::size_t i = 1; i < DIMENSION; i++){
        tailles[i-1] = tailles_[i];
        sous_tailles[i-1] = sous_tailles_[i];
    }

    return TableauIndice<T,DIMENSION-1,DIM>(tableau_,decalage,tailles,sous_tailles);
} 

template < typename T,std::size_t DIM>
class TableauIndice < T,0 ,DIM>{
public:
    TableauIndice(TableauCompact<T,DIM>*,std::size_t,int*,int*);
    //~TableauIndice();

    T get(){
        return tableau_.get_offset(decalage_);
    }

    void set(T  valeur){
        tableau_.set_offset(decalage_,valeur);
    }

    T& operator=(const T&);

    operator T(){return get();}

private:
    TableauCompact<T,DIM>* tableau_;
    std::size_t decalage_;
};

template < typename T,std::size_t DIM>
TableauIndice<T,0,DIM>::TableauIndice(TableauCompact<T,DIM>* tableau,std::size_t decalage,int*,int*):decalage_(decalage){
    tableau_ = tableau;
}

template < typename T,std::size_t DIM>
T& TableauIndice<T,0,DIM>::operator=(const T& valeur){
    this->set(valeur);
    return valeur;
}*/







#endif
