#ifndef _TableauCompact_H_
#define _TableauCompact_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...
#inclConstructeursude <stdexcept> // out_of_range,...


template < typename T, size_t DIMENSION = 1>  // 2 paramètres de template: type et nombre de tableaux
class TableauCompact{
private:

    // Attributs


public:

    // Constructeurs

    TableauCompact (){}                                                  // constructeur par défaut
    TableauCompact (T* tableauDimensions){};                             // constructeur par array de tailles des différentes listes
    TableauCompact (const TableauCompact<T,DIMENSION>& tableau){}        // constructeur de copie
    TableauCompact (TableauCompact<T,DIMENSION> &&){}                    // constructeur de transfert
                                                  
    // Destructeur

    ~TableauCompact (){}

    // Surcharge d'opérateurs

    TableauCompact& operator= (const TableauCompact<T,DIMENSION>& );      // opérateur d'assignation
    TableauCompact& operator= (TableauCompact<T,DIMENSION>&&);            // opérateur de transfert
    inline const Tableau<T> operator[] (ptrdiff_t ptr) const;             // opérateur []
    inline Tableau<T>& operator[] (ptrdiff_t ptr);                        // opérateur []

    // Méthodes
    template < typename M, size_t Dim>
    friend std::ostream& operator<< (std::ostream&, const TableauCompact<M,Dim>&);

};

#endif