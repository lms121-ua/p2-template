// Letisia Mónica Sandu     x8594224k
// Práctica 0: Conceptos básicos

#include <iostream>
using namespace std;

//DECLARACIÓN MÓDULOS
//función que se encarga de devolver true si a es múltiplo de b o viceversa,
//y false si ninguno de los dos es múltiplo del otro
bool multiple(int a,int b){
  int digitos;
  bool es;

  if(a%b==0 || b%a==0){
    es=true;
  }else{
    es=false;
  }

  return es;
}

//función que se encarga de imprimir por pantalla una N, utilizando
//el caracter *, en función de un valor n. (n: debe ser mayor o igual que 4)
int printN(int n){
  int cantidad;
  cantidad=0;

  if(n>=4){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(j==0 || j==n-1 ||j==i){
          printf("*");
          cantidad++;
        }else{
          printf(" ");
        }
      }
      printf("\n");
    }
    printf("\n");
  }else{
    printf("ERROR\n");
  }
  return cantidad;
}

//función auxiliar que indica si un número es primo o no
bool isPrime(int p){
  bool esPrimo=true;

  if(p<=1){ //p%p==0 || p%1==0 && p>1
    esPrimo=false;
  }else{
    for(int i=2;i<p;i++){
      if(p%i==0){
        esPrimo=false;
        break;
      }
    }
  }

  return esPrimo;
}

//función que se encarga de imprimir los n primeros números primos
//y devuelve su suma
int firstPrimes(int n){
  int encontrado, suma, i;
  suma=0;
  encontrado=0;
  i=0;

  while(encontrado<n){
    if(isPrime(i)==true){
      cout<<i<<" "; 
      encontrado++;
      suma=suma+i;
    }
    i++;
  }

  cout<<endl;

  return suma;
}

void Goldbach(int n,int &p1,int &p2){

  //int i=2, 
  int suma;
  bool iIsPrime, jIsPrime;

  p1=0;
  p2=0;


  for(int i = 2; i < n; i++){
    for(int j = 2; j < n; j++){
      iIsPrime = isPrime(i);
      jIsPrime = isPrime(j);
      if(iIsPrime && jIsPrime){
        suma = i + j;
        if(suma == n){
          //cout<<"i: "<<i<<", j: "<<j<<", suma: "<<suma<<", n: "<<n<<endl;

          //es la primera pareja, guaradmos sin comprobar
          if(p1 == 0 && p2 == 0){
            if(i <= j){
              p1 = i;
              p2 = j;
            } else {
              p1 = j;
              p2 = i;
            }
            break;
          } else {
            if( i <= j && i < p1){
              p1 = i;
              p2 = j;
            } else if( j <= i && j < p1){
              p1 = j;
              p2 = i;
            }
          }
          
        }
      }
    }
    if(p1 != 0 && p2 != 0){
      break;
    }
  }

}


//esta función se encarga de devolver true si n está en el vector y
//false en caso contrario.
bool search(int v[],const int TAMVECTOR,int n){
  bool esta;
  
  for(int i = 0; i < n; i++){
    if(v[i] == n){
      esta=true;
    }else{
      esta=false;
    }
  }
  return esta;
}

//Esta función se encarga de devolver la posición que ocupa n
//dentro del vector o -1 en caso contrario.
int position(int v[],const int TAMVECTOR,int n){
  int pos,i;
  pos=-1;

  for(i = 0; i < n; i++){
    if(v[i] == n){
      pos = i;
    }
  }

  return pos;
}

//esta función se encarga de devolver el numero de veces que n aparece
//en el vector, que puede ser 0 si n no está no el vector
int count(int v[],const int TAMVECTOR,int n){
  int veces, pos, i;

  veces=0;
  for(i = 0; i < TAMVECTOR; i++){
    if(v[i] == n){
      veces++;
    }
  }

  return veces;
}

//esta función se encarga de devolver el mínimo de numeros impares que 
//contenga un vector, o -1 si no contiene ningún numero impar.
int minOdds(int v[],const int TAMVECTOR){
  int veces;

  veces=-1;
  for(int i = 0; i < TAMVECTOR; i++){
    if(v[i] % 2 != 0){
      veces=v[i];
      if(veces < v[i+1]){
        veces=v[i];
      }
    }
  }

  return veces;
}

//esta función se encarga de devolver la posición el máximo
//de los números múltiples de 5 que contenga el vector, o -1
//en caso contario
int posMaxMultFive(int v[], const int TAMVECTOR) {
  int posicion, i, maximo; 
  posicion = -1;
  maximo = -1; // Inicializar con un valor que asegure la comparación en la primera iteración

  for (int i = 0; i < TAMVECTOR; ++i) {
    if (v[i] % 5 == 0 && v[i] > maximo) {
      maximo = v[i];
      posicion = i;
    }
  }

  return posicion;
}

/*
void deleteChar(char str[],char c);
*/
