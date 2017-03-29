

#include "FVM2D.hpp"
#include "Problema_2DEjemp01.hpp"
#include "Geometria_2DRectangulos.hpp"
#include "ResuelveCGMBandDisp.hpp"


// Ejemplo para resolver un problema en dos dimensiones mediante el método de diferencias finitas
int main(void)
{
   Geometria_2DRectangulos *ge1 = new Geometria_2DRectangulos();

   Problema_2DEjemp01 *pr = new Problema_2DEjemp01();
   pr->inicializa(ge1, 10,10);
   pr->visualizaProblema();   
   ge1->visualiza();


   ResuelveCGMBandDisp *rsl = new ResuelveCGMBandDisp();
   
   
   FVM2D fvm(pr, ge1, rsl);
   fvm.resuelve();
   fvm.visualizaSolucion();
   fvm.grabaSolucion("Solucion.txt");
   printf("\nError %lf\n\n",fvm.error());
   
   
   delete pr;
   delete ge1;
   delete rsl;
   
   return 0;
}
