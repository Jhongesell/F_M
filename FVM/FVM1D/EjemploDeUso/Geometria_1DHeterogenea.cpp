//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría heterogénea en una dimensión                            //
// Revisión: 1 de Junio del 2006                                                            //
//                                                                                          //
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

#include "Geometria_1DHeterogenea.hpp"


/// Genera la geometria
void Geometria_1DHeterogenea::generaGeometria(void)
{
   EL = new MatrizInt(N_E,NNE,"Nodos que conforman a los elementos",-1);
   if (!EL) errorSolicitudMemoria("Elementos Geometria_1D");

   int col[] = {N_N};
   ND = new MatrizTamanoVariable(DIM,col,"Coordenadas de Nodos");
   if (!ND) errorSolicitudMemoria("Coordenadas Geometria_1D");

   NN = new VectorInt(N_N,"Numeracion de nodos");
   if (!NN) errorSolicitudMemoria("Nodos Geometria_1D");

   int i,j;


   // Almacenamiento de los elementos
   for (i = 0; i < N_E; i++)
   {
      EL->asigna(i,0,i);
      EL->asigna(i,1,i+1);
   }

   // Almacenamiento de las coordenadas de los nodos segun el tipo de geometria solicitada
   switch (Tipo)
   {
   case DOMINIO_NM:
      dominioNM();
      break;
   case DOMINIO_LOGe:
      dominioLOGe();
      break;
   case DIMINIO_LOG10:
      dominioLOG10();
      break;
   }

   // Numeración de los nodos
   j = 0;
   for (i = 0; i <  N_N; i++)
   {
      if (retornaNumeracionNodo(i) != -1)
      {
         estableceNumeroNodo(i,j);
         j++;
      }
   }
}

/// Dominio del tipo 1/N^M
void Geometria_1DHeterogenea::dominioNM(void)
{
   int i, j;
   ldouble val;
   if (Centrada == IZQUIERDA)
   {
      j=2;
      ND->asigna(0,0,Dominio.retorna(0,0));
      for (i = N_E-1; i >= 1; i--)
      {
         val = Dominio.retorna(0,0) + ((Dominio.retorna(1,0) - Dominio.retorna(0,0)) / ((ldouble) j));
         ND->asigna(0,i,val);
         j*=M;
      }
      ND->asigna(0,N_E,Dominio.retorna(1,0));
   }
   else if (Centrada == CENTRADA)
   {
      // Hacer
   }
   else if (Centrada == DERECHA)
   {
      j=2;
      ND->asigna(0,0,Dominio.retorna(0,0));
      for (i = 1; i < N_E; i++)
      {
         val = Dominio.retorna(1,0) - ((Dominio.retorna(1,0) - Dominio.retorna(0,0)) / ((ldouble) j));
         ND->asigna(0,i,val);
         j*=M;
      }
      ND->asigna(0,N_E,Dominio.retorna(1,0));
   }
}


/// Dominio del logarítmico
void Geometria_1DHeterogenea::dominioLOGe(void)
{
   // Hacer
}

/// Dominio del logarítmico
void Geometria_1DHeterogenea::dominioLOG10(void)
{
   // hacer
}
