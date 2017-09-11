NSYM	= 10000
NVERTEX	= 1000
MAXSUCC	= 4
NACTIVE	= 100
PRINT   = 1

PATH    :=$(CURDIR)/scala-2.10.6/bin:$(PATH)

all:
	./download_actors.sh
	@mkdir -p classes
	#scalac -g:vars -d classes dataflow.scala
	#scalac -deprecation -d classes dataflow.scala
	scalac -deprecation -optimise -d classes dataflow.scala
	scala -classpath classes Driver $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) $(PRINT)

compare:
	./download_actors.sh
	scala -classpath classes Driver $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) $(PRINT) > lab2scala.out
	tail -n +4 lab2scala.out > lab2scala; mv lab2scala lab2scala.out
	cd ../Lab1/ && javac Dataflow.java && java -Xmx2048M Dataflow $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) 1 $(PRINT) > ../Lab2Niklas/lab1java.out
	tail -n +9 lab1java.out > out_java_tmp; mv out_java_tmp lab1java.out
	cmp lab1java.out lab2scala.out
