function CrearObjetoAjax() {
	try {
		ajaxobj = new ActiveXObject("Msxml2.XMLHTTP");
	} catch (e) {
		try {
			ajaxobj = new ActiveXObject("Microsoft.XMLHTTP");
		} catch (E) {
			ajaxobj = false;
		}
	}
	if (!ajaxobj && typeof XMLHttpRequest!='undefined') {
		ajaxobj = new XMLHttpRequest();
	}	
	return ajaxobj;
}

var obj_ajax = CrearObjetoAjax(); 

// ----------------------------------------------------------------------------------------------------------------------------------------------------
// Graba chat

function chat_graba(){
	obj_ajax.open('get', 'chat_graba.php?action=chatGraba&usuario='+document.getElementsByName("usuario")[0].value+'&texto='+document.getElementsByName("chat_texto")[0].value);
	obj_ajax.onreadystatechange = GestorProceso_chatGraba; 
	obj_ajax.send(null);
	document.getElementsByName("chat_texto")[0].value = "";
}

function GestorProceso_chatGraba(){
	var respuesta;
	if(obj_ajax.readyState == 4){ 
		var respuesta = obj_ajax.responseText;
		document.getElementById('area_dinamica_chatGraba').innerHTML = respuesta;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------
// Graba chat

function URL_graba(){
	obj_ajax.open('get', 'URL_graba.php?action=URLGraba&url='+document.getElementsByName("url")[0].value);
	//obj_ajax.onreadystatechange = GestorProceso_URLGraba; 
	obj_ajax.send(null);
	document.getElementsByName("url")[0].value = "";
}

function GestorProceso_URLGraba(){
	var respuesta;
	if(obj_ajax.readyState == 4){ 
		var respuesta = obj_ajax.responseText;
		document.getElementById('area_dinamica_URLGraba').innerHTML = respuesta;
	}
}

