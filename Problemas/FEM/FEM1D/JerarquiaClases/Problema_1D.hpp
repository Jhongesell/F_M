//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para definir un problema en una dimensi�n                                     //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// P�gina:   http://www.mmc.igeofcu.unam.mx/acl                                             //
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


#ifndef __Problema_1D__
#define __Problema_1D__

#include "Problema.hpp"
#include "Geometria_1D.hpp"
#include "Lineales.hpp"


/// Clase base para definir un problema en una dimensi�n
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
   /** @param ge Puntero a la definici�n de la geometria en una dimensi�n
       @param part Tama�o de la partici�n */
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
   /** @param f N�mero de interpolador
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
