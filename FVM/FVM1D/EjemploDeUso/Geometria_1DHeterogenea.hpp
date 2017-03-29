//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría heterogénea en una dimensión                            //
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


#ifndef __Geometria_1DHeterogenea__
#define __Geometria_1DHeterogenea__


#include "Geometria_1D.hpp"


/// Tipo de justificación de la malla
#define IZQUIERDA  -1
#define CENTRADA    0
#define DERECHA     1


/// Tipo de Malla
#define DOMINIO_NM     1   // Dominio/(n^m) 
#define DOMINIO_LOGe   2   // Dominio/Loge
#define DIMINIO_LOG10  3   // Dominio/Log10



/// Clase para generar una geometría heterogénea en una dimensión
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
    @todo Implementar diversos tipos de geometría no homogénea
*/
class Geometria_1DHeterogenea : public Geometria_1D
{
private:

   /// Tipo de geometría
   int Tipo;
   /// Indica el tipo de justificación de la geometría
   int Centrada;
   /// Exponente para geometrías del tipo 1/2^M
   int M;

   /// Dominio del tipo 1/N^M
   void dominioNM(void);

   /// Dominio del logarítmico
   void dominioLOGe(void);

   /// Dominio del logarítmico
   void dominioLOG10(void);


public:

   /** @param xi Coordena inicial del dominio de la partición
       @param xf Coordena final del dominio de la partición
       @param part Tamaño de la partición
       @param tp Tipo de partición
       @param cen Partición centrada en el punto indicado */
   Geometria_1DHeterogenea(ldouble xi, ldouble xf, int part, int tp, double cen=0.0) : Geometria_1D()
   {
      Dominio.asigna(0,0,xi);
      Dominio.asigna(1,0,xf);

      Particion.asigna(0,part);

      N_N = part;
      N_E = part - 1;

      Tipo = tp;
      Centrada = cen;
      M = 2;

      generaGeometria();
   }

   /// Constructor de la clase
   /** @param dom Dominio de la particion
       @param part Tamaño de la partición
       @param tp Tipo de partición
       @param cen Partición centrada en el punto indicado */
   Geometria_1DHeterogenea(MatrizDensa *dom, int part, int tp, double cen=0.0) : Geometria_1D()
   {
      dom->copia(&Dominio);

      Particion.asigna(0,part);

      N_N = part;
      N_E = part - 1;

      Tipo = tp;
      Centrada = cen;

      generaGeometria();
   }


   /// Constructor de la clase
   /** @param arch Nombre del archivo que contiene la geometria */
   Geometria_1DHeterogenea(char *arch) : Geometria_1D()
   {
      leeGeometria(arch);
   }


   /// Genera la geometria
   void generaGeometria(void);



};

/**
Esta clase implementa los componentes para el trabajar con una geometría heterogénea en una dimensión
@example EjemploGeometria1D.cpp */

#endif
