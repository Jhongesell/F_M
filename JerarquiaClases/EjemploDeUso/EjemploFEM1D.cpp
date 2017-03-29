
#include "FEM1D.hpp"
#include "Problema_1DEjemp01.hpp"
#include "Geometria_1DHomogenea.hpp"
#include "ResuelveTridiagonal.hpp"
#include "CtrlParametros.hpp"



// Ejemplo para resolver un problema en una dimensión mediante el método de elemento finito
int main(int argc, const char *args[])
{
   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);
	int nx = parm.intVal("nx",10); // Partición en X

   // Geometria 
   Geometria_1DHomogenea *ge = new Geometria_1DHomogenea();

   // Problema
   Problema_1DEjemp01 *pr = new Problema_1DEjemp01();
   pr->inicializa(ge, nx);
   
   // Visualiza problema y geometría
   pr->visualizaProblema();   
   ge->visualiza();

   // Metodo de resolución del sistema lineal asociado al método
   ResuelveTridiagonal *rsl = new ResuelveTridiagonal();
   

   // Método de elemento finito
   FEM1D fem(pr, ge, rsl);
   fem.activaVisualiza(true);
   fem.resuelve();
   fem.visualizaSolucion();
   fem.grabaSolucion("Solucion.txt");
   printf("\nError: %le\n\n",fem.error());
   
   
   // Libera la memoria solicitada
   delete rsl;
   delete pr;
   delete ge;
   
   return 0;
}
