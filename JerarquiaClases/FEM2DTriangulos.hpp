//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el método de elemento finito en dos dimensiones usando triangulos             //
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


#ifndef __FEM2DTriangulos__
#define __FEM2DTriangulos__


#include "FEM2D.hpp"



/// Clase para resolver problemas mediante el método de elemento finito en dos dimensiones usando triangulos
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1 
    @bug No hay errores conocidos
*/
class FEM2DTriangulos : public FEM2D
{
   
  public:

      /// Constructor de la clase
      /** @param pr Puntero a la definición del problema en dos dimensiones
          @param ge Puntero a la definición de la geometria en dos dimensiones
          @param rsl Puntero a la definición del resolvedor de sistemas lineales  */
      FEM2DTriangulos(Problema_2D *pr, Geometria_2D *ge, ResuelveSistemaLineal *rsl) : FEM2D(pr,ge,rsl)
      {
         banda = 7;
         solicitaMemoria();
      }

      /// Establece las condiciones de frontera
      void estableceCondicionesFrontera(void);
      
      /// Genera el sistema lineal asociado al problema
      void generaSistemaLineal(void);
    
};
/**
Esta clase implementa los comportamientos para resolver un problema en dos dimensiones mediante el método de elemento finito en dos dimensiones usando triangulos
@example EjemploFEM2DTriangulos.cpp */

#endif
