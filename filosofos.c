#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N_FILOSOFOS 5
#define ESPERA 5000000

//para ver el estado de los demas filosofos 
#define IZQUIERDA(x)  ((x) !=0 ? (x)-1 : (N_FILOSOFOS-1)) //Calcula el filosofo de la izqda
#define DERECHA(x)    (((x)+1)%N_FILOSOFOS) //Calcula el filosofo de la dcha


//estados de los filosofos.
typedef enum{
  PENSANDO,HAMBRIENTO,COMIENDO
}status;

status estado[N_FILOSOFOS]; //Estado en el que esta cada proceso en cada momento (pensando, hambriento o comiendo)


pthread_mutex_t tenedor[N_FILOSOFOS];

void pensar(int i)
{
  printf("Filosofo %d pensando...\n",i);
  usleep(random() % ESPERA);
}


void comer(int i)
{
  printf("Filosofo %d comiendo...\n",i);
  usleep(random() % ESPERA);
}

/*
  observar: int -> void 
  se encarga de ver si los filosofos que estan a derecha e izquierda  estan comiendo, en caso de estarlo
  espera hasta que terminen, luego de eso pasa a comer.
*/
void observar(int id) 
{ 
  while(estado[id] == HAMBRIENTO && (estado[IZQUIERDA(id)] == COMIENDO && estado[DERECHA(id)] == COMIENDO));
  estado[id]=COMIENDO;
}



void tomar_tenedores(int i)
{ 
  estado[i]=HAMBRIENTO;//agregado
  observar(i);//agregado //se cambia el + 1 por -1 
  pthread_mutex_lock(&tenedor[i]); /* Toma el tenedor a su derecha */
  pthread_mutex_lock(&tenedor[(i+1)%N_FILOSOFOS]); /* Toma el tenedor a su izquierda */
}


void dejar_tenedores(int i)
{
  pthread_mutex_unlock(&tenedor[i]); /* Deja el tenedor de su derecha */
  pthread_mutex_unlock(&tenedor[(i+1)%N_FILOSOFOS]); /* Deja el tenedor de su izquierda */
  estado[i]=PENSANDO;//agregado se cambia a -1 el codigo tenia +1

}

void *filosofo(void *arg)
{
  int i = (int)arg;
  for (;;)
  {
    tomar_tenedores(i);
    comer(i);
    dejar_tenedores(i);
    pensar(i);
  }
}


int main()
{  

  extern status estado[N_FILOSOFOS]; //No es necesario//agregado


  int i;
  pthread_t filo[N_FILOSOFOS];

  //parte agregada
  for(i=0;i<N_FILOSOFOS;i++)        //NO SE PUEDEN LANZAR LOS HILOS HASTA QUE LOS SEMAFOROS NO ESTEN INICIALIZADOS
  {
    estado[i]=PENSANDO;
  }
  //parte agregada

  for (i=0;i<N_FILOSOFOS;i++)
    pthread_mutex_init(&tenedor[i], NULL);
  for (i=0;i<N_FILOSOFOS;i++)
    pthread_create(&filo[i], NULL, filosofo, (void *)i);
  pthread_join(filo[0], NULL);
  return 0;
}

