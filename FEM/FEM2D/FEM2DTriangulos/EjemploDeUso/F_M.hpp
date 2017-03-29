//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para el m�todo de diferencias finitas o elemento finito                       //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// P�gina:   http://www.mmc.geofisica.unam.mx/acl                                           //
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


#ifndef __F_M__
#define __F_M__

#include "VectorExtendido.hpp"
#include "ResuelveSistemaLineal.hpp"
#include "Geometria.hpp"
#include "Problema.hpp"




/// Clase base para resolver problemas por el m�todo de diferencias finitas o elemento finito
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class F_M
{
protected:

   /// Matriz de carga
   Matriz *pM;
   /// Vector de carga
   Vector *pB;
   /// Solucion al sistema lineal
   Vector *pX;
   /// Solucion al problema mediante el m�todo de diferencias finitas
   VectorExtendido *pSol;
   /// Vector de carga completo
   VectorExtendido *pBA;

   /// Visualizaci�n de matrices y vectores generados
   bool visualiza;

   /// Puntero al m�todo de resolucion del sistema lineal
   ResuelveSistemaLineal  *pRSL;
   /// Puntero a la definicion del problema
   Problema   *pPr;
   /// Puntero a la definicion de la geometria
   Geometria  *pGe;

   /// Tama�o de la banda
   int banda;


   /// Establece las condiciones de frontera
   virtual void estableceCondicionesFrontera(void) = 0;

   /// Genera el sistema lineal asociado al problema
   virtual void generaSistemaLineal(void) = 0;

   /// Resuelve el sistema lineal asociado al problema
   void solucionaSistemaLineal(void)
   {
      // Inicializa el m�todo de resoluci�n del sistema lineal
      pRSL->inicializa(pM,pB,pX);
      // Resuelve el sistema lineal
      pRSL->resuelve();
      // Visializa informaci�n sobre la soluci�n del sistema lineal
      pRSL->informacionMetodo();
   }

   /// Ensambla Soluci�n
   void ensamblaSolucion(void);

   /// Solicita la memoria necesaria para soportar los vectores y metrices del m�todo
   void solicitaMemoria(void);


public:

   /// Constructor de la clase
   /** @param pr Puntero a la definici�n del problema
       @param ge Puntero a la definici�n de la geometria
       @param rsl Puntero a la definici�n del resolvedor de sistemas lineales  */
   F_M(Problema *pr, Geometria *ge, ResuelveSistemaLineal *rsl)
   {
      visualiza = false;
      pPr = pr;
      pGe = ge;
      pRSL = rsl;
      pM = NULL;
      pB = NULL;
      pX = NULL;
      pSol = NULL;
      pBA = NULL;
   }

   /// Destructor de la clase
   ~F_M()
   {
      if (pM)
      {
         pM->liberaMemoria();
         delete pM;
      }
      delete pSol;
      delete pBA;
      delete pB;
      delete pX;

   }

   /// Resuelve el problema mediante el m�todo de diferencias finitas o elemento finito
   void resuelve(void)
   {
      // Establece las condiciones de frontera del problema
      estableceCondicionesFrontera();
      // Genera el sistema lineal, i.e genera M  y B
      generaSistemaLineal();
      // Limpia variables temporales usadas para generar el sistema lineal
      pGe->liberaSoporteNodos();
      // Genera la solicion del sistema lineal, i.e. MX=B
      solucionaSistemaLineal();
   }


   /// Visualiza la solicion del problema
   void visualizaSolucion(void)
   {
      pSol->visualiza(1,1,1);
   }

   /// Graba la soluci�n a un archivo
   /** @param arch Nombre del archivo en el cual se grabara la solucion del problema */
   void grabaSolucion(const char *arch);

   /// Muestra el error de la soluci�n vs la soluci�n an�litica
   ldouble error(void);

   /// Visualiza el error indicado por falta de memoria
   /** @param cad Puntero a la cadena de error */
   void errorSolicitudMemoria(const char *cad)
   {
      printf("\nError no hay memoria: %s\n",cad);
      exit(1);
   }

   /// Activa/desactiva la visualizaci�n de matrices y vectores generados
   /** @param st Activa o desactiva la visualizacion */
   void activaVisualiza(bool st)
   {
      visualiza = st;
   }
};

#endif
