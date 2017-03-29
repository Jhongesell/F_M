//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el método de elemento finito en dos dimensiones usando rectangulos            //
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


#include "FEM2DRectangulos.hpp"
#include "GaussQuad.hpp"


/// Establece las condiciones de frontera
void FEM2DRectangulos::estableceCondicionesFrontera(void)
{
   int N_nodos = Ge->retornaNumeroNodos();
   
   // Solicita la memoria necesaria
   int *nds = new int [N_nodos];
   if (!nds) errorSolicitudMemoria("FEM2D");

   
   //~ /////////////////////////////////////////////////////////////////////
   //~ // Llenado de Xto o BA con las condiciones de frontera
   
   // Frontera 1 X = X0
   if (Pr->tipoCondicionFrontera(0) == DIRICHLET) 
   {
      // Frontera tipo Dirichlet
      //~ if (Pr->retornaTipoFrontera(0) == 0) num = Ge->regresaNodosSatisfagan(Dominio[0][0],0,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Dominio[0][0],0,nds,N_nodos,1,Y0,Y1);
      //~ for (i = 0; i < num; i++) Sol->Asigna(nds[i],Pr->Valor_frontera_1(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   } else {
      // Frontera tipo Neumann
      //~ if (Pr->Retorna_tipo_frontera(0) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[0][0],0,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Dominio[0][0],0,nds,N_nodos,1,Y0,Y1);
      //~ for (i = 0; i < num; i++) BA->Asigna(nds[i],Pr->Valor_frontera_1(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   }

   // Frontera 2 X = X0
   if (Pr->tipoCondicionFrontera(1) == DIRICHLET) 
   {
      // Frontera tipo Dirichlet
      //~ if (Pr->Retorna_tipo_frontera(1) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[1][0],0,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(X1,0,nds,N_nodos,1,Y0,Y1);
      //~ for (i = 0; i < num; i++) Sol->Asigna(nds[i],Pr->Valor_frontera_2(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   } else {
      // Frontera tipo Neumann
      //~ if (Pr->Retorna_tipo_frontera(1) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[1][0],0,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(X1,0,nds,N_nodos,1,Y0,Y1);
      //~ for (i = 0; i < num; i++) BA->Asigna(nds[i],Pr->Valor_frontera_2(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   }
   
   // Frontera 3 X = Y0
   if (Pr->tipoCondicionFrontera(2) == DIRICHLET) 
   {
      // Frontera tipo Dirichlet
      //~ if (Pr->Retorna_tipo_frontera(2) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[0][1],1,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Y0,1,nds,N_nodos,0,X0,X1);
      //~ for (i = 0; i < num; i++) Sol->Asigna(nds[i],Pr->Valor_frontera_3(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   } else {
      // Frontera tipo Neumann
      //~ if (Pr->Retorna_tipo_frontera(2) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[0][1],1,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Y0,1,nds,N_nodos,0,X0,X1);
      //~ for (i = 0; i < num; i++) BA->Asigna(nds[i],Pr->Valor_frontera_3(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   }

   // Frontera 4 X = Y1
   if (Pr->tipoCondicionFrontera(3) == DIRICHLET) 
   {
      // Frontera tipo Dirichlet
      //~ if (Pr->Retorna_tipo_frontera(3) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[1][1],1,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Y1,1,nds,N_nodos,0,X0,X1);
      //~ for (i = 0; i < num; i++) Sol->Asigna(nds[i],Pr->Valor_frontera_4(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   } else {
      // Frontera tipo Neumann
      //~ if (Pr->Retorna_tipo_frontera(3) == 0) num = Ge->Regresa_Nodos_Satisfagan(Dominio[1][1],1,nds,N_nodos);
       //~ else num = Ge->Regresa_Nodos_Satisfagan(Y1,1,nds,N_nodos,0,X0,X1);
      //~ for (i = 0; i < num; i++) BA->Asigna(nds[i],Pr->Valor_frontera_4(Ge->Retorna_Valor_Nodo(nds[i],0),Ge->Retorna_Valor_Nodo(nds[i],1)));
   }
   //////////////////////////////////////////////
   delete []nds;
}



/// Genera el sistema lineal asociado al problema
void FEM2DRectangulos::generaSistemaLineal(void)
{   
   ldouble cd[7], cd1[7];

   int i, j, l, m, n, k, p, q, NUMERO_NODOS_ELEMENTO = 4;
   ldouble x;
   ldouble TX[NUMERO_NODOS_ELEMENTO], TY[NUMERO_NODOS_ELEMENTO], J, pmx, pmy;

   ldouble  tp;
   int nd[10], el[10], num, PUNTOS_INTEGRAR = 8, N_nodos = Ge->retornaNumeroNodos();
   
   // Variables para integración
   ldouble itg;
   ldouble *PX = new ldouble[PUNTOS_INTEGRAR];
   ldouble *WX = new ldouble[PUNTOS_INTEGRAR];
   if (!PX || !WX) errorSolicitudMemoria("FEM2DR");
      
   GaussQuad integ(-1.0,1.0,PUNTOS_INTEGRAR,PX,WX);
   
   
   // Solicita memoria para los diferentes vectores y matrices necesarios para el método
   MatrizDensa *pXA   =  new MatrizDensa(Ge->retornaNodosElemento(),Ge->retornaNodosElemento(),"Matriz Temporal para Generar Matriz de Rigidez");
   if (!pXA) errorSolicitudMemoria("Matriz Temporal para Generar Matriz de Rigidez");

   ldouble *pXM = new ldouble[N_nodos];
   if (!pXM) errorSolicitudMemoria("XM FEM2DR");
      
   // Nodos interiores
   for (i = 0; i < Ge->retornaNumeroElementos(); i++)
   { 
      // Recupera la referencia del nodo global con respecto al nodo local
      Ge->retornaNodosElemento(i+1, nd, Ge->retornaNodosElemento());
      // Obtiene las coordenadas del elemento
      Ge->coordenadasElemento(i+1, TX, TY);
      Pr->asignarValorNodo(TX,TY);
      pmx = TX[0] + (TX[1] - TX[0])/2.0;
      pmy = TY[0] + (TY[3] - TY[0])/2.0;

      // Jacobiano de la transformación
#ifdef __Double__
      J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
      J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
      Pr->asignarValorJacobiano(J);


      // Llenado del vector local usando el lado derecho de la ecuacion mediante un cambio del intervalo de integracion
      for (j = 0; j < Ge->retornaNodosElemento(); j++)
      {
         // Calculo de la integral numerica
         itg = 0.0;         
         for (m = 0; m < PUNTOS_INTEGRAR; m++)
         {
            cd[0] = (((TX[1] - TX[0]) / 2.0) * PX[m] + ((TX[1] + TX[0])/2.0));
            for (n = 0; n < PUNTOS_INTEGRAR; n++) 
            {
               cd[1] = (((TY[3] - TY[0]) / 2.0) * PX[n] + ((TY[3] + TY[0])/2.0));
               itg += WX[m] * WX[n] * Pr->ladoDerecho(cd) * Pr->l_n(j,PX[m],PX[n]) * J;     
            }
         }
         x = pBA->retorna(nd[j]) + itg;
         if (x) pBA->asigna(nd[j],x);

      }

      if (Ge->retornaNumeracionNodo(i) >= 0) continue;
         
      for (l = 0; l < N_nodos; l++) pXM[l] = 0.0;

      // Genera matriz de carga local a partir de la integracion sobre cada elemento
      for (j = 0; j < Ge->retornaNodosElemento(); j++)
      {
         for (l = 0; l < Ge->retornaNodosElemento(); l++)
         {
            // Calculo de la integral numerica
            itg = 0.0;
            for (m = 0; m < PUNTOS_INTEGRAR; m++)
            {
               for (n = 0; n < PUNTOS_INTEGRAR; n++)
               {
                  cd1[0] = PX[m];
                  cd1[1] = PX[n];
                  itg += (WX[m] * WX[n] * Pr->f(cd1,j*Ge->retornaNodosElemento()+l)) * J;
               }
            }
            pXA->asigna(j,l,itg);
            x = pXM[nd[l]] + pXA->retorna(j,l);
            pXM[nd[l]] = x;
         }
         x =  pBA->retorna(i) - pXM[j] * pSol->retorna(j);
         if (x) pBA->asigna(i,x);
      }
   }


   delete []pXM;
   
   // Llena la matriz de carga de nodos interiores MII
   int sw = 0;
   for (i = 0; i < N_nodos; i++)
   {
      // Descarta a los nodos que no estan en frontera interior
      if (Ge->retornaNumeracionNodo(i) < 0) continue;
         
      // Busca todos los elemento que contienen al nodo buscado
      num = Ge->retornaElementosContienenNodo(i,el,Ge->numeroElementosSoporteNodo());
      // realiza las integraciones sobre cada elemento que contiene al nodo
      for (k = 0; k < num; k++)
      {
         // Recupera la referencia del nodo global con respecto al nodo local
         Ge->retornaNodosElemento(el[k], nd, Ge->retornaNodosElemento());
         // Obtiene las coordenadas del elemento
         Ge->coordenadasElemento(el[k], TX, TY);
         Pr->asignarValorNodo(TX,TY);
         
         // Jacobiano de la transformación
#ifdef __Double__
         J = fabs( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#else
         J = fabsl( (((TX[1] - TX[0])/2.0) * ((TY[3] - TY[0])/2.0)) - (((TX[3] - TX[0])/2.0) * ((TY[1] - TY[0])/2.0)));
#endif
         Pr->asignarValorJacobiano(J);


         if (sw == 0 || (sw == 1 && !pPr->retornaCoeficientesConstantes()))
         {          
            // Ciclo para calcular la matriz local correspondiente al nodo local J,L
            for (j = 0; j < Ge->retornaNodosElemento(); j++)
            {
               for (l = 0; l < Ge->retornaNodosElemento(); l++)
               {
                  // Calculo de la integral numerica
                  itg = 0.0;
                  for (m = 0; m < PUNTOS_INTEGRAR; m++)
                  {
                     for (n = 0; n < PUNTOS_INTEGRAR; n++)
                     {
                        cd1[0] = PX[m];
                        cd1[1] = PX[n];
                        itg += (WX[m] * WX[n] * Pr->f(cd1,j*Ge->retornaNodosElemento()+l)) * J;
                     }
                  }
                  pXA->asigna(j,l,itg);
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
         // Ciclo para calcular la matriz local correspondiente al nodo local J,L
         for (j = 0; j < Ge->retornaNodosElemento(); j++)
         {
            // Llena la matriz MII
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
   
   delete []PX;
   delete []WX;
   delete pXA;
}

