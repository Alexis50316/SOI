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
  semaphore cuenta con tres elementos.
  Un entero que representa el estado del semáforo,
  una variable mutex, control_valor, que se usa para 
  controlar el acceso y modificación de la variable valor. 
  una variable mutex, control_procesos, que se usa  para bloquear 
  y desbloquear procesos.

*/

struct semaphore_t {
  int valor;
  pthread_mutex_t control_valor;
  pthread_mutex_t control_procesos;
}

typedef struct semapfore_t sem_t;


/*
  NOTA: las funciones retornaran 1 si funcionaron correctamente, en casa contrario 0.
*/


/* Función de creación de Semáforo */
int sem_init(sem_t *sem, int init){
  int a;
  sem->valor = valor; 
  pthread_mutex_t control;
  pthread_mutex_t procesos;
  a = pthread_mutex_init(&control,NULL);
  a += pthread_mutex_init(&procesos,NULL);
  sem->control_valor = control;
  sem->control_procesos = procesos;
  if(a == 0) return 1;
  return 0;
}


/* 
  Incremento del semáforo. 
  Cuando un hilo aumenta el semáforo, si hay un hilo esperando
  este se activa. Si hay varios esperando alguno se activa .
*/
int sem_incr(sem_t *sem)
{ 
  int a;
  a = pthread_mutex_lock(&sem->control_valor);
  sem->valor++;
  a += pthread_mutex_unlock(&sem->control_valor);
  if(!(sem->valor > 0)) a+= pthread_mutex_lock(&sem->control_procesos);
  
  if(a == 0) return 1;
  return 0;
}


/*
  Cuando un hilo decrementa el valor del semáforo, si este es
  negativo, el hilo se bloquea a sí mismo y no puede continuar 
  hasta que otro hilo incremente el semáforo.
   
  Decremento del semáforo. Notar que es una función que puede llegar a bloquear
  el proceso.
*/
int sem_decr(sem_t *sem)
{ 
  int a;
  a = pthread_mutex_lock(&sem->control_valor);
  sem->valor-=1;
  a += pthread_mutex_unlock(&sem->control_valor); 
  if(sem->valor < 0) a += pthread_mutex_lock(&sem->control_procesos);

  if(a == 0) return 1;
  return 0;
}


/* Destrucción de un semáforo */
int sem_destroy(sem_t *sem){
  int a ;
  a = pthread_mutex_destroy(&sem->control_valor);
  a += pthread_mutex_destroy(&sem->control_procesos);
  free(sem);
  if(a == 0) return 1;
  return 0;
}

