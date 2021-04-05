#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<fstream>

using namespace std;
bool creacion(string leido);
bool asignacion(string leido);
bool desplazamientos(string leido);
bool condicion(string leido);
bool encontrar_condicional (string leido);
bool encontrar_interacion (string leido);
bool camara (string leido);
bool iteracion(string leido);
bool condicional(string leido);
string lectura();

string lectura(){
	ifstream archivo_texto;
	string nombreArchivo,texto;
	string archivo="";
	
	cout<<endl;
	cout<<"Digite el nombre o la ubicacion del archivo o fichero: ";
	getline(cin,nombreArchivo);
	
	archivo_texto.open(nombreArchivo.c_str(),ios::in); //Abrimos el archivo en modo lectura
	
	if(archivo_texto.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo_texto.eof()){ //mientras no sea final del archivo
		getline(archivo_texto,texto);
		archivo=archivo+texto+'\n';
	}
	
	archivo_texto.close(); //Cerramos el archivo
	cout<<endl;
	cout<<"Se leyo el archivo y se procedera a analizarlo, presione cualquier tecla"<<endl<<endl;
	system("pause");
	cout<<endl;
	return archivo;
}
bool creacion(string leido){
	char separador= ' ';
	char introducido[40];
	string convertido=leido;
	string separada;
	bool encontro=false;
		
	//deteccion de creacion de variable:  tipo_variable espacio nombre_variable
	
	string tipos_variables[]={"int","string","bool", "float"};
	int tamano_tipoVar=sizeof(tipos_variables)/sizeof(*tipos_variables);
	for(size_t p=0, q=0; p!=convertido.npos; p=q){
		 //separar la primera palabra encontrada
		 separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 for(int j=0;j<tamano_tipoVar;j++){
		 	 //comparar si es de los tipos de variables validos
			 if(separada==tipos_variables[j]){
				encontro=true;
				if(encontro){
		 			//moverse a la siguiente palabra
					p=q;
					//guardar la palabra anterior para validacion de que tenga otra palabra siguiente o sea un espacio en blanco
		 			string anterior=separada;
		 			//obtencion de la siguiente palabra
		 			separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 			//validacion si hay otra palabra o es un espacio en blanco o nada en absoluto
		 			if(separada==anterior || separada==""){
		 				return false;
					 }else{
						for(int k=0;k<separada.length();k++){
							//validacion de que el nombre de la variable no contenga numeros
							if(separada[k]>='0' && separada[k]<='9'){
		 						return false;
				 			}
					 	} 	
					 }
					//moverse a la siguiente palabra
					p=q;
		 			//obtencion de la siguiente palabra en caso de haberla y marcar que no es valido
		 			separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
					//validacion si hay otra palabra o es un espacio en blanco o nada en absoluto
		 			if(separada!=""){
		 				if(separada!=anterior){
		 					return false;
					 	}
					 }
		 		}
			}
		 }
		 if(!encontro){
		 	return false;
		 }
	}
	return true;;
}
bool asignacion(string leido){
	char separador= ' ';
	string convertido=leido;
	string separada;
	
	//deteccion de asignacion de variables: nombre_variable= nombre_variable || nombre_variable=numerio_racional || nombre_variable=true || nombre_variable=false
	//Ciclo para separar palabras separadas por un separador
	separador='=';
	
	bool punto=false;
	bool signo=false;
	string temporal,anterior;
	for(size_t p=0, q=0; p!=convertido.npos; p=q){
		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		for(int k=0;k<separada.length();k++){
			//validacion de que el nombre de la variable no contenga numeros y este bien escrita
			if(separada[k]>='0' && separada[k]<='9'){
		 		return false;
			}
		}
	
		p=q;
		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		//caso: nombre_variable=nombre_variable
		if((separada[0]>='a' && separada[0]<='z' && separada!="true" && separada!="false") || (separada[0]>='A' && separada[0]<='Z' && separada!="true" && separada!="false")){
			for(int k=0;k<separada.length();k++){
				//validacion de que el nombre de la variable no contenga numeros y este bien escrita
				if(separada[k]>='0' && separada[k]<='9'){
		 			return false;
				}
			}
			//guardar palabra anterior, aca normalmente va lo que esta despues del igual
			anterior=separada;
			//moverse a la siguiente palabra
			p=q;
			//obtencion de la siguiente palabra para verificar que solo tenga 1 palabra variable
			separada=separada.substr(p+(p!=0),(q=separada.find(separador, p+1))-p-(p!=0));
			//otro movimiento y obtencion de la siguiente palabra, porque se quiere saber si no hay nada luego del true o false
			//y este movimiento devuelve lo que esta escrito luego del = en caso de no haber mas palabras, si la anterior y separada
			//coinciden entonces no hay otra palabra luego del true o false y esta bien escrito
			//separador cambia a espacio
			separador=' ';
			p=q;
			separada=separada.substr(p+(p!=0),(q=separada.find(separador, p+1))-p-(p!=0));
			
			//validacion si hay otra palabra o es un espacio en blanco o nada en absoluto
			if(separada!=anterior){
				return false;
			}
		//caso: nombre_variable=+numero_racional || nombre_variable=-numero_racional || nombre_variable=numero_racional
		}else if(separada[0]=='+' || separada[0]=='-'|| (separada[0]>='0' && separada[0]<='9')){
			//ciclo para recorrer el valor ingresado
			for(int k=0;k<separada.length();k++){
				//si es un signo al comienzo, solo se concatena a temporal que es una variable string para ayudarnos a saber como lee
				//recordatorio, borrar la variable temporal ya que no aporta nada al programa, solo es una ayuda
				if(separada[k]=='+' || separada[k]=='-'){
					temporal=temporal+separada[k];
					signo=true;
				}else{
					if(separada[k]!='.'){
						temporal=temporal+separada[k];	
					}else if(separada[k]=='.' && !punto){
						temporal=temporal+separada[k];
						punto=true;
					}else if(separada[k]=='.' && punto){
						return false;
					}
				}
			}
		
		}//caso: nombre_variable=true || nombre_variable=false
		else if(separada=="true" || separada=="false"){
			//guardar palabra anterior, aca normalmente se guardaria si es true o false
			anterior=separada;
			//moverse a la siguiente palabra
			p=q;
			//obtencion de la siguiente palabra para verificar que solo este true o false
			separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			//otro movimiento y obtencion de la siguiente palabra, porque se quiere saber si no hay nada luego del true o false
			//y este movimiento devuelve lo que esta escrito luego del = en caso de no haber mas palabras, si la anterior y separada
			//coinciden entonces no hay otra palabra luego del true o false y esta bien escrito
			p=q;
			separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			
			//validacion si hay otra palabra o es un espacio en blanco o nada en absoluto
			if(separada!=anterior){
				return false;
			}
		}else{
			return false;
		}
	
	}
	return true;
}
bool desplazamientos(string leido){
	char separador= ' ';
	string convertido;
	convertido=leido;
	string separada;
	string anterior;
	bool signo=false;	
	bool punto=false;
	
	//Ciclo para separar palabras separadas por un separador y encontrar si la primera palabra es una palabra clave
	
	int cont;
	for(size_t p=0, q=0; p!=convertido.npos; p=q){
		 separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 if(separada=="avanzar"){
		 	p=q;
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			if(separada[0]=='+' || separada[0]=='-'|| (separada[0]>='0' && separada[0]<='9')){
				//ciclo para recorrer el valor ingresado
				for(int k=0;k<separada.length();k++){
					//si es un signo al comienzo, solo se concatena a temporal que es una variable string para ayudarnos a saber como lee					
					if(separada[k]=='+' || separada[k]=='-'){
						signo=true;
					}else{
						if(separada[k]!='.'){
						}else if(separada[k]=='.' && !punto){
							punto=true;
						}else if(separada[k]=='.' && punto){
							return false;
						}
					}
				}
				anterior=separada;
				p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	
				if(separada!="finAvanzar"){
					return false;
				}else{
					anterior=separada;
					
					for(int i=0;i<3;i++){
						p=q;
				 		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
					}
				 	if(anterior!=separada){
				 		return false;
					 }
				}			 							
			 	if(anterior!=separada){
			 		return false;
				}
			}
		 	break;
		 }else if(separada=="retroceder"){
		 	p=q;
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			if(separada[0]=='+' || separada[0]=='-'|| (separada[0]>='0' && separada[0]<='9')){
				//ciclo para recorrer el valor ingresado
				for(int k=0;k<separada.length();k++){
					//si es un signo al comienzo, solo se concatena a temporal que es una variable string para ayudarnos a saber como lee
					if(separada[k]=='+' || separada[k]=='-'){
						signo=true;
					}else{
						if(separada[k]=='.' && !punto){
							punto=true;
						}else if(separada[k]=='.' && punto){
							return false;
						}
					}
				}
				anterior=separada;
				p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	
				if(separada!="finRetroceder"){
					return false;
				}else{
					anterior=separada;
					
					for(int i=0;i<3;i++){
						p=q;
				 		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
					}
				 	if(anterior!=separada){
				 		return false;
					 }
					
				}
			 	
			 	if(anterior!=separada){
			 		return false;
				}
			}
		 	break;
		 }else if(separada=="detener"){
		 	anterior=separada;
			p=q;
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 	if(anterior!=separada){
		 		return false;
			}
			break;
		 }else{
		 	return false;
		 }
	}	
	return true;
}
bool condicion(string leido){
	char separador= ' ';
	string convertido=leido;
	//se ingresa algo tipo (valor1OperadorValor2)
	string valor1;
	string valor2;
	bool cambio=false;  //variable centinela para saber cuando concatenar o no a una variable de valor
	for(int i=1;i<convertido.length()-1;i++){
		if(convertido[i]!='<' && convertido[i]!='>' && convertido[i]!='=' && convertido[i]!='!'){
			if(!cambio){
				valor1=valor1+convertido[i];	
			}
		}else if(convertido[i]=='<'){
			if(convertido[i+1]=='='){
				//i++ porque se ocupa avanzar ese caracter que se evaluo si era otro operador o no
				i++;
				//para no concatenar mas a valor1
				cambio=true;
				//guardar el resto del texto en otra variable para evaluar si esta bien escrito
				for(int j=i+1;j<convertido.length()-1;j++){
					valor2=valor2+convertido[j];
				}
				//validacion de que esten bien escritos
				for(int k=0;k<valor1.length();k++){
					//validacion de que el nombre de la variable no contenga numeros
					if(valor1[k]>='0' && valor1[k]<='9'){
						return false;
		 			}
				}
				
				for(int k=0;k<valor1.length();k++){
					//validacion de que el nombre de la variable no contenga numeros
					if(valor2[k]>='0' && valor2[k]<='9'){
						return false;
		 			}
				}
			
				if((convertido[i+1]>='a' && convertido[i+1]<='z') || (convertido[i+1]>='A' && convertido[i+1]<='Z')){
					//para no concatenar mas a valor1
					cambio=true;
					for(int j=i+1;j<convertido.length()-1;j++){
						valor2=valor2+convertido[j];
					}
					//validacion de que esten bien escritos
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor1[k]>='0' && valor1[k]<='9'){
							return false;
			 			}
					}
					
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor2[k]>='0' && valor2[k]<='9'){
							return false;
				 		}
					}
					
				}else{
				return false;
			}
			}else if(convertido[i]=='='){
				if(convertido[i+1]=='='){
					//i++ porque se ocupa avanzar ese caracter que se evaluo si era otro operador o no
					i++;
					//para no concatenar mas a valor1
					cambio=true;
					//guardar el resto del texto en otra variable para evaluar si esta bien escrito
					for(int j=i+1;j<convertido.length()-1;j++){
						valor2=valor2+convertido[j];
					}
					//validacion de que esten bien escritos
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor1[k]>='0' && valor1[k]<='9'){
							return false;
			 			}
					}
					
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor2[k]>='0' && valor2[k]<='9'){
							return false;
				 		}
					}
					
				}else{
					return false;
				}
			}else if(convertido[i]=='!'){
				if(convertido[i+1]=='='){
					//i++ porque se ocupa avanzar ese caracter que se evaluo si era otro operador o no
					i++;
					//para no concatenar mas a valor1
					cambio=true;
					//guardar el resto del texto en otra variable para evaluar si esta bien escrito
					for(int j=i+1;j<convertido.length()-1;j++){
						valor2=valor2+convertido[j];
					}
					//validacion de que esten bien escritos
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor1[k]>='0' && valor1[k]<='9'){
							return false;
			 			}
					}
					
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor2[k]>='0' && valor2[k]<='9'){
							return false;
				 		}
					}
					
				}else{
					return false;
				}
			}else if(convertido[i]=='>'){
				if(convertido[i+1]=='='){
					//i++ porque se ocupa avanzar ese caracter que se evaluo si era otro operador o no
					i++;
					//para no concatenar mas a valor1
					cambio=true;
					//guardar el resto del texto en otra variable para evaluar si esta bien escrito
					for(int j=i+1;j<convertido.length()-1;j++){
						valor2=valor2+convertido[j];
					}
					//validacion de que esten bien escritos
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor1[k]>='0' && valor1[k]<='9'){
							return false;
			 			}
					}
					
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor2[k]>='0' && valor2[k]<='9'){
							return false;
				 		}
					}
					
				}else if((convertido[i+1]>='a' && convertido[i+1]<='z') || (convertido[i+1]>='A' && convertido[i+1]<='Z')){
					//para no concatenar mas a valor1
					cambio=true;
					for(int j=i+1;j<convertido.length()-1;j++){
						valor2=valor2+convertido[j];
					}
					//validacion de que esten bien escritos
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor1[k]>='0' && valor1[k]<='9'){
							return false;
			 			}
					}
					
					for(int k=0;k<valor1.length();k++){
						//validacion de que el nombre de la variable no contenga numeros
						if(valor2[k]>='0' && valor2[k]<='9'){
							return false;
				 		}
					}
					
				}else{
					return false;
				}
			}
		}
	}
	return true;
}
bool iteracion(string leido){
	string linea=leido;
	string separada;
	char separador=' ';
	
	for(size_t p=0, q=0; p!=leido.npos; p=q){
		separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
		if(encontrar_interacion(linea)){
			separador=' ';
			separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
			if(separada=="hacer"){
				p=q;
				separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
				if(separada=="avanzar"){
					//funcion que reciba leido, y a leido se le aplica todo ese tratamiento de abajo
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;
					}
				}else if (separada=="retroceder"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else if (separada=="detener"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else if (separada=="enviarFoto"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else if (separada=="tomarFoto"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else if (separada=="girarCamara"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else if (separada=="alturaCamara"){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finHacer"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;

					}
				}else{
					return false;
				}
			
			}else if(separada=="mientras"){
				p=q;
				separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
				if(condicion(separada)){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					if(separada=="hacer"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="avanzar"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finMientras"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="retroceder"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finMientras"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="detener"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finMientras"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="girarCamara"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finMientras"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="alturaCamara"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="finMientras"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="enviarFoto"){
							return true;
						}else if(separada=="tomarFoto"){
							return true;
						}else{
							return false;
						}
					}else{
						return false;
					}
				}else{
					return false;
				}
			}else{
				return false;
			}
		}else{
			return false;
		}
	}
	
}
bool condicional(string leido){
	string linea=leido;
	string separada;
	char separador=' ';
	//aca quedé, falta todo lo del condicional, debe recibir string de tipo si condicion entonces instruccion ó si condicion entonces instruccion sinoEntonces instruccion
	for(size_t p=0, q=0; p!=leido.npos; p=q){
		separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
		if(encontrar_condicional(separada)){
			p=q;
			separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
			if(condicion(separada)){
				p=q;
				separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
				if(encontrar_condicional(separada)){
					p=q;
					separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
					
					if(separada=="avanzar"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="entoncesSino"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="avanzar"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="retroceder"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="detenerse"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="enviarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="tomarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="girarCamara"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else{
								return false;
							}
						}else if(separada=="finSi"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="si"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else if (separada=="retroceder"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="entoncesSino"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="avanzar"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="retroceder"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="detenerse"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="enviarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="tomarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="girarCamara"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else{
								return false;
							}
						}else if(separada=="finSi"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="si"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else if(separada=="enviarFoto"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="entoncesSino"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="avanzar"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="retroceder"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="detenerse"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="enviarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="tomarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="girarCamara"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else{
								return false;
							}
						}else if(separada=="finSi"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="si"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else if(separada=="tomarFoto"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="entoncesSino"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="avanzar"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="retroceder"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="detenerse"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="enviarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="tomarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="girarCamara"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else{
								return false;
							}
						}else if(separada=="finSi"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="si"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else if(separada=="girarCamara"){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						if(separada=="entoncesSino"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="avanzar"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="retroceder"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if (separada=="detenerse"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="enviarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="tomarFoto"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else if(separada=="girarCamara"){
								p=q;
								separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
								if(encontrar_condicional(separada)){
									return true;
								}else{
									return false;
								}
							}else{
								return false;
							}
						}else if(separada=="finSi"){
							p=q;
							separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
							if(separada=="si"){
								return true;
							}else{
								return false;
							}
						}else{
							return false;
						}
					}else{
						return false;
						break;
					}
				}else{
					return false;
				}
			}else{
				return false;
			}
			
		}else{
			return false;
		}
	}
	return false;
}
bool camara(string leido){
	char separador= ' ';
	string convertido;
	convertido=leido;
	string separada;
	string anterior;
	bool signo=false;	
	bool punto=false;
	
	
	//Ciclo para separar palabras separadas por un separador y encontrar si la primera palabra es una palabra clave
	
	int cont;
	for(size_t p=0, q=0; p!=convertido.npos; p=q){
		 separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 if(separada=="girarCamara"){ //palabra clave para indicar una cantidad n de grados que la camara se debe mover 
		 	p=q;
		 	
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 	
			if(separada[0]=='+' || separada[0]=='-'|| (separada[0]>='0' && separada[0]<='9')){
				//ciclo para recorrer el valor ingresado
				for(int k=0;k<separada.length();k++){
					//si es un signo al comienzo, solo se concatena a temporal que es una variable string para ayudarnos a saber como lee					
					if(separada[k]=='+' || separada[k]=='-'){
						signo=true;
					}else{
						if(separada[k]!='.'){
						}else if(separada[k]=='.' && !punto){
							punto=true;
						}else if(separada[k]=='.' && punto){
							return false;
						}
					}
				}
				
				p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	if(separada!="finGirarCamara"){
			 		return false;
				}
				
			}else{
				return false;
			}
		}else if(separada=="alturaCamara"){ //palabra clave para indicar una cantidad n de centimentros con los que se desplazara la camara 
		 	p=q;
		 	
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 	
			if(separada[0]=='+' || separada[0]=='-'|| (separada[0]>='0' && separada[0]<='9')){
				//ciclo para recorrer el valor ingresado
				for(int k=0;k<separada.length();k++){
					//si es un signo al comienzo, solo se concatena a temporal que es una variable string para ayudarnos a saber como lee					
					if(separada[k]=='+' || separada[k]=='-'){
						signo=true;
					}else{
						if(separada[k]!='.'){
						}else if(separada[k]=='.' && !punto){
							punto=true;
						}else if(separada[k]=='.' && punto){
							return false;
						}
					}
				}
			 	p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	if(separada!="finAlturaCamara"){
			 		return false;
				}
				
			}
		 	break;
		 }else if(separada=="tomarFoto()"){
		 	anterior=separada;
			p=q;
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 	if(anterior!=separada){
		 		return false;
			}
		 }else if(separada=="enviarFoto()"){
		 	anterior=separada;
			p=q;
		 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		 	if(anterior!=separada){
		 		return false;
			}
			break;
		 }else{
		 	return false;
		 }
	}	
	return true;
}

//esta funcion nos ayudara a analizar que la sintaxis para la encontrar_interacion este escrita correctamente 
//la encontrar_interacion esta compuesta de ciclos: mientras, hacerMientras, para.
bool encontrar_interacion(string leido){

	
	//variables que nos ayudaran a reconocer los patrones correctos 
	char separador= ' ';
	string convertido;
	convertido=leido;
	string separada;
	string anterior;
	string condicion;
	//asumiremos inicialmente el valor de falsedad para la proposicion 	
	//acepta una cadena en la funcion se verificara si esta escrita correctamente sengun nuestro BNF
	//nos ayudara a reconocer la existencua del operador que estemos utilizando
	bool operador = false; 
	
	for(size_t p=0, q=0; p!=convertido.npos; p=q){//inicio
		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		//verificacion de las palabras reservadas 
		if( (separada=="finHacer" )||(separada=="finMientras") ||(separada=="mientras") ||(separada=="hacer")){		
			return true;
		}else{
			return false;
		}//inicio del if para las palabras reservadas 	
	//fin if para palabras reservadas
	}//final del for
}//fin de la funcion

//encontrar condicional
bool encontrar_condicional (string leido){
	
	//variables que nos ayudaran a reconocer los patrones correctos 
	char separador= ' ';
	string convertido;
	convertido=leido;
	string separada;
	//asumiremos inicialmente el valor de falsedad para la proposicion 	
	//acepta una cadena en la funcion se verificara si esta escrita correctamente sengun nuestro BNF
	
	for(size_t p=0, q=0; p!=convertido.npos; p=q){//inicio
		separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
		
		//verificacion de las palabras reservadas 
		if((separada=="si") || (separada=="entonces" )||(separada=="entoncesSino") ||(separada=="finSi")||(separada == "finSino")){//inicio del if para las palabras reservadas 
			return true;
		}
	}//final del ciclo for 	
	return false;
}



	
int main(){
	int contMientras=0;
	int contSi=0;
	int contHacer=0;
	int contCreacion=0;
	int contDesplazamientos=0;
	int contCamara=0;
	int contAsignacion=0;
	int errores=0;
	string leido;
	string linea;
	string separada;
	leido=lectura();
	char separadorLineas='\n';
	char separadorEspacios=' ';
	
	for(size_t l=0, r=0; l!=leido.npos; l=r){
		linea=leido.substr(l+(l!=0),(r=leido.find(separadorLineas, l+1))-l-(l!=0));
		for(size_t p=0, q=0; p!=leido.npos; p=q){
			separada=linea.substr(p+(p!=0),(q=linea.find(separadorEspacios, p+1))-p-(p!=0));
			if(separada=="mientras"){
				if(iteracion(linea)){
					contMientras=contMientras+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if(separada=="si"){
				if(condicional(linea)){
					contSi=contSi+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if(separada=="hacer"){
				if(iteracion(linea)){
					contHacer=contHacer+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if(separada=="int" || separada=="bool" || separada=="string" || separada=="float"){
				if(creacion(linea)){
					contCreacion=contCreacion+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if(separada=="avanzar" || separada=="retroceder" || separada=="detenerse"){
				if(desplazamientos(linea)){
					contDesplazamientos=contDesplazamientos+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if(separada=="girarCamara" || separada=="alturaCamara" || separada=="tomarFoto()" || separada=="enviarFoto()"){
				if(camara(linea)){
					contCamara=contCamara+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}else if((separada[0]>='a' && separada[0]>='z') || (separada[0]>='A' && separada[0]>='Z')){
				if(asignacion(linea)){
					contAsignacion=contAsignacion+1;
					break;
				}else{
					errores=errores+1;
					break;
				}
			}
		}
	}
	
	//escritura del archivo
	ofstream archivo;
	archivo.open("resultados.txt",ios::out);
	if(archivo.fail()){
		cout<<"El archivo no se abrio";
		exit(1);
	}
	archivo<<"Resultados"<<endl;
	
	archivo<<"Contador de Mientras: ";
	archivo<<contMientras<<endl;
	archivo<<"Contador de Mientras: ";	
	archivo<<contMientras<<endl;
	archivo<<"Contador de Si: ";  
	archivo<<contSi<<endl;
	archivo<<"Contador de Hacer: ";               
	archivo<<contHacer<<endl;
	archivo<<"Contador de Creacion de variables: ";
	archivo<<contCreacion<<endl;
	archivo<<"Contador de Desplazamientos: ";
	archivo<<contDesplazamientos<<endl;
	archivo<<"Contador de Camara: ";
	archivo<<contCamara<<endl;
	archivo<<"Contador de Asignacion: ";
	archivo<<contAsignacion<<endl;
	archivo<<"Contador de Errores encontrados: ";
	archivo<<errores<<endl;
	
	archivo.close();
	
	cout<<"En caso de no haber ocurrido un error fatal, puede leer los resultados en un archivo de texto llamado 'Resultados.txt' en la carpeta de origen"<<endl<<endl;
	system("pause");
	
	
	return 0;
}
		
	
	
