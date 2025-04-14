#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int	main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* cloud = new Character("Cloud");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	cloud->equip(tmp);
	tmp = src->createMateria("cure");
	cloud->equip(tmp);

	ICharacter* aerith = new Character("Aerith");

	tmp = src->createMateria("cure");
	aerith->equip(tmp);
	aerith->equip(src->createMateria("ice"));

	cloud->use(0, *aerith);
	cloud->use(1, *cloud);
	cloud->use(3, *cloud);
	//cloud->use(6, *cloud);
	aerith->use(0, *cloud);
	aerith->use(1, *cloud);
	//aerith->use(5, *cloud);
	aerith->unequip(0);
	aerith->use(0, *aerith);
	aerith->equip(src->createMateria("cure"));
	aerith->use(0, *aerith);

	delete aerith;
	delete cloud;
	delete src;

	return 0;
}
