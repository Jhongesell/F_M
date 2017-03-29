//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el m�todo de diferencias finitas                                              //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// P�gina:   http://www.mmc.geofisica.unam.mx/acl                                           //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los t�rminos de la Licencia P�blica General de GNU seg�n es                         //
// publicada por la Free Software Foundation, bien de la versi�n 2 de                       //
// dicha Licencia o bien (seg�n su elecci�n) de cualquier versi�n                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea �til, pero SIN                   //
// NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. V�ase la                        //
// Licencia P�blica General de GNU para m�s detalles.                                       //
//                                                                                          //
// Deber�a haber recibido una copia de la Licencia P�blica General junto                    //
// con este programa. Si no ha sido as�, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


#include "FDM1D.hpp"

/// Establece las condiciones de frontera
void FDM1D::estableceCondicionesFrontera(void)
{
   int ren = pBA->columnas() -1;
   ldouble cd[1];

   pSol->asigna(0,Pr->condicionesFrontera(cd,0));
   pSol->asigna(ren,Pr->condicionesFrontera(cd,1));

   pBA->asigna(0,Pr->condicionesFrontera(cd,0));
   pBA->asigna(ren,Pr->condicionesFrontera(cd,1));
}

// Genera el sistema lineal asociado al problema
void FDM1D::generaSistemaLineal(void)
{
   ldouble cd[1];
   Pr->actualiza_H(Ge->tamanoElemento(1));
   int i, ren = pM->renglones() -1;

   pM->asigna(0,0,Pr->f(cd,0));
   pM->asigna(0,1,Pr->f(cd,1));
   pB->asigna(0,-pBA->retorna(0)*Pr->f(cd,-1));
   for (i = 1; i < ren; i++)
   {
      pM->asigna(i,i-1,Pr->f(cd,-1));
      pM->asigna(i,i,Pr->f(cd,0));
      pM->asigna(i,i+1,Pr->f(cd,1));
   }
   pM->asigna(ren,ren - 1,Pr->f(cd,-1));
   pM->asigna(ren,ren,Pr->f(cd,0));
   pB->asigna(ren,-pBA->retorna(ren+2)*Pr->f(cd,1));

   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pM->visualiza(0);
      pB->visualiza(1,1);
   }
#endif

}


