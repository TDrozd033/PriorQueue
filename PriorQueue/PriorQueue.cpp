#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "PQueue.h"

void QueuePrint( const void* );
int compare( const void*, const void* );
void freemem( const void* );
PQINFO* CreateEl();


#define DEBUG1
#define ROZMIAR 20

int main()
{
  
  srand( ( unsigned ) time( NULL ) );
// wykreowac kolejke 20 - sto elementowa
  PQueue* Kolejka = PCreate( ROZMIAR );
  if( Kolejka == NULL ) // jesli nie udalo sie stworzyc kolejki 
  {
    perror( "Blad podczas kreowania kolejki\n" );
    return -2;
  }
// dodac 6 elementow z roznymi priorytetami i w ró¿nej kolejnosci priorytetów - wydrukowac
  PQINFO* Element1 = CreateEl(); // tworzymy element
  if( Element1 == NULL )
  {
    perror( "Blad podczas kreowania 1 elementu\n" );
    return -8;
  }
  Element1->nKey = 9; // przypisujemy wartosc do klucza
  Element1->pTab[0] = rand() % ROZMIAR; 
  int a = PQEnqueue( Kolejka, Element1, 3 ); // dodajemy element do kolejki 
  if( !a )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 50;
   }
  PQINFO* Element2 = CreateEl();
  if( Element2 == NULL )
  {
    perror( "Blad podczas kreowania 2 elementu\n" );
    return -7;
  }
  Element2->nKey = 2;
  Element2->pTab[0] = rand() % ROZMIAR;
  int b = PQEnqueue( Kolejka, Element2, 2 );
  if( !b )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 51;
  }
  PQINFO* Element3 = CreateEl();
  if( Element3 == NULL )
  {
    perror( "Blad podczas kreowania 3 elementu\n" );
    return -6;
  }
  Element3->nKey = 15;
  Element3->pTab[0] = rand() % ROZMIAR;
  int c = PQEnqueue( Kolejka, Element3, 8 );
  if( !c )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 52;
  }
  PQINFO* Element4 = CreateEl();
  if( Element4 == NULL )
  {
    perror( "Blad podczas kreowania 4 elementu\n" );
    return -5;
  }
  Element4->nKey = 16;
  Element4->pTab[0] = rand() % ROZMIAR;
  int d = PQEnqueue( Kolejka, Element4, 16 );
  if( !d )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 53;
  }
  PQINFO* Element5 = CreateEl();
  if( Element5 == NULL )
  {
    perror( "Blad podczas kreowania 5 elementu\n" );
    return -4;
  }
  Element5->nKey = 7;
  Element5->pTab[0] = rand() % ROZMIAR;
  int e = PQEnqueue( Kolejka, Element5, 19 );
  if( !e )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 54;
  }
  PQINFO* Element6 = CreateEl();
  if( Element6 == NULL )
  {
    perror( "Blad podczas kreowania 6 elementu\n" );
    return -9;
  }
  Element6->nKey = 11;
  Element6->pTab[0] = rand() % ROZMIAR;
  int f = PQEnqueue( Kolejka, Element6, 4 );
  if( !f )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 55;
  }
#ifdef DEBUG1
  printf( "Po dodaniu 6 elementow:\n\n" );
  PQPrint( Kolejka, 0 , QueuePrint );
  printf( "\n" );
#endif

// usunac z kolejki( z najwiekszym priorytetem ) - wydrukowac
   //PQDequeue ( Kolejka);
  
 PQINFO* x = PQDequeue( Kolejka ); // usuwamy 
 if( !x )
 {
   perror( "Blad podczas usuwania elementu \n" );
  // return -12;
 }
 else
 {
   printf( "Klucz usunietego: %d\n", x->nKey );
   freemem( x ); // 
 }
#ifdef DEBUG1
  printf( "Wyglad kolejki po  usunieciu 1 elementu:\n\n" );
  PQPrint( Kolejka, 0 , QueuePrint ); // wypisujemy
  printf( "\n" );
#endif

// dodac dwa elementy - wydrukowac
  PQINFO* nowyElement1 = CreateEl(); // dodajemy 1 element
  if( nowyElement1 == NULL )
  {
    perror( "Blad podczas kreowania nowego elementu  elementu\n" );
    return -10;
  }
  nowyElement1->nKey = 45;
  nowyElement1->pTab[0] = rand () % 100 + 1;
  int g = PQEnqueue( Kolejka, nowyElement1, 87 );
  if( !g )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 57;
  }
  PQINFO* nowyElement2 = CreateEl(); // drugi el
  if( nowyElement2 == NULL )
  {
    perror( "Blad podczas kreowania 2 nowego elementu  elementu\n" );
    return -11;
  }
  nowyElement2->nKey = 69;
  nowyElement2->pTab[0] = rand() % 100 + 1;
  int h = PQEnqueue( Kolejka, nowyElement2, 66 );
  if( !h )
  {
    printf( "Blad podczas sodawania elementu\n" );
    return 59;
  }
#ifdef DEBUG1
  printf( "Po dodaniu  kolejnych 2 elementow:\n\n" );
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
#endif



  //

  //tam gdzie setprior zapamietac wynnik czy PRIORERROR jak nie to blad zmiany priorytetu
  // 
  // // przy find 2 bledy 
  // wyszukac jeden el 
  /*
  PQINFO* SzukanyElement = CreateEl(); // tworzymy el
  SzukanyElement->nKey = 32;
  SzukanyElement->pTab[ 0 ] = 54;
  PQEnqueue( Kolejka, SzukanyElement, 5 );
  */
  /*
  int wyszukiwanie = PQFind( Kolejka, nowyElement1, compare );
  if( wyszukiwanie )
  {
    printf( "Szukany element: Klucz: %d, Pozycja: [%d]\n\n", nowyElement1->nKey, nowyElement1->pTab[ 0 ] );
  }
  */
  // zwiekszyc mu priorytet( unikalny ) - wydrukowac
  int res = PQFind( Kolejka, nowyElement1, compare );
  if( res == POS_ERROR || res == PRIOR_ERROR )
  {
    printf( "Blad podczas wyszukiwania\n" );
    //return 54;
  }
  else
  {
    printf( "Szukany element: Klucz: %d, Pozycja: [%d]\n\n", nowyElement1->nKey, nowyElement1->pTab[ 0 ] );
  }
  int set = PQSetPrior( Kolejka, nowyElement1, 150, compare );
  if( set == PRIOR_ERROR )
  {
    printf( "Error - PQSetPrior\n" );
   // return 12;
 }
  else
  {
    printf( "Poprzedni priorytet: %d\n", set );
  }
  
  //printf( "%d", x );
#ifdef DEBUG1
  printf( "Po zwiekszeniu priorytetu jednego elementu: \n\n" );
  PQPrint( Kolejka,0, QueuePrint );
  printf( "\n" );
#endif





  // zmniejszyc priorytet innemu elementowi( unikalny ) - wydrukowac
  set = PQSetPrior( Kolejka, nowyElement2, -8, compare );
  if( set == PRIOR_ERROR )
  {
    printf( "Error - PQSetPrior\n" );
    // return 12;
  }
  else
  {
    printf( "Poprzedni priorytet: %d\n", set );
  }
  /*
  PQINFO* SzukanyElement2 = CreateEl();
  SzukanyElement2->nKey = 44;
  SzukanyElement2->pTab[ 0 ] = 61;
  PQEnqueue( Kolejka, SzukanyElement2, 6 );
  */
  //PQSetPrior( Kolejka, SzukanyElement2, -8, compare );
#ifdef DEBUG1
  printf( "Kolejka po zmniejszeniu priorytetu jednego elementu:\n\n" );
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
#endif

  /*
  // wyszukac jeden elem
  // zwiekszyc mu priorytet( unikalny ) - wydrukowac
  PQSetPrior( Kolejka, nowyElement1, 150, compare );
  #ifdef DEBUG1
  printf( "Po zwiekszeniu priorytetu jednego elementu: \n\n" );
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
  #endif


  // zmniejszyc priorytet innemu elementowi( unikalny ) - wydrukowac
    PQSetPrior( Kolejka, nowyElement2, -8, compare );
    #ifdef DEBUG1
    printf( "Kolejka po zmniejszeniu priorytetu jednego elementu:\n\n" );
    PQPrint( Kolejka, 0, QueuePrint );
    printf( "\n" );
    #endif
    */


  // przetestowac jak bedzie sie zachowywac modul jesli powtorza sie priorytety niektorych elementow
// ( zmienic priorytet np na maksymalny - powtorzy sie i sciagnac dwa razy, po kazdym drukowanie )
 set =  PQSetPrior( Kolejka, Element1, PQMaxPrior( Kolejka ), compare );
  if( set == PRIOR_ERROR )
  {
    printf( "Error - PQSetPrior\n" );
    // return 12;
  }
  else
  {
    printf( "Poprzedni priorytet: %d\n", set );
  }
#ifdef DEBUG1
  printf( "Po powtorzeniu sie maksymalnego priorytetu:\n\n" );
  
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
#endif

  //PQDequeue( Kolejka ); // sciagamy 
  //sciagamy
  PQINFO* y = PQDequeue( Kolejka ); // usuwamy 
  if( !y )
  {
    perror( "Blad podczas usuwania elementu \n" );
    //return -13;
  }
  else 
  {
    printf( "Klucz usunietego: %d\n", y->nKey );
    freemem( y ); // 
  }
#ifdef DEBUG1
  printf( "Wyglad kolejki po pierwszym sciagnieciu: \n\n" );
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
#endif
  PQINFO* z = PQDequeue( Kolejka ); // usuwamy 
  if( !z )
  {
    perror( "Blad podczas usuwania elementu 2 \n" );
   // return -14;
  }
  else 
  {
    printf( "Klucz usunietego: %d\n", z->nKey );
    freemem( z );
  }
 
 // PQDequeue( Kolejka ); // sciagamy 2 raz
#ifdef DEBUG1
  printf( "Wyglad kolejki po drugim sciagnieciu:\n\n" );
  PQPrint( Kolejka, 0, QueuePrint );
  printf( "\n" );
#endif


  // usunac cala kolejke
  PQRelease( &Kolejka, freemem );
}




void QueuePrint( const void* pTab )
{
  // sprawdzamy  czy wskaŸnik na tablicê jest niepusty
  if( pTab == NULL ) return;
  // rzutujemy wsk na PQINFO
  PQINFO* x = ( PQINFO* ) pTab;
  printf( "Klucz: %d\t element tablicy: %d\n", x->nKey, x->pTab[0] );
}

int compare( const void* number1, const void* number2 )
{
  // porownujemy 
  if( ( (PQINFO* ) number1)->nKey > ( (PQINFO*) number2)->nKey ) return 1;
  if( ( (PQINFO*) number1)->nKey < ( (PQINFO*) number2)->nKey ) return -1;
  return 0;
}



void freemem( const void* Info )
{
  // rzutujemy wsk na PQINFO*
  PQINFO* pInfo = ( PQINFO* ) Info;
  //zwalniamy pamiec dla tablicy pTab
  free( pInfo->pTab );
  // zwalniamy dla struktury PQINFO
  free( pInfo );
  Info = NULL;
}



PQINFO* CreateEl()
{
  // alokacja dla struktury PQINFO
  PQINFO* ptr = (PQINFO*) calloc( 1, sizeof(PQINFO) );
  if( ptr == NULL )
  {
    printf( "Problem 1 z alokacja pamieci w funkcji CreateEl()\n " );
    return NULL;
  }
  // alokacja dla tablicy pTab
  ptr->pTab = (int*) calloc( 2, sizeof(int) );
  if( !( ptr->pTab ) )
  {
    // jeœli alokacja  nie powiedzie siê to  zwalniamy  zaalokowan¹ pamiêæ 
    printf( "Problem 2 z alokacja pamieci w funkcji CreateEl()\n " );
    return NULL;
  }
  // jesli obie alokacje siê powiodly to  zwracany jest wskaŸnik ptr
  return ptr;
}








/*
Kolejka priorytetowa jest kolejk¹, w której elementy s¹ u³o¿one nie w kolejnoœci wprowadzania,
lecz w kolejnoœci priorytetu. Ka¿dy element kolejki posiada dodatkowe pole prio, w którym przechowuje swój priorytet – czyli wa¿noœæ.
Gwarantuje to pobieranie z kolejki jako pierwszych elementów o najwy¿szym priorytecie. 
Elementy o priorytetach ni¿szych zostan¹ pobrane dopiero wtedy, gdy zostan¹ usuniête wszystkie elementy o priorytetach wy¿szych.


*/





