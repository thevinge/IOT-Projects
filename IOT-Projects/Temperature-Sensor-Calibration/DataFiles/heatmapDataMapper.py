out = open("HeatmapOutput.dat", "w+")
ppfile = open("debug.dat", "w+")
maxFile = open("max.dat", "w+")
minFile = open("min.dat", "w+")
meanFile = open("mean.dat", "w+")
heatmapSize = 1028


def trim(str):
    return str.rstrip()


def mean(listOfInts):
    return sum(listOfInts) / len(listOfInts)


heatmapData = list(map(trim, open("ESP32_Data.txt", "r").readlines()))
heatmapDuration = list(map(trim, open("ESP32_Duration.txt", "r").readlines()))

bucketSize = len(heatmapData)/heatmapSize
dataSize = (4096/heatmapSize)

outer = []
columnMaxes = []
columnMins = []
columnMeans = []

for x in range(heatmapSize):
    arr = []
    for y in range(heatmapSize):
        arr.append(0)
    outer.append(arr)


for x in range(heatmapSize):
    lowerTimeBucket = 0
    upperTimeBucket = int(bucketSize)
    if x != 0:
        lowerTimeBucket = int((x-1) * bucketSize)
        upperTimeBucket = int(x * bucketSize)
    colList = []
    for y in range(heatmapSize):
        lowerValueBucket = 0
        upperValueBucket = dataSize
        if y != 0:
            lowerValueBucket = (y-1) * dataSize
            upperValueBucket = y * dataSize
        counter = 0
        for index, data in enumerate(heatmapData[lowerTimeBucket:upperTimeBucket]):
            numberData = int(data)
            if upperValueBucket > numberData and lowerValueBucket <= numberData:
                counter = counter + 1
                colList.append(numberData)
        outer[x][y] = counter
    colMax = max(colList)
    colMin = min(colList)
    colMean = mean(colList)
    columnMaxes.append(f'{x} {colMax}\n')
    columnMins.append(f'{x} {colMin}\n')
    columnMeans.append(f'{x} {colMean}\n')


lines = []
for y in range(heatmapSize):
    for x in range(heatmapSize):
        lines.append(f'{y} {x} {outer[x][y]}\n')
    lines.append('\n')

pp = []
for row in outer:
    pp.append(', '.join(map(str, row)))
    pp.append("\n")


ppfile.writelines(pp)
out.writelines(lines)
maxFile.writelines(columnMaxes)
minFile.writelines(columnMins)
meanFile.writelines(columnMeans)
# for row in outer:
#    out.writelines(row)
