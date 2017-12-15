#!/usr/bin/php
<?php



	$pass=0;
	$cnt=0;
	$ficContents=file_get_contents("splash.raw");

	$size=filesize("splash.raw");

	echo "unsigned char bitmapData[$size]={";

	for ($i=0; $i<$size; $i++){
		if ($pass==1){
				echo ", ";
		}

		echo ord(substr($ficContents,$i,1));
		$pass=1;
		$cnt++;
		if ($cnt==16){
			echo "\n";
			$cnt=0;
		}
	}

	echo "};\n";


?>