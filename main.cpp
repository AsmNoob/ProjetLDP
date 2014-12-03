#include <iostream>
#include "Tableau.hpp"
#include <assert.h>

int main(){ //int argc, char const *argv[] because they are unused

    std::cout<<"//------------Constructeurs--------------//"<<std::endl;
    std::cout<<std::endl<<"1. Constructeur de tableau avec une array"<<std::endl<<std::endl;

    int arraysTest0[5] = {1,2,3,4,5};
    std::size_t taille = 5;

    std::cout<<"Array: [";
    for(size_t i = 0; i < taille; i++){
        std::cout<<arraysTest0[i]<<" ";
    }
    std::cout<<"] et taille: "<<taille<<std::endl;
    
    //TEST1
    Tableau<int> Tab = Tableau<int>(taille,arraysTest0);
    std::cout<< "==> "<<Tab<<std::endl;
    std::cout<<std::endl<<"2. Constructeur Tableau avec une taille: "<< taille<<std::endl<<std::endl;
    // TEST 2
    Tableau<int> Tabl = Tableau<int>(taille); 
    std::cout<<Tabl<<std::endl;
    
    std::cout<<std::endl<<"3. Constructeur de copie Tableau : "<< taille<<std::endl<<std::endl;

    std::cout << "Init Tableau qui va être copié: " << Tab << std::endl;

    Tableau<int> Table = Tableau<int>(Tab);

    std::cout << "Tableau après avoir été par constructeur de copie: " << Table << std::endl;

    std::cout<<std::endl<<"4. Opérateur d'assignation  "<<std::endl<<std::endl;

    int arraysTest1[5] = {1,1,1,1,1};

    Tableau<int> Tablea = Tableau<int>(taille,arraysTest1);

    std::cout<<"Tableau avant assignation: "<<Tablea<<std::endl;

    Tablea = Table;

    std::cout<<"Tableau après assignation: "<<Tablea<<std::endl;

    std::cout<<std::endl<<"5. Opérateur de transfert "<<std::endl<<std::endl;


    
    std::cout<<std::endl<<"X. Constructeur de copie TableauMulti : "<< taille<<std::endl<<std::endl;

    std::cout<<"Test Constructeur Tableau de taille 5, avec une array: "<< Tabl<<std::endl;;
    TableauMulti<char> test0 = TableauMulti<char>();
    std::cout<<"Test Constructeur TableauUlti de taille 1: "<<test0<<std::endl;

    std::cout << Tabl<<std::endl;
    int arraysTest2[5] = {1,2,3,4,5};
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
