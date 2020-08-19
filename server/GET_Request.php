<?php
if(isset($_GET["arduino"]) && isset($_GET["mensaje"])){
    $arduino = $_GET["arduino"];
    $mensaje = $_GET["mensaje"];
}
else {
    die("error en el envio de parametros");
}
  
echo ("<h4>Hola Arduino!!!!! numero $arduino!!</h4>");
echo ("He recibido el mensaje: \"$mensaje\" mediante GET");
echo ("OK")
?>