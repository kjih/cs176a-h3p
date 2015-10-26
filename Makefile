all: EmailSender.c
	gcc -o EmailSender EmailSender.c

clean:
	$(RM) EmailSender
