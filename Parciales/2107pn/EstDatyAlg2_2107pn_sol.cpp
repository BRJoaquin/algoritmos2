// Ejercicio 1
/*
    a.  La táctica de D&C contiene tre etapas: dividir, conquistar y merge.
    Dividir: trata de separar el problema en sub-problemas (problemas de menor tamaño) para hasta un momento llegar a los casos base.
    Conquistar: se trata de usar la recursion para obtener sub-soluciones de los sub-problemas de la etapa anterior.
    Merge: en la última etapa se utilizan las sub-soluciones para formar la solución final.

    La dificultad, por lo general se presenta en la primera ó última etapa. 
    Los algoritmos D&C que son dificiles de dividir pero faciles de unir => hard-split-easy-join (ejemplo quick-sort)
    Los algoritmos D&C que son faciles de dividir pero dificiles de unir => easy-split-hard-join (ejemplo merge-sort)

    b.  La desventaja más notoria de una algoritmo greedy se basa en su principal filosofia:
    "Decisiones optimas locales nos conducen a soluciones optimas globales".
    Esto no siempre es cierto, ya que existen problemas en los cuales dichas decisiones locales no nos llevan la mejor solución.
    Por ejemplo, el problema de la mochila. Donde no importa el enfoque que yo tome (mejor valor, o mejor ratio), existian ejemplos
    en los cuales no me daba una mejor solución.

    c.  La memoización es una herramienta utilizada para guardar datos previamente calculados, básicamente puede verse como cache.
    La programación dinámica, es una táctica que resuelve problemas en lo cuales tienen sub-problemas que se superponen.
    Haciendo uso de la memoización (top-down) ó de la tabulación (botton-up) la PD resuelve el hecho de no tener que volver
    a computar dichos sub-problemas.
    Un algoritmo de PD se puede resolver con memoización, pero no es necesario si se resuelve con tabulación.

*/

// Ejercicio 2
/*
    a.  La poda es una mejora/optimización dentro de BT. Nos ayuda en un momento dado para saber que la solucion candidata (quizas aún no terminada),
    no va resultar un mejor solución de la ya encontrada hasta el momento.
    Es muy común encontrarla en problemas de optmización que quieran reducir la métrica utilizada (lo que mide que tan buena es mi solución).

    Es buena práctica realizar poda cada vez que se pueda, porque podría determinar si el algoritmo termina en un tiempo razonable o simplemente
    la ramificación es tan extensa-profunda que no es útil el algoritmo.

    b.  No, no es siempre posible. Cómo ya dijimos esta relacionada con BT de optimización, por ejemplo un problema de enumeración o de 
    decisión, no existe poda.
    De todas maneras, incluso en problemas de opmización podrían existir casos en donde no es aplicable. Por ejemplo en aquellos casos
    en los que se quiera maximizar una métrica.

    c.  FB crea soluciones finales y luego evaluarla, BT construye las soluciones paso a paso y evalua en cada paso.
    BT evalua en cada paso si se puede realizar dicha acción (movimiento) o poda por ende, puede descartar todos los sub-arboles de decision que no pasan dichas pruebas.
    Dichos sub-arboles descartados se traducen en un mejor orden temporal.
    Hay que tener en cuenta que dependiendo el tipo de problema y la implementacion del algoritmo de BT puede no cortar tantos sub-arboles como
    para que sea significativo.

*/

// Ejercicio 3
#include <string>
#include <iostream>
using namespace std;

// limites
#define Al_MAX 50
#define Si_MAX 60
#define Fe_MAX 100
// valores x kilogramo
#define Al_VALOR 10
#define Si_VALOR 20
#define Fe_VALOR 5
// cantidad de piedras
#define N 10

int max(int a, int b)
{
    return a > b ? a : b;
}
// inicializa una matriz de 4 dimensiones:
// cantidad de objetos con los tres limites (Ai,Si,Fe)
int ****initMatriz()
{
    int ****m = new int ***[N];
    for (int i = 0; i < N; i++)
    {
        m[i] = new int **[Al_MAX + 1];
        for (int j = 0; j < Al_MAX + 1; j++)
        {
            m[i][j] = new int *[Si_MAX + 1];
            for (int k = 0; k < Si_MAX + 1; k++)
            {
                m[i][j][k] = new int[Fe_MAX + 1]();
            }
        }
    }
    return m;
}
// evalua si la roca puede entrar con la capacidad dada por parametro
bool laRocaEntra(int pesoAi, int pesoSi, int pesoFe, int capacidadAi, int capacidadSi, int capacidadFe)
{
    return pesoAi <= capacidadAi && pesoSi <= capacidadSi && pesoFe <= capacidadFe;
}
// dado los pesos de los elementos que componen la roca, devuelve el valor de la misma
int valorDeLaRoca(int pesoAi, int pesoSi, int pesoFe)
{
    return (pesoAi * Al_VALOR) + (pesoSi * Si_VALOR) + (pesoFe * Fe_VALOR);
}

int fundidora(int ai[N], int si[N], int fe[N])
{
    // matriz de 4 dimensiones
    int ****m = initMatriz();
    for (int obj = 0; obj < N; obj++)
    {
        for (int aiHasta = 0; aiHasta < Al_MAX + 1; aiHasta++)
        {
            for (int siHasta = 0; siHasta < Si_MAX + 1; siHasta++)
            {
                for (int feHasta = 0; feHasta < Fe_MAX + 1; feHasta++)
                {
                    // estamos parados en el primer objeto
                    if (obj == 0)
                    {
                        // solo en el caso de que entre vamos a tener valor, sino 0 (valor por defecto de la matriz)
                        if (laRocaEntra(ai[obj], si[obj], fe[obj], aiHasta, siHasta, feHasta))
                        {
                            m[obj][aiHasta][siHasta][feHasta] = valorDeLaRoca(ai[obj], si[obj], fe[obj]);
                        }
                    }
                    else
                    {
                        // en el caso de que la roca no entre, ignoramos el objeto
                        if (!laRocaEntra(ai[obj], si[obj], fe[obj], aiHasta, siHasta, feHasta))
                        {
                            m[obj][aiHasta][siHasta][feHasta] = m[obj - 1][aiHasta][siHasta][feHasta];
                        }
                        else
                        {
                            // evaluamos si es mejor usar o no usar la roca.
                            int valorDeUsarLaRoca = valorDeLaRoca(ai[obj], si[obj], fe[obj]) + m[obj - 1][aiHasta - ai[obj]][siHasta - si[obj]][feHasta - fe[obj]];
                            int valorDeNOUsarLaRoca = m[obj - 1][aiHasta][siHasta][feHasta];
                            m[obj][aiHasta][siHasta][feHasta] = max(valorDeUsarLaRoca, valorDeNOUsarLaRoca);
                        }
                    }
                }
            }
        }
    }

    return m[N-1][Al_MAX][Si_MAX][Fe_MAX];
}

int main()
{
    int ai[10] = {20, 10, 30, 50, 00, 10, 70, 00, 05, 20};
    int si[10] = {10, 20, 50, 70, 00, 00, 35, 12, 23, 10};
    int fe[10] = {80, 90, 50, 10, 20, 80, 90, 00, 12, 34};

    cout << fundidora(ai, si, fe) << endl;
    return 0;
}