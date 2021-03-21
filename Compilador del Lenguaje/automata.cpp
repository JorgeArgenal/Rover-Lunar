#include<iostream>
#include<string>


using namespace std;
int cantPalabras(string palabrasReservadas);

int cantPalabras(string palabrasReservadas){
	int cantPalabras;
	for (int i=0; i<sizeof(palabrasReservadas);i++){
		cantPalabras++;
	}
	return cantPalabras;
}

int main(){
   //tipo de dato estados
    enum TEstado{q0,q1,q2};
	
    //variable estados
    TEstado Estado;
  	//lista con las palabras clave  
	string palabrasClave[]={"girarRuedas", "cambiarAltura", "girarCamara", "inclinarCamara", "avanzar", "retroceder", "detener", "tomarFoto", "enviarFoto", "while", "for", "do", "si", "entonces", "sino", "var", "int", "float", "String", "bool"};
	char separador= ' ';
	char introducido[40];
	string convertido;
	cout<<"Introduzca algo : ";
	cin.getline(introducido,separador);
	convertido="girarRuedas";
	string separada;
	bool encontro=false;
	
	if("girarRuedas"==palabrasClave[0]){
		cout<<"Si es igual";
	}else{
		cout<<"no es igual";
	}
	cout<<endl;
	
	if(convertido==palabrasClave[0]){
		cout<<"Si es igual";
	}else{
		cout<<"no es igual";
	}
	cout<<endl;
	
	//luego de analizar si la palabra es una palabra clave, probar si es un valor (numero racional) para que sea valido y luego verificar que la siguiente palabra sea Grados o Metros
	//para los valores racionales, hacer una funcion que reciba string y devuelva un valor booleano, esta funcion verificara si el string recibido (palabra separada) es un numero racional, esto se hara con el automata que ya tenemos e hicimos en clase
	
	
	int tamano=sizeof(palabrasClave)/sizeof(*palabrasClave);
	cout<<tamano<<endl;
	for(size_t p=0, q=0; p!=convertido.npos; p=q){
		 cout<<convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0))<<endl<<endl;
		 separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 for(int j=0;j<tamano;j++){
		 	cout<<palabrasClave[j]+"    "+separada<<endl;
			 if(separada==palabrasClave[j]){
				cout<<"Se encontro una palabra clave"<<endl;
				encontro=true;
				if(encontro){
		 			break;
		 		}
			}
		 }
		 
	}
	tamano=sizeof(palabrasClave);
	cout<<tamano<<endl;
	if(!encontro){
		cout<<"No se encontro una palabra clave"<<endl;
	}
	return 0;
}
