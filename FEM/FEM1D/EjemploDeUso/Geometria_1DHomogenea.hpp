//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría homogénea en una dimensión                              //
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


#ifndef __Geometria_1DHomogenea__
#define __Geometria_1DHomogenea__

#include "Geometria_1D.hpp"

/// Clase para generar una geometría homogénea en una dimensión
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_1DHomogenea : public Geometria_1D
{

public:

   /// Constructor de la clase
   /** @param xi Coordena inicial del dominio de la partición
       @param xf Coordena final del dominio de la partición
       @param part Tamaño de la partición */
   Geometria_1DHomogenea(ldouble xi, ldouble xf, int part) : Geometria_1D()
   {
      Dominio.asigna(0,0,xi);
      Dominio.asigna(1,0,xf);

      Particion.asigna(0,part);

      N_N = part;
      N_E = part - 1;
      generaGeometria();
   }


   /// Constructor de la clase
   /** @param dom Dominio de la particion
       @param part Tamaño de la partición */
   Geometria_1DHomogenea(MatrizDensa *dom, int part) : Geometria_1D()
   {
      dom->copia(&Dominio);

      Particion.asigna(0,part);

      N_N = part;
      N_E = part - 1;
      generaGeometria();
   }

   /// Constructor de la clase
   Geometria_1DHomogenea(void) : Geometria_1D()
   { }


   /// Constructor de la clase
   /** @param arch Nombre del archivo que contiene la geometria */
   Geometria_1DHomogenea(const char *arch) : Geometria_1D()
   {
      leeGeometria(arch);
   }


   /// Genera la geometria
   void generaGeometria(void);

};

/**
Esta clase implementa los componentes para el trabajar con una geometría homogénea en una dimensión
@example EjemploGeometria1D.cpp */

#endif
