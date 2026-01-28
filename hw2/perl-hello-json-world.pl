#!/usr/bin/perl
# In Perl, you must first install the JSON package from CPAN (the Perl equivalent to npm)
use JSON;

print "Cache-Control: no-cache\n";
print "Content-type: application/json\n\n";

$date = localtime();
$address = $ENV{REMOTE_ADDR};

my %message = ('title' => 'Hello, Everyone!', 'heading' => 'Hello, Perl!', 'message' => 'This page was generated with our love for the Perl programming language - Albert, Hajin, and Joey', 'time' => $date, 'IP' => $address);

my $json = encode_json \%message;
print "$json\n";
