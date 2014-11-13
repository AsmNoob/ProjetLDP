#ifndef _TableauMulti_H_
#define _TableauMulti_H_

#include <cstddef>  // nullptr_t, ptrdiff_t, size_t
#include <cstdlib>  // abs, div, rand...
#include <iostream> // cin, cout...


template < typename T, size_t Dimension = 1>
class TableauMulti{
  T tableau [Dimension];  // tableau qui va contenir tous les autres tableaux
public:
  inline T operator[] (ptrdiff_t ptr) const;
  inline T& operator[] (ptrdiff_t ptr);
  TableauMulti () = default;
  TableauMulti (size_t = 1);        //  QUESTION: pourquoi mettre size_t dimension = 1 provoque des erreurs de déclaration et un shadow du template						 // constructeur initialisant
  TableauMulti (const TableauMulti<T,Dimension>& );                   // constructeur de copie
  TableauMulti (TableauMulti<T,Dimension>&&);                        // constructeur de transfert
  TableauMulti& operator= (const TableauMulti<T,Dimension>& );        // opérateur d'assignation
  TableauMulti& operator= (TableauMulti<T,Dimension>&&);             // opérateur de transfert
  ~TableauMulti ();               // destructeur
};

#endif