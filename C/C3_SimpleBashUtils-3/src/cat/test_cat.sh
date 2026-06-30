#!/ bin / bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_files/test1.txt test_files/test2.txt test_files/test3.txt test_files/test4.txt"
echo "" > log.txt
TEST_DIR="./test_files"
mkdir -p $TEST_DIR
#Создание тестовых файлов
echo -e "\n\nThis is a test file\nWith multiple lines\n\n\nAnd empty lines\n\n" > "$TEST_DIR/test1.txt"
echo -e "File with\ttabs\tand\tspaces\n\n" > "$TEST_DIR/test2.txt"
echo -e "\n\n\nSpecial chars: рпга Non-printing chars test\n\n\n\n" > "$TEST_DIR/test3.txt"
echo -e "\n\n\n\nMultiple\n\n\n\nEmpty\n\n\nLines\n\n\n" > "$TEST_DIR/test4.txt"

for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -q s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
do
  for var2 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -q s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
