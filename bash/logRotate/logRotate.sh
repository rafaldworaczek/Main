TMP_DIR="/usr/local/scripts/tmp/"
MAIN_DIR="/var/log/nginx"
LOG_STRUCTURE_DIR="$MAIN_DIR/archive"
PARSED_LOGS_DIR="$MAIN_DIR/parsed"
COUNTER_OFFSET=10
MAX_CHILD_PROESSES=5
LOGROTATE_TIME=15
 
declare -A months
 
months[Jan]=01;
months[Feb]=02;
months[Mar]=03;
months[Apr]=04;
months[May]=05;
months[Jun]=06;
months[Jul]=07;
months[Aug]=08;
months[Sep]=09;
months[Oct]=10;
months[Nov]=11;
months[Dec]=12;
 
#LOGROTATE_TIME < 0
 
parse_minute () {
    #should work for 30 minutes as weell 
    if [[ "$minute" =~ ^0 ]]; then
        minute="${minute:1:2}"
    fi
 
    minute_base="$(( ($minute / $LOGROTATE_TIME) * $LOGROTATE_TIME ))"
 
    if [[ "$minute_base" -eq 0 ]]; then
        minute_base="00";
    fi
 
}
 
function create_struct () {
    parse_minute $minute;
 
    output_dir="$LOG_STRUCTURE_DIR/$year/$month/$day/$hour"
    if [ ! -d "$output_dir" ]; then
        mkdir -p "$output_dir";
    fi
 
    output_file="$output_dir/$main_name-$year-$month-$day-$hour-$minute_base";
 
    echo "$line" >> "$output_file"; 
 
    if [ $(( $line_counter % $COUNTER_OFFSET )) -eq 0 ]; then
        echo "$line_counter" > $TMP_DIR/$filename; 
    fi
 
    let line_counter=line_counter+1;
    #write line to file if returns fine then update line in file
}
 
 
function fill_date () { 
    if [[ $filename == *error* ]]; then  
       raw_date="${line:0:19}"
       echo "Error $raw_date"
       date="${raw_date//" "/:}"
    else
       raw_date="${line:1:17}"
       echo "Access $date"
    fi
 
    #Performance reason - bash internal
    #raw_date="${line:1:17}"
    date="${raw_date//"/"/:}"
    date_arr=(${date//:/ })
 
    if [[ $filename == *error* ]]; then  
        day=${date_arr[2]};
        month="${date_arr[1]}";
        year=${date_arr[0]};
    else
        day=${date_arr[0]};
        month_name="${date_arr[1]}";
        month=${months[$month_name]};
        year=${date_arr[2]};
    fi
 
   hour=${date_arr[3]};
   minute=${date_arr[4]};
 
   echo $year $monnth $day $hour $minute
 
}
 
function read_file ()
{
    for fnames in $MAIN_DIR/$filename-*
    do
        path="$fnames"
 
        exec 5< $path
 
        if flock -n -x 5; then 
            stream="";
            nline="";
            line_counter=0;
            redirect="";
 
            filename=$1;
            main_name=`echo "$filename" | awk -F "/" '{print $NF}' | awk -F "-" '{print $1}'`
 
 
            if [ -f $TMP_DIR/$filename ]; then
                nline=`cat $TMP_DIR/$filename`;
                line_counter="$nline";
            fi
 
            if [ -z "$nline" ]; then 
                while read line <&5; do
                    fill_date $line;
                    create_struct $line
                done
            else
                #not very nice syntax because bash limitations
                while read line; do
                     fill_date $line;
                     create_struct $line
                done < <(tail -n +"$line_counter" "$path")
            fi
 
            mv $path $PARSED_LOGS_DIR;
 
            [ -f "$TMP_DIR/$filename" ] && rm $TMP_DIR/$filename; 
 
            exec 5>&-
 
        else
            echo "another process is doing job";
            exec 5>&-
            exit 0;
        fi
    done 
 
}
 
###########################################################
#PROGRAM STARTS HERE                                      #
###########################################################
 
find $MAIN_DIR -maxdepth 1 -type f -printf "%f\n" | grep -P "\-[0-9]{10}$" | 
awk -F "-" '{print $1}' | sort | uniq | while read filename; do
   read_file $filename &
 
    curr_child=`jobs -p | wc -l`
    if [[ "$curr_child" -gt "$MAX_CHILD_PROESSES" ]]; then
       echo "have to wait"
       wait
    fi
 
done
 
