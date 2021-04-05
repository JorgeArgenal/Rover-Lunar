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
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
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
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
							
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
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
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
					
					if(encontrar_interacion(separada)){
						p=q;
						separada=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
						
						if(condicion(separada)){
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
							return true;
						}else if(separada=="retroceder"){
							return true;
						}else if(separada=="girarCamara"){
							return true;
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
								return true;
							}else if (separada=="retroceder"){
								return true;
							}else if(separada=="enviarFoto"){
								return true;
							}else if(separada=="tomarFoto"){
								return true;
							}else if(separada=="girarCamara"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="si"){
							return true;
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
								return true;
							}else if (separada=="retroceder"){
								return true;
							}else if(separada=="enviarFoto"){
								return true;
							}else if(separada=="tomarFoto"){
								return true;
							}else if(separada=="girarCamara"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="si"){
							return true;
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
								return true;
							}else if (separada=="retroceder"){
								return true;
							}else if(separada=="enviarFoto"){
								return true;
							}else if(separada=="tomarFoto"){
								return true;
							}else if(separada=="girarCamara"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="si"){
							return true;
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
								return true;
							}else if (separada=="retroceder"){
								return true;
							}else if(separada=="enviarFoto"){
								return true;
							}else if(separada=="tomarFoto"){
								return true;
							}else if(separada=="girarCamara"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="si"){
							return true;
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
								return true;
							}else if (separada=="retroceder"){
								return true;
							}else if(separada=="enviarFoto"){
								return true;
							}else if(separada=="tomarFoto"){
								return true;
							}else if(separada=="girarCamara"){
								return true;
							}else{
								return false;
							}
						}else if(separada=="si"){
							return true;
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
		if((separada=="hacerMientras") || (separada=="finHacer" )||(separada=="finMientras") ||(separada=="mientras") ||(separada=="hacer")){		
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

//falta que responda Iveth para definir si dejaremos con parentesis o no lo de tomarFoto y enviarFoto
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
		 if(separada=="inclinarCamara"){ //palabra clave para indicar una cantidad n de grados que la camara se debe mover 
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
			 	p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	if(anterior!=separada){
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
				anterior=separada;
				p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	p=q;
			 	separada=convertido.substr(p+(p!=0),(q=convertido.find(separador, p+1))-p-(p!=0));
			 	if(anterior!=separada){
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

	
int main(){
	string leido;
	string linea;
	leido=lectura();
	char separador='\n';
	
	//para probar condicional
	for(size_t p=0, q=0; p!=leido.npos; p=q){
		linea=leido.substr(p+(p!=0),(q=leido.find(separador, p+1))-p-(p!=0));
		if(condicional(linea)){
			cout<<"Es valido"<<endl;
			break;
		}else{
			cout<<"No es valido"<<endl;
			break;
		}
	}
		/*
		if(creacion(linea)){
			cout<<"Funciono la lectura con creacion"<<endl;
		}else if(asignacion(linea)){
			cout<<"Funciono la lectura con asignacion"<<endl;
		}else if(desplazamientos(linea)){
			cout<<"Funciono la lectura con desplazamiento"<<endl;
		}
		*/
	return 0;
}
		
	
	
