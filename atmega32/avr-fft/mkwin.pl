# Window table generator

	$fftn = 128;	# FFT samples

	$cn = 8;
	$re = 32767;
	$pi = 3.14159;


	$cn--;
	print "; Window tables for $sn sample int16 FFT.\n";

	# Hamming Window
	print "\nhamming:\n";
	for($p = 0; $p < $fftn; $p++) {
		$n = int((0.54 - 0.46*cos(2*$pi * $p/$fftn)) * $re);
		&put_val;
	}

	# Hanning Window
	print "\nhanning:\n";
	for($p = 0; $p < $fftn; $p++) {
		$n = int((0.5 - 0.5*cos(2*$pi * $p/$fftn)) * $re);
		&put_val;
	}

	# Blackman Window
	print "\nblackman:\n";
	for($p = 0; $p < $fftn; $p++) {
		$n = int((0.42 - 0.5*cos(2*$pi * $p/$fftn) + 0.08*cos(4*$pi * $p/$fftn)) * $re);
		&put_val;
	}

	# Flattop Window type 1
	print "\nflattop1:\n";
	for($p = 0; $p < $fftn; $p++) {
		if((4*$pi * ($p-($fftn/2)) / $fftn) == 0) { $sx = 1; }
		else { $sx = sin(4*$pi * ($p-($fftn/2)) / $fftn) / (4*$pi * ($p-($fftn/2)) / $fftn); }
		$n = int((0.54 - 0.46*cos(2*$pi * $p/$fftn)) * $sx * $re);
		&put_val;
	}

	# Flattop Window type 2
	print "\nflattop2:\n";
	for($p = 0; $p < $fftn; $p++) {
		$n = int((0.2810639 - 0.5208972*cos(2*$pi * $p/$fftn) + 0.1980399*cos(4*$pi * $p/$fftn)) * $re);
		&put_val;
	}

	# Rectanguler Window
	print "\nrectanguler:\n";
	for($p = 0; $p < $fftn; $p++) {
		$n = $re;
		&put_val;
	}

	exit;


sub put_val
{
		if(($p & $cn) == 0) { print "\t.dc.w "; }
		print $n;
		if(($p & $cn) != $cn) { print ", "; }
		if(($p & $cn) == $cn) { print "\n"; }
}
