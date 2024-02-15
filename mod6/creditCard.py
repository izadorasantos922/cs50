
numero = input("Enter the credit card ")
creditNumber = int(numero)
arrayDeDigitos = [int(digito) for digito in numero]
tamanho = len(arrayDeDigitos)
sumOdd = 0
sumEven = 0
for i in range(tamanho - 1, -1, -1):
    if(i % 2 == 0):
        multipy = arrayDeDigitos[i] * 2
        if(multipy > 9):
            newMultiply = [int(numero) for numero in str(multipy)]
            tam = len(newMultiply)
            for i in range(tam - 1, -1, -1):
                sumEven += newMultiply[i]
        else:
            sumEven += multipy
for i in range(tamanho - 1, -1, -1):
    if(i % 2 != 0):
        sumOdd += arrayDeDigitos[i]
sumTotal = sumOdd + sumEven
while(creditNumber > 100):
    creditNumber /= 10
firstTwoDigits = int(creditNumber)

while(creditNumber > 10):
    creditNumber /= 10
firstDigit = int(creditNumber)
print(firstDigit)

if(tamanho == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37)):
    print("It's American Express")
elif(tamanho == 16 and (firstTwoDigits >= 51 and firstTwoDigits <= 55)):
    print("It's Mastecard")
elif(firstDigit == 4 and (tamanho == 13 or tamanho == 16)):
    print("It's Visa")
else:
    print("It's Invalid Card")