<?php
require 'conexion.php';

if($_GET['action'] == 'chatGraba'){
	mysql_set_charset('utf8');
	/*con esto guardo en la base de datos; ver como mostrar en el chat*/
	$usuario = $_GET["usuario"];
	$texto = $_GET["texto"];
	
	date_default_timezone_set('America/Argentina/Cordoba');  // Para hora en cordoba
	$fecha = date('YmdHis');


echo($usuario);
echo($texto);

	if($usuario != "" && $texto != ""){
		$query = $db->query("INSERT INTO `clase360_mensajes`(fecha, usuario, mensaje) VAlUES ('".$fecha."','".$usuario."', '".$texto."');");
		$result = $db->fetch_array($query); 
	}
}
?>