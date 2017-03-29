//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para el método de diferencias finitas o elemento finito                       //
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
#include "F_M.hpp"
#include "MatrizBand.hpp"
#include "MatrizBandComp.hpp"
#include "MatrizDispersa.hpp"
#include "MatrizDispersaComp.hpp"
#include "MatrizDensa.hpp"
#include "Man_arch.hpp"


// Solicita la memoria necesaria para soportar los vectores y metrices del método
void F_M::solicitaMemoria(void)
{
   // Número de nodos desconocidos
   int sw , NN;
   NN = pGe->retornaNumeroNodosDesconocidos();
   // Solicita memoria para la matriz de carga
   sw =  pRSL->retornaRequiereMatriz();
   switch (sw)
   {
   case REQUIERE_MAT_BAND: // Matriz bandada
      if (pRSL->elMetodoModificaMatriz() || !pPr->retornaCoeficientesConstantes())
      {
         pM = new MatrizBand(NN,NN,banda,"Matriz de carga");
      }
      else
      {
         pM = new MatrizBandComp(NN,NN,banda,"Matriz de carga");
      }
      break;
   case REQUIERE_MAT_DISP: // Matriz dispersa
      // Ajusta el tamaño de la banda para soportar la factorización LU dentro de la misma matriz
      banda = (int) sqrt(NN)*3;
      if (pRSL->elMetodoModificaMatriz() || !pPr->retornaCoeficientesConstantes())
      {
         pM = new MatrizDispersa(NN,NN,banda,"Matriz de carga");
      }
      else
      {
         pM = new MatrizDispersaComp(NN,NN,banda,"Matriz de carga");
      }
      break;
   case REQUIERE_MAT_DENS: // Matriz densa
      pM = new MatrizDensa(NN,NN,"Matriz de carga");
      break;
   default:
      printf("\n\n Error en la seleción del tipo de matriz");
      exit(1);
   }

   pB = new Vector(NN,"Vector de carga");
   if (!pB) errorSolicitudMemoria("Lado derecho");

   pX = new Vector(NN,"Solución sistema lineal");
   if (!pX) errorSolicitudMemoria("Solución sistema lineal");

   pSol = new VectorExtendido(pGe->retornaNumeroNodos(),pX,"Solución");
   if (!pSol) errorSolicitudMemoria("Solución");

   pBA = new VectorExtendido(pGe->retornaNumeroNodos(),pB,"Vector de carga global");
   if (!pBA) errorSolicitudMemoria("Vector de carga global");

   ensamblaSolucion();
}



// Ensambla Solucion
void F_M::ensamblaSolucion(void)
{
   int i, j = 0, N_nodos = pGe->retornaNumeroNodos();
   for (i = 0; i < N_nodos; i++)
   {
      if (pGe->retornaNumeracionNodo(i) < 0)
      {
         pSol->inicializa(i,0.0);
         pBA->inicializa(i,0.0);
      }
      else
      {
         pSol->inicializa(i,j);
         pBA->inicializa(i,j);
         j++;
      }
   }
}


// Muestra el error de la solución vs la solución análitica
ldouble F_M::error(void)
{
   // Revisa que este disponible la solución análitica
   if (!pPr->haySolucionAnalitica()) return 0.0;

   int j, tnd;
   int vi = 1;
   ldouble x[10], ve, va, max, err;
   Ctrl_visualizacion cv;


   max = 0.0;
   // Ciclo para encontrar el maximo error
   if (vi) printf("\n\nError por cada nodo\n");
   for (j = 0; j < pGe->retornaNumeroNodos(); j++)
   {
      tnd = pGe->retornaNumeracionNodo(j);
      pGe->retornaValorNodo(j,x);
      ve = pPr->solucionExacta(x);
      va = pSol->retorna(j);
      err = fabsl(ve - va);
      if (tnd == -1)
      {
         if (fabsl(err) > 1e-10)
         {
            printf("\nError en nodo %#3d conocido, error:",j);
            cv.visualiza_en(err);
         }
      }
      if (vi)
      {
         printf("Nodo %#3i (%#3d), Solución exacta:",j,tnd);
         cv.visualiza_e(ve);
         printf(", Error:");
         cv.visualiza_en(err);
      }
      if (err > max) max = err;
   }
   return max;
}


// Graba la solución a un archivo
// @param arch Nombre del archivo en el cual se grabara la solucion del problema */
void F_M::grabaSolucion(const char *arch)
{
   int i, j, tnd;
   ldouble va, x[10];
   char xcad[300], tmp [50];
   xcad[0] = 0;

   Manipulador_archivos *la = new Manipulador_archivos;
   if (!la) errorSolicitudMemoria("Grabar archivo");
   la->parametros(arch,GRABA_ARCHIVO,300);

   for (j = 0; j < pGe->retornaNumeroNodos(); j++)
   {
      tnd = pGe->retornaNumeracionNodo(j);
      pGe->retornaValorNodo(j,x);
      va = pSol->retorna(j);
      for (i = 0; i < pGe->retornaDimension(); i++)
      {
#ifdef __Double__
         sprintf(tmp,"%1.16le ",x[i]);
#else
         sprintf(tmp,"%1.18Le ",x[i]);
#endif
         strcat(xcad, tmp);
      }
#ifdef __Double__
      sprintf(tmp,"%1.16le ",va);
#else
      sprintf(tmp,"%1.18Le ",va);
#endif
      strcat(xcad, tmp);
      la->grabaLinea(xcad);
      xcad[0] = 0;
   }

   delete la;
}

