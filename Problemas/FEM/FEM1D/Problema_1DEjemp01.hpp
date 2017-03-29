//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir un problema en una dimensi�n                                          //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// P�gina:   http://www.mmc.igeofcu.unam.mx/acl                                             //
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


#ifndef __Problema_1DEjemp01__
#define __Problema_1DEjemp01__


#include <math.h>
#include "Problema_1D.hpp"


/// Clase para definir un problema en una dimensi�n
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Problema_1DEjemp01 : public Problema_1D
{


public:

   /// Constructor de la clase
   Problema_1DEjemp01(void) : Problema_1D()
   {
      // Dominio
      Dominio.asigna(0,0,0.0);
      Dominio.asigna(1,0,1.0);

      // Tipo de frontera
      TipoFrontera.asigna(0,DIRICHLET);
      TipoFrontera.asigna(1,DIRICHLET);

      Coeficientes_constantes = true;
      Solucion_analitica = SOLUCION_ANALITICA_DISPONIBLE;
   }


   /// Discretizacion de la ecuacion
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @param di Banda solicitada
       @return Valor de la funci�n */
   ldouble f(ldouble *x, int di)
   {
      if (di == 0 || di == 3) return ( (ln.l_dn1(x[0]) * ln.l_dn1(x[0]) + ln.l_n1(x[0]) * ln.l_n1(x[0])) );
      if (di == 1 || di == 2) return ( (ln.l_dn1(x[0]) * ln.l_dn2(x[0]) + ln.l_n1(x[0]) * ln.l_n2(x[0])) );
      printf("Error al solicitar evaluar el operador");
      exit(1);
      return 0.0;
   }


   /// Retorna la solucion exacta
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @return Valor de la soluci�n */
   ldouble solucionExacta(ldouble *x)
   {
#ifdef __Double__
      return ((1.0 / (1.0 + (M_PI*M_PI)))*sin(M_PI*x[0]));
#else
      return ((1.0 / (1.0 + (M_PI*M_PI)))*sinl(M_PI*x[0]));
#endif
   }

   /// Lado derecho de la ecuacion
   /** @param x Puntero al arreglo de coordenadas
       @return Evaluaci�n del lado derecho */
   ldouble ladoDerecho(ldouble *x)
   {
#ifdef __Double__
      return (sin(M_PI*x[0]));
#else
      return (sinl(M_PI*x[0]));
#endif
   }


   /// Valor en la frontera X = X0
   /** @param x Puntero al arreglo de coordenadas
       @param fr N�mero de frontera
       @return Valor en la frontera */
   ldouble condicionesFrontera(ldouble *x, int fr)
   {
      if (fr == 0) return 0.0;
      if (fr == 1) return 0.0;
      printf("\nError al solicitar valores de la frontera");
      return 0.0;
   }


   /// Visualiza la definicion del problema
   void visualizaProblema(void)
   {
      printf("\nResuelve:\n");
      printf("\n\t-Uxx + U = sin(M_PI * x)");
      printf("\n\ten 0 <= x <= 1");
      printf("\n\tu(0)=u(1)=0");
   }


};

/**
Esta clase implementa los comportamientos para definir un problema en una dimensi�n
@example Ejemplo.cpp */

#endif
