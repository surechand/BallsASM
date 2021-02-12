/*;-------------------------------------------------------------------------
; SYMULATOR ZDERZEÑ
; KRZYSZTOF DEC GR.1
; INFORMATYKA SSI SEMESTR 5 2020/2021
; v.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.1.1 - stworzony interfejs graficzny do obs³ugi programu (14.10.2020)
; v.0.2 - dodanie bibliotek CppDLL oraz AsmDLL do projektu (27.10.2020)
; v.0.3 - implementacja interfejsu graficznego symulacji oraz dodanie podstaw ruchu kul (12.11.2020)
; v.0.3.1 - dodanie obs³ugi wykrywania zderzeñ oraz tworzenia losowych symulacji (14.11.2020)
; v.0.4 - implementacja mechanizmu odbiæ kul od krawêdzi okna symulacji oraz rozdzielania kul nachodz¹cych na siebie (2.12.2020)
; v.0.5 - implementacja algorytmu zderzeñ miêdzy kulami w C++ (9.01.2021)
; v.0.5.1 - dodanie si³ tarcia do symulacji ruchu kul (10.01.2021)
; v.0.5.2 - dodanie obs³ugi w¹tków w symulacji zderzeñ oraz ruchu kul (16.01.2021)
; v.0.6 - implementacja algorytmów zderzeñ oraz ruchu kul w asemblerze (5.02.2021)
; v.0.6.1 - dodanie pomiarów czasu wykonania algorytmów (7.02.2021)
; v.0.7 - poprawiona implementacja algorytmów w asemblerze, usprawnienie dzia³ania w trybie Release w VS2019 (11.02.2021)
; v.1.0 - finalna wersja programu zgodna z za³o¿eniami projektu (12.02.2021)
;-------------------------------------------------------------------------*/

#ifdef CPPDLL_EXPORTS
	#define CPPDLL_API __declspec(dllexport)
#else
	#define CPPDLL_API __declspec(dllimport)
#endif

/* Funkcja calculateSpeeds odblicza prêdkoœci wypadkowe dla zderzeñ dwóch kul.
* Do funkcji przekazywane s¹ dwa parametry : 
* speedValues - wskaŸnik pustej 4-elementowej tablicy, która zostaje wype³niona wartoœciami prêdkoœci wypadkowych kul
* parameters - wskaŸnik tablicy 11-elementowej w której znajduj¹ siê parametry potrzebne do obliczenia wypadkowych prêdkoœci
* S¹ to kolejno odleg³oœæ miêdzy kulami, a nastêpnie pozycja w p³aszczyŸnie X, pozycja w p³aszczyŸnie X, prêdkoœæ X, prêdkoœæ Y oraz œrednica pierwszej kuli, a nastêpnie drugiej.
* Tablica z przekazywanymi parametrami obliczeñ nie jest modyfikowana.
*/
extern "C" void CPPDLL_API calculateSpeeds(float* speedValues, float *parameters);

/* Funkcja calculateSpeeds odblicza wartoœæ zmiany prêdkoœci dla pojedynczej kuli i zwraca wyliczon¹ wartoœæ do g³ównego programu.
* Do funkcji przekazywane s¹ trzy parametry :
* speed - prêdkoœæ kuli w p³aszczyŸnie X lub Y
* friction - wspó³czynnik tarcia wspólny dla ca³ego programu 
* radius - œrednica kuli
* Przekazane wartoœci zastaj¹ przemno¿one wzajemnie przez siebie a nastêpnie podzielone przez - 3, aby zwracana wartoœæ powodowa³a zmniejszenie prêdkoœci kul.
*/
extern "C" float CPPDLL_API updateSpeed(float speed, float friction, float radius);
