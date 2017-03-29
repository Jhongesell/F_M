

#include "FEM2DTriangulos.hpp"
#include "Problema_2DEjemp01.hpp"
#include "Geometria_2DTriangulos.hpp"
#include "ResuelveCGMBandDisp.hpp"
#include "ResuelveJacobiBandDisp.hpp"
#include "ResuelveGaussSeidelBandDisp.hpp"


// Ejemplo para resolver un problema en dos dimensiones mediante el método de elemento finito
int main(void)
{
   Geometria_2DTriangulos *ge = new Geometria_2DTriangulos();

   Problema_2DEjemp01 *pr = new Problema_2DEjemp01();
   pr->inicializa(ge,5,5);
   pr->visualizaProblema();   
   ge->visualiza();

   
   ResuelveCGMBandDisp *rsl1 = new ResuelveCGMBandDisp();
   ResuelveJacobiBandDisp *rsl2 = new ResuelveJacobiBandDisp();
   ResuelveGaussSeidelBandDisp *rsl3 = new ResuelveGaussSeidelBandDisp();
   
   
   ResuelveSistemaLineal *rsl[3];
   rsl[0] = rsl1;   
   rsl[1] = rsl2;   
   rsl[2] = rsl3;
   
   for (int i = 0; i < 3; i++)
   {
      FEM2DTriangulos fem(pr, ge, rsl[i]);
      fem.activaVisualiza(true);
      fem.resuelve();
      fem.visualizaSolucion();
      fem.grabaSolucion("Solucion.txt");
      fem.error();
      printf("\n\n");
   }
   
   
   
   
   delete pr;
   delete ge;
   delete rsl1;
   delete rsl2;
   delete rsl3;
   
   return 0;
}
