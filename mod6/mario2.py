for i in range(5, 0, -1):
  for j in range(i, 0, -1): 
      print(" ", end="")
  for j in range(i - 1, 4, +1): 
      print("#", end="")
  print(" ", end="")
  for j in range(i - 1, 4, +1): 
      print("#", end="")
  print()