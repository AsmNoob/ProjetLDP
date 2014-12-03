#include <iostream>
#include "Tableau.hpp"
#include <assert.h>

int main(){ //int argc, char const *argv[] because they are unused
    std::cout<<"//------------Constructeurs--------------//"<<std::endl;
    int arraysTest[5] = {1,2,3,4,5};
    std::size_t taille = 5;
    std::cout<<"Adresse aray: "<<arraysTest<<" Taille: "<<(sizeof(arraysTest)/sizeof(*arraysTest))<<std::endl;
    //TEST1
    Tableau<int> Tab = Tableau<int>(taille,arraysTest);
    // TEST 2
    Tableau<int> Tabl(taille); // je comprends pas très bien
    Tabl = Tableau<int>(taille,arraysTest); // ok

    std::cout << Tabl;
    int arraysTest2[5] = {5,2,3,4,5};
    const std::size_t number = 5; // const cause template variable can't change
    // TableauMulti (T* tableauDimensions)
    TableauMulti<int,number> test = TableauMulti<int,number>(arraysTest2);
    std::cout << test;
    //assert(false);
    std::cout<<"//--------------Test méthodes GetSize, etc -------------//"<<std::endl;

    std::cout<<"Taille tableauMulti: "<< test.getSize() << std::endl;
    std::cout<<"Taille getALl: "<< test.getSizeAll()<<std::endl;

    std::cout<<"//--------------Test Opérateur[] -------------//"<<std::endl;

    try{
        std::cout<<"Objet Tableau de Tableau Multi[0][0]: "<< test[0]<<std::endl;
    }catch(const std::out_of_range& err){
        std::cout<< err.what() <<std::endl;
    }

    try{
        std::cout<<"Objet Tableau de Tableau Multi[3][2] avant assignation : "<< test[3][2]<<std::endl;
        test[3][2] = 3;
        std::cout<<"Objet Tableau de Tableau Multi[3][2] après assignation: "<< test[3][2]<<std::endl;
    }catch(const std::out_of_range& err){
        std::cout<< err.what() <<std::endl;
    }

    std::cout<<"//--------------Test assignation Tableau-----------------//"<<std::endl;

    std::cout << "Test Affichage complet: " << test << std::endl;

    std::cout<<"Check de la valeur test[0] avant : "<<test[0] << std::endl;
    test[0] = Tab;
    std::cout<<"Check de la valeur test[0] après : "<<test[0] << std::endl;

    std::cout<<"//--------------Problème Destructeurs-----------------//"<<std::endl;
    return 0;
}
