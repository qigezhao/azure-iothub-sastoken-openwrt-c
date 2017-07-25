# by Qige <qigezhao@gmail.com>
# 2017.07.25

APP=azure-sastoken

all: $(APP)

$(APP): *.c zutils/*.c
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) -I. -o $@ $^ -L. -lcrypto

clean:
	rm -f $(APP) *.o zutils/*.o
	
