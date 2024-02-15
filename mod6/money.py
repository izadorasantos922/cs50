cents = input("Enter your cents ")
count = 0
quarter = 25
dem = 10
nickel = 5
penny = 1
coin = round(float(cents) * 100)

while coin > 0:
 if coin >= quarter:
    coin -= quarter
    count = count + 1
 elif coin >= dem:
    coin -= dem
    count = count + 1
 elif coin >= nickel:
    coin -= nickel
    count = count + 1
 elif coin >= penny:
    coin -= penny
    count = count + 1

print("The number of coins is ", count)