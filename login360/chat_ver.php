<?php
require 'conexion.php';

$resultado = mysql_query("SELECT `usuario`, `mensaje` FROM `clase360_mensajes` ORDER BY `id` DESC LIMIT 50");  // el ultimo numero determina cuantas lineas de historial muestra

echo "
	<font face='Arial'>
	<table max-width=400>
	<p><caption>Mensajes</caption></p>
		<tr>
			<td> 
";

/* Como solo tomamos las N ultimas lineas debemos dar vuelta el array para que abajo queden las ultimas */
for ($i = mysql_num_rows($resultado) - 1; $i >= 0; $i--) {

    mysql_data_seek($resultado, $i);
	$fila = mysql_fetch_assoc($resultado);

	echo "<b>".$fila['usuario'].'  dice:  </b>'.utf8_encode($fila['mensaje']). "<br />\n";
}

echo "
			</td>
		</tr>
	</table>
	</font>
";
?>