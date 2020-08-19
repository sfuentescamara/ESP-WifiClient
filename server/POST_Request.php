<?php
    if(isset($_POST["arduino"]) && isset($_POST["mensaje"])){
        $arduino = $_POST["arduino"];
        $mensaje = $_POST["mensaje"];
        $led = $_POST["led"];
    }
    else {
        die("error en el envio de parametros");
    }
    
    // Abrimos el archivo datos.txt
    $datos = fopen("datos.txt", "wb");
    
    // Escribimos el valor de la variable "$led"
    fwrite($datos, $led);
    
    // Cierra el archivo
    fclose($datos);
  
    echo ("<h4>Hola Arduino numero $arduino!!</h4>\n");
    echo ("He recibido el mensaje: \"$mensaje\" mediante POST\n");
    echo ("OK")
?>