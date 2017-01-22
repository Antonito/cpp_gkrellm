if [ "$1" = "" ] || [ "$2" = "" ]
then
    echo "Usage: $0 addr nb_requ"
    exit 1
fi

loadtest -n "$2" "$1"

exit 0
