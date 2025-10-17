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
            //tipo string para poder agregarlo al documento acomodado
            return "FECHA |  HORA  |   DIRECCIÓN IP   | FALLA | \n-----------------------------------------";
        }
        void display(){  //& formato del texto
            //setw estable el espacio que será utilizado por cada columna
            cout << setw(3) << left << mes << " | " << setw(2) << left << dia << " | " << setw(8) << left << hora << " | " << setw(16) << left << ip << " |" << setw(40) << left << falla << endl;
        }
        void save(vector <info> &b1){  //& creacion de un nuevo txt con el vector acomodado
            ofstream file("bitacoraAcomodada.txt");  //crea y abre el archivo
            file << b1[0].design() << endl;  //escribe el titulo de la tabla
            for(int i = 0; i < b1.size(); i++){  //guarda cada objeto
                file << b1[i].mes << " " << b1[i].dia << " " << b1[i].hora << " " << b1[i].ip << " " << b1[i].falla << "\n";
            };
            file.close();  //cierra el archivo ya guardado
            cout << "Cambios guardados con exíto :)" << endl; 
        }
        int binarySearch_inicio(vector<info> &b1, string mesElegido, int diaElegido, int low, int high) {  //&busqueda binaria para la fecha de inicio
            //Complejidad: O(logn)
            if (low > high) {  //caso donde termina la recursion
                return low;
            }
            int mid = low + (high - low) / 2; // calcula el punto medio
            string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};  //array con los meses
            int mesMid = 0, mesBuscar = 0; 
            for (int i = 0; i < 12; i++) {  //mes a numero (con el index)
                if (b1[mid].mes== meses[i]) { 
                    mesMid = i; }
                if (mesElegido == meses[i]) { 
                    mesBuscar = i; }
            }
            //comparacion de meses y dias
            if (mesMid > mesBuscar) {  //mes actual > al mes objetivo
                return binarySearch_inicio(b1, mesElegido, diaElegido, low, mid - 1);  //busca a la izquierda
            } else if (mesMid < mesBuscar) {  //mes actual < mes objetivo
                return binarySearch_inicio(b1, mesElegido, diaElegido, mid + 1, high);  //busca a la derecha
            } else {   //meses iguales, seguimos a comparar dias
                if (b1[mid].dia >= diaElegido)   //dia es igual al del usuario o está en el lado izquierdo
                return binarySearch_inicio(b1, mesElegido, diaElegido, low, mid - 1);
                return binarySearch_inicio(b1, mesElegido, diaElegido, mid + 1, high);  //el dia esta en el lado derecho
            }
        }
        int binarySearch_final(vector<info> &b1, string mesElegido, int diaElegido, int low, int high) { //&busqueda binaria para la fecha del final
            if (low > high) {  //caso donde termina la recursion
                return high;
            }
            int mid = low + (high - low) / 2; // calcula el punto medio
            string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};  //array con los meses
            int mesMid = 0, mesBuscar = 0; 
            for (int i = 0; i < 12; i++) {  //mes a numero (con el index)
                if (b1[mid].mes == meses[i]) { 
                    mesMid = i; }
                if (mesElegido == meses[i]) { 
                    mesBuscar = i; }
            }
            //comparacion de meses y dias
            if (mesMid > mesBuscar) {  //mes actual>al mes objetivo
                return binarySearch_final(b1, mesElegido, diaElegido, low, mid - 1);  //busca a la izquierda
            } else if (mesMid < mesBuscar) {  //mes actual < mes objetivo
                return binarySearch_final(b1, mesElegido, diaElegido, mid + 1, high);  //busca a la derecha
            } else {   //meses iguales, seguimos a comparar dias
                if (b1[mid].dia <= diaElegido)   //dia es igual al del usuario o está en el lado izquierdo
                return binarySearch_final(b1, mesElegido, diaElegido, mid + 1, high);
                return binarySearch_final(b1, mesElegido, diaElegido, low, mid - 1);  //el dia esta en el lado derecho
            }
        }
        void print(vector <info> &b1, int inicio, int final){  //& imprime los valores en el rango encontrado
            cout << "FECHA |  HORA  |   DIRECCIÓN IP   | FALLA | \n-----------------------------------------" << endl;  //titulo de la tabla
            for (int i = inicio; i < final + 1; i++){
                b1[i].display();
            }
        }
        bool operator<(info &in){  //& sobrecarga del operador < usado para el quick sort
            //tipo bool ya que es comparacion. Complejidad: O(1)
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
};
int partition(vector <info> &b1, int low, int high){   //& pivote
    //Complejidad: O(n)
    info pivot = b1[high];  //se establece el pivote central
    int i = low-1;
    for (int j = low; j < high; j++){  //para que se detenga antes de que llegue al valor del pivote
        if (b1[j] < pivot){ //uso de sobrecarga del operador <
            i++;
            swap(b1[i], b1[j]);  //cambio de lugar entre i y j
        }
    }
    swap(b1[i + 1], b1[high]);  //se acomoda el pivote en su lugar
    return i + 1;
}
void quick_sort(vector <info> &b1, int low, int high){  //& acomodo del vector ascendente
    //"divide y vencerás". Complejidad: O(n^2)
    if (low >= high)  //condición que detiene la recursion
    return;
    int pi = partition(b1, low, high);
    quick_sort(b1, low, pi-1);  //izquierda
    quick_sort(b1, pi +1, high);  //derecha
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
    file.close();
    cout << "Datos agregados al vector :)" << endl;   

    quick_sort(b1, 0, b1.size()-1); //acomoda los datos ingresados por fecha
    cout << "Datos acomodados con exito :)" << endl;

    b1[0].save(b1);  //guarda el vector acomodado en un nuevo archivo
    
    int diaInicial, diaFinal;  //variables usadas para respuestas del usuario
    string mesInicial, mesFinal;
    cout << "\n Busqueda en la bítacora de errores" << endl;  //busqueda por rango
    cout << "¿Cuál es el mes en el que quiere empezar la busqueda? Escriba las primeras 3 letras del mes en ingles: Jan, Feb, etc." << endl;
    cin >> mesInicial;
    cout << "¿Cuál es el día en el que quiere empezar la busqueda?" << endl;
    cin >> diaInicial;
    cout << "¿Cuál es el mes en el que quiere terminar la busqueda? Escriba las primeras 3 letras del mes en ingles: Jan, Feb, etc." << endl;
    cin >> mesFinal;
    cout << "¿Cuál es el día en el que quiere terminar la busqueda?" << endl;
    cin >> diaFinal;
    int inicio = b1[0].binarySearch_inicio(b1, mesInicial, diaInicial, 0, b1.size()-1);  //llama a la busqueda para la primera decha
    int Final = b1[0].binarySearch_final(b1, mesFinal, diaFinal, 0, b1.size()-1);  //llama a la busqueda para la fecha final
    
    if (inicio > Final || inicio >= b1.size() || Final < 0) {
    cout << "No se encontraron registros entre " << mesInicial << " " << diaInicial << " y " << mesFinal << " " << diaFinal << endl;
    cout << "Por favor, revise que los datos ingresados fueron escritos de forma correcta." << endl;
    } else {
        cout << "\n Resultados de la búsqueda: " << endl;
        b1[0].print(b1, inicio, Final);//imprime el rango de datos encontrados
        cout << "Valores encontrados: " << Final - inicio << endl;
    }

    return 0;
}