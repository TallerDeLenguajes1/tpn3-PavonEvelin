#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef struct Producto {
  int ProductoID; //Numerado en ciclo iterativo
  int Cantidad; // entre 1 y 10
  char *TipoProducto; // Algún valor del arreglo TiposProductos
  float PrecioUnitario; // entre 10 - 100
}producto;

typedef struct Cliente {
  int ClienteID; // Numerado en el ciclo iterativo
  char *NombreCliente; // Ingresado por usuario
  int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
  producto *Productos;//El tamaño de este arreglo depende de la variable
                      // “CantidadProductosAPedir”
}cliente;

char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

void mostrar(cliente *Clientes, int cantClientes);
float costoTotal(cliente *Cliente);

int main(void) {
  srand(time(NULL));
  char nombre[MAX];
  int cantClientes, aleatorio, tamanio;
  cliente *Clientes;
  producto *Productos;

  printf("Por favor, Ingrese la cantidad de clientes (no debe ser mayor a 5)\n");
  scanf("%d", &cantClientes);

  Clientes = (cliente *)malloc(sizeof(cliente) * cantClientes);//reservo memoria dinamica para la cantidad de clientes ingresada por el usuario.

  //CARGA DE CADA CLIENTE 
  puts("Ingrese el nombre de los clientes a continuación separado por espacios");
  for(int i=0; i<cantClientes;i++){
    gets(nombre);
    Clientes[i].ClienteID = i; 
    strcpy(Clientes[i].NombreCliente, nombre);
    Clientes[i].CantidadProductosAPedir = rand()%10 + 1;
    Clientes[i].Productos = (producto *)malloc(sizeof(producto)*Clientes[i].CantidadProductosAPedir);
    for(int j=0; j<Clientes[i].CantidadProductosAPedir; j++){
      (Clientes[i].Productos[j]).ProductoID = j+1;
      (Clientes[i].Productos[j]).Cantidad = rand()%10 + 1;
      aleatorio = rand()%5;
      tamanio = strlen(TiposProductos[aleatorio]);
      (Clientes[i].Productos[j]).TipoProducto = (char *)malloc(sizeof(tamanio));
      strcpy((Clientes[i].Productos[j]).TipoProducto, TiposProductos[aleatorio]);
      (Clientes[i].Productos[j]).PrecioUnitario = rand()%91 + 10;
    }
  }

  return 0;
}

float costoTotal(cliente *Clientes){
  cliente auxCliente;
  float total;
  total = auxCliente.Productos->PrecioUnitario * auxCliente.Productos->Cantidad;
  auxCliente = *Clientes;
  return total;
}

void mostrar(cliente *Clientes, int cantClientes){
  float suma;
  printf("LISTA DE CLIENTES\n\n");
  for(int i=0; i<cantClientes; i++){
    printf("Cliente N°%d\n", i+1);
    printf("ID: %d\n", Clientes[i].ClienteID);
    printf("Nombre: %s\n", Clientes[i].NombreCliente);
    printf("Cantidad de productos pedidos: %d\n", Clientes[i].CantidadProductosAPedir);
    printf("\nLista de productos\n");
    suma = 0;
    for(int j=0; j<Clientes[i].CantidadProductosAPedir; j++){
      printf("ID: %d\n",(Clientes[i].Productos[j]).ProductoID);
      printf("Tipo de producto: %s\n",(Clientes[i].Productos[j]).TipoProducto);
      printf("Cantidad de %s: %d\n",(Clientes[i].Productos[j]).TipoProducto,(Clientes[i].Productos[j]).Cantidad);
      printf("Precio unitario: %.2f\n", (Clientes[i].Productos[j]).PrecioUnitario);
      printf("Costo total del producto: %f\n", costoTotal(Clientes));
      suma+= costoTotal(Clientes);
    }
    printf("El total a pagar del cliente es: %.2f", suma);
  }
}