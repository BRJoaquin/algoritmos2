import java.util.*;
class Actividades 
{ 
    // pre: se asume que estan ordenadas por orden de finalizacion
    public static void maxActiviades(int inicio[], int finalizacion[]) 
    { 
        int ultimaConcurrida; 
        int cantidadDeActividades =  inicio.length; 
        
        // Siempre se concurre a la primera actividad (la que termina antes)
        ultimaConcurrida = 0; 
        System.out.print(ultimaConcurrida+" "); 
        
        // Consideramos el resto de las actividades
        for (int candidata = 1; candidata < cantidadDeActividades; candidata++) 
        { 
            // Si la actividad a considerar empieza despues (o al mismo tiempo) que
            // termina la actividad anterior concurrida, entonces la aceptamos
            if (inicio[candidata] >= finalizacion[ultimaConcurrida]) 
            { 
                System.out.print(candidata+" "); 
                ultimaConcurrida = candidata; 
            } 
        }
        System.out.println(""); 
    } 
       
    public static void main(String[] args) 
    { 
        int inicio[] =        {1, 3, 0, 5, 8, 5}; 
        int finalizacion[] =  {2, 4, 6, 7, 9, 9};
            
        maxActiviades(inicio, finalizacion); 
    }
}
// fuente: https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/