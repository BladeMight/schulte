name=schulte
dbgflg= -lgdi32 -lcomctl32 -o
uni= -DUNICODE -D_UNICODE
all:
	mkdir -p obj
	gcc -c $(uni) $(name).cpp -o obj/$(name).o
	windres -i $(name).rc -o obj/$(name).rc.o
	gcc $(uni) -s -Os -mwindows obj/$(name).o obj/$(name).rc.o -o $(name).exe
	./$(name)
deb:
	mkdir -p obj
	gcc -c $(uni) $(name).cpp -o obj/$(name).o
	windres -i $(name).rc -o obj/$(name).rc.o
	gcc $(uni) $(dbgflg) obj/$(name).o obj/$(name).rc.o -o $(name).exe
	./$(name)
x86:
	mkdir -p obj
	gcc -m32 -c $(uni) $(name).cpp -o obj/$(name).o
	windres -F pe-i386 -i $(name).rc -o obj/$(name).rc.o
	gcc -m32 $(uni) -s -Os -mwindows obj/$(name).o obj/$(name).rc.o -o $(name).exe
	./$(name)
