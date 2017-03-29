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


#include <math.h>
#include "FEM2DTriangulos.hpp"

// Establece las condiciones de frontera
void FEM2DTriangulos::estableceCondicionesFrontera(void)
{
   
}



// Genera el sistema lineal asociado al problema
void FEM2DTriangulos::generaSistemaLineal(void)
{   
   ldouble cd[10];
   int i, j, l, N_elementos = Ge->retornaNumeroElementos();
   ldouble x;
   ldouble TX[3], TY[3], J, A;
   

   // Genera la matriz de carga global
   int *nd = new int [10];//Ge->Retorna_nodos_elemento()
   if (!nd) errorSolicitudMemoria("FEM2DT");
   int el[10];

   // Solicita memoria para los diferentes vectores y matrices necesarios para el método
   MatrizDensa *pXA   =  new MatrizDensa(Ge->retornaNodosElemento(),Ge->retornaNodosElemento(),"Matriz Temporal para Generar Matriz de Rigidez");
   if (!pXA) errorSolicitudMemoria("Matriz Temporal para Generar Matriz de Rigidez");
      
      
   
   // Nodos interiores
   for (i = 0; i < N_elementos; i++)
   {
      // Obtiene el area del elemento
      A = Ge->areaElemento(i+1);
      Pr->asignarValorArea(A);
      // Recupera la referencia del nodo global con respecto al nodo local
      Ge->retornaNodosElemento(i+1, nd, Ge->retornaNodosElemento());
      // Coordenadas del elemento
      Ge->coordenadasElemento(i+1,TX,TY);
      Pr->asignarValorNodo(TX,TY);

      // Jacobiano de la transformación
#ifdef __Double__
      if (TY[0] == TY[1]) J = fabs(((1.0/(2.0*A))*(TY[2]-TY[0])) * ((1.0/(2.0*A))*(TX[1]-TX[0])));
       else J = fabs(((1.0/(2.0*A))*(TY[1]-TY[0])) * ((1.0/(2.0*A))*(TX[2]-TX[1])));
#else
      if (TY[0] == TY[1]) J = fabsl(((1.0/(2.0*A))*(TY[2]-TY[0])) * ((1.0/(2.0*A))*(TX[1]-TX[0])));
       else J = fabsl(((1.0/(2.0*A))*(TY[1]-TY[0])) * ((1.0/(2.0*A))*(TX[2]-TX[1])));
#endif
      // Llenado de la matriz BA usando el lado derecho de la ecuacion mediante un cambio del intervalo de integracion
      for (j = 0; j < Ge->retornaNodosElemento(); j++)
      {
         // Integral orden 1
         cd[0] = ((TX[0]+TX[1]+TX[2])/3.0);
         cd[1] = ((TY[0]+TY[1]+TY[2])/3.0);
         x = pBA->retorna(nd[j]) +  Pr->ladoDerecho(cd) * Pr->l_n(j,1.0/3.0,1.0/3.0) * J; 

         // Integral orden 2
         //if (T_Y[0] == T_Y[1])  x = BA->Retorna(nd[j]) + (F(T_X[0]+(T_X[1] - T_X[0])/2.0, T_Y[0]) + F(T_X[0]+(T_X[1]-T_X[0])/2.0,T_Y[0]+(T_Y[2]-T_Y[0])/2.0) + F(T_X[0],T_Y[0]+(T_Y[2]-T_Y[0])/2.0)) / 3.0 * L_N(j,1.0/3.0,1.0/3.0);
         // else x = BA->Retorna(nd[j]) + (F(T_X[0],T_Y[0]+(T_Y[1]-T_Y[0])/2.0) + F(T_X[2]+(T_X[1]-T_X[2])/2.0,T_Y[1]) + F(T_X[2]+(T_X[1]-T_X[2])/2.0,T_Y[0]+(T_Y[1]-T_Y[0])/2.0)) / 3.0 * L_N(j,1.0/3.0,1.0/3.0) * J;
         
 
         pBA->asigna(nd[j],x);
      }
   }

   int num,k,n,m,p,q;
   ldouble tp;
   
   // Nodos interiores
   int sw = 0;
   for (i = 0; i < Ge->retornaNumeroNodos(); i++)
   {
      if (Ge->retornaNumeracionNodo(i) < 0) continue;
      
      // Obtiene el area del elemento

      // Recupera la referencia del nodo global con respecto al nodo local
      num = Ge->retornaElementosContienenNodo(i,el, Ge->numeroElementosSoporteNodo());
      for (k = 0; k < num; k++)
      {
         Ge->retornaNodosElemento(el[k],nd,Ge->retornaNodosElemento());
         A = Ge->areaElemento(el[k]);
         Pr->asignarValorArea(A);
         // Coordenadas del elemento
         Ge->coordenadasElemento(el[k],TX,TY);
         Pr->asignarValorNodo(TX,TY);
         //~ pmx = TX[0] + (TX[1] - TX[0])/2.0;
         //~ pmx = TY[0] + (TY[3] - TY[0])/2.0;
      

         // Jacobiano de la transformación
#ifdef __Double__
         if (TY[0] == TY[1]) J = fabs(((1.0/(2.0*A))*(TY[2]-TY[0])) * ((1.0/(2.0*A))*(TX[1]-TX[0])));
          else J = fabs(((1.0/(2.0*A))*(TY[1]-TY[0])) * ((1.0/(2.0*A))*(TX[2]-TX[1])));
#else
         if (TY[0] == TY[1]) J = fabsl(((1.0/(2.0*A))*(TY[2]-TY[0])) * ((1.0/(2.0*A))*(TX[1]-TX[0])));
          else J = fabsl(((1.0/(2.0*A))*(TY[1]-TY[0])) * ((1.0/(2.0*A))*(TX[2]-TX[1])));
#endif

         if (sw == 0 || (sw == 1 && !pPr->retornaCoeficientesConstantes()))
         {          

            // Calculo de las matriz local correspondiente al nodo local J,L
            for (j = 0; j < Ge->retornaNodosElemento(); j++)
            {
               for (l = 0; l < Ge->retornaNodosElemento(); l++)
               {
                  // Integral de orden 1
                  cd[0] = 1.0/3.0;
                  cd[1] = 1.0/3.0;
                  x = Pr->f(cd, j*Ge->retornaNodosElemento()+l) * J;
                  // Almacena el valor en la matriz local J,L
                  pXA->asigna(j,l,x);
               }
            }
            sw = 1;
#ifdef DEPURAR
            if (visualiza)
            {
               // Matriz de carga local
               pXA->visualiza(0);
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

            tp = pM->retorna(n,m) + pXA->retorna(p,q);
            if (tp) pM->asigna(n,m,tp);
         }
      }
   }
   
   // Visualiza la matriz de carga
#ifdef DEPURAR
   if (visualiza)
   {
      pM->visualiza(0);
      pBA->visualiza(1,1);
   }
#endif  
   
   delete []nd;
   delete pXA;
}

