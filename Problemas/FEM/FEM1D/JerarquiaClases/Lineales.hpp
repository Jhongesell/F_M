//////////////////////////////////////////////////////////////////////////////////////////////
// Clase que define los interpoladores lineales                                             //
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


#ifndef __LINEALES_HPP__
#define __LINEALES_HPP__

#include "Definiciones.hpp"


/// Clase que define los interpoladores lineales
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Lineales
{
private:
   /// Coordenadas del elemento actual
   ldouble T_X[2];


public:

   /// Asigna valores de los nodos
   void asignarValorNodo(ldouble x0, ldouble x1)
   {
      T_X[0] = x0;
      T_X[1] = x1;
   }

   /// Interpoladores lineales
   ldouble l_n(int f, ldouble E)
   {
      if (f == 0) return l_n1(E);
      if (f == 1) return l_n2(E);
      return 0.0;
   }


   /// Interpoladores lineales
   ldouble l_n1(ldouble E)
   {
      return (0.5 * (1.0 - E));
   }


   /// Interpoladores lineales
   ldouble l_n2(ldouble E)
   {
      return (0.5 * (1.0 + E));
   }


   /// Interpoladores lineales
   ldouble l_dn1(ldouble E)
   {
      return (-1.0 / (T_X[1] - T_X[0]));
   }


   /// Interpoladores lineales
   ldouble l_dn2(ldouble E)
   {
      return (1.0 / (T_X[1] - T_X[0]));
   }

};

#endif
