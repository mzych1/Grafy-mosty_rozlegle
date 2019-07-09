#include "Graf.h"

int main()
{
	Graf *wejsciowy = new Graf ();//wczytywanie grafu ze standardowego wejscia
	wejsciowy->wypiszMostyRozlegle();
	delete wejsciowy;
			
    return 0;
}

