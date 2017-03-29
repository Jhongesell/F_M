//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el m�todo de volumen finito                                                   //
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


#ifndef __FVM1D__
#define __FVM1D__


#include "F_M.hpp"
#include "MatrizBand.hpp"
#include "Problema_2D.hpp"
#include "Geometria_2D.hpp"



/// Clase para resolver problemas en dos dimensi�n por el m�todo de volumen finito
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class FVM2D : public F_M
{
private:

   /// Puntero a la definicion del problema
   Problema_1D   *Pr;
   /// Puntero a la definicion de la geometria
   Geometria_1D  *Ge;


public:

   /// Constructor de la clase
   /** @param pr Puntero a la definici�n del problema en dos dimensiones
       @param ge Puntero a la definici�n de la geometria en dos dimensiones
       @param rsl Puntero a la definici�n del resolvedor de sistemas lineales  */
   FVM2D(Problema_2D *pr, Geometria_2D *ge, ResuelveSistemaLineal *rsl) : F_M(pr,ge,rsl)
   {
      Pr = pr;
      Ge = ge;

      Banda = 7;
      SolicitaMemoria();
   }

   /// Establece las condiciones de frontera
   void EstableceCondicionesFrontera(void);

   /// Genera el sistema lineal asociado al problema
   void GeneraSistemaLineal(void);


};

/**
Esta clase implementa los comportamientos para resolver un problema en dos dimensiones
@example EjemploFVM2D.cpp */

#endif

