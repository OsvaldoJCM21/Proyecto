Proceso InventarioActivosBasico
	Definir usuario, clave Como Cadena
	Definir usuario_ingresado, clave_ingresada Como Cadena
	usuario <- "admin"
	clave <- "1234"
	
	Repetir
		Escribir "--- Inicio de sesi�n ---"
		Escribir "Usuario: "
		Leer usuario_ingresado
		Escribir "Clave: "
		Leer clave_ingresada
		
		Si usuario_ingresado == usuario Y clave_ingresada == clave Entonces
			Escribir "Acceso concedido."
			
			Repetir
				Escribir "--- Men� de Inventario ---"
				Escribir "1. Agregar activo (sin almacenar informaci�n)"
				Escribir "2. Consultar activos (sin informaci�n disponible)"
				Escribir "3. Desasignar activo (sin informaci�n disponible)"
				Escribir "4. Salir"
				Escribir "Seleccione una opci�n: "
				Leer opcion
				
				Segun opcion Hacer
					1:
						Escribir "Ingrese el nombre del activo: "
						Leer nombre
						Escribir "Ingrese el tipo del activo: "
						Leer tipo
						Escribir "Ingrese el proyecto asignado: "
						Leer proyecto
						Escribir "Ingrese el nombre del empleado asignado: "
						Leer empleado
						Escribir "Ingrese el valor original del activo: "
						Leer valor
						Escribir "Activo registrado (no se almacena informaci�n)."
					2:
						Escribir "No hay activos en el inventario."
					3:
						Escribir "No hay activos para desasignar."
					4:
						Escribir "Saliendo del programa..."
					De Otro Modo:
						Escribir "Opci�n inv�lida. Intente de nuevo."
				Fin Segun
			Hasta Que opcion = 4
		SiNo
			Escribir "Usuario o clave incorrectos. Intente de nuevo."
		Fin Si
	Hasta Que Falso
Fin Proceso
