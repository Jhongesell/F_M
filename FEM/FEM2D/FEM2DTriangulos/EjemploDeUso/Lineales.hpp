//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para definir a los interpoladores lineales para el problema en dos dimensiones     //
// Revisi�n: 20 de Junio del 2006                                                           //
//                                                                                          //
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



#ifndef __LINEALES_HPP__
#define __LINEALES_HPP__


#include "Definiciones.hpp"


/// Clase para definir a los interpoladores lineales para el problema en dos dimensiones
class Lineales
{
private:

   /// Coordenadas del elemento en X
   ldouble T_X[3];
   /// Coordenadas del elemento en Y
   ldouble T_Y[3];
   /// Area del tri�ngulo
   ldouble A;

public:

   void asignarValorJacobiano(ldouble x)
   {  }

   /// Asigna valores de los nodos
   void asignarValorNodo(ldouble x[], ldouble y[])
   {
      T_X[0] = x[0];
      T_X[1] = x[1];
      T_X[2] = x[2];

      T_Y[0] = y[0];
      T_Y[1] = y[1];
      T_Y[2] = y[2];
   }

   /// Asigna valor al area
   void asignarValorArea(ldouble a)
   {
      A = a;
   }

   /// Interpoladores lineales
   ldouble l_n(int f, ldouble E, ldouble N)
   {
      if (f == 0) return l_n1(E,N);
      if (f == 1) return l_n2(E,N);
      if (f == 2) return l_n3(E,N);
      return 0.0;
   }

   /// Interpolador lineal
   ldouble l_n1(ldouble E, ldouble N)
   {
      return (1.0 - E - N);
   }

   /// Interpolador lineal
   ldouble l_n2(ldouble E, ldouble N)
   {
      return (E);
   }

   /// Interpolador lineal
   ldouble l_n3(ldouble E, ldouble N)
   {
      return (N);
   }



   /// Derivada del interpolador lineal
   ldouble l_dn1_E(ldouble E, ldouble N)
   {
      return (-1.0);
   }

   /// Derivada del interpolador lineal
   ldouble l_dn1_N(ldouble E, ldouble N)
   {
      return (-1.0);
   }
   /// Derivada del interpolador lineal
   ldouble l_dn2_E(ldouble E, ldouble N)
   {
      return (1.0);
   }

   /// Derivada del interpolador lineal
   ldouble l_dn2_N(ldouble E, ldouble N)
   {
      return (0.0);
   }

   /// Derivada del interpolador lineal
   ldouble l_dn3_E(ldouble E, ldouble N)
   {
      return (0.0);
   }

   /// Derivada del interpolador lineal
   ldouble l_dn3_N(ldouble E, ldouble N)
   {
      return (1.0);
   }


   /// Derivada con respecto al cambio de coordenadas
   ldouble l_de_X(ldouble E, ldouble N)
   {
      return (1.0/(2.0*A))*(T_Y[2]-T_Y[0]);
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble l_de_Y(ldouble E, ldouble N)
   {
      return (-1.0/(2.0*A))*(T_X[2]-T_X[0]);
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble l_dn_X(ldouble E, ldouble N)
   {
      return (-1.0/(2.0*A))*(T_Y[1]-T_Y[0]);
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble l_dn_Y(ldouble E, ldouble N)
   {
      return (1.0/(2.0*A))*(T_X[1]-T_X[0]);
   }



   /// Derivada con respecto al cambio de coordenadas
   ldouble dn1_X(ldouble x, ldouble y)
   {
      return (l_dn1_E(x,y) * l_de_X(x,y) + l_dn1_N(x,y) * l_dn_X(x,y));
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble dn1_Y(ldouble x, ldouble y)
   {
      return (l_dn1_E(x,y) * l_de_Y(x,y) + l_dn1_N(x,y) * l_dn_Y(x,y));
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble dn2_X(ldouble x, ldouble y)
   {
      return (l_dn2_E(x,y) * l_de_X(x,y) + l_dn2_N(x,y) * l_dn_X(x,y));
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble dn2_Y(ldouble x, ldouble y)
   {
      return (l_dn2_E(x,y) * l_de_Y(x,y) + l_dn2_N(x,y) * l_dn_Y(x,y));
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble dn3_X(ldouble x, ldouble y)
   {
      return (l_dn3_E(x,y) * l_de_X(x,y) + l_dn3_N(x,y) * l_dn_X(x,y));
   }

   /// Derivada con respecto al cambio de coordenadas
   ldouble dn3_Y(ldouble x, ldouble y)
   {
      return (l_dn3_E(x,y) * l_de_Y(x,y) + l_dn3_N(x,y) * l_dn_Y(x,y));
   }

};

#endif
