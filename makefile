name=schulte
conflg= -lgdi32 -lcomctl32 -o
uni= -DUNICODE -D_UNICODE
all:
	gcc $(name).cpp $(uni) -s -Os -mwindows -o $(name).exe
	./$(name)
deb:
	gcc $(name).cpp $(uni) -lgdi32 -lcomctl32 -o $(name).exe
	./$(name)
con:
	gcc 24dr.cpp $(uni) -s -Os $(conflg) $(name).exe
	./$(name)