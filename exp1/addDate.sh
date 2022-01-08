#!/bin/bash

function ergodic(){
  cd $1
  for file in `ls`
  do
    if [ -d $1"/"$file ]
    then
      ergodic $1"/"$file
    else
      if [ "${file##*.}"x = "txt"x ]
      then
        lastSen=$(sed -n '$p' $file)
        if [[ "$lastSen" == *.????????.??:?? ]]
        then
          sed -i '$d' $file
        fi

        info=$USER.$(date "+%Y%m%d.%H:%M")
        # 判断文件是否为空，空则使用echo命令添加，非空则使用sed命令
        test -s $file  \
            && sed -i "\$a $info" $file \
            || echo "$info" >> $file
      fi
    fi
  done
  cd ..
}

IFS=$'\n'
ergodic $1