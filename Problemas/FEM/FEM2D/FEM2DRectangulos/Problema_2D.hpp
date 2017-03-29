//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para definir un problema en dos dimensiones                                   //
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


#ifndef __Problema_2D__
#define __Problema_2D__

#include "Problema.hpp"
#include "Geometria_2D.hpp"
#include "Lineales.hpp"


/// Clase base para definir un problema en dos dimensiones
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Problema_2D : public Problema
{
protected:

   /// Interpoladores Lineales
   Lineales ln;

public:


   /// Constructor de la clase
   Problema_2D(void) : Problema()
   {
      Dominio.redimensiona(2,2);
      TipoFrontera.redimensiona(4);
      Alcance_frontera.redimensiona(4);
   }

   /// Inicializa la geometria
   /** @param ge Puntero a la definici�n de la geometria en dos dimensiones
       @param partx Tama�o de la partici�n en x
       @param party Tama�o de la partici�n en y*/
   void inicializa(Geometria_2D *ge, int partx, int party)
   {
      // Inicializa la particion
      ge->inicializa(&Dominio, partx, party);

      // Marca los nodos externos segun condiciones de frontera
      // Frontera 1 X = X0
      if (tipoCondicionFrontera(0) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(0) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(0,0),0,-1);
         else ge->marcaNodosSatisfagan(Dominio.retorna(0,0),0,-1,1,Dominio.retorna(0,1),Dominio.retorna(1,1));
      }
      // Frontera 2 X = X1
      if (tipoCondicionFrontera(1) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(1) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(1,0),0,-1);
         else ge->marcaNodosSatisfagan(Dominio.retorna(1,0),0,-1,1,Dominio.retorna(0,1),Dominio.retorna(1,1));
      }
      // Frontera 3 Y = Y0
      if (tipoCondicionFrontera(2) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(2) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(0,1),1,-1);
         else ge->marcaNodosSatisfagan(Dominio.retorna(0,1),1,-1,0,Dominio.retorna(0,0),Dominio.retorna(1,0));
      }
      // Frontera 4 Y = Y1
      if (tipoCondicionFrontera(3) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(3) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(1,1),1,-1);
         else ge->marcaNodosSatisfagan(Dominio.retorna(1,1),1,-1,0,Dominio.retorna(0,0),Dominio.retorna(1,0));
      }

      // Numera los nodos
      ge->numeraNodos();

   }


   /// Interpoladores lineales
   /** @param f N�mero de interpolador
       @param e Coordenada
       @param n Coordenada
       @return Valor del interpolador evaluado en la coordenada  */
   ldouble l_n(int f, ldouble e, ldouble n)
   {
      return ln.l_n(f,e,n);
   }

   /// Asigna valores de los nodos
   /** @param x Coordenada
       @param y Coordenada */
   void asignarValorNodo(ldouble *x, ldouble *y)
   {
      ln.asignarValorNodo(x, y);
   }

   /// Asigna valor al Jacobiano
   /** @param j Jacobiano */
   inline void asignarValorJacobiano(ldouble j)
   {
      ln.asignarValorJacobiano(j);
   }

};

#endif
