for i in `seq 1000`; do
	echo "Running..." >> log_test
	./live 10000 1000 4 1000 4 1 > out_c
	tail -n +12 out_c > out_c_tmp; mv out_c_tmp out_c
	cmp out_c out_java >> log_test
done

