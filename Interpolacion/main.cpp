//
//  main.cpp
//  Interpolacion
//
//  Melissa Janet Treviño Caballero     A00816715
//  María Paula Anastás Benavides       A00817285
//  Luis Felipe Salazar Valenzuela      A00817158
//
//  Created by Melissa Trevino on 3/14/16.
//  Copyright © 2016 Melissa Trevino. All rights reserved.


#include <iostream>
#include <cmath>
using namespace std;

// Función para validar que cada par sea distinto.
bool EncuentraPar(int iX, int iY, int iMat[10][2], int iCont)
{
    for (int iR = 0; iR < iCont; iR++)
    {
        if (iMat[iR][0] == iX && iMat[iR][1] == iY)
        {
            cout << "ERROR: los valores de x,y ya existen." << endl;
            return false;
        }
        else if (iMat[iR][0] == iX)
        {
            cout << "ERROR: el valor de x ya existe." << endl;
            return false;
        }
        else if (iMat[iR][1] == iY)
        {
            cout << "ERROR: el valor de y ya existe." << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    // Declaración de variables.
    int iCantPares, iX, iY;
    int iMatPares[10][2];
    
    cout << "¿Cuántas parejas deseas interpolar? \t";
    cin >> iCantPares;

    
    // Ingresamos las parejas de x,y.
    for (int iCont = 0; iCont < iCantPares; iCont++)
    {
        cout << "Ingrese las coordenadas x,y \t";
        cin >> iX >> iY;
        
        // Si no se encuentran repeticiones
        if (EncuentraPar(iX, iY, iMatPares, iCont))
        {
            // Guardamos los valores en la matriz de pares.
            iMatPares[iCont][0] = iX;
            iMatPares[iCont][1] = iY;
        }
        else
            iCont--;    // Decrementamos el contador para no contar este ciclo específico.
    }
    
    // El grado de la matriz es de iCantPares - 1.
    int iGrado = iCantPares - 1;
    
    // Esta será la matriz donde guardemos las ecuaciones a plantear.
    int iMat[10][10];
    
    // iR es el renglón
    for (int iR = 0; iR < iCantPares; iR++)
    {
        // iC es la columna
        for (int iC = 0; iC <= iCantPares; iC++)
        {
            // Esta es la constante a la que se iguala al final, o sea la coordenada y.
            if (iC == iCantPares)
                iMat[iR][iC] = iMatPares[iR][1];
            else
            {
                // Obtenemos la coordenada x correspondiente.
                iX = iMatPares[iR][0];
                
                // Si es la incógnita a0, se guarda la misma x.
                if (iC == 0)
                    iMat[iR][iC] = 1;
                
                // Se guardan los valores de x a la potenica según la columna para las demás constantes.
                else
                    iMat[iR][iC] = pow(iX, iC);
            }
        }
    }
    
    // Declaración de variables para el método de Montante.
    int  iMat2[iCantPares][iCantPares+1], iPivote, iPivoteAnt = 1, iIter = 0;
    int iRenglon[10];
    double dRespuestas[10];
    bool bStat = true;
    int iREN = iCantPares;
    int iCOL = iCantPares+1;
    
    // Se hace una iteración por cada renglón de la matriz (cada ecuación)
    while(iIter < iREN)
    {
        
        // Sacamos el pivote
        iPivote = iMat[iIter][iIter];
        
        // Mientras el pivote valga 0, intercambiamos renglones
        while (iPivote == 0)
        {
            // Se intercambian renglones
            for(int iC = 0; iC < iCOL; iC++) {
                iRenglon[iC] = iMat[iIter + 1][iC];
                iMat[iIter + 1][iC] = iMat[iIter][iC];
                iMat[iIter][iC] = iRenglon[iC];
            }
            
            // Volvemos a sacar pivote
            iPivote = iMat[iIter][iIter];
            
            // Si no se encuentra un pivote diferente a 0, solución única no tiene.
            if(iPivote == 0)
            {
                // Aquí checamos si no tiene solución o tiene un número infinito de soluciones.
                for(int i = 0; i < iCantPares; i++)
                {
                    double resp;
                    if (iMat[i][i] == 0)
                    {
                        if (iMat[i][i+1] != 0)
                            break;
                        cout << "No hay solución." << endl;
                        return 0;
                    }
                    resp = iMat[i][iCOL-1] * 1.0 / iMat[i][i];
                    dRespuestas[i] = resp;
                }
                
                cout << "Hay número infinito de soluciones" << endl;
                bStat = false;
                return 0;
            }
        }
        
        // Pasamos el renglón de la matriz a una matriz nueva.
        for(int iC = 0; iC < iCOL; iC++)
            iMat2[iIter][iC] = iMat[iIter][iC];
        
        // Ponemos 0s en lo faltante de la columna del pivote.
        for(int iR = 0; iR < iREN; iR++)
        {
            if(iIter != iR)
                iMat2[iR][iIter] = 0;
        }
        
        // Sacar el valor de la posición según la matriz anterior.
        for(int iR = 0; iR < iREN; iR++)
        {
            for(int iC = 0; iC < iCOL; iC++)
            {
                if(iR != iIter)
                {
                    if( iC != iIter)
                        iMat2[iR][iC] = (((iMat[iR][iC] * iPivote) - (iMat[iIter][iC] * iMat[iR][iIter])) / iPivoteAnt);
                }
            }
        }
        
        iIter++;
        iPivoteAnt = iPivote;
        
        // Actualizamos la matriz copiando la auxiliar.
        for(int iR = 0; iR < iREN; iR++)
        {
            for(int iC = 0; iC < iCOL; iC++)
                iMat[iR][iC] = iMat2[iR][iC];
        }
    }
    
    cout << "Como fueron "<< iCantPares << " datos, entonces por el método Polinomio Único de Interpolación," << endl;
    cout << "el polinomio obtenido es de grado " << iGrado << " y corresponde a:" << endl;
    cout << "P" << iGrado << "(x) = ";
    double resp = iMat[0][iCOL-1] * 1.0 / iMat[0][0];
    if (resp != 0)
        cout << resp;
    
    for(int i = 1; i < iCantPares; i++)
    {
        resp = iMat[i][iCOL-1] * 1.0 / iMat[i][i];
        if (resp == 0)
        {
            // No mostrarlo
        }
        else if (resp == 1)
        {
            // Solo mostrar la x's.
            if (i == 1)
                cout << "x^" << i;
            else
                cout << " + x^" << i;
        }
        else if (resp < 0)
            cout << " - " << abs(resp) << "x^" << i;
        else
            cout << " + " << resp << "x^" << i;
    }
    cout << endl;
    
    return 0;
}