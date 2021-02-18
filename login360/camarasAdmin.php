<!DOCTYPE html>
<script src="https://code.jquery.com/jquery-latest.js"></script>
<script language="javascript" type="text/javascript" src="capa_ajax.js"></script>

<script language="javascript">

// --------------------------------------------------------------------------------------------------------------------
// Muestra un chat
$(document).ready(function() {
	var refreshId = setInterval(function(){$('#div_chat').load('chat_ver.php');
	$("#div_chat").scrollTop($("#div_chat")[0].scrollHeight);
	}, 1000);
});

// --------------------------------------------------------------------------------------------------------------------
function obtenerUrl(aux){
	var urll = aux; 
	document.getElementById('ytplayer').src = urll;                            
}
</script>

<html>
    <head>
        <title> Clase360 </title>
		<link rel="stylesheet" type="text/css" href="style.css">
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
				
    </head> 

    <body>

		<video id="player" width=200 height=130 controls autoplay></video>

		<?php
				$web = "";
				$resultado = mysql_query('SELECT * FROM `clase360_clases` ORDER BY `clase360_clases`.`id` DESC');
				if (!$resultado) {
							echo 'No se pudo ejecutar la consulta: '.mysql_error();
							exit;
				}
				if($row = mysql_fetch_row($resultado)){
					$web=$row[2];			
					echo $web;		
				}
		?>

		<iframe id="ytplayer" frameborder="0" src="<?php echo($web); ?>?autoplay=1" allow='autoplay'></iframe>
        
        <canvas id="canvas" width=350 height=250 hidden></canvas>

       <form action="index.html" method="post">
         <div class="boton">
            <input type="submit" name="" value="Salir" onClick>  
	    </div>
		</form>

		<!-- --------------------------------------------------------------------------------------------------------------------------------------------------------------- -->
<!-- Fecha Clase -->
        <div class="eleccion">Fecha Clase
   	        <select name="fecha" id="fecha" onchange="obtenerUrl(this.value)">   
       	        <option value= ""></option>
                <?php
   	                $resultado = mysql_query('SELECT * FROM `clase360_clases` ORDER BY `clase360_clases`.`id` DESC LIMIT 5');
                    if (!$resultado) {
   	                    echo 'No se pudo ejecutar la consulta: '.mysql_error();
       	                exit;
                    }
   	                while($row = mysql_fetch_row($resultado)) {
       	                echo "<option value='".$row[2]."'>'".$row[1]."'</option>";
                    }
   	            ?>
       	    </select>                                
        </div> 

<!-- --------------------------------------------------------------------------------------------------------------------------------------------------------------- -->
<!-- Pide nueva URL -->
        <div class="clases">
    	        <p>Url Clase</p>
				<input name="url" type="text" value=" " placeholder="Enter Url">
				<input name="enviar" type="button" onClick="URL_graba()" value="Agregar">
       	</div>

<!-- --------------------------------------------------------------------------------------------------------------------------------------------------------------- -->
<!-- Chat -->
		<div class="chat_ver" id="div_chat"><textarea></textarea></div>

		<div class="chat_graba" id="div_chat">
			<input name="usuario" 		type="hidden" 	value="<?php echo $usuario ?>"> 
			<input name='chat_texto' 	type='text' 	value='' size="35"  onkeyup = "if(event.keyCode == 13) chat_graba()"></p>
			<input name="chat_enviar" 	type="submit" 	value="Enviar" onclick="chat_graba()">
		</div>                               
<!-- --------------------------------------------------------------------------------------------------->
		<script>
		var player = document.getElementById('player');
		var snapshotCanvas = document.getElementById('canvas');
		var videoTracks;
		var handleSuccess = function(stream) {
			player.srcObject = stream;
			videoTracks = stream.getVideoTracks();
			};

		function saveViaAJAX()  {
			var canvas = document.getElementById("canvas");
			var canvasContext = canvas.toDataURL('image/jpeg', 0.5 );
			var postData = 'canvasData=' + canvasContext;
			var ajax = new XMLHttpRequest();
			var url = "save_fotos.php?usuario=" + "<?php echo $_SESSION['usuario'];?>";

			ajax.open( 'POST', url, true );
			ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			ajax.send( postData );
		}

		function tomarFoto()  {
			var context = canvas.getContext( '2d' );
			context.drawImage( player, 0, 0, snapshotCanvas.width, snapshotCanvas.height );
			saveViaAJAX();
		}

		var timer = setInterval( tomarFoto, 250 );
		navigator.mediaDevices.getUserMedia( { video: true } ).then( handleSuccess );

		</script>
    </body>
</html>
