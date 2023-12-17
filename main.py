with open("trigrams.txt", "r") as file:
    text = ""
    for line in file:
        line = line.strip()
        line = line.replace("[", "{")
        line = line.replace("]", "}")
        text += line
    
    with open("trigrams2.txt", "w") as file:
        file.write(text)