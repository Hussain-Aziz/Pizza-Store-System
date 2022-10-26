CC = g++
CCOPTS = -g -Wall -std=c++17 -lstdc++fs
DIR = PizzaStoreSystem
ACCOUNTS = Account.o Admin.o Chef.o Customer.o DeliveryDriver.o Manager.o Staff.o
ACCOUNT = Account.o
ORDERITEMS = Orderitem.o Pizza.o NonPizzaItem.o
ORDERITEM = Orderitem.o
ORDER = Order.o
STORE = Store.o
COMPANY = Company.o
OTHER = $(DIR)/Utils.h $(DIR)/Exceptions.h

StoreLanding: $(DIR)/StoreLanding.cpp $(COMPANY)
	$(CC) $(CCOPTS) $(DIR)/StoreLanding.cpp $(OTHER) $(COMPANY) $(STORE) $(ORDER) $(ORDERITEMS) $(ACCOUNTS) -o PizzaStoreSystem.exe

Company.o: $(DIR)/Company/Company.cpp $(DIR)/Company/Company.h $(OTHER) $(STORE) $(ACCOUNTS)
	$(CC) $(CCOPTS) -c $(DIR)/Company/Company.cpp

Store.o: $(DIR)/Store/Store.cpp $(DIR)/Store/Store.h $(ORDER) $(ACCOUNTS)
	$(CC) $(CCOPTS) -c $(DIR)/Store/Store.cpp

Order.o: $(DIR)/Order/Order.cpp $(DIR)/Order/Order.h $(ORDERITEMS) $(OTHER)
	$(CC) $(CCOPTS) -c $(DIR)/Order/Order.cpp

OrderItem.o: $(DIR)/OrderItem/OrderItem.cpp $(DIR)/OrderItem/OrderItem.h
	$(CC) $(CCOPTS) -c $(DIR)/OrderItem/OrderItem.cpp

Pizza.o: $(DIR)/OrderItem/Pizza.cpp $(DIR)/OrderItem/Pizza.h $(ORDERITEM)
	$(CC) $(CCOPTS) -c $(DIR)/OrderItem/Pizza.cpp

NonPizzaItem.o: $(DIR)/OrderItem/NonPizzaItem.cpp $(DIR)/OrderItem/NonPizzaItem.h $(ORDERITEM)
	$(CC) $(CCOPTS) -c $(DIR)/OrderItem/NonPizzaItem.cpp

Account.o: $(DIR)/Account/Account.cpp $(DIR)/Account/Account.h
	$(CC) $(CCOPTS) -c $(DIR)/Account/Account.cpp

Admin.o: $(DIR)/Account/Admin.cpp $(DIR)/Account/Admin.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/Admin.cpp

Chef.o: $(DIR)/Account/Chef.cpp $(DIR)/Account/Chef.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/Chef.cpp

Customer.o: $(DIR)/Account/Customer.cpp $(DIR)/Account/Customer.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/Customer.cpp

DeliveryDriver.o: $(DIR)/Account/DeliveryDriver.cpp $(DIR)/Account/DeliveryDriver.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/DeliveryDriver.cpp

Manager.o: $(DIR)/Account/Manager.cpp $(DIR)/Account/Manager.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/Manager.cpp

Staff.o: $(DIR)/Account/Staff.cpp $(DIR)/Account/Staff.h $(ACCOUNT)
	$(CC) $(CCOPTS) -c $(DIR)/Account/Staff.cpp

clean:
	rm -f *.o