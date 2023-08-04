#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


struct repartidor {
   char nya[36];
   unsigned dni;
   char patente[20];
   unsigned zona;
};

repartidor info(int [], int&,int []);
void inicializar (int []);
void ordenar (int,repartidor v[]);
bool compvehiculo (int);
bool compdni (int,int,int []);
void zonaConMasVehiculos(int[]);
void trasporteNoDisp(int, int, int, int);
void cantRepxZona(int cuentazonas[], int contadorAutosPorZona[], int contadorCamionesPorZona[], int contadorCamionetasPorZona[], int contadorMotosPorZona[]);
void generarArchivos(int,repartidor v[],char [21]);


int main ()
{
    char te;
    int contaut=0,contcamion=0,contcamioneta=0,contmoto=0,cuentazonas[14],contdni=0;
    repartidor aut[280],moto[280],camioneta[280],camion[280];
    int contadorAutosPorZona[14] = {0};
    int contadorCamionesPorZona[14] = {0};
    int contadorCamionetasPorZona[14] = {0};
    int contadorMotosPorZona[14] = {0};
    inicializar (cuentazonas);
    cout<<"Ingrese vehiculo (A=auto,C=camion,T=camioneta,M=moto,N=fin de ingreso): "<<endl;
    cin>>te;
    while(compvehiculo (te))
    {
        cout<<"vehiculo no valido vuelva a ingresar: "<<endl;
        cin>>te;
    }
    if (te=='N' || te=='n')         
    {
        cout<<"No hubo ingresos";
        return 0;
    }
    else
    {
    while (te!='N') //La persona elige que vehiculo y lo comparamos en un switch, segun cual se haya elegido mandamos el strcut del vehiculo a la funcion de llenado 
{
        switch (te)
    {
        case 'A': 
        case 'a':
        aut[contaut]=info (cuentazonas,contdni,contadorAutosPorZona);
        if (aut[contaut].dni!=0  && aut[contaut].zona!=0)
        {
        contaut++;
        }
        break;
        case 'C': 
        case 'c':
        camion[contcamion]=info (cuentazonas,contdni,contadorCamionesPorZona);
        if (camion[contcamion].dni!=0 && camion[contcamion].zona!=0)
        {
        contcamion++;
        }
        break;
        case 'T': 
        case 't':
        camioneta[contcamioneta]=info (cuentazonas,contdni,contadorCamionetasPorZona);
        if (camioneta[contcamioneta].dni!=0 && camioneta[contcamioneta].zona!=0)
        {
        contcamioneta++;
        }
        break;
        case 'M': 
        case 'm':
        moto[contmoto]=info (cuentazonas,contdni,contadorMotosPorZona);
        if (moto[contmoto].dni!=0 && moto[contmoto].zona!=0)
        {
        contmoto++;
        }
        break;
        default: cout<<"Letra no valida vuelva a intentar"<<endl;
    }
    cout<<"Ingrese vehiculo (A=auto,C=camion,T=camioneta,M=moto,N=fin de ingreso): "<<endl;
    cin>>te;
    while(compvehiculo (te))
    {
        cout<<"vehiculo no valido vuelva a ingresar: "<<endl;
        cin>>te;
    }
}
char nomauto[21]="RepAuto";
char nomcamion[21]="RepCamion";
char nomcamioneta[21]="RepCamioneta";
char nommoto[21]="RepMoto";
ordenar (contaut,aut);
ordenar (contcamion,camion);
ordenar (contcamioneta,camioneta);
ordenar (contmoto,moto);
zonaConMasVehiculos(cuentazonas);
trasporteNoDisp(contaut,contmoto,contcamion,contcamioneta);
cantRepxZona(cuentazonas, contadorAutosPorZona, contadorCamionesPorZona, contadorCamionetasPorZona, contadorMotosPorZona);
generarArchivos(contaut,aut,nomauto);
generarArchivos(contcamion,camion,nomcamion);
generarArchivos(contcamioneta,camioneta,nomcamioneta);
generarArchivos(contmoto,moto,nommoto);
return 0;
    }
}

void inicializar (int v[])
{
   for (int i=0;i<14;i++)
   v[i]=0;
}

repartidor info(int vzongeneral[],int &tamdni,int vzonparticular[])
{
    repartidor r;
    int zona,dni,vdnis[1120];
    cout<<"Ingrese su DNI: "<<endl;
    cin>>dni;
    if (compdni(tamdni,dni,vdnis))
    {
       r.dni=dni;
       vdnis[tamdni]=dni;
       tamdni++;
    }
    else
    {
        cout<<"Usted no puede ingresarse mas de 1 vez deje a la siguiente persona"<<endl;
        r.dni=0;
        return r;
    }
    cout<<"Ingrese nombre y apellido: "<<endl;
    cin.ignore();
    cin.getline(r.nya,36);
    cout<<"Ingrese patente del vehiculo: "<<endl;
    cin.getline(r.patente,20);
    do {
        cout<<"Ingrese la zona en la que quiere trabajar (de 1 a 14): "<<endl;
        cin>>zona;
        if (zona< 1 || zona>14) {
            cout<<"La zona es invalida, vuelva a ingresar."<<endl;
        }
    } while (zona<1 || zona>14);
    if (vzonparticular[zona-1]<20) 
    {
    r.zona=zona;  //número de documento del repartidor, nombre y apellido, patente del vehículo y código de zona 
    vzongeneral[zona-1]++;
    vzonparticular[zona-1]++;
    }
    else
    {
       cout<<"Esa zona esta completa vuelva a ingresar sus datos o deje a la siguiente persona"<<endl;
      r.zona=0;
    }
    
   

    return r;
}

void ordenar (int tam,repartidor vec[])
{
    unsigned i=1;
    int aux1,aux4;
    char aux2[36],aux3[20];
    bool prim;
    if (tam!=0)
    {
    do
    {
        prim=false;
        for(int j=0;j<tam-i;j++)
        {
            if(vec[j].dni>vec[j+1].dni)
            {
                aux1=vec[j].dni;
                vec[j].dni=vec[j+1].dni;
                vec[j+1].dni=aux1;
                strcpy(aux2,vec[j].nya);
                strcpy(vec[j].nya,vec[j+1].nya);
                strcpy(vec[j+1].nya,aux2);
                strcpy(aux3,vec[j].patente);
                strcpy(vec[j].patente,vec[j+1].patente);
                strcpy(vec[j+1].patente,aux3);
                aux4=vec[j].zona;
                vec[j].zona=vec[j+1].zona;
                vec[j+1].zona=aux4;
                prim=true;
            }
        }
        i++;
    }while(i<tam && prim);
    }
}

bool compvehiculo (int vehiculo)
{
    if (vehiculo!='A' && vehiculo!='T' && vehiculo!='M' && vehiculo!='C' && vehiculo!='N' && vehiculo!='a' && vehiculo!='t' && vehiculo!='m' && vehiculo!='c' && vehiculo!='n')
    return true;
    else
    return false;
}

bool compdni (int tam,int bus,int vdni[])
{
   unsigned i=0;
    while (i<tam && vdni[i]!=bus)
    {
    i++;
    }
    if (i==tam)
    return true;
    else
    return false;
}

void cantRepxZona(int cuentazonas[], int contadorAutosPorZona[], int contadorCamionesPorZona[], int contadorCamionetasPorZona[], int contadorMotosPorZona[])
{
    cout << "Cantidad de repartidores por zona y vehiculo:"<<endl;
    for (int i = 0; i < 14; i++)
    {
        cout<< "Zona "<<i + 1<< ":"<<endl;
        cout<< "Autos: "<<contadorAutosPorZona[i]<<endl;
        cout<< "Camiones: "<<contadorCamionesPorZona[i]<<endl;
        cout<< "Camionetas: "<<contadorCamionetasPorZona[i]<<endl;
        cout<< "Motos: "<<contadorMotosPorZona[i]<<endl;
    }
}

void generarArchivos(int tamreal,repartidor vector[], char nombrearch[21])
{
    FILE *arch;
    strcat (nombrearch,".dat");
    arch=fopen(nombrearch, "wb");
    if (arch==NULL)
        cout<<"Error de creacion de archivo "<<nombrearch<<endl;
    else
    {
       for (int i=0;i<tamreal;i++)
       {
        fwrite (&vector[i],sizeof(repartidor),1,arch);
       }
    }
    fclose (arch);
}



void zonaConMasVehiculos(int vzonas[]){ //fun que informa que zona tiene mas repartidores inscriptos
    int mayor = 0, zonaP;
    for (int i = 0; i<14; i++){
        if (vzonas[i] > mayor)
        {
            mayor = vzonas[i]; // la cantidad de repartidores inscriptos
        }
    }
    cout<<"La/s zona/s con mayor cantidad de inscriptos fue/ron: ";
    for (int j=0;j<14;j++)
    {
        if (vzonas[j]==mayor)
        {
        cout<<"la zona "<<j+1<<"    ";
        }
    }
    cout<<endl;
}





/*3)Informar, si hubo, qué medios de transporte no habrá disponibles,
por no haber ningún inscripto, para la
realización de entregas (sin importar la zona).
Se define si el contador del vehículo es 0 o no.
*/
void trasporteNoDisp(int contAuto, int contMoto, int contCamion, int contCamioneta){
    if(contAuto == 0){
        cout<<"No hay autos disponibles para realizar entregas, ya que no hay ningún inscripto"<<endl;
    }
    if(contMoto == 0){
        cout<<"No hay motos disponibles para realizar entregas, ya que no hay ningún inscripto"<<endl;
    }
    if(contCamioneta == 0){
        cout<<"No hay camionetas disponibles para realizar entregas, ya que no hay ningún inscripto"<<endl;
    }
    if(contCamion == 0){
        cout<<"No hay camiones disponibles para realizar entregas, ya que no hay ningún inscripto"<<endl;
    }
}
