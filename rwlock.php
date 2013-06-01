#! /bin/env php
<?php

	$time_to_sleep = 5;

	if(count($argv) != 3) {
		exit("Use: $argv[0] {r|w} file_to_lock\n");
	}

	if(strcmp($argv[1], "r") == 0) {
		$mode = "r";
		$operation = LOCK_SH;
	} else if(strcmp($argv[1], "w") == 0) {
		$mode = "w+";
		$operation = LOCK_EX;
	} else {
		exit("Invalid argument: $argv[1]\n");
	}

	$fp = fopen($argv[2], $mode)
		or exit("Unable to open file ( $argv[2] )\n");

	echo "try $argv[1]lock $argv[2]\n";
	flock($fp, $operation)
		or exit("access denied\nexit\n");
	
	echo "access granted\n sleep $time_to_sleep sec\n";
	sleep($time_to_sleep);
	flock($fp, LOCK_UN);
	echo "exit\n";
?>
