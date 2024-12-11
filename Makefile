all:
	g++ -std=c++17 Contacts0/main/main.cpp Contacts0/source/Contact.cpp Contacts0/source/ContactManager.cpp Contacts0/source/FileHandler.cpp -o Contacts0/build/app -finput-charset=UTF-8
	./Contacts0/build/app
