//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el método de volumen finito                                                   //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// Página:   http://www.mmc.geofisica.unam.mx/acl                                           //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
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



/// Clase para resolver problemas en dos dimensión por el método de volumen finito
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
   /** @param pr Puntero a la definición del problema en dos dimensiones
       @param ge Puntero a la definición de la geometria en dos dimensiones
       @param rsl Puntero a la definición del resolvedor de sistemas lineales  */
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

