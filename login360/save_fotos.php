<?php
session_start();

require( "config.inc.php" ); 
require( "Database.class.php" ); 

mysql_set_charset('utf8');

date_default_timezone_set('America/Argentina/Cordoba');  // Para hora en cordoba

$tiempo = date('YmdHis');  // $jugar tiene el formato de fecha y hora actual. 
// Por ejemplo 20171023163205123 : 2017 / 10 / 23   16 : 32 : 05 

$params = $_GET;

// Aca para pedir por GET
if( count( $params ) > 0 )  {

	$img = $_POST[ 'canvasData' ];

	$primeros_chars = substr( $img, 1, 30 );

	$img = str_replace( 'data:image/jpeg;base64,', '', $img );
	$img = str_replace( ' ', '+', $img );
	$data = base64_decode( $img );

	$file = "/home/ceos1720/domains/vayra.com.ar/public_html/clase360/fotos/" . $params[ 'usuario' ] . "_" . $tiempo . ".jpg";

	$success = file_put_contents( $file, $data );


	// Despues de guardar esta ultima foto, borramos todas las anteriores, salvo esta ultimalas anteriores
	$directorio = opendir( "/home/ceos1720/domains/vayra.com.ar/public_html/clase360/fotos/" );  // directorio para explorar
	while ( $archivo = readdir( $directorio ) )   {  // Obtenemos todo lo que esta en el directorio, archivos y carpetas

	    if ( ! is_dir( $archivo ) )  {  // Este if detecta solo los archivos, no directorios. Tener en cuenta que . y .. son directorios

			// Entra a este if cuando comienza con tal cadena (case insensitive)
	        if ( preg_match( "#^" . $params[ 'usuario' ] . "#i", $archivo ) === 1 )  {  

	        	$archivo_con_ruta_completa = "/home/ceos1720/domains/vayra.com.ar/public_html/clase360/fotos/" . $archivo;

	        	// Este if es para que no se borre la que se acaba de guardar
	        	if ( $archivo_con_ruta_completa != $file )  {

	        		unlink( $archivo_con_ruta_completa );  // Es la funcion que borra el archivo

	        	}
			}
	    }
	}


}
 
?>
