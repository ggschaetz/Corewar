# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gschaetz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:23:56 by gschaetz          #+#    #+#              #
#    Updated: 2017/12/05 11:17:23 by ybenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "\n|||||||||||||||          TEST ASM COREWAR         ||||||||||||||||\n\n"
mkdir cor_us cor_source
i=0
j=0;
tableau1=`ls champs`
echo "-----------------------------------------------------------------\n"
echo "------------------------ \033[31mstart compile\033[0m --------------------------\n"
echo "-----------------------------------------------------------------\n\n"
echo "----------- \033[31mSOURCE ASM\033[0m ------------\n"
for champ in $tableau1
do
	echo "compile $champ"
	echo `./../source/asm champs/$champ`
done
lui=`ls champs/*.cor | cut -d / -f 2`
for champ in $lui
do
	echo "`mv champs/$champ cor_source/.`\c"
	echo "`xxd cor_source/$champ > cor_source/"xxd_"$champ`\c"
	((j++))
done
echo "\n------------    \033[31mASM\033[0m    ------------\n"
for champ in $tableau1
do
	echo "`./asm champs/$champ`"
done

echo "----------------------------------------------------------------\n"
echo "------------------------- \033[31mstart diff\033[0m ---------------------------\n"
echo "----------------------------------------------------------------\n"
nous=`ls champs/*.cor | cut -d / -f 2`
for champ in $nous
do
	echo "`mv champs/$champ cor_us/`\c"
	echo "`xxd cor_us/$champ > cor_us/"xxd_"$champ`\c"
done
echo "`chmod 777 cor_source/xxd_*`\c"
echo "`chmod 777 cor_us/xxd_*`\c"
tableau2=`ls cor_source/xxd_* | cut -d / -f 2`
for champ in $tableau2
do
	diff=`diff cor_source/$champ cor_us/$champ`
	echo "source ASM vs ASM (\033[33m$champ\033[0m)"
	if [ "$diff" == "" ]
	then
		((i++))
		echo "\033[32mOK     ✓ \033[0m\n"
	else
		echo "\033[31mFAILED ✖\033[0m\n"
	fi
done
	if [ $i = $j ]
	then
		echo "----------------------------------------------------------------\n"
		echo "-------------------------- \033[32mALL GOOD\033[0m ----------------------------\n"
		echo "----------------------------------------------------------------\n"
	else
		echo "----------------------------------------------------------------\n"
		echo "------------------------ \033[31m$i\033[0m / \033[32m$j GOOD\033[0m --------------------------\n"
		echo "----------------------------------------------------------------\n"
	fi
	rm -rf cor_us cor_source
