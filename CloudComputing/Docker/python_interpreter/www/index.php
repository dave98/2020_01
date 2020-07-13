<!DOCTYPE html>
<?php
    $api_endpoint = $_ENV["API_ENDPOINT"] ?: "http://localhost:5000/api/"; // Punto de conexión con backend

    $textarea_1 = "";
    $textarea_2 = "";

    if( isset($_POST['send_message']) ){
        $textarea_1 = $_POST['post_code'];
        //$textarea_2 = $_POST['post_code'];
        $textarea_2 = $api_endpoint;

        $file = "temporal.py";
        $content = $_POST['post_code'];
        if(file_exists($file)){
            echo "<font color='red'>Actualizando caché...</font>";
        }
        $fo = fopen($file, "w");
        fwrite($fo, $content);
        echo "<font color='red'>Archivo preparado...</font>";
        

    }
    else{
        $textarea_2 = "";
    }
?>

<head>
    <meta charset="utf-8">
    <title>Python reader</title>
    <style media="screen">
        body
        {
            margin:0 auto;
            padding:0px;
            text-align:center;
            width:100%;
            font-family: "Myriad Pro","Helvetica Neue",Helvetica,Arial,Sans-Serif;
            background-color:#555e61;
        }
        #wrapper
        {
            margin:0 auto;
            padding:0px;
            text-align:left;
            width:995px;
        }
        #wrapper h1
        {
            margin-top:30px;
            font-size:65px;
        }
        #wrapper h1 p
        {
            font-size:18px;
        }
        #sms_div input[type="text"]
        {
            width:450px;
            height:35px;
            border:none;
            padding-left:10px;
            font-size:17px;
        }
        #sms_div textarea
        {
            width:1050px;
            margin-top:20px;
            height:400px;
            border:none;
            padding-left:10px;
            font-size:17px;
        }
        #sms_div input[type="submit"]
        {
            background:none;
            border:1px solid;
            width:400px;
            height:30px;
        }
        #sms_div2 textarea
        {
            width:1050px;
            margin-top:0px;
            height:150px;
            border:none;
            padding-left:10px;
            font-size:17px;
        }
    </style>
</head>
<body>
<div id="wrapper">

    <div id="sms_div">
        <form action="index.php" method="POST">
        <br>
        <textarea name="post_code" placeholder="Bienvenido, coloque su código aquí: "><?php echo $textarea_1?></textarea>
        <br>
        <input type="submit" name="send_message" value="Evaluar codigo">
        </form>
    </div>
    
    <div id="sms_div2">
        <form method="get" action="send_message.php">
        <br>
        <textarea name="message" placeholder="Resultado de consola."><?php echo $textarea_2?></textarea>
        <br>
        </form>
    </div>

</div>
</body>
</html>