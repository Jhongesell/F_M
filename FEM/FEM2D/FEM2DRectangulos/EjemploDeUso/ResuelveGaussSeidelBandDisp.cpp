//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema Ax=b                                                      //
// Revisión: 20 de Junio del 2006                                                           //
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

#include <math.h>
#include "ResuelveGaussSeidelBandDisp.hpp"


// Resuelve Ax=b usando el metodo Gauss-Seidel
void ResuelveGaussSeidelBandDisp::resuelve(void)
{
#ifdef DEPURAR
   if (!M->matrizCuadrada()) error("matriz no cuadrada");
#endif

   int i, j, ind, xcol;
   ldouble sum, mx1, m1;
   Vector *xt = new Vector(M->renglones());
   if (!xt) error("no hay memoria para el vector auxiliar");

   for (NumIteraciones = 1; NumIteraciones <= Iter; NumIteraciones++)
   {
      for (i = 0; i < M->renglones(); i++)
      {
         if (M->retorna(i,i) == 0.0)
         {
            delete xt;
            return;
         }
         sum = 0.0;
         xcol = M->retornaNumeroColumnasBanda(i);
         for (ind = 0; ind < xcol; ind ++)
         {
            j = M->retornaNumeroColumna(i,ind);
            if (i == j) continue;
            sum += M->retorna(i,j) * xt->retorna(j);
            //~ if (j < i) sum += M->retorna(i,j) * xt->retorna(j);
            //~ if (j >= i+1) sum += M->retorna(i,j) * X->retorna(j);
         }
         xt->asigna(i,(B->retorna(i) - sum) / M->retorna(i,i));
      }
      mx1 = 0.0;
      for (i = 0; i < M->renglones(); i++)
      {
#ifdef __Double__
         m1 = fabs(xt->retorna(i) - X->retorna(i));
#else
         m1 = fabsl(xt->retorna(i) - X->retorna(i));
#endif
         if (m1 > mx1) mx1 = m1;
         X->asigna(i,xt->retorna(i));
      }
      //~ printf("\n%f",mx1);
      if (mx1 <= Ep) break;
   }
   delete xt;
}
