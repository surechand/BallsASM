;-------------------------------------------------------------------------
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
;-------------------------------------------------------------------------
.data
;sta�a rzeczywista r�wna -3 do oblicze� zmian pr�dko�ci kul
minusthree real4 -3.0

.code

_DllMainCRTStartup PROC 

        mov rax, 1 
        ret

_DllMainCRTStartup ENDP

;------------------------------
;Funkcja calculateSpeeds odblicza pr�dko�ci wypadkowe dla zderze� dw�ch kul.
;Do funkcji przekazywane s� dwa parametry: dwie zainicjowane wcze�niej tablice. Pierwsza tablica, domy�lnie pusta, zostaje wype�niona w trakcie dzia�ania programu obliczonymi warto�ciami.
;W drugiej tablicy 11-elementowej znajduj� si� parametry potrzebne do obliczenia wypadkowych pr�dko�ci.
;S� to kolejno odleg�o�� mi�dzy kulami, a nast�pnie pozycja w p�aszczy�nie X, pozycja w p�aszczy�nie X, pr�dko�� X, pr�dko�� Y oraz �rednica pierwszej kuli, a nast�pnie drugiej.
;Modyfikowane rejestry: rax, rcx, rdx, r11, rip, rsp, efl, xmm(1-2, 4-13).
;Flagi ulegaj�ce zmianie: ZR.
;Wykorzystanie rejestr�w xmm pozwala na �atwe operowanie na warto�ciach zmiennoprzecinkowych podczas wyliczania warto�ci.
;Tablica z przekazywanymi parametrami oblicze� nie jest modyfikowana.
;------------------------------

calculateSpeeds proc
        ;opis danych przechowywanych w przekazywanej tablicy 
        ;dword ptr[rdx] ; distance
        ;dword ptr[rdx+4] ;ball1 - posX
        ;dword ptr[rdx+8] ;ball2 - posY
        ;dword ptr[rdx+12] ;ball1 - speedX
        ;dword ptr[rdx+16] ;ball1 - speedY
        ;dword ptr[rdx+20] ;ball1 - radius
        ;dword ptr[rdx+24] ;ball2 - posX
        ;dword ptr[rdx+28] ;ball2 - posY
        ;dword ptr[rdx+32] ;ball2 - speedX
        ;dword ptr[rdx+36] ;ball2 - speedY
        ;dword ptr[rdx+40] ;ball2 - radius

        ;zapisanie rbx na stosie
        push rbx 
        ;zapisanie rbp na stosie
        push rbp 

        ;Zapisanie wsp�rz�dnej X kuli 2
        movss xmm4, dword ptr[rdx+24] 
        ;Obliczenie odgleg�o�ci mi�dzy kulami w p�aszczy�nie X
        subss xmm4, dword ptr [rdx + 4] 
        ;Podzielenie odleg�o�ci w p�aszczy�nie X przez odleg�o�� mi�dzy kulami w p�aszczy�nie XY
        divss xmm4, dword ptr [rdx] 
        ;xmm4 przechowuje wsp�rz�dn� X wektora normalnego (normalx)

        ;Zapisanie wsp�rz�dnej Y kuli 2
        movss xmm5, dword ptr[rdx+28] 
        ;Obliczenie odgleg�o�ci mi�dzy kulami w p�aszczy�nie Y
        subss xmm5, dword ptr [rdx + 8] 
        ;Podzielenie odleg�o�ci w p�aszczy�nie Y przez odleg�o�� mi�dzy kulami w p�aszczy�nie XY 
        divss xmm5, dword ptr [rdx] 
        ;xmm5 przechowuje wsp�rz�dn� Y wektora normalnego (normaly)

        ;Zapisanie pr�dko�ci X 1 kuli
        movss xmm7, dword ptr[rdx+12] 
        ;Pomno�enie przez sk�adow� Y wektora normalnego
        mulss xmm7, xmm5 
        ;Zapisanie pr�dko�ci Y 1 kuli
        movss xmm6, dword ptr[rdx+16] 
        ;Pomno�enie przez sk�adow� X wektora normalnego
        mulss xmm6, xmm4 
        ;xmm6 przechowuje warto�� iloczynu skalarnego wektora pr�dko�ci kuli 1 oraz wektora stycznego 
        subss xmm6, xmm7 

        ;Zapisanie pr�dko�ci X 2 kuli
        movss xmm8, dword ptr[rdx+32] 
        ;Pomno�enie przez sk�adow� Y wektora normalnego
        mulss xmm8, xmm5 
        ;Zapisanie pr�dko�ci Y 2 kuli
        movss xmm7, dword ptr[rdx+36] 
        ;Pomno�enie przez sk�adow� X wektora normalnego
        mulss xmm7, xmm4 
        ;xmm7 przechowuje warto�� iloczynu skalarnego wektora pr�dko�ci kuli 2 oraz wektora stycznego 
        subss xmm7, xmm8 

        ;Zapisanie pr�dko�ci X 1 kuli
        movss xmm9, dword ptr[rdx+12] 
        ;Pomno�enie przez sk�adow� X wektora normalnego
        mulss xmm9, xmm4 
        ;Zapisanie pr�dko�ci Y 1 kuli
        movss xmm8, dword ptr[rdx+16] 
        ;Pomno�enie przez sk�adow� Y wektora normalnego
        mulss xmm8, xmm5 
        ;xmm8 przechowuje warto�� iloczynu skalarnego wektora pr�dko�ci kuli 1 oraz wektora normalnego
        addss xmm8, xmm9 

        ;Zapisanie pr�dko�ci X 2 kuli
        movss xmm10, dword ptr[rdx+32] 
        ;Pomno�enie przez sk�adow� X wektora normalnego
        mulss xmm10, xmm4 
        ;Zapisanie pr�dko�ci Y 2 kuli
        movss xmm9, dword ptr[rdx+36] 
        ;Pomno�enie przez sk�adow� Y wektora normalnego
        mulss xmm9, xmm5 
        ;xmm9 przechowuje warto�� iloczynu skalarnego wektora pr�dko�ci kuli 2 oraz wektora normalnego
        addss xmm9, xmm10 

        ;Zapisanie �rednicy 1 kuli
        movss xmm10, dword ptr[rdx+20] 
        ;Odj�cie �rednicy 2 kuli
        subss xmm10, dword ptr[rdx+40] 
        ;Pomno�enie otrzymanego wyniku przez iloczyn skalarny kuli 1 oraz wektora normalnego
        mulss xmm10, xmm8 
        ;Zapisanie �rednicy 2 kuli
        movss xmm11, dword ptr[rdx+40]
        ;Pomno�enie przez iloczyn skalarny kuli 2 oraz wektora normalnego
        mulss xmm11, xmm9 
        ;Pomno�enie razy dwa przez dodanie warto�ci w rejestrze do siebie samego
        addss xmm11, xmm11 
        ;Dodanie wcze�niej policzonych warto�ci
        addss xmm10, xmm11 
        ;Zapisanie �rednicy 1 kuli
        movss xmm13, dword ptr[rdx+20] 
        ;Zapisanie �rednicy 2 kuli
        addss xmm13, dword ptr[rdx+40] 
        ;Podzielenie otrzymanych danych przez sum� �rednic obu kul, zapisanie pierwszej warto�ci si�y wypadkowej (m1) do rejestru xmm10
        divss xmm10, xmm13 

        ;Zapisanie �rednicy 2 kuli
        movss xmm11, dword ptr[rdx+40] 
        ;Odj�cie �rednicy 1 kuli
        subss xmm11, dword ptr[rdx+40] 
        ;Pomno�enie otrzymanego wyniku przez iloczyn skalarny kuli 2 oraz wektora normalnego
        mulss xmm11, xmm9 
        ;Zapisanie �rednicy 1 kuli
        movss xmm12, dword ptr[rdx+20]
        ;Pomno�enie przez iloczyn skalarny kuli 1 oraz wektora normalnego
        mulss xmm12, xmm8 
        ;Pomno�enie razy dwa przez dodanie warto�ci w rejestrze do siebie samego
        addss xmm12, xmm12 
        ;Dodanie wcze�niej policzonych warto�ci
        addss xmm11, xmm12 
        ;Podzielenie otrzymanych danych przez sum� �rednic obu kul, zapisanie drugiej warto�ci si�y wypadkowej (m2) do rejestru xmm11
        divss xmm11, xmm13 

        ;wyliczenie pr�dko�ci X dla kuli 1
        movss xmm0, xmm4
        mulss xmm0, xmm10
        movss xmm1, xmm6
        mulss xmm1, xmm5
        subss xmm0, xmm1

        ;zapisanie otrzymanej warto�ci do tablicy przekazanej do funkcji
        movss dword ptr [rcx], xmm0

        ;wyliczenie pr�dko�ci Y dla kuli 1
        movss xmm0, xmm5
        mulss xmm0, xmm10
        movss xmm1, xmm6
        mulss xmm1, xmm4
        addss xmm0, xmm1
        
        ;zapisanie otrzymanej warto�ci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+4], xmm0

        ;wyliczenie pr�dko�ci X dla kuli 2
        movss xmm0, xmm4
        mulss xmm0, xmm11
        movss xmm1, xmm7
        mulss xmm1, xmm5
        subss xmm0, xmm1
        
        ;zapisanie otrzymanej warto�ci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+8], xmm0

        ;wyliczenie pr�dko�ci Y dla kuli 2
        movss xmm0, xmm5
        mulss xmm0, xmm11
        movss xmm1, xmm7
        mulss xmm1, xmm4
        addss xmm0, xmm1
        
        ;zapisanie otrzymanej warto�ci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+12], xmm0

        ;przywr�cenie rbp ze stosu
        pop rbp 
        ;przywr�cenie rbp ze stosu
        pop rbx 

        ret ;powr�t z procedury

calculateSpeeds endp

;------------------------------
;Funkcja calculateSpeeds odblicza warto�� zmiany pr�dko�ci dla pojedynczej kuli i zwraca wyliczon� warto�� do g��wnego programu.
;Do funkcji przekazywane s� trzy parametry: pr�dko�� kuli w p�aszczy�nie X lub Y, wsp�czynnik tarcia wsp�lny dla ca�ego programu oraz �rednica kuli.
;Przekazane warto�ci zastaj� przemno�one wzajemnie przez siebie a nast�pnie podzielone przez -3, aby zwracana warto�� powodowa�a zmniejszenie pr�dko�ci kul.
;Wyliczona warto�� jest zwracana za pomoc� rejestru xmm0.
;Modyfikowane rejestry: rax, rcx, r11, rip, rsp, rbp, efl, xmm0, xmm1, xmm2.
;Flagi ulegaj�ce zmianie: ZR.
;------------------------------

updateSpeed proc
        ;pomno�enie pr�dko�ci kuli przez wsp�czynnik tarcia
        mulss xmm0, xmm1 
        ;pomno�enie wyniku przez �rednic� kuli
        mulss xmm0, xmm2 
        ;podzielenie wyniku przez -3
        divss xmm0, minusthree 
        ret ;powr�t z procedury
updateSpeed endp

end
;-------------------------------------------------------------------------
