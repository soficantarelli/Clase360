<?php
require 'conexion.php';
$url = $_GET["url"];

if ($url != "") {
    $query = $db->query("INSERT INTO clase360_clases (urlClases, fecha) VALUES ('".$url."', '".date("Y-m-d")."');");
	$result = $db->fetch_array($query); 
}
?>