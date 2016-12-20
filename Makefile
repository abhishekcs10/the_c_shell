all: compile run
compile:
	gcc myshell_16CS60R83.c -o myshell -g
	gcc mymkdir_16CS60R83.c -o mymkdir
	gcc mycd_16CS60R83.c -o mycd
	gcc mypwd_16CS60R83.c -o mypwd
	gcc mygrep_16CS60R83.c -o mygrep
	gcc mymv_16CS60R83.c -o mymv
	gcc myrm_16CS60R83.c -o myrm
	gcc myhistory_16CS60R83.c -o myhistory
	gcc mypipe_16CS60R83.c -o mypipe
	gcc myls_16CS60R83.c -o myls
	gcc myps_16CS60R83.c -o myps
	gcc mytail_16CS60R83.c -o mytail
	gcc sed_grep_16CS60R83.c -o mysed
	gcc signal1_16CS60R83.c -o signal1
	gcc signal2_16CS60R83.c -o signal2
	gcc signal3_16CS60R83.c -o signal3
run:
	./myshell
