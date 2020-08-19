<?php
    $Led=$_POST["Led1"];
    
    
    header('Location: /index.php');
    
    // Abrimos el archivo datos.txt
    $acciones = fopen("acciones.txt", "wb");
    
    if($Led=="Off"){
    
        // Escribimos el valor de la variable "$led"
        fwrite($acciones, 1);
    }
    
    if($Led == "On"){
        // Escribimos el valor de la variable "$led"
        fwrite($acciones, 2);
    }
    
    
    // Cierra el archivo
    fclose($datos);
        
    

?>