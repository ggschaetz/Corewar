# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:23:56 by gschaetz          #+#    #+#              #
#    Updated: 2017/11/30 11:34:56 by gschaetz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "\n||||||||||||||||          TEST COREWAR         |||||||||||||||||\n\n"
a=0
b=0
i=0
j=0
y=0
k=0
z=0
t=0
tableau1=`ls champs/cor`
echo "-----------------------------------------------------------------\n"
echo "------------------------ \033[31mTest 1 champ\033[0m -------------------------\n"
echo "-----------------------------------------------------------------\n"
for champ in $tableau1
do
	echo "VM source`./source/corewar champs/cor/$champ > source_test` vs VM (\033[33m$champ\033[0m) `./corewar champs/cor/$champ > corewar_test`"
	diff=`diff source_test corewar_test`
	if [ "$diff" = "" ]
	then
		((j++))
		echo "\033[32mOK      ✓ \033[0m\n"
	else
		echo "\033[31mFAILED  ✖\033[0m\n"
	fi
	((i++))
done

echo "-----------------------------------------------------------------\n"
echo "------------------------ \033[31mTest 2 champs\033[0m -------------------------\n"
echo "-----------------------------------------------------------------\n"

for champ1 in $tableau1
do
	for champ2 in $tableau1
	do
		if [ "$champ1" != "$champ2" ]
		then
			echo "VM source`./source/corewar champs/cor/$champ1 champs/cor/$champ2 > source_test` vs VM (\033[33m$champ1\033[0m et \033[33m$champ2\033[0m) `./corewar champs/cor/$champ1 champs/cor/$champ2 > corewar_test`"
			diff=`diff source_test corewar_test`
			if [ "$diff" = "" ]
			then
				((k++))
				echo "\033[32mOK      ✓ \033[0m\n"
			else
				echo "\033[31mFAILED  ✖\033[0m\n"
			fi
		((y++))
		fi
	done
done

echo "-----------------------------------------------------------------\n"
echo "----------------------- \033[31mTest 3 champs\033[0m ------------------------\n"
echo "-----------------------------------------------------------------\n"
for champ1 in $tableau1
do
	for champ2 in $tableau1
	do
		for champ3 in $tableau1
		do
			if [ "$champ1" != "$champ2" ] && [ "$champ1" != "$champ3" ] && [ "$champ2" != "$champ3" ]
			then
				echo "VM source`./source/corewar champs/cor/$champ1 champs/cor/$champ2 champs/cor/$champ3 > source_test` vs VM (\033[33m$champ1\033[0m, \033[33m$champ2\033[0m et \033[33m$champ3\033[0m) `./corewar champs/cor/$champ1 champs/cor/$champ2 champs/cor/$champ3 > corewar_test`"
				diff=`diff source_test corewar_test`
				if [ "$diff" = "" ]
				then
					((t++))
					echo "\033[32mOK      ✓ \033[0m\n"
				else
					echo "\033[31mFAILED  ✖\033[0m\n"
				fi
			((z++))
			fi
		done
	done
done

echo "-----------------------------------------------------------------\n"
echo "----------------------- \033[31mTest 4 champs\033[0m ------------------------\n"
echo "-----------------------------------------------------------------\n"
for champ1 in $tableau1
do
	for champ2 in $tableau1
	do
		for champ3 in $tableau1
		do
			for champ4 in $tableau1
			do
				if [ "$champ1" != "$champ2" ] && [ "$champ1" != "$champ3" ] && [ "$champ1" != "$champ4" ] && [ "$champ2" != "$champ3" ] && [ "$champ2" != "$champ4" ] &&  [ "$champ3" != "$champ4" ]
				then
					echo "VM source`./source/corewar champs/cor/$champ1 champs/cor/$champ2 champs/cor/$champ3 champs/cor/$champ4> source_test` vs VM (\033[33m$champ1\033[0m, \033[33m$champ2\033[0m, \033[33m$champ3\033[0m et \033[33m$champ4\033[0m) `./corewar champs/cor/$champ1 champs/cor/$champ2 champs/cor/$champ3 champs/cor/$champ4 > corewar_test`"
					diff=`diff source_test corewar_test`
					if [ "$diff" = "" ]
					then
						((a++))
						echo "\033[32mOK      ✓ \033[0m\n"
					else
						echo "\033[31mFAILED  ✖\033[0m\n"
					fi
				((b++))
				fi
			done
		done
	done
done


echo "-----------------------------------------------------------------\n"
echo "----------------------- \033[31m     RESULTS    \033[0m ------------------------\n"
echo "-----------------------------------------------------------------\n"
if [ $j = $i ]
	then
		echo "			one champ	: \033[32mALL GOOD $j / $i\033[0m"
	else
		echo "			one champ	: \033[31m$j\033[0m / \033[32m$i GOOD\033[0m"
fi
if [ $k = $y ]
	then
		echo "			two champs	: \033[32mALL GOOD $k / $y\033[0m"
	else
		echo "			two champs	: \033[31m$k\033[0m / \033[32m$y GOOD\033[0m"
fi
if [ $t = $z ]
	then
		echo "			three champs	: \033[32mALL GOOD $t / $z\033[0m"
	else
		echo "			three champs	: \033[31m$t\033[0m / \033[32m$z GOOD\033[0m"
fi
if [ $a = $b ]
	then
		echo "			four champs	: \033[32mALL GOOD $a / $b\033[0m"
	else
		echo "			four champs	: \033[31m$a\033[0m / \033[32m$b ONLY\033[0m"
fi
