for FILE in `ls`; do mv $FILE `echo $FILE | sed -e 's:^0*::'`; done
