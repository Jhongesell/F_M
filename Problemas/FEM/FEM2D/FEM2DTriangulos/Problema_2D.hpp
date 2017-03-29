

#ifndef __Problema_1D__
#define __Problema_1D__

#include "Problema.hpp"
#include "Geometria_2D.hpp"
#include "Lineales.hpp"



class Problema_2D : public Problema
{
protected:

   /// Interpoladores Lineales
   Lineales ln;

public:


   /// Constructor de la clase
   Problema_2D(void)
   {
      Dominio.redimensiona(2,2);

      TipoFrontera.redimensiona(4);
      Alcance_frontera.redimensiona(4);
   }

   /// Inicializa la geometria
   void inicializa(Geometria_2D *ge, int partx, int party)
   {

      // Inicializa la particion
      ge->inicializa(&Dominio, partx, party);

      // Marca los nodos externos segun condiciones de frontera
      // Frontera 1 X = X0
      if (tipoCondicionFrontera(0) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(0) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(0,0),0,-1);
         //~ else ge->marcaNodosSatisfagan(Dominio[0][0],0,-1,1,Y0,Y1);
      }
      // Frontera 2 X = X1
      if (tipoCondicionFrontera(1) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(1) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(1,0),0,-1);
         //~ else ge->marcaNodosSatisfagan(Dominio[1][0],0,-1,1,Y0,Y1);
      }
      // Frontera 3 Y = Y0
      if (tipoCondicionFrontera(2) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(2) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(0,1),1,-1);
         //~ else ge->marcaNodosSatisfagan(Dominio[0][1],1,-1,0,X0,X1);
      }
      // Frontera 4 Y = Y1
      if (tipoCondicionFrontera(3) == DIRICHLET)
      {
         if (retornaAlcanceFrontera(3) == 0) ge->marcaNodosSatisfagan(Dominio.retorna(1,1),1,-1);
         //~ else ge->marcaNodosSatisfagan(Dominio[1][1],1,-1,0,X0,X1);
      }

      // Numera los nodos
      ge->numeraNodos();

   }


   /// Interpoladores lineales
   ldouble l_n(int f, ldouble e, ldouble n)
   {
      return ln.l_n(f,e,n);
   }

   /// Asigna valores de los nodos
   void asignarValorNodo(ldouble *x, ldouble *y)
   {
      ln.asignarValorNodo(x, y);
   }

   /// Asigna valor al Jacobiano
   inline void asignarValorJacobiano(ldouble j)
   {
      ln.asignarValorJacobiano(j);
   }

   /// Asigna valor del area del elemento
   inline void asignarValorArea(ldouble a)
   {
      ln.asignarValorArea(a);
   }
};

#endif
