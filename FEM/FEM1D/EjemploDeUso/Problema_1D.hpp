//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para definir un problema en una dimensión                                     //
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


#ifndef __Problema_1D__
#define __Problema_1D__

#include "Problema.hpp"
#include "Geometria_1D.hpp"
#include "Lineales.hpp"


/// Clase base para definir un problema en una dimensión
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Problema_1D : public Problema
{
protected:

   /// Interpolador Lineal
   Lineales ln;

public:


   /// Constructor de la clase
   Problema_1D(void) : Problema()
   {
      Dominio.redimensiona(2,2);
      TipoFrontera.redimensiona(2);
   }

   /// Inicializa la geometria
   /** @param ge Puntero a la definición de la geometria en una dimensión
       @param part Tamaño de la partición */
   void inicializa(Geometria_1D *ge, int part)
   {
      int mc1, mc2;
      // Inicializa la particion
      ge->inicializa(&Dominio, part);
      // Inicializa condiciones de frontera
      if (tipoCondicionFrontera(0) == DIRICHLET) mc1 = CONOCIDO;
      else mc1 = DESCONOCIDO;
      if (tipoCondicionFrontera(1) == DIRICHLET) mc2 = CONOCIDO;
      else mc2 = DESCONOCIDO;
      ge->marcaPrimerNodo(mc1);
      ge->marcaUltimoNodo(mc2);
   }


   /// Interpoladores lineales
   /** @param f Número de interpolador
       @param e Coordenada
       @return Valor del interpolador evaluado en la coordenada  */
   ldouble l_n(int f, ldouble e)
   {
      return ln.l_n(f,e);
   }

   /// Asigna valores de los nodos
   /** @param coord Coordenada */
   void asignarValorNodo(ldouble *coord)
   {
      ln.asignarValorNodo(coord[0], coord[1]);
   }


};

#endif
