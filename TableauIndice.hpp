#ifndef _TableauIndice_H_
#define _TableauIndice_H_

#include "TableauCompact.hpp"

template < typename T, std::size_t DIMENSION>
class TableauCompact;

template < typename T,std::size_t DIMENSION, std::size_t DIM>
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

    //TableauIndice<T,DIMENSION-1,DIM> tableau = 

    return &TableauIndice<T,DIMENSION-1,DIM>(tableau_,decalage,tailles,sous_tailles);
} 



template < typename T,std::size_t DIM>
class TableauIndice < T,0 ,DIM>{
public:
    TableauIndice(TableauCompact<T,DIM>*,std::size_t,int*,int*);
    //~TableauIndice();

    T get(){
        return tableau_->get_offset(decalage_);
    }

    void set(T  valeur){
        tableau_->set_offset(decalage_,valeur);
    }

    T& operator=(const T& valeur){this->set(valeur);return valeur;}

    // Opéateur de cast
    operator T(){return get();}

private:
    TableauCompact<T,DIM>* tableau_;
    std::size_t decalage_;
};

// Constructeur
template < typename T,std::size_t DIM>
TableauIndice<T,0,DIM>::TableauIndice(TableauCompact<T,DIM>* tableau,std::size_t decalage,int*,int*):decalage_(decalage){
    tableau_ = tableau;
}


#endif