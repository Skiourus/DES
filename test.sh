#!/bin/sh
var=1
key=9
msg=10
cipher=11
file=./test/TECBvartext.rsp #for every file
max=64 #nb of count+1
echo "ENCRYPTION TEST"
while [ $var -le $max ]
do
kkey=`head -n $key $file | tail -n 1 | cut -c8-23` #get the key for the test
mmsg=`head -n $msg $file | tail -n 1 | cut -c13-28` #get the plaintext for encrypt
ccipher=`head -n $cipher $file| tail -n 1 | cut -c14-29` #get the theoretical solution
crypt=`./main.exe $mmsg $kkey | cut -c1-16` #compute DES encryption with key and message, store the ciphertext into crypt
echo $crypt " " $ccipher
if [ "$crypt" = "$ccipher" ] #test if crypt is the same as theoretical solution
	then echo TRUE
else
	echo FALSE
fi
var=$((var+1)) #upload variable lines
key=$((key+5))
msg=$((msg+5))
cipher=$((cipher+5))
done



echo "DECRYPTION TEST"
var=1
key=$((key+6))
msg=$((msg+6))
cipher=$((cipher+6))


while [ $var -lt $max ]
do
kkey=`head -n $key $file | tail -n 1 | cut -c8-23` #get key
mmsg=`head -n $msg $file | tail -n 1 | cut -c14-29` #get ciphertext to decrypt
ccipher=`head -n $cipher $file | tail -n 1 | cut -c13-28` #get theoretical plaintext
crypt=`./main2.exe $mmsg $kkey | cut -c1-16` #compute DES decryption 
echo $crypt " " $ccipher
if [ "$crypt" = "$ccipher" ]
	then echo TRUE
else
	echo FALSE
fi
var=$((var+1))
key=$((key+5))
msg=$((msg+5))
cipher=$((cipher+5))
done
