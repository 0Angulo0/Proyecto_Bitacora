#include <iostream>
#include <fstream> //leer el archivo
#include <sstream> //separar las lineas
#include <iomanip> //posicionar el texto en donde quieras
#include <vector>
using namespace std;

class info{
    private:
        string mes, hora, ip, falla;
        int dia;
    public:
        info(string mes, int dia, string hora, string ip, string falla){  //& constructor           
            this-> mes = mes;
            this-> dia = dia;
            this-> hora = hora;
            this-> ip = ip;
            this-> falla = falla;
        }
        string design(){  //& titulo de la tabla
            return "FECHA |  HORA  |   DIRECCIÓN IP   | FALLA | \n-----------------------------------------";
        };
        void display(){  //& formato del texto
            cout << setw(3) << left << mes << " | " << setw(2) << left << dia << " | " << setw(8) << left << hora << " | " << setw(16) << left << ip << " |" << setw(40) << left << falla << endl;
        };
        bool operator<(info &in){  //& sobrecarga del operador < 
            string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};  //array con los meses
            int mesIzq = 0, mesDer = 0; //variables donde guardaremos el indice de los meses a comparar
            for (int i = 0; i < 12; i++){
                if (this->mes == meses[i])  //si el mes de la izquierda es igual al mes de i
                mesIzq = i;
                if (in.mes == meses[i])  //si el mes de la derecha es igual al mes i
                mesDer = i;
            }
            if (mesIzq != mesDer)
            return mesIzq < mesDer;
            return this->dia < in.dia;
        }
        void save(vector <info> &b1){  //& creacion de un nuevo txt con el vector acomodado
            ofstream file("bitacoraAcomodada.txt"); //esccribe los datos al archivo
            file << b1[0].design() << endl;
            for(int i = 1; i < b1.size() +1; i++){  //guarda cada objeto
                file << b1[i].mes << " " << b1[i].dia << " " << b1[i].hora << " " << b1[i].ip << " " << b1[i].falla << "\n";
            };
            file.close();  //cierra el archivo ya guardado
            cout << "Cambios guardados con exíto :)" << endl;
        };
};
int partition(vector <info> &b1, int low, int high){
    info pivot = b1[high];  //se establece el pivote central
    int i = low-1;
    for (int j = low; j < high; j++){  //para que se detenga antes de que llegue al valor del pivote
        if (b1[j] < pivot){ //uso de sobrecarga del operados <
            i++;
            swap(b1[i], b1[j]);  //cambio de lugar entre i y j
        }
    }
    swap(b1[i + 1], b1[high]);  //se acomoda el pivote en su lugar
    return i + 1;
}
void quick_sort(vector <info> &b1, int low, int high){
    if (low >= high)  //condición que detiene la recursion
    return;
    int pi = partition(b1, low, high);
    quick_sort(b1, low, pi-1);
    quick_sort(b1, pi +1, high);
}
int main(){
    ifstream file("bitacora.txt"); // lee el archivo
    string line;  //almacena cada linea del archivo
    string values[5]; //columnas
    vector <info> b1; 

    //& añade las lineas del archivo al vector
    while (getline(file, line)){ //lee el archivo linea por linea
        stringstream ss(line);  //convierte la linea en un stream para separarla
        string mes, dia, hora, ip, falla;
        //lee campos hasta el espacio con ss
        ss >> mes;
        ss >> dia;
        ss >> hora;
        ss >> ip;
        getline(ss, falla); //lee el resto de la linea
        // asigna los valores para cada columna
        values[0] = mes;
        values[1] = dia;   
        values[2] = hora;              
        values[3] = ip;                
        values[4] = falla;    
        b1.push_back(info(values[0], stoi(values[1]), values[2], values[3], values[4])); //agregamos el objeto al vector      
    }    
    cout << "Datos agregados al vector :)" << endl;   

    quick_sort(b1, 0, b1.size()-1); //acomoda los datos ingresados por fecha
    cout << "Datos acomodados con exito :)" << endl;
    

    b1[1].display();
    b1[2].display();
    file.close();

    b1[0].save(b1);  //guarda el vector acomodado en un nuevo archivo


    return 0;
}