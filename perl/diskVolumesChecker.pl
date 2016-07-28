#!/usr/bin/perl

########################################################################
# PLEASE DON'T EXECUTE THIS SCRIPT, UNLESS YOU KNOW WHAT YOU ARE DOING #
######################################################################## 
package main;
 
use strict;
use warnings;
 
# DISK SIZE ROUND - DEFUALT 2%
use constant SIZE_ROUND => 0.02;
 
sub split_data {
    my ($delimiter, $line) = @_;
    my @dataArr = split("$delimiter", "$line");
    return @dataArr;
}
 
# CONVERT KB TO MB OR GB
# ALLOWED UNITS: MB, GB
sub conv_data_unit {
    my ($size, $unit) = @_;
    if ($size == 0) {return 0};
 
    if ($unit eq "MB") {
        return $size / 1024;
    } elsif ($unit eq "GB") {
        return ($size / 1024 / 1024);
    }
}
 
#TO DO
#GROUP DUPLICATION CHECKS
#ERROR HANDLING
 
sub check_volumes {
    my ($IN_FILE) = @_;
    my %volHash;
    #error handling
    open(FILE, "<", $IN_FILE);
    my @vol = `df -T | sed 's/  */ /g'`;
    shift @vol;
 
    for my $line (@vol) {
        chomp $line;
        my @volVal = split_data(" ", "$line");
        #My point as a hash key
        $volHash{$volVal[6]}{"volname"} = $volVal[0];
        $volHash{$volVal[6]}{"fstype"} = $volVal[1];
        $volHash{$volVal[6]}{"size"} = $volVal[2];
        ##ADD MORE STUFF HERE IF YOU WANT
    }
 
    while (my $line = <FILE>) {
        my @volArr = split_data("\t", "$line");
        my ($vgroup,$lvol,$mount,$fstype,$size) = ($volArr[0],
                                                   $volArr[1],
                                                   $volArr[2],
                                                   $volArr[3],
                                                   $volArr[4]);
 
        if (exists $volHash{$mount}) {
            if ($fstype && $volHash{$mount}{"fstype"} ne $fstype){ 
		print "Incorrect fstype for: $mount\n"; 	
	    }

            if ($size) {
                my $vsize = conv_data_unit($volHash{$mount}{"size"}, "GB");
                print "VSIZE $vsize\n";
 
                if ($vsize < ($size - ($size * SIZE_ROUND)) || \
                   ($vsize > ($size + ($size * SIZE_ROUND))))
                {
                   print "Incorrect size: $mount\n";
                }
            }
 
            if ($vgroup && $lvol) {
                $volHash{$mount}{"volname"} =~ /([^\/]*$)/;
                my $vname = $1;
                my @lvmArr = split_data("-", $vname);
                if ($vgroup && ($vgroup ne $lvmArr[0])) { 
		    print "Incorrect lvm group name: $lvmArr[0]\n"; 
		}
                if ($lvol && ($lvol ne $lvmArr[1])) { 
		    print "Incorrect lvm group name $lvmArr[1]\n"; 
		}
            }
        } else {
            print "Mount point $mount does not exist\n";
        }
    }
 
    close(FILE);
}
 
sub check_group {
    my ($IN_FILE, $GFILE) = @_;
    my %grpHash;
    #error handling
    open(FILE, "<", $IN_FILE);
    open(GRPFILE, "<", $GFILE);
 
    while (my $line = <GRPFILE>) {
        my @grpVal = split_data(":", "$line");
        $grpHash{$grpVal[0]}{"pass"} = $grpVal[1];
        $grpHash{$grpVal[0]}{"gid"} = $grpVal[2];
        $grpHash{$grpVal[0]}{"gusers"} = $grpVal[3];
 
     }
 
    while (my $line = <FILE>) {
        my @grpArr = split_data("\t", "$line");
        my ($gid,$gname,$gusers,$valid,$perm) = ($grpArr[0],
                                                 $grpArr[1],
                                                 $grpArr[2],
                                                 $grpArr[3],
                                                 $grpArr[4]);
 
        if (exists $grpHash{$gname}) {
            if ($grpHash{$gname}{"pass"} ne "x"){ 
		print "Password not encrypt group: $gname\n"; 
	    }

            if ($gid && ($grpHash{$gname}{"gid"} ne $gid)){ 
		print "Group $gname has incorrect gid: $gid\n"; 
            }

            if ($gusers) {
                my @usrArr = split_data(",", $gusers);
                for my $user (@usrArr) {
                   chomp $user;
                   if ($grpHash{$gname}{"gusers"} !~ /$user(,|$)/) {
                       print "User $user dosen't belong to group $gname\n";
                   }
                }
            }
        } else {
            print "Group $gname does not exist\n";
        }
     }
 
     close(FILE);
     close(GRPFILE);
}
 
############# MAIN FUNCTION ###########################
check_group("info.php", "group");
check_volumes("info_vol.php");
############# END OF MAIN FUNCTION #####################
