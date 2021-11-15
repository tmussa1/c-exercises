fl: fl.o wordstore13.o process.o mail_merge.o process_record.o
	gcc -Wall -Wextra -o fl fl.o wordstore13.o process.o process_record.o mail_merge.o

fl.o: fl.c fl.h
	cc -c fl.c

wordstore13.o: wordstore13.c ws13.h
	cc -c wordstore13.c

process.o: process.c fl.h ws13.h
	cc -c process.c

process_record.o: process_record.c fl.h ws13.h
	cc -c process_record.c

mail_merge.o: mail_merge.c fl.h ws13.h
	cc -c mail_merge.c

