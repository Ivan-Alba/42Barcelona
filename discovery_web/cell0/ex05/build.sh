if [[ $1 != "" ]]
then
    for arg in $@
do
    mkdir ex$arg
    done
else
    echo "No arguments supplied"
fi


