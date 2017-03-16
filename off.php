<!-- Website to control IoT Snow Machine.
MKR1000 looks at switchState.txt if 0 off, if anything else on 
Opening on.php writes 1 to switchState.txt
Opening off.php writes 0 to switchState.txt -->

<?php 
//Include index file so basic styling is consitant 
include 'index.php';

//Var to open file
$myfile = fopen("switchState.txt", "w") or die("Unable to open file!");

//Text to be written to file. 0 means off. anything else means on
$txt = "0";

//Write to file (file thats been opened, data written to file)
fwrite($myfile, $txt);

//Close file
fclose($myfile);
?>

<footer style="margin-top: 300px">
<div class="container-fluid text-center ">
	<h2>Laser Off</h2>
</div>
</footer>

</body>
</html> 