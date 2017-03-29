//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el método de elemento finito                                                  //
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


#include <math.h>
#include "FEM1D.hpp"
#include "GaussQuad.hpp"


// Establece las condiciones de frontera
void FEM1D::estableceCondicionesFrontera(void)
{

}



// Genera el sistema lineal asociado al problema
void FEM1D::generaSistemaLineal(void)
{
   ldouble cd[3], cd1[3];
   //~ Pr->Actualiza_H(Ge->Tamano_Elemento(1));
   //~ int i, ren = M->Renglones() -1;




   int i, j, l, m, n, k, p, q;
   ldouble x, J, tp;
   int nd[3], el[3], num;

   ///////////////////////////////////////////////////////////////////////////
   // Variables para integración
   int PUNTOS_INTEGRAR = 8;
   ldouble *PX = new ldouble[PUNTOS_INTEGRAR];
   ldouble *FX = new ldouble[PUNTOS_INTEGRAR];
   if (!PX || !FX) errorSolicitudMemoria("FEM1D");
   GaussQuad integ(-1.0,1.0,PUNTOS_INTEGRAR,PX);
   ///////////////////////////////////////////////////////////////////////////

   MatrizDensa *XA = new MatrizDensa(Ge->retornaNodosElemento(),Ge->retornaNodosElemento(),"Matriz Temporal para Generar Matriz de Rigidez");
   if (!XA) errorSolicitudMemoria("Matriz Temporal para Generar Matriz de Rigidez");


   for (i = 0; i < Ge->retornaNumeroElementos(); i++)
   {
      // Recupera al referencia del nodo global con respecto al nodo local
      Ge->retornaNodosElemento(i+1, nd,Ge->retornaNodosElemento());
      // Obtiene las coordenadas del elemento
      cd[0] = Ge->retornaValorNodo(nd[0],0);
      cd[1] = Ge->retornaValorNodo(nd[1],0);
      Pr->asignarValorNodo(cd);
      // Jacobiano de la transformación
      J = fabsl((cd[1] - cd[0])/2.0);

      // Llenado del vector local usando el lado derecho de la ecuacion mediante un cambio del intervalo de integracion
      for (j = 0; j < Ge->retornaNodosElemento(); j++)
      {
         // Calcula las integrales del lado derecho
         for (k = 0; k < PUNTOS_INTEGRAR; k++)
         {
            cd1[0] = ((cd[1] - cd[0]) / 2.0) * PX[k] + ((cd[1] + cd[0])/2.0);
            FX[k] = Pr->ladoDerecho(cd1) * Pr->l_n(j,PX[k]) * J;
         }
         if (Ge->retornaNumeracionNodo(nd[j]) < 0) continue;
         x = pBA->retorna(nd[j]) + integ.integra(FX);
         if(x) pBA->asigna(nd[j],x);
      }
   }

   j = 0;
   for (i = 0; i < Ge->retornaNumeroNodos(); i++)
   {
      if (Ge->retornaNumeracionNodo(i) < 0) continue;
      pB->asigna(j,pBA->retorna(i));
      j++;
   }


   // Llena la matriz de carga de nodos interiores MII
   int sw = 0;
   for (i = 0; i < Ge->retornaNumeroNodos(); i++)
   {
      if (Ge->retornaNumeracionNodo(i) < 0) continue;

      // Busca todos los elemento que contienen al nodo buscado
      num = Ge->retornaElementosContienenNodo(i,el,Ge->numeroElementosSoporteNodo());
      // realiza las integraciones sobre cada elemento que contiene al nodo
      for (k = 0; k < num; k++)
      {
         // Recupera la referencia del nodo global con respecto al nodo local
         Ge->retornaNodosElemento(el[k], nd, Ge->retornaNodosElemento());
         // Obtiene las coordenadas del elemento
         cd[0] = Ge->retornaValorNodo(nd[0],0);
         cd[1] = Ge->retornaValorNodo(nd[1],0);
         Pr->asignarValorNodo(cd);
         // Jacobiano de la transformación
         J = fabsl((cd[1] - cd[0])/2.0);

         if (sw == 0 || (sw == 1 && !pPr->retornaCoeficientesConstantes()))
         {
            // Genera matriz de carga local a partir de la integracion sobre cada elemento
            for (j = 0; j < Ge->retornaNodosElemento(); j++)
            {
               for (l = 0; l < Ge->retornaNodosElemento(); l++)
               {
                  // Calcula el valor correspondiente al nodo local J,L
                  for (m = 0; m < PUNTOS_INTEGRAR; m++)
                  {
                     cd1[0] = PX[m];
                     FX[m] = Pr->f(cd1, j*Ge->retornaNodosElemento()+l) * J;
                  }
                  XA->asigna(j,l,integ.integra(FX));
                  // Almacena el valor calculado del nodo local J,L en el lugar del nodo global correspondiente
               }
            }
            sw = 1;
#ifdef DEPURAR
            if (visualiza)
            {
               // Matriz de carga local
               XA->visualiza(0);
            }
#endif
         }
         for (j = 0; j < Ge->retornaNodosElemento(); j++)
         {
            m = Ge->retornaNumeracionNodo(nd[j]);
            if (m < 0) continue;
            n = Ge->retornaNumeracionNodo(i);
            for (l = 0; l < Ge->retornaNodosElemento(); l++)
            {
               if (nd[l] == nd[j]) p = l;
               if (nd[l] == i) q = l;
            }
            tp = pM->retorna(n,m) + XA->retorna(p,q);
            if (tp) pM->asigna(n,m,tp);
         }
      }
   }




#ifdef DEPURAR
   // Visualiza matrices
   if (visualiza)
   {
      pM->visualiza(0);
      pBA->visualiza(1,1);
   }
#endif

   delete []PX;
   delete []FX;
   delete XA;

}

