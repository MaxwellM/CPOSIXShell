# Author - Mark Royer
# 
# This Makefile is an example that you may use and modify
# as you wish. 
#
# Make sure to modify the LASTNAME, ASSIGNMENT, and VERSION variables
# as needed.  
#  
# See 
# 
# http://www.gnu.org/software/make/manual/make.html
#
# for additional details.

CFLAGS = -std=c99 -O2 -g -Wall -fmessage-length=0 -MMD -MP

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

TARGET = ShellProject

# Make sure to modify these three variables for the project submission!
LASTNAME = morin
ASSIGNMENT = 02
VERSION = 0001

FNAME = $(LASTNAME)-hw$(ASSIGNMENT)-$(VERSION)

DOCDIR = docs

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

all:	$(TARGET) 

-include $(OBJS:%.o=%.d)

clean:
	rm -rf *~ $(OBJS) $(OBJS:%.o=%.d) $(TARGET) $(DOCDIR) $(FNAME).tgz

docs: $(TARGET) README.dox
	doxygen Doxyfile

submit: clean
	cp -r $(PWD) /tmp/$(FNAME)
	tar -cvz -C /tmp/ -f $(FNAME).tgz $(FNAME)
	rm -r /tmp/$(FNAME)
