#include <iostream>
#include "Tableau.hpp"
#include <assert.h>

int main(){ //int argc, char const *argv[] because they are unused
	int arraysTest[5] = {1,2,3,4,5};
	std::size_t taille = 5; 
	std::cout<<"Adresse aray: "<<arraysTest<<" Taille: "<<(sizeof(arraysTest)/sizeof(*arraysTest))<<std::endl;
	//TEST1
	Tableau<int> Tab = Tableau<int>(taille,arraysTest);
	// TEST 2
	Tableau<int> Tabl(taille); // je comprends pas très bien
	Tabl = Tableau<int>(taille,arraysTest); // ok
	
	std::cout << Tabl;
	int arraysTest2[4] = {1,3,4,5};
	const std::size_t number = 4; // const cause template variable can't change
	// TableauMulti (T* tableauDimensions)
	TableauMulti<int,number> test = TableauMulti<int,number>(arraysTest2);
	std::cout << test;
	//assert(false);
	std::cout<<"Problème Destructeurs"<<std::endl;
	return 0;
}