

#include "FDM3D.hpp"
#include "Problema_3DEjemp01.hpp"
#include "Geometria_3DOrtoedros.hpp"
#include "ResuelveCGMBandDisp.hpp"


// Ejemplo para resolver un problema en tres dimensiones mediante el método de diferencias finitas
int main(void)
{
   Geometria_3DOrtoedros *ge1 = new Geometria_3DOrtoedros();

   Problema_3DEjemp01 *pr = new Problema_3DEjemp01();
   pr->inicializa(ge1, 10,10,10);
   pr->visualizaProblema();   
   ge1->visualiza();


   ResuelveCGMBandDisp *rsl = new ResuelveCGMBandDisp();
   
   
   FDM3D fdm(pr, ge1, rsl);
   fdm.resuelve();
   fdm.visualizaSolucion();
   fdm.grabaSolucion("Solucion.txt");
   printf("\nError %lf\n\n",fdm.error());
   
   
   delete pr;
   delete ge1;
   delete rsl;
   
   return 0;
}
