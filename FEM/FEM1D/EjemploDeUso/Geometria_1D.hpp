//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría en una dimensión                                        //
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


#ifndef __Geometria_1D__
#define __Geometria_1D__

#include "Geometria.hpp"



/// Clase para generar una geometría en una dimensión
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_1D : public Geometria
{

public:

   /// Costructor de la clase
   Geometria_1D(void) : Geometria()
   {
      // Dimension 1D
      DIM = 1;
      // Numero de nodos por elemento
      NNE = 2;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 2;

      Dominio.redimensiona(2,2);
      Particion.redimensiona(1);
   }


   /// Inicializa la geometria
   void inicializa(MatrizDensa *dm, int part)
   {
      dm->copia(&Dominio);
      Particion.asigna(0,part);
      N_N = part;
      N_E = part - 1;
      generaGeometria();
   }



   /// Regresa los nodos externos en un arreglo ARR de tamaño ND
   /** @param arr Puntero a un arreglo de enteros
       @param nd Indica el tamaño del arreglo */
   void regresaNodosExternos(int *arr, int nd)
   {
      nd = 2;
      arr[0] = 0;
      arr[1] = N_N - 1;
   }

   /// Marca los nodos externos con el valor MC
   /** @param mc Valor a usar de marca */
   void marcaNodosExternos(int mc)
   {
      estableceNumeroNodo(0,mc);
      estableceNumeroNodo(N_N - 1,mc);
      numeraNodos();
   }

   /// Marca el primer nodo con el valor MC
   /** @param mc Valor a usar de marca */
   void marcaPrimerNodo(int mc)
   {
      estableceNumeroNodo(0,mc);
      numeraNodos();
   }

   /// Marca el ultimo nodo con el valor MC
   /** @param mc Valor a usar de marca */
   void marcaUltimoNodo(int mc)
   {
      estableceNumeroNodo(N_N - 1,mc);
      numeraNodos();
   }

   /// Regresa el tamaño del elemento indicado
   /** @param el Elemento
       @return Tamaño del elemento*/
   ldouble tamanoElemento(int el)
   {
      return (retornaValorNodo(el,0) - retornaValorNodo(el-1,0));
   }

   /// Indica si la coordenada pasada esta dentro del dominio
   /** @param coor Puntero a un arreglo de coordenadas
       @return (1) si las coordenadas estan dentro del dominio, (0) en caso contrario */
   int coordenadasDentroDominio(ldouble *coor)
   {
      if (coor[0] < (Dominio.retorna(0,0) - TOLERANCIA_NODO)) return 0;
      if (coor[1] > (Dominio.retorna(1,0) + TOLERANCIA_NODO)) return 0;
      return 1;
   }

   /// Regresa la coordenada del elemento
   /** @param el Elemento
       @param x Coordenada */
   void coordenadasElemento(int el, ldouble *x);

   /// Visualiza coordenadas del dominio
   void visualizaCoordenadasDominio(void)
   {
#ifdef __Double__
      printf("\n\nDominio: (%f,%f)\n\n",Dominio.retorna(0,0),Dominio.retorna(1,0));
#else
      printf("\n\nDominio: (%Lf,%Lf)\n\n",Dominio.retorna(0,0),Dominio.retorna(1,0));
#endif
   }


};

#endif
