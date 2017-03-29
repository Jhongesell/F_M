//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal tridiagonal                                        //
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



#ifndef __ResuelveTridiagonal__
#define __ResuelveTridiagonal__


#include "ResuelveSistemaLineal.hpp"


/// Clase para resolución del sistema lineal tridiagonal
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class ResuelveTridiagonal: public ResuelveSistemaLineal
{


public:

   /// Constructor de la clase
   ResuelveTridiagonal(void) : ResuelveSistemaLineal()
   {
      M = NULL;
      X = NULL;
      B = NULL;
      MetodoModificaMatriz = true;
      MetodoNumerico = TRIDIAGONAL;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz tipo Matriz */
   ResuelveTridiagonal(Matriz *A) : ResuelveSistemaLineal()
   {
      if (A->maximoTamanoColumnaOcupado() > 3)
      {
         printf("\nError el tamaño de la banda es mayor que 3\n");
         exit(1);
      }
      M = A;
      X = NULL;
      B = NULL;
      MetodoModificaMatriz = true;
      MetodoNumerico = TRIDIAGONAL;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz tipo Matriz
       @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   ResuelveTridiagonal(Matriz *A, Vector *x, Vector *b) : ResuelveSistemaLineal()
   {
      if (A->maximoTamanoColumnaOcupado() > 3)
      {
         printf("\nError el tamaño de la banda es mayor que 3\n");
         exit(1);
      }
      M = A;
      X = x;
      B = b;
      MetodoModificaMatriz = true;
      MetodoNumerico = TRIDIAGONAL;
   }


   /// Resuelve el sistema lineal
   void resuelve(void);


   /// Resuelve el sistema lineal
   /** @param x Puntero a un vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   void resuelve(Vector *x, Vector *b)
   {
      X = x;
      B = b;
      resuelve();
   }

};

#endif
