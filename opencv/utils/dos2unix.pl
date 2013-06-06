#!/usr/bin/perl

open(input_file,$ARGV[0]);
binmode(input_file);

$data = join "", <input_file>;
eval "\$data =~ s/\r//g";

close(input_file);

open(output_file,">$ARGV[0]");
binmode(output_file);

print output_file $data;

close(output_file);

