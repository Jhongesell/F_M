//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal mediante Gauss-Seidel                              //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// Página:   http://www.mmc.igeofcu.unam.mx/acl                                             //
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



#ifndef __ResuelveGaussSeidelBandDisp__
#define __ResuelveGaussSeidelBandDisp__


#include "ResuelveGaussSeidel.hpp"
#include "MatrizBandDisp.hpp"



/// Clase para resolución del sistema lineal mediante Gauss-Seidel
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class ResuelveGaussSeidelBandDisp: public ResuelveGaussSeidel
{

public:

   /// Constructor de la clase
   ResuelveGaussSeidelBandDisp(void) : ResuelveGaussSeidel()
   {
      M = NULL;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp */
   ResuelveGaussSeidelBandDisp(MatrizBandDisp *A) : ResuelveGaussSeidel()
   {
      M = A;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp
       @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal */
   ResuelveGaussSeidelBandDisp(MatrizBandDisp *A, Vector *x, Vector *b) : ResuelveGaussSeidel(x,b)
   {
      M = A;
      RequiereMatriz = REQUIERE_MAT_BAND;
   }

   /// Constructor de la clase
   /** @param A Puntero a una matriz del tipo MatrizBandDisp
       @param x Puntero a un Vector, solución del sistema lineal
       @param b Puntero a un vector, lado derecho del sistema lineal
       @param ep Tolerancia del método
       @param iter Número máximo de iteraciones */
   ResuelveGaussSeidelBandDisp(MatrizBandDisp *A, Vector *x, Vector *b, ldouble ep, int iter) : ResuelveGaussSeidel(x,b,ep,iter)
   {
      M = A;
      RequiereMatriz = REQUIERE_MAT_BAND;
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


/**
Esta clase implementa los componentes para la resolución del sistema lineal mediante Gauss-Seidel
@example EjemploResuelveSistemaLineal.cpp */

#endif
