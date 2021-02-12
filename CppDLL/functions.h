/*;-------------------------------------------------------------------------
; SYMULATOR ZDERZE�
; KRZYSZTOF DEC GR.1
; INFORMATYKA SSI SEMESTR 5 2020/2021
; v.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.1.1 - stworzony interfejs graficzny do obs�ugi programu (14.10.2020)
; v.0.2 - dodanie bibliotek CppDLL oraz AsmDLL do projektu (27.10.2020)
; v.0.3 - implementacja interfejsu graficznego symulacji oraz dodanie podstaw ruchu kul (12.11.2020)
; v.0.3.1 - dodanie obs�ugi wykrywania zderze� oraz tworzenia losowych symulacji (14.11.2020)
; v.0.4 - implementacja mechanizmu odbi� kul od kraw�dzi okna symulacji oraz rozdzielania kul nachodz�cych na siebie (2.12.2020)
; v.0.5 - implementacja algorytmu zderze� mi�dzy kulami w C++ (9.01.2021)
; v.0.5.1 - dodanie si� tarcia do symulacji ruchu kul (10.01.2021)
; v.0.5.2 - dodanie obs�ugi w�tk�w w symulacji zderze� oraz ruchu kul (16.01.2021)
; v.0.6 - implementacja algorytm�w zderze� oraz ruchu kul w asemblerze (5.02.2021)
; v.0.6.1 - dodanie pomiar�w czasu wykonania algorytm�w (7.02.2021)
; v.0.7 - poprawiona implementacja algorytm�w w asemblerze, usprawnienie dzia�ania w trybie Release w VS2019 (11.02.2021)
; v.1.0 - finalna wersja programu zgodna z za�o�eniami projektu (12.02.2021)
;-------------------------------------------------------------------------*/

#ifdef CPPDLL_EXPORTS
	#define CPPDLL_API __declspec(dllexport)
#else
	#define CPPDLL_API __declspec(dllimport)
#endif

/* Funkcja calculateSpeeds odblicza pr�dko�ci wypadkowe dla zderze� dw�ch kul.
* Do funkcji przekazywane s� dwa parametry : 
* speedValues - wska�nik pustej 4-elementowej tablicy, kt�ra zostaje wype�niona warto�ciami pr�dko�ci wypadkowych kul
* parameters - wska�nik tablicy 11-elementowej w kt�rej znajduj� si� parametry potrzebne do obliczenia wypadkowych pr�dko�ci
* S� to kolejno odleg�o�� mi�dzy kulami, a nast�pnie pozycja w p�aszczy�nie X, pozycja w p�aszczy�nie X, pr�dko�� X, pr�dko�� Y oraz �rednica pierwszej kuli, a nast�pnie drugiej.
* Tablica z przekazywanymi parametrami oblicze� nie jest modyfikowana.
*/
extern "C" void CPPDLL_API calculateSpeeds(float* speedValues, float *parameters);

/* Funkcja calculateSpeeds odblicza warto�� zmiany pr�dko�ci dla pojedynczej kuli i zwraca wyliczon� warto�� do g��wnego programu.
* Do funkcji przekazywane s� trzy parametry :
* speed - pr�dko�� kuli w p�aszczy�nie X lub Y
* friction - wsp�czynnik tarcia wsp�lny dla ca�ego programu 
* radius - �rednica kuli
* Przekazane warto�ci zastaj� przemno�one wzajemnie przez siebie a nast�pnie podzielone przez - 3, aby zwracana warto�� powodowa�a zmniejszenie pr�dko�ci kul.
*/
extern "C" float CPPDLL_API updateSpeed(float speed, float friction, float radius);
