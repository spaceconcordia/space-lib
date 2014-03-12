#!/bin/bash
# This cron-job will check for free disk space, and if the given limit is reached, 
# archive and delete logs/archives that are older than given time-frames

# tar.gz vs bz vs zip vs gzip? http://ivoras.net/blog/tree/2010-07-15.what-to-use-for-log-compression.html

# resources
#http://superuser.com/questions/290986/how-to-create-tar-archive-split-into-or-spanning-multiple-files
#https://superuser.com/questions/685386/how-to-create-and-split-a-tar-archive-and-send-the-results-to-my-server
#http://www.cyberciti.biz/faq/how-do-i-rotate-log-files/

man logrotate
exit 1

df -H | grep -vE '^Filesystem|tmpfs|cdrom' | awk '{ print $5 " " $1 }' | while read output;
do
    #echo $output
    usep=$(echo $output | awk '{print $1}' | cut -d'%' -f1  )
    partition=$( echo $output | awk '{ print $2 }' )
    if [ $usep -ge 70 ]; then
        0 0 * * * find /home/logs -mtime +20 -print0 | tar -czvf $(date --iso).tar.gz --remove-files # archive and remove files older than 20 days
        #deal with files with spaces, newlines, leading dashes, and other funniness
        #handle an unlimited number of files
        #won't repeatedly overwrite your backup.tar.gz like using tar -c with xargs will do when you have a large number of files
    fi;
    if [ $usep -ge 90 ]; then
        echo "running out of diskspace \"$partition ($usep%)\" on $(hostname) as on $(date)"
        #0 0 * * * find /home/logs -mtime +20 -exec rm {} \; # remove files older than 20 days
    fi;
done
