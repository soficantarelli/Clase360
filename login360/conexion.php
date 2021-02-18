<?php
session_start();

require 'config.inc.php'; 
require 'Database.class.php'; 

//mysql_set_charset('utf8');

$db = new Database(DB_SERVER, DB_USER, DB_PASS, DB_DATABASE)
    or die('No se pudo conectar');
$db->connect();
?>