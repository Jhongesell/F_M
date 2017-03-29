//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal mediante el uso de la matriz inversa               //
// Revisión: 1 de Junio del 2006                                                            //
//                                                                                          //
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


#include "ResuelveInversa.hpp"


// Calcula la inversa de una matriz usando el método de eliminación Gaussiana
// @param A Puntero a una matriz tipo Matriz
// @param inv Puntero a una matriz tipo Matriz que contendra la inversa
void ResuelveInversa::invierte(Matriz *a, Matriz *inv)
{
#ifdef DEPURAR
   if (!a->mismaDimension(inv) || !a->matrizCuadrada()) error("no son de la misma dimensión");
#endif


   int i,j,k;
   ldouble x, r;

   inv->inicializaDiagonal(1.0);

   for (i = 0; i < a->renglones(); i++)
   {
      x = a->retorna(i,i);
#ifdef DEPURAR
      if (x == 0.0)
      {
         printf("\nValor (%d,%d) se hace cero\n\n",i,i);
         error("Invertir matriz");
      }
#endif
      for (j = 0; j < a->columnas(); j++)
      {
         a->asigna(i,j,a->retorna(i,j) / x);
         inv->asigna(i,j,inv->retorna(i,j) / x);
      }

      x = a->retorna(i,i);
      for (k = 0; k < a->renglones(); k ++)
      {
         if (i == k) continue;
         r = a->retorna(k,i) / x;
         for (j = 0; j < a->columnas(); j++)
         {
            a->asigna(k,j,a->retorna(k,j) - a->retorna(i,j) * r);
            inv->asigna(k,j,inv->retorna(k,j) - inv->retorna(i,j) * r);
         }
      }
   }
   MatrizInvertida = true;
}

