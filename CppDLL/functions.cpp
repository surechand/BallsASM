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

#include "pch.h"
#include "functions.h"

void calculateSpeeds(float* speedValues, float* parameters){

    float normalx = (parameters[6] - parameters[1]) / parameters[0]; //Wyznaczenie wsp�rz�dnych wektora normalnego podzielonych podzielonych przez odleg�o�� pomi�dzy kulami
    float normaly = (parameters[7] - parameters[2]) / parameters[0];

    float dpTan1 = parameters[3] * -normaly + parameters[4] * normalx; //Iloczyny skalarne pr�dko�ci kul z wektorem stycznym do obu kul
    float dpTan2 = parameters[8] * -normaly + parameters[9] * normalx;

    float dpNorm1 = parameters[3] * normalx + parameters[4] * normaly; //Iloczyny skalarne pr�dko�ci kul z wektorem normalnym obu kul
    float dpNorm2 = parameters[8] * normalx + parameters[9] * normaly;

    float m1 = (dpNorm1 * (parameters[5] - parameters[10]) + 2.0f * parameters[10] * dpNorm2) / (parameters[5] + parameters[10]); //Wyliczenie si� wypadkowych obu zderze�
    float m2 = (dpNorm2 * (parameters[10] - parameters[5]) + 2.0f * parameters[5] * dpNorm1) / (parameters[5] + parameters[10]);

    speedValues[0] = (-normaly * dpTan1 + normalx * m1);
    speedValues[1] = (normalx * dpTan1 + normaly * m1);
    speedValues[2] = (-normaly * dpTan2 + normalx * m2);
    speedValues[3] = (normalx * dpTan2 + normaly * m2);
}

float updateSpeed(float speed, float friction, float radius) {
    return -speed * friction * radius / 3;
}