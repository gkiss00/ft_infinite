#########################################################
#                                                       #
#                         VAR                           #
#                                                       #
#########################################################

base="0123456789abcdef"

test="${base}${base}"

echo $base

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
do
    first="${test:${i}:1}"
    for i2 in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    do
        second="${test:${ji2}:1}"
        nb1="${first}${second}"
        for i3 in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        do
            third="${test:${i3}:1}"
            for i4 in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
            do
                fourth="${test:${i4}:1}"
                nb2="${third}${fourth}"
                ./ft_infinite $nb1 "^" $nb2
            done
        done
    done
done

#########################################################
#                                                       #
#                       ADDITION                        #
#                                                       #
#########################################################


test_addition () {
    
    if ( diff <(./ft_infinite $1 + $2) <(echo $3) )
    then
        echo -e "\033[0;32m[OK]\033[0m $1 + $2 = $3"
    else
        echo -e "\033[0;31m[ERROR]\033[0m $1 + $2 = $3"
    fi
}

# if [[ $1 == '' || $1 == '+' ]]
# then
#     test_addition 00 01 01
#     test_addition 00 05 05
#     test_addition f0 01 f1
#     test_addition f0 01 f1
#     test_addition 15 ef 0104
#     test_addition ff 01 0100
#     test_addition 09c4 09c4 1388
#     test_addition 01e240 01e240 03c480
#     test_addition 3c34eb12 3c34eb12 7869d624
#     test_addition 5347f27579 5347f27579 a68fe4eaf2

#     test_addition ffffffffff 00000001 010000000000
#     test_addition 0123456789abcdef0123456789abcdef 0123456789abcdef0123456789abcdef 02468acf13579bde02468acf13579bde
#     test_addition efefefefefefefefefefefefefefefefefefef 11111111111111111111111111111111 efeff001010101010101010101010101010100
# fi