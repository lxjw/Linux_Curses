#Lucian Jiang-Wei
#lxj160030@utdallas.edu
#CS 3377.502
#Editted Dr.Perkin's Example


CXX = g++
CXXFLAGS = -I /scratch/perkins/include 
CPPFLAGS = -Wall
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -l cdk -lcurses

PROJECTNAME = Project6Backup

EXECFILE = prog6

OBJS = prog6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS)  *~ \#*

$(EXECFILE):	$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
