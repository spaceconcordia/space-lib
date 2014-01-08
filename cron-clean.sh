#!/bin/bash
# This cron-job will check for free disk space, and if the given limit is reached, 
# delete logs/archives that are older than a given time-frame

# resources
#http://superuser.com/questions/290986/how-to-create-tar-archive-split-into-or-spanning-multiple-files
#http://www.cyberciti.biz/faq/how-do-i-rotate-log-files/

df -H | grep -vE '^Filesystem|tmpfs|cdrom' | awk '{ print $5 " " $1 }' | while read output;
do
    #echo $output
    usep=$(echo $output | awk '{print $1}' | cut -d'%' -f1  )
    partition=$( echo $output | awk '{ print $2 }' )
    if [ $usep -ge 70 ]; then
        #echo "running out of diskspace \"$partition ($usep%)\" on $(hostname) as on $(date)"
        #0 0 * * * find /home/logs -mtime +20 -exec rm {} \; # remove files older than 20 days
    fi
done
