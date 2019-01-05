typedef struct address{
	char address[50];
	char city[50];
	char state[50];
	int zip_Code;
}address;

address one = {.address = "154 Oak Meadow St.", .city = "Detroit", .state = "Michigan", .zip_Code = 48076};
address two = {.address = "7920 Oakwood St.", .city = "Minneapolis", .state = "Minnesota", .zip_Code = 55414};
address three = {.address = "821 Pheasant Street", .city = "Orlando", .state = "Florida", .zip_Code = 78943};
address four = {.address = "9213 Canal Lane", .city = "Temple", .state = "Arizona", .zip_Code = 23769};
address five = {.address = "330 N. Plumb Branch Road", .city = "Arlington", .state = "Texas", .zip_Code = 98154};
