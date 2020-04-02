/*
  Los semáforos son otra solución propuesta por Dijkstra. Un semáforo al igual 
  que los semáforos en la vida real servirán para indicar cuándo pueden o no 
  ingresar hilos a una región en particular.
  Los semáforos contienen internamente un contador, el cual se le asigna un 
  valor al ser creado , y luego solo se puede aumentar o decrementar. Son 
  varios números enteros, con las siguientes funcionalidades:

  _Al momento de crear un semáforo se le asigna un entero . Luego, de ser creado, 
  solo se puede aumentar o disminuir su valor.
  _Cuando un hilo decrementa el valor del semáforo, si este es negativo, el hilo 
  se bloquea a sí mismo y no puede continuar hasta que otro hilo incremente 
  el semáforo.
  _Cuando un hilo aumenta el semáforo, si hay un hilo esperando este se activa. 
  Si hay varios esperando alguno se activa .

  Cuando un hilo se bloquea a si mismo significa que avisa al planificador que 
  este ya no puede continuar. El planificador entonces lo detiene de continuar 
  su ejecución hasta que vuelva a estar activo.
  A tener en cuenta:

  Cuando un hilo aumenta el semáforo es posible que se active otro hilo. Ambos hilos 
  se ejecutan simultáneamente, y no se puede asumir el orden alguno en su ejecución .
  No se debe asumir que algún hilo está a la espera del semáforo.

  Por ende, un semáforo posee el siguiente significado:

  Si es positivo, este representa el número de hilos que pueden decrementarlo 
  sin bloquearse.
  Si es negativo, este representa el número de hilos que lo decrementaron y 
  están bloqueados.
  Si es cero, significa que no hay ningún hilo esperando, pero si alguien lo 
  decrementa este se bloqueará.


*/

#include <pthread.h>

/*
  semaphore cuenta con dos elementos.
  Un contador, que siempre vale >= 0.
  un pthread_mutex_t que indica el proceso actual.
  Una cola de procesos inicialmente vacía.

*/
struct semaphore_t{
  int valor;
  pthread_mutex_t pactual;
  cola precesos;
}*semaphore_t;

typedef struct semaphore_t sem_t;


sem_t crear_sem()
{ 
  sem_t sem = malloc(sizeof(semaphore_t));
  return sem;
}


/* Función de creación de Semáforo */
int sem_init(sem_t *sem, int init){
  sem->valor = valor; 
  sem->procesos = NULL;
}


/* Incremento del semáforo. */
int sem_incr(sem_t *sem)
{
  if(!cola_es_vacia(sem->procesos)) 
    cola_desencolar(sem->procesos);
  sem->valor++;
}


/* Decremento del semáforo. Notar que es una función que puede llegar a bloquear
   el proceso.*/
int sem_decr(sem_t *sem)
{
  if(sem->valor <= 0) {
  	proceso_bloqueado(sem->pactual);
    cola_encolar(sem->procesos,sem->pactual);
  }
  sem->valor-=1;
}

/* Destrucción de un semáforo */
int sem_destroy(sem_t *sem){
	cola_liberar(sem->proceosos);
	free(sem);
}

/*
  preguntas: 
  *como hacer las funciones bloquear y desbloquear procesos.
  *porque las funciones retornan un entero.

*/
