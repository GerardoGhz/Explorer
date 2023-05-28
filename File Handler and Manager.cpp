#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "File Handler and Manager.h"

std::string nombreArchivo, rutaArchivo, rutaCompleta, extensionArchivo, respuesta, linea, contenidoGuardar;
std::ifstream archivoLectura;
std::ofstream archivoEscritura;

void FileHandler::crearArchivo () {
	// Solicita al usuario el nombre del archivo
	std::cout << "Ingrese el nombre del archivo: ";
	std::getline (std::cin, nombreArchivo);

	// Solicita al usuario la extensión del archivo
	std::cout << "Ingrese la extensión del archivo (txt, docx): ";
	std::getline (std::cin, extensionArchivo);

	// Solicita al usuario la ruta donde desea guardar del archivo
	std::cout << "Ingrese la ruta donde desea guardar del archivo: ";
	std::getline (std::cin, rutaArchivo);

	// Combina la ruta, el nombre y la extensión para formar la ruta completa del archivo
	rutaCompleta = rutaArchivo + "\\" + nombreArchivo + "." + extensionArchivo;

	// Verifica si el archivo ya existe
	std::ifstream existeArchivo (rutaCompleta);
	if ( existeArchivo ) {
		std::cout << "El archivo ya existe. ¿Desea sobrescribirlo? (Si/No): ";
		std::getline (std::cin, respuesta);
		if ( respuesta != "SI" && respuesta != "Si" && respuesta != "si" && respuesta != "S" && respuesta != "s" ) {

			// Si el usuario no desea sobrescribir el archivo, se cancela la operación
			std::cout << "Operación cancelada." << std::endl;
			return;
		}
	}

	// Crea el archivo
	std::ofstream archivo (rutaCompleta);
	if ( !archivo.is_open ()) {
		// Si no se pudo abrir el archivo, se lanza una excepción
		throw std::runtime_error ("No se pudo crear el archivo.");
	}
	archivo.close ();

	// Muestra un mensaje de éxito junto con la ruta completa del archivo creado
	std::cout << "El archivo \"" << nombreArchivo << "\" ha sido creado y guardado exitosamente en la ruta: \"" << rutaCompleta << "\"" << std::endl;
}

void FileHandler::abrirArchivo () {
	// Solicitar al usuario la ruta del archivo a abrir
	std::cout << "Ingrese la ruta del archivo a abrir: ";
	std::getline (std::cin, rutaCompleta);

	// Abrir el archivo en modo lectura
	std::ifstream archivo (rutaCompleta);
	if ( !archivo.is_open ()) {
		throw std::runtime_error ("No se pudo abrir el archivo.");
	}

	// Lee y muestra el contenido del archivo
	std::cout << "Contenido del archivo:" << std::endl;
	while ( std::getline (archivo, linea)) {
		// Imprimir la línea en la consola
		std::cout << linea << std::endl;
	}

	archivo.close (); // Cerrar el archivo después de leerlo
}

void FileHandler::mostrarContenido () {
	// Abrir el archivo en modo lectura
	std::ifstream archivo (rutaCompleta);
	if ( !archivo.is_open ()) {
		throw std::runtime_error ("No se pudo abrir el archivo.");
	}

	// Lee y muestra el contenido del archivo
	std::cout << "Contenido del archivo:" << std::endl;
	while ( std::getline (archivo, linea)) {
		// Imprimir la línea en la consola
		std::cout << linea << std::endl;
	}

	archivo.close (); // Cerrar el archivo después de leerlo
}

void FileHandler::buscarPalabra () {
	bool buscar = true; // Booleano para controlar si se busca otra palabra
	while ( buscar ) { // Mientras buscar sea true, se ejecuta el ciclo
		// Se solicita al usuario la palabra o frase a buscar
		std::cout << "Ingrese la palabra o frase a buscar: ";
		std::string palabra;
		std::getline (std::cin, palabra);

		// Se abre el archivo en modo lectura
		std::ifstream archivo (rutaCompleta);
		if ( !archivo.is_open ()) {
			throw std::runtime_error ("No se pudo abrir el archivo.");
		}

		// Busca la palabra o frase en el archivo
		std::cout << "Resultados de la busqueda:" << std::endl;
		int lineaNumero = 1; // Contador de número de línea
		while ( std::getline (archivo, linea)) {
			// Lee una línea del archivo y la almacena en la variable "linea"
			if ( linea.find (palabra) != std::string::npos )
				// Utiliza la función "find" para buscar la "palabra" en la "linea"
				// La función "find" devuelve la posición de la palabra encontrada o "std::string::npos" si no se encuentra

				// Si la palabra se encuentra en la línea, se ejecuta el siguiente bloque de código
				std::cout << "Linea " << lineaNumero << ": " << linea << std::endl;
			// Imprime en pantalla el número de línea y el contenido de la línea encontrada

			lineaNumero++;
			// Incrementa el contador de número de línea para llevar un seguimiento de las líneas del archivo
		}
		archivo.close ();

		// Pregunta al usuario si desea buscar otra palabra
		std::cout << "¿Desea buscar otra palabra? (Si/No): ";
		std::getline (std::cin, respuesta);

		if ( respuesta != "Si" && respuesta != "si" && respuesta != "S" && respuesta != "s" ) {
			buscar = false; // Si la respuesta no es "Si", "si", "S" o "s", buscar se vuelve false y se termina el ciclo
		}
	}

}

void FileHandler::modificarLinea() {
	// Abrir el archivo en modo lectura
	std::ifstream archivo(rutaCompleta);
	if (!archivo.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo.");
	}

	// Leer el contenido original del archivo línea por línea
	std::vector<std::string> lineas;
	while (std::getline(archivo, linea)) {
		lineas.push_back(linea);
	}
	archivo.close();

	// Solicitar el número de línea a modificar
	int numeroLinea;
	std::cout << "Ingrese el número de línea que desea modificar: ";
	std::cin >> numeroLinea;
	std::cin.ignore();

	// Verificar si el número de línea es válido
	if (numeroLinea <= 0 || numeroLinea > lineas.size()) {
		throw std::runtime_error("Número de línea inválido.");
	}

	// Solicitar el nuevo contenido para la línea seleccionada
	std::string nuevoContenido;
	std::cout << "Ingrese el nuevo contenido para la línea " << numeroLinea << ": ";
	std::getline(std::cin, nuevoContenido);

	// Actualizar el contenido de la línea seleccionada
	lineas[numeroLinea - 1] = nuevoContenido;

	// Abrir el archivo en modo escritura
	std::ofstream archivoEscritura(rutaCompleta);
	if (!archivoEscritura.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo para escritura.");
	}

	// Escribir el contenido modificado en el archivo
	for (const std::string& linea : lineas) {
		archivoEscritura << linea << "\n";
	}
	archivoEscritura.close();

	std::cout << "La línea " << numeroLinea << " ha sido modificada exitosamente." << std::endl;
}

void FileHandler::escribirEnArchivo() {
	// Abre el archivo en modo append
	std::ofstream archivo(rutaCompleta, std::ios::app);
	if (!archivo.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo para escritura.");
	}

	std::string texto;
	std::cout << "Ingrese el texto que desea agregar: ";
	std::getline(std::cin, texto);

	// Escribe el texto ingresado por el usuario al final del archivo
	archivo << texto << std::endl;

	archivo.close();

	std::cout << "El texto se ha agregado exitosamente al archivo." << std::endl;
}

void FileHandler::guardarCambios () {
	// Abre el archivo en modo escritura
	std::ofstream archivo (rutaCompleta);
	if ( !archivo.is_open ()) {
		throw std::runtime_error ("No se pudo abrir el archivo para escritura.");
	}

	// Escribe el contenido guardado en el archivo
	archivo << contenidoGuardar;

	archivo.close (); // Cierra el archivo

	std::cout << "Contenido guardado exitosamente en el archivo." << std::endl;
}

void FileHandler::cerrarArchivo() {
	archivoLectura.close();
	archivoEscritura.close();
	std::cout << "Archivos cerrado con exito." << std::endl;
}