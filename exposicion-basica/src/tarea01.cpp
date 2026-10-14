#include <iostream>
#include <string>

using namespace std;

void actualizar_calificacion(double& nota_alumno, double nueva_nota){
    cout<<"La nota del alumno era: "<<nota_alumno;
    nota_alumno = nueva_nota;
    cout<<"Las nota del alumno ahora es: "<<nota_alumno;
}

double calcular_estadisticas_alumno(const double parciales[], int num_parciales, double& nota_min, double& nota_max){
    double nMax=0,nMin=10;
    double promedio=0, acumulado=0;
    for (int i=0; i<num_parciales; i++){
        if (parciales[i]> nMax) nMax = parciales[i];
        if (parciales[i]<nMin) nMin = parciales[i];
        acumulado = acumulado + parciales[i];
    }
    nota_max = nMax;
    nota_min = nMin;
    promedio = acumulado / num_parciales;
    return promedio;
}

double aplicar_bonificacion(double nota_original, double porcentaje_extra){
    double nota_final=0, bonus=0;
    bonus = porcentaje_extra *0.01;
    nota_final = (nota_original *(1+bonus));
    return nota_final;
}

/*
const double* buscar_calificacion_perfecta(const double matriz[][3], int filas, int parcial){
    for (int i=0;i<filas;i++) {
        double* perfectas;
        if(matriz[i][parcial] == 10){
                cout<<"Calificaciones PREFECTA DETECTADA en el alumno: "<<i+1;
                perfectas = matriz[i][parcial];
            }
        }
    }
    return alumnosPerfectos;
}

*/

//area de reporte 
void imprimir_sabana_notas(const double matriz[][3], int filas, const string& titulo){
    cout<<titulo<<endl;
    for (int i=0; i< filas; i++){
        for(int j=0;j ; j++){
            cout<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int filas =5;
    string titulo ="calificaciones 2ndo parcial";
    double nota_min =0, nota_max=0;
    double calificaciones[5][3]={
        {10,5,7},
        {8,9,10},
        {9,10,4},
        {7,6,5},
        {8,9,10}
    };

    imprimir_sabana_notas( &calificaciones[3],  filas, titulo);

    actualizar_calificacion(calificaciones[0][0],5);

    for (int i=0;i<5; i++){
        calcular_estadisticas_alumno(calificaciones[i], 3,nota_min,nota_max);
        cout<<"la calificacion minima del alumno "<<i<<" son: "<<nota_min<<endl;
        cout<<"la calificacion maxima del alumno "<<i<<" son: "<<nota_max<<endl;        
    }

    calificaciones[0][1]= aplicar_bonificacion(calificaciones[0][1], 10);

    //buscar_calificacion_perfecta(&calificaciones[3], filas, 2);

    return 0;
}