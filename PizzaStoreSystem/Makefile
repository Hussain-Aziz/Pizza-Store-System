CC = g++
CCOPTS = -g -Wall -std=c++17 -lstdc++fs
ACCOUNTS = Account.o Admin.o Chef.o Customer.o DeliveryDriver.o Manager.o Staff.o
ORDERITEMS = Orderitem.o Pizza.o NonPizzaItem.o
ORDER = Order.o
STORE = Store.o
COMPANY = Company.o
OTHER = Utils.h Exceptions.h

StoreLanding: StoreLanding.cpp $(COMPANY)
	$(CC) $(CCOPTS) StoreLanding.cpp $(OTHER) $(COMPANY) $(STORE) $(ORDER) $(ORDERITEMS) $(ACCOUNTS) -o PizzaStoreSystem.exe

Company.o: Company/Company.cpp Company/Company.h $(OTHER) $(STORE) $(ACCOUNTS)
	$(CC) $(CCOPTS) -c Company/Company.cpp

Store.o: Store/Store.cpp Store/Store.h $(ORDER) $(ACCOUNTS)
	$(CC) $(CCOPTS) -c Store/Store.cpp

Order.o: Order/Order.cpp Order/Order.h $(ORDERITEMS) $(OTHER)
	$(CC) $(CCOPTS) -c Order/Order.cpp

OrderItem.o: OrderItem/OrderItem.cpp OrderItem/OrderItem.o
	$(CC) $(CCOPTS) -c OrderItem/OrderItem.cpp

Pizza.o: OrderItem/Pizza.cpp OrderItem/Pizza.h OrderItem.o
	$(CC) $(CCOPTS) -c OrderItem/Pizza.cpp

NonPizzaItem.o: OrderItem/NonPizzaItem.cpp OrderItem/NonPizzaItem.h OrderItem.o
	$(CC) $(CCOPTS) -c OrderItem/NonPizzaItem.cpp

Account.o: Account/Account.cpp Account/Account.h Company.o
	$(CC) $(CCOPTS) -c Account/Account.cpp

Admin.o: Account/Admin.cpp Account/Admin.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/Admin.cpp

Chef.o: Account/Chef.cpp Account/Chef.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/Chef.cpp

Customer.o: Account/Customer.cpp Account/Customer.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/Customer.cpp

DeliveryDriver.o: Account/DeliveryDriver.cpp Account/DeliveryDriver.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/DeliveryDriver.cpp

Manager.o: Account/Manager.cpp Account/Manager.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/Manager.cpp

Staff.o: Account/Staff.cpp Account/Staff.h Account.o Company.o
	$(CC) $(CCOPTS) -c Account/Staff.cpp

clean:
	rm -f *.o *.exe