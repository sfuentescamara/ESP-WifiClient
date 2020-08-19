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
    
    $aLineas = file("acciones.txt");
    
    foreach( $aLineas as $linea => $value ) {
        
                // Comparo si se han cambiado valores en el servidor
        if($value == $led){
            echo ("Mismos valores");
        } else {
            echo ("Nuevo valor $linea es: [$value]\n");
        }
        echo ("0OK");
    }
  
?>