 #ifndef ILIST_H
#define ILIST_H
typedef unsigned long Pos ;
typedef unsigned long size ;

template <class ItemType>
class IList{
	public:
		// adding, deleting and replacing functions
		virtual void insert( ItemType value ) = 0 ;
		virtual ItemType extractByValue( const ItemType value ) = 0 ;
		virtual ItemType extractByIndex( const Pos position ) = 0 ;
		virtual ItemType extractFirst( void ) = 0 ;
		virtual ItemType extractLast( void ) = 0 ;
		virtual bool replace( const ItemType valueOut, ItemType valueIn ) = 0 ;
		// capacity and info functions
		virtual bool isEmpty( void ) = 0 ;
		virtual size listSize( void ) = 0 ;
		virtual Pos indexOf( const ItemType value ) = 0 ;
        virtual bool contained( const ItemType value ) = 0 ;
		// manage functions
		virtual void emptyList( void ) = 0 ;
		virtual void cleanRepeated( void ) = 0 ;
        virtual void allocPtr( void ) = 0 ;
};

#endif
