for f in $(find . -regex '.*(fig|ex).*.c'); do
    echo $f
done
