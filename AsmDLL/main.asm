;-------------------------------------------------------------------------
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
;-------------------------------------------------------------------------
.data
;sta³a rzeczywista równa -3 do obliczeñ zmian prêdkoœci kul
minusthree real4 -3.0

.code

_DllMainCRTStartup PROC 

        mov rax, 1 
        ret

_DllMainCRTStartup ENDP

;------------------------------
;Funkcja calculateSpeeds odblicza prêdkoœci wypadkowe dla zderzeñ dwóch kul.
;Do funkcji przekazywane s¹ dwa parametry: dwie zainicjowane wczeœniej tablice. Pierwsza tablica, domyœlnie pusta, zostaje wype³niona w trakcie dzia³ania programu obliczonymi wartoœciami.
;W drugiej tablicy 11-elementowej znajduj¹ siê parametry potrzebne do obliczenia wypadkowych prêdkoœci.
;S¹ to kolejno odleg³oœæ miêdzy kulami, a nastêpnie pozycja w p³aszczyŸnie X, pozycja w p³aszczyŸnie X, prêdkoœæ X, prêdkoœæ Y oraz œrednica pierwszej kuli, a nastêpnie drugiej.
;Modyfikowane rejestry: rax, rcx, rdx, r11, rip, rsp, efl, xmm(1-2, 4-13).
;Flagi ulegaj¹ce zmianie: ZR.
;Wykorzystanie rejestrów xmm pozwala na ³atwe operowanie na wartoœciach zmiennoprzecinkowych podczas wyliczania wartoœci.
;Tablica z przekazywanymi parametrami obliczeñ nie jest modyfikowana.
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

        ;Zapisanie wspó³rzêdnej X kuli 2
        movss xmm4, dword ptr[rdx+24] 
        ;Obliczenie odgleg³oœci miêdzy kulami w p³aszczyŸnie X
        subss xmm4, dword ptr [rdx + 4] 
        ;Podzielenie odleg³oœci w p³aszczyŸnie X przez odleg³oœæ miêdzy kulami w p³aszczyŸnie XY
        divss xmm4, dword ptr [rdx] 
        ;xmm4 przechowuje wspó³rzêdn¹ X wektora normalnego (normalx)

        ;Zapisanie wspó³rzêdnej Y kuli 2
        movss xmm5, dword ptr[rdx+28] 
        ;Obliczenie odgleg³oœci miêdzy kulami w p³aszczyŸnie Y
        subss xmm5, dword ptr [rdx + 8] 
        ;Podzielenie odleg³oœci w p³aszczyŸnie Y przez odleg³oœæ miêdzy kulami w p³aszczyŸnie XY 
        divss xmm5, dword ptr [rdx] 
        ;xmm5 przechowuje wspó³rzêdn¹ Y wektora normalnego (normaly)

        ;Zapisanie prêdkoœci X 1 kuli
        movss xmm7, dword ptr[rdx+12] 
        ;Pomno¿enie przez sk³adow¹ Y wektora normalnego
        mulss xmm7, xmm5 
        ;Zapisanie prêdkoœci Y 1 kuli
        movss xmm6, dword ptr[rdx+16] 
        ;Pomno¿enie przez sk³adow¹ X wektora normalnego
        mulss xmm6, xmm4 
        ;xmm6 przechowuje wartoœæ iloczynu skalarnego wektora prêdkoœci kuli 1 oraz wektora stycznego 
        subss xmm6, xmm7 

        ;Zapisanie prêdkoœci X 2 kuli
        movss xmm8, dword ptr[rdx+32] 
        ;Pomno¿enie przez sk³adow¹ Y wektora normalnego
        mulss xmm8, xmm5 
        ;Zapisanie prêdkoœci Y 2 kuli
        movss xmm7, dword ptr[rdx+36] 
        ;Pomno¿enie przez sk³adow¹ X wektora normalnego
        mulss xmm7, xmm4 
        ;xmm7 przechowuje wartoœæ iloczynu skalarnego wektora prêdkoœci kuli 2 oraz wektora stycznego 
        subss xmm7, xmm8 

        ;Zapisanie prêdkoœci X 1 kuli
        movss xmm9, dword ptr[rdx+12] 
        ;Pomno¿enie przez sk³adow¹ X wektora normalnego
        mulss xmm9, xmm4 
        ;Zapisanie prêdkoœci Y 1 kuli
        movss xmm8, dword ptr[rdx+16] 
        ;Pomno¿enie przez sk³adow¹ Y wektora normalnego
        mulss xmm8, xmm5 
        ;xmm8 przechowuje wartoœæ iloczynu skalarnego wektora prêdkoœci kuli 1 oraz wektora normalnego
        addss xmm8, xmm9 

        ;Zapisanie prêdkoœci X 2 kuli
        movss xmm10, dword ptr[rdx+32] 
        ;Pomno¿enie przez sk³adow¹ X wektora normalnego
        mulss xmm10, xmm4 
        ;Zapisanie prêdkoœci Y 2 kuli
        movss xmm9, dword ptr[rdx+36] 
        ;Pomno¿enie przez sk³adow¹ Y wektora normalnego
        mulss xmm9, xmm5 
        ;xmm9 przechowuje wartoœæ iloczynu skalarnego wektora prêdkoœci kuli 2 oraz wektora normalnego
        addss xmm9, xmm10 

        ;Zapisanie œrednicy 1 kuli
        movss xmm10, dword ptr[rdx+20] 
        ;Odjêcie œrednicy 2 kuli
        subss xmm10, dword ptr[rdx+40] 
        ;Pomno¿enie otrzymanego wyniku przez iloczyn skalarny kuli 1 oraz wektora normalnego
        mulss xmm10, xmm8 
        ;Zapisanie œrednicy 2 kuli
        movss xmm11, dword ptr[rdx+40]
        ;Pomno¿enie przez iloczyn skalarny kuli 2 oraz wektora normalnego
        mulss xmm11, xmm9 
        ;Pomno¿enie razy dwa przez dodanie wartoœci w rejestrze do siebie samego
        addss xmm11, xmm11 
        ;Dodanie wczeœniej policzonych wartoœci
        addss xmm10, xmm11 
        ;Zapisanie œrednicy 1 kuli
        movss xmm13, dword ptr[rdx+20] 
        ;Zapisanie œrednicy 2 kuli
        addss xmm13, dword ptr[rdx+40] 
        ;Podzielenie otrzymanych danych przez sumê œrednic obu kul, zapisanie pierwszej wartoœci si³y wypadkowej (m1) do rejestru xmm10
        divss xmm10, xmm13 

        ;Zapisanie œrednicy 2 kuli
        movss xmm11, dword ptr[rdx+40] 
        ;Odjêcie œrednicy 1 kuli
        subss xmm11, dword ptr[rdx+40] 
        ;Pomno¿enie otrzymanego wyniku przez iloczyn skalarny kuli 2 oraz wektora normalnego
        mulss xmm11, xmm9 
        ;Zapisanie œrednicy 1 kuli
        movss xmm12, dword ptr[rdx+20]
        ;Pomno¿enie przez iloczyn skalarny kuli 1 oraz wektora normalnego
        mulss xmm12, xmm8 
        ;Pomno¿enie razy dwa przez dodanie wartoœci w rejestrze do siebie samego
        addss xmm12, xmm12 
        ;Dodanie wczeœniej policzonych wartoœci
        addss xmm11, xmm12 
        ;Podzielenie otrzymanych danych przez sumê œrednic obu kul, zapisanie drugiej wartoœci si³y wypadkowej (m2) do rejestru xmm11
        divss xmm11, xmm13 

        ;wyliczenie prêdkoœci X dla kuli 1
        movss xmm0, xmm4
        mulss xmm0, xmm10
        movss xmm1, xmm6
        mulss xmm1, xmm5
        subss xmm0, xmm1

        ;zapisanie otrzymanej wartoœci do tablicy przekazanej do funkcji
        movss dword ptr [rcx], xmm0

        ;wyliczenie prêdkoœci Y dla kuli 1
        movss xmm0, xmm5
        mulss xmm0, xmm10
        movss xmm1, xmm6
        mulss xmm1, xmm4
        addss xmm0, xmm1
        
        ;zapisanie otrzymanej wartoœci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+4], xmm0

        ;wyliczenie prêdkoœci X dla kuli 2
        movss xmm0, xmm4
        mulss xmm0, xmm11
        movss xmm1, xmm7
        mulss xmm1, xmm5
        subss xmm0, xmm1
        
        ;zapisanie otrzymanej wartoœci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+8], xmm0

        ;wyliczenie prêdkoœci Y dla kuli 2
        movss xmm0, xmm5
        mulss xmm0, xmm11
        movss xmm1, xmm7
        mulss xmm1, xmm4
        addss xmm0, xmm1
        
        ;zapisanie otrzymanej wartoœci do tablicy przekazanej do funkcji
        movss dword ptr [rcx+12], xmm0

        ;przywrócenie rbp ze stosu
        pop rbp 
        ;przywrócenie rbp ze stosu
        pop rbx 

        ret ;powrót z procedury

calculateSpeeds endp

;------------------------------
;Funkcja calculateSpeeds odblicza wartoœæ zmiany prêdkoœci dla pojedynczej kuli i zwraca wyliczon¹ wartoœæ do g³ównego programu.
;Do funkcji przekazywane s¹ trzy parametry: prêdkoœæ kuli w p³aszczyŸnie X lub Y, wspó³czynnik tarcia wspólny dla ca³ego programu oraz œrednica kuli.
;Przekazane wartoœci zastaj¹ przemno¿one wzajemnie przez siebie a nastêpnie podzielone przez -3, aby zwracana wartoœæ powodowa³a zmniejszenie prêdkoœci kul.
;Wyliczona wartoœæ jest zwracana za pomoc¹ rejestru xmm0.
;Modyfikowane rejestry: rax, rcx, r11, rip, rsp, rbp, efl, xmm0, xmm1, xmm2.
;Flagi ulegaj¹ce zmianie: ZR.
;------------------------------

updateSpeed proc
        ;pomno¿enie prêdkoœci kuli przez wspó³czynnik tarcia
        mulss xmm0, xmm1 
        ;pomno¿enie wyniku przez œrednicê kuli
        mulss xmm0, xmm2 
        ;podzielenie wyniku przez -3
        divss xmm0, minusthree 
        ret ;powrót z procedury
updateSpeed endp

end
;-------------------------------------------------------------------------
