#include"PQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


void UpdateDown( PQItem* pTab, int l, int p );  // update heap down between index l and p  <--- modified Update() from HeapSort 
void UpdateUp( PQItem* pTab, int l, int p );    // update heap up between index l and p  



//dopisac parametry!!!!
PQueue* PCreate( int nSize )  // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad   /// parametr - zadany rozmiar
{
	// sprawdzamy czy rozmiar kolejki jest poprawny
	if( nSize <= 0 )
	{
		return NULL;
	}
	// Alokacja pamiêci dla struktury kolejki
	PQueue* pQueue = ( PQueue* ) calloc( 1, sizeof( PQueue ));
		if( pQueue == NULL )
		{
			return NULL;
		}
		// alokacja pamiêci dla tablicy elementów kolejki
		pQueue->pPQueue = ( PQItem* ) calloc( nSize, sizeof( PQItem* ) );
		if( pQueue->pPQueue == NULL )
		{
			return NULL;
		}
		pQueue->nPQSize = nSize;
		return pQueue;  // zwracamy  wskaŸnik do utworzonej kolejki

}



int PQisEmpty( PQueue* QUEUE )  // zwraca 0 -nie pusta lub 1 - kolejka pusta
{
	return  !QUEUE || !( QUEUE->nPQCurrSize );
}




int PQSize( PQueue* QUEUE ) // zwraca ilosc elementow w kolejce    /// zwraca nPGCurrSize
{
	/*
	if( QUEUE == NULL )
	{
		return PRIOR_ERROR;
	}
	return QUEUE->nPQCurrSize;
	*/
	return ( QUEUE == NULL ) ? PRIOR_ERROR : QUEUE->nPQCurrSize;
}



int PQMaxPrior( PQueue* QUEUE )  // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR   /// priorytet zerowego elementu 
{
	/*
	// czy pusta 
	if( PQisEmpty( QUEUE ) )
		return PRIOR_ERROR;
	else
		return QUEUE->pPQueue[0].nPrior;  // zwracamy prioryteet zerowego elementu 
		*/
	return ( PQisEmpty( QUEUE ) )? PRIOR_ERROR : QUEUE->pPQueue[ 0 ].nPrior; // zwracamy prioryteet zerowego elementu 
}

int PQEnqueue( PQueue* QUEUE, PQINFO* pInfo, int nPrior )
{
	//czy pusta
	if( !QUEUE )
	{
		return 0;  // jesli nie istnieje kolejka to zwracamy blad
	}
	// sprawdzamy czy pelna
	int currentSize = PQSize( QUEUE ); // aktualna liczba elementów w kolejce
	if( currentSize == QUEUE->nPQSize )
	{
		return 0; // jesli pelna to zwracamy 0 
	}

	
	QUEUE->pPQueue[ currentSize ].nPrior = nPrior; // przypisujemy  priorytet do pola nPrior na pozycji currentSize w tablicy pPQueue     
	QUEUE->pPQueue[ currentSize ].pInfo = pInfo;   // przypisujemy  wsk pInfo do pola pInfo el na pozycji currentSize w tab pPQueue

	if( currentSize > 0 )
	{
		UpdateUp( QUEUE->pPQueue, 0, currentSize );  // aktualizacja kolejki w górê po dodaniu nowego elementu
	}

	QUEUE->nPQCurrSize++;  // aktualna liczba el zwiekszona o 1
	return 1;
}



PQINFO* PQDequeue( PQueue* QUEUE ) // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
{
	// sprawdzamy  czy kolejka jest pusta
	if(  PQisEmpty(QUEUE)  ) // +
	{
		return NULL;
	}
	int a = --QUEUE->nPQCurrSize;  // Zmniejszenie aktualnej liczby elementów w kolejce o 1 i przypisanie do zmiennej a
	PQINFO* res = QUEUE->pPQueue[0].pInfo; // przypisujemy inf do res
	if( a > 0 )
	{
		QUEUE->pPQueue[ 0 ] = QUEUE->pPQueue[a]; // ostatni element kolejki na miejsce korzenia
	}
	memset( QUEUE->pPQueue + a, 0, sizeof( PQItem ) ); // zerujemy pamiec dla elementu który zosta³ usuniêty z kolejki
	if( PQSize( QUEUE ) > 1 )
	{
		UpdateDown( QUEUE->pPQueue, 0, a - 1 ); // aktualizacja kolejki w dó³ po usuniêciu elementu
	}
	return res;
}




void PQClear( PQueue* QUEUE, void( __cdecl* freemem )( const void* ) ) // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura 
                                                                       // do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 
{
	if( !QUEUE || !freemem )
	{
		printf( "Kolejka nie istnieje lub zly adres funkcji\n" );
		return;
	}
	while( ( PQisEmpty( QUEUE ) ) )
		freemem( PQDequeue( QUEUE ) );
}


void PQRelease( PQueue** QUEUE, void( __cdecl* freemem )( const void* ) ) // usuwa cala kolejke, zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto 
                                                                          // wczesniej (czyszczenie kolejki)
{
	if( QUEUE == NULL || *QUEUE == NULL )
	{
		printf( "Kolejka nie istnieje\n" );
	}
	PQClear( *QUEUE, freemem );
	free( ( *QUEUE )->pPQueue );
	free( *QUEUE );
	*QUEUE = NULL;
}


void PQPrint( PQueue* QUEUE, int i, void( __cdecl* printqueue )( const void* )  )  // drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowaæ info uzytkownika 
                                                                                  // przekazac trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach 
                                                                                  // oraz pozycje w  kolejce w kwadratowych nawiasach
{
	if( !QUEUE || i < 0 || !printqueue ) 
	{
		printf( "Nie istnieje kolejka albo podano zbyt mala pozycje  lub nie ma takiej pozycji albo zly adres funkcji \n" );
		return;
	}
	// sprawdzamy  czy indeks przekracza rozmiar kolejki
		if( i >= PQSize( QUEUE ) ) 
		{
			return;
		}
		printqueue( ( const void* ) QUEUE->pPQueue[ i ].pInfo );  // wywo³ujemy printqueue zeby wydrukowaæ inf uzytkownika (przekazane jako wsk pInfo)
		
		// wydrukowanie priorytetu i indeksu elementu
		printf( "Wartosc priorytetu: (%d)\nIndeks elementu: [%d]\n\n", QUEUE->pPQueue[ i ].nPrior, i );
		//rekurencyjnie
		PQPrint( QUEUE, 2 * i + 1, printqueue ); // lewy podrzedny el
		PQPrint( QUEUE, 2 * i + 2, printqueue ); // prawy podrzedny el
	
}

int PQSetPrior( PQueue* QUEUE, PQINFO* pInfo, int nPrior, int( __cdecl* compareFunc )( const void*, const void* ) ) // ustawia nowy priorytet dla zadanej informacji uzytkownika, nie znana struktura informacji, która trzeba 
// wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. 
// Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR /// funkcja jdnolinijkowa i ma wywolac PQsetPrior
{
	return PQsetPrior( QUEUE, PQFind( QUEUE, pInfo, compareFunc ), nPrior );
}



int PQsetPrior( PQueue* QUEUE, int i, int nowyPrior ) // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce 
// (indeks w tablicy). Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 
{
	// sprawdzamy czy istnieje kolejka
	if( PQisEmpty( QUEUE ) ) //+
	{
		return PRIOR_ERROR;
	}

	int StaryPriorytet = PQgetPrior( QUEUE, i ); // bierzemy poporzedni  priorytet elementu na zadanej pozycji
	if( StaryPriorytet != POS_ERROR )
	{
		QUEUE->pPQueue[ i ].nPrior = nowyPrior; // ustawienie nowego priorytetu dla elementu 

		if( StaryPriorytet > nowyPrior )
		{
			UpdateDown( QUEUE->pPQueue, i, PQSize( QUEUE ) - 1 ); // jeœli nowy priorytet jest mniejszy od poprzedniego ->  kolejka w dó³ 
		}
		else if( StaryPriorytet < nowyPrior )
		{
			UpdateUp( QUEUE->pPQueue, 0, i ); // jeœli nowy priorytet jest wiêkszy od poprzedniego -> kolejka  w górê od korzenia 
		}
	}
	return StaryPriorytet;  // zwracamy stry priorytet

}

// zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która 
// trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika 
int PQGetPrior( PQueue* QUEUE, PQINFO* pInfo, int( __cdecl* compareFunc )( const void*, const void* ) )
{
	return PQgetPrior( QUEUE, PQFind( QUEUE, pInfo, compareFunc ) );
}



int PQgetPrior( PQueue* QUEUE, int i ) // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR
{
	if( PQisEmpty( QUEUE ) ) //+
	{
		return PRIOR_ERROR;
	}
	if( i >= 0 && i < PQSize( QUEUE ) )
	{
		return QUEUE->pPQueue[i].nPrior;
	}
	return POS_ERROR;
}

int PQFind( PQueue* QUEUE, PQINFO* pInfo, int( __cdecl* compareFunc )( const void*, const void* ) )// zwraca indeks wyszukiwanej informacji uzytkownika, nie znana struktura informacji uzytkownika dlatego
                                                                                                   // przekazac trzeba funkjce porownujaca informacje uzytkownika
                                                                                                   // Zwaraca POS_ERROR jesli nie ma info w kolejce
{
	
		if( !QUEUE ) {
			return PRIOR_ERROR;
		}

		// sprawdzamy czy funkcja porównuj¹ca jest zdefiniowana
		if( compareFunc == NULL ) {
			return POS_ERROR;
		}

		int queueSize = PQSize( QUEUE ); // pobieramy  rozmiaru kolejki
		for( int i = 0; i < queueSize; i++ )
		{
			// porownujemy 
			if( compareFunc( ( const void* ) pInfo, ( const void* ) QUEUE->pPQueue[ i ].pInfo ) == 0 ) 
			{
				return i; // jesli identyczne, zwracamy indeks znalezionego elementu
			}
		}

		return POS_ERROR;
}



void UpdateDown(  PQItem* pTab, int l, int p )  // update heap down between index l and p  <--- modified Update() from HeapSort 
{
	if( l >= p ) return;  // nie trzeba nic robic wtedy

	int i = l;
	int j = 2 * i + 1;  // indeks pierwszego lewego potomka
	PQItem x = pTab[ i ];

	while( j <= p )
	{
		if( j < p && pTab[ j ].nPrior < pTab[ j + 1 ].nPrior ) j++;  // zwiekszamy j jesli istnieje prawy potomek i ma wiekszy prior niz lewy
		if( x.nPrior >= pTab[ j ].nPrior ) break;  // przerywamy petle jesli prior elementu x jest >= niz prior elementu na pozycji j-tej 
		pTab[ i ] = pTab[ j ];
		i = j;
		j = 2 * i + 1;
	}
	pTab[ i ] = x;  // wstawiamy element 
}



void UpdateUp( PQItem* pTab, int l, int p )   // update heap up between index l and p  
                                               // analog jak w UpdateDown
	                                             // tylko uaktualnienie w gore stogu i jest tylko jeden rodzic 
{
	if( l >= p )return;
	int i = p;
	int j = ( i - 1 ) / 2;
	PQItem x = pTab[ i ];
	while( j >= l && pTab[ j ].nPrior < x.nPrior ) {
		pTab[ i ] = pTab[ j ];
		i = j;
		j = ( i + 1 ) / 2 - 1;  // dzielenie calkowite // bo dla i = 0, j bedzie rowne -1 // bez tego dla i =0 bedzie j= 0 i sie zapetli 
	}
	pTab[ i ] = x;
}




