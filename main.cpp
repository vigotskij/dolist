#ifndef DOLIST_H
	#include "dolist.h"
#endif
#include <stdlib> // for 'system( "pause" )' only.
#include <iostream>
#include "dolist.temp.spec.h"

int main( int argv , char* argc[] ){
	IList<char*> *list = factoryList<char*>() ;

	list->insert( "hola" ) ;
	std::cout << list->extractByValue( "hola" ) << std::endl ;
	list->insert( "chau" ) ;
	list->insert( "gablgabl" ) ;
	std::cout << list->indexOf( "chau" ) << std::endl ;
	std::cout << list->extractFirst() << std::endl ;
	std::cout << list->extractFirst() << std::endl ;

	system("pause") ; // only line dependent of stdlib ;

	delete list ;
	return 17 ;
}
