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

    std::cout<<"Tab: "<<Tab<<std::endl;
    std::cout<<"Table: "<<Table<<std::endl;

    Tab[0] = 3;
    std::cout<<"Changement ..."<<std::endl<<std::endl;

    std::cout<<"Tab: "<<Tab<<std::endl;
    std::cout<<"Table: "<<Table<<std::endl;

    std::cout << "Tableau après avoir été par constructeur de copie: " << Table << std::endl;

    std::cout<<std::endl<<"4. Opérateur d'assignation  "<<std::endl<<std::endl;

    int arraysTest1[5] = {1,1,1,1,1};

    Tableau<int> Tablea = Tableau<int>(taille,arraysTest1);

    std::cout<<"Tableau avant assignation: "<<Tablea<<std::endl;

    Tablea = Table;

    std::cout<<"Tableau après assignation: "<<Tablea<<std::endl;

    std::cout<<std::endl<<"5. Opérateur de transfert "<<std::endl<<std::endl;

    std::cout<<"//------------------------------------------------------------------------------------------//"<<std::endl;
    
    std::cout<<std::endl<<"1. Constructeur TableauMulti par défaut "<<std::endl<<std::endl;

    TableauMulti<int> test0 = TableauMulti<int>();

    std::cout<<"Tableau de dimension 1: "<< test0<<std::endl;

    std::cout<<std::endl<<"2. Constructeur TableauMulti avec une array de tailles "<<std::endl<<std::endl;

    int arraysTest2[5] = {1,2,3,4,5};
    std::cout<<"Array: [";
    for(size_t i = 0; i < taille; i++){
        std::cout<<arraysTest2[i]<<" ";
    }
    std::cout<<"]"<<std::endl;
    const std::size_t number = 5; // const cause template variable can't change
    TableauMulti<int,number> tab = TableauMulti<int,number>(arraysTest2);

    std::cout<<"TableauMulti: "<<tab<<std::endl;

    std::cout<<std::endl<<"3. Constructeur de copie de TableauMulti"<<std::endl<<std::endl;

    TableauMulti<int,number> tabl = TableauMulti<int,number>(tab);


    std::cout<<"tab: "<<tab<<std::endl;
    std::cout<<"tabl: "<<tabl<<std::endl;

    tab[0][0] = 1;
    std::cout<<"Changement ..."<<std::endl<<std::endl;

    std::cout<<"tab: "<<tab<<std::endl;
    std::cout<<"tabl: "<<tabl<<std::endl;

    

    std::cout<<std::endl<<"4. Opérateur d'assignation"<<std::endl<<std::endl;

     std::cout<<"//--------------Test méthodes GetSize DANS OP ASSIGNATION -------------//"<<std::endl;

    std::cout<<"Tableau qui va être assigné (tabl): "<<tabl<<std::endl;

    std::cout<<"Tableau qui utilisé pour la construction par copie (tab): "<<tab<<std::endl;

    TableauMulti<int,number> tablea = TableauMulti<int,number>(tab);



    std::cout<<"Tableau avant assignation(tablea), avant attribution de 3: "<<tablea<<std::endl;
    tablea[3][2] = 3;

    std::cout<<"Tableau avant assignation(tablea): "<<tablea<<std::endl;

    std::cout<<"Tableau que l'on va assigner: "<<tabl<<std::endl;

    tablea = tabl;

    std::cout<<"Tableau après assignation(devenu tabl): "<<tablea<<std::endl;
    
    std::cout<<"//--------------Test méthodes GetSize, etc -------------//"<<std::endl;

    std::cout<<"TableauMulti: "<<tabl<<std::endl;
    std::cout<<"Taille tableauMulti: "<< tabl.getSize() << std::endl;
    std::cout<<"Taille getALl: "<< tabl.getSizeAll()<<std::endl;

    std::cout<<"//--------------Test Opérateur[] -------------//"<<std::endl;

    try{
        std::cout<<"Objet Tableau de Tableau Multi[0][0]: "<< tabl[0]<<std::endl;
    }catch(const std::out_of_range& err){
        std::cout<< err.what() <<std::endl;
    }

    try{
        std::cout<<"Objet Tableau de Tableau Multi[3][2] avant assignation : "<< tabl[3][2]<<std::endl;
        tabl[3][2] = 0;
        std::cout<<"Objet Tableau de Tableau Multi[3][2] après assignation: "<< tabl[3][2]<<std::endl;
    }catch(const std::out_of_range& err){
        std::cout<< err.what() <<std::endl;
    }

    std::cout<<tabl<<std::endl;

    /*std::cout<<"//--------------Test assignation Tableau-----------------//"<<std::endl;

    std::cout << "Test Affichage complet: " << tabl << std::endl;

    std::cout<<"Check de la valeur test[0] avant : "<<tabl[0] << std::endl;
    tabl[0] = Tab;
    std::cout<<"Check de la valeur test[0] après : "<<tabl[0] << std::endl;*/

    std::cout<<"//--------------Problème Destructeurs-----------------//"<<std::endl;
    return 0;
}
