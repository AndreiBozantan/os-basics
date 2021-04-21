VERSION="0.1"
while (True):
  s = input("> ")
  if s == "exit":
    exit()
  elif s == "version":
    print(VERSION)
  elif s == "help":
    print("exit version help")
  else:
    print(f"Command '{s}' not found.")
