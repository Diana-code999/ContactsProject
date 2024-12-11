all:
	g++ -std=c++17 Contacts0/main/main.cpp Contacts0/source/Contact.cpp Contacts0/source/ContactManager.cpp Contacts0/source/FileHandler.cpp -o Contacts0/build/app -finput-charset=UTF-8

Task1:
	cd qt/Contacts && qmake Contacts.pro && make && ./Contacts

Task2:
	cd qt/Contacts2 && qmake Contacts.pro && make && ./Contacts

Task3:
	cd qt/Contacts3 && qmake Contacts.pro && make && ./Contacts

run:
	./Contacts0/build/app
