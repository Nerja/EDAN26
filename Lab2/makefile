SHELL=/bin/bash
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
	cd ../Lab1/ && javac Dataflow.java && java -Xmx2048M Dataflow $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) 1 $(PRINT) > ../Lab2/out_java
	scalac -deprecation -optimise -d classes dataflow.scala
	scala -classpath classes Driver $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) $(PRINT) > out_scala
	tail -n +9 out_java > out_java_tmp; mv out_java_tmp out_java
	tail -n +5 out_scala > out_scala_tmp; mv out_scala_tmp out_scala
	cmp out_scala out_java	
	rm out_scala
	rm out_java	

measuretime:
	./download_actors.sh
	@mkdir -p classes
	scalac -deprecation -optimise -d classes dataflow.scala
	scala -J-Xmx12g -classpath classes Driver 200000 20000 4 100 0
	cd ../Lab1/ && javac Dataflow.java && java -Xmx12048M Dataflow 200000 20000 4 100 1 0
	cd ../Lab1/ && javac FastDataflow.java && java -Xmx12048M FastDataflow 200000 20000 4 100 4 0

run:
	scala -classpath classes Driver $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) $(PRINT)

simple:
	scalac -deprecation -optimise -d classes dataflow.scala
	scala -classpath classes Driver $(NSYM) $(NVERTEX) $(MAXSUCC) $(NACTIVE) $(PRINT)

