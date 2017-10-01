#ifndef DOLIST_H
	#include "dolist.h"
#endif
#include <stdlib>
#include <iostream>

int main( int argv , char* argc[] ){
	IList<char*> *list = factoryList<char*>() ;

	list->insert( "hola" ) ;
	std::cout << list->extractByValue( "hola" ) << std::endl ;
	list->insert( "chau" ) ;
	std::cout << list->indexOf( "chau" ) << std::endl ;
    std::cout << list->extractFirst() << std::endl ;

	system("pause") ;

	delete list ;
	return 17 ;
}
