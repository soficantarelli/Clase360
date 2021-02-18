<?php
require 'conexion.php';

if (!empty($_POST['usuario']) && !empty($_POST['clave'])) {

	$usuario = $_POST[ 'usuario' ];
    $clave = $_POST[ 'clave' ];

    $query = $db->query( "select nombre, apellido, admin from clase360_usuarios ".
                         "where usuario = '".$usuario."' and clave = '".$clave."';" );
    
    if ($result = $db->fetch_array($query)) {
		$_SESSION["usuario"] = $usuario;

        if($result['admin'] == 'S')
            include("camarasAdmin.php");
        else
            include("camaras.php");
	    }
	else {
        include("error.html");
   } 
       
}
else {
    include("error.html");
} 
?>