
duration = open("ManualDuration.txt", "r")
data = open("ManualData.txt", "r")
out = open("result.txt", "w+")

durationCont = duration.readlines()
dataCont = data.readlines()

lines = []
for index,durationLine in enumerate(durationCont):
    line = durationLine.rstrip() + " " + dataCont[index].rstrip() + "\n"
    lines.append(line)

out.writelines(lines)

