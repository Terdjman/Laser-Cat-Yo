<!-- Website to control IoT Snow Machine.
MKR1000 looks at switchState.txt if 0 off, if anything else on 
Opening on.php writes 1 to switchState.txt
Opening off.php writes 0 to switchState.txt -->


<?php 
//Include index file so basic styling is consitant 
include 'index.php';

//Var to open file
$myfile0 = fopen("xpos.txt", "w") or die("Unable to open file!");

//Text to be written to file. 0 means off. anything else means on
$txt = "1";

//Write to file (file thats been opened, data written to file)
fwrite($myfile0, $txt);

//Close file
fclose($myfile0);

sleep(1);

$myfile0 = fopen("xpos.txt", "w") or die("Unable to open file!");

$txt = "0";

fwrite($myfile0, $txt);

//Close file
fclose($myfile0);
?>

<footer style="margin-top: 400px">
<div class="container-fluid text-center ">
	<h2>x pos changed</h2>
</div>
</footer>

</body>
</html> 