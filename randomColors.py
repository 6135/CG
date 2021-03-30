import random
filepath = "outColors.txt"
f = open(filepath,"w")
f.write("static const float colors[] = {\n\t")
for x in range((360+1)*3):
    number = random.random()
    f.write(str(round(number,4)) + ", ")
    if (x+1)%3 == 0 :
        f.write("\n\t")
    
f.write("};\n")