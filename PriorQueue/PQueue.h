#pragma once
#include "global.h"
#include <limits.h>
// zdefiniowac dwie stale:
//   - PRIOR_ERROR  jako minimalna wartosc calkowita
#define PRIOR_ERROR INT_MIN
//   - POS_ERROR    jako wartosc ujemna np -1 (indeks tablicy jakiego nie ma!)
#define POS_ERROR -1


typedef struct tagPQItem   // zachowac oryginalne nazwy!!!!!!  
{
  // pInfo;       // Ptr to user info  
  PQINFO* pInfo;
    // nPrior;      // prior value (int) for the user info  
    int nPrior;
} PQItem;         // type of the queue item


typedef struct   // zachowac oryginalne nazwy!!!!!!
{
  // pPQueue     // kolejka realizowana w postaci stogu  (dynamiczna tablica)
  PQItem* pPQueue;
  // nPQSize      // rozmiar calkowity kolejki priorytetowej
  int nPQSize;
  // nPQCurrSize  // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 
  int nPQCurrSize;

} PQueue;


//dopisac parametry!!!!
PQueue* PCreate( int nSize );  // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad   /// parametr - zadany rozmiar

int PQisEmpty( PQueue* QUEUE );  // zwraca 0 -nie pusta lub 1 - kolejka pusta

int PQSize( PQueue* QUEUE ); // zwraca ilosc elementow w kolejce    /// zwraca nPGCurrSize

int PQMaxPrior( PQueue* QUEUE );  // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR   /// priorytet zerowego elementu 

int PQEnqueue( PQueue* QUEUE, PQINFO* pInfo, int nPrior ); // wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)


PQINFO* PQDequeue( PQueue* QUEUE ); // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie

void PQClear( PQueue* QUEUE, void( __cdecl* freemem )( const void* ) ); // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura 
                                                                       // do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 


void PQRelease( PQueue** QUEUE, void( __cdecl* freemem )( const void* ) ); // usuwa cala kolejke, zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto 
                                                                            // wczesniej (czyszczenie kolejki)

void PQPrint( PQueue* QUEUE,int i, void( __cdecl* printqueue )( const void* ) );  // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika 
                                                                                    // przekazac trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach 
                                                                                    // oraz pozycje w  kolejce w kwadratowych nawiasach


int PQSetPrior( PQueue* QUEUE, PQINFO* pInfo, int nPrior, int( __cdecl* compareFunc )( const void*, const void* ) );
// ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba                                                                                                                  
// wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. 
// Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR /// funkcja jdnolinijkowa i ma wywolac PQsetPrior

int PQsetPrior( PQueue* QUEUE, int i, int nPrior );
// ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce 
// (indeks w tablicy). Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 

int PQGetPrior( PQueue* QUEUE, PQINFO* pInfo, int( __cdecl* compareFunc )( const void*, const void* ) );
// zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która 
// trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  
 
int PQgetPrior( PQueue* QUEUE, int i );  // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR

int PQFind( PQueue* QUEUE, PQINFO* pInfo, int( __cdecl* compareFunc )( const void*, const void* ) );
// zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
// przekazac trzeba funkjce porownujaca informacje uzytkownika
// Zwaraca POS_ERROR jesli nie ma info w kolejce















