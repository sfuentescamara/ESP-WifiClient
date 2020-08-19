<html>
    <head><meta http-equiv="Refresh" content="3"></head>
    <body>
        <h1>Control arduino</h1>
        <form method="POST" action="/Arduino_Acciones.php">
            <button type='submit' style='display:block; margin:auto' width='30%' onClick='display(id)' id='Led1_On' name='Led1' value='On'>Encender led</button>
            <button type='submit' style='display:block; margin:auto' width='30%' onClick='display(id)' id='Led1_Off' name='Led1' value='Off'>Apagar led</button>
        </form>
    </body>
</html>


<?php

    
    $aLineas = file("datos.txt");
    
    $array = array("Led");

    //print_r($aLineas); //print array with data
    echo "<p>DATOS ARDUINO</p>";
    echo "<p>=====================</p>";
    // Mostrar el contenido del archivo:
    foreach( $aLineas as $linea => $value )
        if ($value == "1"){
            echo "El valor del " . $array[0]  . " es apagado" . "<br/ >";
        }
        if ($value == "2"){
            echo "El valor del " . $array[0]  . " es encendido" . "<br/ >";
        }


?>